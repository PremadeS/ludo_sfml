#include <SFML/Graphics.hpp>
#include"Dice.h"
#include"GUI.h"
#include<iostream>

int main()
{
	int x=0,y=0,z=0;
	bool i = true;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Ludo");
	Game game(window);
	GUI gui(window);
	gui.welcome();
	gui.teamSelect(x);
	if (x == 0)
		gui.playerSelect(y);
	else
		y = 6;
	gui.pieceSelect(z);
	
	while (window.isOpen())
	{
		
		if (i)
		{
			gui.start(x,y,z);
		}
		i = false;
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		
		

	}
	return 0;
}