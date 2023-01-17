#include "Canon.h"
#include "raylib.h"

namespace Core
{
	
	Canon::Canon()
	{
	}

	Canon::~Canon()
	{
	}

	void Canon::ShowPredictionShoot()
	{
	}

	void Canon::Shoot()
	{
		// Create Projectile 
	}

	void Canon::Update()
	{
	}

	void Canon::Draw()
	{
		DrawCircle(position.x, position.y, 10, RED);
	}
}