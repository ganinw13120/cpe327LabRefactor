# Makefile for code in refactoring assignment

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= socialNetworkRF$(EXECEXT)

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

linkedListGraphRF.o :	linkedListGraphRF.c abstractGraph.h abstractQueue.h
	gcc -c linkedListGraphRF.c

menu.o : 	menu.c abstractMenu.h abstractUser.h
	gcc -c menu.c

userManager.o : 	userManager.c abstractUser.h
	gcc -c userManager.c
	

socialNetworkRF.o :	socialNetworkRF.c abstractGraph.h types/user.h types/vertex.h
	gcc -c socialNetworkRF.c


socialNetworkRF$(EXECEXT) : socialNetworkRF.o network.o menu.o userManager.o linkedListGraphRF.o linkedListQueue.o
	gcc -o socialNetworkRF$(EXECEXT) socialNetworkRF.o network.o menu.o userManager.o linkedListGraphRF.o linkedListQueue.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
