/*  
 *  user.h
 *
 *  Defines the necessary model for vertex.
 *
 *  Created by Gan Mongklakorn on 23 Sep 2021 for CPE 327
 *
 */
#ifndef VERTEX_H
#define VERTEX_H

/* List items for the adjacency list.
 * Each one represents an edge leading to an existing vertex
 */
typedef struct _adjVertex
{
    void * pVertex;           /* pointer to the VERTEX_T this 
                               * item refers to.
                               */
    struct _adjVertex* next;  /* next item in the ajacency list */ 
} ADJACENT_T;

/* Vertex structure - repeated from linkedListGraph */
typedef struct _vertex
{
    char * key;               /* key for this vertex */
    void * data;              /* additional data for this vertex */
    int color;                /* used to mark nodes as visited */
    struct _vertex * next;    /* next vertex in the list */
    ADJACENT_T * adjacentHead;    /* pointer to the head of the
		                   * adjacent vertices list
                                   */
    ADJACENT_T * adjacentTail;    /* pointer to the tail of the
			           * adjacent vertices list
                                   */
}  VERTEX_T;
 
#endif 