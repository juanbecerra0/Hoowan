#include "hwpch.h"
#include "FrameBuffer.h"

#include "Hoowan/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Hoowan
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecs& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFrameBuffer>(specs);
		}

		HW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}