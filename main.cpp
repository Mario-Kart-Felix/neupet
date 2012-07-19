#include "World.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

int main()
{
	

	
	srand(time(NULL));
	
	World world;
	

	
	
	
	// Create main window
    sf::RenderWindow App(sf::VideoMode(640, 480), "neupet");
	App.Clear();
	
    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }
		
		// Run the simulation.
		world.step();

		// Show the world.
		world.render(App);
		App.Display();
	}
	
    return EXIT_SUCCESS;
}