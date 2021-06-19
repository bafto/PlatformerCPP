#pragma once

#include "../GeneralIncludes.h"

//loads and contains tile textures from a .texmap file
class TextureMap
{
public:
	TextureMap();

	TextureMap(std::string file);
	~TextureMap() = default;

	void Initialize(std::string file);
public:
	std::map<int, std::vector<sf::Texture>> textures;

};