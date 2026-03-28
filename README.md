# Snake SDL2

A classic implementation of the Snake game built with **C** and **SDL2**. This project was developed in **Visual Studio** and features persistent high-score tracking and grid-based collision logic.

## 📺 Gameplay Demo

*(Click the video below to watch the gameplay)* 


https://github.com/user-attachments/assets/1a47a30b-54cf-4e13-a4d6-9a58889c10cb


## 🎮 How to Play

1. **Download:** Go to the [Releases](https://www.google.com/search?q=%23) section and download the `Snake_Game.zip`.
2. **Extract:** Unzip the folder to your desktop.
3. **Run:** Open `Snake.exe`. (Make sure `SDL2.dll` remains in the same folder as the exe!)
4. **Controls:** Use the **Arrow Keys** to move. Eat the red apples to grow and beat the high score.

## 🛠️ Development & Build

This project was authored using **Visual Studio**. To build from source:

### Windows (Visual Studio)

1. Clone the repository.
2. Open the project folder in Visual Studio.
3. Ensure the **SDL2 Development Libraries** are linked in your Project Properties (Include Directories and Library Directories).
4. Build and Run (**F5**).


## 📂 Project Structure

* `main.c`: Core game loop and input handling.
* `funcs.c / .h`: Logic for linked-list snake body management and grid rendering.
* `macros.h`: Game constants (Speed, Window Size, FPS).
* `recs.bin`: Binary file used to save the highest score across sessions.
