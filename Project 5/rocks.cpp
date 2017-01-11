#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);
int manageOneTurn(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

int main()
{
    const int MAXWORDS = 9000; // declares max number of words that can be held in the array
    char wordList[MAXWORDS][MAXWORDLEN+1]; // initializes array to hold words
    int nWords = loadWords(wordList, MAXWORDS); // loads array with words and declares variable to store number of words in array
    if (nWords < 1) // terminates the program if the number of words in the array is less than 1
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1;
    }
    int rounds = 0; // declares variable to store number of rounds to play
    int min = INT_MAX; // declares variable to store minimum number of tries, sets it to largest integer possible initially
    int max = INT_MIN; // declares variable to store maximum number of tries, sets it to smallest integer possible initially
    double average = 0; // declares variable to store average number of tries
    int totalScore = 0; // declares variable to store total score of all rounds
    cout << "How many rounds do you want to play? ";
    cin >> rounds; // reads input from user determining how many rounds to play
    if (rounds <= 0) // terminates the program if the number of rounds entered is not positive
    {
        cout << "The number of rounds must be positive." << endl;
        return -1;
    }
    cin.ignore(10000, '\n'); // solves the problem caused by the newline left by cin
    cout << endl;
    for (int i = 1; i <= rounds; i++) // runs the game for as many rounds as the user specifies
    {
        int wordnum = randInt(0, nWords - 1); // generates random integer to choose random word from word array as secret word
        cout << "Round " << i << endl << "The secret word is " << strlen(wordList[wordnum]) << " letters long." << endl;
        int score = manageOneRound(wordList, nWords, wordnum); // initializes variable to store score returned by manageOneRound
        if (score == -1) // if manageOneRound receives incorrect input, the program terminates
            return -1;
        if (score < min) // updates min to store the current minimum number of tries for a round
            min = score;
        if (score > max) // updates max to store the current maximum number of tries for a round
            max = score;
        totalScore += score; // adds score to total score
        average = 1.0 * totalScore/i; // calculates average score
        if (score == 1) // displays message if player guessed the word in one try
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << score << " tries." << endl; // displays message if player guessed the word in multiple tries
        cout.setf(ios::fixed); // formats doubles so average will display correctly with two decimal points
        cout.precision(2);
        cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl << endl; // displays score statistics
    }
}

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) // checks for incorrect input
        return -1;
    bool match = false; // declares variable to store whether player guessed the secret word and initializes it to false
    int score = 0; // declares variable to store the score of one round
    while (!match) // while the player has not guessed the secret word, keep asking for guesses
    {
        switch (manageOneTurn(words, nWords, wordnum)) // the return value of manageOneTurn indicates what action to take
        {
            case 1: // if manageOneTurn finds that the probe word is not made of 4-6 lower case letters, display message
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                break;
            case 2: // if manageOneTurn cannot find the probe word in the array of words, display message
                cout << "I don't know that word." << endl;
                break;
            case 3: // if manageOneTurn finds that the probe word matches the secret word, increment score and exit loop
                score++;
                match = true;
                break;
            case 4: // if manageOneTurn finds that the probe word does not match the secret word, increment score
                score++;
        }
    }
    return score;
}

int manageOneTurn(const char words[][MAXWORDLEN+1], int nWords, int wordnum) // manages a single turn of a round of gameplay
{
    char probe[100]; // declares array of characters to store probe word
    char checkProbe[100]; // declares array of characters to store a copy of probe word
    char secretWord[MAXWORDLEN+1]; // declares array of characters to store a copy of secret word
    bool found = false; // declares variable to store whether probe word is found in array of words, initializes to false
    int rocks = 0; // declares variable to store number of rocks found between probe word and secret word
    int pebbles = 0; // declares variable to store number of pebbles found between porbe word and secret word
    cout << "Probe word: ";
    cin.getline(probe, 100); // takes input of probe word from the user
    strcpy(checkProbe, probe); // stores a copy of the probe word in checkProbe
    strcpy(secretWord, words[wordnum]); // stores a copy of the secret word in secretWord
    if (strlen(probe) < 4 || strlen(probe) > 6) // checks if the probe word is 4-6 characters long
        return 1;
    for (int i = 0; i < strlen(probe); i++) // checks if the probe word is made of lower case letters
    {
        if (!isalpha(probe[i]) || !islower(probe[i]))
            return 1;
    }
    for (int i = 0; i < nWords; i++) // checks if the probe word can be found in the array of words
    {
        if (strcmp(words[i], probe) == 0)
            found = true;
    }
    if (!found) // if the probe word cannot be found in the array of words
        return 2;
    if (strcmp(words[wordnum], probe) == 0) // if the probe word matches the secret word
        return 3;
    for (int i = 0; secretWord[i] != '\0' && checkProbe[i] != '\0'; i++) // loops through secret word and probe word until one ends
    {
        if (secretWord[i] == checkProbe[i]) // if a letter appears in the same position in both words
        {
            rocks++; // a rock is found so rocks is incremented
            checkProbe[i] = 'Z'; // the character is changed to 'Z' in checkProbe so it will not be counted again
            secretWord[i] = 'A'; // the character is changed to 'A' in secretWord so it will not be counted again
        }
    }
    for (int i = 0; secretWord[i] != '\0'; i++) // loops through every character of secretWord and checkProbe
    {
        for (int j = 0; checkProbe[j] != '\0'; j++)
        {
            if (secretWord[i] == checkProbe[j] && i != j) // if the same letter appears in different positions
            {
                pebbles++; // a pebble is found so pebbles is incremented
                checkProbe[j] = 'Z'; // the character is changed to 'Z' in checkProbe so it will not be counted again
                secretWord[i] = 'A'; // the character is changed to 'A' in secretWord so it will not be counted again
                break;
            }
        }
    }
    cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl; // displays the number of rocks and pebbles for the probe word
    return 4;
}
