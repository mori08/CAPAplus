#pragma once

#include"StringInputer.h"


namespace My
{
	namespace UI
	{

		class Tag
		{

		private:

			Point			m_pos;	// 座標

			Point			m_goal;	// 目的座標

			StringInputer	m_text;	// タグに用いるテキスト入力用

		public:

			Tag(const Point & pos, const String & text = L"");

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const;

			/// <summary>
			/// 目的座標
			/// </summary>
			/// <param name="pos">
			void setGoal(const Point & pos)
			{
				m_goal = pos;
			}

			/// <summary>
			/// 削除ボタンが押されたか示します。
			/// </summary>
			/// <returns> 押されたとき true , そうでないとき false </returns>
			bool clickedDeleteIcon()const
			{
				return Rect(m_pos + Point(196, 9), Size(12, 12)).leftClicked;
			}

			/// <summary>
			/// テキストを取得します。
			/// </summary>
			/// <returns> テキスト </returns>
			String getText()const
			{
				return m_text.getText();
			}

		};



		class TagEditor
		{

		private:

			Array<Tag>  m_tag_list;		// 管理するタグのリスト

			Point		m_add_point;	// タグ追加ボタンの配置座標

			Point		m_add_goal;		// タグ追加ボタンの配置目的座標

			const size_t	TAG_LIMIT_NUM = 5;	// タグが追加できる限界値

		public:

			/// <summary>
			/// タグエディタを生成します。
			/// </summary>
			TagEditor();

		public:

			/// <summary>
			/// 更新
			/// </summary>
			void update();

			/// <summary>
			/// 描画
			/// </summary>
			void draw()const;

			/// <summary>
			/// タグのテキストのリストを取得します。
			/// </summary>
			/// <returns> テキストリスト </returns>
			Array<String> getTextList()const;

			/// <summary>
			/// タグをセットします
			/// </summary>
			/// <param name="text_list"> タグのテキストのリスト </param>
			void Set(const Array<String> & text_list);

		};

	}
}