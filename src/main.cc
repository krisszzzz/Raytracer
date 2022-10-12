#include <stdio.h>
#include "raycaster.h"
#include "raytracer.h"
   
int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };

    int i = 0;

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

        window.clear(sf::Color::Cyan);


        sf::Color color { 0, 0, 50 };
        Sphere objects[2] {};

        objects[1].centre_pos_ = Vector { 960, 600, -600 };
        objects[1].color_ = sf::Color::Blue;
        objects[1].spec_coeff_ = 25.f;
        objects[1].radius_ = 500;

        objects[0].centre_pos_ = Vector { 960, 600, 0 };
        objects[0].color_ = sf::Color::Green;
        objects[0].spec_coeff_ = 25.f;
        objects[0].radius_ = 100;
        

        i += 10;

        if ( i == 1920 )
        {
            i = 0;
        }

        Vector light_pos = { (float)i, 600, 1000 }; 

        raytracer( window, 1920, 1200, objects, 2, Vector { 960, 600, 1500 }, light_pos);

        // sf::Color color = { 20, 20, 20 };

        // Sphere sphere { Vector { 1920 / 2.f, 1200 / 2.f, 0 }, 400, sf::Color::Green, 25 };

        // sphere_raycast( window,
        //                 sphere,
        //                 Vector { 0, 600, 1500 },
        //                 sf::Color::White,
        //                 Vector { 0, 0, 10000 },
        //                 color
        //                );
        
        window.display();
    }

    return 0;
            
}
