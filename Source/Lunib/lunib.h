#pragma once

// Core
#include "Lunib/Core/engine.h"
#include "Lunib/Core/definitions.h"
#include "Lunib/Core/window.h"
#include "Lunib/Core/input.h"
#include "Lunib/Core/key_codes.h"
#include "Lunib/Core/mouse_codes.h"
#include "Lunib/Core/log.h"


// Renderer
#include "Lunib/Renderer/graphics_context.h"
#include "Lunib/Renderer/renderer_api.h"
#include "Lunib/Renderer/shader.h"
#include "Lunib/Renderer/vertex_array.h"
#include "Lunib/Renderer/buffer.h"

// Events
#include "Lunib/Events/event.h"
#include "Lunib/Events/key_event.h"
#include "Lunib/Events/mouse_event.h"
#include "Lunib/Events/window_event.h"

// Math
#include "Lunib/Math/math.h"

// Utils
#include "Lunib/Utils/timer.h"
#include "Lunib/Utils/utils.h"



namespace Lunib
{
    // Call this after creating a window to initialize the rendering context and other subsystems.
    LUNIB_API bool LInit()
    {
        return true;
    }

    // Call this at the end of the program before the method Destroy(Window) to clean up graphics resources, 
    // release memory, and shut down rendering.
    LUNIB_API void LShutdown()
    {
        ShaderLibrary::Release();
        RendererAPI::Release();
    }
}