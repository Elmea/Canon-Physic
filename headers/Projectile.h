#pragma once
#include "Maths.h"
#include "RenderManager.h"
namespace Core
{
	class Projectile : public Renderer::RenderObject
	{
	private:
		Float2 m_position = Float2{ 0,0 };
		double m_weight;
		double m_radius;

	public:
		Projectile(double radius, double weight);
		~Projectile();

		void Update();
		void Draw();


	};

}