#pragma once

#include "core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Phoenix
{
    class PHOENIX_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    //To be define in CLIENT
    Application* CreateApplication();
}
