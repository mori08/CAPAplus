#pragma once


#include<Siv3D.hpp>


namespace My
{

	/// <summary> �������萔�Ȃǂ̊Ǘ� </summary>
	namespace Define
	{		

		/// <summary> �摜�̖��O </summary>
		namespace TextureName
		{
			const String HOME_PLAN_NOTE			= L"PlanNote_260x160";

			const String HOME_PLAN_NOTE_PANEL	= L"PlanNote_260x160_Panel";

			const String HOME_PLAN_CARD			= L"PlanCard_240x25";

			const String HOME_DEADLINE_NOTE		= L"DeadlineNote_260x340";

			const String HOME_DEADLINE_CARD		= L"DeadlineCard_240x45";

			const String EDIT_NOTE				= L"Note_260x340";

			const String EDIT_PLAN_CARD			= L"PlanCard_240x25";

			const String EDIT_DEADLINE_CARD		= L"DeadlineCard_240x25";

			const String PLAN_DETAIL			= L"PlanDetail";

			const String PLAN_DETAIL_CARD		= L"PlanCard_240x25";

			const String DEADLINE_DETAIL		= L"DeadlineDetail";

			const String DEADLINE_DETAIL_CARD	= L"DeadlineCard_240x25";
		}

		namespace COLOR_PATTERN
		{
			const Array<Color> COLORFUL // �J���[�p�^�[���O�i�J���t���j
			{
				Palette::Red,
				Palette::Orange,
				Palette::Yellow,
				Palette::Lime,
				Palette::Aqua,
				Palette::Blueviolet,
				Palette::Magenta
			};

			const Array<Color> RED		// �J���[�p�^�[���P�i�ԃx�[�X�j
			{
				Color(240,0,0 * 40),
				Color(240,0,1 * 40),
				Color(240,0,2 * 40),
				Color(240,0,3 * 40),
				Color(240,0,4 * 40),
				Color(240,0,5 * 40),
				Color(240,0,6 * 40)
			};

			const Array<Color> GREEN	// �J���[�p�^�[���Q�i�΃x�[�X�j
			{
				Color(0 * 25,230,0),
				Color(1 * 25,230,0),
				Color(2 * 25,230,0),
				Color(3 * 25,230,0),
				Color(4 * 25,230,0),
				Color(5 * 25,230,0),
				Color(6 * 25,230,0)
			};

			const Array<Color> BLUE		 // �J���[�p�^�[���R�i�x�[�X�j
			{
				Color(0,0 * 40,240),
				Color(0,1 * 40,240),
				Color(0,2 * 40,240),
				Color(0,3 * 40,240),
				Color(0,4 * 40,240),
				Color(0,5 * 40,240),
				Color(0,6 * 40,240)
			};
		}

		/// <summary> �R���g���[���p�l����̃{�^�� </summary>
		class Button
		{
		public:

			/// <summary> ��� </summary>
			static const enum Type
			{
				HOME,			// �z�[��

				CALENDAR,		// �J�����_�[

				SEARCH,			// ����

				DEADLINE,		// ����

				ON,				// �d��

				ADD,			// �ǉ�

				DELETE,			// �폜

				WRITE,			// ����

				DECISION,		// ����

				SAVE,			// �ۑ�

				BACK,			// �߂�

				SKULL,			// �[

				DOWN_ARROW,		// �����

				UP_ARROW,		// ����

				RIGHT_ARROW,	// �E���

				LEFT_ARROW,		// �����

				SEARCH_START	// �����J�n
			};



			/// <summary> �{�^���̃��X�g </summary>
			class List
			{
			public:

				static List get()
				{
					static List instatnce;

					return instatnce;
				}

				// �z�[��
				const Array<int> HOME
				{ 
					Type::CALENDAR,
					Type::SEARCH,
					Type::DEADLINE,
					Type::ON 
				};

				// �z�[��(�ڍו\����)
				const Array<int> HOME_DETAIL
				{ 
					Type::BACK
				};

				// �J�����_�[�i���t�I���j
				const Array<int> CALENDAR
				{
					Type::HOME,
					Type::LEFT_ARROW,
					Type::RIGHT_ARROW,
				};

				// �G�f�B�b�g�i�J�[�h�ꗗ�j
				const Array<int> EDIT_LIST
				{
					Type::ADD,
					Type::CALENDAR
				};

				// �G�f�B�b�g�i�ڍו\�����j
				const Array<int> EDIT_DETAIL
				{
					Type::ADD,
					Type::WRITE,
					Type::DELETE,
					Type::CALENDAR
				};

				// �G�f�B�b�g�i�����������j
				const Array<int> EDIT_EDIT
				{
					Type::SAVE,
					Type::BACK
				};

				// �T�[�`
				const Array<int> SEARCH
				{
					Type::HOME,
					Type::SEARCH_START
				};

				// �T�[�`�i�����҂��j
				const Array<int> SEARCH_WAIT
				{
				};


			};

		};



		class Face
		{
		public:

			static const int NONE = 0;			// �����\�����Ȃ�

			static const int SMILE = 3;			// ���΂�

			static const int EXCLAMATION = 6;	// �I(�т�����)

			static const int QUESTION = 10;		// �H�i�͂Ăȁj

		};

	};

}