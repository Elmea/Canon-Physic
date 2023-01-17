#pragma once
#include "Maths.h"
#include "RenderManager.h"

namespace Core
{
	class Projectile : public Renderer::RenderObject
	{
	private:
		Float2 m_pos{ 0, 0};
		double m_weight;
		double m_radius;
		double m_lifeTime = 0;

		const double m_frontSurface;

		Float2 m_velocity{ 0, 0 };

		Float2 CalcTrail();
		double CalcTrailCoefficient();

	public:
		Projectile(Float2 position, double radius, double weight, double power, double angle);
		~Projectile();

		void Update(double deltaTime);
		void Draw();
		void AddForce(Float2 force, double deltaTime);
		Float2 GetPos() { return m_pos; };
	};
}