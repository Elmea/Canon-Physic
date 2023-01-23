#pragma once
#include <imgui.h>
#include "rlImGui.h"
#include "RenderManager.h"
#include "Maths.h"
#include "SimulationData.h"
#include "map"

namespace Core
{
	class Canon;
}

struct ProjectileParameters
{
	Float2 velocity;
	Float2 position;
	double currentLifeTime;
	bool shouldDie = true;
	bool controlPos = false;

	bool operator==(const ProjectileParameters& o) {
		return velocity == o.velocity && position == o.position && currentLifeTime == o.currentLifeTime;
	}

	void operator=(const ProjectileParameters& o) {
		velocity = o.velocity;
		position = o.position;
		currentLifeTime = o.currentLifeTime;
	}
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
	/* Last projectile values */
	static double length;
	static double height;
	static double timeAir;

	static std::map<int , ProjectileParameters> projectileParameters;

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
	void CurrentProjectileParam();

	void Shoot(Core::Canon* canon, Renderer::RendererManager& objectManager);

	void ShowValuesBeforeShoot(Core::Canon* canon);
	void MoveCannon(Core::Canon* canon);
	void ShowValuesAfterShoot();
};