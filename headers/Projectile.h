#pragma once
#include "Maths.h"

namespace Core
{
	class Projectile : public Renderer::RenderObject
	{
	private:
		Float2 m_pos{ 0, 0};
		double m_weight;
		double m_radius;
		double m_lifeTime = 0;

		Float2 m_velocity{ 0, 0 };

	public:
		Projectile(Float2 position, double radius, double weight);
		~Projectile();

		void Update(double deltaTime);
		void Draw();
		void AddForce(Float2 force, double deltaTime);
		Float2 GetPos() { return m_pos; };
	};
}