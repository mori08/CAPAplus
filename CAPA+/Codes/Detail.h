#pragma once


#include"Data\Day\Day.h"

#include"Data\Note\Note.h"

#include"Data\DeadlineManager\DeadlineManager.h"

#include"CardBoard.h"

#include"StringInputer.h"

#include"TagEditor.h"



namespace My
{

	namespace UI
	{

		/// <summary> �\��ƒ��؂̏ڍׂ̕\����ҏW���s�� </summary>
		class Detail
		{

		private:

			Point		m_pos;		// ���W

			Point		m_goal;		// �ړI���W

			Point m_title_pos, m_title_goal;

			Data::Card	m_card;		// �J�[�h

			bool		m_is_plan;	// �\��̂Ƃ�true , �����łȂ��Ƃ� false

			StringInputer m_title;	// �^�C�g��

			StringInputer m_detail;	// �ڍ�

			TagEditor m_tag_editor;	// �^�O�̃G�f�B�^
			

		private:

			const Rect PLAN_BUTTON = Rect(340, 140, 120, 40);

			const Rect DEADLINE_BUTTON = Rect(480, 140, 120, 40);

		public:

			/// <summary> �ڍג񎦗p��UI���쐬���܂��B </summary>
			/// <param name="pos"> ���W </param>
			Detail(const Point& pos);

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// ����
			/// </summary>
			void input();

			/// <summary>
			/// �\�肩���؂���I�����܂��B
			/// </summary>
			void selectPlanOrDeadline();

			/// <summary>
			/// ���W��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void setPos(const Point& pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// �ړI���W��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void setGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// �^�C�g���\�����W��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			/// <param name="goal"> �ړI </param>
			void setTitlePos(const Point& pos,const Point& goal)
			{
				m_title_pos = pos;

				m_title_goal = goal;
			}

			/// <summary>
			/// �^�C�g���\���̖ړI���W��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> �ړI�n </param>
			void setTitleGoal(const Point& pos)
			{
				m_title_goal = pos;
			}

			/// <summary>
			/// ��ʊO�ɉB�����߂ɃS�[����ݒ肵�܂��B
			/// </summary>
			void hide()
			{
				m_goal.x = m_title_goal.x = Window::Width();
			}

			/// <summary>
			/// �J�[�h��ݒ肵�܂��B
			/// </summary>
			/// <param name="card"> �J�[�h </param>
			void setCard(const Data::Card & card);

			/// <summary>
			/// �J�[�h���擾���܂��B
			/// </summary>
			/// <returns> �J�[�h </returns>
			Data::Card getCard();

			/// <summary>
			/// �`��
			/// </summary>
			/// <param name="texture_name"> ���ʔԍ� </param>
			/// <param name="card_texture_name"> �J�[�h </param>
			/// <param name="card"> ���t </param>
			void draw() const;

			/// <summary>
			/// Edit�p�̕`��
			/// </summary>
			void drawEdit() const;

			/// <summary>
			/// �\��ƒ��؂̑I��p��UI��`��
			/// </summary>
			void drawPlanOrDeadline() const;

			/// <summary>
			/// �Ǘ����Ă���J�[�h���\�肩���؂���Ԃ��܂��B
			/// </summary>
			/// <returns> �\��̂Ƃ� true , ���؂̂Ƃ� false </returns>
			bool IsPlan() const
			{
				return m_is_plan;
			}

		};

	}

}