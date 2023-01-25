#pragma once
#include "Maths.h"
#include "RenderManager.h"
#include "Rigidbody.h"
#include "raylib.h"

namespace Core
{
	class Projectile;

	class Canon : public Renderer::RenderObject
	{


	private:
		int m_nbProjectileCreated = 0;
		bool m_activeShootPrediction;

		Texture2D m_canonTex;
		Texture2D m_cannonBaseTex;
		Renderer::RendererManager* m_renderManager = nullptr;

		Float2 posImpact;
		Float2 speedZero;
		Float2 speedImpact;
	public:
		Float2 initPos;
		Float2 size;
		Float2 position = Float2{ 200,100 };
		double angle = 0;
		double canonLength = 1;
		double power = 10;
		double timeInAir; 
		double maxW;
		double maxH;
		double weight = 100;

		bool valueChanged = true;
	private:
		void ShowPredictionShoot();
		void DrawCurvePrediction();
		void ResolveFriction();
		Rigidbody rigidbody;

		void ResolveCollision(double p_weight);
	public:
		Canon(Renderer::RendererManager* manager);
		Canon();
		~Canon();

		void ActivateShootPrediction(bool state) { m_activeShootPrediction = state; };

		void Shoot(double radius, double weight);
		void Update(double deltaTime);
		void Draw();

		Rigidbody& GetRigidbody() { return rigidbody; }



	};

}