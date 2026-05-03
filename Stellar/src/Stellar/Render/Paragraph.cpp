#include "Paragraph.h"

namespace Stellar
{
	Paragraph Paragraph::Create(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize)
	{
		Paragraph paragraph;
		paragraph.pos = _pos;
		paragraph.fontPath = _fontPath;
		paragraph.scale = 1.f;
		paragraph.text = Text::Create(_fontPath, "", _pos);
		paragraph.SetCharacterSize(_fontSize);

		std::wstring content = _content.toWideString();
		std::wistringstream stream(content);

		size_t start = 0;
		size_t pos = content.find(L"\\n");

		while (pos != std::wstring::npos) {
			std::wstring line = content.substr(start, pos - start);
			paragraph.strings.push_back(sf::String(line));
			start = pos + 2;
			pos = content.find(L"\\n", start);
		}

		if (start < content.size()) {
			std::wstring line = content.substr(start);
			paragraph.strings.push_back(sf::String(line));
		}

		return paragraph;
	}

	Paragraph Paragraph::CreateCentered(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize)
	{
		Paragraph paragraph = Create(_fontPath, _content, _pos, _fontSize);
		paragraph.isCentered = true;
		paragraph.Center();
		return paragraph;
	}

	void Paragraph::Center()
	{
		text.Center();
	}

	void Paragraph::SetScale(float _scale)
	{
		scale = _scale;
		text.frontText.setScale({ _scale, _scale });
	}

	void Paragraph::SetPosition(sf::Vector2f _pos)
	{
		pos = _pos;
		text.SetPosition(pos);
	}

	void Paragraph::SetCharacterSize(unsigned int _size)
	{
		fontSize = _size;
		text.SetCharacterSize(_size);
	}

	void Paragraph::SetString(const sf::String& _content)
	{
		strings.clear();
		std::wstring content = _content.toWideString();

		size_t start = 0;
		size_t strPos = content.find(L"\\n");

		while (strPos != std::wstring::npos) {
			std::wstring line = content.substr(start, strPos - start);
			strings.push_back(sf::String(line));

			start = strPos + 2;
			strPos = content.find(L"\\n", start);
		}

		if (start < content.size()) {
			std::wstring line = content.substr(start);
			strings.push_back(sf::String(line));
		}
	}

	void Paragraph::Draw(sf::RenderTexture& _rt)
	{
		float lineHeight = fontSize * 1.2f * scale;
		float currentY = pos.y;

		for (sf::String s : strings)
		{
			text.SetString(s);
			text.SetPosition({ pos.x, currentY });
			if (isCentered)
			{
				text.Center();
			}
			text.Draw(_rt);

			currentY += lineHeight;
		}
	}
}