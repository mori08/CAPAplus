#include"CardBoard.h"



My::UI::CardBoard::CardBoard(const Data::Card & card, const Point & pos, const Point & size, const Point & base_pos)
	:
	m_card(card)
{
	m_pos = m_goal = pos;

	m_size = size;

	m_base_pos = base_pos;
}



Array<My::UI::CardBoard> My::UI::CardBoard::makeList(const Array<Data::Card> & card_list, const Point & pos, const Size & size, const Point & base_pos)
{
	Array<CardBoard> card_board_list;

	for (const auto& card : card_list)
	{
		card_board_list.emplace_back(card, pos, size, base_pos);
	}

	return card_board_list;
}



void My::UI::CardBoard::update()
{
	m_pos.x = (m_pos.x + m_goal.x) >> 1;

	m_pos.y = (m_pos.y + m_goal.y) >> 1;

	Point sub = m_pos - m_goal;

	if (Abs(sub.x) + Abs(sub.y) <= 2)
	{
		m_pos = m_goal;
	}
}



bool My::UI::CardBoard::mouseOver() const
{
	if (Mouse::Pos().x < m_base_pos.x || Mouse::Pos().y < m_base_pos.y) { return false; }
	
	return Rect(m_pos, m_size).mouseOver;
}



bool My::UI::CardBoard::clicked() const
{
	if (Mouse::Pos().x < m_base_pos.x || Mouse::Pos().y < m_base_pos.y) { return false; }

	return Rect(m_pos, m_size).leftClicked;
}



void My::UI::CardBoard::draw1(const String & texture_name) const
{
	TextureAsset(texture_name).draw(m_pos);

	FontAsset(L"10")(m_card.title).draw(m_pos + Point(10, 3), Palette::Black);
}



void My::UI::CardBoard::draw2(const String & texture_name) const
{
	TextureAsset(texture_name).draw(m_pos);

	FontAsset(L"10")(m_card.day.toString()).draw(m_pos + Point(10, 3), Palette::Black);
	
	FontAsset(L"10")(m_card.title).draw(m_pos + Point(20, 23), Palette::Black);
}



void My::UI::CardBoard::draw3(const String & texture_name) const
{
	draw2(texture_name);

	FontAsset(L"10")(m_card.status).draw(m_pos + Point(100, 3), m_card.color);
}



void My::UI::CardBoard::draw4(const String & plan_texture_name, const String & deadline_texture_name) const
{
	if (m_card.deadline_id == -1)
	{
		draw1(plan_texture_name);
	}
	else
	{
		draw1(deadline_texture_name);
	}
}



void My::UI::CardBoard::draw5(const String & plan_texture_name, const String & deadline_texture_name) const
{
	if (m_card.deadline_id == -1)
	{
		draw2(plan_texture_name);
	}
	else
	{
		draw2(deadline_texture_name);
	}
}
