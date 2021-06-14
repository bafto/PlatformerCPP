#pragma once

#include "../UIElements/UIPanel.h"
#include "../UIElements/UIText.h"

class UIButton : public UIPanel
{
public:
	UIButton(sf::FloatRect bounds);
	virtual ~UIButton();

	virtual void Initialize() override;

	void SetString(std::string str);
	void SetTextColor(sf::Color color);
	void SetColor(sf::Color color);
	void SetHoverColor(sf::Color color);
	void SetClickColor(sf::Color color);
	void SetCharacterSize(unsigned int size);
	void SetHoverSound(sf::Sound* sound);
	void SetClickSound(sf::Sound* sound);
	void SetReleaseSound(sf::Sound* sound);

	static sf::FloatRect StandardBounds() { return sf::FloatRect(0.f, 0.f, 100.f, 50.f); };

private:
	UIText text;
	sf::Color hoverColor, clickColor;

	sf::Sound* hoverSound, *clickSound, *releaseSound;

};