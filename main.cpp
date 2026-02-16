#include <iostream>
#include <string>
#include <set>
#include <cctype>

using namespace std;

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
    int wrongGuesses = 6 - guessesLeft;

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

        // Using isalpha(g) directly for simplicity instead of the more technical unsigned char cast. Only expect
        // standard characters, so this is fine.s
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

int main()
{
    const string word = "apple";   // Day 1: hardcoded
    string hidden = MakeHidden(word);

    int guessesLeft = 6;

    // Use a set here to store guessed letters so duplicates are automatically prevented, and checking for existing guesses is simple.
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

    if (hidden == word)
    {
        cout << "\nYou won. The word was: " << word << "\n";
    }
    else
    {
        cout << "\nYou lost. The word was: " << word << "\n";
    }

    return 0;
}
// next