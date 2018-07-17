#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// �������W�����͂̂悤�ɏ�������̂��T�|�[�g
		/// </summary>
		class ReadSupporter
		{

		public:

			/// <summary>
			/// TextReader����ReadSupporter���쐬���܂��B
			/// </summary>
			/// <param name="reader"> �ǂݍ��݂����e�L�X�g�t�@�C�� </param>
			ReadSupporter(TextReader& reader)
			{
				splitText(reader.readAll());
			}


		public:

			/// <summary>
			/// ���͂𕶎���Ƃ��đ�����܂��B
			/// </summary>
			/// <param name="value"> ����� </value>
			/// <returns> *this </returns>
			ReadSupporter& operator >> (String & value)
			{
				value = readWord();

				return *this;
			}

			/// <summary>
			/// ���͂𐮐��Ƃ��đ�����܂��B
			/// </summary>
			/// <param name="value"> ����� </value>
			/// <returns> *this </returns>
			ReadSupporter& operator >> (int& value)
			{
				value = readInteger();

				return *this;
			}


		public:

			/// <summary>
			/// ���͂𕶎���Ƃ��Ď擾���܂��B
			/// </summary>
			/// <returns> �擾���镶���� </returns>
			String readWord();

			/// <summary>
			/// ���͂����̉��s�܂ŕ�����Ƃ��Ď擾���܂��B
			/// </summary>
			String readLine();

			/// <summary>
			/// ���͂𐮐��l�Ƃ��Ď擾���܂��B
			/// </summary>
			/// <param name="defalutValue"> �ǂݍ��݂Ɏ��s�����Ƃ��̒l </param>
			/// <returns> �擾���鐮���l </returns>
			int readInteger(int defalutValue = -1)
			{
				return ParseOr<int>(readWord(), defalutValue);
			}


		private:

			/// <summary>
			/// ������𕪊����Ĕz����i�[���܂��B
			/// </summary>
			/// <param name="text"> ���͂Ɏg�������� </param>
			void splitText(String text);
			
			/// <summary>
			/// �ǂݍ��݈ʒu����O�ɐi�߂܂��B
			/// </summary>
			void forword();


		private:

			Array<Array<String>> input_list;	// ���̓��X�g

			int row = 0;	// �s

			int colum = -1;	// ��

			bool isOverflow = false;

		};

	}

}