#include "../../include/LevelRelated/TextureMap.h"
#include "../../include/Utility.h"
#include "../../include/GameException.h"

TextureMap::TextureMap()
{

}

TextureMap::TextureMap(std::string file)
{
	Initialize(file);
}

void TextureMap::Initialize(std::string file)
{
	textures.clear();

	//load the file
	std::ifstream ifs;
	ifs.open(file);
	if (ifs.is_open())
	{
		std::vector<std::string> lines;
		ifs.seekg(3); //because of the .texmap format we need to do this (don't know why)
		//read the file line by line
		for (std::string line; std::getline(ifs, line);)
			lines.push_back(line);
		for (auto& line : lines)
		{
			//split the line into the different parameters
			std::vector<std::string> strs = util::split(line, ' ');

			std::vector<sf::Texture> sliced;
			sliced.reserve(16);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					//load every texture from its rectangle
					sf::Texture tex;
					if (!tex.loadFromFile(strs[1], { x * 16, y * 16, 16, 16 }))
						throw FILEEXCEPTION(strs[1]); //Exceptions follow later
					sliced.push_back(std::move(tex));
				}
			}
			textures[std::stoi(strs[0])] = sliced;
		}
	}
	else
	{
		throw FILEEXCEPTION(file); //exception following later
	}
}