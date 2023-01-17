#include "App.h"

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
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    m_interface.Init();
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
        DrawText("Congrats! You created your first window!", 500, 500, 20, LIGHTGRAY);
        m_interface.DrawCanon();

        /* ========================  */
        /* ImGui */
        m_interface.NewFrame();

        m_interface.NewWindow("MainWindow");

        m_interface.ProjectileParameters();
        m_interface.CanonParameters();
        m_interface.WorldParameters(worldSettings);

        m_interface.CloseWindow();

        m_interface.EndFrame();
        /* ========================  */

        EndDrawing();
    }
}
