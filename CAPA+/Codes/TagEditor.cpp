#include"TagEditor.h"



// -----------------------------------------------------------------------------------------
//	Tagクラス 
// -----------------------------------------------------------------------------------------



My::UI::Tag::Tag(const Point & pos,const String & text)
	:
	m_pos(pos),
	m_goal(pos),
	m_text(FontAsset(L"10"), text, 190 - 35, 1)
{
	m_text.setPos(pos + Point(35, 6));
}



void My::UI::Tag::update()
{
	m_pos = (m_pos + m_goal) / 2;

	if (Abs((m_pos - m_goal).y) < 2) { m_pos = m_goal; }

	m_text.setPos(m_pos + Point(35, 6));

	m_text.input();
}



void My::UI::Tag::draw()const
{
	if (Rect(m_pos, Size(240, 30)).mouseOver)
	{
		TextureAsset(L"SelectedTag").draw(m_pos);
	}
	else
	{
		TextureAsset(L"Tag").draw(m_pos);
	}

	m_text.draw();
}



// -----------------------------------------------------------------------------------------
//	TagEditorクラス 
// -----------------------------------------------------------------------------------------



My::UI::TagEditor::TagEditor()
	:
	m_add_point(340, 240),
	m_add_goal(340, 240)
{
}



void My::UI::TagEditor::update()
{
	if (Rect(m_add_point + Point(32, 7), Size(16, 16)).leftClicked&&m_tag_list.size() < TAG_LIMIT_NUM)
	{
		m_tag_list.emplace_back(Tag(m_add_point));
	}

	for (auto & tag : m_tag_list)
	{
		tag.update();
	}

	m_add_point = (m_add_point + m_add_goal) / 2;

	if (Abs((m_add_point - m_add_goal).y) < 2) { m_add_point = m_add_goal; }

	Erase_if(m_tag_list, [](Tag & object) {return object.clickedDeleteIcon(); });

	int y = 240;

	for (auto & tag : m_tag_list)
	{
		tag.setGoal(Point(340, y));

		y += 40;
	}

	m_add_goal = Point(340, y);
}



void My::UI::TagEditor::draw() const
{
	for (const auto & tag : m_tag_list)
	{
		tag.draw();
	}

	if (m_tag_list.size() < TAG_LIMIT_NUM)
	{
		TextureAsset(L"AddTag").draw(m_add_point);
	}
}



Array<String> My::UI::TagEditor::getTextList() const
{
	Array<String> text_list;

	for (const auto & tag : m_tag_list)
	{
		text_list.emplace_back(tag.getText());
	}
	
	return text_list;
}



void My::UI::TagEditor::Set(const Array<String>& text_list)
{
	m_tag_list.clear();

	int y = 240;

	for (auto & text : text_list)
	{
		m_tag_list.emplace_back(Tag(Point(340, y), text));

		y += 40;
	}

	m_add_point = Point(340, y);
	m_add_goal = Point(340, y);
}
