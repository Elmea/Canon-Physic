#pragma once
#include <imgui.h>
#include "rlImGui.h"
#include "RenderManager.h"
#include "Maths.h"
#include "SimulationData.h"

namespace Core
{
	class Canon;
}

struct WorldParam
{
	double airResistance = 0.1;
	double airViscosity = 15.6;
	double GRAVITY = 9.80665f;
	double pixelPerMeter = 10;
};

class UI
{
private :
	bool SliderDouble(const char* text, double* v, double min, double max);
	bool SliderDoubleN(const char* text, int nbValues , double* v, double min, double max);
	bool ClickInRectangle(Float2 mousePos, Rectangle rec);

	double weight = 10;
	double sizeP = 5;
	double speedDrag = 1;
	Float2 lastMousePos;

	double maxHeightCanon = 1000;
	double minHeightCanon = 100;
	
	double maxAngleCanon = 75;
	double minAngleCanon = -90;
public :
	void Init();
	~UI();

	/* Context */
	void NewFrame();
	void EndFrame();

	void NewWindow(const char* windowName);
	void CloseWindow();
	void ShowFPS() { DrawFPS(10, 10); };

	/* ImGui */
	void ProjectileParameters();
	void CanonParameters(Core::Canon* canon);
	void WorldParameters();
	void Shoot(Core::Canon* canon, Renderer::RendererManager& objectManager);

	void MoveCannon(Core::Canon* canon);
};