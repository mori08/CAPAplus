#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace UI
	{

		/// <summary> 背景で動く泡 </summary>
		class Bubble
		{

		private:

			Circle	m_circle;	// 円

			Color	m_color;	// 色

			Vec2	m_speed;	// 速度

		public:

			/// <summary>
			/// 泡を生成します。
			/// </summary>
			/// <param name="x"> 初期x座標 </param>
			/// <param name="r"> 半径 </param>
			/// <param name="c"> 色 </param>
			Bubble(double x, double r, Color c)
				:
				m_circle(x, 480 + r, r),
				m_color(c, 2 * (int)r),
				m_speed(0, -r*r / 8000.0)
			{ }

			/// <summary>
			/// ソート用比較演算子（奥行計算）
			/// </summary>
			bool operator < (const Bubble& bubble)const
			{
				return m_circle.r < bubble.m_circle.r;
			}

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update()
			{
				m_circle.center += m_speed;
			}

			/// <summary>
			/// 削除
			/// </summary>
			bool eraser()const
			{
				return
					m_circle.y + m_circle.r < 0 ||
					m_circle.y - m_circle.r > Window::Height() ||
					m_circle.x + m_circle.r < 0 ||
					m_circle.y - m_circle.r > Window::Width();
			}

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const
			{
				m_circle.draw(m_color);
			}

			/// <summary>
			/// 速度を設定します。
			/// </summary>
			/// <param name="speed"> 速度 </summary>
			void setSpeed(const Vec2 & speed)
			{
				m_speed = (m_circle.r*m_circle.r / 400.0)*speed;
			}

		};



		/// <summary> 背景 </summary>
		class BackGound
		{

		private:

			Array<Color>	m_color_array;	// 色のリスト

			Array<Bubble>	m_bubble_list;	// 泡のリスト

		public:

			BackGound();

			/// <summary>
			/// インスタンス
			/// </summary>
			static BackGound& Instatnce()
			{
				static BackGound instance;

				return instance;
			}

			/// <summary>
			/// 描画と更新
			/// </summary>
			void updateAndDraw()
			{
				update();

				draw();
			}

			/// <summary>
			/// 生成される泡の色を変更します。
			/// </summary>
			void changeColorPattern(const Array<Color> & color_pattern);

		private:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const;

			/// <summary>
			/// バブルの生成
			/// </summary>
			void generateBubble();

			/// <summary>
			/// 色の選択
			/// </summary>
			Color selectColor();

		};

	}

}