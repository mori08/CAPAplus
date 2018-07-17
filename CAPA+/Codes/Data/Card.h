#pragma once


#include"Day\Day.h"


namespace My
{

	namespace Data
	{

		struct Card
		{
			Day				day;			// ���t

			String			title;			// ���O

			String			detail;			// �ڍ�

			int				deadline_id;	// ���ؔԍ�(�\��̂Ƃ�-1)

			Array<String>	tags;			// �^�O

			bool			check;			// �`�F�b�N

			String			status;			// ���

			Color			color;			// ��Ԃ�`�悷��F
		};

		/// <summary>
		/// �󔒃J�[�h���쐬���܂��B
		/// </summary>
		/// <param name="day"> ���t </param>
		/// <returns> �󔒃J�[�h </returns>
		Card createNewCard(const Day & day);

	}
}