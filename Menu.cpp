#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>	
#include "Button.h"
#include <string.h>
#include <vector>
#include <math.h>
#include <time.h>
#include "Random.h"
#include "Finishlogin.h"
#include "highscore.h"
#include "Linkedlist.h"
#include "TextBox.h"

using namespace sf;

void Genlevel2(sf::RenderWindow& app, int &score, float &duration)
{
    float duratTemp = duration + 180.0f;
    app.close();
    int count = 100;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Linked List !!!");
    sf::Font font;

    font.loadFromFile("Font/IMMORTAL.ttf");
    Button tp[10][10];
    char **a = getRandom(10, 10);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            string temp = "";
            temp += a[i][j];
            tp[i][j].text.setString(temp);
            tp[i][j].text.setCharacterSize(30);
            tp[i][j].text.setFillColor(sf::Color::Black);
            tp[i][j].button.setFillColor(sf::Color::Green);
            tp[i][j].button.setSize({ 50,50 });
            tp[i][j].setFont(font);
            float u = i * 60;
            float v = j * 60;
            tp[i][j].setPosition({ u + 500,v + 200 });
        }
    }
    tp[0][0].setBackgroundColor(sf::Color::White);
    int x = 0;  
    int y = 0;
    std::vector<std::pair<int, int>> couple;
    bool check_[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) check_[i][j] = false;
    }
    list L[10];
    for (int i = 0; i < 10; i++)    L[i].head = L[i].tail = NULL;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)    addTail(L[i], tp[i][j]);
    
    sf::SoundBuffer buffer;
    buffer.loadFromFile("Sound/ClickButton.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);

    //Timer
    sf::Font timerFont;
    sf::Text timerText;
    timerFont.loadFromFile("Font/IMMORTAL.ttf");
    timerText.setFont(timerFont);
    timerText.setString("00:000");
    timerText.setCharacterSize(100);
    timerText.setFillColor(sf::Color::White);

    //Score

    sf::Text scoreText;
    scoreText.setFont(timerFont);
    string tempString = changeInt(score);
    scoreText.setString(tempString + " Pts");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(1200, 140);

    // Text Position //
    sf::FloatRect timerTextRect = timerText.getLocalBounds();
    timerText.setOrigin(timerTextRect.left + timerTextRect.width / 2.0f, timerTextRect.top + timerTextRect.height / 2.0f);
    timerText.setPosition(1600 / 2.0f + 600, 100);

    // Timer Variables //
    sf::Clock clock;
    duration += 180.0f;
    float fMilliseconds, fSeconds;
    int intMilliseconds, intSeconds;
    sf::String stringMilliseconds;
    sf::String stringSeconds;
    sf::String timerString;
    //End of timer variables //

    sf::Text TimerString;
    TimerString.setFont(font);
    TimerString.setString("Timer");
    TimerString.setCharacterSize(100);
    TimerString.setFillColor(sf::Color::White);

    TimerString.setPosition(900, 30);

    while (window.isOpen())
    {
        
        sf::Event event;
        
        // Update clock
        sf::Time time = clock.restart();
        int n, temp;
        std::ifstream ifs("txtFile/score.txt", ios::in);
        
        while(!ifs.eof()) ifs >> n >> temp;
        ifs.close();

        if (duration > 0){
            if (count == 0){
                std::ofstream fout("txtFile/score.txt", ios::in | ios::out | ios::app);
                fout << ++n << '\n';
                fout << score << '\n';
                fout.close();
                GameOver(true, score, duratTemp-duration, 1);
                window.close();
            }
        }
        else{
            std::ofstream fout("txtFile/score.txt", ios::in | ios::out | ios::app);
                fout << ++n << '\n';
                fout << score << '\n';
            fout.close();
            GameOver(false, score, duratTemp, 1);
            window.close();
        }

        if (duration > 0) {
            // Calculate countdown
            duration -= time.asSeconds();
            fMilliseconds = std::modf(duration, &fSeconds);
            // Change float to int
            intSeconds = static_cast<int>(fSeconds);
            intMilliseconds = static_cast<int>(fMilliseconds * 1000);
            // Change int to string 
            stringMilliseconds = std::to_string(intMilliseconds);
            stringSeconds = std::to_string(intSeconds);

            if (intMilliseconds <= 0) {
                stringMilliseconds = "000";
            }

            if (intSeconds <= 0) {
                stringSeconds = "00";
            }
            else if (intSeconds < 10) {
                stringSeconds = "0" + stringSeconds;
            }

            timerString = stringSeconds + ":" + stringMilliseconds;
            timerText.setString(timerString);
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                sound.play();
                    if (event.key.code == sf::Keyboard::Up){
                        if (y >= 0){
                            node* p = L[x].head;
                            int tempY = 0;
                            while (L[x].head == NULL){
                                x++;
                                if (x >= 10)    x = 0;
                                p = L[x].head;
                            } 
                            for (int i = 0; i < y && p->next != NULL; i++){
                                p = p->next;
                                tempY++;
                            }
                            y = tempY;
                            if (p->key.button.getFillColor() != sf::Color::Red && p->key.button.getFillColor() != sf::Color::Transparent)   p->key.setBackgroundColor(sf::Color::Green);
                            y--;
                            while (check_[x][y] == true)    y--;
                            while (y == -1){
                                x++;
                                y = 9;
                                if (x == 10)    x = 0;
                                while(check_[x][y] == true) y--;
                            }                
                            p = L[x].head;            
                            for (int i = 0; i < y; i++) p = p->next;
                            p->key.setBackgroundColor(sf::Color::White);
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Down){
                            if (y <= 9){
                                node* p = L[x].head;
                                while (p == NULL && L[x].head == NULL){
                                    x++;
                                    if (x == 10) x = 0;
                                    p = L[x].head;
                                }

                                int tempY = 0;
                                for (int i = 0; i < y && p != NULL && p->next != NULL; i++){
                                    p = p->next;
                                    tempY++;
                                }
                                y = tempY;


                                if (p != NULL && p->key.button.getFillColor() != sf::Color::Red && p->key.button.getFillColor() != sf::Color::Transparent) {
                                    p->key.setBackgroundColor(sf::Color::Green);
                                }

                                y++;

                                while (check_[x][y] && y <= 10) y++;
                                
                                while (y >= 10){
                                    x++;
                                    if (x == 10) x = 0;
                                    y = 0;
                                    while (check_[x][y] == true && y < 10) y++;
                                }

                                
                                node* q = L[x].head;
                                for (int i = 0; i < y && q != NULL && q->next != NULL; i++) {
                                    q = q->next;
                                }
                                
                                if (q != NULL) {
                                    q->key.setBackgroundColor(sf::Color::White);
                                } else {
                                    if (q->prev != NULL) {
                                        q = q->prev;
                                        y--;
                                        q->key.setBackgroundColor(sf::Color::White);
                                    }
                                }
                            }
                        }
                            else if (event.key.code == sf::Keyboard::Left){
                      
                                    if (x >= 0){
                                        node* p = L[x].head;
                                        int tempY = 0;
                                        for (int i = 0; i < y && p->next != NULL; i++){
                                            p = p->next;
                                            tempY++;
                                        }
                                        y = tempY;
                                        if (p->key.button.getFillColor() != sf::Color::Red && p->key.button.getFillColor() != sf::Color::Transparent)   p->key.setBackgroundColor(sf::Color::Green);
                                        x--;
                                        while (check_[x][y] == true)    x--;
                                        while (x == -1){
                                            y++;
                                            x = 0;
                                            if (y == 10)    y = 0;
                                            while (check_[x][y] == true)    x--;
                                        }
                                        p = L[x].head;
                                        tempY = 0;
                                        for (int i = 0; i < y && p->next != NULL; i++){
                                             p = p->next;
                                             tempY++;
                                        }
                                        y = tempY;
                                        p->key.setBackgroundColor(sf::Color::White);
                                    }            
                                }
                                else if (event.key.code == sf::Keyboard::Right){
                                    
                                        if (x <= 9){
                                            node* p = L[x].head;
                                            int tempY = 0;
                                            for (int i = 0; i < y && p->next != NULL; i++){
                                                p = p->next;
                                                tempY++;
                                            } 
                                            y = tempY;
                                            if (p->key.button.getFillColor() != sf::Color::Red && p->key.button.getFillColor() != sf::Color::Transparent)   p->key.setBackgroundColor(sf::Color::Green);
                                            x++;
                                            while (x == 10){
                                                y++;
                                                x = 0;
                                                if (y == 10)    y = 0;
                                                while (check_[x][y] == true)    x++;
                                            }                        
                                            p = L[x].head;
                                            tempY = 0;
                                            for (int i = 0; i < y && p->next != NULL; i++) {
                                                p = p->next;
                                                tempY++;
                                            }
                                            y = tempY;
                                            p->key.setBackgroundColor(sf::Color::White); 
                                        }                                   
                                    }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    node* p = L[x].head;
                    for (int i = 0; i < y; i++) p = p->next;
                    p->key.setBackgroundColor(sf::Color::Red);
                    couple.push_back(std::make_pair(x, y));
                    if (couple.size() >= 2)
                    {
                        int x0 = couple[0].first;
                        int y0 = couple[0].second;
                        int x1 = couple[1].first;
                        int y1 = couple[1].second;

                        if (y0 < y1){
                            std::swap(x0, x1);
                            std::swap(y0, y1);
                        }
                        if (x1 == x0 && y1 == y0)
                        {
                            node* p = L[x1].head;
                            for (int i = 0; i < y1; i++)    p = p->next;
                            p->key.setBackgroundColor(sf::Color::White);
                            couple.clear();
                        }
                        else {
                            node *q = L[x0].head;
                            node *p = L[x1].head;
                            for (int i = 0; i < y0; i++)    q = q->next;
                            for (int i = 0; i < y1; i++)    p = p->next;
                            if (check_couple(q->key, p->key) == true && checkAll(check_, x0, y0, x1, y1, 10, 10))
                            {
                                if (countElements(L[x0]) != 1)  removePos(L[x0], y0);
                                else{
                                    q->key.setBackgroundColor(sf::Color::Transparent);
                                    check_[x0][0] = true;
                                }
                                if (countElements(L[x1]) != 1)  removePos(L[x1], y1);
                                else{
                                    p->key.setBackgroundColor(sf::Color::Transparent);
                                    check_[x1][0] = true;
                                }
                                if (x0 != x1){
                                    check_[x0][countElements(L[x0])] = true;
                                    check_[x1][countElements(L[x1])] = true;
                                }
                                else{
                                    int N = countElements(L[x0]);
                                    check_[x0][N] = true;
                                    check_[x0][N+1] = true;
                                }
                                p = p->next;
                                q = q->next;
                                int i = 0;
                                for (; q != NULL; q = q->next){
                                    float u = (x0)*60;
                                    float v = (y0+i)*60;
                                    q->key.setPosition({u + 500, v + 200});
                                    i++;
                                }
                                i = 0;
                                for (; p != NULL; p = p->next){
                                    float u = (x1)*60;
                                    float v = (y1+i)*60;
                                    p->key.setPosition({u + 500, v + 200});
                                    i++;
                                }
                                count -= 2;
                                score += (duration/18)*10;
                                string tempString = changeInt(score);
                                scoreText.setString(tempString + " Pts");
                                couple.clear();

                            }
                            else{
                                q->key.setBackgroundColor(sf::Color::Green);
                                p->key.setBackgroundColor(sf::Color::White);
                                couple.clear();
                            }
                        }

                    }

                 }
            }
        }

        window.clear();
        
        for (int i = 0; i < 10; i++) {
            if (countElements(L[i]) >= 1 && check_[i][0] == false)
                for (node* p = L[i].head; p != NULL; p = p->next)
                    p->key.drawto(window);
        }
        window.draw(scoreText);
        window.draw(TimerString);
        window.draw(timerText);
        window.display();
    }
}

