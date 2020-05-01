#include "pch.h"
#include "Sandbox2DLayer.h"

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
