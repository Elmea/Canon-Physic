#pragma once


#include "RenderManager.h"
#include "raylib.h"
#include <imgui.h>
#include "rlImGui.h"
#include <chrono>
#include "Ui.h"


class App
{
private :
	int m_width;
	int m_height;
	Renderer::RendererManager m_objectManager;

	UI m_interface;
	WorldParam worldSettings;
	Core::Canon* canon;

	Camera2D camera = { 0 };

	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrame;
	void CalcDeltaTime();

	void Update();
	void Draw();

public :
	~App();
	static double m_deltaTime ;

	void Init(int width, int height);
	void Run();
	double DeltaTime();
};