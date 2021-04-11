
#include<iostream>
#include<string>

#include"Console.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "zipper fano programm\nвведите команду \"help\" для того, чтобы получить справку о командах программы" << endl << endl;

	Console console;
	do {
		cout<<console.output_path();
		switch (console.input_command())
		{
		case 1: console.help(); break;
		case 2: console.zipA(); break;
		case 3: console.zipB(); break;
		case 4: console.zipC(); break;
		case 5: console.zipD(); break;

		case 6: console.unzipA(); break;
		case 7: console.unzipB(); break;
		case 8: console.unzipC(); break;
		case 9: console.unzipD(); break;

		case 10: console.cd(); break;
		case 11: return 0;
		}

		cout << endl;
	} while (1);
}