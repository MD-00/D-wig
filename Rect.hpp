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
    void gecik();
    void setTxt(std::string fileName);
	void randWeight();
	void textWeight(sf::Text &text);

public:
    sf::RectangleShape body;
    char steer;
    sf::Vector2f main_pos;
    sf::Vector2f size;
    int screenwidth;
    int screenheight;
	int weight;
	bool visibility;
//    std::string fileName;
};

