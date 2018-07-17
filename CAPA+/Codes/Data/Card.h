#pragma once


#include"Day\Day.h"


namespace My
{

	namespace Data
	{

		struct Card
		{
			Day				day;			// 日付

			String			title;			// 名前

			String			detail;			// 詳細

			int				deadline_id;	// 締切番号(予定のとき-1)

			Array<String>	tags;			// タグ

			bool			check;			// チェック

			String			status;			// 状態

			Color			color;			// 状態を描画する色
		};

		/// <summary>
		/// 空白カードを作成します。
		/// </summary>
		/// <param name="day"> 日付 </param>
		/// <returns> 空白カード </returns>
		Card createNewCard(const Day & day);

	}
}