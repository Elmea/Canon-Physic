#include "Rigidbody.h"

using namespace Core;

void Rigidbody::Update(double deltaTime)
{
	double temp = 0.5 * deltaTime * deltaTime;
	for (Float2 force : m_AccelerationForces)
	{
		m_velocity = m_velocity + force * deltaTime; 
		m_pos = m_pos + force * temp;
	}

	for (Float2 force : m_speedForces)
	{
		m_velocity = m_velocity + force;
		m_pos = m_pos + force * deltaTime;
	}

	m_AccelerationForces.clear();
	m_speedForces.clear();
}

void Rigidbody::AddForce(Float2 force, ForceType type)
{
	switch (type)
	{
	case ForceType::FT_SPEED:
		m_speedForces.push_back(force);
		break;
	case ForceType::FT_ACCELERATION:
		m_AccelerationForces.push_back(force);
		break;
	default:
		break;
	}
}

void Rigidbody::SetPos(Float2 position)
{
	m_pos = position;
}

Float2 Rigidbody::GetPos()
{
	return m_pos;
}

Float2 Rigidbody::GetVelocity()
{
	return m_velocity;
}