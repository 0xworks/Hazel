#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Events/Events.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"

namespace Hazel {


	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation)
	: m_aspectRatio(aspectRatio)
	, m_zoom(1.0f)
	, m_camera(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio* m_zoom, -m_zoom)
	, m_cameraPosition(0.0f, 0.0f, 0.0f)
	, m_cameraRotation(0.0f)
	, m_cameraTranslationSpeed(m_zoom)
	, m_cameraRotationSpeed(180.0f)
	, m_isRotationEnabled(enableRotation) {
		Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Mouse::SCROLLED, OrthographicCameraController::OnMouseScrolled));
		Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Window::RESIZE, OrthographicCameraController::OnWindowResized));
	}


	void OrthographicCameraController::OnUpdate(Timestep deltaTime) {
		if (Input::IsKeyPressed(HZ_KEY_A)) {
			m_cameraPosition.x -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
			m_cameraPosition.y -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
		} else if (Input::IsKeyPressed(HZ_KEY_D)) {
			m_cameraPosition.x += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
			m_cameraPosition.y += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(HZ_KEY_W)) {
			m_cameraPosition.x += -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
			m_cameraPosition.y += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
		} else if (Input::IsKeyPressed(HZ_KEY_S)) {
			m_cameraPosition.x -= -sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
			m_cameraPosition.y -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * deltaTime;
		}
		m_camera.SetPosition(m_cameraPosition);

		if (m_isRotationEnabled) {
			if (Input::IsKeyPressed(HZ_KEY_Q)) {
				m_cameraRotation += (m_cameraRotationSpeed * deltaTime);
			} else if (Input::IsKeyPressed(HZ_KEY_E)) {
				m_cameraRotation -= (m_cameraRotationSpeed * deltaTime);
			}
			if (m_cameraRotation > 180.0f) {
				m_cameraRotation -= 360.0f;
			} else if (m_cameraRotation <= -180.0f) {
				m_cameraRotation += 360.0f;
			}
			m_camera.SetRotation(m_cameraRotation);
		}
	}


	const Hazel::OrthographicCamera& OrthographicCameraController::GetCamera() const {
		return m_camera;
	}


	bool OrthographicCameraController::OnMouseScrolled(Event& event) {
		auto yOffset = event.GetParam<float>(Events::Mouse::Scrolled::YOFFSET);
		m_zoom -= yOffset * 0.5f;
		m_zoom = std::max(m_zoom, 0.25f);
		m_cameraTranslationSpeed = m_zoom;
		m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
		return false;
	}


	bool OrthographicCameraController::OnWindowResized(Event& event) {
		auto windowWidth = event.GetParam<int>(Events::Window::Resize::WIDTH);
		auto windowHeight = event.GetParam<int>(Events::Window::Resize::HEIGHT);
		m_aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
		m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
		return false;
	}

}
