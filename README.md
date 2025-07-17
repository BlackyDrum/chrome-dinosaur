# 🦖 Chrome Dinosaur Game (SFML 3)

This is a C++ clone of the classic Chrome Dinosaur Game, built using [SFML 3](https://www.sfml-dev.org/).

---

![gif](https://github.com/user-attachments/assets/267ddebc-1540-4968-9c57-445b8f08df4a)

## 🛠️ Requirements

- C++20 compatible compiler (GCC, Clang, MSVC)
- [CMake ≥ 3.20](https://cmake.org/download/)

---

## 🖥️ Building the Game

### Windows (Visual Studio)

1. **Clone this repository:**

   ```bash
   git clone https://github.com/blackydrum/chrome-dinosaur.git
   cd chrome-dinosaur
   ```
   
2. **Configure with CMake:**

   ```bash
   cmake -B build -S .
   ```

3. **Build the project**

   ```bash
   cmake --build build --config Release
   ```

4. Inside `build/Release`, you'll find `Chrome-Dinosaur.exe`.

### Linux

1. **Install dependencies:**

   ```bash
   sudo apt update && sudo apt install \
     libxrandr-dev \
     libxcursor-dev \
     libxi-dev \
     libudev-dev \
     libflac-dev \
     libvorbis-dev \
     libgl1-mesa-dev \
     libegl1-mesa-dev \
     libdrm-dev \
     libgbm-dev \
     libfreetype6-dev
   ```

2. **Clone this repository:**

   ```bash
   git clone https://github.com/blackydrum/chrome-dinosaur.git
   cd chrome-dinosaur
   ```

3. **Build the project:**

   ```bash
   cmake -B build -S .
   cmake --build build --config Release
   ```

4. **Run the game:**

   ```bash
   ./build/Chrome-Dinosaur
   ```

## 🎮 Controls
- **Jump**: `↑ Up`, `W`, or `Space`
- **Duck**: `↓ Down` or `S`

## ⚠️ Notes
- This project automatically downloads and builds SFML from source using `FetchContent`. **You do not need to install SFML manually.**
- On Windows, all required DLLs and the `assets/` and `data/` folder are automatically copied to the output directory after building.
