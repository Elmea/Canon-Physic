#pragma once

namespace Core
{
	class Canon
	{

		
	private:
		// Positon 
		bool m_activeShootPrediction;

	public:
		double angle = 0;
		double canonLength = 1;
		double power = 25; 

	private : 
		void ShowPredictionShoot();

	public:
		Canon();
		~Canon();
		
		void ActivateShootPrediction(bool state) { m_activeShootPrediction = state; };

		void Shoot();
		void Draw();
		

	

	};

}