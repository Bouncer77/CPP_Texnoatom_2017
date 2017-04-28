#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Point
{
public:
    Point() :
        m_x(0),
        m_y(0)
    {}

    Point(float x, float y) :
        m_x(x),
        m_y(y)
    {}

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    float getX() { return m_x; }
    float getY() { return m_y; }

private:
    float m_x, m_y;
};

class Player
{
public:
    //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
    Player(sf::String file_name, float x, float y, float w, float h) 
    { 
        m_dx = 0; m_dy = 0;
        m_speed = 0; m_dir = 0;
        m_file_name = file_name;                //��� �����+����������
        m_width = w; m_height = h;//������ � ������

        //���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������.
            // � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
        if (!m_image.loadFromFile("images/" + m_file_name))
        {
            std::cout << "Failed upload image" << std::endl;
        }

        m_image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ���� (���� ��� ������)
        m_texture.loadFromImage(m_image);//���������� ���� ����������� � ��������
        m_sprite.setTexture(m_texture);//�������� ������ ���������
        m_point.setX(x);    //���������� ��������� �������
        m_point.setY(y); 
        m_sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
    }

    //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
    void update(float time) 
    {
        /* m_dir = 0   - �������� ������
                 = 1   - �����
                 = 2   - ����
                 = 3   - �����              */
        switch (m_dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
        {
            case 0: m_dx = m_speed;   m_dy = 0;         break;      //�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
            case 1: m_dx = -m_speed;  m_dy = 0;         break;     //�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
            case 2: m_dx = 0;         m_dy = m_speed;   break;      //�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
            case 3: m_dx = 0;         m_dy = -m_speed;   break;     //�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
        }

        m_point.setX(m_point.getX() + m_dx * time); //�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
        m_point.setY(m_point.getY() + m_dy * time); //���������� �� ������

        m_speed = 0;                //�������� ��������, ����� �������� �����������.
        m_sprite.setPosition(m_point.getX(), m_point.getY()); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
    }

    // Set'���
    void setHeight(float h) { m_height = h; }
    void setWidth(float w) { m_width = w; }
    void setSpeed(float speed) { m_speed = speed; }
    void setDx(float dx) { m_dx = dx; }
    void setDy(float dy) { m_dy = dy; }
    void setDir(float dir) { m_dir = dir; }

    // Get'���
    sf::String getFileName() { return m_file_name; }
    sf::Image& getImage() { return m_image; }
    sf::Texture& getTexture() { return m_texture; }
    sf::Sprite& getSprite()  { return m_sprite; }
    Point getPoint() const { return m_point; }
    float getHeight() const { return m_height; }
    float getWidth() const { return m_width; }
    float getSpeed() const { return m_speed; }
    float getDx() const { return m_dx; }
    float getDy() const { return m_dy; }
    int getDir() const { return m_dir; }
    


private:
    sf::String m_file_name;         // �������� ����� + ����������
    sf::Image m_image;              // sfml �����������
    sf::Texture m_texture;          // sfml ��������
    sf::Sprite m_sprite;            // sfml ������
    Point m_point;                  // ����������
    float m_height,  m_width,       // ������, ������
          m_speed = 0,              // ��������
          m_dx, m_dy;               // ���������                  ���������� �� � � y �� ���� ���� ����������
    int   m_dir = 0;                // direction - ����������� �������� ������
   
};