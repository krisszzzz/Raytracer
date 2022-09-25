#include <stdio.h>
#include "raycaster.h"

   
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

        sf::Color color = {};
        color.a = 255;
        color.b = 0;
        color.r = 50;
        color.g = 0;

        sphere_raycast( window,
                        Point2f { 1920 / 2.f, 1200 / 2.f },
                        Point3f { 0, 0, 2000 },
                        
                        400,
                        color
                       );
        
        window.display();
    }

    return 0;
            
}
