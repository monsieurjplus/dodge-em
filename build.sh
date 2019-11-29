g++ -c main.cpp -I/usr/local/Cellar/sfml/2.5.1/include
g++ main.o -o dodge-em-revival -L/usr/local/Cellar/sfml/2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=/usr/local/Cellar/sfml/2.5.1/lib && ./dodge-em-revival