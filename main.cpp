#include <iostream>  // Include the input/output stream library
#include <raylib.h> // Include the raylib library
#include <iterator>


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() {

    // Textures
    const char* playerTexturePath = "textures/scarfy.png";
    const char *nebulaTexturePath = "textures/12_nebula_spritesheet.png";  // Define a string variable nebulaTexturePath with a value of "textures/nebula.png"

    // Game
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Platformer basics C++");  // Initialize the window with the specified screen width, screen height, and window title

    const int gravity{1'000};  // Define a constant variable gravity with a value of 1

    // Player
    const int jumpVelocity{-600};  // Define a constant variable jumpVelocity with a value of -22
    const int playerSpeed{5}; // Define a constant variable playerSpeed with a value of 5
    int velocity{0};  // Declare an integer variable velocity and initialize it with 0

    Texture2D playerTexture = LoadTexture(playerTexturePath);  // Load the player texture
    AnimData playerData{
        .rec = {0, 0, (float)playerTexture.width / 6, (float)playerTexture.height},
        .pos = {0, 0},
        .frame = 0,
        .updateTime = 1.0f / 12.0f,
        .runningTime = 0.0f

    };  // Declare a variable playerData of type AnimData
    bool bIsPlayerGrounded{true};  // Declare a boolean variable bIsPlayerGrounded and initialize it with true
    bool bIsPlayerJumping{false};  // Declare a boolean variable bIsPlayerJumping and initialize it with false


    // Background
    Texture2D backgroundTexture = LoadTexture("textures/back-buildings.png");  // Load the background texture
    Rectangle backgroundRec;  // Declare a variable backgroundRec of type Rectangle
    backgroundRec.width = screenWidth;  // Set the width of backgroundRec to the width of the background texture
    backgroundRec.height = screenHeight;  // Set the height of backgroundRec to the height of the background texture
    backgroundRec.x = 0;  // Set the x-coordinate of backgroundRec to 0
    backgroundRec.y = 0;  // Set the y-coordinate of backgroundRec to 0

    // Nebula
    Texture2D nebulaTexture = LoadTexture(nebulaTexturePath);  // Load the nebula texture


    AnimData nebulae[3]{};
    for(int i = 0; i < std::size(nebulae); i++){
        nebulae[i].rec = {0.0f, 0.0f, (float) nebulaTexture.width / 8, (float) nebulaTexture.height / 8};
        nebulae[i].pos = {screenWidth, screenHeight - (float)nebulaTexture.height / 8};
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0f;
        nebulae[i].updateTime = 1.0f / 16.0f;
    }

    nebulae[1].pos.x = screenWidth + 300;
    nebulae[2].pos.x = screenWidth + 600;

    int nebVelocity{-200};  // Declare an integer variable nevVelocity and initialize it with -600

    SetTargetFPS(60);  // Set the target frames per second to 60

    while (!WindowShouldClose()) {  // Start a loop that runs until the window is closed

        //update
        const float deltaTime = GetFrameTime();  // Get the delta time in seconds
        BeginDrawing();  // Begin drawing the graphics

        DrawTextureRec(backgroundTexture, backgroundRec, Vector2{0.0f, 0.0f}, WHITE);

        ClearBackground(WHITE);  // Clear the background with the color white

        DrawFPS(10, 10);  // Draw the frames per second counter at position (10, 10)

        DrawTextureRec(playerTexture,playerData.rec, playerData.pos, WHITE);  // Draw the player texture at the specified position and with the specified color

        //gravity
        if (playerData.pos.y >= screenHeight - playerData.rec.height) {  // Check if the player's y-coordinate is on the ground
            velocity = 0;  // Set the velocity to 0
            bIsPlayerGrounded = true;  // Set bIsPlayerGrounded to true
            bIsPlayerJumping = false;  // Set bIsPlayerJumping to false
        }else{
            velocity += gravity * deltaTime;  // Add gravity to the velocity
        }

        //jump
        if (IsKeyDown(KEY_SPACE) && bIsPlayerGrounded) {  // Check if the space key is pressed and the player is grounded
            velocity = jumpVelocity;  // Set the velocity to the jump velocity
            bIsPlayerGrounded = false;  // Set bIsPlayerGrounded to false
            bIsPlayerJumping = true;  // Set bIsPlayerJumping to true
        }
        //move
        if(IsKeyDown(KEY_D)){
            playerData.pos.x += playerSpeed; // Update the player's x-coordinate based on the velocity
        }
        //move
        if(IsKeyDown(KEY_A)){
            playerData.pos.x -= playerSpeed; // Update the player's x-coordinate based on the velocity
        }

        playerData.pos.y += velocity * deltaTime;  // Update the player's y-coordinate based on the velocity

        if(!bIsPlayerJumping){
            //update animation frame
            playerData.runningTime += deltaTime;  // Add the delta time to the running time
            if (playerData.runningTime >= playerData.updateTime) {  // Check if the running time is greater than or equal to the update time
                playerData.runningTime = 0;  // Subtract the update time from the running time
                playerData.rec.x = playerData.frame * playerData.rec.width;  // Update the x-coordinate of playerRec based on the frame and playerRec width
                playerData.frame++;  // Increment the frame by 1
                if (playerData.frame > 5) {  // Check if the frame is greater than 5
                    playerData.frame = 0;  // Reset the frame to 0
                }
            }
        }

        //rwte for to loop inside nebulae by checking lenght of it
//        for(int i=0 ; i < std::size(nebulae); i++){
//
//        }


        //draw
        DrawTextureRec(nebulaTexture, nebulae[0].rec, nebulae[0].pos, WHITE);  // Draw the nebula texture at the specified position and with the specified color
        nebulae[0].pos.x += nebVelocity * deltaTime;  // Update the x-coordinate of nebPos based on the delta time

        //nebula animation frame
        nebulae[0].runningTime += deltaTime;
        if(nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7){
                nebulae[0].frame = 0;

            }
        }
        EndDrawing();  // End drawing the graphics
    }

    // Unload
    UnloadTexture(nebulaTexture);  // Unload the nebula texture
    UnloadTexture(playerTexture);  // Unload the player texture

    // Close the window
    CloseWindow();

    return 0;  // Return 0 to indicate successful program termination
}