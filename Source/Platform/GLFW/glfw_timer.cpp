#include "Lunib/Utils/timer.h"

// Lib
#include <GLFW/glfw3.h>



namespace Lunib
{
    double Clock::GetTime()
    {
        return glfwGetTime();
    }

} // Lunib