#pragma once

#include"Main.h"

#include"CardListManager.h"

#include"Detail.h"

namespace My
{

	namespace Scene
	{

		/// <summary> 予定の編集ページ </summary>
		class Editor : public MyApp::Scene
		{

		private:

			enum class State
			{
				NORMAL,		// 通常

				DETAIL,		// 詳細表示

				CREATE_NEW,	// 新規作成

				EDIT		// 編集
			};

		private:

			State					m_state;			// 状態

			Data::Note				m_note;				// 指定された日付のノート

			UI::CardListManager		m_board_list;		// 予定

			UI::Detail				m_detail;			// 詳細の表示

		public:

			Editor();

		public:

			/// <summary>
			/// 初期化
			/// </summary>
			void init();

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

		private:

			/// <summary>
			/// Noraml状態での更新
			/// </summary>
			void updateNormal();

			/// <summary>
			/// Detail状態での更新
			/// </summary>
			void updateDetail();

			/// <summary>
			/// CreateNew状態での更新
			/// </summary>
			void updateCreateNew();

			/// <summary>
			/// Edit状態での更新
			/// </summary>
			void updateEdit();

			/// <summary>
			/// コントロールパネルに加える処理
			/// </summary>
			void useControlPanel();

		};

	}

}