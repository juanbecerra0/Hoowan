#include <Hoowan.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hoowan::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f), m_CameraRotation(0.0f)
	{
		// Triangle verticies
		m_VertexArray.reset(Hoowan::VertexArray::Create());
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// Set up vertex buffer
		std::shared_ptr<Hoowan::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hoowan::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hoowan::BufferLayout layout = {
			{ Hoowan::ShaderDataType::Float3, "a_Position" },
			{ Hoowan::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Set up index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hoowan::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hoowan::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square verticies
		m_SquareVA.reset(Hoowan::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		// Set up vertex buffer
		std::shared_ptr<Hoowan::VertexBuffer> squareVB;
		squareVB.reset(Hoowan::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Hoowan::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		// Set up index buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hoowan::IndexBuffer> squareIB;
		squareIB.reset(Hoowan::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Triangle shaders
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Hoowan::Shader(vertexSrc, fragmentSrc));

		// Square shader
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Hoowan::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}

	void OnUpdate() override
	{
		// Up/down movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_W))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}else if (Hoowan::Input::IsKeyPressed(HW_KEY_S))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}

		// Left/right movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_A))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_D))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}

		// Rotation
		if (Hoowan::Input::IsKeyPressed(HW_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_E))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}

		// Clear  buffer
		Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hoowan::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hoowan::Renderer::BeginScene(m_Camera);

		Hoowan::Renderer::Submit(m_BlueShader, m_SquareVA);
		Hoowan::Renderer::Submit(m_Shader, m_VertexArray);

		Hoowan::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Hoowan::Event& event) override
	{
		
	}

private:
	std::shared_ptr<Hoowan::Shader> m_Shader;
	std::shared_ptr<Hoowan::VertexArray> m_VertexArray;

	std::shared_ptr<Hoowan::Shader> m_BlueShader;
	std::shared_ptr<Hoowan::VertexArray> m_SquareVA;

	Hoowan::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.01f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 2.0f;
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