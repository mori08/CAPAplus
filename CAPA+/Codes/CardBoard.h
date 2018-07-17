#pragma once


#include<Siv3D.hpp>

#include"Data\Note\Note.h"

#include"Data\DeadlineManager\DeadlineManager.h"


namespace My
{

	namespace UI
	{

		/// <summary> �J�[�h(�\������)��UI </summary>
		class CardBoard
		{

		private:

			Point		m_pos;		// ���W

			Point		m_goal;		// �ړ���̍��W

			Point		m_size;		// �T�C�Y

			Point		m_base_pos;	// ����𖳌��ɂ����̓_

			Data::Card	m_card;	// �J�[�h

		public:

			/// <summary>
			/// �J�[�h(�\������)��UI���쐬���܂��B
			/// </summary>
			/// <param name="card"> �J�[�h </param>
			/// <param name="pos"> �������W </param>
			/// <param name="size"> �}�E�X�g�p���̔���̑傫�� </param>
			/// <param name="base_pos"> ����𖳌��ɂ����̓_��ݒ�(�����ݒ�{0,0}) </param>
			CardBoard(const Data::Card& card, const Point& pos, const Point& size = Point(0, 0), const Point& base_pos = Point(0, 0));

			/// <summary>
			/// �J�[�h�{�[�h�̃��X�g���쐬���܂��B
			/// </summary>
			/// <param name="card_list"> �J�[�h�̃��X�g </param>
			/// <param name="pos"> �������W </param>
			/// <param name="size"> �}�E�X�g�p���̔���̑傫�� </param>
			/// <param name="base_pos"> ����𖳌��ɂ����̓_��ݒ�(�����ݒ�{0,0}) </param>
			static Array<CardBoard> makeList(const Array<Data::Card> & card_list, const Point & pos, const Size & size, const Point & base_pos = Point::Zero);

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// ���W��ݒ肵�܂��B
			/// </summary>
			void setPos(const Point& pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// �ړ����ύX���܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void changeGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// �ړI�n��x���W�݂̂�ύX���܂��B
			/// </summary>
			/// <param name="x"> x���W </param>
			void changeGoalX(int x)
			{
				m_goal.x = x;
			}

			/// <summary>
			/// �ړI�n��y���W�݂̂�ύX���܂��B
			/// </summary>
			/// <param name="x"> y���W </param>
			void changeGoalY(int y)
			{
				m_goal.y = y;
			}

			/// <summary>
			/// �T�C�Y���擾���܂��B
			/// </summary>
			Size getSize()const
			{
				return m_size;
			}

			/// <summary>
			/// �J�[�h���擾
			/// </summary>
			/// <returns> �J�[�h </returns>
			Data::Card getCard()const
			{
				return m_card;
			}

			/// <summary>
			/// ��Ƀ}�E�X�J�[�\�������邩�����܂��B
			/// </summary>
			/// <returns> ����Ƃ� true , �Ȃ��Ƃ� false </returns>
			bool mouseOver()const;

			/// <summary>
			/// �}�E�X�ŃN���b�N���ꂽ�������܂��B
			/// </summary>
			/// <returns> �N���b�N���ꂽ�Ƃ� true , �����łȂ��Ƃ��Ƃ� false </returns>
			bool clicked()const;

			/// <summary>
			/// �`��P(�^�C�g�������\��)
			/// </summary>
			/// <param name="texture_name"> �摜�̖��O </param>
			void draw1(const String& texture_name)const;

			/// <summary>
			/// �`��Q(�^�C�g���Ɠ��t�\��)
			/// </summary>
			/// <param name="texture_name"> �摜�̖��O </param>
			void draw2(const String& texture_name)const;

			/// <summary>
			/// �`��R(�^�C�g���Ɠ��t�Ə�Ԃ�\��)
			/// </summary>
			/// <param name="texture_name"> �摜�̖��O </param>
			void draw3(const String& texture_name)const;

			/// <summary>
			/// �`��S(�\��ƒ��؂ŃJ�[�h��ʕ\���F�^�C�g���̂�)
			/// </summary>
			/// <param name="plan_texture_name"> �\��̃J�[�hUI�p�摜�� </param>
			/// <param name="deadline_texture_name"> ���؂̃J�[�hUI�p�摜�� </param>
			void draw4(const String & plan_texture_name, const String & deadline_texture_name)const;

			/// <summary>
			/// �`��T(�\��ƒ��؂ŃJ�[�h��ʕ\���F�^�C�g���Ɠ��t��\��)
			/// </summary>
			/// <param name="plan_texture_name"> �\��̃J�[�hUI�p�摜�� </param>
			/// <param name="deadline_texture_name"> ���؂̃J�[�hUI�p�摜�� </param>
			void draw5(const String & plan_texture_name, const String & deadline_texture_name)const;

		};

	}

}