#pragma once

#include"Main.h"

#include"CardListManager.h"

#include"Detail.h"

namespace My
{

	namespace Scene
	{

		/// <summary> �\��̕ҏW�y�[�W </summary>
		class Editor : public MyApp::Scene
		{

		private:

			enum class State
			{
				NORMAL,		// �ʏ�

				DETAIL,		// �ڍו\��

				CREATE_NEW,	// �V�K�쐬

				EDIT		// �ҏW
			};

		private:

			State					m_state;			// ���

			Data::Note				m_note;				// �w�肳�ꂽ���t�̃m�[�g

			UI::CardListManager		m_board_list;		// �\��

			UI::Detail				m_detail;			// �ڍׂ̕\��

		public:

			Editor();

		public:

			/// <summary>
			/// ������
			/// </summary>
			void init();

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

		private:

			/// <summary>
			/// Noraml��Ԃł̍X�V
			/// </summary>
			void updateNormal();

			/// <summary>
			/// Detail��Ԃł̍X�V
			/// </summary>
			void updateDetail();

			/// <summary>
			/// CreateNew��Ԃł̍X�V
			/// </summary>
			void updateCreateNew();

			/// <summary>
			/// Edit��Ԃł̍X�V
			/// </summary>
			void updateEdit();

			/// <summary>
			/// �R���g���[���p�l���ɉ����鏈��
			/// </summary>
			void useControlPanel();

		};

	}

}