string genNext(){
    sf::RenderWindow window(sf::VideoMode(600, 337), "Next or Finish : D");
    sf::Texture p1;
    sf::Font font;
    font.loadFromFile("Font/Arial.ttf");

    p1.loadFromFile("Picture/Next.jpg");

    sf::Sprite YN(p1);
    
    sf::Text t1;
    t1.setString("Do you want to play next level [Y/N]: ");
    t1.setFont(font);
    t1.setCharacterSize(30);
    t1.setOutlineColor(sf::Color::Black);
    t1.setOutlineThickness(4);
    t1.setPosition({50, 100});

    Textbox t(40, sf::Color::White, true);
    t.setFont(font);
    t.setPosition(sf::Vector2f(200, 150));  // Set the position of the TextBox
    string temp;
    while(window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (e.type == sf::Event::TextEntered){
                t.typedOn(e);
                t.setSelected(false);  // Set the TextBox to selected
            }
        }
        temp = t.getText();
        if (temp != "") window.close();
        window.clear();
        YN.setPosition({0, 0});
        window.draw(YN);
        window.draw(t1);
        t.drawTo(window);  // Draw the TextBox
        window.display();  // Update the window
    }
    return temp;
}

void GenInGameScreen(sf::RenderWindow& app)
{
    app.close();

    int count = 100;
    int score = 0;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Pikachu Game !!!");
    sf::Font font;

    font.loadFromFile("Font/IMMORTAL.ttf");
    Button k[10][10];
    char **a = getRandom(10, 10);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            string temp = "";
            temp += a[i][j];
            k[i][j].text.setString(temp);
            k[i][j].text.setCharacterSize(30);
            k[i][j].text.setFillColor(sf::Color::Black);
            k[i][j].button.setFillColor(sf::Color::Green);
            k[i][j].button.setSize({ 50,50 });
            k[i][j].setFont(font);
            float u = i * 60;
            float v = j * 60;
            k[i][j].setPosition({ u + 500,v + 200 });
        }
    }

    k[0][0].setBackgroundColor(sf::Color::White);
    int x = 0;
    int y = 0;

    std::vector<std::pair<int, int>> couple;
    bool check_[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) check_[i][j] = false;
    }

    sf::Texture t1;
    t1.loadFromFile("Picture/example.jpg");
    Sprite Background(t1);
    Background.setPosition(0, 0);

    sf::SoundBuffer buffer;
    buffer.loadFromFile("Sound/ClickButton.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);



    //Timer
    sf::Font timerFont;
    sf::Text timerText;
    timerFont.loadFromFile("Font/IMMORTAL.ttf");
    timerText.setFont(timerFont);
    timerText.setString("00:000");
    timerText.setCharacterSize(100);
    timerText.setFillColor(sf::Color::White);

    // Text Position //
    sf::FloatRect timerTextRect = timerText.getLocalBounds();
    timerText.setOrigin(timerTextRect.left + timerTextRect.width / 2.0f, timerTextRect.top + timerTextRect.height / 2.0f);
    timerText.setPosition(1600 / 2.0f + 600, 100);

    // Timer Variables //
    sf::Clock clock;
    float duration = 240.0f;
    float fMilliseconds, fSeconds;
    int intMilliseconds, intSeconds;
    sf::String stringMilliseconds;
    sf::String stringSeconds;
    sf::String timerString;
    //End of timer variables //

    //Score

    sf::Text scoreText;
    scoreText.setFont(timerFont);
    scoreText.setString("0 Pts");
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(1200, 140);

    sf::Text TimerString;
    TimerString.setFont(font);
    TimerString.setString("Timer");
    TimerString.setCharacterSize(100);
    TimerString.setFillColor(sf::Color::White);

    TimerString.setPosition(900, 30);

    while (window.isOpen())
    {
        
        sf::Event event;
        
        // Update clock
        sf::Time time = clock.restart();
        int n, temp;
        std::ifstream ifs("txtFile/score.txt", ios::in);
        
        while(!ifs.eof()) ifs >> n >> temp;
        ifs.close();

        if (duration > 0){
            if (count == 0){
                string choice = genNext();
                if (choice == "Y" || choice == "y") {
                    Genlevel2(app, score, duration);
                    window.close();
                }
                else{
                    std::ofstream fout("txtFile/score.txt", ios::in | ios::out | ios::app);
                    fout << ++n << '\n';
                    fout << score << '\n';
                    fout.close();
                    GameOver(true, score, duration, 0);
                    window.close();
                }
                window.close();
            }
        }
        else{
            std::ofstream fout("txtFile/score.txt", ios::in | ios::out | ios::app);
                fout << ++n << '\n';
                fout << score << '\n';
            fout.close();
            GameOver(false, score, 0, 0);
            window.close();
        }

        if (duration > 0) {
            // Calculate countdown
            duration -= time.asSeconds();
            fMilliseconds = std::modf(duration, &fSeconds);
            // Change float to int
            intSeconds = static_cast<int>(fSeconds);
            intMilliseconds = static_cast<int>(fMilliseconds * 1000);
            // Change int to string 
            stringMilliseconds = std::to_string(intMilliseconds);
            stringSeconds = std::to_string(intSeconds);

            if (intMilliseconds <= 0) {
                stringMilliseconds = "000";
            }

            if (intSeconds <= 0) {
                stringSeconds = "00";
            }
            else if (intSeconds < 10) {
                stringSeconds = "0" + stringSeconds;
            }

            timerString = stringSeconds + ":" + stringMilliseconds;
            timerText.setString(timerString);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed) {
                sound.play();
                 if (event.key.code == sf::Keyboard::Up)
                {
                    if (y >= 0)
                    {
                        if (k[x][y].button.getFillColor() != sf::Color::Red && k[x][y].button.getFillColor() != sf::Color::Transparent) k[x][y].setBackgroundColor(sf::Color::Green);
                        y--;
                        while (check_[x][y] == true && y >= -1)    y--;
                        while (y <= -1){
                            x++;
                            y = 9;
                            if (x == 10)    x = 0;
                            while(check_[x][y] == true) y--;
                        }
                        k[x][y].setBackgroundColor(sf::Color::White);
                    }
                    //break;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (y <= 9)
                    {
                        if (k[x][y].button.getFillColor() != sf::Color::Red && k[x][y].button.getFillColor() != sf::Color::Transparent) k[x][y].setBackgroundColor(sf::Color::Green);
                        y++;
                        while (check_[x][y] == true && y <= 10)    {
                            y++;
                        }
                        while (y >= 10){
                            x++;
                            if (x == 10)    x = 0;
                            y = 0;
                            while(check_[x][y] == true) y++;
                        }
                        k[x][y].setBackgroundColor(sf::Color::White);
                    }
                    //break;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (x >= 0)
                    {
                        if (k[x][y].button.getFillColor() != sf::Color::Red && k[x][y].button.getFillColor() != sf::Color::Transparent) k[x][y].setBackgroundColor(sf::Color::Green);
                        x--;
                        while (check_[x][y] == true)    x--;
                        while (x == -1){
                            y++;
                            x = 9;
                            if (y == 10)    y = 0;
                            while (check_[x][y] == true)    x--;
                        }
                        k[x][y].setBackgroundColor(sf::Color::White);
                    }
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (x <= 9)
                    {
                        if (k[x][y].button.getFillColor() != sf::Color::Red && k[x][y].button.getFillColor() != sf::Color::Transparent) k[x][y].setBackgroundColor(sf::Color::Green);
                        x++;
                        while (check_[x][y] == true)    x++;
                        while (x == 10){
                            y++;
                            x = 0;
                            if (y == 10)    y = 0;
                            while (check_[x][y] == true)    x++;
                        }
                        k[x][y].setBackgroundColor(sf::Color::White);
                    }
                    //break;
                }                
                else if (event.key.code == sf::Keyboard::Space)
                {
                    k[x][y].setBackgroundColor(sf::Color::Red);
                    couple.push_back(std::make_pair(x, y));
                    if (couple.size() >= 2)
                    {
                        int x0 = couple[0].first;
                        int y0 = couple[0].second;
                        int x1 = couple[1].first;
                        int y1 = couple[1].second;
                        if (x1 == x0 && y1 == y0)
                        {
                            k[x1][y1].setBackgroundColor(sf::Color::White);
                            couple.clear();
                        }
                        else if (check_couple(k[x0][y0], k[x1][y1]) == true && checkAll(check_, x0, y0, x1, y1, 10, 10))
                        {
                            
                            k[x0][y0].setBackgroundColor(sf::Color::Transparent);
                            k[x1][y1].setBackgroundColor(sf::Color::Transparent);

                            check_[x0][y0] = true;
                            check_[x1][y1] = true;
                            count -= 2;
                            score += (duration/15)*10;
                            string tempString = changeInt(score);
                            scoreText.setString(tempString + " Pts");
                            couple.clear();
                        }
                        else
                        {
                            k[x0][y0].setBackgroundColor(sf::Color::Green);
                            k[x1][y1].setBackgroundColor(sf::Color::White);

                            couple.clear();
                        }
                    }

                }
            }
        }

        window.clear();
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j)
            {
                k[i][j].drawto(window);
            }
        }
        window.draw(scoreText);
        window.draw(TimerString);
        window.draw(timerText);
        window.display();
    }
}

