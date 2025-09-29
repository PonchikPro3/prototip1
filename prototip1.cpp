
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

ifstream inf;
bool stop = true;
string parser(const char* name);
void inputManager();
void ls(vector<string> arguments);
void cd(vector<string> arguments);

void ls(vector<string> arguments) {
	cout << "comand ls  " << "  arguments( ";
	for (auto it : arguments) {
		cout << it << " ";
	}
	cout << ")\n";
}

void cd(vector<string> arguments) {
	cout << "comand cd  " << "  arguments( ";
	for (auto it : arguments) {
		cout << it << " ";
	}
	cout << ")\n";
}

string parser(const char* name) {
	string value;
#pragma warning(suppress : 4996)
	auto ptr = getenv(name);
	if (ptr)
		value = std::string(ptr);
	else
		value = "No such file";
	return value;
}


void inputManager() {

	vector<string> inputs;
	string input;
	getline(inf, input);
	stringstream ss(input);
	string word;

	if (!inf) {
		stop = false;
	}

	while (ss >> word) {
		inputs.push_back(word);
	}

	cout << input << "\n";


	for (int i = 0; i < inputs.size(); i++) {
		if (inputs[i][0] == '$') {//команда взаимодействия с системным окружением 
			string e, a;

			e = inputs[i].substr(1);
			inputs[i] = parser(e.c_str());
		}
	}

	for (int i = 0; i < inputs.size(); i++) {
		if (inputs[i] == "exit") {//команда выхода
			stop = false;
		}
		else if (inputs[0] == "ls") {//команда ls
			for (int i = 1; i < inputs.size(); i++) {
				inputs[i - 1] = inputs[i];
			}
			inputs.pop_back();
			ls(inputs);
			break;
		}
		else if (inputs[0] == "cd") {//команда cd
			for (int i = 1; i < inputs.size(); i++) {
				inputs[i - 1] = inputs[i];
			}
			inputs.pop_back();
			cd(inputs);
			break;
		}
		else {
			cout << "No such comand\n";
			break;
		}
	}
	

}


int main()
{
	setlocale(LC_ALL, "Russian");
	string name;
	name = "VFS.csv";
	ifstream ins;
	ins.open(name);
	inf.open("inputs.txt", ios::in);
	if (!ins) {
		cout << "VFS not found";
		return 1;
	}
	while (stop) {
		cout << name << ">> ";
		inputManager();
	}
	inf.close();
}
