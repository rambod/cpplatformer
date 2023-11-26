#include <iostream>
#include <raylib.h>

int main() {
    InitWindow(640, 480, "Platformer basics C++");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
