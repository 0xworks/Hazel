#include "pch.h"

class ExampleLayer : public Hazel::Layer {
public:
   ExampleLayer() : Layer("Example") {}

   void OnUpdate() override {
      HZ_TRACE("ExampleLayer::OnUpdate()");
   }

   void OnEvent(Hazel::Event& e) override {
      HZ_TRACE("{0}", e);
   }

};

class Sandbox : public Hazel::Application {
public:
   Sandbox() {
   }

   ~Sandbox() {}
};

Hazel::Application* CreateApplication() {
   return new Sandbox;
}
