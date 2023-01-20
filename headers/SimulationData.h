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
		static Float2 originSystem;

		static Float2 GetRaylibPos(const Float2& pos);
		static Float2 GetRaylibSpeed(const Float2& speed);
	private:
		static double m_ratioScreen;

	};

	
}

