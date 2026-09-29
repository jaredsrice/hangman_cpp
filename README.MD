# Hangman

I built a C++ Hangman game that picks words from a file and lets you play multiple rounds. You can add words, and the game saves your win streak between sessions. It was a chance for me to practice classes, file handling, and input validation.

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

- I used ChatGPT as a learning and reference tool throughout this project to help think through design approaches, clarify C++ syntax, and review pseudocode ideas. I primarily used AI to strengthen my understanding of the language and standard library features, while ensuring all final code reflects my own understanding.
