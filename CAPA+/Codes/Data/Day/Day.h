#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// 日付
		/// </summary>
		class Day
		{

		private:

			int m_year;

			int m_month;

			int m_date;

		public:

			/// <summary> 
			/// 今日の日付を作成します。
			/// </summary>
			Day();

			/// <summary>
			/// ３つの整数値から日付を作成します。
			/// </summary>
			/// <param name="year" > 年 </param>
			/// <param name="month"> 月 </param>
			/// <param name="date" > 日 </param>
			Day(int year, int month, int date);


			/// <summary>
			/// 文字列から日付を生成します。
			/// </summary>
			/// <param name="str"> 文字列 例:L"2018/1/1" </param>
			Day(const String & str);


		public:

			/// <summary>
			/// 日付を比較します。
			/// </summary>
			/// <param name="day"> 比較したい日付 </param>
			/// <returns> 同じ日付のときtrue , そうでないとき false </returns>
			bool operator == (const Day & day)const
			{
				return m_year == day.m_year&&m_month == day.m_month&&m_date == day.m_date;
			}

			/// <summary>
			/// もとの日付から日数を進めた日付を取得します。
			/// </summary>
			/// <param name="value"> 進めたい日数 </param>
			/// <returns> 日数を進めた日数 </returns>
			Day operator + (int value)const;

			/// <summary>
			/// もとの日付から日数を戻した日付を取得します。
			/// </summary>
			Day operator - (int value)const;
			
			/// <summary>
			/// 日付を比較し、その日数の差を計算します。
			/// </summary>
			/// <param name="day"> 比較対象の日付 </param>
			/// <returns> 差の日数 </returns>
			/// <remarks> *this＜day のとき戻り値は負になります。 </remarks>
			int operator - (const Day& day)const;

			/// <summary>
			/// 日付の前後を比較します。
			/// </summary>
			/// <param name="day"> 比較対象の日付 </param>
			/// <returns> *thisが前のとき true, そうでないとき false </returns>
			bool operator < (const Day& day)const;


		public:

			/// <summary>
			/// その年が閏年か調べます。
			/// </summary>
			/// <param name="year"> 調べる年 </param>
			/// <returns> 閏年のとき true,そうでないとき false </returns>
			static bool isLeap(int year) 
			{ 
				return year % 4 == 0 && year % 100 != 0 || year % 400 == 0; 
			}

			/// <summary>
			/// その月の最終日を示します。
			/// </summary>
			/// <param name="year" > 年(閏年か調べるために利用) </param>
			/// <param name="month"> 月							</param> 
			/// <returns> その月の最終日 (実例) 2004年2月 → 29 
			static int maxDate(int year, int month);

			/// <summary>
			/// 文字列が日付に変換可能か返します。
			/// </summary>
			/// <param name="str"> 文字列 </param>
			/// <returns> 変換可能な場合 true , そうでない場合 false </returns>
			static bool changeAbleStringToDay(const String & str);

			/// <summary>
			/// Dayクラスの文字列表現を作成します。
			/// </summary>
			/// <returns> Dayクラスの文字列表現 </returns>
			String toString()const
			{
				check();

				return ToString(m_year) + L"/" + ToString(m_month) + L"/" + ToString(m_date);
			}

			/// <summary>
			/// 日付に対応したファイルパスを作成します。
			/// </summary>
			/// <returns> ファイルパス </returns>
			FilePath getFilePath()const
			{
				return L"Assets/Data/Note/" + toString() + L".txt";
			}

			/// <summary>
			/// 年を取得します。
			/// </summary>
			/// <returns> 年 </returns>
			int getYear()const
			{
				return m_year;
			}

			/// <summary>
			/// 月を取得します。
			/// </summary>
			/// <returns> 月 </returns>
			int getMonth()const
			{
				return m_month;
			}

			/// <summary>
			/// 日を取得します。
			/// </summary>
			/// <returns> 日 </returns>
			int getDate()const
			{
				return m_date;
			}

			/// <summary>
			/// 曜日の取得します。
			/// </summary>
			/// <returns> 日曜日 - 0 , 月曜日 - 1 , … , 土曜日 - 6 で値を返します。 </returns>
			/// <remarks> ツェラーの公式を用いる </remarks>
			int dayOfWeak()const;

		private:

			/// <summary>
			/// 年月日が正しい値か確認する
			/// </summary>
			/// <remarks> デバッグモード専用 </remarks>
			void check()const
			{
			#ifdef _DEBUG

				// ツェラーの公式より1582年より前の年月日をエラーとする
				// データ管理の都合上9999年より先の年月日をエラーとする

				if (m_year < 1582 || m_date > 9999 || m_month < 1 || m_month >12 || m_date<1 || m_date>maxDate(m_year, m_month))
				{

					Println(L"error > 年月日が不適切です : ", toString());

				}

			#endif // _DEBUG
			}

			/// <summary>
			/// １月１日からどれだけ日数がたったか計算します。
			/// </summary>
			/// <returns> 計算結果 </returns>
			/// <remarks> １月１日を 1 として値を返します。 </remarks>
			int daysFromNewYears()const;

		};

	}

}