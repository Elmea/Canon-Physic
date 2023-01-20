#pragma once
#include "Maths.h"
#include "RenderManager.h"
#include "raylib.h"
namespace Core
{
	class Canon : public Renderer::RenderObject
	{


	private:
		bool m_activeShootPrediction;

		Texture2D m_canonTex;
		Texture2D m_cannonBaseTex;
		Renderer::RendererManager* m_renderManager;

	public:
		Float2 size;
		Float2 position = Float2{ 200,100 };
		double angle = 0;
		double canonLength = 1;
		double power = 10;

	private:
		void ShowPredictionShoot();
		
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