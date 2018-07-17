#pragma once


#include<Siv3D.hpp>

#include<unordered_map>


namespace My
{
	namespace UI
	{

		/// <summary> ControllPanel�Ŏg�p����{�^�� </summary>
		class Button
		{

		private:

			static const int SIZE_X = 40;	// �{�^����X�T�C�Y

			static const int SIZE_Y = 60;	// �{�^����Y�T�C�Y

		private:

			int		m_type;	// ���

			Point	m_pos;	// �{�^���̍��W

			Point	m_goal;	// �ړI�n�̏ꏊ

			
		public:

			/// <summary>
			/// �{�^�����쐬���܂��B
			/// </summary>
			/// <param name="type"> ��� </param>
			/// <param name="pos"> ���W </param>
			Button(int type, const Point& pos)
			{
				m_type = type;

				m_pos = m_goal = pos;

				Rect().mouseOver;
			}

			/// <summary>
			/// �ړI�n��ύX���܂��B
			/// </summary>
			/// <param name="pos"> ���W </param>
			void changeGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// ���W���X�V���܂��B
			/// </summary>
			void update()
			{
				m_pos.x = (int)((m_pos.x + 0.3*m_goal.x) / 1.3);

				m_pos.y = (int)((m_pos.y + 0.5*m_goal.y) / 1.5);
			}

			/// <summary>
			/// �{�^���̏�Ƀ}�E�X�J�[�\�������邩�����܂��B
			/// </summary>
			/// <returns> ����Ƃ� true , �Ȃ��Ƃ� false </returns>
			int mouseOver()const
			{
				if (Rect(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3, SIZE_X, SIZE_Y).mouseOver)
				{
					return m_type;
				}

				return -1;
			}

			/// <summary>
			/// �{�^�����N���b�N���ꂽ�������܂��B
			/// </summary>
			/// <returns> �����ꂽ�Ƃ�type��Ԃ��܂� , ������ĂȂ��Ƃ� -1 </returns>
			int clicked()const
			{
				if (Rect(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3, SIZE_X, SIZE_Y).leftClicked)
				{
					return m_type;
				}

				return -1;
			}

			/// <summary>
			/// �`�悵�܂�
			/// </summary>
			void draw()const
			{
				TextureAsset(L"Buttons")(m_type % 4 * SIZE_X, m_type / 4 * SIZE_Y, SIZE_X, SIZE_Y).draw(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3);
			}


		};




		/// <summary> ControlPanel��Ŏg�p����� </summary>
		class Face
		{

		private:

			int m_face_id;							// ���ݕ\�����Ă����̎��ʔԍ�

			int m_goal;								// �\����������

			Array<Array<int>> m_graph;				// �O���t�\��

			Array<int> m_path;						// �o�H���L��


		public:

			/// <summary>
			/// ��UI���쐬���܂��B
			/// </summary>
			Face();

			/// <summary>
			/// �O���t�\����CSV�t�@�C�����烍�[�h���܂��B
			/// </summary>
			void loadGraph();

			/// <summary>
			/// �ŒZ�o�H�T�����s���܂��B
			/// </summary>
			/// <param name="goal"> �\���������� </param>
			void searchPath();

			/// <summary>
			/// ���J�ڂ����܂��B
			/// </summary>
			/// <param name="id"> �\����������̎��ʔԍ� </param>
			void changeFace(int id);

			/// <summary>
			/// �X�V���܂��B
			/// </summary>
			void update();

			/// <summary>
			/// �w�肳�ꂽ���W�𒆐S�Ƃ��ĕ`�悵�܂��B
			/// </summary>
			/// <param name="pos"> ���W </pos>
			void draw(const Point& pos)const;


		};


		using Message = std::pair<String, String>;


		/// <summary> CAPA�̑�����s�����߂̃p�l�� </summary> 
		class ControlPanel
		{

		private:

