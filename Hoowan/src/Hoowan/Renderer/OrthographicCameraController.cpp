#include "hwpch.h"

#include "OrthoGraphicCameraController.h"

#include "Hoowan/Core/Input.h"
#include "Hoowan/Core/KeyCodes.h"

namespace Hoowan {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:	m_AspectRatio(aspectRatio),
			m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HW_PROFILE_FUNCTION();

		// Up/down movement
		if (Input::IsKeyPressed(HW_KEY_UP))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HW_KEY_DOWN))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		// Left/right movement
		if (Input::IsKeyPressed(HW_KEY_LEFT))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HW_KEY_RIGHT))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		// Recenter
		if (Input::IsKeyPressed(HW_KEY_SLASH))
		{
			m_CameraRotation = 0.0f;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		// Rotation
		if (m_Rotation) {
			if (Input::IsKeyPressed(HW_KEY_COMMA))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			else if (Input::IsKeyPressed(HW_KEY_PERIOD))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HW_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::Resize(float width, float height)
	{
		HW_PROFILE_FUNCTION();

		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HW_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.2f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HW_PROFILE_FUNCTION();

		Resize((float)e.GetWidth(), (float)e.GetHeight());

		return false;
	}

}