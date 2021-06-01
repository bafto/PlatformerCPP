#include "../../include/LevelRelated/Tilemap.h"
#include "../../include/Utility.h"

Tile::Tile()
    :
    TileID(0),
    texture(nullptr),
    inHitbox(false)
{
    rect.setPosition({ 0, 0 });
    rect.setSize(TileSize);
}

Tile::Tile(sf::Vector2f pos, int tileID, sf::Texture* tex)
	:
	TileID(tileID),
	texture(tex),
	inHitbox(false)
{
	rect.setPosition(pos);
	rect.setSize(TileSize);
	if (tex)
		rect.setTexture(tex);
}

void Tile::updateTexture() 
{
    if (texture)rect.setTexture(texture);
}

int Tile::GetTileID() const
{
    return TileID;
}

void Tile::render(sf::RenderTarget& target)
{
	if (TileID != 0)
		target.draw(rect);
}

Tilemap::Tilemap()
    :
    width(0),
    height(0)
{}

Tilemap::Tilemap(const std::vector<std::string>& lines)
{
	Initialize(lines);
}

void Tilemap::Initialize(const std::vector<std::string>& lines)
{
	texMap.Initialize("assets\\Levels\\" + lines[1]);

	height = lines.size() - 2;
	width = lines[2].length();

	for (auto& vec : tiles)
		vec.clear();
	tiles.clear();
	tiles.resize(width);
	for (auto& vec : tiles)
		vec.resize(height);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			sf::Vector2f WorldPos(x * Tile::TileSize.x, y * Tile::TileSize.y);
			char ch = lines[lines.size() - height + y][x];
			int tileID = std::atoi(&ch);

			tiles[x][y] = Tile(WorldPos, tileID);
		}
	}
	LoadTextures();
	MakeHitboxes();
}

void Tilemap::LoadTextures()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int tileID = tiles[x][y].GetTileID();

            bool topAir = y == 0 || tiles[x][y - 1].GetTileID() == 0;
            bool leftAir = x == 0 || tiles[x - 1][y].GetTileID() == 0;
            bool rightAir = x == width - 1 || tiles[x + 1][y].GetTileID() == 0;
            bool bottomAir = y == height - 1 || tiles[x][y + 1].GetTileID() == 0;

            if (topAir && bottomAir)
            {
                if (leftAir)
                {
                    if (rightAir)
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][15];
                    }
                    else
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][12];
                    }
                }
                else if (rightAir)
                {
                    tiles[x][y].texture = &texMap.textures[tileID][14];
                }
                else
                {
                    tiles[x][y].texture = &texMap.textures[tileID][13];
                }
            }
            else
            {
                if (topAir)
                {
                    if (leftAir)
                    {
                        if (rightAir)
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][3];
                        }
                        else
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][0];
                        }
                    }
                    else if (rightAir)
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][2];
                    }
                    else
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][1];
                    }
                }
                else if (bottomAir)
                {
                    if (leftAir)
                    {
                        if (rightAir)
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][11];
                        }
                        else
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][8];
                        }
                    }
                    else if (rightAir)
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][10];
                    }
                    else
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][9];
                    }
                }
                else
                {
                    if (leftAir)
                    {
                        if (rightAir)
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][7];
                        }
                        else
                        {
                            tiles[x][y].texture = &texMap.textures[tileID][4];
                        }
                    }
                    else if (rightAir)
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][6];
                    }
                    else
                    {
                        tiles[x][y].texture = &texMap.textures[tileID][5];
                    }
                }
            }
        }
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tiles[x][y].updateTexture();
        }
    }
}

void Tilemap::MakeHitboxes()
{
    //loop to each Tile
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            //check if it is solid, and if it isn't already involved in a Hitbox
            if (tiles[x][y].GetTileID() != 0 && !tiles[x][y].inHitbox)
            {
                sf::FloatRect newHitbox = sf::FloatRect(tiles[x][y].rect.getPosition(), tiles[x][y].rect.getSize()); //this will become the finished hitbox
                tiles[x][y].inHitbox = true; //the tile will definitely be in a hitbox, even if it is alone
                bool firstLoop = true, breaked = false; //temporary bools for later
                int xEnd = 0; //the X-Coordinate to determine where the Hitbox will end
                for (int yy = y; yy < height; yy++) //loop from top to bottom starting at the detected Tile (which isn't already in a Hitbox and is non-solid)
                {
                    int xx = x + 1; //declared here to determine the width of the hitbox later
                    if (firstLoop) //in the first loop, the width of the hitbox is determined so it starts one Tile to the right of the original one
                    {
                        for (; xx < width && tiles[xx][yy].GetTileID() != 0 && !tiles[xx][yy].inHitbox; xx++) //loop from left to right until there is a air Tile
                        {
                            newHitbox.width += Tile::TileSize.x; //there is no air, so make the hitbox greater
                            tiles[xx][yy].inHitbox = true; //and set the added Tile to be in a hitbox
                        }
                        xEnd = xx; //the right end of the hitbox is set
                        firstLoop = false;
                    }
                    else
                    {
                        for (xx = x; xx < xEnd && tiles[xx][yy].GetTileID() != 0 && !tiles[xx][yy].inHitbox; xx++) //we know the width, now we start at the tiles directly under the original one
                        {
                            tiles[xx][yy].inHitbox = true; //just add them to the hitbox, the width of it is already set correctly
                        }
                    }
                    if (xx != xEnd) //did we reach the full width of the hitbox?
                    {
                        newHitbox.height -= Tile::TileSize.y; //no, so we don't have to increase the height
                        breaked = true; //we had to end cause it was no perfect rectangle anymore
                        for (int i = x; i < xx; i++) // those hitboxes where added, but now we have to remove them
                        {
                            tiles[i][yy].inHitbox = false;
                        }
                        break;
                    }
                    newHitbox.height += Tile::TileSize.y; //we reached the width of the hitbox so we increase the height
                }
                if (!breaked)
                {
                    newHitbox.height -= Tile::TileSize.y; //it wasn't a perfect rectangle so we decrease the height
                }
                hitboxes.push_back(newHitbox); //just add the Hitbox
            }
        }
    }
}

void Tilemap::render(sf::RenderTarget& target)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            tiles[x][y].render(target);
        }
    }
#ifdef _DEBUG
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    for (auto& rect : hitboxes)
    {
        shape.setPosition({ rect.left, rect.top });
        shape.setSize({ rect.width, rect.height });
        target.draw(shape);
    }
#endif
}

Tile Tilemap::GetTileAtPos(const sf::Vector2f& pos)
{
    return tiles[(int)(pos.x / Tile::TileSize.x)][(int)(pos.y / Tile::TileSize.y)];
}

bool Tilemap::Collides(const sf::FloatRect& rect)
{
    for (auto& hitbox : hitboxes)
    {
        if (util::RectIntersect(hitbox, rect))
            return true;
    }
    return false;
}

sf::Vector2i Tilemap::GetSize() 
{
    return sf::Vector2i(width, height);
}

sf::Vector2f Tilemap::GetPixelSize() 
{
    return sf::Vector2f(width * Tile::TileSize.x, height * Tile::TileSize.y);
}

sf::FloatRect Tilemap::GetBounds() 
{
    return sf::FloatRect({ 0.f, 0.f }, GetPixelSize());
}