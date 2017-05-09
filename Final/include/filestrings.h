#ifndef _FILE_STRINGS_H_
#define _FILE_STRINGS_H_


/* Implemented strcat */
char *stringUnion(char *,char *);

/* String manipulation to create the output name */
char *createName(char *,char *);

/* Function that read's a field from the given file */
unsigned char *readField(FILE *);

/* Function that read's a string from the keyboard */
char *readString();

/* Returns file size */
int fileSize(FILE *);

/* Function that upper case every character in the string */
void strUpper(unsigned char *);

#endif
