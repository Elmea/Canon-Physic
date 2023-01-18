#include <raylib.h>
#include "Projectile.h"
#include "SimulationData.h"
#include "App.h"
#include <iostream>
namespace Core
{

	Projectile::Projectile(Float2 position, double radius, double weight, double power, double angle) : m_pos(position), m_radius(radius), m_weight(weight),
																			m_frontSurface(PI * ((radius * radius)/16.0))
	{
		angle = DEG2RAD * angle;
		std::cout << "Power:  " <<  power <<std::endl;
		std::cout << "DeltaTime  " << App::m_deltaTime <<std::endl;
		std::cout << "Vitesse start :  " << std::endl;
		AddForce(Float2{ power * cos(angle), power  * sin(angle) }, App::m_deltaTime,true) ;
	}

	Projectile::~Projectile()
	{
	}
	
	void Projectile::Update(double deltaTime)
	{
		DrawProjectilePath();
		if (m_pos.y >= 1080)
		{
			m_pos.y = 1080;
			return;
		}

		//AddForce(CalcTrail(), deltaTime);
		AddForce(Float2{ 0,Data::WorldSetting::GRAVITY  }, deltaTime,false);

		m_lifeTime += deltaTime;
		Float2 vel = m_velocity;
		m_pos = m_pos + vel;

		if (m_lifeTime >= m_timeLived)
		{
			m_timeLived += 0.1f;
			m_listPoints.push_back(m_pos);
		}

	
	}

	void Projectile::Draw()
	{
		DrawCircle(m_pos.x, m_pos.y, m_radius, PURPLE);
	}

	void Projectile::AddForce(Float2 force, double deltaTime, bool debug)
	{
		Float2 f = force * deltaTime;
		if(debug) std::cout << f.ToString() << std::endl;
		m_velocity = m_velocity + f;
	}

	Float2 Projectile::CalcTrail()
	{
		double v = m_velocity.Magnitude();
		double magnitude = 0.5 * Data::WorldSetting::airResistance * m_frontSurface * CalcTrailCoefficient() * v * v;

		int xSign = m_velocity.x >= 0 ? -1 : 1;
		int ySign = m_velocity.y >= 0 ? -1 : 1;

		double theta = acos(m_velocity.y);

		return { magnitude * cos(theta) * xSign, magnitude * sin(theta) * ySign };
	}

	double Projectile::CalcTrailCoefficient()
	{
		return 24.0 / ((Data::WorldSetting::airResistance * m_velocity.Magnitude() * m_radius * 2) / Data::WorldSetting::airViscosity);
	}

	void Projectile::DrawProjectilePath()
	{
		int nbPoints = m_listPoints.size();
		if (nbPoints < 1) 
			return;

		for (int i = 0; i < nbPoints -1; i++)
			DrawLine(m_listPoints[i].x, m_listPoints[i].y, m_listPoints[i + 1].x, m_listPoints[i + 1].y, SKYBLUE);

		DrawLine(m_listPoints[nbPoints - 1].x, m_listPoints[nbPoints - 1].y, m_pos.x, m_pos.y, SKYBLUE);
	}
}