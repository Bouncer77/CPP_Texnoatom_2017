#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"


//#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(650, 650), "RPG");

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Red);

    //sf::Image heroImage;
    //    //heroImage.loadFromFile("");
    //    //heroImage.createMaskFromColor(sf::Color(0, 0, 0)); // задать маску
    // убирает определенный цвет в картинке

    //heroSprite.setRotation(90); //повернули спрайт на 90 градусов

    /*sf::Texture herotexture;
    if (!herotexture.loadFromFile("images/hero.png"))
        std::cout << "Error!" << std::endl;
    
    sf::Sprite heroSprite;
    heroSprite.setTexture(herotexture);
    heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96));
    heroSprite.setPosition(100, 100);*/

    Player p1("hero.png", 250, 250, 96, 96);

    sf::Clock clock;
    float CurrentFrame = 0; // хранит текущий кадр

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart();                                      //перезагружает время
        time = time / 800;                                    //скорость игры

         ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) 
        {
            p1.setDir(1);       //dir =1 - направление вверх, speed =0.1 - скорость движения.
            p1.setSpeed(0.1);   //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
             
            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) 
        {

            p1.setDir(0);       //dir =1 - направление вверх, speed =0.1 - скорость движения.
            p1.setSpeed(0.1);   //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз

            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) 
        {
            p1.setDir(3);       //dir =1 - направление вверх, speed =0.1 - скорость движения.
            p1.setSpeed(0.1);   //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз

            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) 
        {
            p1.setDir(2);       //dir =1 - направление вверх, speed =0.1 - скорость движения.
            p1.setSpeed(0.1);   //Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз

            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации

            if (CurrentFrame >= 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

        }

        p1.update(time);// оживляем объект p класса Player с помощью времени sfml, 
                            // передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться


        window.clear(sf::Color::Black);
        window.draw(p1.getSprite());//рисуем спрайт объекта p класса player
        window.display();
    }

    return 0;
}

//    while (window.isOpen())
//    {
//
//        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
//        clock.restart(); //перезагружает время
//        time = time / 800; //скорость игры
//
//
//
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) { heroSprite.move(-0.1*time, 0); heroSprite.setTextureRect(sf::IntRect(0, 96, 96, 96)); } //координата Y, на которой герой изображен идущим влево равна 96
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) { heroSprite.move(0.1*time, 0); heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96)); } //координата Y, на которой герой изображен идущем вправо равна 96+96=192
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) { heroSprite.move(0, -0.1*time); heroSprite.setTextureRect(sf::IntRect(0, 288, 96, 96)); } //координата Y на которой герой изображен идущим вверх равна 288
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) { heroSprite.move(0, 0.1*time); heroSprite.setTextureRect(sf::IntRect(0, 0, 96, 96)); } //координата 0, это верхняя часть изображения с героем, от нее и отталкиваемся ровными квадратиками по 96.
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) { //если нажата клавиша стрелка влево или англ буква А
//            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//            heroSprite.move(-0.1*time, 0);//происходит само движение персонажа влево
//        }
//
//        //if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) { //если нажата клавиша стрелка влево или англ буква А
//        //    CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//        //    if (CurrentFrame >= 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
//        //    heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//        //    heroSprite.move(0.1*time, 0);//происходит само движение персонажа влево
//        //}
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) { //если нажата клавиша стрелка влево или англ буква А
//            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame) + 96, 96, -96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//            heroSprite.move(0.1*time, 0);//происходит само движение персонажа влево
//        }
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { //если нажата клавиша стрелка влево или англ буква А
//            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//            heroSprite.move(0, -0.1*time);//происходит само движение персонажа влево
//        }
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
//            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
//            heroSprite.move(0, 0.1*time);//происходит само движение персонажа влево
//        }
//
//
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            heroSprite.setColor(sf::Color::Red);
//        }
//
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//        {
//            heroSprite.setColor(sf::Color::Green);
//        }
//
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear(sf::Color::Black);
//        window.draw(heroSprite);
//        window.display();
//    }
//
//    return 0;
//}
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(640, 480), "Lesson 3. My SFML2");
//    
//    
//
//    sf::Texture herotexture;
//    if (!herotexture.loadFromFile("images/hero.png"))
//        std::cout << "Error!" << std::endl;
//
//    sf::Sprite heroSprite;
//    heroSprite.setPosition(50, 25);
//
//
//
//
//    while (window.isOpen())
//    {
//
//
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(heroSprite);
//        window.display();
//    }
//
//    return 0;
//}

//window.clear(); – очищает экран.
//window.draw(shape); – рисует объект.
//window.display(); – всё это показывает.