# Aptitude Assessment System

A clean, console-based Aptitude Assessment System written in C. This application allows users to take quizzes on various topics like C Language, Python, Java, Web Technologies, and General Aptitude.

## Features
- **Clean UI**: Aqua text on white background with a clear layout.
- **Timer**: 60-second countdown for each question.
- **Input System**: "Select then Confirm" style (Press 1-4, then Enter).
- **Instant Feedback**: View your score and review wrong answers at the end of the quiz.
- **Categories**: Multiple quiz topics available.

## How to Run
You can run the pre-compiled executable directly on Windows:

```powershell
.\apti_v2.exe
```

### Compiling from Source
If you have a C compiler (like GCC) installed, you can compile the source code yourself:

```powershell
gcc apti.c -o apti.exe
```

## Controls
- **Number Keys (1-4)**: Select an option.
- **Enter**: Confirm your selection.
- **Backspace**: Clear your current selection.
- **0**: Exit the current quiz or menu.

## Project Structure
- `apti.c`: Main source code file.
- `questions/`: Directory containing text files for each quiz category.
