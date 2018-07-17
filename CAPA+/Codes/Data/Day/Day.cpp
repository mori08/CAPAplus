#include"Day.h"




My::Data::Day::Day()
{

	const DateTime today = DateTime::Now();

	m_year	= today.year;
	m_month = today.month;
	m_date  = today.day;

	check();

}




My::Data::Day::Day(int year, int month, int date)
{

	m_year  = year;
	m_month = month;
	m_date  = date;

	check();

}



My::Data::Day::Day(const String & str)
{
	m_year = Parse<int>(str.split('/')[0]);
	m_month = Parse<int>(str.split('/')[1]);
	m_date = Parse<int>(str.split('/')[2]);

	check();
}




My::Data::Day My::Data::Day::operator + (int value)const
{
	
	if (value < 0) { return *this - Abs(value); }

	int y = m_year;
	int m = m_month;
	int d = m_date + value;
		
	while (d > maxDate(y, m))	// “ú‚ª³‚µ‚¢’l‚ğ¦‚·‚Ü‚ÅŒJ‚è•Ô‚·
	{

		d -= maxDate(y, m);

		++m;

		if (m == 13) { m = 1; ++y; }

	}

	return Day(y, m, d);

}




My::Data::Day My::Data::Day::operator - (int value) const
{
	
	if (value < 0) { return *this + Abs(value); }

	int y = m_year;
	int m = m_month;
	int d = m_date - value;;

	while (d < 1)	// “ú‚ª³‚µ‚¢’l‚ğ¦‚·‚Ü‚ÅŒJ‚è•Ô‚·
	{

		--m;

		if (m == 0) { m = 12; --y; }

		d += maxDate(y, m);

	}

	return Day(y, m, d);

}




int My::Data::Day::operator - (const Day & day) const
{
	
	if (*this < day) { return -(day - *this); }

	int sub = 0;

	for (int y = day.m_year; y < m_year; ++y)
	{

		sub += isLeap(y) ? 366 : 365;

	}

	return sub + daysFromNewYears() - day.daysFromNewYears();

}




bool My::Data::Day::operator < (const Day & day) const
{

	if (m_year < day.m_year)   { return true;  }
	if (m_year > day.m_year)   { return false; }

	if (m_month < day.m_month) { return true;  }
	if (m_month > day.m_month) { return false; }

	if (m_date < day.m_date)   { return true;  }
	if (m_date > day.m_date)   { return false; }

	return false;

}





int My::Data::Day::maxDate(int year, int month)
{
	
	switch(month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 2:
		return isLeap(year) ? 29 : 28;

	default:
#ifdef _DEBUG
		Println(L"error > My::Data::Day::maxData(int,int)");
#endif // _DEBUG
		return 31;

	}

}



bool My::Data::Day::changeAbleStringToDay(const String & str)
{
	Array<String> split_text = str.split('/');

	if (split_text.size() != 3) { return false; }

	int year = Parse<int>(split_text[0]);
	int month = Parse<int>(split_text[1]);
	int date = Parse<int>(split_text[2]);

	if (year < 1582 || date > 9999 || month < 1 || month >12 || date<1 || date>maxDate(year, month))
	{
		return false;
	}

	return true;
}




int My::Data::Day::dayOfWeak() const
{
	int y = m_year;

	int m = m_month;

	if (m == 1 || m == 2)
	{
		y--;

		m += 12;
	}

	return(y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + m_date) % 7;
}



int My::Data::Day::daysFromNewYears() const
{

	int sub = 0;

	for (int i = 1; i < m_month; ++i)
	{
		sub += maxDate(m_year, i);
	}

	return sub + m_date;

}
