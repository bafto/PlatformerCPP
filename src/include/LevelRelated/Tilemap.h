#pragma once

#include "TextureMap.h"

//represents a single tile in the tilemap
class Tile
{
public:
	Tile();
	Tile(sf::Vector2f pos, int tileID, sf::Texture* tex = nullptr);

	sf::Vector2f GetPosition();
	int GetTileID() const; //returns the TileID

public:
	static inline const sf::Vector2f TileSize = sf::Vector2f(50.f, 50.f); //size of a tile

	sf::FloatRect rect; //the tiles bounds
	sf::Texture* texture;
	bool inHitbox; //used to generate the hitboxes in the tilemap

private:
	int TileID; //the ID of the tile. represents if it is  0 for air and numbers > 0 for grass, stone... etc.
};

//manages a tilemap that can be drawn and has collision hitboxes
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
	Tile GetTileAtPos(const sf::Vector2f& pos); //returns the tile at pos (not index)
	bool Collides(const sf::FloatRect& rect); //check if rect collides with any hitbox
	sf::Vector2i GetSize(); //Get the size as number of tiles
	sf::Vector2f GetPixelSize(); //Get the actual pixel size of the map
	sf::FloatRect GetBounds(); //the bounding rectangle that contains all tiles

public:
	std::vector<std::vector<Tile>> tiles;
	std::vector<sf::FloatRect> hitboxes; //the hitboxes used for collision

private:
	sf::RenderTexture renderTexture; //all tiles are rendered once on this texture, which is then used to render the map as a whole
	sf::Texture texture; //holds renderTextures texture once
	sf::RectangleShape surface; //uses texture to actually draw the tilemap
	TextureMap texMap; //the textures for all tiles
	int width, height; //the dimensions of the map (number of tiles)

};