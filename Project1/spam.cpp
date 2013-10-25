#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

void test();
void spam();									// I *could* rearrange my code so I don't have to do this,
int scoreString(string subject, string body);	// but I refuse to shove the main program code to the bottom
string getFirstWord(string text);				// of the file. If there is a better way to do this, I would
string getLastWord(string text);				// love to learn of it in class.
string extractWord(string& text);
bool isUppercase(string text);
string makeUppercase(string text);
bool hasMultipleExclamations(string text);
bool isGibberishWord(string text);

int main() {
	test(); // Contains unit tests
	spam();	// Contains main program body
}

void spam() {				// Main program body
	string subject;			// Initialisation
	string body;
	int score;
	string bodyLine;
	string selection;
	int spamMessages = 0;
	int legitMessages = 0;

	while (selection != "n") {			// Input
		body = "";
		cout << "Enter the subject line of the email: ";
		getline(cin, subject);
		cout << "Enter the body of the email.  Press Enter on an empty line to finish." << endl;
		while (true) {
			getline(cin, bodyLine);
			if (bodyLine == "") {
				break;
			}
			body += bodyLine + "\n";
		}

		score = scoreString(subject, body);		//Spam checking code.
		if (score > 100) {
			spamMessages++;
			cout << "This email is classified as spam, because its spam score is " << score << "." << endl;
		} else {
			legitMessages++;
			cout << "This email is classified as legitimate, because its spam score is " << score << "." << endl;
		}

		do {									// Return query.
			cout << "Would you like to classify another email (y or n)? ";
			getline(cin, selection);
			if (selection == "n") {
				break;
			} else if (selection != "y") {
				cout << "Please enter y or n." << endl;
			}
		} while (selection != "y" && selection != "n");
	}

	cout << "Number of spam messages: " << spamMessages << endl;
	cout << "Number of legitimate messages: " << legitMessages << endl;
}

void test() {			// Testing function
	assert(getFirstWord("838hello3023") == "hello");
	assert(getFirstWord("3244234") == "");
	assert(getFirstWord("838 dsddf") == "dsddf");
	assert(getFirstWord("Hi my name is david") == "Hi");
	assert(getFirstWord("Hi") == "Hi");
	assert(getFirstWord("") == "");
	assert(getLastWord("838hello3023") == "hello");
	assert(getLastWord("hello") == "hello");
	assert(getLastWord("3244234") == "");
	assert(getLastWord("") == "");
	assert(getLastWord("838 dsddf") == "dsddf");
	assert(getLastWord("Hi my name is david") == "david");
	string tester = "Hello people.";
	assert(extractWord(tester) == "Hello");
	assert(tester == " people.");
	assert(extractWord(tester) == "people");
	assert(tester == ".");
	assert(extractWord(tester) == "");
	assert(tester == "");
	assert(extractWord(tester) == "");
	tester = "32948098235 324 ";
	assert(extractWord(tester) == "");
	tester = "hi";
	assert(extractWord(tester) == "hi");
	assert(isUppercase("SIJFSDKJ"));
	assert(!isUppercase("HellO"));
	assert(isUppercase(""));
	assert(isUppercase("WRJDSK3J#("));
	assert(makeUppercase("hello") == "HELLO");
	assert(makeUppercase("Earn *big* MONEY at home!!") == "EARN *BIG* MONEY AT HOME!!");
	assert(makeUppercase("") == "");
	assert(hasMultipleExclamations("!!!!!!!!!!!!!"));
	assert(!hasMultipleExclamations(" !! !! hi!! ! !"));
	assert(hasMultipleExclamations("ddd!!!sdfjn"));
	assert(hasMultipleExclamations("Congrats!!!! Good luck"));
	assert(isGibberishWord("AGPQrxab"));
	assert(isGibberishWord("xxxxozzzz"));
	assert(!isGibberishWord("mortgage"));
	assert(!isGibberishWord("discount prescriptions"));
	assert(scoreString("MAKE MONEY FAST XTFWAQQQ", "THIS IS YOUR CHANCE TO MAKE lots of moolah!\nCLICK ON www.lotsofmoolah.com FOR MORE INFORMATION!") == 115);
	assert(scoreString("hi mom", "Hi mom,\nI hope you're doing OK.  My CS class is great, but the instructor is WEIRD!\nI love you!") == 0);
	assert(scoreString("Greetings FROM YOUR GOOD FRIEND", "THIS IS YOUR CHANCE TO MAKE lots of moolah!\nGO TO www.lotsofmoolah.com FOR MORE INFORMATION!") == 40);
	assert(scoreString("Looking for cheap tickets?", "You can find cheap! tickets ONLY on our website.  Save money with this\ngreat OfFeR!!  Don't be a cheapskate.  Click now for this offer!") == 35);
	assert(scoreString("", "") == 0);
}

