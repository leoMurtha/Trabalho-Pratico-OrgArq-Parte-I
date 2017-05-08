#ifndef _RFF_H_
#define _RFF_H_

/*
	Write sequence on the output file:
	Fixed Fields: ticket->doc->initialTime->updatedTime
	Variable Fields: domain,name,city,state
*/

/* Funtion that free's the memory of a register content */
void freeRegisterContent(RFF *);

/* Function that will print only one register */
void printRegister_RFF(RFF ,int );

/* Function that read's and recovers one register of the given file */ 
RFF readOneBinary_RFF(FILE *);

/* Function that prints an menu for the field selection and then scan the user option */
int fieldSelection();

/* Print an register that match the position and the criteria given by the user */ 
void printViaPosField_RFF(char *,int ,int );

/* Print an register that match the position give by the user */ 
void printViaPosition_RFF(char *);

/* Print all the registers that match the criteria given by the user */
void printViaField_RFF(char *,int , char *);

/* Function that print all the registers that were recovered one by one and by the demand of the user */
void printAll_RFF(char *);

/* Read's a register of type RFF(Fixed number of fields) of the input,
   write's it in the output */
void readAndWrite_RFF(FILE *,FILE *);

/* Receives a name of a file read's it and create's a new file using
   fixed number of fields in a variable size register */
char *createNewFile_RFF(char *);

#endif
