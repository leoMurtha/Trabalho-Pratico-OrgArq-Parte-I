#ifndef _RFF_H_
#define _RFF_H_

/* Print an register that match the position and the criteria given by the user */ 
void printViaPosField_RFF(char *,int ,int );

/* Print an register that match the position give by the user */ 
void printViaPosition_RFF(char *,int);

/* Print all the registers that match the criteria given by the user */
void printViaField_RFF(char *,int , char *);

/* Function that print all the registers that were recovered one by one and by the demand of the user */
void printAll_RFF(char *);

/* Receives a name of a file read's it and create's a new file using
   fixed number of fields in a variable size register */
char *createNewFile_RFF(char *);

#endif