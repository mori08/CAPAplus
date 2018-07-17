#include"Search.h"

#include"ControllPanel.h"

#include"Define.h"

#include"BackGround.h"



My::Scene::Search::Search()
	:m_term_first(FontAsset(L"15"),Data::Day::Day().toString(),160,1,Palette::Black)
	,m_term_last (FontAsset(L"15"),Data::Day::Day().toString(),160,1,Palette::Black)
	,m_keywords  (FontAsset(L"10"),L"",380,1,Palette::Black)
{
	m_term_first.setPos(TERM_POINT + Point(110, -12));
	m_term_last.setPos(TERM_POINT + Point(310, -12));
	m_keywords.setPos(KEYWORD_POINT + Point(103, 30));
}



void My::Scene::Search::init()
{
	m_default_text      = L"";

	m_criteria.first    = Data::Day();

	m_criteria.last     = Data::Day();

	m_criteria.plan     = false;

	m_criteria.deadline = false;

	m_criteria.title    = false;

	m_criteria.detail   = false;

	m_criteria.tags     = false;
	
	updateFunc = [this]() { setCriteriaUpdate(); };
}



void My::Scene::Search::update()
{
	updateFunc();
}



void My::Scene::Search::updateFadeIn(double)
{
	
}



void My::Scene::Search::updateFadeOut(double)
{

}



void My::Scene::Search::draw() const
{
	TextureAsset(L"Criteria").drawAt(TERM_POINT);
	FontAsset(L"15")(L"Term").drawAt(TERM_POINT, Palette::Black);
	TextureAsset(L"Term").drawAt(TERM_POINT + Point(290, 0));
	m_term_first.draw();
	m_term_last.draw();

	TextureAsset(L"Criteria").drawAt(TYPE_POINT);
	FontAsset(L"15")(L"Type").drawAt(TYPE_POINT, Palette::Black);
	TextureAsset(m_criteria.plan ? L"CheckOn" : L"Check").drawAt(PLAN_POINT);
	FontAsset(L"20")(L"Plan").drawAt(PLAN_POINT + Point(50, 0), Palette::Black);
	TextureAsset(m_criteria.deadline ? L"CheckOn" : L"Check").drawAt(DEADLINE_POINT);
	FontAsset(L"20")(L"Deadline").drawAt(DEADLINE_POINT + Point(80, 0), Palette::Black);

	TextureAsset(L"Criteria").drawAt(KEYWORD_POINT);
	FontAsset(L"15")(L"Keyword").drawAt(KEYWORD_POINT, Palette::Black);
	TextureAsset(m_criteria.title ? L"CheckOn" : L"Check").drawAt(TITLE_POINT);
	FontAsset(L"20")(L"Title").drawAt(TITLE_POINT + Point(50, 0), Palette::Black);
	TextureAsset(m_criteria.tags ? L"CheckOn" : L"Check").drawAt(TAG_POINT);
	FontAsset(L"20")(L"Tag").drawAt(TAG_POINT + Point(50, 0), Palette::Black);
	TextureAsset(m_criteria.detail ? L"CheckOn" : L"Check").drawAt(MAIN_POINT);
	FontAsset(L"20")(L"Main").drawAt(MAIN_POINT + Point(60, 0), Palette::Black);
	TextureAsset(L"Keyword").draw(KEYWORD_POINT + Point(70, 25));
	m_keywords.draw();
}



