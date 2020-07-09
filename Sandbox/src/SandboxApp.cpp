#include <Hoowan.h>
#include <Hoowan/Core/EntryPoint.h>

#include "test/Sandbox2D.h"
#include "game/GameSandbox2D.h"

class Sandbox : public Hoowan::Application {
public:
	Sandbox() {
		PushLayer(new GameSandbox2D());
	}

	~Sandbox() {

	}
};

Hoowan::Application* Hoowan::CreateApplication() {
	return new Sandbox();
}