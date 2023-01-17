#include <raylib.h>

#include "Projectile.h"
#include "SimulationData.h"

namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight) : m_pos(position), m_radius(radius), m_weight(weight), 
																			m_frontSurface(PI * ((radius * radius)/16.0))
	{
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::Update(double deltaTime)
	{
		if (m_pos.y >= 1080)
		{
			m_pos.y = 1080;
			return;
		}

		AddForce(Float2{ 0, 9.81 }, deltaTime);
		AddForce(CalcTrail(), deltaTime);

		m_lifeTime += deltaTime;
		Float2 vel = m_velocity;
		m_pos = m_pos + vel;
	}

	void Projectile::Draw()
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, PURPLE);
	}

	void Projectile::AddForce(Float2 force, double deltaTime)
	{
		Float2 f = force * deltaTime;
		m_velocity = m_velocity + f;
	}

	Float2 Projectile::CalcTrail()
	{
		double v = m_velocity.Magnitude();
		double magnitude = 0.5 * Data::airResistance * m_frontSurface * CalcTrailCoefficient() * v * v;

		int xSign = m_velocity.x >= 0 ? -1 : 1;
		int ySign = m_velocity.y >= 0 ? -1 : 1;

		double theta = acos(m_velocity.y);

		return { magnitude * cos(theta) * xSign, magnitude * sin(theta) * ySign };
	}

	double Projectile::CalcTrailCoefficient()
	{
		return 24.0 / ((Data::airResistance * m_velocity.Magnitude() * m_radius * 2) / Data::airViscosity);
	}
}