#include "Canon.h"
#include "raylib.h"
#include "Projectile.h"
#include "SimulationData.h"
#include "UI.h"

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
			valueChanged = true;
		}
		else
		{
			ResetPosition();
		}
	}

	void Canon::ResetPosition()
	{
		rigidbody.StopVelocity();
		rigidbody.ClearForces();
		if (position != initPos)
		{
			position = initPos;
			valueChanged = true;
		}
		
	}

	Canon::Canon()
	{
		m_activeShootPrediction = true;
		m_canonTex = LoadTexture("assets/Cannon.png");
		m_cannonBaseTex = LoadTexture("assets/Cannonbase.png");

		size.x  = m_canonTex.width;
		size.y  = m_canonTex.height;
		rigidbody.SetStartPos(position);
		initPos = position;

	}

	Canon::~Canon()
	{
	}

	/// <summary>
	/// Calcul de la vitesse du canon apres le tir en appliquant la conversion de quantité de mouvement.
	/// Retourne le coefficient de friction qui sera la vitesse initiale de la balle lors du tir.
	/// </summary>
	/// <returns></returns>
	Float2 Canon::ResolveCollision(double p_weight)
	{
		/* Calcul du recul du canon et ajout de la force */
		Float2 speedCanon = ((speedZero * p_weight) / weight) * -1;
		speedCanon.y = 0;
		rigidbody.AddForce(speedCanon, ForceType::FT_SPEED);

		/* Calcul du coefficient de friction */
		float weight = Data::WorldSetting::GRAVITY * p_weight;
		double RadAngle = DEG2RAD * angle;

		/* Valeur brut du a l'enoncé */
		double deccelerationFriction = -2;
		double coefFriction = sqrt(2.f * deccelerationFriction * canonLength + (speedZero.Magnitude() * speedZero.Magnitude()));
		return { coefFriction * cos(RadAngle) , coefFriction * sin(-RadAngle) };
	}

	/// <summary>
	/// Precalcul des valeurs de temps de vol, distance max en hauteur et longueur.
	/// Dessine une courbe en fonction de ces valeurs.
	/// Ne prend pas en compte la resistance de l'air ni la collision et les frottements avec le canon.
	/// </summary>
	/// <returns></returns>
	void Canon::ShowPredictionShoot()
	{
		if (valueChanged)
		{
			timeInCanon = canonLength / speedZero.Magnitude();
			valueChanged = false;

			/* Setup values */
			double RadAngle = DEG2RAD * angle;
			speedZero = { power * cos(RadAngle) , power * sin(-RadAngle) };
			
			/* Set the values to make equation more readable*/
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
		Float2 raylibSPos = Data::WorldSetting::GetRaylibPos(position);
		Float2 raylibEPos = Data::WorldSetting::GetRaylibPos(posImpact * Data::WorldSetting::pixelPerMeter);
		Float2 raylibSZero = Data::WorldSetting::GetRaylibSpeed(speedZero);
		Float2 raylibSEnd = Data::WorldSetting::GetRaylibSpeed(speedImpact);

		DrawCircle(raylibEPos.x, raylibEPos.y, 15, RED);
		Float2 controlPoint = Float2::LineIntersection(raylibSPos, raylibSZero, raylibEPos, raylibSEnd);
		DrawLineBezierQuad(raylibSPos, raylibEPos, controlPoint, 2, LIME);
	}

	void Canon::Shoot(double radius, double weight)
	{
		Float2 newSpeed;
		if (isCollisionActive)
		{
			rigidbody.SetStartPos(position);
			newSpeed = ResolveCollision(weight);
		}
		else 
		{
			newSpeed = speedZero;
		}

		Float2 newPos {position.x + cos(-angle * DEG2RAD) * size.x/2, position.y + sin(-angle * DEG2RAD) * size.x / 2 };

		Projectile* pProjectile = new Projectile(newPos, radius, weight, newSpeed, m_renderManager);
		m_renderManager->AddObject(pProjectile);
	}

	void Canon::Update(double deltaTime)
	{
		if (UI::drawShootPrediction) ShowPredictionShoot();
		rigidbody.Update(deltaTime);
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
		DrawRectangle(0, raylibPos.y + m_cannonBaseTex.height, initPos.x + (float)size.x/2, 1080, { 80, 80, 80 , 250 });
	}
}