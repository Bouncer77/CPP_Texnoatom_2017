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
    //    //heroImage.createMaskFromColor(sf::Color(0, 0, 0)); // ������ �����
    // ������� ������������ ���� � ��������

    //heroSprite.setRotation(90); //��������� ������ �� 90 ��������

    /*sf::Texture herotexture;
    if (!herotexture.loadFromFile("images/hero.png"))
        std::cout << "Error!" << std::endl;
    
    sf::Sprite heroSprite;
    heroSprite.setTexture(herotexture);
    heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96));
    heroSprite.setPosition(100, 100);*/

    Player p1("hero.png", 250, 250, 96, 96);

    sf::Clock clock;
    float CurrentFrame = 0; // ������ ������� ����

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
        clock.restart();                                      //������������� �����
        time = time / 800;                                    //�������� ����

         ///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) 
        {
            p1.setDir(1);       //dir =1 - ����������� �����, speed =0.1 - �������� ��������.
            p1.setSpeed(0.1);   //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
             
            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) 
        {

            p1.setDir(0);       //dir =1 - ����������� �����, speed =0.1 - �������� ��������.
            p1.setSpeed(0.1);   //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���

            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) 
        {
            p1.setDir(3);       //dir =1 - ����������� �����, speed =0.1 - �������� ��������.
            p1.setSpeed(0.1);   //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���

            CurrentFrame += 0.005*time;

            if (CurrentFrame >= 3) CurrentFrame -= 3;
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

        }

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) 
        {
            p1.setDir(2);       //dir =1 - ����������� �����, speed =0.1 - �������� ��������.
            p1.setSpeed(0.1);   //�������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���

            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������

            if (CurrentFrame >= 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
            p1.getSprite().setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

        }

        p1.update(time);// �������� ������ p ������ Player � ������� ������� sfml, 
                            // ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������


        window.clear(sf::Color::Black);
        window.draw(p1.getSprite());//������ ������ ������� p ������ player
        window.display();
    }

    return 0;
}

//    while (window.isOpen())
//    {
//
//        float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
//        clock.restart(); //������������� �����
//        time = time / 800; //�������� ����
//
//
//
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) { heroSprite.move(-0.1*time, 0); heroSprite.setTextureRect(sf::IntRect(0, 96, 96, 96)); } //���������� Y, �� ������� ����� ��������� ������ ����� ����� 96
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) { heroSprite.move(0.1*time, 0); heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96)); } //���������� Y, �� ������� ����� ��������� ������ ������ ����� 96+96=192
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W))) { heroSprite.move(0, -0.1*time); heroSprite.setTextureRect(sf::IntRect(0, 288, 96, 96)); } //���������� Y �� ������� ����� ��������� ������ ����� ����� 288
//        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S))) { heroSprite.move(0, 0.1*time); heroSprite.setTextureRect(sf::IntRect(0, 0, 96, 96)); } //���������� 0, ��� ������� ����� ����������� � ������, �� ��� � ������������� ������� ������������ �� 96.
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 96, 96, 96)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
//            heroSprite.move(-0.1*time, 0);//���������� ���� �������� ��������� �����
//        }
//
//        //if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//        //    CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//        //    if (CurrentFrame >= 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
//        //    heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 192, 96, 96)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
//        //    heroSprite.move(0.1*time, 0);//���������� ���� �������� ��������� �����
//        //}
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame) + 96, 96, -96, 96)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
//            heroSprite.move(0.1*time, 0);//���������� ���� �������� ��������� �����
//        }
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 288, 96, 96)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
//            heroSprite.move(0, -0.1*time);//���������� ���� �������� ��������� �����
//        }
//
//        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
//            CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
//            if (CurrentFrame >= 3) CurrentFrame -= 3; // ���� ������ � �������� ����� - ������������ �����.
//            heroSprite.setTextureRect(sf::IntRect(96 * int(CurrentFrame), 0, 96, 96)); //���������� �� ����������� �. ���������� �������� ��������� � ���������� � ������ 0,96,96*2, � ����� 0
//            heroSprite.move(0, 0.1*time);//���������� ���� �������� ��������� �����
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

//window.clear(); � ������� �����.
//window.draw(shape); � ������ ������.
//window.display(); � �� ��� ����������.