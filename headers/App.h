#pragma once


#include "RenderManager.h"
#include "raylib.h"
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
public :
	~App();

	void Init(int width, int height);
	void Update();
	
};