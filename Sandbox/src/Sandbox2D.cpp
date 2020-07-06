#include "Sandbox2D.h"
#include "Hoowan/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

//#include <Hoowan\Renderer\Renderer2D.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	/*
	// Square verts
	m_VertexArray = Hoowan::VertexArray::Create();
	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	// Set up vertex buffer
	Hoowan::Ref<Hoowan::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Hoowan::VertexBuffer::Create(vertices, sizeof(vertices)));

	vertexBuffer->SetLayout({
		{ Hoowan::ShaderDataType::Float3, "a_Position" },
		});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	// Set up index buffer
	uint32_t indexBuffer[6] = { 0, 1, 2, 2, 3, 0 };
	Hoowan::Ref<Hoowan::IndexBuffer> squareIB;
	squareIB.reset(Hoowan::IndexBuffer::Create(indexBuffer, sizeof(indexBuffer) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(squareIB);

	// Compile Shaders
	m_Shader = (Hoowan::Shader::Create("assets/shaders/FlatColor.glsl"));
	*/
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hoowan::Timestep ts)
{

	// Camera
	m_CameraController.OnUpdate(ts);

	// Clear  buffer
	Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hoowan::RenderCommand::Clear();

	// Begin scene
	Hoowan::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Hoowan::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});

	/*
	// Setup for square
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);

	glm::vec3 pos(0);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
	Hoowan::Renderer::Submit(m_Shader, m_VertexArray, transform);
	*/

	Hoowan::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
