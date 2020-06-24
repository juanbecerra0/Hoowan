#include <Hoowan.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hoowan::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f)
	{
		// Triangle verticies
		m_VertexArray.reset(Hoowan::VertexArray::Create());
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		// Set up vertex buffer
		Hoowan::Ref<Hoowan::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hoowan::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hoowan::BufferLayout layout = {
			{ Hoowan::ShaderDataType::Float3, "a_Position" },
			{ Hoowan::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Set up index buffer
		uint32_t indices[3] = { 0, 1, 2 };
		Hoowan::Ref<Hoowan::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hoowan::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square verticies
		m_SquareVA.reset(Hoowan::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		// Set up vertex buffer
		Hoowan::Ref<Hoowan::VertexBuffer> squareVB;
		squareVB.reset(Hoowan::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Hoowan::ShaderDataType::Float3, "a_Position" },
			{ Hoowan::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		// Set up index buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Hoowan::Ref<Hoowan::IndexBuffer> squareIB;
		squareIB.reset(Hoowan::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Triangle shaders
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_Shader.reset(Hoowan::Shader::Create(vertexSrc, fragmentSrc));

		// Square shader
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Hoowan::Shader::Create(blueShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Hoowan::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Hoowan::Texture2D::Create("assets/textures/test.png");
		m_TransTexture = Hoowan::Texture2D::Create("assets/textures/trans.png");

		std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Hoowan::Timestep ts) override
	{
		float time = ts;

		// Camera interaction

		// Up/down movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_I))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}else if (Hoowan::Input::IsKeyPressed(HW_KEY_K))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		// Left/right movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_J))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_L))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		// Rotation
		if (Hoowan::Input::IsKeyPressed(HW_KEY_U))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_O))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		// Model interaction 

		// Up/down movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_W))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_S))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		// Left/right movement
		if (Hoowan::Input::IsKeyPressed(HW_KEY_A))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}
		else if (Hoowan::Input::IsKeyPressed(HW_KEY_D))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}

		// Clear  buffer
		Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hoowan::RenderCommand::Clear();

		// Set camera
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		// Begine scene
		Hoowan::Renderer::BeginScene(m_Camera);
		
		// Setup for little squares
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_FlatColorShader) -> Bind();
		std::dynamic_pointer_cast<Hoowan::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		// Submit little squares
		for (int i = -20; i < 20; i++) {
			for (int j = -20; j < 20; j++) {
				glm::vec3 pos(i * 0.12f, j * 0.12f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				Hoowan::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		// Submit textured square
		
		m_Texture->Bind();
		Hoowan::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_TransTexture->Bind();
		Hoowan::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Submit triangle
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		Hoowan::Renderer::Submit(m_Shader, m_VertexArray, transform);

		Hoowan::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hoowan::Event& event) override
	{
		
	}

private:
	Hoowan::Ref<Hoowan::Shader> m_Shader;
	Hoowan::Ref<Hoowan::VertexArray> m_VertexArray;
				
	Hoowan::Ref<Hoowan::Shader> m_FlatColorShader, m_TextureShader;
	Hoowan::Ref<Hoowan::VertexArray> m_SquareVA;

	Hoowan::Ref<Hoowan::Texture2D> m_Texture, m_TransTexture;

	Hoowan::OrthographicCamera m_Camera;

	// Speeds are per second

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 90.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 2.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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