//podnoszenie na enter
//opuszczanie na spacji
//poruszanie sie wasd




#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include<cmath>


const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 800;

int main(int argc, const char * argv[]) {
    sf::RenderWindow window (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dzwig");
    window.setFramerateLimit(60);
    Rect *suwak;
    suwak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 80.0f, 33.0f, 'a');
    suwak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2-250.0f);
    suwak->setColor(sf::Color::Red);
    
    Rect *hak;
    hak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 20.0f, 40.0f, 'b');
    hak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-250.0f);
    hak->setColor(sf::Color::Black);
    
    
    sf::Texture txt;
    txt.loadFromFile("hak.png");
    hak->body.setTexture(&txt);
    
    Rect *box;
    box = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 50.0f, 50.0f, 'c');
    box->setPos((float)SCREEN_WIDTH-25.0f, (float)SCREEN_HEIGHT-25.0f);
    box->setColor(sf::Color::Green);
    
    Rect *lina;
    lina = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 1.5f, 100.0f, 'a');
    lina->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-280.0f);
    lina->setColor(sf::Color::Black);
    
    
    sf::Texture bckgrnd;
    if(!bckgrnd.loadFromFile("xd.png")){
        std::cout << "Nie zaladowano tekstury bckgrnd" << std::endl;
    }
    sf::Sprite background(bckgrnd);
    
    hak->setTxt("tux.png");
    
    float deltaTime = 0.0f;
    sf::Clock clock;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
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
        
        sf::Vector2f xdd;
        xdd.x=5.0f;
        xdd.y=(float)abs(suwak->body.getPosition().y - hak->body.getPosition().y)-5.0f;
        lina->body.setSize(xdd);

        
        if(hak->body.getGlobalBounds().intersects(box->body.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
            box->steer='b';
        }
        
        if (box->steer=='b'){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                box->steer='c';

            }
        }
        
         sf::Vector2f xd=box->body.getPosition();
        if(xd.y<SCREEN_HEIGHT-(box->size.y/2)-3.0f && box->steer=='c'){
            float speed = 30.0f;
            box->body.setPosition(xd.x, xd.y+speed);
        }
        if(xd.y>SCREEN_HEIGHT-(box->size.y/2)-3.0f && box->steer=='c'){       //konieczna korekta wysokosci!! bez tego sie buguje
            
            box->body.setPosition(xd.x, SCREEN_HEIGHT-(box->size.y/2)-3.0f);
        }

        
        
        
        
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                lina->body.move(-20.0f, 0.0f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                lina->body.move(20.0f, 0.0f);
            }
        
        
        
        
        window.clear();
        window.draw(background);
        box->Update();
        box->Draw(window);
        lina->Draw(window);
     
        suwak->Update();
        suwak->Draw(window);
        hak->Update();
        hak->Draw(window);
    
        window.display();
        
        
        
        //warunek taki na koncu, zeby sie nic nie rozjezdzalo
        if(hak->body.getPosition().x!=suwak->body.getPosition().x || lina->body.getPosition().x!=suwak->body.getPosition().x ){
            float y_hak = hak->body.getPosition().y;
            float y_lina = lina->body.getPosition().y;
            
            hak->body.setPosition(suwak->body.getPosition().x, y_hak);
            lina->body.setPosition(suwak->body.getPosition().x, y_lina);
        }
        

    }
    delete hak;
    delete suwak;
    delete box;
    return EXIT_SUCCESS;
}
