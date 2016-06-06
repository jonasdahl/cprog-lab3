#FILES = test.cpp ammunition.cpp char.cpp env.cpp gondorian.cpp lembas.cpp obj.cpp quiver.cpp wizard.cpp backpack.cpp city.cpp food.cpp hobbit.cpp man.cpp orch.cpp ring.cpp treasure.cpp bag.cpp container.cpp forest.cpp house.cpp mine.cpp outdoors.cpp rohirrim.cpp wand.cpp bow.cpp elf.cpp game.cpp indoors.cpp mountain.cpp poison.cpp sword.cpp weapon.cpp 
FILES = *.cpp
CC    = g++
#CC   = clang++-3.6 -L /usr/lib/gcc/x86_64-linux-gnu/4.8 -I /usr/include/x86_64-linux-gnu/c++/4.8 -I /usr/include/c++/4.8 
FLAGS = -std=c++11 -g -Wall -pedantic

all:
	@ clear ; clear
	@ echo "[***] Kompilerar"
	@ make -s test.out
	@ echo "[***] Kör programmet"
#	@ ./test.out
	@ valgrind ./test.out

test.out: test.cpp ammunition.o char.o env.o gondorian.o indoors.o mine.o outdoors.o rohirrim.o weapon.o backpack.o city.o food.o hobbit.o lembas.o mountain.o poison.o sword.o wizard.o bag.o container.o forest.o house.o man.o obj.o quiver.o treasure.o bow.o elf.o game.o orch.o ring.o wand.o *.h 
	@ echo "[***] Kompilerar huvudklassen test.out"
	@ $(CC) $(FLAGS) test.cpp *.o -o test.out

%.o: *.h %.cpp
	@ echo "[***] Kompilerar $*.o"
	@ $(CC) $(FLAGS) -c $*.cpp

clean:
	rm -f *.o *.out
