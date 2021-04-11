

#include<string>
#include<map>
#include<fstream>
#include<iostream>	

#include<climits>

#include"algoritpht_fano.h"


using namespace std;

//проверка на тип данных курвор
bool check_true_type(string name_of_file)
{
	if (name_of_file.size() > 7)
	{
		if (name_of_file.substr(name_of_file.size() - 7) != ".curwor")
		{
			cout << "фаил который вы хотите разархивировать не типа .curwor" << endl;
			return 1;
		}
	}
	else
	{
		cout << "фаил который вы хотите разархивировать не типа .curwor" << endl;
		return 1;
	}
	return 0;
}

//возвращает бит из символа
bool get_bit(char num, int position)
{
	return num & (1 << position);
}

//ищет символ записанный в карту
void algoritpht_fano::find_and_input(char  symbol)
{
	for (quantity_iterator = quantity.begin(); quantity_iterator != quantity.end(); ++quantity_iterator)
	{
		if (quantity_iterator->second == symbol)
		{
			quantity.insert(pair<int, char>(quantity_iterator->first + 1, symbol));
			quantity.erase(quantity_iterator);
			return;
		}
	}
	quantity.insert(pair<int, char>(1, symbol));
}

void algoritpht_fano::strange_wood(string str, vector<bool> bit, map<char, vector<bool>> &Map)
{
	map<string, vector<bool>> ::iterator Iterator;
	if (str.size() == 1)
	{
		Map.insert(pair<char, vector<bool>>(str[0], bit));
		return;
	}
	string str0, str1; //создаем строки для будущего разделения строки которая пришла на две строки
	vector<bool> bit0 = bit, bit1 = bit;//записываем битовые последовательности в новые разделенные
	bit0.push_back(0);//в ветку 0 вписываем 0
	bit1.push_back(1);//в ветку 1 вписыввается 1

	for (int i = 0; i < str.size(); i++)//проходим по строке
	{
		if (i < (str.size() / 2)) //разделяется строка приблихзительно одинковой частоты
			str0.push_back(str[i]);
		else
			str1.push_back(str[i]);
	}
	strange_wood(str0, bit0, Map);//запускается функция на расчет ветки дальше
	strange_wood(str1, bit1, Map);
}


int algoritpht_fano::zip(string path_out, string path_in)

{
	char symbol, output_symbol = 0;

	vector<bool> bit0, bit1; //для хрения двоичных кодов к символам
	bit0.push_back(0); 
	bit1.push_back(1);

	map<char, vector<bool>> Map; //словарь для хранения кодировок фаила
	map < char, vector < bool >> ::iterator Map_iterator;

	string str0, str1, main_str;

	int counter_symbols_in_input_file = 0;

	file_input.open(path_out); //open file
	if (!file_input.is_open())
	{
		std::cout << "фаил который необходимо заархивировать не найден" << endl;
		return 1;
	}

	//подсчитываем количество символов в фаиле
	file_input.get(symbol);
	while (!file_input.eof()) 
	{
		find_and_input(symbol);
		counter_symbols_in_input_file++;
		file_input.get(symbol);
	}

	file_input.close();//закрываем фаил

	bool temp = false;

	for (--(quantity_iterator = quantity.end()); (quantity_iterator != quantity.begin()) || (quantity_iterator == quantity.begin()); --quantity_iterator)
	{//здесь он сортирует наоборот с конца мапа до начала...точнее проходит
		if (temp)//можно придумать разделение и получше
			str0.push_back(quantity_iterator->second);
		else
			str1.push_back(quantity_iterator->second);
		temp = !temp;

		main_str.push_back(quantity_iterator->second);
		if (quantity_iterator == quantity.begin())
			break;
	}
	
	strange_wood(str0, bit0, Map);//надо бы вот тут потестить, те ли коды оно дает...пока что давало те...но...
	strange_wood(str1, bit1, Map);

	//зашифровка сообщения и создание фаила
	file_input.open(path_out);
	file_output.open(path_in + ".curwor", ios::out | ios::binary);

	//записываем кодировки в фаил
	
	for (; counter_symbols_in_input_file != 0; counter_symbols_in_input_file /= 10 ) //выписываем количество букв в фаиле
	{
		file_output <<  counter_symbols_in_input_file % 10;
	}
	file_output << '\1';//специсмвол показывающий что дальше, символы, которые в фаиле закодируются
	file_output << main_str;//строка символов
	file_output << '\2';//спецсимвол начала текста

	//перекодируем входящие символы и кодируем их и выводим их в выходящий фаил
	int counter_in_symbol = 7;
	file_input.get(symbol);
	while (!file_input.eof())
	{
		
		//ищем код данного символа
		for (Map_iterator = Map.begin(); Map_iterator->first != symbol; ++Map_iterator) {}
		
		int i;
		for (i = 0; (i < Map_iterator->second.size()) && counter_in_symbol >= 0; i++, counter_in_symbol--)
		{
			if (Map_iterator->second[i])
				output_symbol |= (1 << counter_in_symbol);
			else
				output_symbol &= ~(1 << counter_in_symbol);
		}
		if (counter_in_symbol == -1)
		{
			file_output << output_symbol;
			counter_in_symbol = 7;
			output_symbol = '\0';
			if (i < Map_iterator->second.size())
			{
				for ( ; i < Map_iterator->second.size(); i++, counter_in_symbol--)
				{
					if (Map_iterator->second[i])
						output_symbol |= (1 << counter_in_symbol);
					else
						output_symbol &= ~(1 << counter_in_symbol);
				}
			}
		}
		file_input.get(symbol);
	}
	if (counter_in_symbol != 7)
		file_output << output_symbol;
	std::cout << "task is successful";
	file_input.close();
	file_output.close();
	return 0;
}

