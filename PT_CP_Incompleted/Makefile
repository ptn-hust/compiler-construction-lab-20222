# Project: parser
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
OBJ      = main.o charcode.o error.o parser.o reader.o scanner.o token.o
LINKOBJ  = main.o charcode.o error.o parser.o reader.o scanner.o token.o
LIBS     = -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib" -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib" -static-libgcc
INCS     = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include"
CXXINCS  = -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include" -I"C:/Program Files (x86)/Dev-Cpp/MinGW64/lib/gcc/x86_64-w64-mingw32/4.9.2/include/c++"
BIN      = parser.exe
CXXFLAGS = $(CXXINCS) 
CFLAGS   = $(INCS) 
RM       = rm.exe -f
CFLAGS	= -Wall -Werror

.PHONY: all all-before all-after clean clean-custom

# all: all-before $(BIN) all-after

# clean: clean-custom
# 	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o $(CFLAGS)

charcode.o: charcode.c
	$(CC) $(CFLAGS) -c charcode.c -o charcode.o $(CFLAGS)

error.o: error.c
	$(CC) $(CFLAGS) -c error.c -o error.o $(CFLAGS)

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c -o parser.o $(CFLAGS)

reader.o: reader.c
	$(CC) $(CFLAGS) -c reader.c -o reader.o $(CFLAGS)

scanner.o: scanner.c
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o $(CFLAGS)

token.o: token.c
	$(CC) $(CFLAGS) -c token.c -o token.o $(CFLAGS)

clean:
	rm -f *.o parser