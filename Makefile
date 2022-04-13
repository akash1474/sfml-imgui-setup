libs=-lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio  -lopengl32 -lsfml-network
lib_path=-L./libraries/lib
includes=-I./libraries/include -I./imgui/include -I./include
o_files=main.o imgui.o imgui-SFML.o imgui_tables.o imgui_draw.o imgui_widgets.o
cmds=-g -Wall -std=c++17 


all:compile
	./bin/main.exe
compile:main.o imgui.o
	g++ $(o_files) $(cmds) -o ./bin/main.exe $(includes) $(lib_path) $(libs) 
main.o:./src/main.cpp
	g++ ./src/main.cpp $(cmds) -c $(includes) 
imgui.o:
	g++ ./imgui/src/* $(cmds) -c $(includes) 
clean:
	rm -r *.o
run:
	./bin/main.exe
