/*  
 *  abstractUser.h
 *
 *  Defines the necessary functions for managing user
 *
 *  Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 *
 */
#ifndef ABSTRACTUSER_H
#define ABSTRACTUSER_H

#include "types/user.h"

/* Check if user exists, return boolean result.
 */
int checkExistingUser(char* username);

/* Add user by user's data.
 */
int addUser(char* username, char* firstname, char* lastname, char* birthday);

/* Print all user friends, return number of friends.
 */
int printFriends(char* username,  USER_T * pExcludeUser, char** userFriends, int count);

/* Print all suggested friends list, by username.
 */
void suggestFriends(char* username);

/* Add user friend.
 */
void addFriends(char* username);
#endif
