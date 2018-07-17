#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace UI
	{

		class StringInputer
		{

		private:

			Point	m_pos;			// ���W

			Rect	m_cursol;		// �J�[�\��

			int		m_input_index;	// ���͈ʒu

			Font	m_font;			// �t�H���g

			String	m_text;			// �e�L�X�g

			Color	m_color;		// �F

			int		m_time;			// ����

			int		m_width;		// ��

			int		m_line_limit;	// �s�̌��E�l

			int		m_key_value;	// ���E�L�[�̉����ꂽ���� (+ �E , - ��)

			static const int NON_SELECT = -1;

		public:

			/// <summary>
			/// ���͉\�ȕ�����t�h�̍쐬
			/// </summary>
			/// <param name="font"> �t�H���g </param>
			/// <param name="text"> ���������� </param>
			/// <param name="break_able"> ���s�\�� </param>
			/// <param name="width"> �� </width>
			/// <param name="color"> ������\�����̐F </param>
			StringInputer(Font & font, String text, int width, int line_limit, Color color = Palette::Black);

			/// <summary>
			/// ���͉\�ȕ�����t�h�̍쐬
			/// </summary>
			/// <param name="pos"> �\�����W </param>
			/// <param name="font"> �t�H���g </param>
			/// <param name="text"> ���������� </param>
			/// <param name="break_able"> ���s�\�� </param>
			/// <param name="width"> �� </width>
			/// <param name="color"> ������\�����̐F </param>
			StringInputer(Point pos, Font & font, String text, int width, int line_limit, Color color = Palette::Black);

			/// <summary>
			/// �e�L�X�g��\�����邽�߂ɉ��s�����ŕ������܂��B
			/// </summary>
			/// <param name="width"> �� </param>
			static Array<String> splitText(const String text, const Font & font, int width);

		public:

			/// <summary>
			/// �������ݒ�
			/// </summary>
			/// <param name="text"> ������ </param>
			void setText(const String & text)
			{
				m_text = text;
			}
			
			/// <summary>
			/// ��������擾
			/// </summary>
			/// <returns> ������ </returns>
			String getText() const
			{
				return m_text;
			}

			/// <summary>
			/// ���W���擾���܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void setPos(const Point & pos)
			{
				m_pos = pos;
			}

			/// <summary>
			/// ���͂ł���͈͂ɃJ�[�\�������邩�����܂��B
			/// </summary>
			/// <returns> �J�[�\��������Ƃ� true , �����łȂ��Ƃ� false </returns>
			bool mouseOver()const
			{
				return Rect(m_pos, m_width, m_line_limit*m_font.height).mouseOver;
			}

			/// <summary>
			/// ���͂��s��
			/// </summary>
			void input();

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const;

		private:

			/// <summary>
			/// ���͉ӏ��̑I��
			/// </summary>
			void select();

			/// <summary>
			/// �J�[�\�����ړ������܂��B
			/// </summary>
			void moveCursol();

			/// <summary>
			/// ���E�L�[�ŃC���f�b�N�X��ύX���܂��B
			/// </summary>
			/// <returns> �ύX���ꂽ�ꍇ true , �����łȂ��Ƃ� false </returns>
			bool changeIndexAtKey();

			/// <summary>
			/// �s���𒲐����܂��B
			/// </summary>
			void adjustLineNum();

		};

	}

}