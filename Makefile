CFLAGS = -Wall -Wextra -g
.PHONY: clean

map: map.o map_main.o
map.o: map.c map.h
map_main.o: map_main.c map.h

clean:
	$(RM) *.o map
