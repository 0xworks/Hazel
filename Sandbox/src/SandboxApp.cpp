#define ECS_IMPLEMENT
#include "Hazel/ECS/ECS.h"

#include "Sandbox2DLayer.h"

#include "Hazel/Core/Application.h"
#include "Hazel/Core/EntryPoint.h"


class SandboxApp : public Hazel::Application {
public:
	SandboxApp() {
		PushLayer(std::make_unique<Sandbox2DLayer>());
	}

	~SandboxApp() {}
};


std::unique_ptr<Hazel::Application> CreateApplication() {
	HZ_PROFILE_FUNCTION();
	return std::make_unique<SandboxApp>();
}
