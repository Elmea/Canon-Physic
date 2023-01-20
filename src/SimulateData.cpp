#include "SimulationData.h"

namespace Data
{
	 double WorldSetting::airResistance = 0.1;
	 double WorldSetting::airViscosity = 15.6;
	 double WorldSetting::GRAVITY = 9.80665f;
	 double WorldSetting::pixelPerMeter = 10;
	 double WorldSetting::horizontalMeterSize = 100;
	 double WorldSetting::verticalMeterSize = 100;
	 double WorldSetting::m_ratioScreen = 1080.0 / 1920.0;;

	WorldSetting::WorldSetting()
	{

	}

	WorldSetting::~WorldSetting()
	{
	}
	void WorldSetting::SetScreen()
	{
		verticalMeterSize = m_ratioScreen * horizontalMeterSize;
	}
}