

#include<iostream>
#include<string>

using namespace std;

class Console
{
private:
	string path_now = "D:\\учеба\\3 семестр\\Курсовой проект";
public:
	string output_path();
	int input_command();

	void zipA(); //путь из нынешней в нынешную
	void zipB(); //путь из нынешний в другую
	void zipC(); //путь из другой в нынешную
	void zipD(); //путь из другой в другую

	void unzipA(); //путь из нынешней в нынешную
	void unzipB(); //путь из нынешний в другую
	void unzipC(); //путь из другой в нынешную
	void unzipD(); //путь из другой в другую

	void cd(); //смена каталога
	void help();
	void exit();
};

