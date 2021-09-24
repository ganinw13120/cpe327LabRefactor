/* Module to control menu for socialNetwork program
 *   Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abstractUser.h"
#include "abstractGraph.h"
#include "types/user.h"
#include "types/vertex.h"


/*  62070501006 – Modified 2021-09-23 – Create new function, adding users by data. */
/* Create a new user and add to the social network.
 *   username     Username for the new user 
 *   firstname    Firstname for the new user 
 *   lastname     Lastname for the new user 
 *   birthday     Birthday for the new user 
 * Returns status of adding.
 */
int addUser(char* username, char* firstname, char* lastname, char* birthday)
{
    int status = 0;
    USER_T * newUser = NULL;
    newUser = calloc(1,sizeof(USER_T));
    if (newUser == NULL)
    {
        printf("Memory allocation error creating a user\n");
        return 0;
    }
    if (newUser != NULL)
    {
        strcpy(newUser->username,username);   
        strcpy(newUser->firstname,firstname);   
        strcpy(newUser->lastname,lastname);   
        strcpy(newUser->birthday,birthday);   
        status = addVertex(username,newUser);
        if (status != 1)
        {
            printf("Error adding new user\n");
            free(newUser);
        }   
    }
    return status;
}

/*  62070501006 – Modified 2021-09-23 – Create new function, search if user if exist. */
/* Check if user exists by username.
 * Return result by bool (0 false, 1 true);
 */
int checkExistingUser (char* username) 
{
    USER_T * myProfile = NULL;
    myProfile = findVertex(username);
    if (myProfile == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Look through a list of existing friend usernames
 * to make sure the target username does not appear.
 *    targetUsername           Name we're looking for
 *    friendnames              Array of keys
 *    count                    Size of friendnames
 * Returns 1 if found, 0 if not found
 */
int searchExisting(char* targetUsername, char** friendnames, int count)
{
  int i = 0;
  int found = 0;
  for (i = 0; (i < count) && (!found); i++)
    if (strcmp(targetUsername,friendnames[i]) == 0)
      found = 1;
  return found;
}

/*  62070501006 – Modified 2021-09-23 – Change function to find user in  functions, used in different functions. */
/* This function will print the names of all the friends
 * of the passed user. It will return the number of friends
 * found (which could be 0).
 * The function is used both for simply printing friends of a user (Case1)
 * and for suggesting new friends (by printing the friends of friends) (Case 2)
 *   pUser                  User whose friends we are printing
 *   pExcludeUser           If non-NULL, we are printing suggestions (Case 2)
 *                          So we will not print the header, and we
 *                          will exclude this username if he or she
 *                          appears in the suggestion list
 *   userFriends            Only specified if pExcludeUser is non-null (Case 2)
 *                          holds the keys for all of pExcludeUser's friends
 *                          so we don't suggest someone with whom the
 *                          user is already connected.
 *   count                  0 if userFriends is NULL, else size of userFriends
 */
int printFriends(char* username,  USER_T * pExcludeUser, char** userFriends, int count)
{
    int i = 0;
    int friendCount = 0;
    USER_T * pUser = NULL;
    pUser = findVertex(username);
    if (pUser == NULL)
    {
        printf("\tNo user exists with that username\n");
        return 0;
    }
    int adjustedFriendCount = 0;  /* number of friends who were not excluded */
    char** friendKeys = getAdjacentVertices(pUser->username,&friendCount);
    if (friendCount > 0)
    {
        adjustedFriendCount = friendCount;  
        if (pExcludeUser == NULL)  
            printf("Here is a list of your current friends:\n");
        for (i = 0; i < friendCount; i++)
        {
            USER_T * friend = findVertex(friendKeys[i]);
            if (friend == NULL)
                printf("Something is wrong - can't find USER_T for key '%s'\n",
	                friendKeys[i]);
            else if (friend == pExcludeUser) /* exclude me! */
                adjustedFriendCount--;
            else 
	        {
	            /* exclude people who are already my friends */  
	            if (!searchExisting(friendKeys[i],userFriends,count))
                {
                    printf("\t%s %s (%s) - Birthday %s\n",
                        friend->firstname,friend->lastname,friend->username,
                        friend->birthday);
                }
                else
                    adjustedFriendCount--;
	        }
        }
    }
    else
    {
        if (pExcludeUser == NULL) /* Case 1, when there are 0 adjacents */
        printf("You do not have any friends yet\n");
    }
    if (friendKeys != NULL)
        free(friendKeys);
    return adjustedFriendCount;
}


/*  62070501006 – Modified 2021-09-23 – Move function to user manager module. */
/* Suggest as new friends people who are friends of your friends.
 *   pUser -- focus user for whom we are suggesting friends.
 */
void suggestFriends(char* username)
{
    USER_T * pUser = NULL;
    pUser = findVertex(username);
    if (pUser == NULL)
    {
        printf("\tNo user exists with that username\n");
        return;
    }
    int i = 0;
    int dummyCount = 0;
    int friendCount = 0;
    char** friendKeys = getAdjacentVertices(pUser->username,&friendCount);
    if (friendCount > 0)
    {
        printf("\n-- Here are some people you might like to know --\n");  
        for (i = 0; i < friendCount; i++)
        {
            /*  62070501006 – Modified 2021-09-23 – Move finding user to print friend function, sending username instead. */
            printf("  Friends of %s whom you might like: \n",friendKeys[i]);  
            dummyCount = printFriends(friendKeys[i],pUser,friendKeys,friendCount);
            if (dummyCount == 0)
                printf("\t>> %s has no friends who aren't already your friends\n",friendKeys[i]);
        }
    }
}

/*  62070501006 – Modified 2021-09-23 – Move function to user manager module. */
/* Create friend relationships with the focus user
 *  focusUser      User for whom we are creating friends
 *                 Assumes this user exists
 */
void addFriends(char* username)
{
  USER_T * focusUser = findVertex(username);
  if (focusUser == NULL)
  {
    printf("\tNo user exists with that username\n");
    return;
  }
    char input[32];
    char friendname[32];
    int status = 1;
    printf("\nAdding friends for user '%s %s (%s)'\n",focusUser->firstname,
        focusUser->lastname,focusUser->username);  
    while (1)
    {
        printf("\tWho do you want to add (username)? (DONE to stop) ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%s",friendname);
        if (strcasecmp(friendname,"DONE") == 0)
            break;
        if (strcmp(friendname,focusUser->username) == 0)
            printf("\t>>You can't add yourself as a friend!\n");
        else
        {
            status = addEdge(focusUser->username,friendname);
            if (status == 0)
                printf("\t>> User '%s' does not exist\n",friendname);
            else if (status < 0)
                printf("\t>> User '%s' is already your friend\n",friendname);
            else
                printf("\t>> User '%s' is now your friend\n",friendname);
        }
    }
}