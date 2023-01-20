#pragma once
#include "Maths.h"

namespace Data
{
	class WorldSetting
	{
	public:
		WorldSetting();
		~WorldSetting();
		static double airResistance;
		static double airViscosity;
		static double GRAVITY;
		static double pixelPerMeter;
		static double horizontalMeterSize;
		static double verticalMeterSize;
		static void SetScreen();
	private:
		static double m_ratioScreen;

	};

	
}

