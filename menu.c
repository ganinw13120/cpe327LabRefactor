/* Module to control menu for socialNetwork program
 *   Created by Sally Goldin 16 September 2021
 */
#include <stdio.h>
#include <string.h>
#include "abstractMenu.h"
#include "abstractUser.h"

/* Present a menu of actions and ask the user which one they
 * want. Keep asking until a valid option is provided.
 * Return the selected option.
 */
int getMenuChoice()
{
  int choice = 0;
  printf("\nAvailable actions:\n");
  printf("\t1 - Create a new user\n");
  printf("\t2 - Show a user's friends\n");
  printf("\t3 - Suggest new friends\n");
  printf("\t4 - Add new friends\n");
  printf("\t5 - Exit the program\n");
  while ((choice < 1) || (choice > 5))
  {
    printf("What action? ");
    /*  62070501006 – Modified 2021-09-23 – Change input method to reduce variable */
    scanf("%d",  &choice);
    rewind(stdin);
  }
  return choice;
}

/*  62070501006 – Modified 2021-09-23 – Add new function which refer from main function, display choice. */
/* Display more input and information
 * about choice 1 : create user.
 * Call user function for users' function part.
 */
void createUserMenu () 
{
  char inputline[32];
  char username[32] ="";
  printf("\nEnter new username: ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",username);
  printf("'%s'", username);
  int status = 0;
  status = checkExistingUser(username);
  if (status == 1) 
  {
    printf("\tSorry, that username is already in use\n");
    return;
  }
  char firstname[32], lastname[32], birthday[16];
  printf("\tWhat is your first name? ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",firstname);
  printf("\tWhat is your last name? ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",lastname);
  printf("\tWhat is your birthday (dd-mm-yyyy)? ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",birthday);
  status = addUser(username, firstname, lastname, birthday);
  if (status != 1) 
  {
      printf("Error adding new user\n");
  }
}

/*  62070501006 – Modified 2021-09-23 – Add new function which refer from main function, display choice. */
/* Display more input and information
 * about choice 2 : print friend.
 * Call user function for users' function part.
 */
void printFriendMenu () 
{
  char inputline[32];
  char username[32] ="";
  printf("\nPrint friends for what user? ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",username);
  printFriends(username,NULL,NULL,0);
}

/*  62070501006 – Modified 2021-09-23 – Add new function which refer from main function, display choice. */
/* Display more input and information
 * about choice 3 : suggest friend.
 * Call user function for users' function part.
 */
void suggestFriendMenu () 
{
  char inputline[32];
  char username[32] ="";
  printf("\nSuggest friends for what user? ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%s",username);
  suggestFriends(username);
}

/*  62070501006 – Modified 2021-09-23 – Add new function which refer from main function, display choice. */
/* Display more input and information
 * about choice 1 : create user.
 * Call user function for users' function part.
 */
void addFrientMenu ()
{
  char inputline[32];
  char username[32] ="";
  printf("\nAdd friends for what user? ");
  fgets(inputline,sizeof(inputline),stdin);
  sscanf(inputline,"%s",username);
  addFriends(username);
}