#pragma once


#include<Siv3D.hpp>

#include"Data\Note\Note.h"

#include"Data\DeadlineManager\DeadlineManager.h"


namespace My
{

	namespace UI
	{

		/// <summary> カード(予定や締切)のUI </summary>
		class CardBoard
		{

		private:

			Point		m_pos;		// 座標

			Point		m_goal;		// 移動先の座標

			Point		m_size;		// サイズ

			Point		m_base_pos;	// 判定を無効にする基準の点

			Data::Card	m_card;	// カード

		public:

			/// <summary>
			/// カード(予定や締切)のUIを作成します。
			/// </summary>
			/// <param name="card"> カード </param>
			/// <param name="pos"> 初期座標 </param>
			/// <param name="size"> マウス使用時の判定の大きさ </param>
			/// <param name="base_pos"> 判定を無効にする基準の点を設定(初期設定{0,0}) </param>
			CardBoard(const Data::Card& card, const Point& pos, const Point& size = Point(0, 0), const Point& base_pos = Point(0, 0));

			/// <summary>
			/// カードボードのリストを作成します。
			/// </summary>
			/// <param name="card_list"> カードのリスト </param>
			/// <param name="pos"> 初期座標 </param>
			/// <param name="size"> マウス使用時の判定の大きさ </param>
			/// <param name="base_pos"> 判定を無効にする基準の点を設定(初期設定{0,0}) </param>
			static Array<CardBoard> makeList(const Array<Data::Card> & card_list, const Point & pos, const Size & size, const Point & base_pos = Point::Zero);

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 座標を設定します。
			/// </summary>
			void setPos(const Point& pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// 移動先を変更します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void changeGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// 目的地のx座標のみを変更します。
			/// </summary>
			/// <param name="x"> x座標 </param>
			void changeGoalX(int x)
			{
				m_goal.x = x;
			}

			/// <summary>
			/// 目的地のy座標のみを変更します。
			/// </summary>
			/// <param name="x"> y座標 </param>
			void changeGoalY(int y)
			{
				m_goal.y = y;
			}

			/// <summary>
			/// サイズを取得します。
			/// </summary>
			Size getSize()const
			{
				return m_size;
			}

			/// <summary>
			/// カードを取得
			/// </summary>
			/// <returns> カード </returns>
			Data::Card getCard()const
			{
				return m_card;
			}

			/// <summary>
			/// 上にマウスカーソルがあるか示します。
			/// </summary>
			/// <returns> あるとき true , ないとき false </returns>
			bool mouseOver()const;

			/// <summary>
			/// マウスでクリックされたか示します。
			/// </summary>
			/// <returns> クリックされたとき true , そうでないときとき false </returns>
			bool clicked()const;

			/// <summary>
			/// 描画１(タイトルだけ表示)
			/// </summary>
			/// <param name="texture_name"> 画像の名前 </param>
			void draw1(const String& texture_name)const;

			/// <summary>
			/// 描画２(タイトルと日付表示)
			/// </summary>
			/// <param name="texture_name"> 画像の名前 </param>
			void draw2(const String& texture_name)const;

			/// <summary>
			/// 描画３(タイトルと日付と状態を表示)
			/// </summary>
			/// <param name="texture_name"> 画像の名前 </param>
			void draw3(const String& texture_name)const;

			/// <summary>
			/// 描画４(予定と締切でカードを別表示：タイトルのみ)
			/// </summary>
			/// <param name="plan_texture_name"> 予定のカードUI用画像名 </param>
			/// <param name="deadline_texture_name"> 締切のカードUI用画像名 </param>
			void draw4(const String & plan_texture_name, const String & deadline_texture_name)const;

			/// <summary>
			/// 描画５(予定と締切でカードを別表示：タイトルと日付を表示)
			/// </summary>
			/// <param name="plan_texture_name"> 予定のカードUI用画像名 </param>
			/// <param name="deadline_texture_name"> 締切のカードUI用画像名 </param>
			void draw5(const String & plan_texture_name, const String & deadline_texture_name)const;

		};

	}

}