#pragma once
#include "Lunib/Core/base.h"
#include "timer.h"


namespace Lunib
{
    class LUNIB_API FpsCalculator
    {
        public:
            void Calculate()
            {
                if (double currentTime = Clock::GetTime();
					currentTime - m_LastTime >= 1.0f)
				{
					m_FPS = m_Counter / (currentTime - m_LastTime);
					m_LastTime = currentTime;
					m_Counter = 0.0;
				}
                m_Counter++;
            }

            double GetFPS() const { return m_FPS; }

        private:
            double m_LastTime = 0.0;
            double m_FPS = 0.0f;
            double m_Counter = 0.0;
    };

} // Lunib