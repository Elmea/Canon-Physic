#include "Canon.h"
#include "raylib.h"
#include "Projectile.h"

namespace Core
{
	Canon::Canon(Renderer::RendererManager* manager) :m_renderManager(manager)
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");
	}
	Canon::Canon()
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");
	}

	Canon::~Canon()
	{
	}

	void Canon::ShowPredictionShoot()
	{
	}

	void Canon::Shoot(double radius, double weight)
	{
		Projectile* pProjectile = new Projectile(position, radius, weight, power, angle);
		m_renderManager->AddObject(pProjectile);
	}

	void Canon::Update(double deltaTime)
	{
	}

	void Canon::Draw()
	{
		int frameWidth = m_canonTex.width;
		int frameHeight = m_canonTex.height;

		// Source rectangle (part of the texture to use for drawing)
		Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
		// Destination rectangle (screen rectangle where drawing part of texture)
		Rectangle destRec = { 200, position.y, frameWidth , frameHeight };

		// Origin of the texture (rotation/scale point), it's relative to destination rectangle size
		Vector2 origin = { (float)frameWidth / 2, (float)frameHeight / 2 };

		/* Draw cannon and it's base */
		DrawTexturePro(m_canonTex, sourceRec, destRec, origin, angle, WHITE);
		DrawTexture(m_cannonBaseTex, destRec.x - frameWidth / 2 + 25, destRec.y, WHITE);

		/* Draw support of the cannon */
		DrawRectangle(destRec.x - frameWidth / 2, position.y + m_cannonBaseTex.height, frameWidth, 1080, BLACK);
	}
}