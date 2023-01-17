#include "App.h"
#include "Projectile.h"
#include "Maths.h"
#include "Canon.h" 

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

    InitWindow(m_width, m_height, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    m_interface.Init();

    canon = new Core::Canon();;
    m_objectManager.AddObject(canon);
}

void App::Update()
{
    CalcDeltaTime();

    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        CalcDeltaTime();

       

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
