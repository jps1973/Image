cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra Image.cpp StatusBarWindow.cpp Resource.o -o Image.exe
