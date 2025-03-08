#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include <string.h>

class Button { //Data of all button includes button Play, Highest score, exit, and objects in the game.
public:
	sf::RectangleShape button;
	sf::Text text;

	Button(){  }

	Button(std::string t, sf::Vector2f size,int charSize, sf::Color backgroundColor, sf::Color textColor) {
		text.setString(t);	
		text.setFillColor(textColor); //Color of text of the object
		text.setCharacterSize(charSize);	//Size of the text

		button.setSize(size);	//Size of the button
		button.setFillColor(backgroundColor); //Color of the button
	}

	void setFont(sf::Font &font) {
		text.setFont(font);	//Font of the button
	}

	void setBackgroundColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f pos) {
		button.setPosition(pos);

		// The position of the button when draw to window
		float xPos = (pos.x + button.getLocalBounds().width / 3 - (text.getLocalBounds().width / 2));
		float yPos = (pos.y + button.getLocalBounds().height / 3 - (text.getLocalBounds().height / 2));
		text.setPosition({xPos,yPos});		
	}

	void drawto(sf::RenderWindow &window) { //Draw the button to window with the text of it 
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnposX = button.getPosition().x;
		float btnposY = button.getPosition().y;

		float btnposwidth = button.getPosition().x + button.getLocalBounds().width;
		float btnposheight = button.getPosition().y + button.getLocalBounds().height;
		if (mouseX >= btnposX && mouseX <= btnposwidth && mouseY >= btnposY && mouseY <= btnposheight) {
			return true;
		}
		return false;
	}


};

void GenMainMenu();	//Go to main menu screen
void GenInGameScreen(sf::RenderWindow& app);	//Start the game
bool check_couple(Button A, Button B);	//check Same of the button
//Check UILZ Moving
bool CheckIMatching(bool IsExist[][10], int x0, int y0, int x1, int y1);	
bool CheckZMatching(bool Isexist[][10], int x0, int y0, int x1, int y1);
bool checkLMatching(bool IsExist[][10], int x0, int y0, int x1, int y1);
bool checkUMatching(bool IsExist[][10], int x0, int y0, int x1, int y1, int ROWS, int COLS);
bool checkAll(bool IsExist[][10], int x0, int y0, int x1, int y1, int Rows, int Cols);

std::string genNext();//check [Do you want to play the next level]