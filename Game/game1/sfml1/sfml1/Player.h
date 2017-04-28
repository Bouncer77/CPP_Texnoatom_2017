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
    //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
    Player(sf::String file_name, float x, float y, float w, float h) 
    { 
        m_dx = 0; m_dy = 0;
        m_speed = 0; m_dir = 0;
        m_file_name = file_name;                //имя файла+расширение
        m_width = w; m_height = h;//высота и ширина

        //запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта.
            // В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
        if (!m_image.loadFromFile("images/" + m_file_name))
        {
            std::cout << "Failed upload image" << std::endl;
        }

        m_image.createMaskFromColor(sf::Color(41, 33, 59));//убираем ненужный темно-синий цвет (тень под волком)
        m_texture.loadFromImage(m_image);//закидываем наше изображение в текстуру
        m_sprite.setTexture(m_texture);//заливаем спрайт текстурой
        m_point.setX(x);    //координата появления спрайта
        m_point.setY(y); 
        m_sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
    }

    //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
    void update(float time) 
    {
        /* m_dir = 0   - движение вправо
                 = 1   - влево
                 = 2   - вниз
                 = 3   - вверх              */
        switch (m_dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
        {
            case 0: m_dx = m_speed;   m_dy = 0;         break;      //по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
            case 1: m_dx = -m_speed;  m_dy = 0;         break;     //по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
            case 2: m_dx = 0;         m_dy = m_speed;   break;      //по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
            case 3: m_dx = 0;         m_dy = -m_speed;   break;     //по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
        }

        m_point.setX(m_point.getX() + m_dx * time); //то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
        m_point.setY(m_point.getY() + m_dy * time); //аналогично по игреку

        m_speed = 0;                //зануляем скорость, чтобы персонаж остановился.
        m_sprite.setPosition(m_point.getX(), m_point.getY()); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }

    // Set'еры
    void setHeight(float h) { m_height = h; }
    void setWidth(float w) { m_width = w; }
    void setSpeed(float speed) { m_speed = speed; }
    void setDx(float dx) { m_dx = dx; }
    void setDy(float dy) { m_dy = dy; }
    void setDir(float dir) { m_dir = dir; }

    // Get'еры
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
    sf::String m_file_name;         // название файла + расширение
    sf::Image m_image;              // sfml изображение
    sf::Texture m_texture;          // sfml текстура
    sf::Sprite m_sprite;            // sfml спрайт
    Point m_point;                  // координыты
    float m_height,  m_width,       // высота, ширина
          m_speed = 0,              // скорость
          m_dx, m_dy;               // ускорение                  приращение по х и y за один цикл обновления
    int   m_dir = 0;                // direction - направление движения игрока
   
};