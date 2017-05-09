#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filestrings.h>

typedef enum{
	FALSE,
	TRUE
}BOOLEAN;

typedef struct{
	int ticket;
	unsigned char document[20];
	unsigned char initialTimestamp[20];
	unsigned char updatedTimestamp[20];
	unsigned char *domain;
	unsigned char *name;
	unsigned char *city;
	unsigned char *state;
}RSI;


/* This functions frees the memory alocated by the register struct
	*/
void freeRegister(RSI *r){

	if(r == NULL){
		printf("Invalid Register for alocation free");
		return;
	}

	free(r->domain);
	free(r->name);
	free(r->city);
	free(r->state);
	free(r);
}

/* Reads the field from de '.csv' file and makes the treatment for the 'null' exeption case
	*/
unsigned char *readFieldVer(FILE *fp){
	unsigned char *field = readField(fp);

	// verifying 'null' exeption, alocates a string of lenght zero
	if(strcmp((char *)field,"null") == 0){
		free(field);
		field = (unsigned char *)malloc(sizeof(unsigned char));
		field[0] = '\0';
	}

	return field;
}

/*	This function reads a variable field, demarcated by a size indicator,from the data file
	*/
unsigned char *readVariableField(FILE *fp){
	unsigned char *field = NULL;
	int fieldSize;

	// Reads fields size indicator
	fread(&fieldSize, sizeof(int), 1, fp);
	// Reads field using the size indicator
	field = (unsigned char*)malloc(sizeof(unsigned char)*(fieldSize+1));
	fread(field, sizeof(unsigned char)*fieldSize, 1, fp);
	field[fieldSize] = '\0';

	return field;
}


/*	This function calculates the size of a register based in the register struct
	*/
int registerSize(RSI *r){
	int rSize = 0;
	int fixedFieldSize = sizeof(char)*20;
	int sizeIndicator = sizeof(int);

	// fixed fields size
	rSize += sizeof(int) + (3*fixedFieldSize);

	// Variable fields size
	rSize += strlen((char *)r->domain) + sizeIndicator;
	rSize += strlen((char *)r->name) + sizeIndicator;
	rSize += strlen((char *)r->state) + sizeIndicator;
	rSize += strlen((char *)r->city) + sizeIndicator;

	return rSize;
}

/*	This function reads a fixed field as a dynamic vector and copy that to the static vector
	*/
void readCSVFixedField(FILE *fp, char *field){
	char *aux = (char *)readFieldVer(fp);
	memcpy(field,aux,strlen(aux)+sizeof(unsigned char));
	free(aux);
}

/*	This function reads all the register fields  from the '.csv' file, and put it
	into the register struct
	*/
RSI *readCSVRegister(FILE *fp){
	RSI *reg = (RSI *)calloc(1,sizeof(RSI));
	char *ticket;

	// domain field reading
	reg->domain = readFieldVer(fp);
	// document field reading
	readCSVFixedField(fp,(char *)reg->document);
	// name field reading
	reg->name = readFieldVer(fp);
	// state field reading
	reg->state = readFieldVer(fp);
	// city field reading
	reg->city = readFieldVer(fp);
	// initial Timestamp field reading
	readCSVFixedField(fp,(char *)reg->initialTimestamp);
	// updated Timestamp field reading
	readCSVFixedField(fp,(char *)reg->updatedTimestamp);
	// ticket field reading
	ticket = (char *)readFieldVer(fp);
	reg->ticket = atoi(ticket);
	free(ticket);

	return reg;
}

/*	This function writes a variable field with its size indicator in the data file
	*/
void writeField(FILE *fp,unsigned char *field){
	int fieldSize = strlen((char *)field);
	// Size indicator writing
	fwrite(&fieldSize,sizeof(int),1,fp);
	// field value writing
	fwrite(field,sizeof(char)*fieldSize,1,fp);
}

/*	This function writes all the register's fields on the data file
	*/
void writeRegister(FILE *fp,RSI *reg){
	int fixedFieldSize = sizeof(char)*20;

	if(reg == NULL){
		printf("Invalid Register for Writing!\n");
		return;
	}

	/* ----------------- Fixed Fields Writing ------------------- */
	// ticket
	fwrite(&reg->ticket,sizeof(int),1,fp);
	// document
	fwrite(reg->document,fixedFieldSize,1,fp);
	// initialTimestamp
	fwrite(reg->initialTimestamp,fixedFieldSize,1,fp);
	// updatedTimestamp
	fwrite(reg->updatedTimestamp,fixedFieldSize,1,fp);

	/* ----------------- Variable Fields Writing ---------------- */
	// domain
	writeField(fp,reg->domain);
	// name
	writeField(fp,reg->name);
	// city
	writeField(fp,reg->city);
	// state
	writeField(fp,reg->state);
}


