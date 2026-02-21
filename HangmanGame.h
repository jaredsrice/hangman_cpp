
// Went with header guards over #pragma. Guards are more universal
#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include <string>
#include <set>


// I refactored from procedural to OOP style for encapsulation and better organization. 
class HangmanGame
{
    private:
        static constexpr int MAX_GUESSES = 6;

        std::string _word;
        // Track the hidden word directly as opposed to recalculating from scratch each turn. 
        std::string _hidden;
        int _guessesLeft;

        // Using a set here so duplicate guesses are automatically prevented.
        // Keeps the checking for a duplicate letter logic simple.
        std::set<char> _guessed;

        // Marked const so  these functions cant modify the game state. 
        std::string GetHangmanArt(int wrongGuesses) const;
        std::string MakeHidden() const;
        char GetGuess();
        bool ApplyGuess(char guess);

    public:
        // Reuse the same object for multiple rounds as opposed to
        // creating a new one each game. 
        HangmanGame();

        void Reset(const std::string& newWord);
        void RunOneTurn();
        void PrintState() const;

        bool IsWon() const;
        bool IsLost() const;
        std::string GetWord() const;
};

#endif