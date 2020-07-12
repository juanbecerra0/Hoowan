#pragma once

#include "Hoowan/Core/Core.h"

namespace Hoowan
{
	struct FrameBufferSpecs
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		// Should this framebuffer render to the swapchain?
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpecs& GetSpecs() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecs& specs);
	};
}