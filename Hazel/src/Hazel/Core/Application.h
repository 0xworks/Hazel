#pragma once

#include "Hazel/Core/LayerStack.h"
#include "Hazel/Core/Window.h"
#include "Hazel/Events/Event.h"

#include <memory>

namespace Hazel {

	class Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(std::unique_ptr<Layer> layer);

		void PushOverlay(std::unique_ptr<Layer> overlay);

		Window& GetWindow();

		static Application& Get();

	private:
		void OnWindowClose(Event& event);
		void OnWindowResize(Event& event);

	private:
		LayerStack m_layerStack;
		float m_lastFrameTime = 0.0f;
		std::unique_ptr<Window> m_window;
		bool m_isRunning = true;
		bool m_isMinimised = false;

	private:
		static Application* sm_application;

	};

}


// Must be defined in client
extern std::unique_ptr<Hazel::Application> CreateApplication();
