#include <stdio.h>
#include "raytracer.h"
   
int main()
{
    sf::RenderWindow window { sf::VideoMode { 1920, 1200 }, "Cringe" };
    Raytracer ray_tracer { 1920, 1080, Vector{ 960, 600, 500 } };

    sf::Color color { 255, 250, 250, 0 };

    Sphere object_1 { Vector { 460, 600, -900 },
                      550,
                      color,
                      35.f,
                      0.8f };
    
    Sphere object_2 { Vector { 160, 400, -200 },
                      150,
                      sf::Color::Green,
                      25.f,
                      0.5f };

    Sphere object_3 { Vector { 1460, 600, -200 },
                      300,
                      sf::Color::Yellow,
                      25.f };

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

        ray_tracer.render();
        window.draw( ray_tracer.get_point_map());
       
        window.display();
    }

    return 0;
            
}
