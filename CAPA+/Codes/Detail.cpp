#include"Detail.h"

#include"Define.h"



My::UI::Detail::Detail(const Point & pos)
	:
	m_pos(pos),
	m_goal(pos),
	m_title(FontAsset(L"10"), L"", 200, 1),
	m_detail(FontAsset(L"10"), L"", 200, 13)
{
	
}



void My::UI::Detail::update()
{
	m_pos.x = (m_pos.x + m_goal.x) >> 1;

	m_pos.y = (m_pos.y + m_goal.y) >> 1;

	Point sub = m_pos - m_goal;

	if (Abs(sub.x) + Abs(sub.y) <= 2)
	{
		m_pos = m_goal;
	}

	m_title_pos = (m_title_goal + m_title_pos) / 2;

	m_title.setPos(m_title_pos + Point(5, 3));

	m_detail.setPos(m_pos + Point(30, 60));
}



void My::UI::Detail::input()
{
	m_title.input();

	m_detail.input();
	
	m_tag_editor.update();
}



void My::UI::Detail::selectPlanOrDeadline()
{
	if (PLAN_BUTTON.leftClicked) { m_is_plan = true; }

	if (DEADLINE_BUTTON.leftClicked) { m_is_plan = false; }
}



void My::UI::Detail::setCard(const Data::Card & card)
{
	m_card = card;

	m_title.setText(card.title);

	m_detail.setText(card.detail);

	m_tag_editor.Set(card.tags);

	m_is_plan = card.deadline_id == -1;
}



My::Data::Card My::UI::Detail::getCard()
{
	m_card.title	= m_title.getText();

	m_card.detail	= m_detail.getText();

	m_card.tags		= m_tag_editor.getTextList();

	return m_card;
}



void My::UI::Detail::draw() const
{
	String texture_name = m_is_plan ? Define::TextureName::PLAN_DETAIL : Define::TextureName::DEADLINE_DETAIL;

	String card_texture_name = m_is_plan ? Define::TextureName::PLAN_DETAIL_CARD : Define::TextureName::DEADLINE_DETAIL_CARD;

	TextureAsset(texture_name).draw(m_pos);

	FontAsset(L"10")(m_card.day.toString()).draw(m_pos + Point(20, 3));

	m_detail.draw();

	TextureAsset(card_texture_name).draw(m_title_pos);

	m_title.draw();
}



void My::UI::Detail::drawEdit() const
{
	m_tag_editor.draw();

	draw();
}



void My::UI::Detail::drawPlanOrDeadline() const
{
	TextureAsset(L"Plan").draw(PLAN_BUTTON.tl, m_is_plan ? Palette::White : Palette::Gray);

	FontAsset(L"15")(L"Plan").drawAt(PLAN_BUTTON.center, Palette::Black);

	TextureAsset(L"Deadline").draw(DEADLINE_BUTTON.tl, !m_is_plan ? Palette::White : Palette::Gray);

	FontAsset(L"15")(L"Deadline").drawAt(DEADLINE_BUTTON.center, Palette::Black);
}
