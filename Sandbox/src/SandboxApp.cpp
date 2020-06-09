#include <Hoowan.h>

class ExampleLayer : public Hoowan::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		HW_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hoowan::Event& event) override
	{
		HW_TRACE("{0}", event);
	}

};

class Sandbox : public Hoowan::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Hoowan::Application* Hoowan::CreateApplication() {
	return new Sandbox();
}