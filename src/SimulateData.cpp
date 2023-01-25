#include "SimulationData.h"

namespace Data
{
	 double WorldSetting::airResistance = 0.1;
	 double WorldSetting::airViscosity = 1.56;
	 double WorldSetting::GRAVITY = -9.80665f;
	 double WorldSetting::pixelPerMeter = 100;
	 Float2 WorldSetting::originSystem = { 0, 1080 };

	WorldSetting::WorldSetting()
	{

	}

	WorldSetting::~WorldSetting()
	{
	}

	Float2 WorldSetting::GetRaylibPos(const Float2& pos)
	{
		return { pos.x , originSystem.y - pos.y };
	}

	Float2 WorldSetting::GetRaylibSpeed(const Float2& speed)
	{
		return { speed.x, speed.y * -1 };
	}
}