/**
 * Simple social network
 * This code reads a file that defines vertices and edges
 * and builds a graph using the graph ADT defined in abstractGraph.h.
 * It then allows the user to search for users, display their friends,
 * suggest new friends, and add new friends.
 * Version created 16 September 2021 with deliberate Code Smells,
 * for CPE327 Refactoring Exercise
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractMenu.h"
#include "abstractNetwork.h"  

/*  62070501006 – Modified 2021-09-23 – Remove functions to their modules. */
/* main function builds the graph, then enters a loop 
 * doing different operations 
 */
int main(int argc, char* argv[])
{
  /*  62070501006 – Modified 2021-09-23 – Move reject part to top for no file scenario, to reduce unnecessary variable declaration */
  if (argc < 2)
  {
    printf("Please provide an input file name: ./socialNetwork [file]\n");
    exit(0);
  }
  int status = 1;
  status = buildNetwork(argv[1]);
  if (!status)
  {
    printf("Fatal error building the social network\n");
    exit(1);
  }
  /*  62070501006 – Modified 2021-09-23 – Remove some unnecessary variable */
  int option = 0;
  while (option != 5)
  {
    option = getMenuChoice();
    switch(option)
    {
      /*  62070501006 – Modified 2021-09-23 – Move choice functions' to menu.c and userManager.c */
      case 1:
        createUserMenu();
        break;
      case 2:
        printFriendMenu();
        break;
      case 3:
        suggestFriendMenu();
        break;
      case 4:
        addFrientMenu();
        break;
      case 5:
	      break;
    }
  }
  printf("\nGoodbye!\n");
}
