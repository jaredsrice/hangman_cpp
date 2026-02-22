# Overview

I developed a console-based Hangman game in C++ that allows the user to play repeated rounds against a randomly selected word from a file. The program is written using OOP fundamentals, along with structured game logic, input validation, the ability to read/write to a file, and a persistent streak tracker. Words are loaded from the text file at startup, and the user has the ability to add a new word to the wordback if desired. The current winstreak is tracked between sessions. 

[Software Demo Video](https://youtu.be/pc6F-Op0jPE)

# Development Environment

- Visual Studio Code
- MacOS Command Line Tools (g++)
- Git/GitHub

# Libraries Used

- `<iostream>` for console input/output
- `<vector>` for dynamic word storage
- `<set>` for tracking guessed letters without duplicates
- `<fstream>` for file reading/writing
- `<cctype>` for validating and normalizing characters
- `<cstdlib>` with `<ctime>` for random number generation

# Useful Websites

- [C Plus Plus](https://cplusplus.com)
- [CppReference](https://en.cppreference.com)
- [Cplusplus](http://www.cplusplus.com/reference/stl/)
- [Stack Overflow](https://stackoverflow.com)

# Future Work

- Implement a GUI to replace the console interface
- Add a difficulty setting that would filter word lengths
- Add the ability to guess the whole word

# AI disclosure

- I used ChatGPT as a learning and reference tool throughout this project to help think through design approaches,clarify C++ syntax, and review pseudocode ideas. I primarily used AI to strengthen my understanding of the language and standard library features, while ensuring all final code reflects my own understanding. 