int algoritpht_fano::unzip(string path_out, string path_in)
{
	//проверка на тип данных
	if (check_true_type(path_out))
		return 1;


	file_input.open(path_out, ios::in|ios::binary); //открытие фаила откуда 
	//проверка на открытие фаила
	if (!file_input.is_open())
	{
		std::cout << "фаил не найден" << endl;
		return 1;
	}


	vector<bool> bit0, bit1; //для кодирования
	bit0.push_back(0);
	bit1.push_back(1);

	map<char, vector<bool>> Map; //для хранения кодировки
	map < char, vector < bool >> ::iterator Map_iterator;

	string str0, str1;

	char input_symbol;
	bool temp = false;

	int quantity_symbols_in_input_file = 0;
	//считывание количествоа символов, которые закодированы
	for (int i = 1; ;i *= 10)
	{
		char temp;
		file_input.get(temp);
		if (temp == '\x01')
			break;
		quantity_symbols_in_input_file += (temp - 0x30) * i;
	}

	//считывание строки
	for (;;)
	{
		file_input.get(input_symbol);
		if (input_symbol == '\x02')
			break;
		if (temp)
			str0.push_back(input_symbol);
		else
			str1.push_back(input_symbol);
		temp = !temp;
	}
	strange_wood(str0, bit0, Map);
	strange_wood(str1, bit1, Map);


	file_output.open(path_out + ".txt");
	int counter_symbols = 7;
	vector<bool> code_of_symbol;
	 
	file_input.get(input_symbol);//считываем символ
	while (!file_input.eof()) //цикл прохождящий по входящему фаилу
	{ 
		//ищем код данного символа
		for (counter_symbols; counter_symbols >= 0; counter_symbols--) //проходим внутри байта 
		{//да что ты здесь написал...
			code_of_symbol.push_back(get_bit(input_symbol, counter_symbols));//добавляем новый бит в вектор битов
			for (Map_iterator = Map.begin(); Map_iterator != Map.end(); ++Map_iterator)//ищем обнавленный вектор битов
			{
				if (Map_iterator->second == code_of_symbol)//если нашли, то выписываем его ключ в фаил
				{
					file_output << Map_iterator->first;
					code_of_symbol.clear();
					quantity_symbols_in_input_file--;
					break;
				}
				//если не нашли в мапе выходим из мапы
			}
			//и внутри байта
			if (quantity_symbols_in_input_file == 0)
				break;
		}
		//если не нашли в этом байте, продолжим поиски в другом
		counter_symbols = 7;
		file_input.get(input_symbol);//считываем символ
	}

	std::cout << "task is successful";
	file_output.close();
	file_input.close();
	return 0;
}
