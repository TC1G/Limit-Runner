#include "raylib.h" // Jumping runner game made by Alija.A

struct AnimData //ANIM DATA
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float runningTime;
    float updateTime;
};

bool isOnGround(AnimData data, int windowHeight) {

   return data.pos.y >= windowHeight - data.rec.height;
}
AnimData updateAnimData (AnimData data, float deltaTime, int maxframe) {

//update running time
data.runningTime += deltaTime ;


}

int main() {

    float WindowDimensions [2]; //ARRAY FOR WINDOW
    WindowDimensions [0]=800; // width
    WindowDimensions [1]=600; // height



   
    //FPS
    SetTargetFPS(60);  

    //VARIABLES FOR RUNNER AND GRAVITY
    float velocity = 0;
    bool isJumping = false;
    const float jumpForce = -3000;
    const float gravity = 20;

    //WINDOW
    InitWindow(WindowDimensions[0], WindowDimensions [1], "Runner");

    //RUNNER TEXTURE SPRITES INITIALIZATION
    Texture2D Runner = LoadTexture("textures/Runner.png");
    AnimData RunnerData;
    RunnerData.rec.width = Runner.width / 6;
    RunnerData.rec.height = Runner.height;
    RunnerData.rec.x = 0;
    RunnerData.rec.y = 0;
    RunnerData.pos.x = WindowDimensions [0]/ 2 - RunnerData.rec.width / 2;
    RunnerData.pos.y = WindowDimensions [1] - RunnerData.rec.height;
    RunnerData.frame = 0;
    RunnerData.updateTime = 1.0 / 12.0;
    RunnerData.runningTime = 0.0;

    //SPRITE HAZARD TEXTURE INITIALIZATION
    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    //ANIM DATA ARRAY FOR HAZARD NEBULA
    const int sizeOfnebulae{6};

    AnimData nebulae[sizeOfnebulae]{};
    

    for (int i = 0; i < sizeOfnebulae; i++)
    {
        nebulae[i].rec.x= 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = Nebula.width/8.f;
        nebulae[i].rec.height = Nebula.height/8.f;
        nebulae[i].pos.y = WindowDimensions[1] - Nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
        nebulae[i].pos.x = WindowDimensions[0] + i * 300;

    }
        float finishline {nebulae[sizeOfnebulae - 1].pos.x}; // FINISH LINE


    //VELOCITY
    int NebVel = -200;

    Texture2D background = LoadTexture ("textures/far-buildings.png");
   
    float bgX{0};
    
    //WHILE LOOP START (GAME START)
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        float dT = GetFrameTime();
        bgX -= 20 * dT;
        if (bgX <= -background.width * 2)
        {
            bgX = 0.0;
        }
        

        Vector2 bg1pos{bgX, 0.0};
        DrawTextureEx (background,bg1pos, 0.0, 3.5, WHITE );
        Vector2 bg2pos {bgX + background.width * 2, 0.0};
        DrawTextureEx (background,bg2pos, 0.0, 3.5, WHITE );

         //DELTA TIME

        RunnerData.pos.y += velocity;
        //IS IN THE AIR?
        if (isOnGround (RunnerData, WindowDimensions[1])) {
            velocity = 0;
            isJumping = false;
        } else {
            velocity += gravity * dT;
            isJumping = true;
            RunnerData.frame = 0;
        }
        //JUMP MECHANIC
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isJumping) {
            velocity += jumpForce * 0.25f * dT;
        }
       //UPDATE NEBULA POS FRAME
       for (int i = 0; i < sizeOfnebulae; i++)
       {
        nebulae[i].pos.x += NebVel * dT;
       }
       
       finishline += NebVel * dT; //finish line
       bool collisionDetected {};
    
        //UPDATE RUNNER POS FRAME
        RunnerData.pos.y += velocity;

        RunnerData.runningTime += dT;
            if (!isJumping)
            
                if (RunnerData.runningTime >= RunnerData.updateTime) {
            RunnerData.runningTime = 0;
            RunnerData.rec.x = RunnerData.frame * RunnerData.rec.width;
            RunnerData.frame++;
            if (RunnerData.frame > 5) {
                RunnerData.frame = 0;
            }
            
        }
        //UPDATE NEBULA ANIM FRAME*
        for (int i = 0; i < sizeOfnebulae; i++)
        {
                nebulae[i].runningTime += dT;
                if (nebulae[i].runningTime >= nebulae[i].updateTime) 
                {
                nebulae[i].runningTime = 0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++; }
                if (nebulae[i].frame > 7) 
                {
                    nebulae[i].frame = 0;
                }

                    
                    for (AnimData Nebula : nebulae)
                    {
                        float pad {20};
                        Rectangle nebRec{
                                Nebula.pos.x + pad,
                                Nebula.pos.y + pad,                           // COLLISION
                                Nebula.rec.width - 2* pad,
                                Nebula.rec.height - 2* pad,


                        };
                        Rectangle RunnerRec {

                            RunnerData.pos.x,
                            RunnerData.pos.y,
                            RunnerData.rec.height,
                            RunnerData.rec.width
                        };

                        if (CheckCollisionRecs(nebRec,RunnerRec))
                        {
                            collisionDetected = true;
                        }
                        


                    }
                    
                
        }

        if (collisionDetected)
        {
            DrawText ("You Lose!", WindowDimensions[0]/4,WindowDimensions[1]/2,50, RED);
            UnloadTexture(Nebula);
            UnloadTexture(Runner);
        }
else if (RunnerData.pos.x >= finishline)
{
   DrawText ("You WIN!", WindowDimensions[0]/4,WindowDimensions[1]/2,50, GREEN);
}

        else {
        for (int i = 0; i < sizeOfnebulae; i++)
                {
                    DrawTextureRec(Nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
                }
                

            
                DrawTextureRec(Runner, RunnerData.rec, RunnerData.pos, WHITE);


        }
        

        

        EndDrawing();
    }


    UnloadTexture(Runner);
    UnloadTexture(Nebula);
    UnloadTexture (background);
    CloseWindow();
   
}
