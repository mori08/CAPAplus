#include "Card.h"



My::Data::Card My::Data::createNewCard(const Day & day)
{
	Card new_card;

	new_card.day = day;

	new_card.title = L"";

	new_card.detail = L"";

	new_card.deadline_id = -1;

	new_card.tags.clear();

	new_card.check = false;

	new_card.color = Palette::Black;

	return new_card;
}
