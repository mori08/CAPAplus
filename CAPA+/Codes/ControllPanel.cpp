#include"ControllPanel.h"

#include<queue>

#include"Define.h"


// -----------------------------------------------------------------------------------------
//	Faceクラス 
// -----------------------------------------------------------------------------------------


My::UI::Face::Face()
{
	loadGraph();

	m_face_id = 0;

	m_goal = 3;

	searchPath();
}



void My::UI::Face::loadGraph()
{
	CSVReader reader(L"Assets/Data/FaceGraph.csv");
	
	m_graph = Array<Array<int>>(reader.rows);

	m_path	= Array<int>(reader.rows);

	for (int i = 0; i < reader.rows; ++i)
	{
		for (int j = 0; j < reader.rows; ++j)
		{

			if (reader.get<int>(i, j) == -1) { break; }

			m_graph[i].emplace_back(reader.get<int>(i, j));

		}
	}

}



void My::UI::Face::searchPath()
{
	// 幅優先探索

	std::queue<int> Q;

	m_path = Array<int>(m_path.size(), -1);	// 未訪問は-1

	m_path[m_goal] = m_goal;

	Q.push(m_goal);

	while (!Q.empty())
	{
		int p = Q.front();

		Q.pop();

		for (int q : m_graph[p])
		{
			if (m_path[q] != -1) { continue; }

			m_path[q] = p;

			Q.push(q);
		}

	}
}



void My::UI::Face::changeFace(int id)
{
	if (m_goal == id) { return; }

	m_goal = id;

	searchPath();
}



void My::UI::Face::update()
{
	if (m_path[m_face_id] == -1) { return; }

	m_face_id = m_path[m_face_id];
}



void My::UI::Face::draw(const Point& pos) const
{

	TextureAsset(L"Face")((m_face_id % 4) * 40, (m_face_id / 4) * 40, 40, 40).draw(pos);

}




// -----------------------------------------------------------------------------------------
//  ControllPanelクラス
// -----------------------------------------------------------------------------------------


My::UI::ControlPanel::ControlPanel()
{
	m_timer = -1;

	m_buttons_type = Define::Button::List::get().HOME;

	createButton();

	changeButtonStart();

	m_text = L"";

	m_message_pos = m_message_goal = Vec2(640, 95);
}



void My::UI::ControlPanel::update()
{
	static int face_clock = 0;

	m_message_pos = (m_message_pos + m_message_goal) / 2;

	moveButton();

	if (m_timer == -1)
	{
		for (int i = 0; i < m_button_list.size(); ++i)
		{
			if (m_button_list[i].mouseOver() != -1 && Mouse::Pos().y > 60)
			{
				m_button_list[i].changeGoal(Point(80 + i * 50, 100));
			}
			else
			{
				m_button_list[i].changeGoal(Point(80 + i * 50, 80));
			}

			if (m_button_list[i].clicked() != -1 && Mouse::Pos().y > 60)
			{
				m_timer = 0;

				m_sel_button = i;
			}
		}
	}

	if (++face_clock % 5 == 0)
	{
		m_face.update();
	}
}



void My::UI::ControlPanel::draw() const
{
	TextureAsset(L"ControlPanel_bottom").draw();

	m_face.draw(Point(10, 9));

	for (const auto& button : m_button_list)
	{
		button.draw();
	}

	TextureAsset(L"ControlPanel_top").draw();

	TextureAsset(L"MessageBar").draw(m_message_pos);

	drawMessage();

	FontAsset(L"10")(m_text).draw(70, 20, Palette::Black);
}



int My::UI::ControlPanel::mouseOver()const
{
	if (m_timer != -1) { return -1; }

	for (const Button & button : m_button_list)
	{
		int type;

		if ((type = button.mouseOver()) != -1)
		{
			return type;
		}
	}

	return -1;
}



int My::UI::ControlPanel::buttonClicked()const
{
	if (m_timer != 0) { return -1; }

	for (const Button & button:m_button_list)
	{
		int type;

		if ((type = button.clicked()) != -1)
		{
			return type;
		}
	}

	return -1;
}




void My::UI::ControlPanel::moveButton()
{

	for (auto & button : m_button_list)
	{
		button.update();
	}

	if (m_timer == -1) { return; }


	const int CREATE_TIME = 35;
	const int CLEANUP_TIME = 5;

	++m_timer;

	// m_timer==5  からボタンを片づけます。
	setButtonGoal(40, CLEANUP_TIME);

	// m_timer==35 で古いボタンを削除し、新しいボタンを生成します。
	if (m_timer == CREATE_TIME)
	{
		m_button_list.clear();

		createButton();
	}

	// m_timer==35 からボタンを取り出します。
	setButtonGoal(80, CREATE_TIME);

	// m_timer==60 で演出を初期化します。
	if (m_timer == CREATE_TIME + 5 * m_button_list.size())
	{
		m_timer = -1;
	}

}



void My::UI::ControlPanel::setButtonGoal(int goal_y, int timer_0)
{
	int t = m_timer - timer_0;

	if (t%5 == 0 && t/5 >=0 && t/5 < m_button_list.size())
	{
		m_button_list[t / 5].changeGoal(Point(80 + t / 5 * 50, goal_y));
	}
}



void My::UI::ControlPanel::createButton()
{
	if (!m_button_list.empty()) { return; }

	for (int i = 0; i < m_buttons_type.size(); ++i)
	{
		m_button_list.emplace_back(m_buttons_type[i], Point(80 + i * 50, 20));
	}
}



void My::UI::ControlPanel::drawMessage() const
{
	int x = 10;
	
	for (const auto & message : m_message_data)
	{
		FontAsset(message.first)(message.second).draw(m_message_pos + Point(x, -FontAsset(message.first).ascent), Palette::Black);

		x += FontAsset(message.first)(message.second).region().w;
	}
}
