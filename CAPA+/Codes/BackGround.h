#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace UI
	{

		/// <summary> �w�i�œ����A </summary>
		class Bubble
		{

		private:

			Circle	m_circle;	// �~

			Color	m_color;	// �F

			Vec2	m_speed;	// ���x

		public:

			/// <summary>
			/// �A�𐶐����܂��B
			/// </summary>
			/// <param name="x"> ����x���W </param>
			/// <param name="r"> ���a </param>
			/// <param name="c"> �F </param>
			Bubble(double x, double r, Color c)
				:
				m_circle(x, 480 + r, r),
				m_color(c, 2 * (int)r),
				m_speed(0, -r*r / 8000.0)
			{ }

			/// <summary>
			/// �\�[�g�p��r���Z�q�i���s�v�Z�j
			/// </summary>
			bool operator < (const Bubble& bubble)const
			{
				return m_circle.r < bubble.m_circle.r;
			}

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update()
			{
				m_circle.center += m_speed;
			}

			/// <summary>
			/// �폜
			/// </summary>
			bool eraser()const
			{
				return
					m_circle.y + m_circle.r < 0 ||
					m_circle.y - m_circle.r > Window::Height() ||
					m_circle.x + m_circle.r < 0 ||
					m_circle.y - m_circle.r > Window::Width();
			}

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const
			{
				m_circle.draw(m_color);
			}

			/// <summary>
			/// ���x��ݒ肵�܂��B
			/// </summary>
			/// <param name="speed"> ���x </summary>
			void setSpeed(const Vec2 & speed)
			{
				m_speed = (m_circle.r*m_circle.r / 400.0)*speed;
			}

		};



		/// <summary> �w�i </summary>
		class BackGound
		{

		private:

			Array<Color>	m_color_array;	// �F�̃��X�g

			Array<Bubble>	m_bubble_list;	// �A�̃��X�g

		public:

			BackGound();

			/// <summary>
			/// �C���X�^���X
			/// </summary>
			static BackGound& Instatnce()
			{
				static BackGound instance;

				return instance;
			}

			/// <summary>
			/// �`��ƍX�V
			/// </summary>
			void updateAndDraw()
			{
				update();

				draw();
			}

			/// <summary>
			/// ���������A�̐F��ύX���܂��B
			/// </summary>
			void changeColorPattern(const Array<Color> & color_pattern);

		private:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const;

			/// <summary>
			/// �o�u���̐���
			/// </summary>
			void generateBubble();

			/// <summary>
			/// �F�̑I��
			/// </summary>
			Color selectColor();

		};

	}

}