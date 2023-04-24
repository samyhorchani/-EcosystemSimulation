CFLAGS=-g -Wall -Wextra -pedantic
CC=gcc

PROGRAMS=tests_ecosys ecosys
all: $(PROGRAMS)

# $@ représente la cible visée par la commande, en l'occurrence, c'est tests_ecosys
tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $^ $(CFLAGS)

ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $^ $(CFLAGS)

# $< est la 1ère dépendance qui permet de construire main_tests.o (en l'occurrence, c'est main_tests.c)
# $^ , pour faire simple, c'est comme $< mais prend en compte toutes les dépendances
main_tests.o: main_tests.c
	$(CC) -o $@ $(CFLAGS) -c $<

main_ecosys.o: main_ecosys.c
	$(CC) -o $@ -c $< $(CFLAGS)

ecosys.o: ecosys.c
	$(CC) -o $@ -c $< $(CFLAGS)


.PHONY:	all clean

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
