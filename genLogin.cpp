#include "genLogin.h"

void input(account acc[], int &n){
//input the account to the file to save data
	std::ifstream fin("txtFile/Data.txt", std::ios::in | std::ios::out);
	int temp;
	while (fin >> temp){
		fin >> acc[n].email;
		fin >> acc[n++].password;
	}
	fin.close();
}

bool genLogin(){ // check gen Login
//if true continue to Main Menu 
//if false continue to Wrong Password screen
//Press ESC_KEY to get out the Wrong Password screen
	int scene = 1, n = 0;
	scn1 scene1;
	account acc[100];
	bool first = true;
	int check;
	bool checkLogin = false;
	
	sf::RenderWindow window(sf::VideoMode(600, 600), "Pikachu login");
	sf::Texture t1, t2, t3, t4, t5;

	t1.loadFromFile("Picture/Email.png");
	t2.loadFromFile("Picture/Password.png");
	t3.loadFromFile("Picture/Submit.png");
	t4.loadFromFile("Picture/LoginOk.png");
	t5.loadFromFile("Picture/Simpsons.jpg");

	sf::Sprite Email(t1);
	sf::Sprite Password(t2);
	sf::Sprite Submit(t3);
	sf::Sprite LoginOK(t4);
	sf::Sprite Wrong(t5);
	sf::Font arial;
	arial.loadFromFile("Font/Arial.ttf");

	Textbox textLoginEmail(30, sf::Color::White, true);
	textLoginEmail.setFont(arial);
	Textbox textLoginPassword(30, sf::Color::White, true);
	textLoginPassword.setFont(arial);

	input(acc, n);

	std::ofstream fout("txtFile/Data.txt", std::ios::in | std::ios::out);
	std::string Emaill, Passwordd;
	while (window.isOpen())
	{
		sf::Event e;
		if (first == true){
			for (int i = 0; i < n; i++){
				fout << i << "\n";
				fout << acc[i].email << "\n";
				fout << acc[i].password << "\n";
			}
			first = false;
		}
		while (window.pollEvent(e)){
			if (e.type == sf::Event::Closed)	window.close();
			if (e.type == sf::Event::TextEntered){
				if (scene == 1){
					if (scene1.email == true){
						if (e.key.code == ENTER_KEY){
							textLoginEmail.setSelected(false);
							scene1.email = false;
						}
						else{
							textLoginEmail.typedOn(e);
						}
					}
					else if (scene1.password == true){
							if (e.key.code == ENTER_KEY){
								textLoginPassword.setSelected(false);
								scene1.password = false;
							}
							else {
								textLoginPassword.typedOn(e);
							}
						}
				}
			}
		}
		Emaill = textLoginEmail.getText();
		Passwordd = textLoginPassword.getText();
		if (scene1.password == false){
			check = 3; //not same email;
			scene = 2;
			for (int i = 0; i < n; i++)
			if (acc[i].email == Emaill){
				if (acc[i].password == Passwordd){
					check = 2; //Same email + pass
					scene = 2; 
					break;
				}
				else{
					check = 1; //Same email not same pass
					scene = 3;
					break;
				}
			}
			
		}
		window.clear(sf::Color(104, 167, 92));
		if (scene == 1){
			Submit.setPosition(143, 405);
			window.draw(Submit);
			Password.setPosition(50, 235);
			window.draw(Password);
			Email.setPosition(50, 75);
			window.draw(Email);
			textLoginEmail.setPosition({ 210,76 });
			textLoginEmail.drawTo(window);
			textLoginPassword.setPosition({ 269,237 });
			textLoginPassword.drawTo(window);
		}
		if (check == 3){
			fout << n << '\n';
	 		fout << Emaill << '\n';
	 		fout << Passwordd << '\n';
			return true;
	 	}
		if (scene == 2){
			checkLogin = true;
			fout << n << '\n';
	 		fout << Emaill << '\n';
	 		fout << Passwordd << '\n';
			return checkLogin;
		}
		if (scene == 3){
			if (e.key.code == ESCAPE_KEY)	window.close();
			Wrong.setPosition(-70, -500);
			window.draw(Wrong);
		}
		window.display();
	}
	fout.close();
	return checkLogin;
}