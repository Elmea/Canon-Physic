#include "Canon.h"
#include "raylib.h"

namespace Core
{
	
	Canon::Canon()
	{
		m_activeShootPrediction = true;
		cannon = LoadTexture("assets/Cannon.png");
		cannonBase = LoadTexture("assets/Cannonbase.png");

		size.x  = cannon.width;
		size.y = cannon.height;
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


		// Source rectangle (part of the texture to use for drawing)
		Rectangle sourceRec = { 0.0f, 0.0f, (float)size.x, (float)size.y };
		// Destination rectangle (screen rectangle where drawing part of texture)
		Rectangle destRec = { 200, position.y, size.x , size.y };

		// Origin of the texture (rotation/scale point), it's relative to destination rectangle size
		Vector2 origin = { (float)size.x / 2, (float)size.y / 2 };

		/* Draw cannon and it's base */
		DrawTexturePro(cannon, sourceRec, destRec, origin, angle, WHITE);
		DrawTexture(cannonBase, destRec.x - size.x / 2 + 25, destRec.y, WHITE);

		/* Draw support of the cannon */
		DrawRectangle(destRec.x - size.x / 2, position.y + cannonBase.height, size.x, 1080, BLACK);
	}
}