#include <raylib.h>

#include "Projectile.h"
#include "SimulationData.h"


namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight) : m_pos(position), m_radius(radius), m_weight(weight)
	{
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::Update(double deltaTime)
	{
		AddForce(Float2{ 0, 9.81 }, deltaTime*2);

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

}