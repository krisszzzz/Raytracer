#include <stdio.h>
#include "raycaster.h"
#include "raytracer.h"
   
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


        // Sphere sphere { sf::Color::Green, Vector { 960, 600, 0 }, 200 };
        // raytracer( window, 1920, 1200, &sphere, Vector { 20000, 600, 1500 }); 

        sf::Color color = {};
        // color.a = 50;
        // color.b = 50;
        // color.r = 50;
        // color.g = 0;

        Sphere sphere { sf::Color::Green, Vector { 1920 / 2.f, 1200 / 2.f, 0 }, 400 };

        sphere_raycast( window,
                        sphere,
                        Vector { 0, 600, 1000 },
                        sf::Color::White,
                        Vector { 0, 0, 1000 },
                        color
                       );
        
        window.display();
    }

    return 0;
            
}
