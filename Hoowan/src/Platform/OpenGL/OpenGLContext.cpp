#include "hwpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Hoowan {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HW_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		HW_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HW_CORE_ASSERT(status, "Failed to initialize Glad!");

		HW_CORE_INFO("OpenGL Info:");
		HW_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		HW_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		HW_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		HW_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}