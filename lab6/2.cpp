#include <iostream>

using namespace std;

const int N = 6;

char maze[N][N] = {
    {'S', 0, 0, 1, 0, 0},
    {1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 0},
    {1, 1, 1, 0, 0, 'F'}
};

bool visited[N][N] = {};
int pathX[N * N];
int pathY[N * N];
int pathLen = 0;

void printMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == 1) {
                cout << "# ";
            }
            else if (maze[i][j] == 'S') {
                cout << "S ";
            }
            else if (maze[i][j] == 'F') {
                cout << "F ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

void printMazeWithPath() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bool onPath = false;
            for (int k = 0; k < pathLen; k++) {
                if (pathX[k] == i && pathY[k] == j) {
                    onPath = true;
                    break;
                }
            }
            if (maze[i][j] == 'S') {
                cout << "S ";
            }
            else if (maze[i][j] == 'F') {
                cout << "F ";
            }
            else if (maze[i][j] == 1) {
                cout << "# ";
            }
            else if (onPath) {
                cout << "* ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

bool solveMaze(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N) {
        return false;
    }
    if (maze[x][y] == 1 || visited[x][y]) {
        return false;
    }
    visited[x][y] = true;
    pathX[pathLen] = x;
    pathY[pathLen] = y;
    pathLen++;
    if (maze[x][y] == 'F') {
        return true;
    }
    if (solveMaze(x + 1, y)) {
        return true;
    }
    if (solveMaze(x - 1, y)) {
        return true;
    }
    if (solveMaze(x, y + 1)) {
        return true;
    }
    if (solveMaze(x, y - 1)) {
        return true;
    }
    visited[x][y] = false;
    pathLen--;
    return false;
}

void runMaze() {
    cout << "Исходный лабиринт:\n";
    printMaze();
    cout << endl;
    
    if (solveMaze(0, 0)) {
        cout << "Путь найден (длина " << pathLen << "):\n";
        printMazeWithPath();
        cout << endl;
    }
    else {
        cout << "Пути нет" << endl;
    }
    cout << endl;
}

const int Q = 5;
int board[Q][Q] = {};
int solutions = 0;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col]) {
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < Q; i--, j++) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

void solveQueens(int row) {
    if (row == Q) {
        solutions++;
        cout << "Решение " << solutions << ":" << endl;
        for (int i = 0; i < Q; i++) {
            for (int j = 0; j < Q; j++) {
                if (board[i][j]) {
                    cout << "Q ";
                }
                else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    for (int col = 0; col < Q; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            solveQueens(row + 1);
            board[row][col] = 0;
        }
    }
}

void runQueens() {
    solveQueens(0);
    cout << "Всего решений: " << solutions << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    cout << "Лабиринт" << endl;
    runMaze();
    
    cout << "Задача о ферзях" << endl;
    runQueens();
    
    return 0;
}