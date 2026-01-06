# 🐍 Snake Game (SFML)

A polished **Snake game** developed in **C++** using **SFML**, featuring menus, animations, sound effects, and a structured game state system.  
This project focuses on clean architecture, object-oriented design, and real-time game mechanics.

---

## 🎮 Features

- Classic Snake gameplay
- Grid-based movement system
- Main menu & pause menu
- Smooth menu animations (fade & scale)
- Keyboard navigation in menus
- Pause / Resume functionality
- Sound effects & background music
- Score system
- Win & loss conditions
- Framerate-independent movement
- Modular game state system (Main Menu, Playing, Paused)

---

## 🧠 Architecture Overview

The game is centered around a `Game` class that manages:

- The main game loop
- Event handling
- Game state transitions
- Rendering and updates
- Menu logic and animations
- Sound and music management
- UI text handling

Key components:
- `Game` – core game controller
- `Snake` – movement, growth, collisions
- `Fruit` – spawning logic
- `Grid` – visual playfield
- `Menu` – menu navigation
- `TextManager` – text rendering & animations
- `SoundManager` – sound effects & music

---

## ⌨️ Controls

### Gameplay
- **W / A / S / D** – Move snake
- **ESC** – Pause game

### Menus
- **Up / Down Arrow** – Navigate
- **Enter** – Select option

---

## 🛠️ Technologies Used

- **C++**
- **SFML**
  - Graphics
  - Window
  - Audio
  - System

---

## 🚀 Getting Started

### Prerequisites

- C++ compiler (GCC / Clang / MSVC)
- SFML installed on your system

### Build & Run (example)

```bash
g++ *.cpp -o snake -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./snake
