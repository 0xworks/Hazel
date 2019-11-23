#include "pch.h"
#include "ExampleLayer.h"
#include "Sandbox2DLayer.h"

class SandboxApp : public Hazel::Application {
public:
   SandboxApp() {
      //PushLayer(std::make_unique<ExampleLayer>());
      PushLayer(std::make_unique<Sandbox2DLayer>());
   }

   ~SandboxApp() {}
};


std::unique_ptr<Hazel::Application> CreateApplication() {
   return std::make_unique<SandboxApp>();
}
