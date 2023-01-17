#include "App.h"
#include "Canon.h" 

App::~App()
{
    rlImGuiShutdown();
    CloseWindow();       
}

void App::Init(int width, int height)
{
	m_height = height;
	m_width = width;

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    rlImGuiSetup(true);

    SetTargetFPS(60);

    Core::Canon* canon = new Core::Canon();

    m_objectManager.AddObject(canon);

}

void App::Update()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        /* Raylib Draws */
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        m_objectManager.DrawObject();
        /* ========================  */
        /* ImGui */
        rlImGuiBegin();
        ImGui::Begin("Test");
        ImGui::Button("button");
        ImGui::End();

        rlImGuiEnd();
        /* ========================  */

        EndDrawing();
    }
}
