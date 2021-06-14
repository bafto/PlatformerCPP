#pragma once

#include "../UIElements/UIPanel.h"

class UIImage : public UIPanel
{
public:
	UIImage(sf::FloatRect bounds);
	virtual ~UIImage();

	virtual void SetImage(sf::Texture tex);
	virtual void SetImage(sf::Image img);
	virtual void SetTextureRectangle(sf::IntRect bounds);
	virtual void LoadFromFile(std::string file, sf::IntRect area = sf::IntRect());

private:
	sf::Texture texture;
};