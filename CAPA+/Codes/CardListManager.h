#pragma once


#include"CardBoard.h"


const int NON_SELECT = -1;


namespace My
{

	namespace UI
	{

		class CardListManager
		{

		private:

			String	m_texture_name;

			String	m_card_texture_name;

			Point	m_pos;			// 座標

			Point	m_goal;			// 目的地

			int		m_direction;	// 移動方向

			String	m_title;		// タイトル

			int		m_num_limit;	// 表示できるカードの限界値

			Array<CardBoard>	m_card_list;	// カードのリスト

			int		m_card_height;	// カードの高さ

			int		m_select;		// 選択しているカードの識別番号

		public:

			/// <summary>
			/// カードリストマネージャーの作成
			/// </summary>
			/// <param name="direction"> 隠れる方向 </param>
			/// <param name="num_limit"> 表示できるカードの限界時 </param>
			/// <param name="card_height"> カードUIの高さ </param>
			/// <param name="texture_name"> UIの画像名 </param>
			/// <param name="card_texture_name"> カードUIの画像名 </param>
			CardListManager(int direction, int num_limit, int card_height, const String & texture_name, const String & card_texture_name);

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 操作
			/// </summary>
			void control();

			/// <summary>
			/// 描画
			/// </summary>
			/// <param name="pattern"> 描画パターン </param>
			void draw(int pattern)const;

			/// <summary>
			/// 隠す
			/// </summary>
			void hide();

			/// <summary>
			/// タイトルを設定します。
			/// </summary>
			/// <param name="title"> タイトル </param>
			void setTitle(const String & title)
			{
				m_title = title;
			}

			/// <summary>
			/// 座標を設定します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void setPos(const Point & pos)
			{
				m_pos = m_goal = pos;
			}

			/// <summary>
			/// 目的地を設定します。
			/// </summary>
			/// <param name="goal"> 目的地 </param>
			void setGoal(const Point & goal)
			{
				m_goal = goal;
			}

			/// <summary>
			/// 選択されているカードの識別番号を返します。
			/// </summary>
			/// <returns> 識別番号 , -1のとき選択なし </returns>
			int getSelectedId()const
			{
				return m_select;
			}

			/// <summary>
			/// カードボードのリストをセットします。
			/// </summary>
			void setBoardList(const Array<CardBoard> & card_list)
			{
				m_card_list = card_list;
			}

			/// <summary>
			/// 選択されているカードを取得します。
			/// </summary>
			Data::Card getSelectedCard() const;

			/// <summary>
			/// カードが押されたかどうか返します。
			/// </summary>
			/// <returns> 押された番号の番号 , 押されていないないとき -1 </returns>
			int clicked()const;

			/// <summary>
			/// カードUIの上にカーソルがあるか示します
			/// </summary>
			bool mouseOver()const;

			/// <summary>
			/// 選択をはずします。
			/// </summary>
			void clearSelect()
			{
				if (m_select != NON_SELECT)
				{
					m_card_list[m_select].changeGoal(m_pos + Point(30, 45 + 30 * m_select));
				}

				m_select = NON_SELECT;
			}

		};

	}

}