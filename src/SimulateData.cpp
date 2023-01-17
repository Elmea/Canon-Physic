#include "SimulationData.h"

namespace Data
{
	 double WorldSetting::airResistance = 0.1;
	 double WorldSetting::airViscosity = 15.6;
	 double WorldSetting::GRAVITY = 9.80665f;
	 double WorldSetting::pixelPerMeter = 10;

	WorldSetting::WorldSetting()
	{
	}

	WorldSetting::~WorldSetting()
	{
	}
}