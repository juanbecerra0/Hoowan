#include "LevelParser.h"
#include "SpriteSheet.h"
#include "glm/gtx/string_cast.hpp"

LevelParser::LevelParser(const std::string& levelString, Hoowan::Ref<Hoowan::Scene> scene)
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
			// Create an entity
			auto sprite = scene->CreateEntity("LevelSprite :: " + glm::to_string(position));

			// Set position
			sprite.GetComponent<Hoowan::TransformComponent>().GetTransform() = 
				glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f });

			// Add subtexture component
			sprite.AddComponent<Hoowan::SpriteRendererSubTextureComponent>(symbolMap.at(c));

			// (Maybe) add a static collider component
			if (c != 'B' && c!= 'b')
				sprite.AddComponent<Hoowan::CollisionComponent>(false, sprite.GetComponent<Hoowan::TransformComponent>().GetTransform());

			position.x += 1.0f;
		}
	}
}
