#include "App.h"
#include "Projectile.h"
#include "Maths.h"

App::~App()
{
    rlImGuiShutdown();
    CloseWindow();       
}

double App::DeltaTime()
{
    return m_deltaTime;
}

void App::CalcDeltaTime()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    
    m_deltaTime = std::chrono::duration<double>(now - m_lastFrame).count();
    m_lastFrame = now;
}

void App::Init(int width, int height)
{
	m_height = height;
	m_width = width;
    CalcDeltaTime();

    screenWidth = 1920;
    screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    rlImGuiSetup(true);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
}

void App::Update()
{
    CalcDeltaTime();

    Core::Projectile testProjectile{ Float2{(double)screenWidth/10, (double)6*screenHeight/8}, 15, 5 };
    testProjectile.AddForce(Float2{ 25 , -50 }, DeltaTime());

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        CalcDeltaTime();

        testProjectile.Update(DeltaTime());

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        /* Raylib Draws */
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        testProjectile.Draw();

        /* ========================  */
        /* ImGui */
        rlImGuiBegin();
        ImGui::Begin("Test");
        ImGui::Button("button");
        ImGui::Text("Delta time : %f", DeltaTime());
        ImGui::Text(testProjectile.GetPos().ToString().c_str());
        ImGui::End();

        rlImGuiEnd();
        /* ========================  */

        EndDrawing();
    }
}
