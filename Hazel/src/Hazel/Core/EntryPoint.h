#include "Hazel/Core/Application.h"
#include "Hazel/Core/Log.h"

#include <memory>

int main(int argc, char* argv[]) {
   Hazel::Log::Init();
   HZ_CORE_WARN("Initialized Log!");
   std::unique_ptr<Hazel::Application> app = CreateApplication();
   Hazel::Application::Get().Run();
}
