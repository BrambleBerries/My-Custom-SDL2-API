all:

	g++ -Wall -Werror -pedantic -I src/include -L src/lib -o main My_SDL_Implementation.cpp Example_main.cpp  -lmingw32 -lSDL2main -lSDL2
	
	./main.exe
	$(info  )
	$(info ***************************************)
	$(info ************ Program Start ************)
	$(info ***************************************)
	$(info  )



test:
	g++ -Wall -Werror -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2


$(V).SILENT:
	