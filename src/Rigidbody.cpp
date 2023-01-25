#include <iostream>

#include "Rigidbody.h"
#include "SimulationData.h"


namespace Core
{
	/// <summary>
	/// Simulation des forces appliqué au corps par la méthode d'Euler.
	/// </summary>
	/// <param name="deltaTime"> : Temps entre deux frame</param>
	void Rigidbody::Update(double deltaTime)
	{
		for (Float2 force : m_AccelerationForces)
		{
			m_velocity += force * deltaTime;
		}

		for (Float2 force : m_speedForces)
		{
			m_velocity += force;
		}

		m_pos += m_velocity * deltaTime;
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

	void Rigidbody::SetStartPos(Float2 position)
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

	void Rigidbody::DrawForces()
	{
		Float2 raylibPos = Data::WorldSetting::GetRaylibPos(m_pos * Data::WorldSetting::pixelPerMeter);
		for (Float2 force : m_AccelerationForces)
		{
			Float2 raylibPosForce{ force.x * 10 , -force.y * 10 };
			DrawLine(raylibPos.x, raylibPos.y, raylibPos.x + raylibPosForce.x, raylibPos.y + raylibPosForce.y, ORANGE);
		}

		for (Float2 force : m_speedForces)
		{
			Float2 raylibPosForce{ force.x * 1000 , -force.y * 1000 };
			DrawLine(raylibPos.x, raylibPos.y, raylibPos.x + raylibPosForce.x, raylibPos.y + raylibPosForce.y, BLUE);
		}

		Float2 raylibPosForce{ m_velocity.x * 15 , -m_velocity.y * 15 };
		DrawLine(raylibPos.x, raylibPos.y, raylibPos.x + raylibPosForce.x, raylibPos.y + raylibPosForce.y, RED);
	}

	void Rigidbody::ClearForces()
	{
		m_AccelerationForces.clear();
		m_speedForces.clear();
	}
}