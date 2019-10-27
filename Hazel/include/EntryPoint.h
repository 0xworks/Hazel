#include "Application.h"

int main(int argc, char* argv[]) {
   Hazel::Application* pApp = CreateApplication();
   pApp->Run();
   delete pApp;
}
