#include "Application.h"
#include "Log.h"

int main(int argc, char* argv[]) {
   Hazel::Log::Init();
   HZ_CORE_WARN("Initialized Log!");
   HZ_INFO("Hello! Var = {}", 42);

   std::unique_ptr<Hazel::Application> app = CreateApplication();

   Hazel::Application::Get().Run();
}
