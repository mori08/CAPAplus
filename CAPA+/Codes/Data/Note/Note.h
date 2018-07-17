#pragma region Format
/*

�\��̐�
�� �^�C�g��
�� �s�� ���ߐ؂�ԍ� �^�O�̐�
�� �ڍ�
�� �^�O*n�s

(����\��̐������J��Ԃ�)

*/
#pragma endregion



#pragma once



#include"../Day/Day.h"

#include"../Card.h"

#include<map>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// �m�[�g�̏��
		/// </summary>
		enum class NoteState
		{
			NORMAL,	// �\�肪����������
			ERROR	// �e�L�X�g�t�@�C���𐳏�ɓǂݍ��߂Ȃ�
		};



		/// <summary>
		/// ��������
		/// </summary>
		struct SearchCriteria
		{
			Day		first;		// �����̎n�܂�

			Day		last;		// �����̏I���

			bool	plan;		// �\���T�����邩

			bool	deadline;	// ���؂�T�����邩

			bool	title;		// �^�C�g���Ō������邩

			bool	tags;		// �^�O�Ō������邩

			bool	detail;		// �{���ŒT�����邩

			Array<String>	keywords;	// �L�[���[�h
		};



		/// <summary>
		/// �m�[�g�i�����̃J�[�h���Ǘ��j
		/// </summary>
		class Note
		{
		private:

			Array<Card> m_plan_list;		// �\��̃��X�g

			Array<Card> m_deadline_list;	// ���؂̃��X�g

			Day			m_day;				// ���t

			bool		m_error;			// �G���[�����邩

			bool		m_is_dirty;			// �e�L�X�g�t�@�C���ɏ������݂��K�v��

		private:

			/// <summary>
			/// �u�b�N�i�S�m�[�g���Ǘ��j
			/// </summary>
			class Book
			{
			private:

				std::map<Day, Note> m_note_map;	// �m�[�g���ꊇ�Ǘ�

			public:

				/// <summary>
				/// ���t�ɑΉ�����m�[�g���擾���܂��B
				/// </summary>
				/// <param name="day"> ���t </param>
				/// <returns> �m�[�g�̎Q�� </returns>
				Note & operator[](const Day& day)
				{
					return m_note_map[day];
				}

			public:

				/// <summary>
				/// ���t�ɑΉ������m�[�g��ێ����Ă��邩�����܂��B
				/// </summary>
				/// <param name="day"> ���t </param>
				/// <returns> �ێ����Ă���Ƃ� true , �����łȂ��Ƃ� false </returns>
				bool containsNote(const Day & day)
				{
					return m_note_map.find(day) != m_note_map.end();
				}

				/// <summary>
				/// Assets/Data/Note�f�B���N�g�����ɑ��݂���S�m�[�g��ǂݍ��݁ABook�Ɋi�[���܂��B
				/// </summary>
				void readAllText();

				/// <summary>
				/// Book�̃m�[�g��S��Assets/Data/Note�f�B���N�g���ɏ������݂܂��B
				/// </summary>
				void writeAllText()const;

				/// <summary>
				/// ���������𖞂����J�[�h��T�����܂��B
				/// </summary>
				/// <param name="criteria"> �������� </param>
				/// <param name="result"> �������ʂ��i�[���郊�X�g </param>
				void searchCard(const SearchCriteria & criteria, Array<Card> & result)const;

			private:

				/// <summary>
				/// �Ή�������t�̃e�L�X�g�t�@�C���̃m�[�g��ǂݍ���
				/// </summary>
				/// <param name="day"> ���t </param>
				/// <returns> �ǂݍ��񂾃m�[�g </returns>
				static Data::Note readText(const FilePath & filepath);

				/// <summary>
				/// �Ή�������t�̃e�L�X�g�t�@�C���Ƀm�[�g����������
				/// </summary>
				/// <param name="note"> �������݂����m�[�g </param>
				static void writeText(const Note & note);

			};

			static Book book;	// �m�[�g���Ǘ�

		public:

			/// <summary>
			/// ��̃m�[�g�𐶐����܂��B
			/// </summary>
			Note() {}

			/// <summary>
			/// ���t����m�[�g���쐬����
			/// </summary>
			/// <param name="day"> ���t </param>
			Note(const Day& day)
				: m_day(day)
			{
				read();
			}

			/// <summary>
			/// �m�[�g�̑召�֌W����t�̑召�Œ�`���܂��B
			/// </summary>
			/// <param name="note"> ��r�������m�[�g </param>
			/// <returns> ���̃m�[�g�̓��t�̂ق��������Ƃ� true , �����łȂ��Ƃ� false </returns>
			bool operator<(const Note & note)const
			{
				return m_day < note.m_day;
			}

			/// <summary>
			/// Book�ɃA�N�Z�X���܂��B
			/// </summary>
			/// <returns> Book </returns>
			static Book & accessBook()
			{
				return book;
			}

			/// <summary>
			/// �J�[�h�����������𖞂����������܂��B
			/// </summary>
			/// <param name="card"> �J�[�h </param>
			/// <param name="criteria"> �������� </param>
			/// <returns> �J�[�h�������𖞂����Ƃ� true , �����łȂ��Ƃ� false </returns>
			static bool checkSearchCriteria(const Card & card, const SearchCriteria & criteria);

		public:

			/// <summary>
			/// ���t���擾���܂��B
			/// </summary>
			/// <returns> ���t </returns>
			Day getDay()const
			{
				return m_day;
			}

			/// <summary>
			/// �\��̃��X�g���擾���܂��B
			/// </summary>
			/// <returns> �\��̃��X�g </returns>
			Array<Card> getPlanList()const
			{
				return m_plan_list;
			}

			/// <summary>
			/// ���؂̃��X�g���擾���܂��B
			/// </summary>
			/// <returns> ���؂̃��X�g </returns>
			Array<Card> getDeadlineList()const
			{
				return m_deadline_list;
			}

			/// <summary>
			/// �\��ƒ��؂̃��X�g���擾���܂��B
			/// </summary>
			Array<Card> getPlanAndDeadlineList()const;

			/// <summary>
			/// �V�������t�̃m�[�g�����[�h���܂��B
			/// </summary>
			/// <param name="">
			void load(const Day& day)
			{
				m_day = day;

				read();
			}

			/// <summary>
			/// �J�[�h�̓��e�̕ύX���܂��B
			/// </summary>
			/// <param name="index"> �J�[�h�̔ԍ� </param>
			/// <param name="card"> �ύX��̃J�[�h���e </param>
			void changeCard(int index, const Card & card);

			/// <summary>
			/// �J�[�h��ǉ����܂��B
			/// </summary>
			/// <param name="card"> �ǉ��������J�[�h </param>
			void addCard(const Card & card);

			/// <summary>
			/// �J�[�h���폜���܂��B
			/// </summary>
			/// <param name="index"> �J�[�h�̔ԍ� </param>
			void deleteCard(int index);

			/// <summary>
			/// Book����Note��ǂݍ��݂܂��B
			/// </summary>
			void read();

			/// <summary>
			/// Book��Note���������݂܂��B
			/// </summary>
			void write()const;

			/// <summary>
			/// ���������𖞂����J�[�h��T�����܂��B
			/// </summary>
			/// <param name="criteria"> �������� </param>
			/// <returns> �������� </returns>
			Array<Card> searchCard(SearchCriteria criteria)const;

		private:

			/// <summary>
			/// �G���[���������Ƃ����b�Z�[�W��\�����܂�
			/// </summary>
			/// <remarks> �f�o�b�O���[�h��p </remarks>
			void sendErrorMessage()
			{
#ifdef _DEBUG
				m_error = true;

				Println(L"error > �e�L�X�g����m�[�g��ǂݍ��ނ̂Ɏ��s���܂����B");
#endif // _DEBUG
			}

		};

	}

}