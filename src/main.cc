#include "vector.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };
    Vector vec { 300, 300 }; 
    
    while ( window.isOpen() )
    {
        sf::Event event = {};
        while ( window.pollEvent( event) )
        {
            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
        }

        window.clear();
        vec.draw( window, sf::Vector2f { 1920.f / 2, 1200.f / 2 });
        vec.rotate( 3.14f / 60);
        window.display();
    }

    return 0;
            
}
