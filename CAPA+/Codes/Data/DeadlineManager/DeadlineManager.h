#pragma once

#include"../Day/Day.h"

#include"../Card.h"


namespace My
{

	namespace Data
	{		


		/// <summary> ���؂�������������̃N���X�ɂ܂Ƃ߂� </summary>
		class DeadlineManager
		{

		public:

			/// <summary>
			/// �J�[�h�̃X�e�[�^�X��ݒ肵�܂��B
			/// </summary>
			/// <param name="card"> �J�[�h </param>
			static void setStatus(Card & card);

			/// <summary>
			/// ���؂�T�����z��Ƃ��ďo�͂��܂��B
			/// </summary>
			/// <returns> ���؂̔z�� </returns>
			static Array<Card> loadDeadlineList();

			/// <summary>
			/// ���`�F�b�N�̒��ߐ؂��T�����z��Ƃ��ďo�͂��܂��B
			/// </summary>
			/// <returns> ���`�F�b�N�̒��؂̔z�� </returns>
			static Array<Card> loadNocheckDeadlineList();

			/// <summary>
			/// ���؂�ǉ����܂��B
			/// </summary>
			/// <param name="day"> ���t </param>
			/// <returns> �ݒ肳�ꂽ���ؔԍ���Ԃ��܂��B </returns>
			static int addDeadline(const Day & day);

			/// <summary>
			/// ���؂��폜���܂��B
			/// </summary>
			/// <param name="id"> ���ؔԍ� </param>
			static void deleteDeadline(int id);

		private:

			/// <summary>
			/// �J�[�h����؂Ƃ��ėD�揇�ʂ��r���܂�
			/// </summary>
			/// <param name="c1"> �J�[�h�P </param>
			/// <param name="c2"> �J�[�h�Q </param>
			/// <returns> �D�揇�ʂ�c2�̂ق�����̂Ƃ� true , �����łȂ��Ƃ� false </param>
			static bool compareDeadlineCard(const Card & c1, const Card & c2);

			/// <summary>
			/// Deadline��Day����title��detail��ݒ肵�܂��B
			/// </summary>
			/// <param name="deadline"> ���؏�� </param>
			static void searchDeadline(Card& deadline);

		};

	}

}