#pragma once

#include "TextureMap.h"

class Tile
{
public:
	Tile();
	Tile(sf::Vector2f pos, int tileID, sf::Texture* tex = nullptr);

	void updateTexture();
	void render(sf::RenderTarget& target);

	int GetTileID() const;

public:
	static inline const sf::Vector2f TileSize = sf::Vector2f(50.f, 50.f);

	sf::RectangleShape rect;
	sf::Texture* texture;
	bool inHitbox;

private:
	int TileID;
};

class Tilemap
{
public:
	Tilemap();
	Tilemap(const std::vector<std::string>& lines);

	void Initialize(const std::vector<std::string>& lines);

	void render(sf::RenderTarget& target);
private:
	void LoadTextures();
	void MakeHitboxes();

public:
	Tile GetTileAtPos(const sf::Vector2f& pos);
	bool Collides(const sf::FloatRect& rect);
	sf::Vector2i GetSize();
	sf::Vector2f GetPixelSize();
	sf::FloatRect GetBounds();

public:
	std::vector<std::vector<Tile>> tiles;
	std::vector<sf::FloatRect> hitboxes;

private:
	TextureMap texMap;
	int width, height;

};