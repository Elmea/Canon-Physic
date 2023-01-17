#pragma once
#include "Maths.h"
#include "RenderManager.h"
namespace Core
{
	class Canon : public Renderer::RenderObject
	{


	private:
		bool m_activeShootPrediction;

	public:
		Float2 position = Float2{ 10,100 };
		double angle = 0;
		double canonLength = 1;
		double power = 25;

	private:
		void ShowPredictionShoot();

	public:
		Canon();
		~Canon();

		void ActivateShootPrediction(bool state) { m_activeShootPrediction = state; };

		void Shoot();
		void Update();
		void Draw();




	};

}