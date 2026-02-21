#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_GUESSES = 6; 

// TODO (Part 2): Create class HangmanGame and move these responsibilities into it:
// - State: word, hidden, guessesLeft, guessed
// - Methods: Reset(newWord), PrintState(), GetGuess(), ApplyGuess/ProcessGuess(), IsWon(), IsLost()

// Pass strings by const reference to avoid copying and to prevent accidental changes.
string MakeHidden(const string& word)
{
    return string(word.size(), '_');
}

// Isolated the display logic for the hangman art into its own function to keep the game loop clean.
string GetHangmanArt(int wrongGuesses)
{
    switch (wrongGuesses)
    {
        case 0:
            return
                "  +---+\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n";
        case 1:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n";
        case 2:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "=========\n";
        case 3:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|   |\n"
                "      |\n"
                "      |\n"
                "=========\n";
        case 4:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                "      |\n"
                "      |\n"
                "=========\n";
        case 5:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " /    |\n"
                "      |\n"
                "=========\n";
        default:
            return
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " / \\  |\n"
                "      |\n"
                "=========\n";
    }
}

void PrintState(const string& hidden, int guessesLeft, const set<char>& guessed)
{
    // Derive wrong guesses from guessesLeft to avoid tracking two separate counters.
    int wrongGuesses = MAX_GUESSES - guessesLeft;

    cout << "\n" << GetHangmanArt(wrongGuesses);

    cout << "Word: ";
    for (char c : hidden) cout << c << ' ';
    cout << "\nGuesses left: " << guessesLeft;

    cout << "\nGuessed: ";
    if (guessed.empty())
    {
        cout << "(none)";
    }
    else
    {
        for (char c : guessed) cout << c << ' ';
    }
    cout << "\n";
}

char GetGuess(const set<char>& guessed)
{
    while (true)
    {
        cout << "Enter a letter: ";
        string input;
        getline(cin, input);

        if (input.size() != 1)
        {
            cout << "Type exactly 1 character.\n";
            continue;
        }

        char g = tolower(input[0]);

        // Using isalpha(g) directly for simplicity instead of the more technical unsigned char cast.
        // Only expect standard characters, so this is fine.
        if (!isalpha(g))
        {
            cout << "Type a letter a-z.\n";
            continue;
        }

        if (guessed.count(g) > 0)
        {
            cout << "You already guessed that.\n";
            continue;
        }

        return g;
    }
}

bool ApplyGuess(const string& word, string& hidden, char guess)
{
    bool found = false;

    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] == guess)
        {
            hidden[i] = guess;
            found = true;
        }
    }

    return found;
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

// Loads all words into memory at once during startup. Simpler and faster than dealing with it every round.
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
        string cleaned = "";

        // Normalize input to keep game logic consistent.
        for (char c : line)
        {
            char lc = tolower(c);
            if (isalpha(lc)) cleaned += lc;
        }

        if (!cleaned.empty())
        {
            words.push_back(cleaned);
        }
    }

    return words;
}

string PickRandomWord(const vector<string>& words)
{
    int index = rand() % (int)words.size();
    return words[index];
}

bool AskYesNo(const string& prompt)
{
    while (true)
    {
        cout << prompt;
        string input;
        getline(cin, input);

        if (input.size() == 0) continue;

        char c = tolower(input[0]);
        if (c == 'y') return true;
        if (c == 'n') return false;

        cout << "Type y or n.\n";
    }
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

int main()
{
    srand((unsigned)time(nullptr));

    const string WORDS_FILE = "words.txt";
    const string STATS_FILE = "stats.txt";

    vector<string> words = LoadWords(WORDS_FILE);
    if (words.empty())
    {
        cout << "No usable words found in " << WORDS_FILE << ". Add words (one per line) and try again.\n";
        return 0;
    }

    // Store best streak separately to maintain file independence and integrity.
    int bestStreak = LoadBestStreak(STATS_FILE);
    int currentStreak = 0;

    cout << "Best win streak: " << bestStreak << "\n";

    // TODO (Part 3): Simplify main() after you create HangmanGame.
    // Goal: main() should only deal with:
    // - load words + stats
    // - pick word
    // - run HangmanGame until win/lose
    // - update stats + optionally add word
    // - replay prompt
    while (true)
    {
        string word = PickRandomWord(words);
        string hidden = MakeHidden(word);

        int guessesLeft = MAX_GUESSES;

        // Use a set here to store guessed letters so duplicates are automatically prevented,
        // and checking for existing guesses is simple.
        set<char> guessed;

        while (guessesLeft > 0 && hidden != word)
        {
            PrintState(hidden, guessesLeft, guessed);

            char guess = GetGuess(guessed);
            guessed.insert(guess);

            bool correct = ApplyGuess(word, hidden, guess);

            if (!correct)
            {
                guessesLeft--;
                cout << "Miss.\n";
            }
            else
            {
                cout << "Hit.\n";
            }
        }

        PrintState(hidden, guessesLeft, guessed);

        bool won = (hidden == word);

        if (won)
        {
            cout << "\nYou won. The word was: " << word << "\n";
            currentStreak++;

            if (currentStreak > bestStreak)
            {
                bestStreak = currentStreak;
                SaveBestStreak(STATS_FILE, bestStreak);
                cout << "New best win streak: " << bestStreak << "\n";
            }

            // Adds the new word to the in-memory list so we dont have to fully restart to use it.
            if (AskYesNo("Add a new word to the word bank? (y/n): "))
            {
                while (true)
                {
                    cout << "Enter a new word (letters only): ";
                    string newWord;
                    getline(cin, newWord);

                    for (char& c : newWord) c = tolower(c);

                    if (!IsValidWord(newWord))
                    {
                        cout << "Invalid word. Letters only, no spaces.\n";
                        continue;
                    }

                    AppendWordToFile(WORDS_FILE, newWord);
                    words.push_back(newWord);
                    cout << "Word added.\n";
                    break;
                }
            }
        }
        else
        {
            cout << "\nYou lost. The word was: " << word << "\n";
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