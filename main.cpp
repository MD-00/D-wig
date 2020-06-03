//podnoszenie na enter
//opuszczanie na spacji
//poruszanie sie wasd

//Zmiany:
//zmniejszanie/zwiekszanie wagi na N/M
//przeniesienie textboxa do glownej petli, zeby sie aktualizowal wraz ze zmiana wagi

//do zrobienia:
//przeniesc textboxa do klasy, bo przy wiekszej ilosci obiektow bedzie potrzebna wieksza ilosc textboxow
// no i znowu kod uporzadkowac
// i moze zrobic tak, ze jedno wcisniecie m -> zwiekszenie wagi dokladnie o 1, bo teraz dziala na zasadzie isKeyPressed i za duzo sie zwieksza


#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <cmath>
#include <time.h>
#include <sstream>

const int MAX_CRANE_WEIGHT = 15; // udzwig to 15t
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 800;

int main(int argc, const char * argv[]) {
    srand(time(0));
    sf::RenderWindow window (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dzwig");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    
    Rect *suwak;
    suwak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 80.0f, 33.0f, 'a');
    suwak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2-250.0f); // -250 zeby tlo sie zgralo
    
    Rect *hak;
    hak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 20.0f, 40.0f, 'b');
    hak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-250.0f); //+85 zeby bylo pod suwakiem, -250 zeby tlo sie zgralo
    
    
    sf::Texture hakTxt;
    hakTxt.loadFromFile("hak.png");
    hak->body.setTexture(&hakTxt);
    
    sf::Texture suwakTxt;
    suwakTxt.loadFromFile("suwak.png");
    suwak->body.setTexture(&suwakTxt);
    
    
    
    Rect *box;
    box = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 50.0f, 50.0f, 'c');
    box->setPos((float)SCREEN_WIDTH-500.0f, (float)SCREEN_HEIGHT-25.0f);
    box->setColor(sf::Color::Green);
    
    box->randWeight(); // losowanie wagi
    
    sf::Text text; // wyswietlanie tekstu dla boxa, w funkcji cos nie dziala - trzeba dopracowac
    sf::Font font;
    if (!font.loadFromFile("arial.otf"))
        throw("Nie zaladowano czcionki");



    
    Rect *lina;
    lina = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 5.0f, 100.0f, 'a');
    lina->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-280.0f);
    lina->setColor(sf::Color::Black);
    
    
    sf::Texture bckgrnd;
    if(!bckgrnd.loadFromFile("background.png")){
        std::cout << "Nie zaladowano tekstury bckgrnd" << std::endl;
    }
    sf::Sprite background(bckgrnd);
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        std::stringstream textbox;
        textbox << "Ciezar boxa:  " << box->weight << "t";
        text.setFont(font);
        text.setCharacterSize(16);
        text.setPosition(50.0f, 25.0f);
        text.setFillColor(sf::Color::Black);
        text.setString(textbox.str());
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)){
            box->weight+=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)){
            box->weight-=1;
        }
        
        sf::Vector2f zmiana_liny;
        zmiana_liny.x=5.0f;
        zmiana_liny.y=(float)abs(suwak->body.getPosition().y - hak->body.getPosition().y)-5.0f; //-5.0f zeby pokryc braki przy rysowaniu
        lina->body.setSize(zmiana_liny);
        
        if(hak->body.getGlobalBounds().intersects(box->body.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
            
            box->visibility = true;
            if (box->weight > MAX_CRANE_WEIGHT)
            {
                box->steer = 'c';
            }
            else box->steer='b';
        }
        
        if (box->steer=='b' || box->steer=='c'){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                box->steer='c';
                box->visibility = false;

            }
        }
        

        
        sf::Vector2f fall=box->body.getPosition();
        if(fall.y<SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f && box->steer=='c'){
            float speed = 30.0f;
            box->body.setPosition(fall.x, fall.y+speed);
        }
        if(fall.y>SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f && box->steer=='c'){       //konieczna korekta wysokosci!! bez tego sie buguje
            
            box->body.setPosition(fall.x, SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f);
        }
        
        window.clear();
        window.draw(background);
        
        box->Update();
        box->Draw(window);
        
        lina->Update();
        lina->Draw(window);
     
        suwak->Update();
        suwak->Draw(window);
        
        hak->Update();
        hak->Draw(window);
    
        
        
        if(box->visibility)
            window.draw(text);

        window.display();
        
        
        
        //warunek taki na koncu, zeby sie nic nie rozjezdzalo, wszystko pod suwak
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
