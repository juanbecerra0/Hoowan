#pragma once
#include "Hoowan/Renderer/FrameBuffer.h"

namespace Hoowan
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecs& specs);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };

		virtual const FrameBufferSpecs& GetSpecs() const override { return m_Specs; };

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecs m_Specs;
	};
}