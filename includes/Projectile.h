#pragma once

namespace Core
{
	class Projectile
	{
	private:
		// Position 
		double m_weight;
		double m_radius;

	public:
		Projectile(double radius, double weight);
		~Projectile();

		void Update();
		void Draw();


	};

}