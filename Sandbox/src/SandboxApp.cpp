#include <Hoowan.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class ExampleLayer : public Hoowan::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Hoowan::Input::IsKeyPressed(HW_KEY_TAB))
			HW_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Hoowan::Event& event) override
	{
		if (event.GetEventType() == Hoowan::EventType::KeyPressed)
		{
			Hoowan::KeyPressedEvent& e = (Hoowan::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HW_KEY_TAB)
				HW_TRACE("Tab key is pressed (event)!");
			HW_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Hoowan::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Hoowan::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Hoowan::Application* Hoowan::CreateApplication() {
	return new Sandbox();
}