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


		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };

		virtual const FrameBufferSpecs& GetSpecs() const override { return m_Specs; };

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferSpecs m_Specs;
	};
}