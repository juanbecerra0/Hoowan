#include "LevelParser.h"
#include "SpriteSheet.h"

LevelParser::LevelParser(const std::string& levelString)
{
	// Init symbols
	PlatformSprites platformSprites;
	std::unordered_map<char, Hoowan::Ref<Hoowan::SubTexture2D>> symbolMap;

	symbolMap['A'] = platformSprites.GreenLand;
	symbolMap['a'] = platformSprites.LandUnder;
	symbolMap['B'] = platformSprites.WaterSurface;
	symbolMap['b'] = platformSprites.WaterDepths;

	// Parse string, push things into vector
	glm::vec2 position = { 0.0f, 0.0f };
	for (char const& c : levelString)
	{
		if (c == '\n')
		{
			position.x = 0.0f;
			position.y -= 1.0f;
		}
		else if (symbolMap.find(c) == symbolMap.end())
		{
			position.x += 1.0f;
		}
		else
		{
			m_QuadRenderList.push_back({ position, symbolMap.at(c) });
			position.x += 1.0f;
		}
	}
}

void LevelParser::RenderLevel()
{
	for (QuadRender qr : m_QuadRenderList)
	{
		Hoowan::Renderer2D::DrawStaticQuad(qr.Position, { 1.0f, 1.0f }, qr.Sprite);
	}
}
