#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 101

using namespace std;

int presentation();
int game(int n);
void classification(double wpm, double cpm);

bool isInteger(int *n, string str);
void readWords(string words[MAX]);

int main()
{
	int flag;
	do
	{
		int amount;
		string str;
		do
		{
			system("cls");
			presentation();
			cout << "\n\n Menu: \n";
			cout << " 1. Start Game  \n 2. Exit \n Option: ";
			cin >> str;
		} while (!isInteger(&flag, str) || flag < 1 || flag > 2);
		if (flag != 2)
		{
			//Chooses amount
			do
			{
				system("cls");
				presentation();
				cout << "\n\n Choose amount of words [10 - 100]: ";
				cin >> str;
			} while (!isInteger(&amount, str) || amount < 10 || amount > 100);
			//Start the game
			game(amount);
		}

	} while (flag != 2);
	system("cls");
	cout << "\n\n\n\n\t\t THANKS FOR PLAYING! \n\n\n\n\n";
	return 0;
}

int presentation()
{
	cout << "\n\n\t\t Typing Speed Test\n";
	cout << "\t Are you fast and accurate enough? \n";
}

int game(int n)
{
	srand((unsigned)time(NULL));
	system("cls");
	string words[MAX];
	int correct = 0, chars = 0, index[n];
	double time = 0, avgTime = 0;

	cout << " \n\n Amount of words: " << n;
	cout << " \n\n Press any key to START! ";
	getch();
	fflush(stdin);

	//Selects random indexs for tha words
	for (int i = 0; i < n; i++)
	{
		int r = rand() % 100;
		index[i] = r;
	}

	system("cls");
	readWords(words);
	for (int i = 0; i < n; i++)
	{
		//Shows the random words
		cout << " \n\n Words left " << n - i << "\n\n";
		for (int j = i; j < n; j++)
		{
			cout << " " << words[index[j]];
		}

		//Starts measuring time
		auto start = std::chrono::system_clock::now();

		cout << "\n\n Type here: ";
		string answer;
		getline(cin, answer);

		auto end = std::chrono::system_clock::now();

		//if word is corrrect, count words and characters
		if (!answer.compare(words[index[i]]))
		{
			correct++;
			int sizeAnswer = answer.length();
			chars += sizeAnswer;
		}

		std::chrono::duration<double> elapsed_seconds = end - start;

		avgTime += elapsed_seconds.count();
		system("cls");
	}

	//Here we tell you yout score
	cout << "\n\n\t " << n << " WORDS TEST ";
	cout << "\n\n\t YOUR SCORE: ";
	cout << "\n\n Time =  " << avgTime;
	cout << "\n Rigth words = " << correct;
	cout << "\n Rigth chars = " << chars;
	cout << "\n wpm = " << correct * 60 / avgTime;
	cout << "\n cpm = " << chars * 60 / avgTime;
	cout << "\n accuracy = " << correct * 100 / n << " %";
	cout << "\n\n\t YOUR CLASSIFICATION: \n\n";
	classification(correct * 60 / avgTime, chars * 60 / avgTime);
	cout << "\n\n Press any key to continue: ";
	getch();
	fflush(stdin);
	system("cls");
}

void readWords(string words[MAX])
{
	int i;
	fstream file;
	file.open("Words.txt", ios::in);
	while (getline(file, words[i]))
	{
		i++;
	}
	file.close();
}

bool isInteger(int *n, string str)
{
	try
	{
		*n = std::stoi(str);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void classification(double wpm, double cpm)
{
	if ((cpm < 120) || wpm < 24)
	{
		cout << " Slow typing speed. A person with a little experience using the keyboard.";
	}
	else if ((cpm >= 120 || cpm < 160) || (wpm >= 24 || wpm < 32))
	{
		cout << " Medium typing speed for a person that types with 2-4 fingers, looking at the keyboard.";
	}
	else if ((cpm >= 160 || cpm < 260) || (wpm >= 32 || wpm < 52))
	{
		cout << " Medium typing speed for a person that types with 10 fingers, without looking at the keyboard.";
	}
	else if ((cpm >= 260 || cpm < 350) || (wpm >= 52 || wpm < 70))
	{
		cout << " Good typing speed for a person who has complete a blind typing course more than once.";
	}
	else if ((cpm >= 350 || cpm < 400) || (wpm >= 70 || wpm < 80))
	{
		cout << " Professional typing speed. A person who has a professional knowledge about typing.  ";
	}
	else
	{
		cout << " Very High typing speed. Near to the speaking speed.";
	}
}
