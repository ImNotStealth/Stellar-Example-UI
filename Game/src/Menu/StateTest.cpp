#include "StateTest.h"

#include "Common.h"
#include "StateMainMenu.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

void StateTest::Load()
{
	buttonBack = Button::Create(UI_FONT_MAIN, "test.back", {});
}

void StateTest::OnResize(sf::Vector2u _size)
{
	float scale = Utils::Scale(1.f);

	float spacing = Utils::Scale(48.f);
	unsigned int buttonSize = (unsigned int)(30.f * scale);
	buttonBack.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f - spacing });
	buttonBack.SetSize((unsigned int)(40.f * scale));
}

void StateTest::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonBack.isHovered)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		Game::Get().SetState<StateMainMenu>();
		return;
	}
}

void StateTest::Update(float _deltaTime)
{
	buttonBack.Update(_deltaTime);
}

void StateTest::UpdateImGui(float _deltaTime)
{
	ImGui::Text("This ImGui menu is only available in StateTest while in Debug, use this if you want to create State specific tools!");

	if (ImGui::Button("Test!"))
		std::cout << "ImGui test button pressed!" << std::endl;
}

void StateTest::Draw(sf::RenderTexture& _texture)
{
	buttonBack.Draw(_texture);
}
