#include <raylib.h>
#include "Projectile.h"
#include "SimulationData.h"
#include "App.h"
#include <iostream>

namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight, double power, double angle, Renderer::RendererManager* _manager) : m_pos(position), m_radius(radius), m_weight(weight),
																			m_frontSurface(PI * ((radius * radius)/16.0)), m_manager(_manager)
	{
		m_startPos = position;
		rigidbody.SetStartPos(position / Data::WorldSetting::pixelPerMeter);
		m_pos = position / Data::WorldSetting::pixelPerMeter;
		maxHeight = position.y / Data::WorldSetting::pixelPerMeter;
		angle = DEG2RAD * angle;
		m_vInit = Float2{ power * cos(angle), power * sin(-angle) };
		AddForce(m_vInit, Core::ForceType::FT_SPEED);
	}

	Projectile::~Projectile()
	{
	}
	
	void Projectile::Update(double deltaTime)
	{
		if (m_pos.y <= 0)
		{
			if (!hasHitGround)
			{
				m_inAirTime = m_lifeTime ;
				hasHitGround = true;
				m_endPos = m_pos;
				m_vFinal = m_velocity;

				UI::length  = m_endPos.x - ( m_startPos.x / Data::WorldSetting::pixelPerMeter) - m_vInit.x * deltaTime;
				UI::height  = maxHeight;
				UI::timeAir = m_inAirTime;
			}

			if (m_lifeTime - m_inAirTime > 2)
			{
				m_manager->ShouldRemove(this);
				return;
			}

			m_lifeTime += deltaTime;
			m_pos.y = 0;
			DrawProjectilePath();
			return;
		}
		
		m_velocity = rigidbody.GetVelocity();
		
		rigidbody.AddForce(CalcTrail(), Core::ForceType::FT_SPEED);
		rigidbody.AddForce(Float2{ 0, Data::WorldSetting::GRAVITY }, Core::ForceType::FT_ACCELERATION);
		
		rigidbody.Update(deltaTime, m_lifeTime);

		//m_pos = ( Float2{ 0,(Data::WorldSetting::GRAVITY / 2.0 )* (m_lifeTime * m_lifeTime) } + m_vInit * m_lifeTime ) + m_startPos / Data::WorldSetting::pixelPerMeter;
		m_pos = rigidbody.GetPos();

		if (m_pos.y >= maxHeight)
		{
			maxHeight = m_pos.y;
		}
		m_lifeTime += deltaTime;

	}

	void Projectile::Draw()
	{
		Float2 raylibPos = Data::WorldSetting::GetRaylibPos(m_pos * Data::WorldSetting::pixelPerMeter);
		DrawCircle(raylibPos.x, raylibPos.y, m_radius, PURPLE);
		rigidbody.DrawForces();
		rigidbody.ClearForces();
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

		double magnitude = (0.5 * Data::WorldSetting::airResistance * Data::WorldSetting::airResistance * m_frontSurface * CalcTrailCoefficient() * v * v);

		double theta = atan2(m_velocity.y, m_velocity.x);

		return Float2{ -(magnitude - m_weight) * cos(theta), -(magnitude - m_weight) * sin(theta) } / Data::WorldSetting::pixelPerMeter;
	}

	double Projectile::CalcTrailCoefficient()
	{
		return 24.0 / ((Data::WorldSetting::airResistance * m_velocity.Magnitude() * m_radius * 2) / Data::WorldSetting::airViscosity * 10);
	}

	void Projectile::DrawProjectilePath()
	{
		Float2 raylibSPos = Data::WorldSetting::GetRaylibPos(m_startPos );
		Float2 raylibEPos = Data::WorldSetting::GetRaylibPos(m_endPos   * Data::WorldSetting::pixelPerMeter);
		Float2 raylibSZero = Data::WorldSetting::GetRaylibSpeed(m_vInit);
		Float2 raylibSEnd = Data::WorldSetting::GetRaylibSpeed(m_vFinal);

		Float2 controlPoint = Float2::LineIntersection(raylibSPos, raylibSZero, raylibEPos, raylibSEnd);
		DrawLineBezierQuad(raylibSPos, raylibEPos, controlPoint, 2, SKYBLUE);
	}
}