#include "SaveEntry.h"

#include "Common.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

SaveEntry SaveEntry::Create(std::filesystem::path _worldPath)
{
    SaveEntry entry;
    entry.buttonBackground = ImageButton::Create("UI/SelectCreateWorld/Save.png", {});
    entry.buttonEdit = ImageButton::Create("UI/SelectCreateWorld/Rename.png", {});
    entry.buttonDelete = ImageButton::Create("UI/SelectCreateWorld/Delete.png", {});
    entry.buttonConfirm = ImageButton::Create("UI/SelectCreateWorld/Confirm.png", {});
    entry.textName = Text::Create(UI_FONT_MAIN, _worldPath.filename().string(), {});
    entry.textConfirm = Text::CreateCentered(UI_FONT_MAIN, Language::Get().Translate("selectworld.confirmdelete"), {});
    entry.inputName = Textbox::Create(UI_FONT_MAIN, _worldPath.filename().string(), {}, false);
    entry.inputName.SetMaxCharLength(16);
    entry.inputName.SetFocusColor(sf::Color(0x909090FF));
    entry.inputName.text = _worldPath.filename().string();
    entry.worldPath = _worldPath;
    return entry;
}

SaveEntryAction SaveEntry::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
    if (buttonBackground.isHovered && !isRenaming)
    {
        SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
        return SaveEntryAction::LOAD;
    }

    if (buttonEdit.isHovered)
    {
        isRenaming = !isRenaming;
        if (isRenaming)
            inputName.SetFocused(true);

        SaveEntryAction action = !isRenaming && !inputName.text.empty() ? SaveEntryAction::EDIT : SaveEntryAction::NONE;

        if (action != SaveEntryAction::NONE)
            SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);

        return action;
    }

    if (buttonConfirm.isHovered && confirmDeletion)
    {
        SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
        return SaveEntryAction::DELETE;
    }

    if (buttonDelete.isHovered && !confirmDeletion)
    {
        confirmDeletion = true;
        SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
        return SaveEntryAction::NONE;
    }

    // If nothing is clicked, reset the confirm button
    confirmDeletion = false;
    isRenaming = false;

    SaveEntryAction action = !isRenaming && !inputName.text.empty() ? SaveEntryAction::EDIT : SaveEntryAction::NONE;

    //if (action != SaveEntryAction::NONE)
        //SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);

    return action;
}

void SaveEntry::OnTextEntered(sf::Event::TextEvent _text)
{
    inputName.OnTextEntered(_text);
}

void SaveEntry::Update(float _deltaTime)
{
    if (!isRenaming)
        buttonBackground.Update(_deltaTime);
    
    if (!confirmDeletion)
    {
        buttonEdit.Update(_deltaTime);
        buttonDelete.Update(_deltaTime);
    }
    else
    {
        buttonConfirm.Update(_deltaTime);
    }
}

void SaveEntry::Draw(sf::RenderTexture& _rt)
{
    buttonBackground.Draw(_rt);
    
    if (!confirmDeletion)
    {
        buttonEdit.Draw(_rt);
        buttonDelete.Draw(_rt);
    }
    else
    {
        buttonConfirm.Draw(_rt);
        textConfirm.Draw(_rt);
    }

    if (isRenaming)
        inputName.Draw(_rt);
    else
        textName.Draw(_rt);
}

void SaveEntry::SetPosition(sf::Vector2f _pos)
{
    buttonBackground.SetPosition(_pos);
    buttonEdit.SetPosition({ _pos.x + Utils::Scale(265.f), _pos.y });
    buttonDelete.SetPosition({ _pos.x + Utils::Scale(325.f), _pos.y });
    buttonConfirm.SetPosition({ _pos.x + Utils::Scale(295.f), _pos.y });
    textName.SetPosition({ _pos.x - Utils::Scale(210.f), _pos.y - textName.fontSize / 2.f });
    inputName.SetPosition({ _pos.x - Utils::Scale(210.f), _pos.y - textName.fontSize / 2.f });
    textConfirm.SetPosition({ _pos.x + Utils::Scale(295.f), _pos.y });
}

void SaveEntry::SetScale(float _scale)
{
    buttonBackground.SetScale(_scale);
    buttonEdit.SetScale(_scale);
    buttonDelete.SetScale(_scale);
    buttonConfirm.SetScale(_scale);
    textName.SetCharacterSize((unsigned int)(25.f * _scale));
    inputName.SetSize((unsigned int)(25.f * _scale));
    textConfirm.SetCharacterSize((unsigned int)(15.f * _scale));
}
