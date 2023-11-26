#include <iostream>  // Include the input/output stream library
#include <raylib.h>  // Include the raylib library


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main() {
    const char *playerTexturePath = "C:\\Users\\rambo\\CLionProjects\\cpplatformer\\textures\\scarfy.png";  // Define a string variable playerTexturePath with a value of "textures/player.png"
    const char *nebulaTexturePath = "C:\\Users\\rambo\\CLionProjects\\cpplatformer\\textures\\12_nebula_spritesheet.png";  // Define a string variable nebulaTexturePath with a value of "textures/nebula.png"
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Platformer basics C++");  // Initialize the window with the specified screen width, screen height, and window title

    const int gravity{1'000};  // Define a constant variable gravity with a value of 1

    // Player
    const int jumpVelocity{-600};  // Define a constant variable jumpVelocity with a value of -22
    const int playerSpeed{5};
    int velocity{0};  // Declare an integer variable velocity and initialize it with 0

    Texture2D playerTexture = LoadTexture(playerTexturePath);  // Load the player texture
    AnimData playerData;  // Declare a variable playerData of type AnimData
    playerData.rec.width = playerTexture.width / 6;  // Set the width of playerData.rec to 20
    playerData.rec.height = playerTexture.height;  // Set the height of playerData.rec to 20
    playerData.rec.x = 0;  // Set the x-coordinate of playerData.rec to 0
    playerData.rec.y = 0;  // Set the y-coordinate of playerData.rec to 0
    playerData.pos.x = screenWidth / 2 - playerData.rec.width / 2;  // Calculate the x-coordinate of playerData.pos based on the screen width and playerData.rec width
    playerData.pos.y = screenHeight - playerData.rec.height;  // Calculate the y-coordinate of playerData.pos based on the screen height and playerData.rec height
    playerData.frame = 0;  // Set the frame of playerData to 0
    playerData.updateTime = 1.0f / 12.0f;  // Set the update time of playerData to 1.0f / 12.0f
    playerData.runningTime = 0.0f;

    Rectangle playerRec;  // Declare a variable playerRec of type Rectangle
    playerRec.width = playerTexture.width / 6;  // Set the width of playerRec to 20
    playerRec.height = playerTexture.height;  // Set the height of playerRec to 20
    playerRec.x = 0;  // Set the x-coordinate of playerRec to 0
    playerRec.y = 0;  // Set the y-coordinate of playerRec to 0

    Vector2 playerPos{0.0f, 0.0f};  // Declare a variable playerPos of type Vector2 and initialize it with (0.0f, 0.0f)
    playerPos.x = screenWidth / 2 - playerRec.width / 2;  // Calculate the x-coordinate of playerPos based on the screen width and playerRec width
    playerPos.y = screenHeight - playerRec.height;  // Calculate the y-coordinate of playerPos based on the screen height and playerRec height

    bool bIsPlayerGrounded{true};  // Declare a boolean variable bIsPlayerGrounded and initialize it with true
    bool bIsPlayerJumping{false};  // Declare a boolean variable bIsPlayerJumping and initialize it with false
    int frame{0}; // Declare an integer variable frame and initialize it with 0
    const float updateTime = 0.12f;  // Declare a constant variable updateTime and initialize it with 0.1f
    float runningTime{0.0f};  // Declare a float variable runningTime and initialize it with 0.0f


    // Background
    Texture2D backgroundTexture = LoadTexture("C:\\Users\\rambo\\CLionProjects\\cpplatformer\\textures\\back-buildings.png");  // Load the background texture
    Rectangle backgroundRec;  // Declare a variable backgroundRec of type Rectangle
    backgroundRec.width = screenWidth;  // Set the width of backgroundRec to the width of the background texture
    backgroundRec.height = screenHeight;  // Set the height of backgroundRec to the height of the background texture
    backgroundRec.x = 0;  // Set the x-coordinate of backgroundRec to 0
    backgroundRec.y = 0;  // Set the y-coordinate of backgroundRec to 0

    // Nebula
    Texture2D nebulaTexture = LoadTexture(nebulaTexturePath);  // Load the nebula texture

    AnimData nebData{
            .rec = {0.0f, 0.0f, (float) nebulaTexture.width / 8, (float) nebulaTexture.height / 8},
            .pos = {screenWidth, screenHeight - (float)nebulaTexture.height / 8},
            .frame = 0,
            .updateTime = 1.0f / 12.0f,
            .runningTime = 0.0f
    };
    AnimData neb2Data{
            .rec = {0.0f, 0.0f, (float) nebulaTexture.width / 8, (float) nebulaTexture.height / 8},
            .pos = {screenWidth + 300, screenHeight - (float)nebulaTexture.height / 8},
            .frame = 0,
            .updateTime = 1.0f / 12.0f,
            .runningTime = 0.0f
    };
    Rectangle nebRec;  // Declare a variable nebRec of type Rectangle
    nebRec.width = nebulaTexture.width / 8;  // Set the width of nebRec to the screen width
    nebRec.height = nebulaTexture.height / 8;  // Set the height of nebRec to the screen height
    nebRec.x = 0.0f;  // Set the x-coordinate of nebRec to 0
    nebRec.y = 0.0f;  // Set the y-coordinate of nebRec to 0

    Vector2 nebPos;  // Declare a variable nebPos of type Vector2 and initialize it with (0.0f, 0.0f)
    nebPos.x = screenWidth;  // Calculate the x-coordinate of nebPos based on the screen width and nebRec width
    nebPos.y = screenHeight - nebRec.height;  // Calculate the y-coordinate of nebPos based on the screen height and nebRec height
    int nebFrame{0};  // Declare an integer variable nebFrame and initialize it with 0
    int nebVelocity{-200};  // Declare an integer variable nevVelocity and initialize it with -600
    float nubRunningTime{0.0f};  // Declare a float variable nubRunningTime and initialize it with 0.0f
    float nubUpdateTime{0.12f};  // Declare a float variable nubUpdateTime and initialize it with 0.12f


    SetTargetFPS(60);  // Set the target frames per second to 60

    while (!WindowShouldClose()) {  // Start a loop that runs until the window is closed


        //update

        const float deltaTime = GetFrameTime();  // Get the delta time in seconds
        BeginDrawing();  // Begin drawing the graphics

        DrawTextureRec(backgroundTexture, backgroundRec, Vector2{0.0f, 0.0f}, WHITE);

        ClearBackground(WHITE);  // Clear the background with the color white

        DrawFPS(10, 10);  // Draw the frames per second counter at position (10, 10)

       // DrawRectangle(playerPos.x, playerPos.y, playerRec.width, playerRec.height, RED);  // Draw a rectangle representing the player at the specified position and with the specified width, height, and color
        DrawTextureRec(playerTexture,playerRec, playerPos, WHITE);  // Draw the player texture at the specified position and with the specified color

        //gravity
        if (playerPos.y >= screenHeight - playerRec.height) {  // Check if the player's y-coordinate is on the ground
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
            playerPos.x += playerSpeed; // Update the player's x-coordinate based on the velocity
        }
        //move
        if(IsKeyDown(KEY_A)){
            playerPos.x -= playerSpeed; // Update the player's x-coordinate based on the velocity
        }

        playerPos.y += velocity * deltaTime;  // Update the player's y-coordinate based on the velocity

        if(!bIsPlayerJumping){
            //update animation frame
            runningTime += deltaTime;  // Add the delta time to the running time
            if (runningTime >= updateTime) {  // Check if the running time is greater than or equal to the update time
                runningTime = 0;  // Subtract the update time from the running time
                playerRec.x = frame * playerRec.width;  // Update the x-coordinate of playerRec based on the frame and playerRec width
                frame++;  // Increment the frame by 1
                if (frame > 5) {  // Check if the frame is greater than 5
                    frame = 0;  // Reset the frame to 0
                }
            }
        }


        //draw
        DrawTextureRec(nebulaTexture, nebRec, nebPos, WHITE);  // Draw the nebula texture at the specified position and with the specified color
        nebPos.x += nebVelocity * deltaTime;  // Update the x-coordinate of nebPos based on the delta time

        //nebula animation frame
        nubRunningTime += deltaTime;
        if(nubRunningTime >= nubUpdateTime){
            nubRunningTime = 0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame = 0;

            }
        }
        EndDrawing();  // End drawing the graphics
    }


    //unload
    UnloadTexture(nebulaTexture);  // Unload the nebula texture
    UnloadTexture(playerTexture);  // Unload the player texture
    CloseWindow();  // Close the window

    return 0;  // Return 0 to indicate successful program termination
}