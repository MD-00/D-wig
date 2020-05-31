#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <iostream>



Rect::Rect(int SCREEN_WIDTH, int SCREEN_HEIGHT, float size_x, float size_y, char steer_select)
{
    screenwidth=SCREEN_WIDTH;
    screenheight=SCREEN_HEIGHT;
    sf::Vector2f bodySize(size_x, size_y);
    body.setSize(bodySize);
    size.x=size_x;
    size.y=size_y;

    body.setOrigin(bodySize.x/2, bodySize.y/2);
    
    

    
    steer=steer_select;
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            movement.x-=20.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            movement.x+=20.0f;
        }
        body.move(movement.x, movement.y);
    }
    if(steer=='b'){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            movement.x-=20.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            movement.x+=20.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            movement.y-=20.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            movement.y+=20.0f;
        }
        
        
        
        //if(body.getPosition().x<=screenwidth-size.x/2 && body.getPosition().y<=screenheight-size.y/2){
            body.move(movement.x, movement.y);
        //}
    }
}

void Rect::gecik(){
    sf::Vector2f xd = body.getSize();
    
}


void Rect::setTxt(std::string fileName){
        sf::Texture bodyTexture;
    
        bodyTexture.loadFromFile(fileName);
        body.setTexture(&bodyTexture);
//        sf::Vector2u textureSize = bodyTexture.getSize();
//        textureSize.x /= 3;
//        textureSize.y /=9;
//        body.setTextureRect(sf::IntRect(textureSize.x*2, textureSize.y*3, textureSize.x, textureSize.y));
}
