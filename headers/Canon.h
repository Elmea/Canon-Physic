#pragma once
#include "Maths.h"
#include "RenderManager.h"
namespace Core
{
	class Canon :RenderObject
	{


	private:
		bool m_activeShootPrediction;

	public:
		Float2 position;
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
		void Draw();




	};

}