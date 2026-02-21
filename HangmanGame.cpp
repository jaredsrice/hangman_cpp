#include "HangmanGame.h"
#include <iostream>
#include <cctype>

using namespace std;

HangmanGame::HangmanGame()
{
    _word = "";
    _hidden = "";
    _guessesLeft = MAX_GUESSES;
}

// Reset the game state here so we can reuse the same object across multiple rounds. 
void HangmanGame::Reset(const string& newWord)
{
    _word = newWord;
    _hidden = MakeHidden();
    _guessesLeft = MAX_GUESSES;
    _guessed.clear();
}

// Build the hidden word based on the length of the actual word.
// Keeps word length dynamic instead of hardcoding anything. Works really
// well here since we can have the game be dynamic and words can be added with no issue.
string HangmanGame::MakeHidden() const
{
    return string(_word.size(), '_');
}

void HangmanGame::PrintState() const
{
    // Derive wrong guesses from guessesLeft so we don’t have to track
    // two separate counters.
    int wrongGuesses = MAX_GUESSES - _guessesLeft;

    cout << "\n" << GetHangmanArt(wrongGuesses);

    cout << "Word: ";
    for (char c : _hidden) cout << c << ' ';
    cout << "\nGuesses left: " << _guessesLeft;

    cout << "\nGuessed: ";
    if (_guessed.empty())
        cout << "(none)";
    else
        for (char c : _guessed) cout << c << ' ';
    cout << "\n";
}

char HangmanGame::GetGuess()
{
    while (true)
    {
        cout << "Enter a letter: ";
        string input;
        getline(cin, input);

        // Put all input validation in one place so the RunOneTurn method stays clean and focused on main game
        // flow.
        if (input.size() != 1)
        {
            cout << "Type exactly 1 character.\n";
            continue;
        }

        char g = (char)tolower(input[0]);

        // Using isalpha directly for simplicity. Only ever expect and allow standard input, so its fine.
        if (!isalpha(g))
        {
            cout << "Type a letter a-z.\n";
            continue;
        }

        if (_guessed.count(g) > 0)
        {
            cout << "You already guessed that.\n";
            continue;
        }

        return g;
    }
}

bool HangmanGame::ApplyGuess(char guess)
{
    bool found = false;

    for (size_t i = 0; i < _word.size(); i++)
    {
        if (_word[i] == guess)
        {
            _hidden[i] = guess;
            found = true;
        }
    }

    return found;
}

// Another OOP decision. Encapsulates turn logic so main() doesnt manage turn mechanics directly.  
void HangmanGame::RunOneTurn()
{
    PrintState();

    char guess = GetGuess();
    _guessed.insert(guess);

    bool correct = ApplyGuess(guess);

    if (!correct)
    {
        _guessesLeft--;
        cout << "Miss.\n";
    }
    else
    {
        cout << "Hit.\n";
    }
}

bool HangmanGame::IsWon() const
{
    // Here we see the benefit of tracking the hidden word directly. All we need to do is 
    // compare the hidden word to the actual word.  
    return _hidden == _word;
}

bool HangmanGame::IsLost() const
{
    return _guessesLeft <= 0;
}

string HangmanGame::GetWord() const
{
    return _word;
}

// Keep the hangman drawing logic separate from the game logic.
// Makes the main game flow cleaner and easier to read.
string HangmanGame::GetHangmanArt(int wrongGuesses) const
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