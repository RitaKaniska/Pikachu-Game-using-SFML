#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextBox.h"
#include <conio.h>
#include <iostream> 
#include <string.h>

struct scn1{
	bool email = true;
	bool password = true;
};

struct account{
	std::string email;
	std::string password;
};

void input(account acc[], int &n); //input 
bool genLogin();	//check account