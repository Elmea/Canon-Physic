#include "Canon.h"
#include "raylib.h"
#include "Projectile.h"
#include "SimulationData.h"

namespace Core
{
	Canon::Canon(Renderer::RendererManager* manager) :m_renderManager(manager)
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");
		
		size.x = m_canonTex.width;
		size.y = m_canonTex.height;
	}
	Canon::Canon()
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");

		size.x  = m_canonTex.width;
		size.y  = m_canonTex.height;
	}

	Canon::~Canon()
	{
	}

	void Canon::ShowPredictionShoot()
	{

	}

	void Canon::Shoot(double radius, double weight)
	{
		Projectile* pProjectile = new Projectile(position, radius, weight, power, angle, m_renderManager, m_nbProjectileCreated);
		m_renderManager->AddObject(pProjectile);
		m_nbProjectileCreated++;
	}

	void Canon::Update(double deltaTime)
	{
	}

	void Canon::Draw()
	{
		Float2 raylibPos = Data::WorldSetting::GetRaylibPos(position);

		// Source rectangle (part of the texture to use for drawing)
		Rectangle sourceRec = { 0.0f, 0.0f, (float)size.x, (float)size.y };
		// Destination rectangle (screen rectangle where drawing part of texture)
		Rectangle destRec = { raylibPos.x, raylibPos.y, size.x , size.y };

		// Origin of the texture (rotation/scale point), it's relative to destination rectangle size
		Vector2 origin = { (float)size.x / 2, (float)size.y / 2 };

		/* Draw cannon and it's base */
		DrawTexturePro(m_canonTex, sourceRec, destRec, origin, angle, WHITE);
		DrawTexture(m_cannonBaseTex, destRec.x - (float)size.x / 2 + 25, destRec.y, WHITE);

		/* Draw support of the cannon */
		DrawRectangle(destRec.x - (float)size.x / 2, raylibPos.y + m_cannonBaseTex.height, (float)size.x, 1080, BLACK);
	}
}