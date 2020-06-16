#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <cmath>
#include <time.h>
#include <sstream>

const int MAX_CRANE_WEIGHT = 15; // udzwig to 15t
const int SCREEN_WIDTH = 1260;   //rozdzielczosc
const int SCREEN_HEIGHT = 800;

int main(int argc, const char * argv[]) {
    srand(time(0));
    sf::RenderWindow window (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dzwig"); //renderowanie okna
    
    
    window.setFramerateLimit(60);   //ustawienie limitu klatek
    
    Rect *suwak;                   //utworzenie obiektu suwaka
    suwak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 80.0f, 33.0f, 'a');
    suwak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2-250.0f); // -250 zeby tlo sie zgralo
    
    Rect *hak;                    //utworzenie obiektu haka
    hak = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 20.0f, 40.0f, 'b');
    hak->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-250.0f); //+85 zeby bylo pod suwakiem, -250 zeby tlo sie zgralo
    
    
    sf::Texture hakTxt;               //wczytanie tekstury haka
    hakTxt.loadFromFile("hak.png");
    hak->body.setTexture(&hakTxt);
    
    sf::Texture suwakTxt;            //wczytanie tekstury suwaka
    suwakTxt.loadFromFile("suwak.png");
    suwak->body.setTexture(&suwakTxt);
    
    Rect *box;                       //wczytanie tekstury boxa
    box = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 50.0f, 50.0f, 'c');
    box->setPos((float)SCREEN_WIDTH-500.0f, (float)SCREEN_HEIGHT-25.0f);
    box->setColor(sf::Color::Red);
    
    box->randWeight(); // losowanie wagi
    
    sf::Text text;
    sf::Font font;
    
    if (!font.loadFromFile("arial.otf"))  //zaladowanie czcionki
        throw("Nie zaladowano czcionki");
	box->visibility = true;              //ustawienie widocznosci napisu

    
    Rect *lina;                         //utworzenie obiektu liny
    lina = new Rect(SCREEN_WIDTH, SCREEN_HEIGHT, 5.0f, 100.0f, 'a');
    lina->setPos((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2+85.0f-280.0f);
    lina->setColor(sf::Color::Black);
    
    
    sf::Texture bckgrnd;             //wczytanie tla
    if(!bckgrnd.loadFromFile("background.png"))
        std::cout << "Nie zaladowano tekstury bckgrnd" << std::endl;
    
    sf::Sprite background(bckgrnd);
    
    while(window.isOpen()){  //glowna petla programu
        sf::Event event;
		window.setKeyRepeatEnabled(false);
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::N)
					box->weight += 1;

				else if (event.key.code == sf::Keyboard::Key::M && box->weight>1)
					box->weight -= 1;
			}
        }

		if (box->weight > MAX_CRANE_WEIGHT) 		
			box->steer = 'c';

        std::stringstream textbox;
        textbox << "Ciezar boxa:  " << box->weight << "t";
        text.setFont(font);
        text.setCharacterSize(16);
        text.setPosition(50.0f, 25.0f);
        text.setFillColor(sf::Color::Black);
        text.setString(textbox.str());

        sf::Vector2f zmiana_liny;              //aktualizacja dlugosci liny
        zmiana_liny.x=5.0f;
        zmiana_liny.y=(float)abs(suwak->body.getPosition().y - hak->body.getPosition().y)-5.0f; //-5.0f zeby pokryc braki przy rysowaniu
        lina->body.setSize(zmiana_liny);
        
        
        //podnoszenie obiektu
        if(hak->body.getGlobalBounds().intersects(box->body.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
            
            if (box->weight > MAX_CRANE_WEIGHT)
                box->steer = 'c';

            else box->steer='b';
        }
        
        //upuszczanie obiektu
        if (box->steer=='b' || box->steer=='c')
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                box->steer='c';

        //opadanie obiektu
        sf::Vector2f fall=box->body.getPosition();
        if(fall.y<SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f && box->steer=='c'){
            float speed = 30.0f;
            box->body.setPosition(fall.x, fall.y+speed);
        }

        if(fall.y>SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f && box->steer=='c')     //konieczna korekta wysokosci!! bez tego sie buguje           
            box->body.setPosition(fall.x, SCREEN_HEIGHT-(box->body.getSize().y/2)-3.0f);

        
        window.clear();          //clearowanie okna
        window.draw(background);  //ustawienie tla
        
        box->Update();         //update obiektu
        box->Draw(window);     //rysowanie obiektu
        
        lina->Update();
        lina->Draw(window);
     
        suwak->Update();
        suwak->Draw(window);
        
        hak->Update();
        hak->Draw(window);
               
        
        window.draw(text);   //rysowanie tekstu o aktualnej wadze obiektu

        window.display();
                       
        //warunek taki na koncu, zeby sie nic nie rozjezdzalo, wszystko pod suwak (suwak jest glownym punktem zaczepienia)
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