/*	This function reads all the register's fields from the data file,
	returning the reguister struct with the readed fields
	*/
RSI *readRegister(FILE *fp){
	RSI *reg = (RSI *)calloc(1,sizeof(RSI));
	int  fixedFieldSize = sizeof(char)*20;

	if(feof(fp))
		return NULL;

	// ------------------- Reading size fixed fields ------------------
	//Reading ticket field value
	fread(&reg->ticket,sizeof(int),1,fp);
	//Reading document field value
	fread(reg->document,fixedFieldSize,1,fp);
	//Reading initial timestamp
	fread(reg->initialTimestamp,fixedFieldSize,1,fp);
	//Reading updated timestamp
	fread(reg->updatedTimestamp,fixedFieldSize,1,fp);
	// ------------------- Reading variable size fields ---------------
	//Reading domain field value
	reg->domain = readVariableField(fp);
	//Reading name field value
	reg->name = readVariableField(fp);
	//Reading city field value
	reg->city = readVariableField(fp);
	//Reading state field value
	reg->state = readVariableField(fp);

	return reg;
}

/*	This function prints all the register fields in a ordered way
	*/
void printRegister(RSI *reg,int rSize,int rNum){

	if(reg == NULL){
		printf("Invalid Register for printing!\n");
		return;
	}

	printf("\n\tREGISTER [%d] - Size [%d]\n\n", rNum, rSize);
	printf("Domain: %s\n", reg->domain);
	printf("Document: %s\n",reg->document);
	printf("Name: %s\n",reg->name);
	printf("State: %s\n", reg->state);
	printf("City: %s\n",reg->city);
	printf("Initial Timestamp: %s\n", reg->initialTimestamp);
	printf("Updated Timestamp: %s\n", reg->updatedTimestamp);
	printf("Ticket: %d\n\n", reg->ticket);

}

/*	This function reads and prints a register, demarcaded by a size indicator, from the data file
	*/
void registerRecovery(FILE *fp, int rNum){
	RSI *reg;
	int rSize;

	//Reading register size
	fread(&rSize,sizeof(int),1,fp);
	// Reading Register
	reg = readRegister(fp);
	// Printing register
	printRegister(reg,rSize,rNum);
	freeRegister(reg);

}

/*	This function positions the file pointer right before the register indicated by the rrn
	*/
int registerSearch(FILE *fp, int rnn){
	int rSize;
	while(!feof(fp) && rnn-->0){
		fread(&rSize,sizeof(int),1,fp);
		fseek(fp,rSize,SEEK_CUR);
	}

	if(rnn > 0){
		printf("Register Not Found!\n");
		return -1;
	}
	return 0;
}


/*	Returns the relative position on the file
		of a specified field
 */
int fieldRelativePos(int field){
	int pos = -1;

	switch(field){
		case 1: // domain
			pos = 4;
			break;
		case 2: // document
			pos = 1;
			break;
		case 3: // name
			pos = 5;
			break;
		case 4: // state
			pos = 7;
			break;
		case 5: // city
			pos = 6;
			break;
		case 6: // initial timestamp
			pos = 2;
			break;
		case 7: // updated timestamp
			pos = 3;
			break;
		case 8:
			pos = 0;
			break;
	}

	return pos;
}

/*	This function reads the field right in front of the file pointer
	and prints it
	*/
void fieldRecovery(FILE *fp,int field){

	int fieldPos = fieldRelativePos(field);
	int fixedFieldSize = sizeof(char)*20;

	if(fieldPos == 0){
		int ticket;
		fread(&ticket,sizeof(int),1,fp);
		printf("%d\n",ticket);
	}else if(fieldPos < 4){
		unsigned char *fixedField = (unsigned char *)malloc(fixedFieldSize);
		fread(fixedField,fixedFieldSize,1,fp);
		printf("%s\n",fixedField);
		free(fixedField);
	}else{
		unsigned char *variableField = readVariableField(fp);
		printf("%s\n", variableField);
		free(variableField);
	}

}

/*	This function positions the file pointer right before the searched field
	*/
