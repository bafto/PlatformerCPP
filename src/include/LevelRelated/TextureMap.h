#pragma once

#include "../GeneralIncludes.h"

//basically a wrapper for the map
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