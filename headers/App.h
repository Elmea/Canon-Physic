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

	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrame;
	double m_deltaTime;
	void CalcDeltaTime();

public :
	~App();

	void Init(int width, int height);
	void Update();
	double DeltaTime();
};