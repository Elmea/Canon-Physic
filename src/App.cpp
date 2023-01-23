#include "App.h"
#include "Projectile.h"
#include "Maths.h"
#include "Canon.h" 


double App::m_deltaTime = 0.0;

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
  
    m_deltaTime = GetFrameTime();
    m_lastFrame = now;
}



void App::Init(int width , int height)
{
	m_height = height;
	m_width = width;

    InitWindow(m_width, m_height, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    m_interface.Init();
    CalcDeltaTime();

    canon = new Core::Canon{ &m_objectManager };
    m_objectManager.AddObject(canon);
}

void App::Update()
{
    CalcDeltaTime();
    m_objectManager.UpdateObject(m_deltaTime);
}

void App::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_objectManager.DrawObject();

    m_interface.Draw(canon, m_objectManager);

    EndDrawing();
}

void App::Run()
{

    while (!WindowShouldClose())   
    {
        Update();
        Draw();
    }
}
