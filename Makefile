COMPILADOR = g++

LIBRERIAS_PATH = C:\SDL2MINGW\x86_64-w64-mingw32

SRC = src

CPP_SOURCE = $(wildcard *.cpp) $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*/*.cpp)
CPP_HEADERS = $(wildcard *.hpp) $(wildcard $(SRC)/*.hpp) $(wildcard $(SRC)/*/*.hpp)

#LIB = C:\SDL2

CFLAGS = -std=c++17 -O2 -I"$(LIBRERIAS_PATH)\include\SDL2"

LDFLAGSG = -L"$(LIBRERIAS_PATH)\lib" -lmingw32 -mwindows -mconsole -lSDL2main -lSDL2 -lSDL2_ttf   

TARGET = main.exe

$(TARGET): $(CPP_SOURCE) $(CPP_HEADERS)
	$(COMPILADOR) $(CFLAGS) -o $(TARGET) $(CPP_SOURCE) $(LDFLAGSG)
correr:
	rm -f $(TARGET)