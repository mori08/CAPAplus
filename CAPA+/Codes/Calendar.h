#pragma once


#include"Data\Note\Note.h"

#include"Main.h"

#include"CardBoard.h"



namespace My
{

	namespace UI
	{

		/// <summary> カレンダーを構成するパーツ </summary>
		class CalendarPart
		{

		private:

			Point		m_pos;		// 座標

			Point		m_goal;		// 目的座標

			Data::Note	m_note;		// ノート

			double		m_scale;	// 倍率

			const Point SIZE = Point(60, 40);

		public:

			/// <summary>
			/// カレンダーのパーツ
			/// </summary>
			/// <param name="day"> 日付 </param>
			/// <param name="pos"> 座標 </param>
			CalendarPart(const Data::Day& day, const Point& pos)
				:
				m_note(day),
				m_pos(pos),
				m_goal(pos),
				m_scale(1.0)
			{

			}

		public:

			/// <summary>
			/// 更新します。
			/// </summary>
			void update();

			/// <summary>
			/// 描画します。
			/// </summary>
			void draw()const;

			/// <summary>
			/// 上にマウスカーソルがあるか示します。
			/// </summary>
			/// <returns> あるとき true , ないとき false </returns>
			bool mouseOver()const
			{
				return Rect(m_pos, SIZE).mouseOver;
			}

			/// <summary>
			/// マウスでクリックされたか示します。
			/// </summary>
			/// <returns> クリックされたとき true , そうでないときとき false </returns>
			bool clicked()const
			{
				return Rect(m_pos, SIZE).leftClicked;
			}

			/// <summary>
			/// ノートを取得します。
			/// </summary>
			/// <returns> ノート </returns>
			Data::Note getNote()const
			{
				return m_note;
			}

			/// <summary>
			/// 目的地を設定します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void setGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// 目的地のX座標を設定します。
			/// </summary>
			/// <param name="x"> x </param>
			void setGoalX(int x)
			{
				m_goal.x = x;
			}

			/// <summary>
			/// 座標を取得します。
			/// </summary>
			Point getPos()const
			{
				return m_pos;
			}

			/// <summary>
			/// ノートを新しい日付で再読み込みします。
			/// </summary>
			/// <param name="day"> 日付 </param>
			void reloadNote(const Data::Day& day)
			{
				m_note = Data::Note(day);
			}

			/// <summary>
			/// 倍率を変更します。
			/// </summary>
			/// <param name="select_able"> 選べるとき true 、そうでないとき false </param>
			void changeScale(bool select_able = true);

		};

	}



	namespace Scene
	{

		/// <summary> カレンダーシーン </summary>
		class Calendar : public MyApp::Scene
		{

		private:

			int m_year;		// 表示している年

			int m_month;	// 表示している月

			int m_date;		// 選択している日

			Array<UI::CalendarPart> m_part_list;	// パーツリスト

		public:

			Calendar();

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update()override;

			/// <summary>
			/// フェードイン時の更新
			/// </summary>
			void updateFadeIn(double)override;

			/// <summary>
			/// フェードアウト時の更新
			/// </summary>
			void updateFadeOut(double)override;

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const override;

			/// <summary>
			/// フェードイン時の描画
			/// </summary>
			void drawFadeIn(double)const override
			{
				draw();
			}

			/// <summary>
			/// フェードアウト時の描画
			/// </summary>
			void drawFadeOut(double)const override
			{
				draw();
			}

			/// <summary>
			/// パーツを生成します。
			/// </summary>
			void reloadPats();

			/// <summary>
			/// カーソルがコントロールパネルのボタンの上にあるときの処理を行います。
			/// </summary>
			void mouseOverControlPanel();

			/// <summary>
			/// コントロールパネルのボタンをクリックしたときの処理を行います。
			/// </summary>
			void clickControlPanel();

			/// <summary>
			/// CALENDAR_SELECTの状態での更新を行います。
			/// </summary>
			void updateCalendarSelect();

		};

	}

}