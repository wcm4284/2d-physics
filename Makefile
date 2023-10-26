all: compile link

compile:
  g++ -c *.cpp -IC:\SFML-2.6.0\include
link:
  g++ *.o -o main -LC:\SFML-2.6.0\bin -lsfml-graphics -lsfml-window -lsfml-system
clean:
  rm *.o
  rm *.exe
