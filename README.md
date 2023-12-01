# fantasy-adventure
A Programming-Design final project.

![screenshot1](https://i.imgur.com/NVtSdwf.png) --- I am Mr. PDOGS

## Usage
### Requirement
Type the following command in your terminal, you should have g++ compiler and [SFML](https://www.sfml-dev.org/download.php) in your system to run program.

```sh
git clone https://github.com/willychen0146/fantasy-adventure.git
cd fantasy-adventure
```
#### Linux system (Ubuntu)
```sh
# Install g++ compiler.
sudo apt-get update
sudo apt-get install g++
# Install SFML library.
sudo apt-get install libsfml-dev
```
#### Windows
```sh
# Need to install the msys2 -> mingw environment or use other method.
# msys2 terminal
# Install g++ compiler.
pacman -S mingw-w64-x86_64-gcc
# Install SFML library.
pacman -S mingw-w64-x86_64-sfml
```
#### Other file
Need to download the source file (file like mp3, txt, etc.), unzip it and put it into the under the root path like the following structure

Download link: [Source file](https://drive.google.com/file/d/11IQt2FRKaZ8WQ39wwUG9c1hON9sq56Y1/view?usp=drive_link)
```
Root
│   main.cpp
│
└───src
    │
    ├───ost
    │       Chasing-the-Black-Caped-Man.mp3
    │       Fighting.mp3
    │       J-E-N-O-V-A.mp3
    │       test.mp3
    │       The-Prelude.mp3
    │       Yomawari.mp3
    │
    └───text
            scene_2.txt
```

### Quick start

```sh
# cd to the main.cpp file path.
cd {file_path}

# Simply compile the source code.
g++ main.cpp -o {output_file_name} -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Execute the executable file based on you system (.exe,.out, etc.).
./{output_file_name}
```