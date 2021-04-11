

#include<string>
#include<map>
#include<vector>
#include<fstream>



using namespace std;

class algoritpht_fano {
private:
	ofstream file_output;
	ifstream file_input;

	multimap<int, char> quantity; //��� ������������� ���������� ��������
	multimap<int, char> :: iterator quantity_iterator;

	void input_text(string path); //�������, ������ �� ����, ����� ��
	void output_text(string path); 

	void strange_wood(string str, vector<bool> bit, map<char, vector<bool>> &Map); //������� ���������� �� ������������� ������, ������� ����� �� ��������

	void find_and_input(char symbol); //���� ������ ���������� � �����

public:
	int zip(string path_out, string path_in);
	int unzip(string path_out, string path_in);
};
