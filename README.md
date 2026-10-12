# Snake SFML – projekt C++

Projekt obiektowej gry Snake wykonany w C++20 z użyciem biblioteki SFML.

## Funkcje

- graficzne okno gry SFML,
- menu główne,
- tryb klasyczny,
- tryb z przeszkodami,
- sterowanie WASD albo strzałkami,
- obiekty planszy obsługiwane polimorficznie,
- zwykłe jedzenie i jedzenie bonusowe,
- zapis oraz odczyt wyników z pliku `scores.txt`,
- struktura klas przygotowana pod obronę projektu.

## Instalacja SFML na macOS

Najprościej przez Homebrew:

```bash
brew install sfml cmake
```

Projekt jest przygotowany pod SFML 3.0. Jeżeli na laboratorium używana jest inna wersja, wystarczy dostosować `CMakeLists.txt`.

## Uruchomienie w terminalu

```bash
mkdir build
cd build
cmake ..
cmake --build .
./SnakeSFML
```

## Uruchomienie w VS Code

1. Otwórz folder projektu w VS Code.
2. Upewnij się, że masz zainstalowane rozszerzenia C/C++ oraz CMake Tools.
3. W terminalu VS Code wykonaj:

```bash
mkdir build
cd build
cmake ..
cmake --build .
./SnakeSFML
```

## Sterowanie

- `W` / strzałka w górę – ruch w górę,
- `S` / strzałka w dół – ruch w dół,
- `A` / strzałka w lewo – ruch w lewo,
- `D` / strzałka w prawo – ruch w prawo,
- `1` – nowa gra klasyczna,
- `2` – nowa gra z przeszkodami,
- `Enter` – powrót do menu po zakończeniu gry,
- `Esc` – wyjście.

## Struktura projektu

```text
SnakeSFMLProject/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── Board.h
│   ├── BonusFood.h
│   ├── Direction.h
│   ├── Food.h
│   ├── Game.h
│   ├── GameObject.h
│   ├── GameState.h
│   ├── InputHandler.h
│   ├── Obstacle.h
│   ├── Position.h
│   ├── Renderer.h
│   ├── ScoreManager.h
│   └── Snake.h
└── src/
    ├── Board.cpp
    ├── BonusFood.cpp
    ├── Food.cpp
    ├── Game.cpp
    ├── GameObject.cpp
    ├── InputHandler.cpp
    ├── Obstacle.cpp
    ├── Renderer.cpp
    ├── ScoreManager.cpp
    ├── Snake.cpp
    └── main.cpp
```
