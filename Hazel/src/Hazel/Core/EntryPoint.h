#include "Hazel/Components/Camera.h"
#include "Hazel/Components/CameraSettings.h"
#include "Hazel/Components/Transform.h"
#include "Hazel/Core/Application.h"
#include "Hazel/Core/Log.h"
#include "Hazel/ECS/ECS.h"
#include "Hazel/Events/Events.h"

#include <memory>

int main(int argc, char* argv[]) {
   Hazel::Log::Init();
   HZ_CORE_WARN("Initialized Log!");

   Hazel::Events::Init();
   HZ_CORE_WARN("Initialized Event System!");

   Hazel::ECS::Init();
   HZ_CORE_WARN("Initialized Entity Component System!");

   Hazel::ECS::RegisterComponent<Hazel::Camera>();
   Hazel::ECS::RegisterComponent<Hazel::CameraSettings>();
   Hazel::ECS::RegisterComponent<Hazel::Transform>();

   std::unique_ptr<Hazel::Application> app = CreateApplication();
   Hazel::Application::Get().Run();
}
