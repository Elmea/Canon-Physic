#include "Canon.h"
#include "raylib.h"

namespace Core
{
	
	Canon::Canon()
	{
		m_activeShootPrediction = true;
		cannon = LoadTexture("assets/Cannon.png");
		cannonBase = LoadTexture("assets/Cannonbase.png");
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
		//DrawCircle(position.x, position.y, 10, RED);
		int frameWidth = cannon.width;
		int frameHeight = cannon.height;

		// Source rectangle (part of the texture to use for drawing)
		Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
		// Destination rectangle (screen rectangle where drawing part of texture)
		Rectangle destRec = { 200, position.y, frameWidth , frameHeight };

		// Origin of the texture (rotation/scale point), it's relative to destination rectangle size
		Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

		/* Draw cannon and it's base */
		DrawTexturePro(cannon, sourceRec, destRec, origin, angle, WHITE);
		DrawTexture(cannonBase, destRec.x - frameWidth / 2 + 25, destRec.y, WHITE);

		/* Draw support of the cannon */
		DrawRectangle(destRec.x - frameWidth / 2, position.y + cannonBase.height, frameWidth, 1080, BLACK);
	}
}