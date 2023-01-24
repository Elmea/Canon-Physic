#pragma once
#include "Maths.h"
#include "RenderManager.h"
#include "raylib.h"
namespace Core
{
	class Canon : public Renderer::RenderObject
	{


	private:
		int m_nbProjectileCreated = 0;
		bool m_activeShootPrediction;

		Texture2D m_canonTex;
		Texture2D m_cannonBaseTex;
		Renderer::RendererManager* m_renderManager;

		Float2 posImpact;
		Float2 speedZero;
		Float2 speedImpact;

	public:
		Float2 size;
		Float2 position = Float2{ 200,100 };
		double angle = 0;
		double canonLength = 1;
		double power = 10;
		double timeInAir; 
		double maxW;
		double maxH;

		bool valueChanged = true;
	private:
		void ShowPredictionShoot();
		void DrawCurvePrediction();

	public:
		Canon(Renderer::RendererManager* manager);
		Canon();
		~Canon();

		void ActivateShootPrediction(bool state) { m_activeShootPrediction = state; };

		void Shoot(double radius, double weight);
		void Update(double deltaTime);
		void Draw();




	};

}