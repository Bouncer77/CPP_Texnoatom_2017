#ifndef BIG_VECTOR_BOOL_HPP
#define BIG_VECTOR_BOOL_HPP 1

#include <fstream>
#include <memory.h>
#include "bool_space.h"
#include "exceptions.h"
#include "debug_tools.h"
#include <iostream>

namespace big {

    void vector_b<bool>::shrink_alloc(const size_type n_bit) {
        const size_type new_capacity = bit_to_block(n_bit);
        const size_type new_size = std::min(n_bit, size_);

        bit_container_type* tmp_buffer = nullptr;

        try {
            tmp_buffer = new bit_container_type[new_capacity];
        }
        catch (std::bad_alloc) {
            throw big::badAlloc(FULL_COORDINATES_FFL);
        }

        copy_bits(tmp_buffer, data_, new_size, BIT_BLOCK_SIZE);

        clear();

        std::swap(data_, tmp_buffer);
        capacity_ = block_to_bit(new_capacity);
        size_ = new_size;

#ifndef BIG_NDEBUG
        fill_n_bit(size_, capacity_ - size_, POISON<bool>::value);
#endif

        BIG_ASSERT_VALID(this);
    }

    vector_b<bool>::vector_b(const vector_b& that) :
        size_(0),
        capacity_(0),
        data_(nullptr),
        status_valid_(1) {

#ifndef BIG_NDEBUG
        try {
#endif
            shrink_alloc(that.size_);
#ifndef BIG_NDEBUG
        }
        catch (...) {
            status_valid_ = 0;
            throw;
        }
#endif

        copy_bits(data_, that.data_, that.size_, BIT_BLOCK_SIZE);

        size_ = that.size_;

        BIG_ASSERT_VALID(this);
    }

    void vector_b<bool>::resize(const size_type n, const bool value) {
        BIG_ASSERT_VALID(this);

        const size_type new_size = n;

        shrink_alloc(new_size);

        if (new_size > size_) {
            fill_n_bit(size_, new_size - size_, value);
        }

        size_ = new_size;

        BIG_ASSERT_VALID(this);
    }

    void vector_b<bool>::alloc(const size_type n) {
        BIG_ASSERT_VALID(this);

        if (n <= capacity_) {
            return;
        }

        size_type new_capacity = std::max(bit_to_block(capacity_), static_cast<size_type>(1));

        size_type need_capacity = bit_to_block(n);
        while (new_capacity < need_capacity) {
            new_capacity *= MEMORY_MULTIPLIER_;
        }

        shrink_alloc(block_to_bit(new_capacity));

        BIG_ASSERT_VALID(this);
    }

    void vector_b<bool>::fill_n_bit(const size_type begin,
        const size_type n,
        const bool      value) {

        BIG_ASSERT_VALID(this);

        BIG_OUT_OF_RANGE(begin + n > capacity_);

        size_type       it = begin;
        const size_type end = begin + n;

        while (it % BIT_BLOCK_SIZE && it != end) {
            set_bit(it, value);
            ++it;
        }
        while (it + BIT_BLOCK_SIZE <= end) {
            data_[n_block(it)] = value ? ~0 : 0;
            it += BIT_BLOCK_SIZE;
        }
        for (; it < end; ++it) {
            set_bit(it, value);
        }

        BIG_ASSERT_VALID(this);
    }

    bool vector_b<bool>::erase(const size_type pos) {
        BIG_ASSERT_VALID(this);

        if (pos >= size_) {
            return false;
        }

        size_type it = pos;
        --size_;

        while (it % BIT_BLOCK_SIZE && it != size_) {
            set_bit(it, get_bit(it + 1));
            ++it;
        }
        while (it + BIT_BLOCK_SIZE <= size_) {
            data_[n_block(it)] >>= 1;
            it += BIT_BLOCK_SIZE;
        }
        for (; it < size_; ++it) {
            set_bit(it, get_bit(it + 1));
        }

#ifndef BIG_NDEBUG
        set_bit(size_, POISON<bool>::value);
#endif
        BIG_ASSERT_VALID(this);
        return true;
    }


    vector_b<bool>::size_type
        vector_b<bool>::count() const {
        BIG_ASSERT_VALID(this);

        size_type result = 0;
        size_type count_blocks = size_ / BIT_BLOCK_SIZE;

        for (size_type i = 0; i < count_blocks; ++i) {
            bit_container_type copy_block = data_[i];
            while (copy_block) {
                result += last_bit(copy_block);
                copy_block >>= 1;
            }
        }
        if (data_) {
            bit_container_type copy_block = data_[count_blocks];
            for (size_type i = block_to_bit(count_blocks); i < size_; ++i) {
                result += last_bit(copy_block);
                copy_block >>= 1;
            }
        }

        return result;
    }

    void vector_b<bool>::invert() {
        BIG_ASSERT_VALID(this);

        const size_type count_blocks = size_ / BIT_BLOCK_SIZE;

        for (size_type i = 0; i < count_blocks; ++i) {
            data_[i] = ~data_[i];
        }

        const size_type remain_bits = size_ % BIT_BLOCK_SIZE;
        const size_type first_remaim_bit = block_to_bit(count_blocks);

        for (size_type i = 0; i < remain_bits; ++i) {
            flip(first_remaim_bit + i);
        }

        BIG_ASSERT_VALID(this);
    }

    void vector_b<bool>::dump(const char* file,
        const char* function_name,
        int         line_number,
        const char* output_file) const {

        std::ofstream fout(output_file, std::ios_base::app);

        BIG_BAD_STREAM(!fout.is_open());

        fout << "-------------------\n"
            "Class vector_b:\n"
            "time: " << __TIME__ << "\n"
            "file: " << file << "\n"
            "function: " << function_name << "\n"
            "line: " << line_number << "\n"
            "status: " << (is_valid() ? "ok\n{\n" : "FAIL\n{\n");
        fout << "\tsize: " << size_ << "\n"
            "\tcapacity: " << capacity_ << "\n"
            "\tfield_status: " << (status_valid_ ? "ok\n\n" : "fail\n\n");

#ifndef BIG_NWRITE
        try {
            for (size_type i = 0; i < size_; ++i) {
                fout << "\t* [" << i << "] =  " << get_bit_dump_version(i) << "\n";
            }
            for (size_type i = size_; i < capacity_; ++i) {
                fout << "\t  [" << i << "] =  " << get_bit_dump_version(i)
                    << (get_bit_dump_version(i) != POISON<bool>::value ? "\t//ERROR!\n" : "\n");
            }
        }
        catch (...) {
            fout << "ERROR with output\n";
        }
#endif
        fout << "}\n"
            "-------------------\n";

        fout.close();
    }

}

#endif // BIG_VECTOR_BOOL_HPP