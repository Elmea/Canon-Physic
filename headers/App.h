#pragma once


#include "raylib.h"
#include <imgui.h>
#include "rlImGui.h"
#include <chrono>

class App
{
private :
	int m_width;
	int m_height;

	int screenWidth = 1920;
	int screenHeight = 1080;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrame;
	double m_deltaTime;
	void CalcDeltaTime();

public :
	~App();

	void Init(int width, int height);
	void Update();
	double DeltaTime();
};