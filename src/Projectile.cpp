#include <raylib.h>
#include "Projectile.h"
#include "SimulationData.h"
#include "App.h"
#include <iostream>

namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight, double power, double angle) : m_pos(position), m_radius(radius), m_weight(weight),
																			m_frontSurface(PI * ((radius * radius)/16.0))
	{
		m_startPos = position;
		angle = DEG2RAD * angle;
		m_vInit = Float2{ power * cos(angle), power * sin(angle) };
		AddForce(m_vInit, App::m_deltaTime, true) ;
	}

	Projectile::~Projectile()
	{
	}
	
	void Projectile::Update(double deltaTime)
	{
		if (m_pos.y >= 1080)
		{
			if (!hasHitGround)
			{
				m_inAirTime = m_lifeTime;
				hasHitGround = true;
				m_endPos = m_pos;
				m_vFinal = m_velocity;

				UI::length  = m_endPos.x - m_startPos.x;
				UI::height  = m_endPos.y - m_startPos.y;
				UI::timeAir = m_inAirTime;
			}
			m_pos.y = 1080;
			DrawProjectilePath();
			return;
		}

		AddForce(CalcTrail(), deltaTime);
		AddForce(Float2{ 0, Data::WorldSetting::GRAVITY }, deltaTime);

		m_lifeTime += deltaTime;
		Float2 vel = m_velocity ;
		Float2 vel2 = Float2{ m_velocity.x * 60 , m_velocity.y * 60};
		m_pos = m_pos + vel;
	}

	void Projectile::Draw()
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, PURPLE);
	}

	void Projectile::AddForce(Float2 force, double deltaTime, bool debug)
	{
		Float2 f = force * deltaTime;
		m_velocity = m_velocity + f;
	}

	Float2 Projectile::CalcTrail()
	{
		double v = m_velocity.Magnitude();
		double magnitude = (0.5 * Data::WorldSetting::airResistance * Data::WorldSetting::airResistance * m_frontSurface * CalcTrailCoefficient() * v * v)/ 100;

		double theta = atan2(m_velocity.y, m_velocity.x);

		return { -(magnitude - (m_weight/1000.0)) * cos(theta), -(magnitude - (m_weight / 1000.0)) * sin(theta) };
	}

	double Projectile::CalcTrailCoefficient()
	{
		return 24.0 / ((Data::WorldSetting::airResistance * m_velocity.Magnitude() * m_radius * 2) / Data::WorldSetting::airViscosity * 10);
	}

	void Projectile::DrawProjectilePath()
	{
		Float2 controlPoint = Float2::LineIntersection(m_startPos, m_vInit, m_endPos, m_vFinal);
		DrawLineBezierQuad(m_startPos, m_endPos, controlPoint, 2, SKYBLUE);
	}
}