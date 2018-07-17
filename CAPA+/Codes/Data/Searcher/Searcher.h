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

			Array<Card> m_result_list;    // �������ʂ��i�[���郊�X�g

			std::thread m_search_thread;  // ���������s����X���b�h

			bool        m_thread_running; // �X���b�h�������Ă��邩�ǂ��� 

		public:

			Searcher()
				:m_thread_running(false)
			{}

			~Searcher()
			{
				if (!m_thread_running) { return; }

#ifdef _DEBUG
				Println(L"warning > �����X���b�h���I�������Ă��������B");
#endif // _DEBUG

				m_search_thread.join();
			}

		public:

			/// <summary>
			/// �ʃX���b�h�𓮂����J�[�h��T�����܂��B
			/// </summary>
			/// <param name="criteria"> �������� </param>
			/// <returns> �����ɐ��������Ƃ� true , ���s�����Ƃ� false </returns>
			/// <remarks> �K���������I�������Ă�����s���Ă��������B </remarks>
			bool startSearchThread(const SearchCriteria & criteria);

			/// <summary>
			/// �������I�����Ă���Ƃ��A�X���b�h��join���܂��B
			/// </summary>
			/// <returns> �I�����Ă����Ƃ� true , �����łȂ��Ƃ� false </returns>
			bool joinSearchThread();

			/// <summary>
			/// �������ʂ��i�[���܂��B
			/// </summary>
			/// <param name="card_list"> ���ʂ��i�[���郊�X�g </param>
			void storeResult(Array<Card> & card_list);

		private:

			/// <summary>
			/// �J�[�h���������܂��B
			/// </summary>
			/// <param name="criteria"> �������� </param>
			void search(const SearchCriteria & criteria);

		};

	}

}