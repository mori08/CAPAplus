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

			String                m_default_text;      // 何もしてしないときにコントロールパネルに表示するテキスト

			Point                 m_criteria_draw_pos; // 検索条件を描画する位置

			Point                 m_result_draw_pos;   // 検索結果を描画する位置

			Data::Searcher        m_searcher;          // 検索

			Data::SearchCriteria  m_criteria;          // 検索条件

			UI::StringInputer     m_term_first;        // 期間のはじめ

			UI::StringInputer     m_term_last;         // 期間のおわり

			UI::StringInputer     m_keywords;          // 検索時のキーワード

		private:

			const int   R              = 20;     // 半径

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
			/// 各状態ごとの更新を行います。
			/// </summary>
			std::function<void(void)> updateFunc;

			/// <summary>
			/// コントロールパネルが表示する文字列を変更します。
			/// </summary>
			void setControlPanelText()const;

			/// <summary>
			/// 検索します。
			/// </summary>
			/// <returns> 検索が開始できたとき true , そうでないとき false </returns>
			bool startSearching();

		public:

			/// <summary>
			/// 検索条件を設定時の更新を行います。
			/// </summary>
			void setCriteriaUpdate();

			/// <summary>
			/// 検索結果待ち時の更新を行います。
			/// </summary>
			void waitSearchingUpdate();

			/// <summary>
			/// 検索結果表示時の更新を行います。
			/// </summary>
			void showResultUpdate();

		};

	}

}