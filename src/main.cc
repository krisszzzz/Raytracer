#include "vector.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>

void
sphere_raycast( sf::RenderWindow& window,
                const Point2f centre,
                const Point3f light_pos,
                const float radius);

int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };
    Vector vec { 300, 300, 300 }; 
    
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

        sphere_raycast( window,
                        Point2f { 1920.f / 2, 1200.f / 2 },
                        Point3f { 0, 10000, 0 },
                        500);
        window.display();
    }

    return 0;
            
}