int fieldSeek(FILE *fp,int field){
	int pos = -1, jump = 3;
	int fSize;
	int fixedFieldSize = sizeof(char)*20;
	int fieldPos = fieldRelativePos(field);

	if(fieldPos == 0)
		return 0;

	if(fieldPos < 4)
		jump = fieldPos-1;

	pos = sizeof(int)+(jump*fixedFieldSize);
	fseek(fp,pos,SEEK_CUR);

	while(fieldPos-- > 4){
		fread(&fSize,sizeof(int),1,fp);
		fseek(fp,fSize,SEEK_CUR);
	}

	return pos;
}

/*	This functions searchs for a field of a register
	*/
BOOLEAN fieldValidation(FILE *fp,int field,char * fieldValue){
	BOOLEAN valid = FALSE;

	int origin = ftell(fp);

	fieldSeek(fp,field);

	int fieldPos = fieldRelativePos(field);
	int fixedFieldSize = sizeof(char)*20;

	if(fieldPos == 0){
		int ticket;
		fread(&ticket,sizeof(int),1,fp);
		if(ticket == atoi(fieldValue))
			valid = TRUE;
	}else if(fieldPos < 4){
		unsigned char *fixedField = (unsigned char *)malloc(fixedFieldSize);
		fread(fixedField,fixedFieldSize,1,fp);
		if(strcmp((char *)fixedField,fieldValue) == 0)
			valid = TRUE;
		free(fixedField);
	}else{
		unsigned char *variableField = readVariableField(fp);
		if(strcmp((char *)variableField,fieldValue) == 0)
			valid = TRUE;
		free(variableField);
	}

	fseek(fp,origin,SEEK_SET);

	return valid;
}


/* 	This function reads a '.csv' file and turns it into a new data file with register
 size indicators, fixed size fields and delimiters for variable size fields
	Returns : The name of the new file */
char *createNewFile_RSI(char *fileNameEntry){
	// File control variables
	FILE *fpEntry = fopen(fileNameEntry, "r");
	char *fileNameNew = "new";
	FILE *fpNew = fopen(fileNameNew, "wb");
	RSI *reg;
	int rSize;

	fseek(fpEntry,0,SEEK_END);
	int fileSize = ftell(fpEntry);
	fseek(fpEntry,0,SEEK_SET);

	while(ftell(fpEntry) < fileSize){
	 	// Register Reading from csv file
		reg = readCSVRegister(fpEntry);
		// Size of register
		rSize = registerSize(reg);
		fwrite(&rSize,sizeof(int),1,fpNew);
		// Register Writing in data file
		writeRegister(fpNew,reg);
		// Register memory liberation
		freeRegister(reg);
	}

	fclose(fpEntry);
	fclose(fpNew);

	return fileNameNew;
}



/* This function prints all the register in the data file
	in a ordered way of fields, printing only register at time */
void printAll_RSI(char *fileName){
	FILE *fp = fopen(fileName,"rb");
	int rNum = 1;

	fseek(fp,0,SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp,0,SEEK_SET);

	while(ftell(fp) != fileSize){

		registerRecovery(fp,rNum++);

		printf("Press a digit to continue printing registers...");
		scanf("%*c");
	}

	fclose(fp);
}

/*
	*/
void printViaField_RSI(char *fileName,int field,char *fieldValue){
	FILE *fp = fopen(fileName,"rb");
	BOOLEAN validRegister;
	int rNum =0, rSize;

	fseek(fp,0,SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp,0,SEEK_SET);

	while(ftell(fp) != fileSize){

		// Verifying field
		fread(&rSize,sizeof(int),1,fp);
		validRegister = fieldValidation(fp,field,fieldValue);
		fseek(fp,(-1)*sizeof(int),SEEK_CUR);

		if(validRegister){
			registerRecovery(fp,rNum);
			printf("Press a digit to continue printing registers...");
			scanf("%*c");
		}else{
			fseek(fp,rSize+sizeof(int),SEEK_CUR);
		}

		rNum++;

	}

	fclose(fp);
}

/* This function prints the values of a register in a especified position
	*/
void printViaPosition_RSI(char *fileName,int rnn){
	FILE *fp = fopen(fileName,"rb");

	// Searching for the register
	registerSearch(fp,rnn);
	// Printing Register
	registerRecovery(fp,rnn);

	fclose(fp);
}

/*
	*/
void printViaPosField_RSI(char *fileName,int rnn,int field){
	FILE *fp = fopen(fileName,"rb");
	int rSize;

	// Searching for the register
	registerSearch(fp,rnn);

	// Searching and printing Field
	fread(&rSize,sizeof(int),1,fp);
	fieldSeek(fp,field);
	fieldRecovery(fp,field);

	fclose(fp);
}
