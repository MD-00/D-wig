#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <iostream>


Rect::Rect(int SCREEN_WIDTH, int SCREEN_HEIGHT, float size_x, float size_y, char steer_select)
{
    sf::Vector2f bodySize(size_x, size_y);
    body.setSize(bodySize);
    body.setOrigin(bodySize.x/2, bodySize.y/2); //ustalenie srodka kazdego recta
    steer=steer_select;
    weight = 0;
}

Rect::~Rect(){
    
}

void Rect::setPos(float setPos_x, float setPos_y){
    body.setPosition(setPos_x, setPos_y);
    main_pos.x=setPos_x;
    main_pos.y=setPos_y;
}

void Rect::Draw(sf::RenderWindow &window){
    window.draw(body);
}

void Rect::setColor(sf::Color color){
    body.setFillColor(color);
}

void Rect::Update(){
    sf::Vector2f movement(0.0f, 0.0f);

    if(steer=='a'){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && body.getPosition().x >= 130.0f){
				movement.x -= 20.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && body.getPosition().x <= 790.0f){
            movement.x+=20.0f;
        }
        body.move(movement.x, movement.y);
    }
	if (steer == 'b') {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && body.getPosition().x >= 130.0f) 
		{
			movement.x -= 20.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && body.getPosition().x <= 790.0f)
		{
			movement.x += 20.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && body.getPosition().y >= 200.0f) {
			movement.y -= 20.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && body.getPosition().y <= 780.0f) {
			movement.y += 20.0f;
		}

            body.move(movement.x, movement.y);

    }
}

void Rect::randWeight()
{
    weight = rand() % 20 + 5;
}
