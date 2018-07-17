#pragma once

#include"StringInputer.h"


namespace My
{
	namespace UI
	{

		class Tag
		{

		private:

			Point			m_pos;	// ���W

			Point			m_goal;	// �ړI���W

			StringInputer	m_text;	// �^�O�ɗp����e�L�X�g���͗p

		public:

			Tag(const Point & pos, const String & text = L"");

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const;

			/// <summary>
			/// �ړI���W
			/// </summary>
			/// <param name="pos">
			void setGoal(const Point & pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// �폜�{�^���������ꂽ�������܂��B
			/// </summary>
			/// <returns> �����ꂽ�Ƃ� true , �����łȂ��Ƃ� false </returns>
			bool clickedDeleteIcon()const
			{
				return Rect(m_pos + Point(196, 9), Size(12, 12)).leftClicked;
			}

			/// <summary>
			/// �e�L�X�g���擾���܂��B
			/// </summary>
			/// <returns> �e�L�X�g </returns>
			String getText()const
			{
				return m_text.getText();
			}

		};



		class TagEditor
		{

		private:

			Array<Tag>  m_tag_list;		// �Ǘ�����^�O�̃��X�g

			Point		m_add_point;	// �^�O�ǉ��{�^���̔z�u���W

			Point		m_add_goal;		// �^�O�ǉ��{�^���̔z�u�ړI���W

			const size_t	TAG_LIMIT_NUM = 5;	// �^�O���ǉ��ł�����E�l

		public:

			/// <summary>
			/// �^�O�G�f�B�^�𐶐����܂��B
			/// </summary>
			TagEditor();

		public:

			/// <summary>
			/// �X�V
			/// </summary>
			void update();

			/// <summary>
			/// �`��
			/// </summary>
			void draw()const;

			/// <summary>
			/// �^�O�̃e�L�X�g�̃��X�g���擾���܂��B
			/// </summary>
			/// <returns> �e�L�X�g���X�g </returns>
			Array<String> getTextList()const;

			/// <summary>
			/// �^�O���Z�b�g���܂�
			/// </summary>
			/// <param name="text_list"> �^�O�̃e�L�X�g�̃��X�g </param>
			void Set(const Array<String> & text_list);

		};

	}
}