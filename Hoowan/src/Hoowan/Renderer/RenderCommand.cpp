#include "hwpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hoowan {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}