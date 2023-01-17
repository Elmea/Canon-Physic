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
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    m_interface.Init();

    canon = new Core::Canon();;
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
        m_objectManager.DrawObject();

        /* ========================  */
        /* ImGui */
        m_interface.NewFrame();

        m_interface.MoveCannon(canon);
        m_interface.NewWindow("MainWindow");

        m_interface.ProjectileParameters();
        m_interface.CanonParameters(canon);
        m_interface.WorldParameters(worldSettings);

        m_interface.CloseWindow();

        m_interface.NewWindow("Game");
        m_interface.Shoot(canon , m_objectManager);
        m_interface.CloseWindow();

        m_interface.EndFrame();
        /* ========================  */

        EndDrawing();
    }
}
