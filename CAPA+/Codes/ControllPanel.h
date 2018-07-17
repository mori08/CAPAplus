#pragma once


#include<Siv3D.hpp>

#include<unordered_map>


namespace My
{
	namespace UI
	{

		/// <summary> ControllPanelで使用するボタン </summary>
		class Button
		{

		private:

			static const int SIZE_X = 40;	// ボタンのXサイズ

			static const int SIZE_Y = 60;	// ボタンのYサイズ

		private:

			int		m_type;	// 種類

			Point	m_pos;	// ボタンの座標

			Point	m_goal;	// 目的地の場所

			
		public:

			/// <summary>
			/// ボタンを作成します。
			/// </summary>
			/// <param name="type"> 種類 </param>
			/// <param name="pos"> 座標 </param>
			Button(int type, const Point& pos)
			{
				m_type = type;

				m_pos = m_goal = pos;

				Rect().mouseOver;
			}

			/// <summary>
			/// 目的地を変更します。
			/// </summary>
			/// <param name="pos"> 座標 </param>
			void changeGoal(const Point& pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// 座標を更新します。
			/// </summary>
			void update()
			{
				m_pos.x = (int)((m_pos.x + 0.3*m_goal.x) / 1.3);

				m_pos.y = (int)((m_pos.y + 0.5*m_goal.y) / 1.5);
			}

			/// <summary>
			/// ボタンの上にマウスカーソルがあるか示します。
			/// </summary>
			/// <returns> あるとき true , ないとき false </returns>
			int mouseOver()const
			{
				if (Rect(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3, SIZE_X, SIZE_Y).mouseOver)
				{
					return m_type;
				}

				return -1;
			}

			/// <summary>
			/// ボタンがクリックされたか示します。
			/// </summary>
			/// <returns> 押されたときtypeを返します , 押されてないとき -1 </returns>
			int clicked()const
			{
				if (Rect(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3, SIZE_X, SIZE_Y).leftClicked)
				{
					return m_type;
				}

				return -1;
			}

			/// <summary>
			/// 描画します
			/// </summary>
			void draw()const
			{
				TextureAsset(L"Buttons")(m_type % 4 * SIZE_X, m_type / 4 * SIZE_Y, SIZE_X, SIZE_Y).draw(m_pos.x - SIZE_X / 2, m_pos.y - SIZE_Y * 2 / 3);
			}


		};




		/// <summary> ControlPanel上で使用する顔 </summary>
		class Face
		{

		private:

			int m_face_id;							// 現在表示している顔の識別番号

			int m_goal;								// 表示したい顔

			Array<Array<int>> m_graph;				// グラフ構造

			Array<int> m_path;						// 経路を記憶


		public:

			/// <summary>
			/// 顔UIを作成します。
			/// </summary>
			Face();

			/// <summary>
			/// グラフ構造をCSVファイルからロードします。
			/// </summary>
			void loadGraph();

			/// <summary>
			/// 最短経路探索を行います。
			/// </summary>
			/// <param name="goal"> 表示したい顔 </param>
			void searchPath();

			/// <summary>
			/// 顔を遷移させます。
			/// </summary>
			/// <param name="id"> 表示したい顔の識別番号 </param>
			void changeFace(int id);

			/// <summary>
			/// 更新します。
			/// </summary>
			void update();

			/// <summary>
			/// 指定された座標を中心として描画します。
			/// </summary>
			/// <param name="pos"> 座標 </pos>
			void draw(const Point& pos)const;


		};


		using Message = std::pair<String, String>;


		/// <summary> CAPAの操作を行うためのパネル </summary> 
		class ControlPanel
		{

		private:

			int				m_timer;		// ボタンの動作同期用のカウンター

			Array<Button>	m_button_list;	// ボタンのリスト

			Array<int>		m_buttons_type;	// ボタンのタイプの配列

			int				m_sel_button;	// 選ばれたボタン

			String			m_text;			// 表示するテキスト

			Face			m_face;			// 顔

			Vec2			m_message_pos;	// メッセージを表示する座標

			Vec2			m_message_goal; // メッセージを表示する目的地

			Array<std::pair<String, String>>	m_message_data;	// メッセージ

		public:

			/// <summary>
			/// インスタンスを取得します。
			/// </summary>
			/// <returns> インスタンス </returns>
			static ControlPanel& Instance()
			{
				static ControlPanel instance;

				return instance;
			}


		public:

			/// <summary>
			/// ControllPanelを初期化します。
			/// </summary>
			ControlPanel();
			
			/// <summary>
			/// 操作可能か示します。
			/// </summary>
			/// <remarks> 他のシーンでも操作が必要場合この判定を用いる </remarks>
			/// <returns> 可能なとき true , そうでないとき false </returns>
			bool controlAble()const
			{
				return m_timer == -1;
			}

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const;

			/// <summary>
			/// ボタンの上にマウスカーソルがあるか示します。
			/// </summary>
			/// <returns> あるとき true , ないとき false </returns>
			int mouseOver()const;

			/// <summary>
			/// ボタンがクリックされたかどうか示します。
			/// </summary>
			/// <returns> 押されたボタンのtypeを返します , 押されてないとき -1 </returns>
			int buttonClicked()const;

			/// <summary>
			/// ボタンの種類を示す配列を変更します。
			/// </summary>
			/// <param name="kinds"> 種類 </param>
			void setButtonsType(const Array<int> & types)
			{
				m_buttons_type = types;
			}

			/// <summary>
			/// ボタンの変更を開始します。
			/// </summary>
			void changeButtonStart()
			{
				if (m_timer == -1)
				{
					m_timer = 0;
				}
			}

			/// <summary>
			/// ボタンの動きをリセットする。
			/// </summary>
			void resetMoveButton()
			{
				if (m_timer < 5)
				{
					m_timer = -1;
				}
			}

			/// <summary>
			/// Faceを変更します。
			/// </summary>
			/// <param name="face_id"> 顔番号 </param>
			void changeFace(int face_id)
			{
				m_face.changeFace(face_id);
			}

			/// <summary>
			/// 表示するテキストを変更します。
			/// </summary>
			/// <param name="text"> テキスト </param>
			void changeText(const String& text)
			{
				m_text = text;
			}

			void changeMessage(const Array<Message> & message_data)
			{
				m_message_data = message_data;

				m_message_pos.x = 640;

				m_message_goal.x = 400;
			}

			void hideMessage()
			{
				m_message_goal.x = 640;
			}

		private:

			/// <summary>
			/// ボタンを動かします
			/// </summary>
			void moveButton();

			/// <summary>
			/// 時間差を持ってボタンの移動先を設定します。
			/// </summary>
			/// <param name="goal_y"> 移動先のy座標 </summary>
			/// <param name="timer0"> 初期時間 </param>
			void setButtonGoal(int goal_y, int timer_0);

			/// <summary>
			/// 新しくボタンを生成します。
			/// </summary>
			void createButton();

			/// <summary>
			/// メッセージを描画します。
			/// </summary>
			void drawMessage() const;

		};

	}
}