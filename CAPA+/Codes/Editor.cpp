#include"Editor.h"

#include"ControllPanel.h"

#include"Define.h"



const Point CARD_LIST_POS = Point(40, 120);

const Point DETAIL_POS = Point(340, 120);



My::Scene::Editor::Editor()
	:
	m_state(State::NORMAL),
	m_note(),
	m_detail(Point(640, 0)),
	m_board_list(-1, 10, 30, Define::TextureName::EDIT_NOTE, L"")
{
	
}



void My::Scene::Editor::init()
{
	m_note.load(m_data->day);

	m_board_list.setTitle(m_data->day.toString());
	Array<Data::Card> card_list = m_note.getPlanAndDeadlineList();
	m_board_list.setBoardList(UI::CardBoard::makeList(card_list, CARD_LIST_POS, Size(240, 25), CARD_LIST_POS + Point(30, 0)));

	m_board_list.setPos(Point(-280, CARD_LIST_POS.y));
	m_board_list.setGoal(CARD_LIST_POS);
}



void My::Scene::Editor::update()
{
	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::CALENDAR)
	{
		m_board_list.hide();

		m_detail.hide();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().CALENDAR);

		changeScene(L"Calendar");

		return;
	}

	m_board_list.update();

	m_detail.update();

	switch(m_state)
	{
	case State::NORMAL:		updateNormal();		break;

	case State::DETAIL:		updateDetail();		break;

	case State::CREATE_NEW:	updateCreateNew();	break;

	case State::EDIT:		updateEdit();		break;
	}

	useControlPanel();
}



void My::Scene::Editor::updateFadeIn(double)
{
	m_board_list.update();

	UI::ControlPanel::Instance().resetMoveButton();
}



void My::Scene::Editor::updateFadeOut(double)
{
	m_board_list.update();

	m_detail.update();
}



void My::Scene::Editor::draw() const
{
	m_board_list.draw(4);

	switch(m_state)
	{
	case State::CREATE_NEW:

		m_detail.drawPlanOrDeadline();

	case State::EDIT:

		m_detail.drawEdit();

		break;

	default:

		m_detail.draw();

	}
}



void My::Scene::Editor::updateNormal()
{
	m_board_list.control();

	if (m_board_list.clicked() != NON_SELECT)
	{
		m_detail.setCard(m_board_list.getSelectedCard());

		m_detail.setTitlePos(Point(640, DETAIL_POS.y + 21), DETAIL_POS + Point(10, 21));

		m_detail.setPos(Point(Window::Width(), DETAIL_POS.y));

		m_detail.setGoal(DETAIL_POS);

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List().get().EDIT_DETAIL);

		UI::ControlPanel::Instance().changeButtonStart();

		m_state = State::DETAIL;
	}

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::ADD)
	{
		m_detail.setCard(Data::createNewCard(m_note.getDay()));

		m_detail.setTitlePos(Point(640, CARD_LIST_POS.y + 21), CARD_LIST_POS + Point(10, 21));

		m_detail.setPos(Point(Window::Width(), DETAIL_POS.y));

		m_detail.setGoal(CARD_LIST_POS);

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List().get().EDIT_EDIT);

		UI::ControlPanel::Instance().changeButtonStart();

		m_state = State::CREATE_NEW;
	}
}



void My::Scene::Editor::updateDetail()
{
	m_board_list.control();

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::WRITE)
	{
		m_detail.setGoal(CARD_LIST_POS);

		m_detail.setTitleGoal(CARD_LIST_POS + Point(10, 21));

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_EDIT);

		m_state = State::EDIT;
	}

	if (m_board_list.clicked() != NON_SELECT)
	{
		m_detail.setCard(m_board_list.getSelectedCard());

		m_detail.setTitlePos(Point(640, DETAIL_POS.y + 21), DETAIL_POS + Point(10, 21));
	}

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::ADD)
	{
		m_detail.setCard(Data::createNewCard(m_note.getDay()));

		m_detail.setTitlePos(Point(640, CARD_LIST_POS.y + 21), CARD_LIST_POS + Point(10, 21));

		m_detail.setGoal(CARD_LIST_POS);

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List().get().EDIT_EDIT);

		UI::ControlPanel::Instance().changeButtonStart();

		m_state = State::CREATE_NEW;
	}

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::DELETE)
	{
		Data::DeadlineManager::deleteDeadline(m_detail.getCard().deadline_id);

		m_note.deleteCard(m_board_list.getSelectedId());

		m_note.write();

		m_detail.hide();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List().get().EDIT_LIST);

		UI::ControlPanel::Instance().changeButtonStart();

		m_state = State::NORMAL;
	}
}



void My::Scene::Editor::updateCreateNew()
{
	m_detail.input();

	m_detail.selectPlanOrDeadline();

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::BACK)
	{
		m_detail.hide();

		m_board_list.clearSelect();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_LIST);

		m_state = State::NORMAL;
	}

	if (UI::ControlPanel::Instance().buttonClicked() == (Define::Button::Type::SAVE))
	{
		Data::Card card = m_detail.getCard();

		if (!m_detail.IsPlan())
		{
			card.deadline_id = Data::DeadlineManager::addDeadline(card.day);
		}

		m_note.addCard(card);

		m_note.write();

		m_board_list.setBoardList(UI::CardBoard::makeList(m_note.getPlanAndDeadlineList(), CARD_LIST_POS, Size(240, 25), CARD_LIST_POS + Point(30, 0)));

		m_detail.hide();

		m_board_list.clearSelect();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_LIST);

		m_state = State::NORMAL;
	}
}



void My::Scene::Editor::updateEdit()
{
	m_detail.input();

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::BACK)
	{
		m_detail.hide();

		m_board_list.clearSelect();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_LIST);

		m_state = State::NORMAL;
	}

	if (UI::ControlPanel::Instance().buttonClicked() == (Define::Button::Type::SAVE))
	{
		Data::Card card = m_detail.getCard();

		m_note.changeCard(m_board_list.getSelectedId(), card);

		m_note.write();

		m_board_list.setBoardList(UI::CardBoard::makeList(m_note.getPlanAndDeadlineList(), CARD_LIST_POS, Size(240, 25), CARD_LIST_POS + Point(30, 0)));

		m_detail.hide();

		m_board_list.clearSelect();

		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().EDIT_LIST);

		m_state = State::NORMAL;
	}
}



void My::Scene::Editor::useControlPanel()
{
	String	text = m_note.getDay().toString() + L"のノートです。";

	int		face_id = Define::Face::SMILE;

	switch (UI::ControlPanel::Instance().mouseOver())
	{
	case Define::Button::ADD:

		text = L"新規作成します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::CALENDAR:

		text = L"カレンダーへ移行します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::WRITE:

		text = L"編集します。";

		face_id = Define::Face::EXCLAMATION;

		break;


	case Define::Button::DELETE:

		text = L"削除します。";

		face_id = Define::Face::EXCLAMATION;

		break;

	case Define::Button::SAVE:

		text = L"保存します。";

		face_id = Define::Face::EXCLAMATION;

		break;

	case Define::Button::BACK:

		if (m_state == State::CREATE_NEW)
		{
			text = L"ノートを破棄して戻ります。";
		}
		else
		{
			text = L"変更を破棄して戻ります。";
		}

		face_id = Define::Face::EXCLAMATION;

		break;

	}

	UI::ControlPanel::Instance().changeText(text);

	UI::ControlPanel::Instance().changeFace(face_id);
}
