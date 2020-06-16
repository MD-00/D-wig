#include <SFML/Graphics.hpp>


class Rect{
public:
    Rect(int SCREENWIDTH, int SCREENHEIGHT, float size_x, float size_y, char steer_select);  //konstruktor
    ~Rect();
    void setPos(float setPos_x, float setPos_y);   //ustawianie pozycji
    void Draw(sf::RenderWindow &window);           //rysowanie obiektu
    void Update();                                 //updatowanie obiektu
    void setColor(sf::Color color);                //ustawienie koloru
    void randWeight();                              //wylosowanie poczatkowej wagi
    void textWeight(sf::Text &text);
    
public:
    sf::RectangleShape body;                     //cialo obiektu
    sf::Vector2f main_pos;                       //aktualna pozycja
    char steer;                                  //typ sterowania
    int weight;                                  //aktualna waga obiektu
    bool visibility;      
};

