
#include<iostream>
#include<string>

#include"console.h"
#include"algoritpht_fano.h"

using namespace std;




string Console::output_path()
{	
	return path_now + ">";
}

int Console::input_command()
{
	string help = "help";

	string zipA = "zipA";
	string zipB = "zipB";
	string zipC = "zipC";
	string zipD = "zipD";

	string unzipA = "unzipA";
	string unzipB = "unzipB";
	string unzipC = "unzipC";
	string unzipD = "unzipD";
	
	string cd = "cd";
	string exit = "exit";

	string command;
	cin >> command;

	if (command == help)
		return 1;
	else if (command == zipA)
		return 2;
	else if (command == zipB)
		return 3;
	else if (command == zipC)
		return 4;
	else if (command == zipD)
		return 5;
	else if (command == unzipA)
		return 6;
	else if (command == unzipB)
		return 7;
	else if (command == unzipC)
		return 8;
	else if (command == unzipD)
		return 9;
	else if (command == cd)
		return 10;
	else if (command == exit)
		return 11;
	else
		cout << "\"" << command << "\" �� �������� ��������" << endl;
}
//���� �� �������� � ��������
void Console::zipA()
{
	algoritpht_fano something;
	string name_of_file;
	do {
		cout << "input name of file: ";
		cin >> name_of_file;
		if (name_of_file == "exit")
			return;
	}while(something.zip(path_now + name_of_file, path_now + name_of_file));
}
//���� �� �������� � ������
void Console::zipB()
{
	algoritpht_fano something;
	string path_to_file, name_of_file;
	do {
		cout << "input name of file: ";
		cin >> name_of_file;
		cout << "input path to file: ";
		cin >> path_to_file;
		if (name_of_file == "exit" || path_to_file == "exit")
			return;
	} while (something.zip(path_now + name_of_file, path_to_file + name_of_file));
}
//���� �� ������ � ��������
void Console::zipC()
{
	algoritpht_fano something;
	string path_to_file;
	do {
		cout << "input path to file: ";
		cin >> path_to_file;
		if (path_to_file == "exit")
			return;
	} while (something.zip(path_to_file, path_now + path_to_file.substr(path_to_file.find_last_of("\\"))));
}
//���� �� ������ � ������
void Console::zipD()
{
	algoritpht_fano something;
	string path_to_input_file, path_to_output_file;
	do {
		cout << "input path to input_file: ";
		cin >> path_to_input_file;

		cout << "input path to output_file: ";
		cin >> path_to_output_file;

		if (path_to_input_file == "exit" || path_to_output_file == "exit")
			return;
	} while (something.zip(path_to_input_file, path_to_output_file));
}



//���� �� �������� � ��������
void Console::unzipA()
{
	algoritpht_fano something;
	string name_of_file;
	do {
		cout << "input name of file: ";
		cin >> name_of_file;
		if (name_of_file == "exit")
			return;
	} while (something.unzip(path_now + name_of_file, path_now + name_of_file));
}
//���� �� �������� � ������
void Console::unzipB()
{
	algoritpht_fano something;
	string path_to_file, name_of_file;
	do {
		cout << "input name of file: ";
		cin >> name_of_file;
		cout << "input path to file: ";
		cin >> path_to_file;
		//������ ���� �������� �����
	} while (something.unzip(path_now + name_of_file, path_to_file + name_of_file));
}
//���� �� ������ � ��������
void Console::unzipC()
{
	algoritpht_fano something;
	string path_to_file;
	do {
		cout << "input path to file: ";
		cin >> path_to_file;
		if (path_to_file == "exit")
			return;
	} while (something.unzip(path_to_file, path_now + path_to_file.substr(path_to_file.find_last_of("\\"))));
}
//���� �� ������ � ������
void Console::unzipD()
{
	algoritpht_fano something;
	string path_to_input_file, path_to_output_file;
	do {
		cout << "input path to input_file: ";
		cin >> path_to_input_file;

		cout << "input path to output_file: ";
		cin >> path_to_output_file;

		if (path_to_input_file == "exit" || path_to_output_file == "exit")
			return;
	} while (something.unzip(path_to_input_file, path_to_output_file));
}

void Console::help()
{
	cout << "ZIP - ������������� �����" << endl
		<< "	-zipA - �� ������� ����� � ������� �����" << endl
		<< "	-zipB - �� ������� ����� � ������ �����" << endl
		<< "	-zipC - �� ������ ����� � ������� �����" << endl
		<< "	-zipD - �� ������ ����� � ������ �����" << endl

		<< "UNZIP - ���������������� �����" << endl
		<< "	-unzipA - �� ������� ����� � ������� �����" << endl
		<< "	-unzipB - �� ������� ����� � ������ �����" << endl
		<< "	-unzipC - �� ������ ����� � ������� �����" << endl
		<< "	-unzipD - �� ������ ����� � ������ �����" << endl

		<< "cd - ����� ������� �����" << endl
		<< "help - ������� �� ��������" << endl
		<< "exit - �������� ���������" << endl;
}

void Console::cd()
{
	string new_path;
	cout << "���� �� ������ ��������� � �������� ������� �������� ������� - home " << endl
		<< "������� ����� ����: "; cin >> new_path;
	if (new_path == "home")
		path_now = "D:\\�����\\3 �������\\�������� ������";
	else
		path_now = new_path;
}

