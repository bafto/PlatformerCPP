#include "../../../include/UI/UIElements/UIImage.h"

UIImage::UIImage(sf::FloatRect bounds)
	:
	UIPanel(bounds)
{
	texture.create(bounds.width, bounds.height);
	rect.setTexture(&texture);
}

UIImage::~UIImage()
{

}

void UIImage::SetImage(sf::Texture tex)
{
	texture = tex;
}

void UIImage::SetImage(sf::Image img)
{
	texture.loadFromImage(img);
}

void UIImage::SetTextureRectangle(sf::IntRect bounds)
{
	rect.setTextureRect(bounds);
}

void UIImage::LoadFromFile(std::string file, sf::IntRect area)
{
	texture.loadFromFile(file, area);
}