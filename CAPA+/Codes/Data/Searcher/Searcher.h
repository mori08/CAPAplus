#pragma once


#include"../Note/Note.h"

#include<queue>

#include<thread>



namespace My
{

	namespace Data
	{

		class Searcher
		{

		private:

			Array<Card> m_result_list;    // 検索結果を格納するリスト

			std::thread m_search_thread;  // 検索を実行するスレッド

			bool        m_thread_running; // スレッドが走っているかどうか 

		public:

			Searcher()
				:m_thread_running(false)
			{}

			~Searcher()
			{
				if (!m_thread_running) { return; }

#ifdef _DEBUG
				Println(L"warning > 検索スレッドを終了させてください。");
#endif // _DEBUG

				m_search_thread.join();
			}

		public:

			/// <summary>
			/// 別スレッドを動かしカードを探索します。
			/// </summary>
			/// <param name="criteria"> 検索条件 </param>
			/// <returns> 検索に成功したとき true , 失敗したとき false </returns>
			/// <remarks> 必ず検索を終了させてから実行してください。 </remarks>
			bool startSearchThread(const SearchCriteria & criteria);

			/// <summary>
			/// 検索を終了しているとき、スレッドをjoinします。
			/// </summary>
			/// <returns> 終了していたとき true , そうでないとき false </returns>
			bool joinSearchThread();

			/// <summary>
			/// 検索結果を格納します。
			/// </summary>
			/// <param name="card_list"> 結果を格納するリスト </param>
			void storeResult(Array<Card> & card_list);

		private:

			/// <summary>
			/// カードを検索します。
			/// </summary>
			/// <param name="criteria"> 検索条件 </param>
			void search(const SearchCriteria & criteria);

		};

	}

}