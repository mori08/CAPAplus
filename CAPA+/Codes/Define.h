#pragma once


#include<Siv3D.hpp>


namespace My
{

	/// <summary> 文字列や定数などの管理 </summary>
	namespace Define
	{		

		/// <summary> 画像の名前 </summary>
		namespace TextureName
		{
			const String HOME_PLAN_NOTE			= L"PlanNote_260x160";

			const String HOME_PLAN_NOTE_PANEL	= L"PlanNote_260x160_Panel";

			const String HOME_PLAN_CARD			= L"PlanCard_240x25";

			const String HOME_DEADLINE_NOTE		= L"DeadlineNote_260x340";

			const String HOME_DEADLINE_CARD		= L"DeadlineCard_240x45";

			const String EDIT_NOTE				= L"Note_260x340";

			const String EDIT_PLAN_CARD			= L"PlanCard_240x25";

			const String EDIT_DEADLINE_CARD		= L"DeadlineCard_240x25";

			const String PLAN_DETAIL			= L"PlanDetail";

			const String PLAN_DETAIL_CARD		= L"PlanCard_240x25";

			const String DEADLINE_DETAIL		= L"DeadlineDetail";

			const String DEADLINE_DETAIL_CARD	= L"DeadlineCard_240x25";
		}

		namespace COLOR_PATTERN
		{
			const Array<Color> COLORFUL // カラーパターン０（カラフル）
			{
				Palette::Red,
				Palette::Orange,
				Palette::Yellow,
				Palette::Lime,
				Palette::Aqua,
				Palette::Blueviolet,
				Palette::Magenta
			};

			const Array<Color> RED		// カラーパターン１（赤ベース）
			{
				Color(240,0,0 * 40),
				Color(240,0,1 * 40),
				Color(240,0,2 * 40),
				Color(240,0,3 * 40),
				Color(240,0,4 * 40),
				Color(240,0,5 * 40),
				Color(240,0,6 * 40)
			};

			const Array<Color> GREEN	// カラーパターン２（緑ベース）
			{
				Color(0 * 25,230,0),
				Color(1 * 25,230,0),
				Color(2 * 25,230,0),
				Color(3 * 25,230,0),
				Color(4 * 25,230,0),
				Color(5 * 25,230,0),
				Color(6 * 25,230,0)
			};

			const Array<Color> BLUE		 // カラーパターン３（青ベース）
			{
				Color(0,0 * 40,240),
				Color(0,1 * 40,240),
				Color(0,2 * 40,240),
				Color(0,3 * 40,240),
				Color(0,4 * 40,240),
				Color(0,5 * 40,240),
				Color(0,6 * 40,240)
			};
		}

		/// <summary> コントロールパネル上のボタン </summary>
		class Button
		{
		public:

			/// <summary> 種類 </summary>
			static const enum Type
			{
				HOME,			// ホーム

				CALENDAR,		// カレンダー

				SEARCH,			// 検索

				DEADLINE,		// 締切

				ON,				// 電源

				ADD,			// 追加

				DELETE,			// 削除

				WRITE,			// 書込

				DECISION,		// 決定

				SAVE,			// 保存

				BACK,			// 戻る

				SKULL,			// 骸

				DOWN_ARROW,		// 下矢印

				UP_ARROW,		// 上矢印

				RIGHT_ARROW,	// 右矢印

				LEFT_ARROW,		// 左矢印

				SEARCH_START	// 検索開始
			};



			/// <summary> ボタンのリスト </summary>
			class List
			{
			public:

				static List get()
				{
					static List instatnce;

					return instatnce;
				}

				// ホーム
				const Array<int> HOME
				{ 
					Type::CALENDAR,
					Type::SEARCH,
					Type::DEADLINE,
					Type::ON 
				};

				// ホーム(詳細表示時)
				const Array<int> HOME_DETAIL
				{ 
					Type::BACK
				};

				// カレンダー（日付選択）
				const Array<int> CALENDAR
				{
					Type::HOME,
					Type::LEFT_ARROW,
					Type::RIGHT_ARROW,
				};

				// エディット（カード一覧）
				const Array<int> EDIT_LIST
				{
					Type::ADD,
					Type::CALENDAR
				};

				// エディット（詳細表示時）
				const Array<int> EDIT_DETAIL
				{
					Type::ADD,
					Type::WRITE,
					Type::DELETE,
					Type::CALENDAR
				};

				// エディット（書き換え時）
				const Array<int> EDIT_EDIT
				{
					Type::SAVE,
					Type::BACK
				};

				// サーチ
				const Array<int> SEARCH
				{
					Type::HOME,
					Type::SEARCH_START
				};

				// サーチ（検索待ち）
				const Array<int> SEARCH_WAIT
				{
				};


			};

		};



		class Face
		{
		public:

			static const int NONE = 0;			// 何も表示しない

			static const int SMILE = 3;			// 微笑み

			static const int EXCLAMATION = 6;	// ！(びっくり)

			static const int QUESTION = 10;		// ？（はてな）

		};

	};

}