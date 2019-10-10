GCC=gcc
OPTS=-Wall

all: dice

dice: dice.c
	$(GCC) $(OPTS) dice.c -o dice -lpopt 




