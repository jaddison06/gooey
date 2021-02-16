main: build/objects/main.o build/objects/Gooey.o build/objects/WindowManager.o build/objects/RenderWindow.o build/objects/Drawable.o build/objects/Text.o build/objects/MyWidget.o build/objects/Button.o
		g++ build/objects/main.o build/objects/Gooey.o build/objects/WindowManager.o build/objects/RenderWindow.o build/objects/Drawable.o build/objects/Text.o build/objects/MyWidget.o build/objects/Button.o -o ./gooey_demo -lSDL2 -lSDL2_ttf

debug: build/objects/main-debug.o build/objects/Gooey-debug.o build/objects/WindowManager-debug.o build/objects/RenderWindow-debug.o build/objects/Drawable-debug.o build/objects/Text-debug.o build/objects/MyWidget-debug.o build/objects/Button-debug.o
		g++ build/objects/main-debug.o build/objects/Gooey-debug.o build/objects/WindowManager-debug.o build/objects/RenderWindow-debug.o build/objects/Drawable-debug.o build/objects/Text-debug.o build/objects/MyWidget-debug.o build/objects/Button-debug.o -g -O0 -o ./gooey_demo -lSDL2 -lSDL2_ttf

clean:
		rm -r ./build/objects
		mkdir ./build/objects
		rm ./gooey_demo

makefile:
		python3 ./build/generate_makefile.py

build/objects/main.o: ./main.cpp
		g++ -c ./main.cpp -I . -Wall -std=c++11 -o ./build/objects/main.o

build/objects/main-debug.o: ./main.cpp
		g++ -c ./main.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/main-debug.o

build/objects/Gooey.o: ./control/Gooey.cpp ./control/Gooey.h
		g++ -c ./control/Gooey.cpp -I . -Wall -std=c++11 -o ./build/objects/Gooey.o

build/objects/Gooey-debug.o: ./control/Gooey.cpp ./control/Gooey.h
		g++ -c ./control/Gooey.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Gooey-debug.o

build/objects/WindowManager.o: ./graphics/WindowManager.cpp ./graphics/WindowManager.h
		g++ -c ./graphics/WindowManager.cpp -I . -Wall -std=c++11 -o ./build/objects/WindowManager.o

build/objects/WindowManager-debug.o: ./graphics/WindowManager.cpp ./graphics/WindowManager.h
		g++ -c ./graphics/WindowManager.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/WindowManager-debug.o

build/objects/RenderWindow.o: ./graphics/RenderWindow.cpp ./graphics/RenderWindow.h
		g++ -c ./graphics/RenderWindow.cpp -I . -Wall -std=c++11 -o ./build/objects/RenderWindow.o

build/objects/RenderWindow-debug.o: ./graphics/RenderWindow.cpp ./graphics/RenderWindow.h
		g++ -c ./graphics/RenderWindow.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/RenderWindow-debug.o

build/objects/Drawable.o: ./graphics/Drawable.cpp ./graphics/Drawable.h
		g++ -c ./graphics/Drawable.cpp -I . -Wall -std=c++11 -o ./build/objects/Drawable.o

build/objects/Drawable-debug.o: ./graphics/Drawable.cpp ./graphics/Drawable.h
		g++ -c ./graphics/Drawable.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Drawable-debug.o

build/objects/Text.o: ./graphics/widgets/Text.cpp ./graphics/widgets/Text.h
		g++ -c ./graphics/widgets/Text.cpp -I . -Wall -std=c++11 -o ./build/objects/Text.o

build/objects/Text-debug.o: ./graphics/widgets/Text.cpp ./graphics/widgets/Text.h
		g++ -c ./graphics/widgets/Text.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Text-debug.o

build/objects/MyWidget.o: ./graphics/widgets/MyWidget.cpp ./graphics/widgets/MyWidget.h
		g++ -c ./graphics/widgets/MyWidget.cpp -I . -Wall -std=c++11 -o ./build/objects/MyWidget.o

build/objects/MyWidget-debug.o: ./graphics/widgets/MyWidget.cpp ./graphics/widgets/MyWidget.h
		g++ -c ./graphics/widgets/MyWidget.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/MyWidget-debug.o

build/objects/Button.o: ./graphics/widgets/Button.cpp ./graphics/widgets/Button.h
		g++ -c ./graphics/widgets/Button.cpp -I . -Wall -std=c++11 -o ./build/objects/Button.o

build/objects/Button-debug.o: ./graphics/widgets/Button.cpp ./graphics/widgets/Button.h
		g++ -c ./graphics/widgets/Button.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Button-debug.o

