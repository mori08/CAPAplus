#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace UI
	{

		class StringInputer
		{

		private:

			Point	m_pos;			// 座標

			Rect	m_cursol;		// カーソル

			int		m_input_index;	// 入力位置

			Font	m_font;			// フォント

			String	m_text;			// テキスト

			Color	m_color;		// 色

			int		m_time;			// 時間

			int		m_width;		// 幅

			int		m_line_limit;	// 行の限界値

			int		m_key_value;	// 左右キーの押された長さ (+ 右 , - 左)

			static const int NON_SELECT = -1;

		public:

			/// <summary>
			/// 入力可能な文字列ＵＩの作成
			/// </summary>
			/// <param name="font"> フォント </param>
			/// <param name="text"> 初期文字列 </param>
			/// <param name="break_able"> 改行可能か </param>
			/// <param name="width"> 幅 </width>
			/// <param name="color"> 文字列表示時の色 </param>
			StringInputer(Font & font, String text, int width, int line_limit, Color color = Palette::Black);

			/// <summary>
			/// 入力可能な文字列ＵＩの作成
			/// </summary>
			/// <param name="pos"> 表示座標 </param>
			/// <param name="font"> フォント </param>
			/// <param name="text"> 初期文字列 </param>
			/// <param name="break_able"> 改行可能か </param>
			/// <param name="width"> 幅 </width>
			/// <param name="color"> 文字列表示時の色 </param>
			StringInputer(Point pos, Font & font, String text, int width, int line_limit, Color color = Palette::Black);

			/// <summary>
			/// テキストを表示するために改行部分で分割します。
			/// </summary>
			/// <param name="width"> 幅 </param>
			static Array<String> splitText(const String text, const Font & font, int width);

		public:

			/// <summary>
			/// 文字列を設定
			/// </summary>
			/// <param name="text"> 文字列 </param>
			void setText(const String & text)
			{
				m_text = text;
			}
			
			/// <summary>
			/// 文字列を取得
			/// </summary>
			/// <returns> 文字列 </returns>
			String getText() const
			{
				return m_text;
			}

			/// <summary>
			/// 座標を取得します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void setPos(const Point & pos)
			{
				m_pos = pos;
			}

			/// <summary>
			/// 入力できる範囲にカーソルがあるか示します。
			/// </summary>
			/// <returns> カーソルがあるとき true , そうでないとき false </returns>
			bool mouseOver()const
			{
				return Rect(m_pos, m_width, m_line_limit*m_font.height).mouseOver;
			}

			/// <summary>
			/// 入力を行う
			/// </summary>
			void input();

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const;

		private:

			/// <summary>
			/// 入力箇所の選択
			/// </summary>
			void select();

			/// <summary>
			/// カーソルを移動させます。
			/// </summary>
			void moveCursol();

			/// <summary>
			/// 左右キーでインデックスを変更します。
			/// </summary>
			/// <returns> 変更された場合 true , そうでないとき false </returns>
			bool changeIndexAtKey();

			/// <summary>
			/// 行数を調整します。
			/// </summary>
			void adjustLineNum();

		};

	}

}