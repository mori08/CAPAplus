#include"Home.h"

#include"Data\DeadlineManager\DeadlineManager.h"

#include"ControllPanel.h"

#include"BackGround.h"

#include"Define.h"


const Point TODAY_POS = Point(40, 120);

const Point TOMORROW_POS = Point(40, 300);

const Point DEADLINE_POS = Point(340, 120);

const size_t PLAN_NUM = 4;

const size_t DEADLINE_NUM = 6;



My::Scene::Home::Home()
	:
	TODAY(),
	m_today_plan   (-1, PLAN_NUM,     30, Define::TextureName::HOME_PLAN_NOTE,     Define::TextureName::HOME_PLAN_CARD),
	m_tomorrow_plan(-1, PLAN_NUM,     30, Define::TextureName::HOME_PLAN_NOTE,     Define::TextureName::HOME_PLAN_CARD),
	m_deadline     (+1, DEADLINE_NUM, 50, Define::TextureName::HOME_DEADLINE_NOTE, Define::TextureName::HOME_DEADLINE_CARD),
	m_detail(Point(640, 100)),
	m_state(State::NORMAL)
{
	Data::Note today_note = Data::Note(Data::Day());

	Data::Note tomorrow_note = Data::Note(Data::Day() + 1);


	m_today_plan.setTitle(L"Today");
	Array<UI::CardBoard> today_plan_list	= UI::CardBoard::makeList(today_note.getPlanList(), TODAY_POS + Point(10, 0), Size(240, 25), TODAY_POS + Point(30, 0));
	m_today_plan.setBoardList(today_plan_list);


	m_tomorrow_plan.setTitle(L"Tomorrow");
	Array<UI::CardBoard> tomorrow_plan_list = UI::CardBoard::makeList(tomorrow_note.getPlanList(), TOMORROW_POS + Point(10, 0), Size(240, 25), TOMORROW_POS + Point(30, 0));
	m_tomorrow_plan.setBoardList(tomorrow_plan_list);


	m_deadline.setTitle(L"Deadline");
	Array<UI::CardBoard> deadline_list = UI::CardBoard::makeList(Data::DeadlineManager::loadNocheckDeadlineList(), DEADLINE_POS + Point(10, 0), Size(240, 45), DEADLINE_POS + Point(30, 0));
	m_deadline.setBoardList(deadline_list);


	m_today_plan.setPos(Point(-280, TODAY_POS.y));
	m_today_plan.setGoal(TODAY_POS);

	m_tomorrow_plan.setPos(Point(-280, TOMORROW_POS.y));
	m_tomorrow_plan.setGoal(TOMORROW_POS);

	m_deadline.setPos(Point(640, DEADLINE_POS.y));
	m_deadline.setGoal(DEADLINE_POS);
}



void My::Scene::Home::update()
{
	static int timer = 0;	// 同期用変数
	
	if (timer > 0) { --timer; }

	m_today_plan.update();

	m_tomorrow_plan.update();

	m_deadline.update();

	if (m_state != State::DEADLINE_DETAIL)
	{
		m_today_plan.control();

		m_tomorrow_plan.control();

		if (m_tomorrow_plan.clicked() != NON_SELECT)
		{
			m_detail.setCard(m_tomorrow_plan.getSelectedCard());

			m_today_plan.clearSelect();
		}

		if (m_today_plan.clicked() != NON_SELECT)
		{
			m_detail.setCard(m_today_plan.getSelectedCard());

			m_tomorrow_plan.clearSelect();
		}

		if (m_today_plan.clicked() != NON_SELECT || m_tomorrow_plan.clicked() != NON_SELECT)
		{
			m_detail.setTitlePos(Point(640, DEADLINE_POS.y + 21), DEADLINE_POS + Point(10, 21));

			changeState(DEADLINE_POS, State::PLAN_DETAIL);
		}
	}

	if (m_state != State::PLAN_DETAIL)
	{
		m_deadline.control();

		if (m_deadline.clicked() != NON_SELECT)
		{
			m_detail.setCard(m_deadline.getSelectedCard());

			m_detail.setTitlePos(Point(-280, TODAY_POS.y + 21), TODAY_POS + Point(10, 21));

			changeState(TODAY_POS, State::DEADLINE_DETAIL);
		}
	}

	if (m_state != State::NORMAL)
	{
		m_detail.update();

		if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::BACK)
		{
			UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().HOME);

			timer = 20;

			if (m_state == State::PLAN_DETAIL) 
			{
				m_today_plan.clearSelect();
				m_tomorrow_plan.clearSelect();

				m_detail.setGoal(Point(640, DEADLINE_POS.y));
				m_detail.setTitleGoal(Point(640, DEADLINE_POS.y));
			}

			if (m_state == State::DEADLINE_DETAIL)
			{
				m_deadline.clearSelect();

				m_detail.setGoal(Point(-280, TODAY_POS.y));
				m_detail.setTitleGoal(Point(-280, TODAY_POS.y));
			}
		}

		if (timer == 1) { m_state = State::NORMAL; }
	}

	setControlPanel();

	controlSceneChange();
}



