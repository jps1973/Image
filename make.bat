cls

del *.exe

windres Resource.rc -o Resource.o

g++ -mwindows -m64 -static -Wall -Wextra Image.cpp Bitmap.cpp StatusBarWindow.cpp Resource.o -o Image.exe -lole32 -loleaut32 -luuid
