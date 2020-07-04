#include "hwpch.h"

#include "OrthoGraphicCameraController.h"

#include "Hoowan/Input.h"
#include "Hoowan/KeyCodes.h"

namespace Hoowan {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:	m_AspectRatio(aspectRatio),
			m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
			m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		// Up/down movement
		if (Input::IsKeyPressed(HW_KEY_I))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HW_KEY_K))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		// Left/right movement
		if (Input::IsKeyPressed(HW_KEY_J))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HW_KEY_L))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		// Rotation
		if (m_Rotation) {
			if (Input::IsKeyPressed(HW_KEY_U))
			{
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			else if (Input::IsKeyPressed(HW_KEY_O))
			{
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.2f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}