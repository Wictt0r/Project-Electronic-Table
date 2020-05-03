#pragma warning(disable:4996)
#include "Table.h"

Table::Table():width(0),height(0),matrix(nullptr){}

Table::~Table()
{
	for (size_t i = 0; i < height; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] file_name;
}

void Table::split_input(char*input, size_t lenght)
{

	size_t counter = 1;
	for (size_t i = 0; i < lenght; ++i)
	{
		if (input[i] == ' ')
		{
			counter++;
			while (input[i] == ' ')
				i++;
		}
	}
	char** split_input = new (std::nothrow) char* [counter];
	if (split_input == nullptr)
	{
		std::cout << "Error with memory allocation" << std::endl;
		return;
	}
	size_t split_input_counter = 0;
	char* token = strtok(input, " ");
	split_input[split_input_counter] = new(std::nothrow) char[strlen(token) + 1];
	if (split_input[split_input_counter] == nullptr)
	{
		std::cout << "Error\n";
	}
	strcpy(split_input[split_input_counter], token);
	++split_input_counter;
	while (token != nullptr)
	{
		token = strtok(nullptr, " ");
		if (token != nullptr)
		{
			split_input[split_input_counter] = new(std::nothrow) char[strlen(token) + 1];
			if (split_input[split_input_counter] == nullptr)
			{
				std::cout << "Error";
				delete[] token;
				for (size_t i = 0; i <= split_input_counter; ++i)
					delete[] split_input[i];
				delete []split_input;
				return;
			}
			strcpy(split_input[split_input_counter], token);
			++split_input_counter;
		}
	}
	detect_function(split_input, counter);
	delete[] token;
	for (size_t i = 0; i < split_input_counter; ++i)
		delete[] split_input[i];
	delete[] split_input;
	return;
}

void Table::detect_function(char** split_input, size_t lenght)
{
	if (strcmp(split_input[0],"open")==0)
	{
		if (open(split_input[1]) == true)
		{
			std::cout << "Table added successfully\n";
			return;
		}
		else
		{
			std::cout << "Error table did not load\n";
			return;
		}
	}
	if (strcmp(split_input[0], "close") == 0)
	{
		//????
	}
	if (strcmp(split_input[0], "print") == 0)
	{
		print();
		return;
	}
	if (strcmp(split_input[0], "edit") == 0)
	{

	}
	if (strcmp(split_input[0], "save") == 0 && strcmp(split_input[1],"as")==0 && lenght==3)
	{

	}
	if (strcmp(split_input[0], "save") == 0 && lenght==1)
	{

	}
	if (strcmp(split_input[0], "help") == 0)
	{

	}
	if (strcmp(split_input[0], "exit") != 0 || lenght > 1)
		std::cout << "Invalid input\n";
}

bool Table::open(char* _file)
{
	file_name = new(std::nothrow)char[strlen(_file) + 1];
	if (file_name == nullptr)
		return false;
	strcpy(file_name, _file);
	std::ifstream file;
	file.open(_file);
	size_t width_counter=1;
	height = 0;
	width = 1;
	file.seekg(0);
	while (file.good())
	{
		char character;
		file.get(character);
		if (character == ',')
			width_counter++;
		if (character == '\n' || file.eof()==true)
		{
			height++;
			if (width < width_counter)
				width = width_counter;
			width_counter = 1;
		}
	}
	matrix = new(std::nothrow)  Cell*[height];
	if (matrix == nullptr)
	{
		file.close();
		return false;
	}
	for (size_t i = 0; i < height; ++i)
	{
		matrix[i] = new(std::nothrow) Cell[width];
		if (matrix[i] == nullptr)
		{
			for (size_t p = 0; p < i; ++p)
				delete[] matrix[p];
			delete[] matrix;
			file.close();
			return false;
		}
	}
	size_t current_width = 0, current_height = 0;
	file.close();
	file.open(_file);
	while (file.good())
	{
		char word[100];
		file>>word;
		/*while (symbol == ' ')
		{
			file.get(symbol);
		}*/
		if (strcmp(word, "\n") == 0)
		{
			current_height++;
			current_width = 0;
			continue;
		}
		if (strcmp(word ,",")==0)
			continue;
		/*size_t counter = 2;
		char* word=new (std::nothrow)char[counter];
		if (word == nullptr)
		{
			return false; std::cout << "here2\n";
		}
		while (symbol != ',' && symbol!=' ')
		{
			char* word_temp;
			word_temp = new(std::nothrow)char[counter+2];
			if (word_temp == nullptr)
			{
				delete[] word;
				std::cout << "here1\n";
				return false;
			}
			strcpy(word_temp, word);
			word_temp[counter] = symbol;
			word_temp[counter + 1] = '\0';
			delete[] word;
			word = word_temp;
		}*/
		std::cout << word << std::endl;
		if (matrix[current_height][current_width].Initialize(word) == false)
		{
			
			std::cout << "Column:" << current_height + 1 << " Line:" << current_width;
			//add delete
			return false;
		}
		std::cout << matrix[current_height][current_width].get_initial_text() << std::endl;
		//delete[]word;
	}
	file.close();
	return true;
}

void Table::save()
{
	save_as(file_name);
	return;
}

void Table::save_as(char* _file)
{
	std::ofstream file;
	file.open(_file,std::ios::trunc);
	for (size_t i = 0; i < height && file.good(); ++i)
	{
		for (size_t j = 0; j < width &&file.good(); ++j)
		{
			//file << matrix[i][j];
		}
		file << '\n';
	}
	file.close();
}

void Table::print()
{
	//size_t max_lenght = 0;
	/*for (size_t i = 0; i <width ; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{

		}
	}*/
	for (size_t i = 0; i < height; ++i)
	{
		
		for (size_t j = 0; j < width; ++j)
		{
			if (matrix[i][j].get_initial_text() != nullptr)
				std::cout << std::setw(10) << matrix[i][j].get_initial_text();
			else
				std::cout << " ";
			if (i != height - 1)
				std::cout << "|";
		}
		std::cout << std::endl;
	}
	return;
}
