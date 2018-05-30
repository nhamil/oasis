# Oasis Engine

Open source game engine written in C++ and Java 

## License 

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Dependencies 

* [CMake](https://cmake.org/download/) 
* [SDL2](https://www.libsdl.org/download-2.0.php) 
* [GLEW](http://glew.sourceforge.net/) 

## Building 

### Windows with MinGW

* Install CMake 
* Download SDL2 and GLEW development libraries
  * It is recommended you create a folder called `ThirdParty` and place the folders in there. This will make it easier for CMake to find them. 
  * Rename folder `SDL-2.X.X` to `SDL2`
  * Rename folder `glew-2.X.X` to `GLEW` 
* Run CMake and Make 
  * Other makefile generators may work as well, but MinGW has been tested 
```
mkdir Build 
cd Build 
cmake -G "MinGW Makefiles" .. 
mingw32-make
```


### Linux (Ubuntu) 

* Install dependencies 
```
sudo apt install cmake libsdl2-dev libglew-dev 
```
* Run CMake and Make 
```
mkdir Build
cd Build
cmake .. 
make 
``` 
