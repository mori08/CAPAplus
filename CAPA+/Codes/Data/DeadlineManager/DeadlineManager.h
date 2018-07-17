#pragma once

#include"../Day/Day.h"

#include"../Card.h"


namespace My
{

	namespace Data
	{		


		/// <summary> 締切を扱う処理を一つのクラスにまとめる </summary>
		class DeadlineManager
		{

		public:

			/// <summary>
			/// カードのステータスを設定します。
			/// </summary>
			/// <param name="card"> カード </param>
			static void setStatus(Card & card);

			/// <summary>
			/// 締切を探索し配列として出力します。
			/// </summary>
			/// <returns> 締切の配列 </returns>
			static Array<Card> loadDeadlineList();

			/// <summary>
			/// 未チェックの締め切りを探索し配列として出力します。
			/// </summary>
			/// <returns> 未チェックの締切の配列 </returns>
			static Array<Card> loadNocheckDeadlineList();

			/// <summary>
			/// 締切を追加します。
			/// </summary>
			/// <param name="day"> 日付 </param>
			/// <returns> 設定された締切番号を返します。 </returns>
			static int addDeadline(const Day & day);

			/// <summary>
			/// 締切を削除します。
			/// </summary>
			/// <param name="id"> 締切番号 </param>
			static void deleteDeadline(int id);

		private:

			/// <summary>
			/// カードを締切として優先順位を比較します
			/// </summary>
			/// <param name="c1"> カード１ </param>
			/// <param name="c2"> カード２ </param>
			/// <returns> 優先順位がc2のほうが上のとき true , そうでないとき false </param>
			static bool compareDeadlineCard(const Card & c1, const Card & c2);

			/// <summary>
			/// DeadlineのDayからtitleとdetailを設定します。
			/// </summary>
			/// <param name="deadline"> 締切情報 </param>
			static void searchDeadline(Card& deadline);

		};

	}

}