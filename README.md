# 🦖 Chrome Dinosaur Game (SFML 3)

This is a C++ clone of the classic Chrome Dinosaur Game, built using [SFML 3](https://www.sfml-dev.org/).

---

<img width="1189" height="504" alt="screenshot" src="https://github.com/user-attachments/assets/b0133d70-24aa-424c-9d1b-e8047683e8bf" />


## 🛠️ Requirements

- C++20 compatible compiler (GCC, Clang, MSVC)
- [CMake ≥ 3.20](https://cmake.org/download/)
- [SFML 3.x](https://www.sfml-dev.org/) (Graphics, Window, System, Audio modules)

---

## 🖥️ Building the Game

### Windows (Visual Studio)

1. **Install SFML 3:**

   - Download the **SFML 3.x Visual C++** development files from the [SFML website](https://www.sfml-dev.org/download.php).
   - Extract it somewhere (e.g., `C:/Program Files/SFML-3.0.0`).

2. **Clone this repository:**

   ```bash
   git clone https://github.com/blackydrum/chrome-dinosaur.git
   cd chrome-dinosaur
   ```
   
3. **Configure with CMake:**
   Replace the path to SFML with yours:

   ```bash
   cmake -B build -S . -DCMAKE_PREFIX_PATH="C:/Program Files/SFML-3.0.0"
   ```

4. **Build with Visual Studio**

   ```bash
   cmake --build build --config Release
   ```

5. Inside `build/Release`, you'll find `Chrome-Dinosaur.exe`. All required DLLs and the `assets/` folder should be copied automatically.

### Linux

1. **Install SFML 3:**

   If your distro has SFML 3 packages, install them. Otherwise, build from source:

   ```bash
   sudo apt-get install libsfml-dev
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

## ⚠️ Notes
- This game requires SFML 3.x. It will not compile or run with SFML 2.x.
- On Windows, SFML DLLs and assets are automatically copied next to the executable after build.
- On Linux, make sure SFML is discoverable via CMAKE_PREFIX_PATH or installed to a standard location (`/usr/local/lib/cmake/SFML`).
