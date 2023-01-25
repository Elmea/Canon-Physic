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
		rigidbody.SetStartPos(position);
		initPos = position;

	}

	void Canon::ResolveFriction()
	{
		if (rigidbody.GetVelocity().x < 0)
		{
			rigidbody.AddForce(Float2{ 0.03, 0 }, ForceType::FT_SPEED);
		}
		else
		{
			rigidbody.StopVelocity();
			rigidbody.ClearForces();
			position = initPos;
		}
	}

	Canon::Canon()
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");

		size.x  = m_canonTex.width;
		size.y  = m_canonTex.height;
		initPos = position;

	}

	Canon::~Canon()
	{
	}

	void Canon::ResolveCollision(double p_weight)
	{
		Float2 speedCanon =( (speedZero * p_weight) / weight ) * -1;
		speedCanon.y = 0;
		rigidbody.AddForce(speedCanon, ForceType::FT_SPEED);
	}

	void Canon::ShowPredictionShoot()
	{
		if (valueChanged)
		{
			valueChanged = false;
			/* Setup values */
			double RadAngle = DEG2RAD * angle;
			speedZero = { power * cos(RadAngle) , power * sin(-RadAngle) };
			double ySqr = speedZero.y * speedZero.y;
			double realHeight = position.y / Data::WorldSetting::pixelPerMeter;

			double delta = sqrt((ySqr)+2 * -Data::WorldSetting::GRAVITY * realHeight);

			/* Calculation */
			timeInAir = (speedZero.y + delta) / -Data::WorldSetting::GRAVITY;
			maxW = timeInAir * speedZero.x;
			maxH = (ySqr / (2.0 * (-Data::WorldSetting::GRAVITY))) + realHeight;

			posImpact = (Float2{ 0,(Data::WorldSetting::GRAVITY / 2.0) * (timeInAir * timeInAir) } + speedZero * timeInAir) + position / Data::WorldSetting::pixelPerMeter;
			Float2 acc = { 0, Data::WorldSetting::GRAVITY };
			speedImpact = acc * timeInAir + speedZero;
		}
		
		DrawCurvePrediction();
	}

	void Canon::DrawCurvePrediction()
	{
		Float2 raylibSPos  = Data::WorldSetting::GetRaylibPos(position);
		Float2 raylibEPos  = Data::WorldSetting::GetRaylibPos(posImpact * Data::WorldSetting::pixelPerMeter);
		Float2 raylibSZero = Data::WorldSetting::GetRaylibSpeed(speedZero);
		Float2 raylibSEnd  = Data::WorldSetting::GetRaylibSpeed(speedImpact);

		DrawCircle(raylibEPos.x, raylibEPos.y, 15, RED);
		Float2 controlPoint = Float2::LineIntersection(raylibSPos, raylibSZero, raylibEPos, raylibSEnd);
		DrawLineBezierQuad(raylibSPos, raylibEPos, controlPoint, 2, LIME);
	}

	void Canon::Shoot(double radius, double weight)
	{
		rigidbody.SetStartPos(position);
		ResolveCollision(weight);
		Projectile* pProjectile = new Projectile(position, radius, weight, speedZero, m_renderManager, m_nbProjectileCreated);
		m_renderManager->AddObject(pProjectile);
		m_nbProjectileCreated++;
	}

	void Canon::Update(double deltaTime)
	{
		ShowPredictionShoot();
		rigidbody.Update(deltaTime, 1);
		position = rigidbody.GetPos();
		ResolveFriction();
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