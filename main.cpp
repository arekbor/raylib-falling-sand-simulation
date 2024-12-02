/**
 * The program was created based on Coding Challenge 180: Falling Sand
 * 
 * Link below:
 * 
 * https://youtu.be/L4u7Zy_b868?si=XQV6_CyIKhQKtJnn
 * 
 */

#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

#define HEIGHT 400
#define WIDTH 400
#define TITLE "Falling Sand"

vector<vector<bool>> grid(WIDTH, vector<bool>(HEIGHT, false));

void Draw();
void AddSandGrainOnMouseDown();
bool IsInGrid(int x, int y);

int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    Draw();
    return 0;
}

void Draw() {
    while(!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        AddSandGrainOnMouseDown();

        for(int x = 0; x < WIDTH; x++) {
            for(int y = 0; y < HEIGHT; y++) {
                if (grid[x][y] == true) {
                    DrawPixel(x, y, YELLOW);
                }
            }
        }

        vector<vector<bool>> nextGrid(WIDTH, vector<bool>(HEIGHT, false));

        for(int x = 0; x < WIDTH; x++) {
            for(int y = 0; y < HEIGHT; y++) {
                bool currentState = grid[x][y];
                if (currentState) {

                    //Changes direction of falling sand randomly
                    int direction = rand() % (1 - 0 + 1) + 0;

                    bool stateBelow = IsInGrid(x, y + 1) && !grid[x][y + 1];
                    bool stateA = IsInGrid((x - direction), (y + 1)) && !grid[x - direction][y + 1];
                    bool stateB = IsInGrid((x + direction), (y + 1)) && !grid[x + direction][y + 1];

                    if (stateBelow) {
                        nextGrid[x][y + 1] = true;
                    } else if(stateA) {
                        nextGrid[x - direction][y + 1] = true;
                    } else if(stateB) {
                        nextGrid[x + direction][y + 1] = true;
                    } else {
                        nextGrid[x][y] = true;
                    }
                }
            }
        }
        grid = nextGrid;

        EndDrawing();
    }
    CloseWindow();
}

void AddSandGrainOnMouseDown() {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const int radius = 10;

        //Generates filled circle of sand
        for (int y = -radius; y <= radius; y++) {
            for(int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    int posX = GetMouseX() + x;
                    int posY = GetMouseY() + y;
                    if (IsInGrid(posX, posY)) {
                        grid[posX][posY] = true;
                    }
                }
            }
        }
    }
}

bool IsInGrid(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}