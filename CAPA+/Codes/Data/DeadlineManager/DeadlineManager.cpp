#include"DeadlineManager.h"

#include"../ReadSupporter/ReadSupporter.h"


const String DEADLINE_LIST_TEXT = L"Assets/Data/DeadlineList.txt";

const String EMPTY = L"empty";



void My::Data::DeadlineManager::setStatus(Card & card)
{
	int sub = card.day - Day();

	if (card.check)
	{
		if (sub >= 0)
		{
			card.status = L"完了済";
			card.color = Color(0, 200, 0);
		}

		if (sub < 0)
		{
			card.status = L"済";
			card.color = Color(0, 128);
		}

	}

	else
	{
		if (sub > 0 && sub <= 3)
		{
			card.status = L"あと" + ToString(sub) + L"日";
			card.color = Color(255, sub * 50, 0);
		}
		if (sub == 0)
		{
			card.status = L"今日中";
			card.color = Color(255, 0, 0);
		}
		if (sub < 0)
		{
			card.status = ToString(-sub) + L"日遅れ";
			card.color = Color(128, 0, 0);
		}
	}
}



Array<My::Data::Card> My::Data::DeadlineManager::loadDeadlineList()
{
	Array<Card> card_list;

	TextReader reader(DEADLINE_LIST_TEXT);

	String line;

	for (int i = 0; reader.readLine(line); ++i)
	{
		if (line == EMPTY) { continue; }

		Card deadline;

		deadline.deadline_id = i;

		deadline.day = Day(line.split(L' ')[0]);

		deadline.check = (line.split(L' ')[1] == L"1") ? true : false;

		searchDeadline(deadline);

		setStatus(deadline);

		card_list.emplace_back(deadline);
	}

	reader.close();

	std::sort(card_list.begin(), card_list.end(), compareDeadlineCard);

	return card_list;

}



Array<My::Data::Card> My::Data::DeadlineManager::loadNocheckDeadlineList()
{
	Array<Card> deadlineList = loadDeadlineList();

	Array<Card> rtn;

	for (const auto& deadline : deadlineList)
	{
		if (!deadline.check)
		{
			rtn.emplace_back(deadline);
		}
	}

	return rtn;
}



int My::Data::DeadlineManager::addDeadline(const Day & day)
{
	int id = -1;					// 登録する識別番号

	int row;						// 探索中の行数

	TextReader reader(DEADLINE_LIST_TEXT);

	Array<String> deadline_list;	// 締め切りリスト

	String line;					// 取得した文字列の一時保管


	for (row = 0; reader.readLine(line); row++)
	{

		if (line == EMPTY&&id == -1)		// 空いている識別番号があったとき
		{
			id = row;
			line = day.toString() + L" 0";
		}

		deadline_list.emplace_back(line);	// 締め切りリストに保管

	}

	if (id == -1)							// 空きがなかったとき
	{
		id = row;

		deadline_list.emplace_back(day.toString() + L" 0");
	}

	reader.close();



	TextWriter writer(DEADLINE_LIST_TEXT);

	for (const auto& deadline : deadline_list)
	{

		writer.writeln(deadline);

	}

	writer.close();


	return id;
}



void My::Data::DeadlineManager::deleteDeadline(int id)
{
	Array<String> deadline_list;

	TextReader reader(DEADLINE_LIST_TEXT);

	String line;

	for (int i = 0; reader.readLine(line); ++i)
	{

		if (i == id) { line = EMPTY; }

		deadline_list.emplace_back(line);

	}

	reader.close();



	TextWriter writer(DEADLINE_LIST_TEXT);

	for (const auto& deadline : deadline_list)
	{

		writer.writeln(deadline);

	}

	writer.close();
}



bool My::Data::DeadlineManager::compareDeadlineCard(const Card & c1, const Card & c2)
{
	static Day today = Day();

	if (!c1.check&& c2.check) { return true; }
	if (c1.check && !c2.check) { return false; }

	if (!c1.check)
	{
		if (c1.day < c2.day) { return true; }

		return false;
	}

	if (!(c1.day < today) && c2.day < today) { return true; }
	if (c1.day < today && !(c2.day < today)) { return false; }

	if (c1.day < c2.day) { return true; }

	return false;
}



void My::Data::DeadlineManager::searchDeadline(Card & deadline)
{
	TextReader textReader(L"Assets/Data/Note/" + deadline.day.toString() + L".txt");

	// 対応するテキストファイルが存在しないとき
	if (!textReader.isOpened())
	{
		return;
	}


	ReadSupporter reader(textReader);

	reader.readWord();

	int size = reader.readInteger();

	if (size < 0)
	{
		return;
	}

	for (int i = 0; i < size; ++i)
	{
		int row, tag_size, id;

		String title, detail;

		title = reader.readLine();

		reader >> row >> id >> tag_size;

		if (tag_size < 0)
		{
			return;
		}

		for (int j = 0; j < tag_size; ++j)
		{
			reader.readLine();
		}

		if (row < 0)
		{
			return;
		}

		detail = L"";

		for (int j = 0; j < row; ++j)
		{
			detail += reader.readLine() + L"\n";
		}


		if (deadline.deadline_id == id)
		{
			deadline.title = title;
			deadline.detail = detail;
			break;
		}

	}

	textReader.close();
}
