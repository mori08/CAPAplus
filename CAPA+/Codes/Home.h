#pragma once


#include"Main.h"

#include"ControllPanel.h"

#include"CardBoard.h"

#include"CardListManager.h"

#include"Detail.h"


namespace My
{

	namespace Scene
	{

		/// <summary> ホーム画面 </summary>
		class Home : public MyApp::Scene
		{

		private:

			enum class State
			{
				NORMAL,				// 通常時

				PLAN_DETAIL,		// 予定の詳細

				DEADLINE_DETAIL		// 締切の詳細
			};

		private:

			const Data::Day TODAY;			// 今日

			UI::CardListManager m_today_plan;		// 今日の予定のカード管理

			UI::CardListManager m_tomorrow_plan;	// 明日の予定のカード管理

			UI::CardListManager m_deadline;			// 締切のカード管理

			UI::Detail	m_detail;			// 詳細表示用UI

			State		m_state;			// 状態

		public:

			Home();

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
			/// フェードイン時の更新
			/// </summay>
			void drawFadeIn(double)const override
			{
				draw();
			}

			/// <summary>
			/// フェードアウト時の更新
			/// </summary>
			void drawFadeOut(double)const override
			{
				draw();
			}

		private:

			/// <summary>
			/// 状態を変更します。
			/// </summary>
			/// <param name="pos"> 詳細を表示させる座標 </param>
			/// <param name="state"> 状態 </param>
			/// <param name="button_list"> ボタンのリスト </param>
			void changeState(const Point & pos, const State & state);

			/// <summary>
			/// ControlPanelのFace,textを変更
			/// </summary>
			void setControlPanel();

			/// <summary>
			/// シーンチェンジを扱います。
			/// </summary>
			void controlSceneChange();

		};

	}

}