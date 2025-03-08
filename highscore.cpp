#include "highscore.h"


void highscore(){
//Getting 5 highest score of player
    std::fstream file("txtFile/score.txt", std::ios::in);
    int a[100], index[100], n = 0, highest = -5, temp;
    while (!file.eof()){
        file >> n;
        file >> a[n];
        if (a[n] > highest) highest = a[n];
    }
    n++;
    for (int i = 0; i < n; i++) index[i] = i;
    file.close();
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (a[i] < a[j]){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
    std::string highestScore[5];
    for (int i = 0; i < 5; i++)
        highestScore[i] = changeInt(a[i]);
    std::ifstream ifs("txtFile/Data.txt", std::ios::in);
    std::string name[100], tempString, tp;
    while(ifs >> n){
        ifs >> name[n];
        ifs >> tempString;
    }
    ifs.close();
    sf::RenderWindow window(sf::VideoMode(564, 1003), "Pikachu Game Over !!!");
    sf::Texture t1;
    sf::Font Molot;
    Molot.loadFromFile("Font/Molot.otf");
    sf::Text header, first, second, third, fourth, fifth, sc[5];
    for (int i = 0; i < 5; i++){
        highestScore[i] += " Points";
        sc[i].setFont(Molot);
        sc[i].setString(highestScore[i]);
        sc[i].setFillColor(sf::Color::White);
        sc[i].setCharacterSize(40);
        sc[i].setOutlineColor(sf::Color::Black);
        sc[i].setOutlineThickness(7);
    }
    header.setFont(Molot);
    header.setString("LEADERBOARD !!!");
    header.setFillColor(sf::Color::White);
    header.setCharacterSize(60);
    header.setOutlineColor(sf::Color::Black);
    header.setOutlineThickness(7);
    first.setFont(Molot);
    name[index[0]] = changeInt(1) + ". " + name[index[0]];
    name[index[1]] = changeInt(2) + ". " + name[index[1]];
    name[index[2]] = changeInt(3) + ". " + name[index[2]];
    name[index[3]] = changeInt(4) + ". " + name[index[3]];
    name[index[4]] = changeInt(5) + ". " + name[index[4]];
    first.setString(name[index[0]]);
    second.setFont(Molot);
    second.setString(name[index[1]]);
    third.setFont(Molot);
    third.setString(name[index[2]]);
    fourth.setFont(Molot);
    fourth.setString(name[index[3]]);
    fifth.setFont(Molot);
    fifth.setString(name[index[4]]);

    first.setCharacterSize(50);
    first.setFillColor(sf::Color::Black);
    first.setOutlineColor(sf::Color::White);
    first.setOutlineThickness(4);
    second.setCharacterSize(50);
    second.setFillColor(sf::Color::Black);
    second.setOutlineColor(sf::Color::White);
    second.setOutlineThickness(4);
    third.setCharacterSize(50);
    third.setFillColor(sf::Color::Black);
    third.setOutlineColor(sf::Color::White);
    third.setOutlineThickness(4);
    fourth.setCharacterSize(50);
    fourth.setFillColor(sf::Color::Black);
    fourth.setOutlineColor(sf::Color::White);
    fourth.setOutlineThickness(4);
    fifth.setCharacterSize(50);
    fifth.setFillColor(sf::Color::Black);
    fifth.setOutlineColor(sf::Color::White);
    fifth.setOutlineThickness(4);
    t1.loadFromFile("Picture/highscore.jpg");
    sf::Sprite high(t1);

    while(window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)    window.close();
        }
        window.clear(sf::Color::Black);
        high.setPosition(0, 0);
        window.draw(high);
        header.setPosition(60, 100);
        window.draw(header);
        first.setPosition(40, 280);
        window.draw(first);
        second.setPosition(40, 400);
        window.draw(second);
        third.setPosition(40, 520);
        window.draw(third);
        fourth.setPosition(40, 640);
        window.draw(fourth);
        fifth.setPosition(40, 760);
        window.draw(fifth);
        int firstPos = 340;
        for (int i = 0; i < 5; i++){
            sc[i].setPosition(100, firstPos);
            window.draw(sc[i]);
            firstPos += 120;
        }
        window.display();
    }
    return; 
}