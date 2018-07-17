#include"ReadSupporter.h"




String My::Data::ReadSupporter::readWord()
{
	
	forword();

#ifdef _DEBUG

	if (isOverflow)
	{
		Println(L"error > [ReadSupporter] オーバフローが起きました");

		return L"";
	}

#endif // _DEBUG
	
	return input_list[row][colum];

}




String My::Data::ReadSupporter::readLine()
{

	forword();

#ifdef _DEBUG

	if (isOverflow)
	{
		Println(L"error > [ReadSupporter] オーバフローが起きました");

		return L"";
	}

#endif // _DEBUG


	String line = L"";

	for (; colum < input_list[row].size(); ++colum)
	{

		line += input_list[row][colum];

		if (colum < input_list[row].size() - 1)
		{
			line += L" ";
		}

	}

	return line;

}




void My::Data::ReadSupporter::splitText(String text)
{

	for (const String& line : text.split(L'\n'))
	{
		
		Array<String> input_line;

		for (const String& word : line.split(L' '))
		{

			input_line.emplace_back(word);

		}

		input_list.emplace_back(input_line);

	}

}




void My::Data::ReadSupporter::forword()
{
	++colum;

#ifdef _DEBUG

	if (isOverflow) { return; }

#endif // _DEBUG

	if (colum >= input_list[row].size())
	{
		colum = 0;

		++row;
	}

	if (row >= input_list.size())
	{
		isOverflow = true;
	}
}