int scoreString(string subject, string body) {	// Calculates score from subject line and body and returns it.
	int score = 0;
	string currentWord;
	double wordsInSubject = 0;
	double wordsInBody = 0;
	double allcapsInSubject = 0;
	double allcapsInBody = 0;
	cout.setf(ios::fixed);
	cout.precision(2);

	if (isGibberishWord(getLastWord(subject))) { // Spam rule 2
		score += 40;
	}
	
	if (hasMultipleExclamations(subject)) {		// Spam rule 3
		score += 20;
	}
	
	while (true) {								// Spam rule 1; executed third because extractWord() is destructive.
		currentWord = extractWord(subject);
		if (currentWord == "") {
			break;
		}
		wordsInSubject++;
		if (isUppercase(currentWord)) {
			allcapsInSubject++;
		}
	}
	if ((wordsInSubject != 0) && (allcapsInSubject/wordsInSubject > 0.9)) {
		score += 30;
	}

	while (true) {
		currentWord = extractWord(body);
		if (currentWord == "") {
			break;
		}
		wordsInBody++;
		if (isUppercase(currentWord)) {
			allcapsInBody++;
		}
		currentWord = makeUppercase(currentWord);
		if (currentWord == "BUY"||currentWord == "CHEAP"||currentWord == "CLICK"||currentWord == "DIPLOMA"||currentWord == "ENLARGE"||currentWord == "FREE"||currentWord == "LONELY"||currentWord == "MONEY"||currentWord == "NOW"||currentWord == "OFFER"||currentWord == "ONLY"||currentWord == "PILLS"||currentWord == "SEX") {
			score += 5;							// Spam rule 5, with the greatest argument for using arrays that you've ever seen in the if clause.
		}
	}
	if ((wordsInBody != 0) && (allcapsInBody/wordsInBody > 0.5)) { // Spam rule 4.
		score += 40;
	}
	return score;
}

string getFirstWord(string text) {				// This function returns the first word in the string variable text.
	size_t start = 0;
	size_t length = 0;
	while (!isalpha(text[start]) && start < text.length()) {
		start++;
	}
	while (isalpha(text[start+length]) && (start + length) < text.length()) {
		length++;
	}
	return text.substr(start, length);
}

string getLastWord(string text) {			// This function returns the last word in the string variable text.
	size_t end = text.length();				// Fix this.
	size_t length = 0;
	
	bool hasLetters = false;				// Ugly workarounds.
	bool onlyLetters = true;
	for (size_t i = 0; i < text.length(); i++) {
		if (isalpha(text[i])) {
			hasLetters = true;
		} else {
			onlyLetters = false;
		}
	}
	if (!hasLetters) {
		return "";
	}
	if (onlyLetters) {
		return text;
	}

	while (!isalpha(text[end]) && end > 0 ) {
		end--;
	}
	while (isalpha(text[end - length]) && (end - length) > 0) {
		length++;
	}
	return text.substr(end - length + 1, length);
}

string extractWord(string& text) {				// This function returns the first word in the string that text is a reference to.
	bool hasLetters = false;
	string firstWord = "";
	size_t start = 0;
	size_t length = 0;
	while (!isalpha(text[start]) && start < text.length()) {
		start++;
	}
	while (isalpha(text[start+length]) && (start + length) < text.length()) {
		length++;
	}
	firstWord = text.substr(start, length);
	text = text.substr(start + length, text.length() - (start + length));
	return firstWord;
}

bool isUppercase(string text) {					// This function returns true if and only if every letter in the string text is uppercase.
	bool allUpper = true;
	for (size_t i=0; i < text.length(); i++) {
		if (isalpha(text[i]) && !isupper(text[i])) {
			allUpper = false;
			break;
		}
	}
	return allUpper;
}

string makeUppercase(string text) {				// Makes all letters uppercase.
	string output = "";
	for (size_t i=0; i < text.length(); i++) {
		output += toupper(text[i]);
	}
	return output;
}

bool hasMultipleExclamations(string text) {		// This function returns true if the string text contains three consecutive exclamation marks.
	bool hasMultiple = false;
	int count = 0;
	for (size_t i=0; i<text.length(); i++) {
		if (text[i]=='!') {
			count++;
		} else {
			count = 0;
		}
		if (count == 3) {
			hasMultiple = true;
			break;
		}
	}
	return hasMultiple;
}

bool isGibberishWord(string text) {				//  This function returns true if the string text contains more than three consecutive consonants.
	bool hasMultiple = false;
	int count = 0;
	char letter; // This variable isn't strictly needed, but it makes the if clause so much cleaner and I don't think we're supposed to use arrays yet.
	for (size_t i=0; i<text.length(); i++) {
		letter = tolower(text[i]);
		if (!(letter=='a'||letter=='e'||letter=='i'||letter=='o'||letter=='u') && isalpha(letter)) {
			count++;
		} else {
			count = 0;
		}
		if (count == 4) {
			hasMultiple = true;
			break;
		}
	}
	return hasMultiple;
}