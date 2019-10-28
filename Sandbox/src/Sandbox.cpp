#include "include/pch.h"

class Sandbox : public Hazel::Application {
public:
   Sandbox() {}

   ~Sandbox() {}
};

Hazel::Application* CreateApplication() {
   return new Sandbox;
}
