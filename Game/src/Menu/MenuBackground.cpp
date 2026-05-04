#include "MenuBackground.h"

#include <Stellar/Utils/Utils.h>

#define BG_TIMER 10.f // 10 For the milestone, don't forget to put it back to: 30.f
#define BG_SPEED 15.f

using namespace Stellar;

float MenuBackground::xOffset = 0.f;
float MenuBackground::timer = 0.f;
int MenuBackground::backgroundIndex = -1;

void MenuBackground::Load()
{
	// Not preloading textures because it freezes the menu and stops the MainMenu's fade in.

	// All the values should add up to 100
	backgroundPaths.push_back({ "Sky", 15 });
	backgroundPaths.push_back({ "Plains", 20 });
	backgroundPaths.push_back({ "Mountains", 15 });
	backgroundPaths.push_back({ "Ocean", 15 });
	backgroundPaths.push_back({ "Caves", 20 });
	backgroundPaths.push_back({ "Deep_Caves", 10 });
	backgroundPaths.push_back({ "Hell", 5 });

	SetBackground(backgroundIndex == -1 ? RandomIndex() : backgroundIndex);
}

void MenuBackground::OnResize(sf::Vector2u _size)
{
	sf::Vector2u backgroundTexSize = bg.at(0).getTexture()->getSize();
	float scaleX = (float)_size.x / (float)backgroundTexSize.x;
	float scaleY = (float)_size.y / (float)backgroundTexSize.y;
	float scale = std::max(scaleX, scaleY);
	for (sf::Sprite& spr : bg)
	{
		spr.setScale({ scale, scale });
	}

	for (sf::Sprite& spr : bgTrans)
	{
		spr.setScale({ scale, scale });
	}
}

void MenuBackground::Update(float _dt)
{
	xOffset -= _dt * BG_SPEED;

	timer += _dt;
	if (timer >= BG_TIMER)
	{
		timer = 0.f;
		SetBackground(RandomIndex());
	}

	if (!easing.IsFinished())
	{
		easing.Update(_dt);

		sf::Color color = sf::Color(255, 255, 255, (unsigned int)easing.value);

		for (unsigned int i = 0; i < bgTrans.size(); i++)
		{
			bgTrans.at(i).setColor(color);
			if (i < bg.size())
			{
				bgTrans.at(i).setPosition(bg.at(i).getPosition());
			}
			else
			{
				float xPos = Utils::Scale(xOffset) * (i == 0 ? 1.f : i * 3.f);
				float spriteWidth = bgTrans.at(i).getGlobalBounds().width;

				float x = fmod(xPos, spriteWidth);

				if (x < 0)
					x += spriteWidth;
				bgTrans.at(i).setPosition(x, 0.f);
			}
		}

		if (easing.IsFinished())
		{
			std::swap(bg, bgTrans);
			bgTrans.clear();
		}
	}
}

void MenuBackground::Draw(sf::RenderTexture& _rt)
{
	DrawBackground(_rt, bg);

	if (!easing.IsFinished())
	{
		DrawBackground(_rt, bgTrans);
	}
}

void MenuBackground::DrawBackground(sf::RenderTexture& _rt, std::vector<sf::Sprite>& _sprites)
{
	unsigned int i = 0;
	for (sf::Sprite& spr : _sprites)
	{
		float xPos = Utils::Scale(xOffset) * (i == 0 ? 1.f : i * 3.f);
		float spriteWidth = spr.getGlobalBounds().width;

		float x = fmod(xPos, spriteWidth);

		if (x < 0)
			x += spriteWidth;

		sf::Vector2f originalPos = spr.getPosition();

		spr.setPosition(x, 0.f);
		_rt.draw(spr);

		spr.setPosition(x - spriteWidth, 0.f);
		_rt.draw(spr);

		spr.setPosition(originalPos);
		i++;
	}
}

void MenuBackground::SetBackground(unsigned int _index)
{
	bool firstLoad = bg.empty(); // If this is true, we're loading for the first time

	// If the new index is the same as the current one, just wait till the next switch
	if (_index == backgroundIndex && !firstLoad) 
		return;

	if (_index >= backgroundPaths.size())
	{
		_index = 0;
	}

	std::string textureDir = "Sprites/WorldBackgrounds/";
	for (const auto& entry : std::filesystem::directory_iterator("Assets/" + textureDir))
	{
		if (!entry.is_regular_file())
			continue;

		std::string fileName = entry.path().filename().string();
		if (fileName.rfind(backgroundPaths.at(_index).name, 0) == 0)
		{
			sf::Sprite spr = sf::Sprite(AssetManager::GetTexture(textureDir + fileName));
			
			if (!firstLoad)
			{
				spr.setColor(sf::Color::Transparent);
				bgTrans.emplace_back(spr);
			}
			else
			{
				bg.emplace_back(spr);
			}
		}
	}

	OnResize(Settings::GetWindowSize());

	if (!firstLoad)
		easing = Easing(EasingType::IN_QUAD, 1.f, 0.f, 255.f);

	backgroundIndex = (int)_index;
}

unsigned int MenuBackground::RandomIndex()
{
	int weightTotal = 0;
	for (const Background& entry : backgroundPaths)
	{
		weightTotal += entry.chance;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, weightTotal - 1);

	int rdm = dist(gen);

	int addedWeight = 0;
	for (int i = 0; i < backgroundPaths.size(); i++)
	{
		addedWeight += backgroundPaths[i].chance;

		if (rdm < addedWeight)
			return i;
	}

	return 0;
}
