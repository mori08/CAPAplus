#include"CardListManager.h"

#include"ControllPanel.h"


const int RIGHT = 1;

const int LEFT = -1;



My::UI::CardListManager::CardListManager(int direction, int num_limit, int card_height, const String & texture_name, const String & card_texture_name)
{
	m_select = -1;

	m_direction = direction;

	m_num_limit = num_limit;

	m_card_height = card_height;

	m_texture_name = texture_name;

	m_card_texture_name = card_texture_name;
}



void My::UI::CardListManager::update()
{
	if (Abs((m_pos - m_goal).x) + Abs((m_pos - m_goal).y) < 2) 
	{ 
		m_pos = m_goal; 
	}
	else
	{
		m_pos = (m_pos + m_goal) / 2;
	}

	for(auto & card : m_card_list)
	{
		card.update();
	}
}



void My::UI::CardListManager::control()
{
	for (int i = 0; i < m_card_list.size(); ++i)
	{
		if (i == m_select) { continue; }

		if (m_card_list[i].mouseOver())
		{
			m_card_list[i].changeGoal(m_pos + Point(30, 45 + m_card_height * i));
		}
		else
		{
			m_card_list[i].changeGoal(m_pos + Point(12, 45 + m_card_height * i));
		}

		if (m_card_list[i].clicked())
		{
			int p = (m_direction == 1) ? Window::Width() : -m_card_list[i].getSize().x;

			m_card_list[i].changeGoal(Point(p, m_pos.y + 45 + m_card_height * i));

			m_select = i;
		}

	}
}



void My::UI::CardListManager::draw(int pattern) const
{
	TextureAsset(m_texture_name + L"_Panel").draw(m_pos, Alpha(128));

	for (const auto & card : m_card_list)
	{
		switch (pattern)
		{
		case 1: card.draw1(m_card_texture_name); break;

		case 2: card.draw2(m_card_texture_name); break;

		case 3: card.draw3(m_card_texture_name); break;

		case 4: card.draw4(L"PlanCard_240x25", L"DeadlineCard_240x25"); break;

		case 5: card.draw5(L"PlanCard_240x45", L"DeadlineCard_240x45"); break;
		}
	}

	TextureAsset(m_texture_name).draw(m_pos);

	FontAsset(L"20")(m_title).draw(m_pos + Point(10, 5), Palette::Black);
}



void My::UI::CardListManager::hide()
{
	int p = (m_direction == 1) ? Window::Width() : -280;

	m_goal = Point(p, m_pos.y);

	for (int i = 0; i < m_card_list.size(); ++i)
	{
		m_card_list[i].changeGoal(Point(p, m_pos.y + 45 + m_card_height * i));
	}
}



My::Data::Card My::UI::CardListManager::getSelectedCard() const
{
	if (m_select == NON_SELECT)
	{
		Println(L"error > カードが選択されていません");

		return Data::Card();
	}
	else
	{
		return m_card_list[m_select].getCard();
	}
}



int My::UI::CardListManager::clicked() const
{
	for (int i = 0; i < m_card_list.size(); ++i)
	{
		if (m_card_list[i].clicked())
		{
			return i;
		}
	}

	return NON_SELECT;
}



bool My::UI::CardListManager::mouseOver() const
{
	for (const auto & card : m_card_list)
	{
		if (card.mouseOver())
		{
			return true;
		}
	}

	return false;
}
