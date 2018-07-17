#include"Calendar.h"

#include"ControllPanel.h"

#include"BackGround.h"

#include"Define.h"

#include<queue>


const Point PLAN_POS = Point(40, 120);

const Point DEADLINE_POS = Point(340, 120);




// -----------------------------------------------------------------------------------------
//	CalendarPartクラス 
// -----------------------------------------------------------------------------------------



void My::UI::CalendarPart::update()
{
	std::queue<int> Q;

	if (Abs(m_pos.x - m_goal.x) + Abs(m_pos.y - m_goal.y) <= 2)
	{
		m_pos = m_goal;
	}
	else
	{
		m_pos.x = (m_pos.x + m_goal.x) >> 1;

		m_pos.y = (m_pos.y + m_goal.y) >> 1;
	}
}



void My::UI::CalendarPart::draw() const
{
	TextureAsset(L"CalendarPart_Base").scale(m_scale).draw(m_pos + (m_scale - 1.0)*Point(-30, -25));

	FontAsset(L"10")(m_note.getDay().getDate()).drawCenter(m_pos + Point(30, 10), Palette::White);

	if (!m_note.getPlanList().empty())
	{
		TextureAsset(L"CalendarPart_Plan").draw(m_pos);
	}

	if (!m_note.getDeadlineList().empty())
	{
		TextureAsset(L"CalendarPart_Deadline").draw(m_pos);
	}
}



void My::UI::CalendarPart::changeScale(bool select_able)
{
	if (mouseOver()&&select_able)
	{
		if (m_scale < 8.0 / 7.0) { m_scale += 0.05; }
	}
	else
	{
		if (m_scale > 1.0) { m_scale -= 0.01; }

		else { m_scale = 1.0; }
	}
}



// -----------------------------------------------------------------------------------------
//	Calendarクラス 
// -----------------------------------------------------------------------------------------



My::Scene::Calendar::Calendar()
{
	Data::Day today;
	
	m_year = today.getYear();

	m_month = today.getMonth();

	m_date = 1;

	for (int i = 0; i < 31; ++i)
	{
		m_part_list.emplace_back(today, Point(-60, 100));
	}

	reloadPats();
}



void My::Scene::Calendar::update()
{
	mouseOverControlPanel();

	clickControlPanel();

	updateCalendarSelect();

}



void My::Scene::Calendar::updateFadeIn(double)
{
	UI::ControlPanel::Instance().resetMoveButton();

	for (auto& part : m_part_list)
	{
		part.update();
	}
}



void My::Scene::Calendar::updateFadeOut(double)
{
	for (auto& part : m_part_list)
	{
		part.update();
	}
}



void My::Scene::Calendar::draw() const
{
	static const String DAY_NAME[7] =
	{
		L"Sun",
		L"Mon",
		L"Tues",
		L"Wed",
		L"Thurs",
		L"Fri",
		L"Sat"
	};

	for (int i = 0; i < 7; ++i)
	{
		FontAsset(L"10")(DAY_NAME[i]).drawAt(90 + 80 * i, 125, Palette::Black);
	}

	for (const auto& part : m_part_list)
	{
		part.draw();
	}
}



void My::Scene::Calendar::reloadPats()
{
	int y = 138;

	Data::Day first_day(m_year, m_month, 1);

	for (int i = 0; i < 31; ++i)
	{
		Data::Day day = first_day + i;

		m_part_list[i].reloadNote(day);

		if (i < Data::Day::maxDate(m_year, m_month))
		{
			m_part_list[i].setGoal(Point(60 + day.dayOfWeak() * 80, y));
		}
		else
		{
			m_part_list[i].setGoalX(640);
		}

		if (day.dayOfWeak() == 6)
		{
			y += 55;
		}
	}

	Array<UI::Message> message_data;

	message_data.emplace_back(L"10", ToString(m_year) + L"/ ");

	message_data.emplace_back(L"20", ToString(m_month) + L"月");

	UI::ControlPanel::Instance().changeMessage(message_data);
}



void My::Scene::Calendar::mouseOverControlPanel()
{
	int type = UI::ControlPanel::Instance().mouseOver();

	String	text = L"";

	int		face_id = Define::Face::SMILE;

	switch(type)
	{
	case -1: 

		text = ToString(m_year) + L"年 " + ToString(m_month) + L"月 のカレンダーです";

		break;


	case Define::Button::HOME:

		text = L"「ホーム」に戻ります。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::RIGHT_ARROW:

		text = L"カレンダーを一か月進めます。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::LEFT_ARROW:

		text = L"カレンダーを一か月戻します。";

		face_id = Define::Face::EXCLAMATION;

	}

	UI::ControlPanel::Instance().changeText(text);

	UI::ControlPanel::Instance().changeFace(face_id);
}



void My::Scene::Calendar::clickControlPanel()
{
	int type = UI::ControlPanel::Instance().buttonClicked();

	switch (type)
	{
	case -1: return;

	case Define::Button::HOME:

		for (auto& part : m_part_list)
		{
			part.setGoalX(640);
		}

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().HOME);

		UI::ControlPanel::Instance().hideMessage();

		UI::BackGound::Instatnce().changeColorPattern(Define::COLOR_PATTERN::COLORFUL);

		changeScene(L"Home");

		break;


	case Define::Button::RIGHT_ARROW:

		++m_month;

		if (m_month == 13)
		{
			m_month = 1;

			++m_year;
		}

		reloadPats();

		break;


	case Define::Button::LEFT_ARROW:

		--m_month;

		if (m_month == 0)
		{
			m_month = 12;

			--m_year;
		}

		reloadPats();

		break;

	}
}



void My::Scene::Calendar::updateCalendarSelect()
{
	static int m_timer = 0;

	if (m_timer > 0) 
	{
		if (m_timer == 1)
		{
			changeScene(L"Editor");
			m_data->day = Data::Day(m_year, m_month, m_date);
			UI::ControlPanel::Instance().hideMessage();
		}

		--m_timer; 
	}


	if (m_timer > 0 && m_timer < 10)
	{
		for (auto& part : m_part_list)
		{
			part.setGoalX(-70);
		}
	}


	if (m_timer == 10)
	{
		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_LIST);

		UI::ControlPanel::Instance().changeButtonStart();
	}


	for (const auto& part : m_part_list)
	{
		if (part.clicked() && m_timer == 0)
		{
			m_date = part.getNote().getDay().getDate();

			Point goal = part.getPos();

			for (auto& p : m_part_list) { p.setGoal(goal); }

			m_timer = 20;
		}
	}

	for (auto& part : m_part_list)
	{
		part.update();

		part.changeScale();
	}

}
