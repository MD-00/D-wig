#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <iostream>
#include <sstream>


Rect::Rect(int SCREEN_WIDTH, int SCREEN_HEIGHT, float size_x, float size_y, char steer_select)
{
    screenwidth=SCREEN_WIDTH;
    screenheight=SCREEN_HEIGHT;
    sf::Vector2f bodySize(size_x, size_y);
    body.setSize(bodySize);
    size.x=size_x;
    size.y=size_y;
	weight = 0;
    body.setOrigin(bodySize.x/2, bodySize.y/2);
    steer=steer_select;
	visibility = false;
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

void Rect::gecik() {
	sf::Vector2f xd = body.getSize();
}

void Rect::randWeight()
{
	weight = rand() % 20 + 5;
}

/*
void Rect::textWeight(sf::Text &text) {
	sf::Font font;
	if (!font.loadFromFile("arial.otf"))
		throw("Nie zaladowano czcionki");
	std::stringstream textbox;
	textbox << "Ciezar boxa:  " << weight << "t";
	text.setFont(font);
	text.setCharacterSize(16);
	text.setPosition(50.0f, 25.0f);
	text.setFillColor(sf::Color::Black);
	text.setString(textbox.str());

}
*/
void Rect::setTxt(std::string fileName){
        sf::Texture bodyTexture;
    
        bodyTexture.loadFromFile(fileName);
        body.setTexture(&bodyTexture);
//        sf::Vector2u textureSize = bodyTexture.getSize();
//        textureSize.x /= 3;
//        textureSize.y /=9;
//        body.setTextureRect(sf::IntRect(textureSize.x*2, textureSize.y*3, textureSize.x, textureSize.y));
}