void My::Scene::Search::setControlPanelText() const
{
	switch(UI::ControlPanel::Instance().mouseOver())
	{
	case Define::Button::Type::HOME:

		UI::ControlPanel::Instance().changeText(L"「ホーム」に戻ります。");
		UI::ControlPanel::Instance().changeFace(Define::Face::EXCLAMATION);
		return;

	case Define::Button::Type::SEARCH_START:

		UI::ControlPanel::Instance().changeText(L"検索を開始します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::EXCLAMATION);

		return;
	}

	if (m_term_first.mouseOver())
	{
		UI::ControlPanel::Instance().changeText(L"検索期間の先頭の日付を指定します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (m_term_last.mouseOver())
	{
		UI::ControlPanel::Instance().changeText(L"検索期間の末尾の日付を指定します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (Circle(PLAN_POINT, R).mouseOver)
	{
		UI::ControlPanel::Instance().changeText(m_criteria.title ? L"予定を検索します。" : L"予定を検索対象から外します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (Circle(DEADLINE_POINT, R).mouseOver)
	{
		UI::ControlPanel::Instance().changeText(m_criteria.deadline ? L"締切を検索します。" : L"締切を検索対象から外します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (Circle(TITLE_POINT, R).mouseOver)
	{
		UI::ControlPanel::Instance().changeText(m_criteria.deadline ? L"タイトルを検索します。" : L"タイトルを検索対象から外します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (Circle(TAG_POINT, R).mouseOver)
	{
		UI::ControlPanel::Instance().changeText(m_criteria.deadline ? L"タグを検索します。" : L"タグを検索対象から外します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (Circle(MAIN_POINT, R).mouseOver)
	{
		UI::ControlPanel::Instance().changeText(m_criteria.deadline ? L"本文を検索します。" : L"本文を検索対象から外します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	if (m_keywords.mouseOver()) 
	{
		UI::ControlPanel::Instance().changeText(L"キーワードを指定します。");
		UI::ControlPanel::Instance().changeFace(Define::Face::QUESTION);

		return;
	}

	UI::ControlPanel::Instance().changeText(m_default_text);
	UI::ControlPanel::Instance().changeFace(Define::Face::SMILE);
}



bool My::Scene::Search::startSearching()
{
	if (!Data::Day::changeAbleStringToDay(m_term_first.getText()))
	{
		return false;
	}

	if (!Data::Day::changeAbleStringToDay(m_term_last.getText()))
	{
		return false;
	}

	m_criteria.first = Data::Day(m_term_first.getText());

	m_criteria.last  = Data::Day(m_term_last.getText());

	return m_searcher.startSearchThread(m_criteria);
}



void My::Scene::Search::setCriteriaUpdate()
{
	setControlPanelText();

	m_term_first.input();
	m_term_last.input();
	m_keywords.input();

	if (Circle(PLAN_POINT, R).leftClicked) { m_criteria.plan = !m_criteria.plan; }
	if (Circle(DEADLINE_POINT, R).leftClicked) { m_criteria.deadline = !m_criteria.deadline; }
	if (Circle(TITLE_POINT, R).leftClicked) { m_criteria.title = !m_criteria.title; }
	if (Circle(TAG_POINT, R).leftClicked) { m_criteria.tags = !m_criteria.tags; }
	if (Circle(MAIN_POINT, R).leftClicked) { m_criteria.detail = !m_criteria.detail; }

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::SEARCH_START)
	{
		if (startSearching())
		{
			updateFunc = [this]() { waitSearchingUpdate(); };

			UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().SEARCH_WAIT);

			m_default_text = L"";
		}
		else
		{
			m_default_text = L"検索に失敗しました。";
		}
	}

	if (UI::ControlPanel::Instance().buttonClicked() == Define::Button::Type::HOME)
	{
		UI::ControlPanel::Instance().setButtonsType(Define::Button::List::get().HOME);
		UI::BackGound::Instatnce().changeColorPattern(Define::COLOR_PATTERN::COLORFUL);
		changeScene(L"Home");
	}
}



void My::Scene::Search::waitSearchingUpdate()
{
	UI::ControlPanel::Instance().changeText(L"検索中…");

	if (m_searcher.joinSearchThread())
	{
		updateFunc = [this]() { this->showResultUpdate(); };
	}
}



void My::Scene::Search::showResultUpdate()
{
	UI::ControlPanel::Instance().changeText(L"検索を終了しました。");
}
