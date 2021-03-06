#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

class Engine {
	private:
		string word;
		int mistakes;
		vector<char> usedRightLetters;
		vector<char> usedWrongLetters;
		vector<char> wordLetters;
		bool hidden;
		bool wrong;
	public:
		Engine(string w, int mist,vector<char> usedRight, vector<char> usedWrong, vector<char> wordLet) {
			word = w;
			mistakes = mist;
			usedRightLetters = usedRight;
			usedWrongLetters = usedWrong;
			wordLetters = wordLet;
		}
		void GetAllLettersFromTheWord() {
			for (int i = 0; i < word.size(); i++)
			{
				if (find(wordLetters.begin(), wordLetters.end(), word[i]) != wordLetters.end()) {

				}
				else {
					wordLetters.push_back(word[i]);
				}
			}
		}
		void GetTheFirstAndLastLetter() {
			usedRightLetters.push_back(word[0]);
			usedRightLetters.push_back(word[word.size() - 1]);
		}
		void SetHiddenToTrue() {
			hidden = true;
		}
		void LoopThroughTheWordAndCheckIfLettersIsFound() {
			for (int i = 0; i < word.size(); i++)
			{
				hidden = true;
				for (int j = 0; j < usedRightLetters.size(); j++)
				{
					if (word[i] == usedRightLetters[j]) {
						hidden = false;
					}
				}
				if (hidden == false) {
					cout << word[i];
				}
				else {
					cout << " _ ";
				}
			}
		}
		void SetWrongToTrue() {
			wrong = true;
		}
		void CheckIfWordContainsUserChar(char ch) {
			for (int i = 0; i < wordLetters.size(); i++)
			{
				if (ch == wordLetters[i]) {
					usedRightLetters.push_back(ch);
					wrong = false;
				}
			}
			if (wrong == true) {
				if (find(usedWrongLetters.begin(), usedWrongLetters.end(), ch) != usedWrongLetters.end()) {
				}
				else {
					usedWrongLetters.push_back(ch);
					mistakes += 1;
				}
			}
		}
		void PrintsWrongLetters() {
			cout << endl << "===================" << endl;
			cout << "Wrong letters: ";
			for (int i = 0; i < usedWrongLetters.size(); i++)
			{
				cout << " " << usedWrongLetters[i];
			}
			cout << endl << "===================" << endl;
		}
		void Draw() {
			switch (mistakes)
			{
			case 1:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |         " << endl;
				cout << "_|______________" << endl;
				break;
			case 2:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \  0 " << endl;
				cout << "_|______________" << endl;
				break;
			case 3:       cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \\ 0 " << endl;
				cout << "_|______________" << endl;
				break;
			case 4:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \\ 0 /" << endl;
				cout << "_|______________" << endl;
				break;
			case 5:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \\ 0 /" << endl;
				cout << " |         |" << endl;
				cout << "_|______________" << endl;
				break;
			case 6:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \\ 0 /" << endl;
				cout << " |         |" << endl;
				cout << " |        /  " << endl;
				cout << "_|______________" << endl;
				break;
			case 7:
				cout << " ___________" << endl;
				cout << " |         }" << endl;
				cout << " |       \\ 0 /" << endl;
				cout << " |         |" << endl;
				cout << " |        / \\ " << endl;
				cout << "_|______________" << endl;
			}
		}
		void SortVectors(){
			sort(wordLetters.begin(), wordLetters.end());
			sort(usedRightLetters.begin(), usedRightLetters.end());
			sort(usedWrongLetters.begin(), usedWrongLetters.end());
		}
		bool CheckForEndOfGame() {
			bool gameOver = false;
			if (wordLetters == usedRightLetters || mistakes == 7) {
				gameOver = true;
				if (mistakes == 7) {
					cout << endl << "UNFORTUNATELY YOU LOST";
					cout << endl << "THE WORD WAS: " << word;
				}
				else {
					cout << endl << "CONGRATULATIONS YOU WON";
				}
			}
			return gameOver;
		}
};

int main()
{
	string line, word;
	vector<char> usedRightLetters;
	vector<char> usedWrongLetters;
	vector<char> wordLetters;

	char ch;
	bool gameover = false;
	bool wrong = true;
	int mistakes = 1;
	bool hidden = true;

	ifstream myfile("words.txt");
	srand(time(0));
	int random = rand() % 50;
	int numOfLines = 0;

	// Get a word
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			++numOfLines;

			if (numOfLines == random)
			{
				word = line;
			}
		}
		myfile.close();
	}
	else {
		cout << "Not opened";
	}
	//Used for testing
	cout << word << endl;

	Engine engine = Engine(word, mistakes, usedRightLetters, usedWrongLetters, wordLetters);

	engine.GetAllLettersFromTheWord();
	
	engine.GetTheFirstAndLastLetter();
	
	// Game

	while (gameover == false)
	{
		engine.SetWrongToTrue();
		engine.SetHiddenToTrue();
		engine.LoopThroughTheWordAndCheckIfLettersIsFound();

		// Gets user`s letter
		cout << endl;
		cin  >>  ch;
	
		engine.CheckIfWordContainsUserChar(ch);
	
		engine.PrintsWrongLetters();

		engine.Draw();

		engine.SortVectors();
		
		gameover = engine.CheckForEndOfGame();
	}
	
	return 0;
}
