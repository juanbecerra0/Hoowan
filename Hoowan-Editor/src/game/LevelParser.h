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
	LevelParser() = default;
	LevelParser(const std::string& levelString, Hoowan::Ref<Hoowan::Scene> scene);
};