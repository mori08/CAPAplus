#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// 文字列を標準入力のように処理するのをサポート
		/// </summary>
		class ReadSupporter
		{

		public:

			/// <summary>
			/// TextReaderからReadSupporterを作成します。
			/// </summary>
			/// <param name="reader"> 読み込みたいテキストファイル </param>
			ReadSupporter(TextReader& reader)
			{
				splitText(reader.readAll());
			}


		public:

			/// <summary>
			/// 入力を文字列として代入します。
			/// </summary>
			/// <param name="value"> 代入先 </value>
			/// <returns> *this </returns>
			ReadSupporter& operator >> (String & value)
			{
				value = readWord();

				return *this;
			}

			/// <summary>
			/// 入力を整数として代入します。
			/// </summary>
			/// <param name="value"> 代入先 </value>
			/// <returns> *this </returns>
			ReadSupporter& operator >> (int& value)
			{
				value = readInteger();

				return *this;
			}


		public:

			/// <summary>
			/// 入力を文字列として取得します。
			/// </summary>
			/// <returns> 取得する文字列 </returns>
			String readWord();

			/// <summary>
			/// 入力を次の改行まで文字列として取得します。
			/// </summary>
			String readLine();

			/// <summary>
			/// 入力を整数値として取得します。
			/// </summary>
			/// <param name="defalutValue"> 読み込みに失敗したときの値 </param>
			/// <returns> 取得する整数値 </returns>
			int readInteger(int defalutValue = -1)
			{
				return ParseOr<int>(readWord(), defalutValue);
			}


		private:

			/// <summary>
			/// 文字列を分割して配列を格納します。
			/// </summary>
			/// <param name="text"> 入力に使う文字列 </param>
			void splitText(String text);
			
			/// <summary>
			/// 読み込み位置を一つ前に進めます。
			/// </summary>
			void forword();


		private:

			Array<Array<String>> input_list;	// 入力リスト

			int row = 0;	// 行

			int colum = -1;	// 列

			bool isOverflow = false;

		};

	}

}