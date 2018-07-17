#include "StringInputer.h"



My::UI::StringInputer::StringInputer(Font & font, String text, int width, int line_limit, Color color)
	:
	m_cursol(Point::Zero, Size(1, font.height)),
	m_font(font),
	m_text(text),
	m_color(color),
	m_input_index(NON_SELECT),
	m_width(width),
	m_line_limit(line_limit)
{
	
}



My::UI::StringInputer::StringInputer(Point pos, Font & font, String text, int width, int line_limit, Color color)
	:
	m_pos(pos),
	m_cursol(pos, Size(1, font.height)),
	m_font(font),
	m_text(text),
	m_color(color),
	m_input_index(NON_SELECT),
	m_width(width),
	m_line_limit(line_limit)
{

}



Array<String> My::UI::StringInputer::splitText(const String text,const Font & font, int width)
{
	if (text == L"")
	{
		return Array<String>{L""};
	}

	Array<String> rtn;

	for (auto& t : text.split(L'\n'))
	{
		if (t == L"")
		{
			rtn.emplace_back(L"");

			continue;
		}

		while (t.length != 0)
		{

			const size_t n = font.drawableCharacters(t, width);

			rtn.emplace_back(t.substr(0, n));

			t.erase(0, n);

		}

	}
	
	return rtn;
}



void My::UI::StringInputer::input()
{
	select();
	
	if (m_input_index == NON_SELECT) { return; }

	String text1(m_text.substr(0, m_input_index));				// 選択された地点より前の文字列

	String text2(m_text.substr(m_input_index, String::npos));	// 選択された地点より後の文字列

	String text1_copy = text1;

	Input::GetCharsHelper(text1);

	m_input_index = (int)text1.length;

	m_text = text1 + text2;

	if (changeIndexAtKey() || text1 != text1_copy)
	{
		moveCursol();
	}

	adjustLineNum();
}



void My::UI::StringInputer::draw() const
{
	
	int y = 0;

	for (const auto & text : splitText(m_text, m_font, m_width))
	{
		m_font(text).draw(m_pos + Point(0, y), m_color);

		y += m_font.height;
	}
	
	if (m_input_index == NON_SELECT) { return; }
	
	m_cursol.draw(m_color);
}



void My::UI::StringInputer::select()
{
	if (!Input::MouseL.pressed) { return; }
	
	Array<String> text_list = m_text == L"" ? Array<String>{L""} : m_text.split(L'\n');

	int x = m_pos.x, y = m_pos.y;

	int index = 0;
	
	for (const auto & text : text_list)
	{
		for (const auto & t : splitText(text, m_font, m_width))
		{
			if (y >= Mouse::Pos().y) { break; }

			if (y + m_font.height <= Mouse::Pos().y)
			{
				index += (int)t.length;

				y += m_font.height;

				continue;
			}

			for (int i = 0; i <= t.length; ++i)
			{
				x = m_pos.x + m_font(t.substr(0, i)).region().w;

				if (Mouse::Pos().x <= m_pos.x - 10) { break; }

				int r = (i == t.length) ? m_width : (m_font(t.substr(0, i + 1)).region().w - m_font(t[i]).region().w / 2);

				if (Mouse::Pos().x < (m_pos.x + r))
				{
					m_input_index = index;

					m_cursol.pos = Point(x, y);

					return;
				}

				++index;
			}

			--index;

			y += m_font.height;
		}

		++index;
	}

	m_input_index = NON_SELECT;
}



void My::UI::StringInputer::moveCursol()
{
	Point pos = Point::Zero;

	size_t index = 0;

	for (const auto & text : m_text == L"" ? Array<String>{L""} : m_text.split(L'\n'))
	{
		for (const auto & t : splitText(text, m_font, m_width))
		{
			if (index + t.length >= m_input_index)
			{
				pos.x = m_font(t.substr(0, m_input_index - index)).region().w;

				m_cursol.pos = m_pos + pos;

				return;
			}

			index += t.length;

			pos.y += m_font.height;
		}

		++index;
	}

#ifdef _DEBUG

	Println(L"error > moveCursol()で対応するindexが見つかりません");
	Println(L"index : ", index);

#endif // _DEBUG
}



bool My::UI::StringInputer::changeIndexAtKey()
{
	int index_copy = m_input_index;

	const int SPAN = 3;

	if ((m_key_value > 0 && !Input::KeyRight.pressed) || (m_key_value < 0 && !Input::KeyLeft.pressed) || (Input::KeyLeft.pressed && Input::KeyRight.pressed))
	{
		m_key_value = 0;

		return false;
	}

	m_key_value += Input::KeyRight.pressed - Input::KeyLeft.pressed;

	if (m_key_value == +1 || (m_key_value > +30 && m_key_value % 3 == 0))
	{
		++m_input_index;
	}

	if (m_key_value == -1 || (m_key_value < -30 && m_key_value % 3 == 0))
	{
		--m_input_index;
	}

	if (m_input_index < 0) { m_input_index = 0; }

	if (m_input_index > (int)m_text.length) { m_input_index = (int)m_text.length; }

	return index_copy != m_input_index;
}



void My::UI::StringInputer::adjustLineNum()
{
	if (splitText(m_text, m_font, m_width).size() <= m_line_limit) { return; }

	String copy_text = L"";

	int line_num = 0;

	for (const auto & text : m_text == L"" ? Array<String>{L""} : m_text.split(L'\n'))
	{
		for (const auto & line : splitText(text, m_font, m_width))
		{
			++line_num;

			copy_text += line;

			if (line_num == m_line_limit)
			{
				m_text = copy_text;

				m_input_index = (int)m_text.length;

				moveCursol();

				return;
			}
		}

		copy_text += L"\n";
	}
}
