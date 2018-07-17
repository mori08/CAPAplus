#pragma once


#include"Main.h"

#include"ControllPanel.h"

#include"CardBoard.h"

#include"CardListManager.h"

#include"Detail.h"


namespace My
{

	namespace Scene
	{

		/// <summary> �z�[����� </summary>
		class Home : public MyApp::Scene
		{

		private:

			enum class State
			{
				NORMAL,				// �ʏ펞

				PLAN_DETAIL,		// �\��̏ڍ�

				DEADLINE_DETAIL		// ���؂̏ڍ�
			};

		private:

			const Data::Day TODAY;			// ����

			UI::CardListManager m_today_plan;		// �����̗\��̃J�[�h�Ǘ�

			UI::CardListManager m_tomorrow_plan;	// �����̗\��̃J�[�h�Ǘ�

			UI::CardListManager m_deadline;			// ���؂̃J�[�h�Ǘ�

			UI::Detail	m_detail;			// �ڍו\���pUI

			State		m_state;			// ���

		public:

			Home();

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
			/// �t�F�[�h�C�����̍X�V
			/// </summay>
			void drawFadeIn(double)const override
			{
				draw();
			}

			/// <summary>
			/// �t�F�[�h�A�E�g���̍X�V
			/// </summary>
			void drawFadeOut(double)const override
			{
				draw();
			}

		private:

			/// <summary>
			/// ��Ԃ�ύX���܂��B
			/// </summary>
			/// <param name="pos"> �ڍׂ�\����������W </param>
			/// <param name="state"> ��� </param>
			/// <param name="button_list"> �{�^���̃��X�g </param>
			void changeState(const Point & pos, const State & state);

			/// <summary>
			/// ControlPanel��Face,text��ύX
			/// </summary>
			void setControlPanel();

			/// <summary>
			/// �V�[���`�F���W�������܂��B
			/// </summary>
			void controlSceneChange();

		};

	}

}