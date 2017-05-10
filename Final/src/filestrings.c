#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <filestrings.h>
#include <ctype.h>

/* Implemented strcat */
char *stringUnion(char *str1,char *str2){
	char *strUnion;
	int i,len1=strlen(str1),len2=strlen(str2);

		strUnion=(char*)malloc(sizeof(char)*(len1+len2+2));
		strcpy(strUnion,str1);
		
		for(i=0;i<len2;i++) strUnion[i+len1]=str2[i];

		strUnion[i+len1]='\0';

	return strUnion;
}

/* String manipulation to create the output name */
char *createName(char *name,char *extension){
	char *str1,*str2;
		str1=strtok(name,".");
		str2=stringUnion(str1,extension);

	free(str1);

	return str2;
}


/* Function that read's a string from the keyboard */
char *readString(){
	char *string = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one byte */
			string = (char*)realloc(string,sizeof(char)*(n+1));
			/* Reading a char from the file */
			string[n++] = (char) fgetc(stdin);			
		}while(string[n-1] != '\n');
		/* Putting a \0 on at the end of the string */
		string[n-1] = '\0';

	return string;	
}

/* Function that read's a field from the given file */
unsigned char *readField(FILE *file){
	unsigned char *field = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one unsigned byte */
			field = (unsigned char*)realloc(field,sizeof(unsigned char)*(n+1));
			/* Reading a unsigned char from the file */
			field[n++] = (unsigned char) fgetc(file);			
		}while(field[n-1] != ';' && field[n-1] != '\n');
		/* Putting a \0 on at the end of the string */
		field[n-1] = '\0';

	return field;	
}

/* Function that read's a field from the given binary file */
unsigned char *readFieldBinary(FILE *file,int sizeIndicator){
	unsigned char *field = NULL;
	int n = 0;

		/* Loop that will get the string */
		do{
			/* Allocating one unsigned byte */
			field = (unsigned char*)realloc(field,sizeof(unsigned char)*(n+1));
			/* Reading a unsigned char from the file */
			fread(&field[n++],sizeof(unsigned char),1,file);
		}while(field[n-1] != '\n' && field[n-1] != EOF && n < sizeIndicator);
		/* Putting a \0 on at the end of the string */
		field[n-1] = '\0';
	return field;	
}

/* Function that upper case every character in the string */
void strUpper(unsigned char *string){
	int i,size = strlen((char*)string);
	for(i = 0 ; i < size ; i++) string[i] = toupper(string[i]);
}

/* Returns file size */
int fileSize(FILE *file){
	int size;
	fseek(file,0,SEEK_END);
	size = (int) ftell(file);
	rewind(file);

	return size;
}