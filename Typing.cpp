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


int main() {
	int flag = 1;
	while (flag == 1){
		int n, amount;
		string str;
		do {
			system("cls");
			presentation();
			cout << "\n\n Choose amount of words \n";
			cout << " 1. 20 \n 2. 40 \n 3. 60 \n 4. 80 \n 5. 100\n Option: ";
			cin  >> str;
		} while(!isInteger(&n, str) || n < 1 || n > 5);
		
		switch(n) {
			case 1: amount = 20; break;
			case 2: amount = 40; break;
			case 3: amount = 60; break;
			case 4: amount = 80; break;	
			case 5: amount = 100; break;
		}

		game(amount);
		
		system("cls");
		do {
			cout << "\n\n Play again? [1: Yes, 2: No]: ";
			cin >> str;
		} while(!isInteger(&flag, str) || (n != 1 && n!= 2) );
	}

	return 0;
}

int presentation() {
	cout << "\n\n\t\t English Typing Speed \n";
	cout << "\t Are you fast and accurate enough? \n";
}

int game(int n) {
	srand( (unsigned)time(NULL) );
	system("cls");
	string words[MAX];	
	int correct = 0, chars = 0;
	double time = 0, avgTime = 0;
	
	cout <<" \n\n Amount of words: " <<n;
	cout <<" \n\n Press any key to START! ";
	getch();
	fflush(stdin);
	
	system("cls");
	readWords(words);
	for(int i = 0; i < n; i++) {
		int r = rand() % 100;

		cout <<" \n\n Word " <<i+1 <<": " <<words[r];
		
		auto start = std::chrono::system_clock::now();
		
		cout << "\n\n Type here: ";
		string answer;
		getline(cin, answer);
		
		auto end = std::chrono::system_clock::now();
		
		//if word is corrrect, count word and characters
		if(! answer.compare(words[r]) ){
			correct++;
			int sizeAnswer = answer.length();
			for(int j = 0; j < sizeAnswer; j++) {
				std::string letterR(1, answer[j]); // cast to string
				std::string letterUser(1, words[r][j]);
			
				chars = chars + (letterR == letterUser);
			}
		}
		
		std::chrono::duration<double> elapsed_seconds = end-start;
		
		avgTime = avgTime + elapsed_seconds.count();
		system("cls");
	}
	cout << "\n\n\t YOUR SCORE: ";
	cout << "\n\n Time =  " <<avgTime;
	cout << "\n Rigth words = " <<correct;
	cout << "\n Rigth chars = " <<chars;
	cout << "\n wpm = " <<correct*60/avgTime;
	cout << "\n cpm = " <<chars*60/avgTime;
	cout << "\n accuracy = " <<correct*100/n <<" %";
	cout << "\n\n\t YOUR CLASSIFICATION: \n\n";
	classification(correct*60/avgTime, chars*60/avgTime);
	cout << "\n\n Press any key to continue: ";
	getch();
}

void readWords(string words[MAX]) {
    int i;
    fstream file;
    file.open("Words.txt",ios::in); 
    while(getline(file, words[i])){ 
       	i++;
    }
    file.close(); 
}

bool isInteger(int *n, string str) {
	try {
		*n = std::stoi(str);
		return true;
	} catch (...) {
		return false;
	}
}

void classification(double wpm, double cpm) {
	if((cpm < 120) || wpm < 24) {
		cout << " Slow typing speed. A person with a little experience using the keyboard.";
	} else if((cpm >= 120 || cpm < 160) || (wpm >= 24 || wpm < 32)) {
		cout<<" Medium typing speed for a person that types with 2-4 fingers, looking at the keyboard.";
	} else if((cpm >= 160 || cpm < 260) || (wpm >= 32 || wpm < 52)) {
		cout<<" Medium typing speed for a person that types with 10 fingers, without looking at the keyboard.";
	} else if((cpm >= 260 || cpm < 350) || (wpm >= 52 || wpm < 70)) {
		cout<<" Good typing speed for a person who has complete a blind typing course.";
	} else if((cpm >= 350 || cpm < 400) || (wpm >= 70 || wpm < 80)) {
		cout<<" High typing speed. A person who has a professional knowledge about typing.  ";
	} else {
		cout<<" Very High typing speed. Near to the speaking speed.";
	}
}
