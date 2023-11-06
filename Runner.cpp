#include "raylib.h"


int main() {

const int screenWidth{800};
const int screenHeight{600};

//FPS
SetTargetFPS(60);

//CHARACTER MAIN
    int posX {screenWidth/2};
    float velocity {0};
    bool isJumping {};
    const float jumpForce {-3000};

InitWindow(screenWidth, screenHeight, "Runner");

//GRAVITY
const float gravity {20};

//LOAD TEXTURES && VARIABLES FOR CHARACTER
Texture2D Runner = LoadTexture("textures/Runner.png");
Rectangle RunnerRec ;
RunnerRec.width = Runner.width/6;  
RunnerRec.height = Runner.height;
RunnerRec.x = 0;
RunnerRec.y = 0;
Vector2 RunnerPosition;
RunnerPosition.x = screenWidth/2 - RunnerRec.width/2;
RunnerPosition.y = screenHeight - RunnerRec.height;
//ANIM FRAME
int frame{};
//RUNNING
const float updateTime {1.0 / 12.0};
float runningTime {0};  

//HAZARD TEXTURES
Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");






//WHILE LOOP
while (!WindowShouldClose())
{
    BeginDrawing ();
    ClearBackground(WHITE);
    float dT{GetFrameTime()};

   //Update Position
    RunnerPosition.y += velocity;

    //CHECK IF CHAR IS OUT OF SCREEN
    if (posX + Runner.width > screenWidth)
{
    posX = screenWidth - Runner.width;
}

if (RunnerPosition.y + RunnerRec.height > screenHeight)
{
    RunnerPosition.y = screenHeight - RunnerRec.height;
}
if (RunnerPosition.y < 0)
{
    RunnerPosition.y = 0;
    velocity = 0;
}
    
    
    //JUMP MECHANICS 
    if (RunnerPosition.y >= screenHeight - RunnerRec.height)
    {
        velocity = 0;
        isJumping = false;
    }
    else 
    {

    velocity += gravity * dT;
    isJumping = true;

    }

    if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) && !isJumping)
    {
        velocity += jumpForce * 0.25f * dT;
    }
    RunnerPosition.y += velocity;
    runningTime += dT;
    if (runningTime >= updateTime)
    {
        runningTime = 0;
        
    //UPDATE ANIM FRAME
        RunnerRec.x = frame * RunnerRec.width;
        frame++;
        if (frame > 5)
        {
            frame = 0;
        }
    }
    

    

    DrawTextureRec(Runner, RunnerRec, RunnerPosition, WHITE);



    EndDrawing();
}
UnloadTexture (Runner);    
CloseWindow();
}









