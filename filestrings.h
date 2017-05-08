#ifndef _FILE_STRINGS_H_
#define _FILE_STRINGS_H_

/* Function that read's a field from the given file */
unsigned char *readField(FILE *);

/* Function thar read's a field from the given binary file */
unsigned char *readFieldBinary(FILE *,int);

/* Function that read's a string from the keyboard */
char *readString();

/* Returns file size */
int fileSize(FILE *);

/* Function that upper case every character in the string */
void strUpper(unsigned char *);

#endif
