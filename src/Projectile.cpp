#include <raylib.h>
#include "Projectile.h"
#include "SimulationData.h"
#include "App.h"
#include <iostream>
#include "Ui.h"

namespace Core
{
	double Projectile::lifeTimeAfterCollision = 2.5f;

	Projectile::Projectile(Float2 position, double radius, double weight, const Float2& projSpeedZero, Renderer::RendererManager* _manager, int _id) : m_pos(position), m_radius(radius), m_weight(weight),
		m_frontSurface(PI* ((radius* radius) / 16.0)), m_manager(_manager), m_id(_id)
	{
		m_startPos = position;
		rigidbody.SetStartPos(position / Data::WorldSetting::pixelPerMeter);
		m_pos = position / Data::WorldSetting::pixelPerMeter;
		m_maxHeight = position.y / Data::WorldSetting::pixelPerMeter;
		m_vInit = projSpeedZero;
		AddForce(m_vInit, Core::ForceType::FT_SPEED);
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::Update(double deltaTime)
	{
		UI::projectileParameters[m_id].currentLifeTime = m_lifeTime - m_inAirTime;

		if (IsOnFloor())
		{
			ImpactReaction(deltaTime);
			return;
		}

		
		
		Move(deltaTime);

		if (m_pos.y >= m_maxHeight)
			m_maxHeight = m_pos.y;

		m_lifeTime += deltaTime;

		UI::projectileParameters[m_id].position = m_pos;
		UI::projectileParameters[m_id].velocity = m_velocity;
	}

	void Projectile::Draw()
	{
		Float2 raylibPos = Data::WorldSetting::GetRaylibPos(m_pos * Data::WorldSetting::pixelPerMeter);
		DrawCircle(raylibPos.x, raylibPos.y, m_radius, PURPLE);
	}

	void Projectile::AddForce(Float2 force, Core::ForceType type)
	{
		rigidbody.AddForce(force, type);
	}

	Float2 Projectile::CalcTrail()
	{
		double v = m_velocity.Magnitude();
		if (Data::WorldSetting::airResistance == 0 || v == 0)
			return { 0,0 };

		double magnitude = (0.5 * Data::WorldSetting::airResistance * Data::WorldSetting::airResistance * m_frontSurface * CalcTrailCoefficient() * v * v)/ 100;

		double theta = atan2(m_velocity.y, m_velocity.x);

		return { -(magnitude - (m_weight/1000.0)) * cos(theta), -(magnitude - (m_weight / 1000.0)) * sin(theta) };
	}

	double Projectile::CalcTrailCoefficient()
	{
		return (24.0 / ((Data::WorldSetting::airResistance * m_velocity.Magnitude() * m_radius * 2) / Data::WorldSetting::airViscosity * 10) / m_weight);
	}

	void Projectile::DrawProjectilePath()
	{
		Float2 raylibSPos = Data::WorldSetting::GetRaylibPos(m_startPos);
		Float2 raylibEPos = Data::WorldSetting::GetRaylibPos(m_endPos * Data::WorldSetting::pixelPerMeter);
		Float2 raylibSZero = Data::WorldSetting::GetRaylibSpeed(m_vInit);
		Float2 raylibSEnd = Data::WorldSetting::GetRaylibSpeed(m_vFinal);

		Float2 controlPoint = Float2::LineIntersection(raylibSPos, raylibSZero, raylibEPos, raylibSEnd);
		DrawLineBezierQuad(raylibSPos, raylibEPos, controlPoint, 2, SKYBLUE);
	}

	void Projectile::TouchGround(double deltaTime)
	{
		m_inAirTime = m_lifeTime;
		m_hasHitGround = true;
		m_endPos = m_pos;
		m_vFinal = m_velocity;

		UI::length = m_endPos.x - (m_startPos.x / Data::WorldSetting::pixelPerMeter) - m_vInit.x * deltaTime;
		UI::height = m_maxHeight;
		UI::timeAir = m_inAirTime;
	}
	void Projectile::Move(double deltaTime)
	{
	
		if (!UI::projectileParameters[m_id].controlPos)
		{
			m_velocity = rigidbody.GetVelocity();

			rigidbody.AddForce(CalcTrail(), Core::ForceType::FT_SPEED);
			rigidbody.AddForce(Float2{ 0, Data::WorldSetting::GRAVITY }, Core::ForceType::FT_ACCELERATION);

			rigidbody.Update(deltaTime, m_lifeTime);

			m_pos = rigidbody.GetPos();
		}
		else
		{
			m_pos = UI::projectileParameters[m_id].position;
		}
	}
	void Projectile::ImpactReaction(double deltaTime)
	{
		if (!m_hasHitGround)
			TouchGround(deltaTime);

		if (UI::projectileParameters[m_id].shouldDie && m_lifeTime - m_inAirTime > lifeTimeAfterCollision)
		{
			UI::projectileParameters.erase(m_id);
			m_manager->ShouldRemove(this);
			return;
		}

		m_lifeTime += deltaTime;
		m_pos.y = 0;
		return;
	}
	bool Projectile::IsOnFloor()
	{
		return m_pos.y <= 0;
	}
}