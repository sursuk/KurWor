

#include<iostream>
#include<string>

using namespace std;

class Console
{
private:
	string path_now = "D:\\�����\\3 �������\\�������� ������";
public:
	string output_path();
	int input_command();

	void zipA(); //���� �� �������� � ��������
	void zipB(); //���� �� �������� � ������
	void zipC(); //���� �� ������ � ��������
	void zipD(); //���� �� ������ � ������

	void unzipA(); //���� �� �������� � ��������
	void unzipB(); //���� �� �������� � ������
	void unzipC(); //���� �� ������ � ��������
	void unzipD(); //���� �� ������ � ������

	void cd(); //����� ��������
	void help();
	void exit();
};

