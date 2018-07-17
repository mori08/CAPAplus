#pragma once


#include"CardBoard.h"


const int NON_SELECT = -1;


namespace My
{

	namespace UI
	{

		class CardListManager
		{

		private:

			String	m_texture_name;

			String	m_card_texture_name;

			Point	m_pos;			// ���W

			Point	m_goal;			// �ړI�n

			int		m_direction;	// �ړ�����

			String	m_title;		// �^�C�g��

			int		m_num_limit;	// �\���ł���J�[�h�̌��E�l

			Array<CardBoard>	m_card_list;	// �J�[�h�̃��X�g

			int		m_card_height;	// �J�[�h�̍���

			int		m_select;		// �I�����Ă���J�[�h�̎��ʔԍ�

		public:

			/// <summary>
			/// �J�[�h���X�g�}�l�[�W���[�̍쐬
			/// </summary>
			/// <param name="direction"> �B������ </param>
			/// <param name="num_limit"> �\���ł���J�[�h�̌��E�� </param>
			/// <param name="card_height"> �J�[�hUI�̍��� </param>
			/// <param name="texture_name"> UI�̉摜�� </param>
			/// <param name="card_texture_name"> �J�[�hUI�̉摜�� </param>
			CardListManager(int direction, int num_limit, int card_height, const String & texture_name, const String & card_texture_name);

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// ����
			/// </summary>
			void control();

			/// <summary>
			/// �`��
			/// </summary>
			/// <param name="pattern"> �`��p�^�[�� </param>
			void draw(int pattern)const;

			/// <summary>
			/// �B��
			/// </summary>
			void hide();

			/// <summary>
			/// �^�C�g����ݒ肵�܂��B
			/// </summary>
			/// <param name="title"> �^�C�g�� </param>
			void setTitle(const String & title)
			{
				m_title = title;
			}

			/// <summary>
			/// ���W��ݒ肵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void setPos(const Point & pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// �ړI�n��ݒ肵�܂��B
			/// </summary>
			/// <param name="goal"> �ړI�n </param>
			void setGoal(const Point & goal)
			{
				m_goal = goal;
			}

			/// <summary>
			/// �I������Ă���J�[�h�̎��ʔԍ���Ԃ��܂��B
			/// </summary>
			/// <returns> ���ʔԍ� , -1�̂Ƃ��I���Ȃ� </returns>
			int getSelectedId()const
			{
				return m_select;
			}

			/// <summary>
			/// �J�[�h�{�[�h�̃��X�g���Z�b�g���܂��B
			/// </summary>
			void setBoardList(const Array<CardBoard> & card_list)
			{
				m_card_list = card_list;
			}

			/// <summary>
			/// �I������Ă���J�[�h���擾���܂��B
			/// </summary>
			Data::Card getSelectedCard() const;

			/// <summary>
			/// �J�[�h�������ꂽ���ǂ����Ԃ��܂��B
			/// </summary>
			/// <returns> �����ꂽ�ԍ��̔ԍ� , ������Ă��Ȃ��Ȃ��Ƃ� -1 </returns>
			int clicked()const;

			/// <summary>
			/// �J�[�hUI�̏�ɃJ�[�\�������邩�����܂�
			/// </summary>
			bool mouseOver()const;

			/// <summary>
			/// �I�����͂����܂��B
			/// </summary>
			void clearSelect()
			{
				if (m_select != NON_SELECT)
				{
					m_card_list[m_select].changeGoal(m_pos + Point(30, 45 + 30 * m_select));
				}

				m_select = NON_SELECT;
			}

		};

	}

}