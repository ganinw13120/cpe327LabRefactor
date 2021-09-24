/*  
 *  user.h
 *
 *  Defines the necessary model for user.
 *
 *  Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 *
 */
#ifndef USER_H
#define USER_H

 /* Structure type for user in the social network
 * This will be the data stored at a vertex of the network. 
 */
typedef struct
{
  char username[32];
  char firstname[32];
  char lastname[32];
  char birthday[16];
} USER_T;   
 
#endif