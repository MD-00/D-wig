#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect.hpp"



const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, const char * argv[]) {
    sf::RenderWindow window (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dzwig");
    window.setFramerateLimit(60);
    Rect *suwak;
    suwak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 175.0f, 100.0f, 'a');
    suwak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2-350.0f);
    suwak->setColor(sf::Color::Red);
    
    Rect *hak;
    hak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 30.0f, 70.0f, 'b');
    hak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-350.0f);
    hak->setColor(sf::Color::Black);
    
    
    
    
    float deltaTime = 0.0f;
    sf::Clock clock;
    
    while(window.isOpen()){
        deltaTime = clock.restart().asSeconds();
        
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear(sf::Color::White);
        hak->Update();
        hak->Draw(window);
        suwak->Update();
        suwak->Draw(window);
//        suwak->gecik();
        window.display();
    }
    delete hak;
    delete suwak;
    return EXIT_SUCCESS;
}
