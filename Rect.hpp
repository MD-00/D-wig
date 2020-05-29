#pragma once
#include <SFML/Graphics.hpp>


class Rect{
public:
    Rect(int SCREENWIDTH, int SCREENHEIGHT, float size_x, float size_y, char steer_select);
    ~Rect();
    void setPos(float setPos_x, float setPos_y);
    void Draw(sf::RenderWindow &window);
    void Update();
    void setColor(sf::Color color);
//    void gecik();
    

private:
    sf::RectangleShape body;
    char steer; 
};

