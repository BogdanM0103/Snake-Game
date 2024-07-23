#include <iostream>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;
const int dimension = 9;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

char arena[dimension][dimension];

int headX, headY;

int fruitX, fruitY;

int score;

bool gameOver;

void End() {
    cout << "Game Over!" << endl;
    return;
}

void Generate_fruit() {
    srand(time(NULL));
    fruitX = rand() % dimension + 1;
    fruitY = rand() % dimension + 1;
    Sleep(1000);
    while((fruitX == headX && fruitY == headY) || (fruitX == 0 || fruitX == dimension - 1 || fruitY == 0 || fruitY == dimension - 1)) {
        fruitX = rand() % dimension + 1;
        fruitY = rand() % dimension + 1;
    }
    arena[fruitX][fruitY] = 'F';
}

void Setup() {
    headX = dimension / 2;
    headY = dimension / 2;
    Generate_fruit();
    for(int row = 0; row < dimension; row++) {
        for(int column = 0; column < dimension; column++) {
            if(row == 0 || row == dimension - 1 || column == 0 || column == dimension - 1) {
                arena[row][column] = '#';
            } else {
                arena[row][column] = ' ';
            }
        }
    }
    arena[headX][headY] = 'O';
    arena[fruitX][fruitY] = 'F';
}

void Draw() {
    system("cls");
    for(int row = 0; row < dimension; row++) {
        for(int column = 0; column < dimension; column++) {
            cout << arena[row][column] << " ";
        }
        cout << endl;
    }
    cout << "score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
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
            End();
            break;
        }
    }
}

void Logic() {
    if(headX == 0 || headX == dimension - 1 || headY == 0 || headY == dimension - 1) {
        gameOver = true;
        End();
    }
    if(headX == fruitX && headY == fruitY) {
        //Sleep(1000);
        score++;
        Generate_fruit();
    }
    switch(dir) {
    case UP:
        arena[headX - 1][headY] = 'O';
        arena[headX][headY] = ' ';
        headX--;
        break;
    case DOWN:
        arena[headX + 1][headY] = 'O';
        arena[headX][headY] = ' ';
        headX++;
        break;
    case LEFT:
        arena[headX][headY - 1] = 'O';
        arena[headX][headY] = ' ';
        headY--;
        break;
    case RIGHT:
        arena[headX][headY + 1] = 'O';
        arena[headX][headY] = ' ';
        headY++;
        break;
    }
}

int main() {
    Setup();
    while(!gameOver) {
        Input();
        Logic();
        Draw();
        Sleep(1000);
    }
    return 0;
}
