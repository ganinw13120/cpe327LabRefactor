/*  
 *  abstractMenu.h
 *
 *  Defines the necessary functions for menu
 *
 *  Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 *
 */
#ifndef ABSTRACTMENU_H
#define ABSTRACTMENU_H

/* Print out all the menu and return user choice
 */
int getMenuChoice();

/* Print out information and collect more information about creating user and call users' function for user part.
 */
void createUserMenu();

/* Print out information and collect more information about print friends and call users' function for user part.
 */
void printFriendMenu();

/* Print out information and collect more information about suggesting friends and call users' function for user part.
 */
void suggestFriendMenu();

/* Print out information and collect more information about adding new friends and call users' function for user part.
 */
void addFrientMenu();

#endif
