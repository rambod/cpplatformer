#include <iostream>  // Include the input/output stream library
#include <raylib.h>  // Include the raylib library

int main() {
    const char *playerTexturePath = "C:\\Users\\rambo\\CLionProjects\\cpplatformer\\textures\\scarfy.png";  // Define a string variable playerTexturePath with a value of "textures/player.png"
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Platformer basics C++");  // Initialize the window with the specified screen width, screen height, and window title

    const int gravity{1};  // Define a constant variable gravity with a value of 1
    const int jumpVelocity{-22};  // Define a constant variable jumpVelocity with a value of -22

    Texture2D playerTexture = LoadTexture(playerTexturePath);  // Load the player texture
    Texture2D platformTexture = LoadTexture("textures/foreground.png");  // Load the platform texture

    Rectangle playerRec;  // Declare a variable playerRec of type Rectangle
    playerRec.width = playerTexture.width / 6;  // Set the width of playerRec to 20
    playerRec.height = playerTexture.height;  // Set the height of playerRec to 20
    playerRec.x = 0;  // Set the x-coordinate of playerRec to 0
    playerRec.y = 0;  // Set the y-coordinate of playerRec to 0

    Vector2 playerPos{0.0f, 0.0f};  // Declare a variable playerPos of type Vector2 and initialize it with (0.0f, 0.0f)
    playerPos.x = screenWidth / 2 - playerRec.width / 2;  // Calculate the x-coordinate of playerPos based on the screen width and playerRec width
    playerPos.y = screenHeight - playerRec.height;  // Calculate the y-coordinate of playerPos based on the screen height and playerRec height

    bool bIsPlayerGrounded{true};  // Declare a boolean variable bIsPlayerGrounded and initialize it with true

    int velocity{0};  // Declare an integer variable velocity and initialize it with 0

    SetTargetFPS(60);  // Set the target frames per second to 60

    while (!WindowShouldClose()) {  // Start a loop that runs until the window is closed
        BeginDrawing();  // Begin drawing the graphics

        ClearBackground(WHITE);  // Clear the background with the color white

        DrawFPS(10, 10);  // Draw the frames per second counter at position (10, 10)

       // DrawRectangle(playerPos.x, playerPos.y, playerRec.width, playerRec.height, RED);  // Draw a rectangle representing the player at the specified position and with the specified width, height, and color
        DrawTextureRec(playerTexture,playerRec, playerPos, WHITE);  // Draw the player texture at the specified position and with the specified color

        if (playerPos.y >= screenHeight - playerRec.height) {  // Check if the player's y-coordinate is on the ground
            velocity = 0;  // Set the velocity to 0
            bIsPlayerGrounded = true;  // Set bIsPlayerGrounded to true
        }else{
            velocity += gravity;  // Add gravity to the velocity
        }

        if (IsKeyDown(KEY_SPACE) && bIsPlayerGrounded) {  // Check if the space key is pressed and the player is grounded
            velocity = jumpVelocity;  // Set the velocity to the jump velocity
            bIsPlayerGrounded = false;  // Set bIsPlayerGrounded to false
        }
        if(IsKeyDown(KEY_D)){
            playerPos.x += 5; // Update the player's x-coordinate based on the velocity
        }
        if(IsKeyDown(KEY_A)){
            playerPos.x -= 5; // Update the player's x-coordinate based on the velocity
        }

        playerPos.y += velocity;  // Update the player's y-coordinate based on the velocity

        EndDrawing();  // End drawing the graphics
    }

    UnloadTexture(playerTexture);  // Unload the player texture
    CloseWindow();  // Close the window

    return 0;  // Return 0 to indicate successful program termination
}