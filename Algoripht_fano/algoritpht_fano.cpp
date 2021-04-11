

#include<string>
#include<map>
#include<fstream>
#include<iostream>	

#include<climits>

#include"algoritpht_fano.h"


using namespace std;

//�������� �� ��� ������ ������
bool check_true_type(string name_of_file)
{
	if (name_of_file.size() > 7)
	{
		if (name_of_file.substr(name_of_file.size() - 7) != ".curwor")
		{
			cout << "���� ������� �� ������ ��������������� �� ���� .curwor" << endl;
			return 1;
		}
	}
	else
	{
		cout << "���� ������� �� ������ ��������������� �� ���� .curwor" << endl;
		return 1;
	}
	return 0;
}

//���������� ��� �� �������
bool get_bit(char num, int position)
{
	return num & (1 << position);
}

//���� ������ ���������� � �����
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
	string str0, str1; //������� ������ ��� �������� ���������� ������ ������� ������ �� ��� ������
	vector<bool> bit0 = bit, bit1 = bit;//���������� ������� ������������������ � ����� �����������
	bit0.push_back(0);//� ����� 0 ��������� 0
	bit1.push_back(1);//� ����� 1 ������������ 1

	for (int i = 0; i < str.size(); i++)//�������� �� ������
	{
		if (i < (str.size() / 2)) //����������� ������ ��������������� ��������� �������
			str0.push_back(str[i]);
		else
			str1.push_back(str[i]);
	}
	strange_wood(str0, bit0, Map);//����������� ������� �� ������ ����� ������
	strange_wood(str1, bit1, Map);
}


int algoritpht_fano::zip(string path_out, string path_in)

{
	char symbol, output_symbol = 0;

	vector<bool> bit0, bit1; //��� ������ �������� ����� � ��������
	bit0.push_back(0); 
	bit1.push_back(1);

	map<char, vector<bool>> Map; //������� ��� �������� ��������� �����
	map < char, vector < bool >> ::iterator Map_iterator;

	string str0, str1, main_str;

	int counter_symbols_in_input_file = 0;

	file_input.open(path_out); //open file
	if (!file_input.is_open())
	{
		std::cout << "���� ������� ���������� �������������� �� ������" << endl;
		return 1;
	}

	//������������ ���������� �������� � �����
	file_input.get(symbol);
	while (!file_input.eof()) 
	{
		find_and_input(symbol);
		counter_symbols_in_input_file++;
		file_input.get(symbol);
	}

	file_input.close();//��������� ����

	bool temp = false;

	for (--(quantity_iterator = quantity.end()); (quantity_iterator != quantity.begin()) || (quantity_iterator == quantity.begin()); --quantity_iterator)
	{//����� �� ��������� �������� � ����� ���� �� ������...������ ��������
		if (temp)//����� ��������� ���������� � �������
			str0.push_back(quantity_iterator->second);
		else
			str1.push_back(quantity_iterator->second);
		temp = !temp;

		main_str.push_back(quantity_iterator->second);
		if (quantity_iterator == quantity.begin())
			break;
	}
	
	strange_wood(str0, bit0, Map);//���� �� ��� ��� ���������, �� �� ���� ��� ����...���� ��� ������ ��...��...
	strange_wood(str1, bit1, Map);

	//���������� ��������� � �������� �����
	file_input.open(path_out);
	file_output.open(path_in + ".curwor", ios::out | ios::binary);

	//���������� ��������� � ����
	
	for (; counter_symbols_in_input_file != 0; counter_symbols_in_input_file /= 10 ) //���������� ���������� ���� � �����
	{
		file_output <<  counter_symbols_in_input_file % 10;
	}
	file_output << '\1';//���������� ������������ ��� ������, �������, ������� � ����� ������������
	file_output << main_str;//������ ��������
	file_output << '\2';//���������� ������ ������

	//������������ �������� ������� � �������� �� � ������� �� � ��������� ����
	int counter_in_symbol = 7;
	file_input.get(symbol);
	while (!file_input.eof())
	{
		
		//���� ��� ������� �������
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
	//�������� �� ��� ������
	if (check_true_type(path_out))
		return 1;


	file_input.open(path_out, ios::in|ios::binary); //�������� ����� ������ 
	//�������� �� �������� �����
	if (!file_input.is_open())
	{
		std::cout << "���� �� ������" << endl;
		return 1;
	}


	vector<bool> bit0, bit1; //��� �����������
	bit0.push_back(0);
	bit1.push_back(1);

	map<char, vector<bool>> Map; //��� �������� ���������
	map < char, vector < bool >> ::iterator Map_iterator;

	string str0, str1;

	char input_symbol;
	bool temp = false;

	int quantity_symbols_in_input_file = 0;
	//���������� ����������� ��������, ������� ������������
	for (int i = 1; ;i *= 10)
	{
		char temp;
		file_input.get(temp);
		if (temp == '\x01')
			break;
		quantity_symbols_in_input_file += (temp - 0x30) * i;
	}

	//���������� ������
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
	 
	file_input.get(input_symbol);//��������� ������
	while (!file_input.eof()) //���� ����������� �� ��������� �����
	{ 
		//���� ��� ������� �������
		for (counter_symbols; counter_symbols >= 0; counter_symbols--) //�������� ������ ����� 
		{//�� ��� �� ����� �������...
			code_of_symbol.push_back(get_bit(input_symbol, counter_symbols));//��������� ����� ��� � ������ �����
			for (Map_iterator = Map.begin(); Map_iterator != Map.end(); ++Map_iterator)//���� ����������� ������ �����
			{
				if (Map_iterator->second == code_of_symbol)//���� �����, �� ���������� ��� ���� � ����
				{
					file_output << Map_iterator->first;
					code_of_symbol.clear();
					quantity_symbols_in_input_file--;
					break;
				}
				//���� �� ����� � ���� ������� �� ����
			}
			//� ������ �����
			if (quantity_symbols_in_input_file == 0)
				break;
		}
		//���� �� ����� � ���� �����, ��������� ������ � ������
		counter_symbols = 7;
		file_input.get(input_symbol);//��������� ������
	}

	std::cout << "task is successful";
	file_output.close();
	file_input.close();
	return 0;
}
