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

bool isOnGround(const int screenHeight, const AnimData &playerData) {
    return playerData.pos.y >= (float)screenHeight - playerData.rec.height;
}

AnimData &updateAnimData(AnimData &data, const float deltaTime, int maxFrame) {
    data.runningTime += deltaTime;  // Add the delta time to the running time
    if (data.runningTime >= data.updateTime) {  // Check if the running time is greater than or equal to the update time
        data.runningTime = 0;  // Subtract the update time from the running time
        data.rec.x = data.frame * data.rec.width;  // Update the x-coordinate of playerRec based on the frame and playerRec width
        data.frame++;  // Increment the frame by 1
        if (data.frame > maxFrame) {  // Check if the frame is greater than 5
            data.frame = 0;  // Reset the frame to 0
        }
    }
    return data;
}

int main() {

    // Textures
    const char* playerTexturePath = "textures/scarfy.png";
    const char *nebulaTexturePath = "textures/12_nebula_spritesheet.png";  // Define a string variable nebulaTexturePath with a value of "textures/nebula.png"

    // Game
    const int screenWidth = 750;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Platformer basics C++");  // Initialize the window with the specified screen width, screen height, and window title

    const int gravity{1'000};  // Define a constant variable gravity with a value of 1

    // Player
    const int jumpVelocity{-600};  // Define a constant variable jumpVelocity with a value of -22
    int playerSpeed{5}; // Define a constant variable playerSpeed with a value of 5
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
    Texture2D backgroundTexture = LoadTexture("textures/far-buildings.png");  // Load the background texture
    Texture2D midgroundTexture = LoadTexture("textures/back-buildings.png");  // Load the background texture
    Texture2D foregroundTexture = LoadTexture("textures/foreground.png");  // Load the background texture
    float bgx{};  // Declare a float variable bgx and initialize it with 0
    float midgx{};  // Declare a float variable midgx and initialize it with 0
    float fgx{};  // Declare a float variable fgx and initialize it with 0
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
        nebulae[i].pos = {(float)screenWidth + (300 * (float)i), screenHeight - (float)nebulaTexture.height / 8};
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0f;
        nebulae[i].updateTime = 1.0f / 16.0f;
    }

    float finishLine{ nebulae[std::size(nebulae) - 1].pos.x };

    int nebVelocity{-200};  // Declare an integer variable nevVelocity and initialize it with -600
    bool collision = false;

    SetTargetFPS(60);  // Set the target frames per second to 60

    while (!WindowShouldClose()) {  // Start a loop that runs until the window is closed

        //update
        const float deltaTime = GetFrameTime();  // Get the delta time in seconds
        BeginDrawing();  // Begin drawing the graphics


        ClearBackground(WHITE);  // Clear the background with the color white

        // scroll background
        bgx -= 20 * deltaTime;
        Vector2 bg1{bgx, 0.0f};
        DrawTextureEx(backgroundTexture,  bg1,0.0,3.0, WHITE);
        Vector2 bg2{bgx + backgroundTexture.width * 3, 0.0f};
        DrawTextureEx(backgroundTexture, bg2,0.0,3.0, WHITE);
        if(bgx <= -backgroundTexture.width * 3){
            bgx = 0;
        }

        // scroll midground
        midgx -= 40 * deltaTime;
        Vector2 midg1{midgx, 0.0f};
        DrawTextureEx(midgroundTexture,  midg1,0.0,3.0, WHITE);
        Vector2 midg2{midgx + midgroundTexture.width *3, 0.0f};
        DrawTextureEx(midgroundTexture, midg2,0.0,3.0, WHITE);
        if(midgx <= -midgroundTexture.width * 3){
            midgx = 0;
        }

        // scroll foreground
        fgx -= 80 * deltaTime;
        Vector2 fg1{fgx, 0.0f};
        DrawTextureEx(foregroundTexture,  fg1,0.0,3.0, WHITE);
        Vector2 fg2{fgx + foregroundTexture.width * 3, 0.0f};
        DrawTextureEx(foregroundTexture, fg2,0.0,3.0, WHITE);
        if(fgx <= -foregroundTexture.width * 3){
            fgx = 0;
        }

        DrawFPS(10, 10);  // Draw the frames per second counter at position (10, 10)


        //gravity
        if (isOnGround(screenHeight, playerData)) {  // Check if the player's y-coordinate is on the ground
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

        //run or walk
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            playerSpeed = 10; // Update the player's x-coordinate based on the velocity
        }
        if(IsKeyReleased(KEY_LEFT_SHIFT)){
            playerSpeed = 5; // Update the player's x-coordinate based on the velocity
        }

        playerData.pos.y += velocity * deltaTime;  // Update the player's y-coordinate based on the velocity

        if(!bIsPlayerJumping){
            //update animation frame
            playerData = updateAnimData(playerData, deltaTime,5);
        }



        for(AnimData & i : nebulae){
            float pad{40};
            Rectangle nebRec{
                i.pos.x + pad,
                i.pos.y + pad,
                i.rec.width -  2 * pad,
                i.rec.height - 2 * pad
            };
            Rectangle playerRec{
                playerData.pos.x,
                playerData.pos.y,
                playerData.rec.width,
                playerData.rec.height
            };
            if(CheckCollisionRecs( playerRec, nebRec)){
                printf("Collision");
                collision = true;
            }
        }
        if (collision){
            // lose the game
            DrawText("Game Over", screenWidth / 4, screenHeight / 2, 50, RED);
        }
        else if(playerData.pos.x >= finishLine){
            // win the game
            DrawText("You Win", screenWidth / 2, screenHeight / 2, 50, GREEN);
        }
        else{
            // win the game
            for(auto & i : nebulae){
                DrawTextureRec(nebulaTexture, i.rec, i.pos, WHITE);  // Draw the nebula texture at the specified position and with the specified color
            }

            DrawTextureRec(playerTexture,playerData.rec, playerData.pos, WHITE);  // Draw the player texture at the specified position and with the specified color

        }

        for(AnimData & i : nebulae){
            i.pos.x += (float)nebVelocity * deltaTime;

        }

        finishLine += (float)nebVelocity * deltaTime;

        //nebula animation frame
        for(auto & i : nebulae){
            i = updateAnimData(i, deltaTime, 7);
        }



        EndDrawing();  // End drawing the graphics
    }

    // Unload
    UnloadTexture(nebulaTexture);  // Unload the nebula texture
    UnloadTexture(backgroundTexture);  // Unload the nebula texture
    UnloadTexture(playerTexture);  // Unload the player texture
    UnloadTexture(midgroundTexture);
    UnloadTexture(foregroundTexture);


    // Close the window
    CloseWindow();

    return 0;  // Return 0 to indicate successful program termination
}