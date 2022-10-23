#include <stdio.h>
#include "raytracer.h"
   
int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };
    Raytracer ray_tracer { 1920, 1080, Vector{ 960, 600, 500 } };

    sf::Color color { 120, 50, 50, 0 };

    Sphere object_1 { Vector { 460, 600, -900 },
                      550,
                      sf::Color::Blue,
                      35.f,
                      0.5f
    };
    
    Sphere object_2 { Vector { 160, 400, -200 },
                      150,
                      sf::Color::Green,
                      25.f,
                      0.5f
    };

    Sphere object_3 { Vector { 1460, 600, -200 },
                      300,
                      sf::Color::Yellow,
                      25.f };

    int i = 0;

    ray_tracer.add_object( object_1);
    ray_tracer.add_object( object_2);
    ray_tracer.add_object( object_3);

    ray_tracer.add_light( Light { Vector { 560, 300, 400 }, sf::Color::White });
    

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

        ray_tracer.render();
        window.draw( ray_tracer.get_point_map());
       
        window.display();
    }

    return 0;
            
}
