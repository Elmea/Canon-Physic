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

		double m_timeLived = 0; /* 0.1f * m_timeLived = the life time  */
		const double m_frontSurface;


		Float2 m_velocity{ 0, 0 };
		std::vector<Float2>m_listPoints;



		Float2 CalcTrail();
		double CalcTrailCoefficient();
		void DrawProjectilePath();

	public:
		Projectile(Float2 position, double radius, double weight, double power, double angle);
		~Projectile();

		double& GetWeightRef() { return m_weight; }
		double& GetRadiusRef() { return m_radius; }

		void Update(double deltaTime);
		void Draw();
		void AddForce(Float2 force, double deltaTime, bool debug);
		Float2 GetPos() { return m_pos; };
	};
}