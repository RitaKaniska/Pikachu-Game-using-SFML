#include "Button.h"
#include <iostream>
//#include "Character.h"
#include <math.h>
#include<SFML/Audio.hpp>
#include "genLogin.h"
#include "Textbox.h"
#include "Finishlogin.h"


int main(int argc, const char* argv[])
{
	/*sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");

	sf::SoundBuffer buffer;
	buffer.loadFromFile("ClickButton.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				sound.play();
			}
		}
		window.clear();
		window.display();
	}*/
 	bool checkLogin = genLogin();
	if (checkLogin)	GenMainMenu();
}