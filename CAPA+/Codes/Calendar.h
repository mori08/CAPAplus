#pragma once


#include"Data\Note\Note.h"

#include"Main.h"

#include"CardBoard.h"



namespace My
{

	namespace UI
	{

		/// <summary> �J�����_�[���\������p�[�c </summary>
		class CalendarPart
		{

		private:

			Point		m_pos;		// ���W

			Point		m_goal;		// �ړI���W

			Data::Note	m_note;		// �m�[�g

			double		m_scale;	// �{��

			const Point SIZE = Point(60, 40);

		public:

			/// <summary>
			/// �J�����_�[�̃p�[�c
			/// </summary>
			/// <param name="day"> ���t </param>
			/// <param name="pos"> ���W </param>
			CalendarPart(const Data::Day& day, const Point& pos)
				:
				m_note(day),
				m_pos(pos),
				m_goal(pos),
				m_scale(1.0)
			{

			}

		public:

			/// <summary>
			/// �X�V���܂��B
			/// </summary>
			void update();

			/// <summary>
			/// �`�悵�܂��B
			/// </summary>
			void draw()const;

			/// <summary>
			/// ��Ƀ}�E�X�J�[�\�������邩�����܂��B
			/// </summary>
			/// <returns> ����Ƃ� true , �Ȃ��Ƃ� false </returns>
			bool mouseOver()const
			{
				return Rect(m_pos, SIZE).mouseOver;
			}

			/// <summary>
			/// �}�E�X�ŃN���b�N���ꂽ�������܂��B
			/// </summary>
			/// <returns> �N���b�N���ꂽ�Ƃ� true , �����łȂ��Ƃ��Ƃ� false </returns>
			bool clicked()const
			{
				return Rect(m_pos, SIZE).leftClicked;
			}

			/// <summary>
			/// �m�[�g���擾���܂��B
			/// </summary>
			/// <returns> �m�[�g </returns>
			Data::Note getNote()const
			{
				return m_note;
			}

			/// <summary>
			/// �ړI�n��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void setGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// �ړI�n��X���W��ݒ肵�܂��B
			/// </summary>
			/// <param name="x"> x </param>
			void setGoalX(int x)
			{
				m_goal.x = x;
			}

			/// <summary>
			/// ���W���擾���܂��B
			/// </summary>
			Point getPos()const
			{
				return m_pos;
			}

			/// <summary>
			/// �m�[�g��V�������t�ōēǂݍ��݂��܂��B
			/// </summary>
			/// <param name="day"> ���t </param>
			void reloadNote(const Data::Day& day)
			{
				m_note = Data::Note(day);
			}

			/// <summary>
			/// �{����ύX���܂��B
			/// </summary>
			/// <param name="select_able"> �I�ׂ�Ƃ� true �A�����łȂ��Ƃ� false </param>
			void changeScale(bool select_able = true);

		};

	}



	namespace Scene
	{

		/// <summary> �J�����_�[�V�[�� </summary>
		class Calendar : public MyApp::Scene
		{

		private:

			int m_year;		// �\�����Ă���N

			int m_month;	// �\�����Ă��錎

			int m_date;		// �I�����Ă����

			Array<UI::CalendarPart> m_part_list;	// �p�[�c���X�g

		public:

			Calendar();

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update()override;

			/// <summary>
			/// �t�F�[�h�C�����̍X�V
			/// </summary>
			void updateFadeIn(double)override;

			/// <summary>
			/// �t�F�[�h�A�E�g���̍X�V
			/// </summary>
			void updateFadeOut(double)override;

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const override;

			/// <summary>
			/// �t�F�[�h�C�����̕`��
			/// </summary>
			void drawFadeIn(double)const override
			{
				draw();
			}

			/// <summary>
			/// �t�F�[�h�A�E�g���̕`��
			/// </summary>
			void drawFadeOut(double)const override
			{
				draw();
			}

			/// <summary>
			/// �p�[�c�𐶐����܂��B
			/// </summary>
			void reloadPats();

			/// <summary>
			/// �J�[�\�����R���g���[���p�l���̃{�^���̏�ɂ���Ƃ��̏������s���܂��B
			/// </summary>
			void mouseOverControlPanel();

			/// <summary>
			/// �R���g���[���p�l���̃{�^�����N���b�N�����Ƃ��̏������s���܂��B
			/// </summary>
			void clickControlPanel();

			/// <summary>
			/// CALENDAR_SELECT�̏�Ԃł̍X�V���s���܂��B
			/// </summary>
			void updateCalendarSelect();

		};

	}

}