void My::Scene::Home::updateFadeIn(double)
{
	m_today_plan.update();

	m_tomorrow_plan.update();

	m_deadline.update();

	UI::ControlPanel::Instance().resetMoveButton();
}



void My::Scene::Home::updateFadeOut(double)
{
	m_today_plan.update();

	m_tomorrow_plan.update();

	m_deadline.update();
}



void My::Scene::Home::draw() const
{
	m_today_plan.draw(1);

	m_tomorrow_plan.draw(1);

	m_deadline.draw(2);

	if (m_state == State::PLAN_DETAIL || m_state == State::DEADLINE_DETAIL)
	{
		m_detail.draw();
	}
}



void My::Scene::Home::changeState(const Point & pos, const State & state)
{
	if (m_state != State::NORMAL) { return; }

	if (pos.x > Window::Center().x) { m_detail.setPos(Point(Window::Width(), pos.y)); }

	else { m_detail.setPos(Point(-240, pos.y)); }

	m_detail.setGoal(pos);

	UI::ControlPanel::Instance().setButtonsType(Define::Button::List().get().HOME_DETAIL);

	UI::ControlPanel::Instance().changeButtonStart();

	m_state = state;
}



void My::Scene::Home::setControlPanel()
{

	String text = L"";

	int face_id = Define::Face::SMILE;

	switch (UI::ControlPanel::Instance().mouseOver())
	{
	case Define::Button::CALENDAR:

		text = L"「カレンダー」に移行します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::SEARCH:

		text = L"「検索」に移行します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::DEADLINE:

		text = L"「締切管理」に移行します。";

		face_id = Define::Face::EXCLAMATION;

		break;

	
	case Define::Button::ON:

		text = L"CAPA+を終了します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::BACK:

		text = L"詳細の表示をやめます。";

		face_id = Define::Face::EXCLAMATION;

		break;


	default:

		if (!UI::ControlPanel::Instance().controlAble()) { break; }

		if (m_today_plan.mouseOver() || m_tomorrow_plan.mouseOver())
		{
			text = L"予定の詳細を確認します。";

			face_id = Define::Face::EXCLAMATION;
		}

		if (m_deadline.mouseOver())
		{
			text = L"締切の詳細を確認します。";

			face_id = Define::Face::EXCLAMATION;
		}

		break;

	}


	UI::ControlPanel::Instance().changeText(text);

	UI::ControlPanel::Instance().changeFace(face_id);

}



void My::Scene::Home::controlSceneChange()
{	
	int type = UI::ControlPanel::Instance().buttonClicked();

	if (type == -1) { return; }

	m_today_plan.hide();

	m_tomorrow_plan.hide();

	m_deadline.hide();

	switch (type)
	{

	case Define::Button::CALENDAR:

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().CALENDAR);

		UI::BackGound::Instatnce().changeColorPattern(Define::COLOR_PATTERN::BLUE);

		changeScene(L"Calendar");

		break;

	case Define::Button::SEARCH:

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().SEARCH);

		UI::BackGound::Instatnce().changeColorPattern(Define::COLOR_PATTERN::GREEN);

		changeScene(L"Search");

		break;
	}

}
