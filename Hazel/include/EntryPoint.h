#include "Application.h"
#include "Log.h"

int main(int argc, char* argv[]) {
   Hazel::Log::Init();
   HZ_CORE_WARN("Initialized Log!");
   HZ_INFO("Hello! Var = {}", 42);
   Hazel::Application* pApp = CreateApplication();
   pApp->Run();
   delete pApp;
}
