/* Name: Luna Y.
 * Date: February 20, 2020
 * Desc: Tells and rates knock knock jokes. */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <windows.h>

using namespace std;

int main()
{
	srand(time(NULL));

	// Get console handle & set up colours.
	// Colours may look different on some computers.
	HANDLE consHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	const int COMP_COLOUR = 15, USER_COLOUR = 3;
	SetConsoleTextAttribute(consHandle, COMP_COLOUR);

	const string STARTPATH = "Resources/jokes_start.txt", FINISHPATH = "Resources/jokes_end.txt";

	int userChoice = 1;
	string textBuffer = "";
	cout << "Would you like to Hear (1) a joke, or Add (2) one to my memory?" << endl;
	cout << "Enter your choice: ";
	//SetConsoleTextAttribute(consHandle, USER_COLOUR);
	getline(cin, textBuffer);
	if (textBuffer != "1") // Don't let the user break the program by not entering a number.
	{
		textBuffer = "2";
	}
	userChoice = stoi(textBuffer);
	//SetConsoleTextAttribute(consHandle, COMP_COLOUR);

	//string userResponse = "";

	// Read in from text files
	ifstream bankFirst(STARTPATH);
	ifstream bankLast(FINISHPATH);
	map<string, int> jokeStarts; // Key is the joke start, value is how "funny" it is.
	map<string, int> jokeEnds;
	while (!bankFirst.eof()) // Read in joke beginnings to a map.
	{
		getline(bankFirst, textBuffer);
		if (textBuffer == "")
		{
			continue;
		}
		int scIndex = textBuffer.find(";"); // Location of the semicolon
		string joke = textBuffer.substr(0, scIndex);
		textBuffer = textBuffer.substr(scIndex + 1);
		int funnyness = stoi(textBuffer);
		jokeStarts[joke] = funnyness;
	}
	while (!bankLast.eof()) // Do the same for punchlines.
	{
		getline(bankLast, textBuffer);
		if (textBuffer == "")
		{
			continue;
		}
		int scIndex = textBuffer.find(";"); // Location of the semicolon
		string joke = textBuffer.substr(0, scIndex);
		textBuffer = textBuffer.substr(scIndex + 1);
		int funnyness = stoi(textBuffer);
		jokeEnds[joke] = funnyness;
	}

	// User wants to hear a joke.
	if (userChoice == 1)
	{
		// Turn the maps into vectors so that it's easier to pick one at random. Funnyness values are the weight of each joke part.
		vector<string> jokeStartsVect, jokeEndsVect;
		for (map<string, int>::iterator i = jokeStarts.begin(); i != jokeStarts.end(); i++)
		{
			for (int j = 0; j < i->second; j++)
			{
				jokeStartsVect.push_back(i->first);
			}
		}
		for (map<string, int>::iterator i = jokeEnds.begin(); i != jokeEnds.end(); i++)
		{
			for (int j = 0; j < i->second; j++)
			{
				jokeEndsVect.push_back(i->first);
			}
		}

		// Finally, pick a joke.
		string starter = "", punchline = "";
		int startRoll = rand() % jokeStartsVect.size();
		int endRoll = rand() % jokeEndsVect.size();
		starter = jokeStartsVect[startRoll];
		punchline = jokeEndsVect[endRoll];

		// Tell the joke and ask whether it was funny. The idea is that the jokes the user likes will be told more
		// And since parts of different jokes can be combined, the computer will create a new joke that is theoretically funny.
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << "Let's hear a joke." << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << "Knock knock." << endl
			 << "Enter your response: ";
		// Note: This merely presents the user with the illusion of choice. They will respond, "Who's there?" regardless of what they actually want.
		getline(cin, textBuffer);
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << "Who's there?" << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << starter << "." << endl
			 << "Enter your response: ";
		getline(cin, textBuffer);
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << starter << " who?" << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << starter << " " << punchline << endl
			 << "...was that funny?" << endl
			 << "Enter your response: ";
		getline(cin, textBuffer);

		// Is the joke funny?
		const vector<string> WORDS_MEANING_YES = {"yes", "y", "sure", "i guess", "definitely"};
		for (int i = 0; i < textBuffer.length(); i++)
		{
			textBuffer[i] = tolower(textBuffer[i]);
		}
		if (find(WORDS_MEANING_YES.begin(), WORDS_MEANING_YES.end(), textBuffer) != WORDS_MEANING_YES.end())
		{
			jokeStarts[starter]++;
			jokeEnds[punchline]++;
			cout << "Awesome! Thanks for your feedback." << endl;
		}
		else
		{
			cout << "I see...very well then, I'll work on something better." << endl;
		}

		// Clean up and overwrite text files.
		bankFirst.close(); // I don't know what happens if you try to open an ofstream on a file that's already open, and I don't want to find out here.
		bankLast.close();
		ofstream startersFile(STARTPATH);
		ofstream punchlinesFile(FINISHPATH);
		for (map<string, int>::iterator i = jokeStarts.begin(); i != jokeStarts.end(); i++)
		{
			startersFile << i->first << ";" << i->second << endl;
		}
		for (map<string, int>::iterator i = jokeEnds.begin(); i != jokeEnds.end(); i++)
		{
			punchlinesFile << i->first << ";" << i->second << endl;
		}
		startersFile.close();
		punchlinesFile.close();
	}
	// User wants to enter a joke.
	else
	{
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << "I'll tell you a joke." << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << "Start the joke: "; // Once again, the user is railroaded into following the structure of a knock knock joke.
		getline(cin, textBuffer);
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << "Knock knock." << endl;

		// Start of the Joke
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << "Who's there?" << endl;
		cout << "Enter your response: ";
		getline(cin, textBuffer);
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		string starter = textBuffer;
		cout << starter << "." << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);
		cout << starter << " who?" << endl;

		// Joke punchline.
		cout << "Enter your response (Do not include the joke starter): ";
		getline(cin, textBuffer);
		string punchline = textBuffer;
		SetConsoleTextAttribute(consHandle, USER_COLOUR);
		cout << starter << " " << punchline << endl;
		SetConsoleTextAttribute(consHandle, COMP_COLOUR);

		// Add joke to the library if it's not already there
		bool writeStart = false, writeEnd = false;
		if (jokeStarts.count(starter) < 1) // Starter doesn't exist
		{
			writeStart = true;
			if (jokeEnds.count(punchline) < 1) // Punchline doesn't exist
			{
				writeEnd = true;
				cout << "That was a pretty original joke." << endl;
			}
			else // Punchline exists, but not starter.
			{
				cout << "Hmm, never seen the punchline used like that before." << endl;
			}
		}
		else if (jokeEnds.count(punchline) < 1) // Starter exists, but not punchline
		{
			writeEnd = true;
			cout << "You had me in the first half, not gonna lie." << endl;
		}
		else // Both already exist
		{
			cout << "Yeah, I've actually heard that joke before." << endl;
		}

		// Write starter and/or punchline to the joke library.
		if (writeStart)
		{
			bankFirst.close();
			ofstream startersFile(STARTPATH);
			jokeStarts[starter] = 1;
			for (map<string, int>::iterator i = jokeStarts.begin(); i != jokeStarts.end(); i++)
			{
				startersFile << i->first << ";" << i->second << endl;
			}
			startersFile.close();
		}
		if (writeEnd)
		{
			bankLast.close();
			ofstream punchlinesFile(FINISHPATH);
			jokeEnds[punchline] = 1;
			for (map<string, int>::iterator i = jokeEnds.begin(); i != jokeEnds.end(); i++)
			{
				punchlinesFile << i->first << ";" << i->second << endl;
			}
			punchlinesFile.close();
		}
		if (writeStart || writeEnd)
		{
			cout << "I'll remember that joke for later." << endl;
		}
		else
		{
			cout << "You should really work on your material." << endl;
		}
	}

	cout << "Press ENTER to exit...";
	getline(cin, textBuffer);
	return 0;
}
