
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

ifstream inf;
ifstream ins;
bool stop = true;
bool script = false;
vector<string> paths;
string parser(const char* name);
void inputManager();
void CommandSTR(int commands, char* command[]);
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
	

	if (script) {
		getline(inf, input);
		if (!inf) {
			stop = false;
		}

	}
	else
	{
		getline(cin, input);
	}
	stringstream ss(input);
	string word;
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

void CommandSTR(int commands, char* command[]) {
	for (int i = 0; i < commands; i++) {
		paths.push_back(command[i]);
	}
}


int main(int q_commands, char* with_command[])
{
	setlocale(LC_ALL, "Russian");

	string VFSname = "";
	string name;
	CommandSTR(q_commands, with_command);
	if (q_commands != 1) {
		for (int i = 1; i < q_commands; i++) {
			if (paths[i][0] == 'V' && paths[i][1] == 'F' && paths[i][2] == 'S' && VFSname == "") {
				VFSname = paths[i];
			}
			else if (paths[i][0] == '-') {
				paths[i] = paths[i].substr(1);
				name = paths[i];
			}
			cout << paths[i] << " ";
		}
		cout << endl;
		script = true;

		ins.open(VFSname);

		inf.open(name, ios::in);
	}

	if (!ins) {
		cout << "VFS not found" << endl;
		return 1;
	}
	while (stop) {
		cout << VFSname << ">> ";
		inputManager();
	}
	inf.close();
}
