#pragma once


#include"Main.h"

#include"Data\Searcher\Searcher.h"

#include"StringInputer.h"


namespace My
{
	
	namespace Scene
	{

		class Search : public MyApp::Scene
		{

		private:

			String                m_default_text;      // �������Ă��Ȃ��Ƃ��ɃR���g���[���p�l���ɕ\������e�L�X�g

			Point                 m_criteria_draw_pos; // ����������`�悷��ʒu

			Point                 m_result_draw_pos;   // �������ʂ�`�悷��ʒu

			Data::Searcher        m_searcher;          // ����

			Data::SearchCriteria  m_criteria;          // ��������

			UI::StringInputer     m_term_first;        // ���Ԃ̂͂���

			UI::StringInputer     m_term_last;         // ���Ԃ̂����

			UI::StringInputer     m_keywords;          // �������̃L�[���[�h

		private:

			const int   R              = 20;     // ���a

			const Point TERM_POINT     = Point(120, 150);

			const Point TYPE_POINT     = Point(120, 220);
			const Point PLAN_POINT     = Point(220, 220);
			const Point DEADLINE_POINT = Point(360, 220);

			const Point KEYWORD_POINT  = Point(120, 290);
			const Point TITLE_POINT    = Point(220, 290);
			const Point TAG_POINT      = Point(360, 290);
			const Point MAIN_POINT     = Point(500, 290);

		public:

			Search();

		public:

			void init()override;

			void update()override;

			void updateFadeIn(double)override;

			void updateFadeOut(double)override;

			void draw()const override;

			void drawFadeIn(double)const override
			{
				draw();
			}

			void drawFadeOut(double)const override
			{
				draw();
			}

		private:

			/// <summary>
			/// �e��Ԃ��Ƃ̍X�V���s���܂��B
			/// </summary>
			std::function<void(void)> updateFunc;

			/// <summary>
			/// �R���g���[���p�l�����\�����镶�����ύX���܂��B
			/// </summary>
			void setControlPanelText()const;

			/// <summary>
			/// �������܂��B
			/// </summary>
			/// <returns> �������J�n�ł����Ƃ� true , �����łȂ��Ƃ� false </returns>
			bool startSearching();

		public:

			/// <summary>
			/// ����������ݒ莞�̍X�V���s���܂��B
			/// </summary>
			void setCriteriaUpdate();

			/// <summary>
			/// �������ʑ҂����̍X�V���s���܂��B
			/// </summary>
			void waitSearchingUpdate();

			/// <summary>
			/// �������ʕ\�����̍X�V���s���܂��B
			/// </summary>
			void showResultUpdate();

		};

	}

}