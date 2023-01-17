#pragma once
#include "Maths.h"
#include "RenderManager.h"
namespace Core
{
	class Projectile :RenderObject
	{
	private:
		Float2 m_position;
		double m_weight;
		double m_radius;

	public:
		Projectile(double radius, double weight);
		~Projectile();

		void Update();
		void Draw();


	};

}