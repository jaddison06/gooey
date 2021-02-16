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

build/objects/Gooey.o: ./src/control/Gooey.cpp ./src/control/Gooey.h
		g++ -c ./src/control/Gooey.cpp -I . -Wall -std=c++11 -o ./build/objects/Gooey.o

build/objects/Gooey-debug.o: ./src/control/Gooey.cpp ./src/control/Gooey.h
		g++ -c ./src/control/Gooey.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Gooey-debug.o

build/objects/WindowManager.o: ./src/graphics/WindowManager.cpp ./src/graphics/WindowManager.h
		g++ -c ./src/graphics/WindowManager.cpp -I . -Wall -std=c++11 -o ./build/objects/WindowManager.o

build/objects/WindowManager-debug.o: ./src/graphics/WindowManager.cpp ./src/graphics/WindowManager.h
		g++ -c ./src/graphics/WindowManager.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/WindowManager-debug.o

build/objects/RenderWindow.o: ./src/graphics/RenderWindow.cpp ./src/graphics/RenderWindow.h
		g++ -c ./src/graphics/RenderWindow.cpp -I . -Wall -std=c++11 -o ./build/objects/RenderWindow.o

build/objects/RenderWindow-debug.o: ./src/graphics/RenderWindow.cpp ./src/graphics/RenderWindow.h
		g++ -c ./src/graphics/RenderWindow.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/RenderWindow-debug.o

build/objects/Drawable.o: ./src/graphics/Drawable.cpp ./src/graphics/Drawable.h
		g++ -c ./src/graphics/Drawable.cpp -I . -Wall -std=c++11 -o ./build/objects/Drawable.o

build/objects/Drawable-debug.o: ./src/graphics/Drawable.cpp ./src/graphics/Drawable.h
		g++ -c ./src/graphics/Drawable.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Drawable-debug.o

build/objects/Text.o: ./src/graphics/widgets/Text.cpp ./src/graphics/widgets/Text.h
		g++ -c ./src/graphics/widgets/Text.cpp -I . -Wall -std=c++11 -o ./build/objects/Text.o

build/objects/Text-debug.o: ./src/graphics/widgets/Text.cpp ./src/graphics/widgets/Text.h
		g++ -c ./src/graphics/widgets/Text.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Text-debug.o

build/objects/MyWidget.o: ./src/graphics/widgets/MyWidget.cpp ./src/graphics/widgets/MyWidget.h
		g++ -c ./src/graphics/widgets/MyWidget.cpp -I . -Wall -std=c++11 -o ./build/objects/MyWidget.o

build/objects/MyWidget-debug.o: ./src/graphics/widgets/MyWidget.cpp ./src/graphics/widgets/MyWidget.h
		g++ -c ./src/graphics/widgets/MyWidget.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/MyWidget-debug.o

build/objects/Button.o: ./src/graphics/widgets/Button.cpp ./src/graphics/widgets/Button.h
		g++ -c ./src/graphics/widgets/Button.cpp -I . -Wall -std=c++11 -o ./build/objects/Button.o

build/objects/Button-debug.o: ./src/graphics/widgets/Button.cpp ./src/graphics/widgets/Button.h
		g++ -c ./src/graphics/widgets/Button.cpp -I . -Wall -std=c++11 -g -O0 -o ./build/objects/Button-debug.o

