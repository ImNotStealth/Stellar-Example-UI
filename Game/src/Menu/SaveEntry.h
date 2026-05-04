#ifndef SAVE_ENTRY_H
#define SAVE_ENTRY_H

#include <Stellar/Stellar.h>

enum class SaveEntryAction
{
	NONE,
	LOAD,
	EDIT,
	DELETE
};

class SaveEntry
{
public:
	static SaveEntry Create(std::filesystem::path _worldPath);

	SaveEntryAction OnMousePressed(sf::Event::MouseButtonEvent _mouse);
	void OnTextEntered(sf::Event::TextEvent _text);
	void Update(float _deltaTime);
	void Draw(sf::RenderTexture& _rt);

	void SetPosition(sf::Vector2f _pos);
	void SetScale(float _scale);

	inline std::filesystem::path GetPath() { return worldPath; }
	inline std::string GetNewName() { return inputName.text; }

private:
	Stellar::ImageButton buttonBackground;
	Stellar::ImageButton buttonEdit;
	Stellar::ImageButton buttonDelete;
	Stellar::ImageButton buttonConfirm;

	Stellar::Textbox inputName;

	Stellar::Text textName;
	Stellar::Text textConfirm;

	bool confirmDeletion = false;
	bool isRenaming = false;
	
	std::filesystem::path worldPath;

};

#endif