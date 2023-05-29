all:

	g++ -I src/include -Wall -pedantic -o main My_SDL_Implementation.cpp My_SDL_Shapes.cpp Example_main.cpp  -L src/lib -lmingw32 -lSDL2main -lSDL2
	
	./main.exe
	$(info  )
	$(info ***************************************)
	$(info ************ Program Start ************)
	$(info ***************************************)
	$(info  )



test:
	g++ -Wall -Werror -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2


$(V).SILENT:
	