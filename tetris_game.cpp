#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>  // Windows: kbhit() and getch()
#else
#include <fcntl.h>
#include <sys/ioctl.h>
#endif

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
const char EMPTY = ' ';

// Tetromino shapes
const int tetrominoes[7][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // J
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // L
};

const char shapeChars[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

class Tetromino {
public:
    int shape[4][4] = {};
    int x, y;
    char blockChar;

    Tetromino(int type) : blockChar(shapeChars[type]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = tetrominoes[type][i][j];
        x = WIDTH / 2 - 2;
        y = 0;
    }
};

class GameBoard {
public:
    char grid[HEIGHT][WIDTH];

    GameBoard() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = EMPTY;
    }

    void draw(Tetromino &t) {
        cout << "\033[H\033[J"; // Clear screen
        for (int i = 0; i < HEIGHT; i++) {
            cout << "|";
            for (int j = 0; j < WIDTH; j++) {
                char displayChar = grid[i][j];

                for (int ti = 0; ti < 4; ti++) {
                    for (int tj = 0; tj < 4; tj++) {
                        if (t.shape[ti][tj] && (i == t.y + ti) && (j == t.x + tj)) {
                            displayChar = t.blockChar;
                        }
                    }
                }
                cout << displayChar;
            }
            cout << "|\n";
        }
        cout << " ";
        for (int i = 0; i < WIDTH; i++) cout << "-";
        cout << " \n";
        cout << "[A] Left  [D] Right  [S] Down  [P] Pause  [R] Restart  [X] Exit\n";
    }

    bool canMove(Tetromino &t, int dx, int dy) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (t.shape[i][j]) {
                    int newX = t.x + j + dx;
                    int newY = t.y + i + dy;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && grid[newY][newX] != EMPTY))
                        return false;
                }
            }
        }
        return true;
    }

    void placeTetromino(Tetromino &t) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j])
                    grid[t.y + i][t.x + j] = t.blockChar;
    }

    void clearBoard() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = EMPTY;
    }
};

class TetrisGame {
public:
    GameBoard board;
    Tetromino *currentPiece;
    bool gameOver = false;

    TetrisGame() {
        srand(time(0));
        currentPiece = new Tetromino(rand() % 7);
    }

    void run() {
        while (!gameOver) {
            handleInput();
            update();
            render();
            usleep(500000);
        }
        cout << "Game Over!" << endl;
    }

private:
    char getInput() {
#ifdef _WIN32
        if (_kbhit()) {
            return _getch();
        }
#else
        int bytesAvailable;
        ioctl(STDIN_FILENO, FIONREAD, &bytesAvailable);
        if (bytesAvailable > 0) {
            char key;
            read(STDIN_FILENO, &key, 1);
            return key;
        }
#endif
        return 0;
    }

    void handleInput() {
        char key = getInput();
        if (key == 'a' && board.canMove(*currentPiece, -1, 0))
            currentPiece->x--;  // Move left
        else if (key == 'd' && board.canMove(*currentPiece, 1, 0))
            currentPiece->x++;  // Move right
        else if (key == 's' && board.canMove(*currentPiece, 0, 1))
            currentPiece->y++;  // Move down
        else if (key == 'x')
            exitGame();  // Exit game
        else if (key == 'p')
            pauseGame(); // Pause game
        else if (key == 'r')
            restartGame(); // Restart game
    }

    void update() {
        if (board.canMove(*currentPiece, 0, 1))
            currentPiece->y++;
        else {
            board.placeTetromino(*currentPiece);
            delete currentPiece;
            currentPiece = new Tetromino(rand() % 7);
            if (!board.canMove(*currentPiece, 0, 0))
                gameOver = true;
        }
    }

    void render() {
        board.draw(*currentPiece);
    }

    void exitGame() {
        cout << "Exiting game...\n";
        exit(0);
    }

    void pauseGame() {
        cout << "Game paused. Press any key to continue...\n";
        cin.get(); // Wait for user input
    }

    void restartGame() {
        cout << "Restarting game...\n";
        board.clearBoard();
        delete currentPiece;
        currentPiece = new Tetromino(rand() % 7);
        gameOver = false;
    }
};

int main() {
#ifndef _WIN32
    system("stty -icanon -echo"); // Disable terminal buffering for macOS/Linux
#endif

    TetrisGame game;
    game.run();

#ifndef _WIN32
    system("stty icanon echo"); // Restore terminal settings
#endif

    return 0;
}
