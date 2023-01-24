#pragma once
#include "Maths.h"
#include <vector>


namespace Core
{
	enum class ForceType
	{
		FT_SPEED,
		FT_ACCELERATION,
		FT_INSTANT
	};

	class Rigidbody
	{
	private:
		Float2 m_startPos{ 0, 0 };
		Float2 m_pos{ 0, 0 };
		Float2 m_velocity{ 0, 0 };
		Float2 m_speed{ 0, 0 };

		std::vector<Float2> m_speedForces;
		std::vector<Float2> m_AccelerationForces;
		std::vector<Float2> m_InstantForces;

		// Temp 
		Float2 gravityVal ;

	public:

		void Update(double deltaTime, double lifeTime);
		void DrawForces();
		void ClearForces();
		void AddForce(Float2 force, ForceType type);
		void SetStartPos(Float2 position);

		Float2 GetPos();
		Float2 GetVelocity();
	};
}