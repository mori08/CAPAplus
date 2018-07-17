#include "Searcher.h"



bool My::Data::Searcher::startSearchThread(const SearchCriteria & criteria)
{
	if (criteria.last < criteria.first) { return false; }

	if (!criteria.plan && !criteria.deadline) { return false; }

	if (!criteria.title && !criteria.tags && !criteria.detail) { return false; }

	m_result_list.clear();

	m_search_thread = std::thread([this, criteria](){ this->search(criteria); });

	m_thread_running = true;

	return true;
}



bool My::Data::Searcher::joinSearchThread()
{
	if (!m_thread_running||!m_search_thread.joinable())
	{
		return false;
	}

	m_thread_running = false;

	m_search_thread.join();

	return true;
}



void My::Data::Searcher::storeResult(Array<Card> & card_list)
{
	card_list = std::move(m_result_list);

	m_result_list = std::move(Array<Card>());
}



void My::Data::Searcher::search(const SearchCriteria & criteria)
{
	Note::accessBook().searchCard(criteria, m_result_list);
}
