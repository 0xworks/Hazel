#include "pch.h"

class Sandbox : public Hazel::Application {
public:
   Sandbox() {
   }

   ~Sandbox() {}
};


std::unique_ptr<Hazel::Application> CreateApplication() {
   return std::make_unique<Sandbox>();
}
