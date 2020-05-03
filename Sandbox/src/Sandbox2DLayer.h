#pragma once

#include "Hazel/Core/Layer.h"
#include "Hazel/Debug/Instrumentor.h"
#include "Hazel/ECS/ECS.h"
#include "Hazel/Renderer/OrthographicCameraController.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Texture.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2DLayer : public Hazel::Layer {
public:
	Sandbox2DLayer()
	: Hazel::Layer("Sandbox2D")
	, m_CameraController(/*aspectRatio=*/1280.0f / 720.0f, /*allowRotation=*/true)
	, m_SquareColor(0.2f, 0.3f, 0.8f, 1.0f)
	{}


	virtual void OnAttach() override {
		m_Texture = Hazel::Texture2D::Create("Assets/Textures/Checkerboard.png");
	}


	virtual void OnDetach() override {
		m_Texture = nullptr;
	}


	virtual void OnUpdate(Hazel::Timestep deltaTime) override {
		HZ_PROFILE_FUNCTION();
		// Update
		static float rotationDegrees = 0.0f;
		rotationDegrees += deltaTime * 50.0f;
		m_CameraController.OnUpdate(deltaTime);

		// Render
		Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		Hazel::RenderCommand::Clear();

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera().GetViewProjectionMatrix());

		Hazel::Renderer2D::DrawQuad({-0.5f, 0.5f}, {1.0f,  1.0f}, glm::radians(45.0f), m_SquareColor);
		Hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.75f, 0.5f}, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f});
		Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, -0.1f}, {10.0f, 10.0f}, 0.0f, *m_Texture);
		Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotationDegrees), *m_Texture, 10.0f);
		Hazel::Renderer2D::EndScene();
	}


	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

private:
	Hazel::OrthographicCameraController m_CameraController;
	std::unique_ptr<Hazel::Texture> m_Texture;
	Hazel::ECS::Entity m_Camera;
	glm::vec4 m_SquareColor;

};
