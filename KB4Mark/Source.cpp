#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


vector<char> specialNums = { '1', '2', '3', '4', '5', '6', '7' };

map<int, pair<string, string>> mapping = {
	{0, {"1", ""}},
	{1, {"2", ""}},
	{2, {"3", ""}},
	{3, {"4", ""}},
	{4, {"5", ""}},
	{5, {"6", ""}},
	{6, {"7", ""}},

	{7, {"8", "1"}},
	{8, {"8", "2"}},
	{9, {"8", "3"}},
	{10, {"8", "4"}},
	{11, {"8", "5"}},
	{12, {"8", "6"}},
	{13, {"8", "7"}},
	{14, {"8", "8"}},
	{15, {"8", "9"}},
	{16, {"8", "0"}},

	{17, {"9", "1"}},
	{18, {"9", "2"}},
	{19, {"9", "3"}},
	{20, {"9", "4"}},
	{21, {"9", "5"}},
	{22, {"9", "6"}},
	{23, {"9", "7"}},
	{24, {"9", "8"}},
	{25, {"9", "9"}},
	{26, {"9", "0"}},

	{27, {"0", "1"}},
	{28, {"0", "2"}},
	{29, {"0", "3"}},
	{30, {"0", "4"}},
	{31, {"0", "5"}},
	{32, {"0", "6"}},
	{33, {"0", "7"}},
};

string encode(string line, string markLetters) {
	string res = "";
	for (int i = 0; i < line.length(); i++) {
		if (line[i] != ' ') {
			res += mapping[markLetters.find(line[i])].first + mapping[markLetters.find(line[i])].second;
		}
		else {
			res += line[i];
		}
	}
	return res;
}

string decode(string line, string markLetters) {
	string res = "";
	string currEncode = "";
	vector<int> keys;
	for (auto const& imap : mapping)
		keys.push_back(imap.first);
	for (int i = 0; i < line.length(); i++) {
		if (currEncode._Equal("")) {
			if (count(specialNums.begin(), specialNums.end(), line[i])) {
				res += markLetters[int(line[i]) - 1];
			}
			else if (isdigit(line[i])) {
				currEncode += line[i];
			}
			else {
				res += line[i];
			}
		}
		else {
			currEncode += line[i];
			for (int j = 0; j < keys.size(); j++) {
				if ((mapping[keys[j]].first + mapping[keys[j]].second)._Equal(currEncode)) {
					res += specialNums[j];
				}
			}
			currEncode = "";
		}
	}
	return res;
}

int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "RUS");
	ifstream mark;
	mark.open("mark.txt");
	string markLetters = "";
	getline(mark, markLetters);
	cout << markLetters << "\n";
	string urlIn, urlOut;
	cout << "Url to input file\n";
	cin >> urlIn;
	cout << "Url to output file\n";
	cin >> urlOut;
	ifstream input;
	input.open(urlIn);
	vector<string> inS = {};
	while (!input.eof()) {
		string temp;
		getline(input, temp);
		cout << temp;
		inS.push_back(temp);
	}
	input.close();
	ofstream output;
	output.open(urlOut);
	string res = "";
	vector<string> enc = {};
	for (int i = 0; i < inS.size(); i++)
	{
		string temp = encode(inS[i], markLetters);
		enc.push_back(temp);
		res += temp;
	}
	output << res << "\n";
	cout << res << "\n";
	res = "";
	for (int i = 0; i < enc.size(); i++)
	{
		string temp = decode(inS[i], markLetters);
		res += temp;
	}
	output << res << "\n";
	cout << res << "\n";
	output.close();
	return 0;
}