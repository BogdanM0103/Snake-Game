#include <iostream>
#include <cstdint>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

//score of the game
int score;

//size of the playing area
const int _SIZE = 15;

//position of the snake's head
int headX, headY;

//state of the game
bool gameOver;

//fruit position
int fruitX;
int fruitY;

//direction
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//tail of snake
int tailX[100], tailY[100];
int nTail;

void End() {
    cout << "You Lost!";
    exit(1);
}

void Generate_fruit() {
    srand(time(NULL));
    fruitX = rand() % _SIZE;
    fruitY = rand() % _SIZE;
    while(fruitX < 1 || fruitX > _SIZE - 1 || fruitY < 1 || fruitY > _SIZE - 1 || (fruitX == _SIZE / 2 && fruitY == _SIZE / 2)) {
        fruitX = rand() % _SIZE;
        fruitY = rand() % _SIZE;
    }
}

void Setup() {
    //initialize game state
    gameOver = false;

    //put snake's head in the middle
    headX = _SIZE / 2;
    headY = _SIZE / 2;

    //put the fruit somewhere random
    Generate_fruit();
}

void Input() {
    if(_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    //The logic behind the tail moving alongside the head
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    if(headX == 0 || headX == _SIZE - 1 || headY == 0 || headY == _SIZE - 1) {
        gameOver = true;
        End();
    }
    switch(dir) {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }

    //If the snake bites his own tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            gameOver = true;
        }
    }

    //Snake eats fruit
    if(headX == fruitX && headY == fruitY) {
        score += 1;
        Generate_fruit();
        nTail++;
    }
}

void Draw() {
    //refresh the window
    system("cls");

    for(int row = 0; row < _SIZE; row++) {
        for(int column = 0; column < _SIZE; column++) {
            if(row == 0 || row == _SIZE - 1 || column == 0 || column == _SIZE - 1) { //print border
                cout << "#" << " ";
            } else if(column == fruitX && row == fruitY) { // print fruit
                cout << "F" << " ";
            } else if(column == headX && row == headY) { //print snake head
                cout << "O" << " ";
            } else {
                //print tail
                int ok = 0;
                for(int i = 0; i < nTail; i++) {
                    if(column == tailX[i] && row == tailY[i]) {
                        cout << "O" << " ";
                        ok = 1;
                    }
                }
                //print the blank space in case its not the tail
                if(ok == 0)
                    cout << " " << " ";
            }
        }
        cout << endl;
    }

    //print score
    cout << "Your score: " << score << endl;
}

int main() {
    //Setup of the game
    Setup();

    //Game infinite loop
    while(!gameOver) {
        Input();
        Logic();
        Draw();
        Sleep(1000);
    }

    return 0;
}