			int				m_timer;		// �{�^���̓��쓯���p�̃J�E���^�[

			Array<Button>	m_button_list;	// �{�^���̃��X�g

			Array<int>		m_buttons_type;	// �{�^���̃^�C�v�̔z��

			int				m_sel_button;	// �I�΂ꂽ�{�^��

			String			m_text;			// �\������e�L�X�g

			Face			m_face;			// ��

			Vec2			m_message_pos;	// ���b�Z�[�W��\��������W

			Vec2			m_message_goal; // ���b�Z�[�W��\������ړI�n

			Array<std::pair<String, String>>	m_message_data;	// ���b�Z�[�W

		public:

			/// <summary>
			/// �C���X�^���X���擾���܂��B
			/// </summary>
			/// <returns> �C���X�^���X </returns>
			static ControlPanel& Instance()
			{
				static ControlPanel instance;

				return instance;
			}


		public:

			/// <summary>
			/// ControllPanel�����������܂��B
			/// </summary>
			ControlPanel();
			
			/// <summary>
			/// ����\�������܂��B
			/// </summary>
			/// <remarks> ���̃V�[���ł����삪�K�v�ꍇ���̔����p���� </remarks>
			/// <returns> �\�ȂƂ� true , �����łȂ��Ƃ� false </returns>
			bool controlAble()const
			{
				return m_timer == -1;
			}

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const;

			/// <summary>
			/// �{�^���̏�Ƀ}�E�X�J�[�\�������邩�����܂��B
			/// </summary>
			/// <returns> ����Ƃ� true , �Ȃ��Ƃ� false </returns>
			int mouseOver()const;

			/// <summary>
			/// �{�^�����N���b�N���ꂽ���ǂ��������܂��B
			/// </summary>
			/// <returns> �����ꂽ�{�^����type��Ԃ��܂� , ������ĂȂ��Ƃ� -1 </returns>
			int buttonClicked()const;

			/// <summary>
			/// �{�^���̎�ނ������z���ύX���܂��B
			/// </summary>
			/// <param name="kinds"> ��� </param>
			void setButtonsType(const Array<int> & types)
			{
				m_buttons_type = types;
			}

			/// <summary>
			/// �{�^���̕ύX���J�n���܂��B
			/// </summary>
			void changeButtonStart()
			{
				if (m_timer == -1)
				{
					m_timer = 0;
				}
			}

			/// <summary>
			/// �{�^���̓��������Z�b�g����B
			/// </summary>
			void resetMoveButton()
			{
				if (m_timer < 5)
				{
					m_timer = -1;
				}
			}

			/// <summary>
			/// Face��ύX���܂��B
			/// </summary>
			/// <param name="face_id"> ��ԍ� </param>
			void changeFace(int face_id)
			{
				m_face.changeFace(face_id);
			}

			/// <summary>
			/// �\������e�L�X�g��ύX���܂��B
			/// </summary>
			/// <param name="text"> �e�L�X�g </param>
			void changeText(const String& text)
			{
				m_text = text;
			}

			void changeMessage(const Array<Message> & message_data)
			{
				m_message_data = message_data;

				m_message_pos.x = 640;

				m_message_goal.x = 400;
			}

			void hideMessage()
			{
				m_message_goal.x = 640;
			}

		private:

			/// <summary>
			/// �{�^���𓮂����܂�
			/// </summary>
			void moveButton();

			/// <summary>
			/// ���ԍ��������ă{�^���̈ړ����ݒ肵�܂��B
			/// </summary>
			/// <param name="goal_y"> �ړ����y���W </summary>
			/// <param name="timer0"> �������� </param>
			void setButtonGoal(int goal_y, int timer_0);

			/// <summary>
			/// �V�����{�^���𐶐����܂��B
			/// </summary>
			void createButton();

			/// <summary>
			/// ���b�Z�[�W��`�悵�܂��B
			/// </summary>
			void drawMessage() const;

		};

	}
}