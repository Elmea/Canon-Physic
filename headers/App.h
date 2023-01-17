#pragma once

#include "raylib.h"
#include "Ui.h"



class App
{
private :
	int m_width;
	int m_height;

	UI m_interface;
	WorldParam worldSettings;

public :
	~App();

	void Init(int width, int height);
	void Update();
	
};