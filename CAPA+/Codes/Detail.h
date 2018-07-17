#pragma once


#include"Data\Day\Day.h"

#include"Data\Note\Note.h"

#include"Data\DeadlineManager\DeadlineManager.h"

#include"CardBoard.h"

#include"StringInputer.h"

#include"TagEditor.h"



namespace My
{

	namespace UI
	{

		/// <summary> 予定と締切の詳細の表示や編集を行う </summary>
		class Detail
		{

		private:

			Point		m_pos;		// 座標

			Point		m_goal;		// 目的座標

			Point m_title_pos, m_title_goal;

			Data::Card	m_card;		// カード

			bool		m_is_plan;	// 予定のときtrue , そうでないとき false

			StringInputer m_title;	// タイトル

			StringInputer m_detail;	// 詳細

			TagEditor m_tag_editor;	// タグのエディタ
			

		private:

			const Rect PLAN_BUTTON = Rect(340, 140, 120, 40);

			const Rect DEADLINE_BUTTON = Rect(480, 140, 120, 40);

		public:

			/// <summary> 詳細提示用のUIを作成します。 </summary>
			/// <param name="pos"> 座標 </param>
			Detail(const Point& pos);

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 入力
			/// </summary>
			void input();

			/// <summary>
			/// 予定か締切かを選択します。
			/// </summary>
			void selectPlanOrDeadline();

			/// <summary>
			/// 座標を設定します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void setPos(const Point& pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// 目的座標を設定します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void setGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// タイトル表示座標を設定します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			/// <param name="goal"> 目的 </param>
			void setTitlePos(const Point& pos,const Point& goal)
			{
				m_title_pos = pos;

				m_title_goal = goal;
			}

			/// <summary>
			/// タイトル表示の目的座標を設定します。
			/// </summary>
			/// <param name="pos"> 目的地 </param>
			void setTitleGoal(const Point& pos)
			{
				m_title_goal = pos;
			}

			/// <summary>
			/// 画面外に隠すためにゴールを設定します。
			/// </summary>
			void hide()
			{
				m_goal.x = m_title_goal.x = Window::Width();
			}

			/// <summary>
			/// カードを設定します。
			/// </summary>
			/// <param name="card"> カード </param>
			void setCard(const Data::Card & card);

			/// <summary>
			/// カードを取得します。
			/// </summary>
			/// <returns> カード </returns>
			Data::Card getCard();

			/// <summary>
			/// 描画
			/// </summary>
			/// <param name="texture_name"> 識別番号 </param>
			/// <param name="card_texture_name"> カード </param>
			/// <param name="card"> 日付 </param>
			void draw() const;

			/// <summary>
			/// Edit用の描画
			/// </summary>
			void drawEdit() const;

			/// <summary>
			/// 予定と締切の選択用のUIを描画
			/// </summary>
			void drawPlanOrDeadline() const;

			/// <summary>
			/// 管理しているカードが予定か締切かを返します。
			/// </summary>
			/// <returns> 予定のとき true , 締切のとき false </returns>
			bool IsPlan() const
			{
				return m_is_plan;
			}

		};

	}

}