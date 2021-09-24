/* Module to control menu for socialNetwork program
 *   Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 */
#include <stdio.h>
#include <string.h>
#include "abstractGraph.h"
#include "abstractUser.h"
#include "types/user.h"
#include "types/vertex.h"

/*  62070501006 – Modified 2021-09-23 – Move build network to new module. */
/* Initializes and builds the network based on
 * the information in the file.
 * Returns 1 if successful, 0 if any error occurred
 */
int buildNetwork(char * filename)
{
  FILE* pIn = NULL;
  /*  62070501006 – Modified 2021-09-23 – Move reject part to top for no file scenario, to reduce unnecessary variable declaration */
  int status = 1; /* used to test for errors */
  /* try to open the file */
  pIn = fopen(filename,"r");
  if (pIn == NULL)
  {
    printf("Error - cannot open file '%s'\n", filename);
    return 0;  
  }
  /* since we can open the file, go ahead and initialize the graph */
  status = initGraph(1000,0); /* this should be an UNDIRECTED graph */
  if (!status)
  {
    printf("Error initializing the graph\n");
    return status;  
  }

  char inputline[128];
  char username[32];
  char username2[32];  /* second user in a 'FRIEND' line */
  char firstname[32];
  char lastname[32];
  char birthday[16];
  /* Let's read the file and build the network */
  while (fgets(inputline,sizeof(inputline),pIn) != NULL)
  {
      printf("read %s", inputline);
      /* if this is a FRIEND specification, create an edge */  
      if (strncmp(inputline,"FRIEND",strlen("FRIEND")) == 0)
      {
        if (sscanf(inputline,"FRIEND %s %s",username,username2) != 2)
	      {
	        printf("Invalid format for FRIEND line: '%s'",inputline);  
	      }
        else
        {
          status = addEdge(username,username2);
          if (status == 0)
            printf("At least one user ('%s' and '%s') does not exist\n",username,username2);
          else if (status < 0)
            printf("'%s' and '%s' are already friends\n", username,username2);
          else
            printf("'%s' and '%s' are now friends\n", username,username2);
        }
      }
      else /* this is a user (VERTEX) */
      {
        if (sscanf(inputline,"%s %s %s %s",username,firstname,lastname,birthday) != 4)
            printf("Invalid input line, skipping: '%s'",inputline);
        else
        {
            VERTEX_T * dummy;  
            VERTEX_T* v = findVertexByKey(username,&dummy);  
            if (v != NULL)
            {
                printf(">> ERROR in data file! User '%s' already exists\n",username);
            }
            else
            {
                /*  62070501006 – Modified 2021-09-23 – Move user adding to functions, which also used in other scenario */
                status = addUser(username,firstname, lastname, birthday);
                if (status == 0)
                    printf(">> Memory allocation error adding user '%s'\n",username);
                else if (status < 0)
                    printf(">> ERROR in data file! User '%s' already exists\n",username);
                else   
                    printf("Successfully added user '%s' to the social network\n",username);
            }
        }	
      }
    }
    fclose(pIn);
    return 1;
}
