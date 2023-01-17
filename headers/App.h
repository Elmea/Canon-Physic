#pragma once


#include "RenderManager.h"
#include "raylib.h"
#include <imgui.h>
#include "rlImGui.h"

class App
{
private :
	int m_width;
	int m_height;
	Renderer::RendererManager m_objectManager;

public :
	~App();

	void Init(int width, int height);
	void Update();
	
};