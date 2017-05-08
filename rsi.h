#ifndef _RSI_H_
#define _RSI_H_




/* Receives the entry file(.csv) name and return the output file(data file) name */
char *createNewFile_RSI(char *);
/* Receives the file name and prints all the registers */
void printAllData_RSI(char *);
/* Receives the file name, the field position and the field searched value and prints all the searched registers*/
void printDeterminedRegisters_RSI(char *,int,char *);
/* Receives the register position */
void printOneRegister_RSI(char *,int );
/* Receives the file name, the register position and the field position */
void printField_RSI(char *,int,int);



#endif
