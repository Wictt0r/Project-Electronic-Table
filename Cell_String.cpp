#include "Cell_String.h"
Cell_String::Cell_String(const Cell_String& other)
{
	set_type(other.type);
	set_initial_text(other.initial_text);
}
Cell_String::Cell_String(char* input)
{
	initial_text = new(std::nothrow) char[strlen(input) + 1];
	if (initial_text != nullptr)
		strcpy(initial_text, input);
	strcpy(type, "string");
}

Cell_String::Cell_String():Cell()
{
}

float Cell_String::value()
{
	float number;
	size_t dot_counter = 0,i=1;
	if (initial_text[i] == '+' || initial_text[i] == '-')
		++i;
	
	for (i; i < strlen(initial_text)-1; ++i)
	{
		if ((initial_text[i] < '0' || initial_text[i]>'9') && initial_text[i] != '.')
			return 0;
		if (initial_text[i] == '.')
			dot_counter++;
	}
	if (dot_counter > 1)
		return 0;
	if (dot_counter == 1 || dot_counter==0)
	{
		return Cell::str_to_float(remove_quotes());
	}
}

char* Cell_String::print()
{
	return remove_quotes();
}

Cell* Cell_String::copy()
{
	return new (std::nothrow) Cell_String(*this);
}

char* Cell_String::remove_quotes()
{
	size_t word_lenght = strlen(initial_text) - 1;
	for (size_t i = 1; i < strlen(initial_text) - 1; ++i)
	{
		if (initial_text[i] == '\\')
		{
			word_lenght--;
		}
	}
	char* new_word = new(std::nothrow)char[word_lenght];
	if (new_word == nullptr)
		return initial_text;
	size_t symbol_counter = 0;
	for (size_t i = 1; i < strlen(initial_text) - 1; ++i)
	{
		if (initial_text[i] == '\\' && (initial_text[i+1]=='\\' || initial_text[i+1]=='\"'))
		{
			new_word[symbol_counter] = initial_text[i+1];
			symbol_counter++;
			++i;
			continue;
		}
		new_word[symbol_counter] = initial_text[i];
		symbol_counter++;
	}
	new_word[symbol_counter] = '\0';

	return new_word;
}
