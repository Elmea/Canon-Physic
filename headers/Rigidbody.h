#pragma once
#include "Maths.h"
#include <vector>


namespace Core
{
	enum class ForceType
	{
		FT_SPEED,
		FT_ACCELERATION
	};

	class Rigidbody
	{
	private:
		Float2 m_pos{ 0, 0 };
		Float2 m_velocity{ 0, 0 };

		std::vector<Float2> m_speedForces;
		std::vector<Float2> m_AccelerationForces;

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