#pragma once
#include "Hoowan.h"

struct QuadRender
{
	glm::vec2 Position;
	Hoowan::Ref<Hoowan::SubTexture2D> Sprite;
};

class LevelParser
{
public:
	LevelParser(const std::string& levelString);
	void RenderLevel();

private:
	std::vector<QuadRender> m_QuadRenderList;

};