void GenMainMenu()
{
			sf::RenderWindow app(sf::VideoMode(1600, 900), "Pikachu Game");

			sf::Mouse::setPosition(sf::Vector2i(700, 200), app);

			sf::Texture t;
			t.loadFromFile("Picture/pikachu.jpg");
			sf::Sprite s(t);

			sf::Font font;
			font.loadFromFile("Font/IMMORTAL.ttf");

			sf::Text text;
			text.setFont(font);
			text.setString("The Matching Game");
			text.setCharacterSize(60);
			text.setFillColor(sf::Color::Magenta);
			text.setPosition(500, 0);

			sf::SoundBuffer buffer;
			buffer.loadFromFile("Sound/ClickButton.wav");
			sf::Sound sound;
			sound.setBuffer(buffer);

			sf::Music music;
			music.openFromFile("Sound/INTRO.mp3");

			Button Play{ "PLAY",{200,100},35,sf::Color::White,sf::Color::Black };
			Play.setPosition({ 700 , 200 });
			Play.setFont(font);

			Button Option{ "HIGH",{250,100},35,sf::Color::Green,sf::Color::Black };
			Option.setPosition({ 675 , 350 });
			Option.setFont(font);

			Button Exit{ "EXIT",{200,100},35,sf::Color::Green,sf::Color::Black };
			Exit.setPosition({ 700 , 500 });
			Exit.setFont(font);
            
            int n = 0;
            
            std::ifstream ifs("txtFile/Data.txt", std::ios::in);
            ifs.seekg(0, ios::beg);
            string temp;
            while (ifs >> temp) n++;
            ifs.close();
            n /= 3;
            n--;
			while (app.isOpen()) {
				sf::Event event;
				while (app.pollEvent(event)) {

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						sound.play();
						if (Play.button.getFillColor() == sf::Color::White) {
							music.stop();
							GenInGameScreen(app);
						}
						if (Option.button.getFillColor() == sf::Color::White) {
                            highscore();
						}
						if (Exit.button.getFillColor() == sf::Color::White) {
                            std::ofstream ofs("txtFile/score.txt", std::ios::out | std::ios::app);
                            ofs << n << '\n' << 0 << '\n';
                            ofs.close();
							app.close();
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						sound.play();
						if (Play.button.getFillColor() == sf::Color::White) {
							Play.setBackgroundColor(sf::Color::Green);
							Option.setBackgroundColor(sf::Color::White);
							//break;
						}
						if (Option.button.getFillColor() == sf::Color::White) {
							Option.setBackgroundColor(sf::Color::Green);
							Exit.setBackgroundColor(sf::Color::White);
							//break;
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						sound.play();
						if (Option.button.getFillColor() == sf::Color::White) {
							Option.setBackgroundColor(sf::Color::Green);
							Play.setBackgroundColor(sf::Color::White);
							sf::sleep(sf::seconds(1));
							break;
						}
						if (Exit.button.getFillColor() == sf::Color::White) {
							Exit.setBackgroundColor(sf::Color::Green);
							Option.setBackgroundColor(sf::Color::White);
							sf::sleep(sf::seconds(1));
							break;
						}
					}

					app.clear();
					app.draw(s);
					app.draw(text);
					Play.drawto(app);
					Option.drawto(app);
					Exit.drawto(app);
					music.play();
					app.display();
				}
			}
			return;
}
