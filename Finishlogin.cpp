#include "Finishlogin.h"
#include "highscore.h"

std::string changeInt(int n){ //Change from integer to string
    std::string s = "";
    while (n!=0){
        int temp = n%10;
        n/=10;
        s = (char) (temp + '0') + s;
    }
    return s;
}

void GameOver(bool WIN_LOSE, int scor, float duration, bool nextLevel){ //true = win false = lose
// nextLevel = 1: there are 2 level else just level 1
//Finishing Game Screen
    int durat;
    if (nextLevel)  durat = (int) (duration);
    else durat = (int) (240-duration);
    std::fstream file("txtFile/score.txt", std::ios::in);
    int a[100], index[100], n = 0, highest = -5;
    while (!file.eof()){
        file >> index[n];
        file >> a[n];
        if (a[n] > highest) highest = a[n];
        n++;
    }
    file.close();
    std::string high = changeInt(highest);
    high += " Pts";
    std::string Durati = changeInt(durat);
    Durati += " Second";
    std::string scoreEnd = changeInt(scor);
    scoreEnd += " Pts";
    if (scor == 0)  scoreEnd = "0";
    RenderWindow window(VideoMode(400, 666), "Pikachu Game Over !!!");
    Texture t1, t2;

    t1.loadFromFile("Picture/PikaPika.jpg");

    Sprite Back(t1);

    Font arial;
	arial.loadFromFile("Font/Arial.ttf");
    Font Roman;
    Roman.loadFromFile("Font/Roman.ttf");
    Font Molot;
    Molot.loadFromFile("Font/Molot.otf");
    
    sf::Text text, score, highscore, time, win, lose, scr, timeLeft, biggest;
    biggest.setFont(Molot);
    biggest.setString(high);
    timeLeft.setFont(Molot);
    timeLeft.setString(Durati);
    scr.setFont(Molot);
    scr.setString(scoreEnd);
    text.setFont( Roman );
    text.setString("GAME OVER!!!");
    win.setFont(Roman);
    win.setString("YOU WIN!!!");
    lose.setFont(Roman);
    lose.setString("YOU LOSE!!!");
    score.setFont(Molot);
    score.setString("Score :");
    highscore.setFont(Molot);
    highscore.setString("HighScore :");
    time.setFont(Molot);
    time.setString("Time :");

    biggest.setCharacterSize(30);
    biggest.setOutlineColor(sf::Color::Black);
    biggest.setOutlineThickness(3);
    timeLeft.setCharacterSize(30);
    timeLeft.setOutlineColor(sf::Color::Black);
    timeLeft.setOutlineThickness(3);
    score.setCharacterSize(30);
    score.setOutlineColor(sf::Color::Black);
    score.setOutlineThickness(3);
    time.setCharacterSize(30);
    time.setOutlineColor(sf::Color::Black);
    time.setOutlineThickness(3);
    highscore.setCharacterSize(30);
    highscore.setOutlineColor(sf::Color::Black);
    highscore.setOutlineThickness(3);

    scr.setCharacterSize(30);
    scr.setOutlineColor(sf::Color::Black);
    scr.setOutlineThickness(3);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(7);
    win.setCharacterSize(50);
    win.setFillColor(sf::Color::Red);
    win.setOutlineColor(sf::Color::Black);
    win.setOutlineThickness(7);
    lose.setCharacterSize(50);
    lose.setFillColor(sf::Color::Red);
    lose.setOutlineColor(sf::Color::Black);
    lose.setOutlineThickness(7);

    while (window.isOpen()){
        Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)    window.close();
        }
        window.clear(sf::Color::Yellow);
        Back.setPosition(0, 0);
        window.draw(Back);
        scr.setPosition(150, 97);
        window.draw(scr);
        score.setPosition(25,97);
        window.draw(score);
        time.setPosition(25, 137);
        timeLeft.setPosition(150, 137);
        window.draw(timeLeft);
        window.draw(time);
        highscore.setPosition(25, 177);
        biggest.setPosition(220, 177);
        window.draw(biggest);
        window.draw(highscore);
        win.setPosition(10, 20);
        lose.setPosition(10, 20);
        if (WIN_LOSE == true)   window.draw(win);
        else window.draw(lose);
        window.display();
        
    }
    return;
}