#pragma once


#include<Siv3D.hpp>


namespace My
{

	namespace Data
	{

		/// <summary>
		/// ���t
		/// </summary>
		class Day
		{

		private:

			int m_year;

			int m_month;

			int m_date;

		public:

			/// <summary> 
			/// �����̓��t���쐬���܂��B
			/// </summary>
			Day();

			/// <summary>
			/// �R�̐����l������t���쐬���܂��B
			/// </summary>
			/// <param name="year" > �N </param>
			/// <param name="month"> �� </param>
			/// <param name="date" > �� </param>
			Day(int year, int month, int date);


			/// <summary>
			/// �����񂩂���t�𐶐����܂��B
			/// </summary>
			/// <param name="str"> ������ ��:L"2018/1/1" </param>
			Day(const String & str);


		public:

			/// <summary>
			/// ���t���r���܂��B
			/// </summary>
			/// <param name="day"> ��r���������t </param>
			/// <returns> �������t�̂Ƃ�true , �����łȂ��Ƃ� false </returns>
			bool operator == (const Day & day)const
			{
				return m_year == day.m_year&&m_month == day.m_month&&m_date == day.m_date;
			}

			/// <summary>
			/// ���Ƃ̓��t���������i�߂����t���擾���܂��B
			/// </summary>
			/// <param name="value"> �i�߂������� </param>
			/// <returns> ������i�߂����� </returns>
			Day operator + (int value)const;

			/// <summary>
			/// ���Ƃ̓��t���������߂������t���擾���܂��B
			/// </summary>
			Day operator - (int value)const;
			
			/// <summary>
			/// ���t���r���A���̓����̍����v�Z���܂��B
			/// </summary>
			/// <param name="day"> ��r�Ώۂ̓��t </param>
			/// <returns> ���̓��� </returns>
			/// <remarks> *this��day �̂Ƃ��߂�l�͕��ɂȂ�܂��B </remarks>
			int operator - (const Day& day)const;

			/// <summary>
			/// ���t�̑O����r���܂��B
			/// </summary>
			/// <param name="day"> ��r�Ώۂ̓��t </param>
			/// <returns> *this���O�̂Ƃ� true, �����łȂ��Ƃ� false </returns>
			bool operator < (const Day& day)const;


		public:

			/// <summary>
			/// ���̔N���[�N�����ׂ܂��B
			/// </summary>
			/// <param name="year"> ���ׂ�N </param>
			/// <returns> �[�N�̂Ƃ� true,�����łȂ��Ƃ� false </returns>
			static bool isLeap(int year) 
			{ 
				return year % 4 == 0 && year % 100 != 0 || year % 400 == 0; 
			}

			/// <summary>
			/// ���̌��̍ŏI���������܂��B
			/// </summary>
			/// <param name="year" > �N(�[�N�����ׂ邽�߂ɗ��p) </param>
			/// <param name="month"> ��							</param> 
			/// <returns> ���̌��̍ŏI�� (����) 2004�N2�� �� 29 
			static int maxDate(int year, int month);

			/// <summary>
			/// �����񂪓��t�ɕϊ��\���Ԃ��܂��B
			/// </summary>
			/// <param name="str"> ������ </param>
			/// <returns> �ϊ��\�ȏꍇ true , �����łȂ��ꍇ false </returns>
			static bool changeAbleStringToDay(const String & str);

			/// <summary>
			/// Day�N���X�̕�����\�����쐬���܂��B
			/// </summary>
			/// <returns> Day�N���X�̕�����\�� </returns>
			String toString()const
			{
				check();

				return ToString(m_year) + L"/" + ToString(m_month) + L"/" + ToString(m_date);
			}

			/// <summary>
			/// ���t�ɑΉ������t�@�C���p�X���쐬���܂��B
			/// </summary>
			/// <returns> �t�@�C���p�X </returns>
			FilePath getFilePath()const
			{
				return L"Assets/Data/Note/" + toString() + L".txt";
			}

			/// <summary>
			/// �N���擾���܂��B
			/// </summary>
			/// <returns> �N </returns>
			int getYear()const
			{
				return m_year;
			}

			/// <summary>
			/// �����擾���܂��B
			/// </summary>
			/// <returns> �� </returns>
			int getMonth()const
			{
				return m_month;
			}

			/// <summary>
			/// �����擾���܂��B
			/// </summary>
			/// <returns> �� </returns>
			int getDate()const
			{
				return m_date;
			}

			/// <summary>
			/// �j���̎擾���܂��B
			/// </summary>
			/// <returns> ���j�� - 0 , ���j�� - 1 , �c , �y�j�� - 6 �Œl��Ԃ��܂��B </returns>
			/// <remarks> �c�F���[�̌�����p���� </remarks>
			int dayOfWeak()const;

		private:

			/// <summary>
			/// �N�������������l���m�F����
			/// </summary>
			/// <remarks> �f�o�b�O���[�h��p </remarks>
			void check()const
			{
			#ifdef _DEBUG

				// �c�F���[�̌������1582�N���O�̔N�������G���[�Ƃ���
				// �f�[�^�Ǘ��̓s����9999�N����̔N�������G���[�Ƃ���

				if (m_year < 1582 || m_date > 9999 || m_month < 1 || m_month >12 || m_date<1 || m_date>maxDate(m_year, m_month))
				{

					Println(L"error > �N�������s�K�؂ł� : ", toString());

				}

			#endif // _DEBUG
			}

			/// <summary>
			/// �P���P������ǂꂾ�����������������v�Z���܂��B
			/// </summary>
			/// <returns> �v�Z���� </returns>
			/// <remarks> �P���P���� 1 �Ƃ��Ēl��Ԃ��܂��B </remarks>
			int daysFromNewYears()const;

		};

	}

}