#include <stdio.h>
#include "scene.h"
   
int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };

    
    Scene ray_tracer { &window, Vector { 960, 600, 500 } }; 

    Sphere object_1 { Vector { 960, 600, -500 },
                      500,
                      sf::Color::Blue,
                      25.f };
    
    Sphere object_2 { Vector { 960, 600, 0 },
                      100,
                      sf::Color::Green,
                      25.f };
    

    int i = 0;

    ray_tracer.add_obj( object_1);
    ray_tracer.add_obj( object_2);

    ray_tracer.add_light( Light { Vector { 0, 600, 1000 }, sf::Color::White });
    ray_tracer.add_light( Light { Vector { 960, 0, 1000 }, sf::Color::White });
    

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


        i += 10;

        if ( i == 1920 )
        {
            i = 0;
        }

        Light light { Vector { (float)i, 600, 1000 }, sf::Color::White }; 

        ray_tracer.set_light( 0, light);
        ray_tracer.raytrace();
        // ray_tracer.raycast(0);
 

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
