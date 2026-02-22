#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "HangmanGame.h"

using namespace std;

vector<string> LoadWords(const string& filename);
string PickRandomWord(const vector<string>& words);
bool AskYesNo(const string& prompt);
bool IsValidWord(const string& w);
void AppendWordToFile(const string& filename, const string& word);
int LoadBestStreak(const string& filename);
void SaveBestStreak(const string& filename, int best);

int main()
{
    // Seed the random number generator at the start so each game session is different. 
    srand((unsigned)time(nullptr));

    const string WORDS_FILE = "words.txt";
    const string STATS_FILE = "stats.txt";

    // Load all words into memory at startup.
    // Simpler and faster than re-reading the file every round.
    vector<string> words = LoadWords(WORDS_FILE);
    if (words.empty())
    {
        cout << "No usable words found in " << WORDS_FILE << ". Add words (one per line) and try again.\n";
        return 0;
    }

    // Store best streak separately so word list and stats stay independent.
    int bestStreak = LoadBestStreak(STATS_FILE);
    int currentStreak = 0;

    cout << "\n\n\n";
    cout << "=====================\n";
    cout << "      HANGMAN\n";
    cout << "=====================\n";
    cout << "Max guesses: 6\n";
    cout << "Best win streak: " << bestStreak << "\n\n";

    HangmanGame game;

    // Went with two loops here, one loop that deals with the session and one that handles an individual round.
    while (true)
    {
        string word = PickRandomWord(words);
        game.Reset(word);

        while (!game.IsWon() && !game.IsLost())
        {
            game.RunOneTurn();
        }

        game.PrintState();

        if (game.IsWon())
        {
            cout << "\nYou won. The word was: " << game.GetWord() << "\n";

            // Only write for the best streak if a new best is achieved. 
            currentStreak++;

            if (currentStreak > bestStreak)
            {
                bestStreak = currentStreak;
                SaveBestStreak(STATS_FILE, bestStreak);
                cout << "New best win streak: " << bestStreak << "\n";
            }

            if (AskYesNo("Add a new word to the word bank? (y/n): "))
            {
                while (true)
                {
                    cout << "Enter a new word (letters only): ";
                    string newWord;
                    getline(cin, newWord);

                    for (char& c : newWord) c = (char)tolower(c);

                    if (!IsValidWord(newWord))
                    {
                        cout << "Invalid word. Letters only, no spaces.\n";
                        continue;
                    }
                    
                    // Add the new word to both the file and the in-memory list so we can use it 
                    // immediately without full program restart. 
                    AppendWordToFile(WORDS_FILE, newWord);

                    words.push_back(newWord);

                    cout << "Word added.\n";
                    break;
                }
            }
        }
        else
        {
            cout << "\nYou lost. The word was: " << game.GetWord() << "\n";
            currentStreak = 0;
        }

        if (!AskYesNo("Play again? (y/n): "))
        {
            cout << "Goodbye.\n";
            break;
        }
    }

    return 0;
}

vector<string> LoadWords(const string& filename)
{
    vector<string> words;

    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Could not open " << filename << ". Make sure it is in the same folder as your program.\n";
        return words;
    }

    string line;
   while (getline(in, line))
    {
        // Normalize to lowercase so comparisons stay consistent
        for (char& c : line)
            c = (char)tolower(c);

        // Only load valid words and strictly reject invalid lines. Keeps the word list clean instead of 
        // trying to fix them. 
        if (IsValidWord(line))
        {
            words.push_back(line);
        }
    }

    return words;
}

string PickRandomWord(const vector<string>& words)
{
    int index = rand() % (int)words.size();
    return words[index];
}

// Wrote a function for Yes or No functionality. I only use it twice,
// but kept me from writing inline input validation. 
bool AskYesNo(const string& prompt)
{
    while (true)
    {
        cout << prompt;
        string input;
        getline(cin, input);

        if (input.empty()) continue;

        char c = (char)tolower(input[0]);
        if (c == 'y') return true;
        if (c == 'n') return false;

        cout << "Type y or n.\n";
    }
}

bool IsValidWord(const string& w)
{
    if (w.empty()) return false;

    for (char c : w)
    {
        if (!isalpha(c)) return false;
    }

    return true;
}

void AppendWordToFile(const string& filename, const string& word)
{
    ofstream out(filename, ios::app);
    if (!out.is_open())
    {
        cout << "Could not write to " << filename << ".\n";
        return;
    }

    out << word << "\n";
}

int LoadBestStreak(const string& filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        return 0;
    }

    int best = 0;
    in >> best;
    if (best < 0) best = 0;
    return best;
}

void SaveBestStreak(const string& filename, int best)
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Could not write to " << filename << ".\n";
        return;
    }

    out << best;
}