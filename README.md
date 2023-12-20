# Fantasy-Adventure
A Text-based adventure game project.

![screenshot1](https://i.imgur.com/NVtSdwf.png) --- I am Mr. PDOGS

Welcome! brave warrior, to the world full of magic and  mystery, and your choices will shape the fate of the world. In "Fantasy Adventure, you are about to embark on an endless journey of exploration and exciting adventures.

![demo_screenshot_group27](https://github.com/willychen0146/fantasy-adventure/assets/43375835/e2f89a24-fb1b-49e1-ada7-241abb39c769)

## Usage
### Requirement
Type the following command in your terminal. 

To run this program properly, the system must have the g++ compiler, CMake, and the [SFML](https://www.sfml-dev.org/download.php) library installed.

```sh
git clone https://github.com/willychen0146/fantasy-adventure.git
cd fantasy-adventure
```
#### Linux system (Ubuntu)
```sh
# Install g++ compiler.
sudo apt-get install g++
# Install CMake.
sudo apt install cmake
# Install SFML library.
sudo apt-get install libsfml-dev
```
#### Windows
Need to install the [MSYS2](https://www.msys2.org/) environment which I used in this project, and setup mingw environment or use other method to install the proper environment.

Note: It is essential to add {path/to/msys64/mingw64/bin} from MSYS2 environment to your Windows system path to ensure that SFML and other SFML-related libraries can be properly recognized by the system.
```sh
# MSYS2's mingw64 terminal
# Install g++ compiler.
pacman -S mingw-w64-x86_64-gcc
# Install CMake.
pacman -S mingw-w64-x86_64-cmake
# Install SFML library.
pacman -S mingw-w64-x86_64-sfml
```
#### Other file
Need to download the source file first (file like ost, image, etc.), unzip it and put all the file into the src folder under the root path like the following structure

Download link: [Source file](https://drive.google.com/file/d/11IQt2FRKaZ8WQ39wwUG9c1hON9sq56Y1/view?usp=drive_link)
```
Root
|   CMakeLists.txt
|   fantasy_adventure.cpp
|   README.md
|
+---src
|   +---font
|   |       Arial.ttf
|   |
|   +---image
|   |       bad.jpg
|   |       battle.jpg
|   |       boss1.jpg
|   |       ...
|   |       ...
|   |
|   +---ost
|   |       The-Prelude.mp3
|   |       Yomawari.mp3
|   |       ...
|   |       ...
|   |
|   +---short_txt
|   |       chapter1.txt
|   |       chapter2.txt
|   |       ...
|   |       ...
|   |
|   \---txt
|           chapter1.txt
|           chapter2.txt
|           ...
|           ...
|
\---utils
        character.cpp
        character.h
        game.cpp
        game.h
        item.cpp
        item.h
        utils.cpp
        utils.h
        window.cpp
        window.h
```

### Quick start

```sh
# cd to the CMakeLists.txt file path.
cd {file_path}

# Simply use cmake and make to link and compile the source code. 
# Depending on the system, the commands may not be the same, the following use Windows MSYS2 and linux Ubuntu as an example
'''Windows MSYS2'''
cmake -G "MinGW Makefiles" .
mingw32-make

'''linux Ubuntu'''
cmake .
make

# Execute the executable file based on you system (.exe,.out, etc.).
./{executable_file_name}
```
