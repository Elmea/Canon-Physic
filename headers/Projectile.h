#pragma once
#include "Maths.h"
#include "RenderManager.h"

namespace Core
{
	class Projectile : public Renderer::RenderObject
	{
	private:
		int m_id;

		Float2 m_pos{ 0, 0};
		double m_weight;
		double m_radius;
		double m_lifeTime = 0;
		double m_inAirTime = 0;

		/* Values for drawing curve */
		Float2 m_startPos;
		Float2 m_endPos;
		bool m_hasHitGround = false;
		Float2 m_vInit;
		Float2 m_vFinal;
		double m_maxHeight;

		const double m_frontSurface;
		Float2 m_velocity{ 0, 0 };

		Float2 CalcTrail();
		double CalcTrailCoefficient();
		void DrawProjectilePath();
		void TouchGround(double deltaTime);

		Renderer::RendererManager* m_manager;
	public:
		static double lifeTimeAfterCollision;

		Projectile(Float2 position, double radius, double weight, double power, double angle , Renderer::RendererManager* _manager , int _id);
		~Projectile();

		double& GetWeightRef() { return m_weight; }
		double& GetRadiusRef() { return m_radius; }

		void Update(double deltaTime);
		void Draw();
		void AddForce(Float2 force, double deltaTime, bool debug = false);
		Float2 GetPos() { return m_pos; };
	};
}