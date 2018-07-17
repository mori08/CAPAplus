#include "BackGround.h"

#include "Define.h"



My::UI::BackGound::BackGound()
	:
	m_color_array(Define::COLOR_PATTERN::COLORFUL)
{

}



void My::UI::BackGound::changeColorPattern(const Array<Color>& color_pattern)
{
	for (auto & bubble : m_bubble_list)
	{
		double angle = Random(2 * Pi);

		bubble.setSpeed(Vec2(Cos(angle), Sin(angle)));
	}

	m_color_array = color_pattern;
}



void My::UI::BackGound::update()
{
	generateBubble();

	for (Bubble& bubble : m_bubble_list)
	{
		bubble.update();
	}
	
	Erase_if(m_bubble_list, [](const Bubble bubble) { return bubble.eraser(); });

	std::sort(m_bubble_list.begin(), m_bubble_list.end());

}



void My::UI::BackGound::draw() const
{

	Window::ClientRect().draw(Color(240));

	for (const Bubble& bubble : m_bubble_list)
	{
		bubble.draw();
	}

	Rect(10, 0, 620, 475).draw(Color(240, 190));

}



void My::UI::BackGound::generateBubble()
{
	static int rand_max = 0;
	
	if (Random(rand_max) == 0)
	{
		rand_max += 100;

		double x = Random(0.0, 640.0);

		double r = Random(30.0, 70.0);

		Color c = selectColor();
		
		m_bubble_list.emplace_back(Bubble(x, r, c));
	}
	else
	{
		--rand_max;
	}
}



Color My::UI::BackGound::selectColor()
{
	static const int COLOR_NUM = 7;

	static int color_value[COLOR_NUM] =
	{
		3,3,3,3,3,3,3
	};

	int total = 0;

	for (int i = 0; i < COLOR_NUM; ++i) { total += color_value[i]; }

	int r = Random(total - 1);

	for (int i = 0; i < COLOR_NUM; ++i)
	{
		if (r < color_value[i])
		{
			for (int j = 0; j < COLOR_NUM; ++j)
			{
				if (i == j) { color_value[j] = 0; }

				else { color_value[j] += 1; }
			}

			return m_color_array[i];
		}

		r -= color_value[i];
	}

	return Color(240);
}
