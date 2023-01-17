#pragma once
#include <imgui.h>
#include "rlImGui.h"

namespace Core
{
	class Canon;
}

struct WorldParam
{
	double gravity = 9.81;
	double airResistance;
};

class UI
{
private :
	bool SliderDouble(const char* text, double* v, double min, double max);
	bool SliderDoubleN(const char* text, int nbValues , double* v, double min, double max);
	bool ClickInRectangle(Vector2 mousePos, Rectangle rec);

	double weight = 10;
	double sizeP = 5;

public :
	void Init();
	~UI();

	/* Context */
	void NewFrame();
	void EndFrame();

	void NewWindow(const char* windowName);
	void CloseWindow();

	/* ImGui */
	void ProjectileParameters(/* TODO Get the projectile class here */);
	void CanonParameters(Core::Canon* canon);
	void WorldParameters(WorldParam& world);

	void MoveCannon();
};