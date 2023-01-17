#include <raylib.h>
#include "Projectile.h"
#include "SimulationData.h"
#include "App.h"

namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight,double power, double angle) : m_pos(position), m_radius(radius), m_weight(weight)
	{
		angle = DEG2RAD * angle;
		AddForce(Float2{ power * cos(angle), power * sin(angle) }, App::m_deltaTime);
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