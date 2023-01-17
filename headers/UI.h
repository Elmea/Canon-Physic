#pragma once
#include <imgui.h>
#include "rlImGui.h"

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
	double angle = 0; /*degree here */
	int height = 1000;

	Texture2D cannon;
	Texture2D cannonBase;

	Rectangle destRec;
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
	void CanonParameters(/*TODO Get the canon class here */);
	void WorldParameters(WorldParam& world);

	/* Raylib */
	void MoveCannon();
	void DrawCanon();
};