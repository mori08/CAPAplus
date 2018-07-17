#pragma region Format
/*

予定の数
※ タイトル
※ 行数 締め切り番号 タグの数
※ 詳細
※ タグ*n行

(※を予定の数だけ繰り返し)

*/
#pragma endregion



#pragma once



#include"../Day/Day.h"

#include"../Card.h"

#include<map>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// ノートの状態
		/// </summary>
		enum class NoteState
		{
			NORMAL,	// 予定がいくつかある
			ERROR	// テキストファイルを正常に読み込めない
		};



		/// <summary>
		/// 検索条件
		/// </summary>
		struct SearchCriteria
		{
			Day		first;		// 期限の始まり

			Day		last;		// 期限の終わり

			bool	plan;		// 予定を探索するか

			bool	deadline;	// 締切を探索するか

			bool	title;		// タイトルで検索するか

			bool	tags;		// タグで検索するか

			bool	detail;		// 本文で探索するか

			Array<String>	keywords;	// キーワード
		};



		/// <summary>
		/// ノート（複数のカードを管理）
		/// </summary>
		class Note
		{
		private:

			Array<Card> m_plan_list;		// 予定のリスト

			Array<Card> m_deadline_list;	// 締切のリスト

			Day			m_day;				// 日付

			bool		m_error;			// エラーがあるか

			bool		m_is_dirty;			// テキストファイルに書き込みが必要か

		private:

			/// <summary>
			/// ブック（全ノートを管理）
			/// </summary>
			class Book
			{
			private:

				std::map<Day, Note> m_note_map;	// ノートを一括管理

			public:

				/// <summary>
				/// 日付に対応するノートを取得します。
				/// </summary>
				/// <param name="day"> 日付 </param>
				/// <returns> ノートの参照 </returns>
				Note & operator[](const Day& day)
				{
					return m_note_map[day];
				}

			public:

				/// <summary>
				/// 日付に対応したノートを保持しているか示します。
				/// </summary>
				/// <param name="day"> 日付 </param>
				/// <returns> 保持しているとき true , そうでないとき false </returns>
				bool containsNote(const Day & day)
				{
					return m_note_map.find(day) != m_note_map.end();
				}

				/// <summary>
				/// Assets/Data/Noteディレクトリ内に存在する全ノートを読み込み、Bookに格納します。
				/// </summary>
				void readAllText();

				/// <summary>
				/// Bookのノートを全てAssets/Data/Noteディレクトリに書き込みます。
				/// </summary>
				void writeAllText()const;

				/// <summary>
				/// 検索条件を満たすカードを探索します。
				/// </summary>
				/// <param name="criteria"> 検索条件 </param>
				/// <param name="result"> 検索結果を格納するリスト </param>
				void searchCard(const SearchCriteria & criteria, Array<Card> & result)const;

			private:

				/// <summary>
				/// 対応する日付のテキストファイルのノートを読み込む
				/// </summary>
				/// <param name="day"> 日付 </param>
				/// <returns> 読み込んだノート </returns>
				static Data::Note readText(const FilePath & filepath);

				/// <summary>
				/// 対応する日付のテキストファイルにノートを書き込む
				/// </summary>
				/// <param name="note"> 書き込みたいノート </param>
				static void writeText(const Note & note);

			};

			static Book book;	// ノートを管理

		public:

			/// <summary>
			/// 空のノートを生成します。
			/// </summary>
			Note() {}

			/// <summary>
			/// 日付からノートを作成する
			/// </summary>
			/// <param name="day"> 日付 </param>
			Note(const Day& day)
				: m_day(day)
			{
				read();
			}

			/// <summary>
			/// ノートの大小関係を日付の大小で定義します。
			/// </summary>
			/// <param name="note"> 比較したいノート </param>
			/// <returns> このノートの日付のほうが早いとき true , そうでないとき false </returns>
			bool operator<(const Note & note)const
			{
				return m_day < note.m_day;
			}

			/// <summary>
			/// Bookにアクセスします。
			/// </summary>
			/// <returns> Book </returns>
			static Book & accessBook()
			{
				return book;
			}

			/// <summary>
			/// カードが検索条件を満たすか示します。
			/// </summary>
			/// <param name="card"> カード </param>
			/// <param name="criteria"> 検索条件 </param>
			/// <returns> カードが条件を満たすとき true , そうでないとき false </returns>
			static bool checkSearchCriteria(const Card & card, const SearchCriteria & criteria);

		public:

			/// <summary>
			/// 日付を取得します。
			/// </summary>
			/// <returns> 日付 </returns>
			Day getDay()const
			{
				return m_day;
			}

			/// <summary>
			/// 予定のリストを取得します。
			/// </summary>
			/// <returns> 予定のリスト </returns>
			Array<Card> getPlanList()const
			{
				return m_plan_list;
			}

			/// <summary>
			/// 締切のリストを取得します。
			/// </summary>
			/// <returns> 締切のリスト </returns>
			Array<Card> getDeadlineList()const
			{
				return m_deadline_list;
			}

			/// <summary>
			/// 予定と締切のリストを取得します。
			/// </summary>
			Array<Card> getPlanAndDeadlineList()const;

			/// <summary>
			/// 新しい日付のノートをロードします。
			/// </summary>
			/// <param name="">
			void load(const Day& day)
			{
				m_day = day;

				read();
			}

			/// <summary>
			/// カードの内容の変更します。
			/// </summary>
			/// <param name="index"> カードの番号 </param>
			/// <param name="card"> 変更後のカード内容 </param>
			void changeCard(int index, const Card & card);

			/// <summary>
			/// カードを追加します。
			/// </summary>
			/// <param name="card"> 追加したいカード </param>
			void addCard(const Card & card);

			/// <summary>
			/// カードを削除します。
			/// </summary>
			/// <param name="index"> カードの番号 </param>
			void deleteCard(int index);

			/// <summary>
			/// BookからNoteを読み込みます。
			/// </summary>
			void read();

			/// <summary>
			/// BookにNoteを書き込みます。
			/// </summary>
			void write()const;

			/// <summary>
			/// 検索条件を満たすカードを探索します。
			/// </summary>
			/// <param name="criteria"> 検索条件 </param>
			/// <returns> 検索結果 </returns>
			Array<Card> searchCard(SearchCriteria criteria)const;

		private:

			/// <summary>
			/// エラーがあったときメッセージを表示します
			/// </summary>
			/// <remarks> デバッグモード専用 </remarks>
			void sendErrorMessage()
			{
#ifdef _DEBUG
				m_error = true;

				Println(L"error > テキストからノートを読み込むのに失敗しました。");
#endif // _DEBUG
			}

		};

	}

}