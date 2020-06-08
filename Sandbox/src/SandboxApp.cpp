#include <Hoowan.h>

class Sandbox : public Hoowan::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Hoowan::Application* Hoowan::CreateApplication() {
	return new Sandbox();
}