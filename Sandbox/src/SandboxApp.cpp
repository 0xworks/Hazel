#include "pch.h"
#include "Sandbox2DLayer.h"
#include "Hazel/Components/Camera.h"
#include "Hazel/Components/Transform.h"
#include "Hazel/ECS/ECS.h"

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
