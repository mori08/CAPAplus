#include"Note.h"

#include"../ReadSupporter/ReadSupporter.h"

#include<queue>



// -----------------------------------------------------------------------------------------
//	Bookクラス 
// -----------------------------------------------------------------------------------------



void My::Data::Note::Book::readAllText()
{
	std::queue<FilePath> Q;

	Q.push(L"Assets/Data/Note");

	while (!Q.empty())
	{
		FilePath path = Q.front(); Q.pop();

		if (FileSystem::IsFile(path))
		{
			Note note = readText(path);

			m_note_map[note.m_day] = note;
		}

		path += L"/";

		for (const auto & content : FileSystem::DirectoryContents(path))
		{
			Q.push(path + FileSystem::FileName(content));
		}
	}
}



void My::Data::Note::Book::writeAllText()const
{
	for (auto itr = m_note_map.begin(); itr != m_note_map.end(); ++itr)
	{
		writeText(itr->second);
	}
}



void My::Data::Note::Book::searchCard(const SearchCriteria & criteria,Array<Card> & result) const
{
	result.clear();

	for (auto itr = m_note_map.begin(); itr != m_note_map.end(); ++itr)
	{
		if (criteria.last < itr->first)  break;

		if (itr->first < criteria.first) continue;

		Array<Card> cards = itr->second.searchCard(criteria);

		result.insert(result.end(), cards.begin(), cards.end());
	}
}



My::Data::Note My::Data::Note::Book::readText(const FilePath & filepath)
{
#pragma region Format
	/*

	予定の数
	※ タイトル
	※ 行数 締め切り番号 タグの数
	※ タグ*n行
	※ 詳細

	(※を予定の数だけ繰り返し)

	*/
#pragma endregion

	Note note;

	TextReader textReader(filepath);

	// 対応するテキストファイルが存在しないとき
	if (!textReader.isOpened())
	{
		return note;
	}

	note.m_error = false;

	note.m_is_dirty = false;

	note.m_plan_list.clear();

	note.m_deadline_list.clear();


	ReadSupporter reader(textReader);
	
	note.m_day = Day(reader.readWord());
	
	int size = reader.readInteger();

	if (size < 0)
	{
		note.sendErrorMessage();

		return note;
	}

	for (int i = 0; i < size; ++i)
	{
		Card card;

		card.day = note.m_day;

		int row, tag_size;

		card.title = reader.readLine();

		reader >> row >> card.deadline_id >> tag_size;

		if (tag_size < 0)
		{
			note.sendErrorMessage();

			return note;
		}

		for (int j = 0; j < tag_size; ++j)
		{
			card.tags.emplace_back(reader.readLine());
		}

		if (row < 0)
		{
			note.sendErrorMessage();

			return note;
		}

		card.detail = L"";

		for (int j = 0; j < row; ++j)
		{
			card.detail += reader.readLine() + L"\n";
		}


		if (card.deadline_id == -1)
		{
			card.check = false;

			card.status = L"";

			card.color = Palette::Black;

			note.m_plan_list.emplace_back(card);
		}
		else
		{
			note.m_deadline_list.emplace_back(card);
		}

	}

	textReader.close();

	return note;
}



void My::Data::Note::Book::writeText(const Note & note)
{
	if (note.m_error || !note.m_is_dirty) { return; }

#pragma region Format
	/*

	予定の数
	※ タイトル
	※ 行数 締め切り番号 タグの数
	※ 詳細
	※ タグ*n行

	(※を予定の数だけ繰り返し)

	*/
#pragma endregion

	Array<Card> card_list = note.getPlanAndDeadlineList();

	if (card_list.size() == 0)
	{
		FileSystem::Remove(note.m_day.getFilePath());

		return;
	}

	TextWriter writer(note.m_day.getFilePath());

	writer.writeln(note.getDay().toString());

	writer.writeln(card_list.size());

	for (const auto& card : card_list)
	{

		writer.writeln(card.title);

		writer.writeln(card.detail.count(L"\n") + 1, L" ", card.deadline_id, L" ", card.tags.size());

		for (const auto& tag : card.tags)
		{
			writer.writeln(tag);
		}

		writer.writeln(card.detail);

	}

	writer.close();

}



// -----------------------------------------------------------------------------------------
//	Noteクラス 
// -----------------------------------------------------------------------------------------



My::Data::Note::Book My::Data::Note::book;



bool My::Data::Note::checkSearchCriteria(const Card & card, const SearchCriteria & criteria)
{
	for (const String & key : criteria.keywords)
	{

		if (criteria.title&&card.title.includes(key))
		{
			continue;
		}

		if (criteria.detail&&card.detail.includes(key))
		{
			continue;
		}

		if(criteria.tags)
		{
			for (const String & tag : card.tags)
			{
				if (tag.includes(key))
				{
					continue;
				}
			}
		}

		return false;
	}

	return true;
}



Array<My::Data::Card> My::Data::Note::getPlanAndDeadlineList() const
{
	Array<Card> plan = getPlanList(), deadline = getDeadlineList();

	plan.insert(plan.end(), deadline.begin(), deadline.end());

	return plan;
}



void My::Data::Note::changeCard(int index, const Card & card)
{
	m_is_dirty = true;

	if (index < m_plan_list.size())
	{
		m_plan_list[index] = card;

		return;
	}
	else if (index < m_plan_list.size() + m_deadline_list.size())
	{
		m_deadline_list[index - (int)m_plan_list.size()] = card;

		return;
	}

#ifdef _DEBUG

	Println(L"error > 対応するカードが見つかりません");

#endif // _DEBUG

}



void My::Data::Note::addCard(const Card & card)
{
	m_is_dirty = true;

	if (card.deadline_id == -1)
	{
		m_plan_list.emplace_back(card);
	}
	else
	{
		m_deadline_list.emplace_back(card);
	}
}



void My::Data::Note::deleteCard(int index)
{
	m_is_dirty = true;

	if (index < m_plan_list.size())
	{
		m_plan_list.erase(m_plan_list.begin() + index);

		return;
	}
	else if (index < m_plan_list.size() + m_deadline_list.size())
	{
		m_deadline_list.erase(m_deadline_list.begin() + (index - (int)m_plan_list.size()));

		return;
	}

#ifdef _DEBUG

	Println(L"error > 対応するカードが見つかりません");

#endif // _DEBUG
}



void My::Data::Note::read()
{
	if (!book.containsNote(m_day))
	{
		/*
			日付に対応するNoteがBookにないとき
			このNoteを新しいNoteとして
			Bookに格納します。
		*/

		m_error = false;

		m_is_dirty = false;

		book[m_day] = *this;

		return;
	}

	*this = book[m_day];

}



void My::Data::Note::write()const
{
	if (m_is_dirty)
	{
		book[m_day] = *this;
	}
}



Array<My::Data::Card> My::Data::Note::searchCard(SearchCriteria criteria) const
{
	Array<Card> result;

	if (criteria.plan)
	{
		for (const Card & card : m_plan_list)
		{
			if (checkSearchCriteria(card, criteria))
			{
				result.emplace_back(card);
			}
		}
	}

	if (criteria.deadline)
	{
		for (const Card & card : m_deadline_list)
		{
			if (checkSearchCriteria(card, criteria))
			{
				result.emplace_back(card);
			}
		}
	}

	return std::move(result);
}

