#include "Random.h"

char **getRandom(int ROWS, int COLS){
    char **board;
    srand(time(0));
    board = new char *[ROWS];
    for (int i = 0; i < ROWS; i++)  board[i] = new char [COLS];
    int dem = ROWS*COLS/2;
    int count[26], n = 0, o = 5, temp = 0;
    for (int i = 0; i < 25; i++){
        count[i] = rand()%(dem+1)/2;
        if (count[i] >= o) {
            temp++;
            count[i] = o;
        }
        if (temp%5==0) {
            o--;
        } 
        dem -= count[i];
        if (count[i] < 0)   n+=count[i];
    }
    count[25] = dem + n;
    for (int i = 0; i < 26; i++)    count[i] *= 2;
    vector <char> characters;
    for (int i = 0; i < 26; i++)
        if (count[i] > 0)
            while (count[i]--)  characters.push_back('A'+i);
    random_shuffle(characters.begin(), characters.end());
    int k = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++){
            board[i][j] = characters[k];
            k = (k+1)%characters.size();
        }
    return board;
}