#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filestrings.h>
#include <rdr.h>

typedef struct reg{
	unsigned char *domain; // Field variable size (0 case's) 
	unsigned char *doc; // Field fixed size = 20 (1 case's)
	unsigned char *name; // Field variable size (2 cases's)
	unsigned char *state; // Field variable size (3 cases's)
	unsigned char *city; // Field variable size (4 cases's)
	unsigned char *initialTimeStamp; // Field fixed size = 20 (5 cases's)
	unsigned char *updatedTimeStamp; // Field fixed size = 20 (6 cases's)
	int ticket; // Field fixed size (int → 4 bytes) (7 cases's)
}REG;

void switchREG(REG *reg, unsigned char* fieldStr, int locale){
	int auxInt; //this variable was created to help the case 7 switch's

	if(strcmp((char*)fieldStr, "null") == 0 && locale != 7){
		free(fieldStr);
		return;
	}

	switch(locale){
		case 0:
			reg->domain = fieldStr;
			break;

		case 1:
			reg->doc = fieldStr;
			break;
		
		case 2:
			reg->name = fieldStr;
			break;
		
		case 3:
			reg->state = fieldStr;
			break;
		
		case 4:
			reg->city = fieldStr;
			break;
		
		case 5:
			reg->initialTimeStamp = fieldStr;
			break;
		
		case 6:
			reg->updatedTimeStamp = fieldStr;
			break;
		
		case 7:
			if(strcmp((char*)fieldStr, "null") == 0){
				reg->ticket = -1;
			}else{
				auxInt = atoi((char*)fieldStr);
				reg->ticket = auxInt;
				free(fieldStr);
			}
			break;
	}
}

void writeRegister_RDR(FILE *file, REG *reg){
	int sizeField;
	char *emptyStr;
	char delimin = '#';

	//---------- Fixed fields -----------------
	fwrite(&reg->ticket, sizeof(int), 1, file);
	
	if(reg->doc != NULL){
		emptyStr = (char *)calloc(20, sizeof(char));
		strcat(emptyStr,(char*) reg->doc);
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}else{
		emptyStr = (char *)calloc(20, sizeof(char));
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}

	if(reg->initialTimeStamp != NULL){
		emptyStr = (char *)calloc(20, sizeof(char));
		strcat(emptyStr,(char*) reg->initialTimeStamp);
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}else{
		emptyStr = (char *)calloc(20, sizeof(char));
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}

	if(reg->updatedTimeStamp != NULL){
		emptyStr = (char *)calloc(20, sizeof(char));
		strcat(emptyStr,(char*) reg->updatedTimeStamp);
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}else{
		emptyStr = (char *)calloc(20, sizeof(char));
		fwrite(emptyStr, sizeof(char), 20, file);
		free(emptyStr);
	}


	//---------- Variables fields ---------------
	if(reg->domain != NULL){
		sizeField = strlen((char*)reg->domain);
		fwrite(&sizeField, sizeof(int), 1, file);
		fwrite(reg->domain,sizeof(char), sizeField, file);
	}else{
		sizeField = 0;
		fwrite(&sizeField, sizeof(int), 1, file);
	}

	if(reg->name != NULL){
		sizeField = strlen((char*)reg->name);
		fwrite(&sizeField, sizeof(int), 1, file);
		fwrite(reg->name,sizeof(char), sizeField, file);
	}else{
		sizeField = 0;
		fwrite(&sizeField, sizeof(int), 1, file);
	}

	if(reg->city != NULL){
		sizeField = strlen((char*)reg->city);
		fwrite(&sizeField, sizeof(int), 1, file);
		fwrite(reg->city,sizeof(char), sizeField, file);
	}else{
		sizeField = 0;
		fwrite(&sizeField, sizeof(int), 1, file);
	}

	if(reg->state != NULL){
		sizeField = strlen((char*)reg->state);
		fwrite(&sizeField, sizeof(int), 1, file);
		fwrite(reg->state,sizeof(char), sizeField, file);
	}else{
		sizeField = 0;
		fwrite(&sizeField, sizeof(int), 1, file);
	}

	fwrite(&delimin, sizeof(char), 1, file);
}

void freeReg(REG **reg){

	if(reg != NULL && (*reg) != NULL){
		if((*reg)->domain != NULL) free((*reg)->domain);
		if((*reg)->doc != NULL) free((*reg)->doc);
		if((*reg)->name != NULL) free((*reg)->name);
		if((*reg)->state != NULL) free((*reg)->state);
		if((*reg)->city != NULL) free((*reg)->city);
		if((*reg)->initialTimeStamp != NULL) free((*reg)->initialTimeStamp);
		if((*reg)->updatedTimeStamp != NULL) free((*reg)->updatedTimeStamp);

		free((*reg));
		(*reg) = NULL;
	}
}

char *createNewFile_RDR(char *fileNameEntry){
	FILE *fileEntry = fopen(fileNameEntry, "r+");
	FILE *fileNew;
	char *fileNameNew;
	REG *newReg;
	unsigned char *fieldStr;
	int i,size;

	if(fileEntry == NULL){
		printf("File was not found.\n");
		return NULL;
	}

	fileNameNew = createName(fileNameEntry,".rff");
	fileNew = fopen(fileNameNew, "wb+");


	fseek(fileEntry, 0, SEEK_END);
	size = ftell(fileEntry);
	rewind(fileEntry);

	while(ftell(fileEntry) != size){
		newReg = (REG *)calloc(1, sizeof(REG));

		for(i=0;i<8;i++){
			fieldStr = readField(fileEntry);
			switchREG(newReg, fieldStr, i);
		}		

		writeRegister_RDR(fileNew, newReg);
		

		freeReg(&newReg);
	}

	fclose(fileEntry);
	fclose(fileNew);

	return fileNameNew;
}

int fieldRelativePos_RDR(int field){
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
		case 8: // ticket
			pos = 0;
			break;
	}

	return pos;
}

int fieldSeek_RDR(FILE *binaryFile,int field){
	int pos = -1, jump = 3;
	int fSize;
	int fixedFieldSize = (sizeof(char)*20);
	int fieldPos = fieldRelativePos_RDR(field);
	
	if(fieldPos == 0)
		return 0;

	if(fieldPos < 4)
		jump = fieldPos-1;

	pos = sizeof(int)+(jump*fixedFieldSize);
	fseek(binaryFile,pos,SEEK_CUR);	
	
	while(fieldPos-- > 4){
		fread(&fSize,sizeof(int),1,binaryFile);
		pos += fSize;
		fseek(binaryFile,fSize,SEEK_CUR);
	}

	return pos;
}

void printReg(FILE *binaryFile){
	char *auxString, buffer;
	int auxInt;

	system("clear");

	fread(&auxInt, sizeof(int), 1, binaryFile);
	printf("Ticket: %d\n", auxInt);

	auxString = (char *)calloc(20, sizeof(char));
	fread(auxString, sizeof(char), 20, binaryFile);
	printf("Doc: %s\n", auxString);
	free(auxString);

	auxString = (char *)calloc(20, sizeof(char));
	fread(auxString, sizeof(char), 20, binaryFile);
	printf("Initial Date/Hour: %s\n", auxString);
	free(auxString);


	auxString = (char *)calloc(20, sizeof(char));
	fread(auxString, sizeof(char), 20, binaryFile);
	printf("Updated Date/Hour: %s\n", auxString);
	free(auxString);


	//------------- Variables Fields -------------
	fread(&auxInt, sizeof(int), 1, binaryFile);
	if(auxInt == 0){
		printf("Domain: ");
	}else{
		printf("Domain: ");
		//auxString = readFieldBinary(binaryFile, auxInt);
		auxString = (char *)calloc(auxInt, sizeof(char));
		fread(auxString, sizeof(char), auxInt, binaryFile);
		printf("%s", auxString);
		free(auxString);
	}
	printf("\n");


	fread(&auxInt, sizeof(int), 1, binaryFile);
	if(auxInt == 0){
		printf("Name: ");
	}else{
		printf("Name: ");
		//auxString = readFieldBinary(binaryFile, auxInt);
		auxString = (char *)calloc(auxInt, sizeof(char));
		fread(auxString, sizeof(char), auxInt, binaryFile);
		printf("%s", auxString);
		free(auxString);
	}
	printf("\n");


	fread(&auxInt, sizeof(int), 1, binaryFile);
	if(auxInt == 0){
		printf("City: ");
	}else{
		printf("City: ");
		//auxString = readFieldBinary(binaryFile, auxInt);
		auxString = (char *)calloc(auxInt, sizeof(char));
		fread(auxString, sizeof(char), auxInt, binaryFile);
		printf("%s", auxString);
		free(auxString);
	}
	printf("\n");

	fread(&auxInt, sizeof(int), 1, binaryFile);
	if(auxInt == 0){
		printf("State: ");
	}else{
		printf("State: ");
		//auxString = readFieldBinary(binaryFile, auxInt);
		auxString = (char *)calloc(auxInt, sizeof(char));
		fread(auxString, sizeof(char), auxInt, binaryFile);
		printf("%s", auxString);
		free(auxString);
	}
	printf("\n");

	do{
		printf("Press ENTER to continue...\n");
		scanf("%c", &buffer);
	}while(buffer != 10);

	system("clear");
}

int searchByTicket(FILE *binaryFile, int ticket){
	int sizeBinaryFile;
	int auxTicket;
	char c;

	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);

	while(ftell(binaryFile) != sizeBinaryFile){
		fieldSeek_RDR(binaryFile, 8);
		fread(&auxTicket, sizeof(int), 1, binaryFile);
		
		if(ticket == auxTicket){
			fseek(binaryFile,-4,SEEK_CUR);
			printReg(binaryFile);
			return 1;
		}else{
			do{
				fread(&c, sizeof(char), 1, binaryFile);
			}while(c!='#');
		}
	}

	return 0;
}

void searchByFixedFields(FILE *binaryFile, int op, char *searchField){
	int sizeBinaryFile, relativePos;
	char *auxField;
	char c;

	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);

	while(ftell(binaryFile) != sizeBinaryFile){
		relativePos =  fieldSeek_RDR(binaryFile, op);
		auxField = (char *)calloc(20, sizeof(char));
		fread(auxField, sizeof(char), 20, binaryFile);
		
		if(strcmp(auxField, searchField) == 0){
			fseek(binaryFile, -(relativePos+20), SEEK_CUR);
			printReg(binaryFile);
			fread(&c, sizeof(char), 1, binaryFile); // read '#'
			printf("\n\n");
		}else{
			do{
				fread(&c, sizeof(char), 1, binaryFile);
			}while(c!='#');
		}

		free(auxField);
	}
}

void searchByVariablesFields(FILE *binaryFile, int op, char *searchField){
	int sizeBinaryFile, relativePos, sizeField, origin;
	char *auxField;
	char c;

	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);

	while(ftell(binaryFile) != sizeBinaryFile){
		origin = ftell(binaryFile);
		relativePos =  fieldSeek_RDR(binaryFile, op);
		relativePos = relativePos;
		fread(&sizeField, sizeof(int), 1, binaryFile);
		auxField = (char *)calloc(sizeField, sizeof(char));
		fread(auxField, sizeof(char), sizeField, binaryFile);

		
		if(strcmp(auxField, searchField) == 0){
			fseek(binaryFile, origin, SEEK_SET);
			printReg(binaryFile);
			fread(&c, sizeof(char), 1, binaryFile);  // read '#'
			printf("\n\n");
		}else{
			do{
				fread(&c, sizeof(char), 1, binaryFile);
			}while(c!='#');
		}

		free(auxField);
	}
}

void printViaField_RDR(char *fileNameBinary, int op, char *search){
	FILE *binaryFile = fopen(fileNameBinary, "rb");
	int opBFile = fieldRelativePos_RDR(op);
	int ticket;

	if(opBFile == 0){ //ticket
		ticket = atoi(search);
		printf("%d\n", searchByTicket(binaryFile, ticket));
	}else if(opBFile < 4){ //campos fixos
		searchByFixedFields(binaryFile, op, search);
	}else{ //campos variáveis
		searchByVariablesFields(binaryFile, op, search);
	}

	fclose(binaryFile);
}

void printViaPosition_RDR(char *fileNameBinary, int rrn){
	FILE *binaryFile = fopen(fileNameBinary, "rb");
	int counter=0;
	int sizeBinaryFile, sizeField, i;
	
	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);	

	while(ftell(binaryFile) != sizeBinaryFile && counter < rrn){
		fseek(binaryFile, 64, SEEK_CUR);
		for(i=0;i<4;i++){
			fread(&sizeField, sizeof(int), 1, binaryFile);
			fseek(binaryFile, sizeField, SEEK_CUR);
		}

		fseek(binaryFile, 1, SEEK_CUR);
		counter++;
	}

	if(ftell(binaryFile) <= sizeBinaryFile || counter < rrn) printReg(binaryFile);
	else printf("RRN not found\n");
}

void printField(FILE *binaryFile, int field){
	fieldSeek_RDR(binaryFile, field);
	field = fieldRelativePos_RDR(field);
	char *stringAux;
	int intAux;

	switch(field){
		case 0:
			fread(&intAux, sizeof(int), 1, binaryFile);
			printf("Ticket: %d\n", intAux);
			break;
		case 1:
			stringAux = (char *)calloc(20, sizeof(char));
			fread(stringAux, sizeof(char), 20, binaryFile);
			printf("Doc: %s\n", stringAux);
			free(stringAux);
			break;
		case 2:
			stringAux = (char *)calloc(20, sizeof(char));
			fread(stringAux, sizeof(char), 20, binaryFile);
			printf("Inital Date/Hour: %s\n", stringAux);
			free(stringAux);
			break;
		case 3:
			stringAux = (char *)calloc(20, sizeof(char));
			fread(stringAux, sizeof(char), 20, binaryFile);
			printf("Updated Date/Hour: %s\n", stringAux);
			free(stringAux);
			break;
		case 4:
			fread(&intAux, sizeof(int), 1, binaryFile);
			stringAux = (char *)calloc(sizeof(char), intAux);
			fread(stringAux, sizeof(char), intAux, binaryFile);
			printf("Domain: %s\n", stringAux);
			free(stringAux);
			break;
		case 5:
			fread(&intAux, sizeof(int), 1, binaryFile);
			stringAux = (char *)calloc(sizeof(char), intAux);
			fread(stringAux, sizeof(char), intAux, binaryFile);
			printf("Name: %s\n", stringAux);
			free(stringAux);
			break;
		case 6:
			fread(&intAux, sizeof(int), 1, binaryFile);
			stringAux = (char *)calloc(sizeof(char), intAux);
			fread(stringAux, sizeof(char), intAux, binaryFile);
			printf("City: %s\n", stringAux);
			free(stringAux);
			break;
		case 7:
			fread(&intAux, sizeof(int), 1, binaryFile);
			stringAux = (char *)calloc(sizeof(char), intAux);
			fread(stringAux, sizeof(char), intAux, binaryFile);
			printf("State: %s\n", stringAux);
			free(stringAux);
			break;
	}
}

void printViaPosField_RDR(char *fileNameBinary, int rrn, int field){
	FILE *binaryFile = fopen(fileNameBinary, "rb");
	int counter=0;
	int sizeBinaryFile, sizeField, i;
	
	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);	

	while(ftell(binaryFile) != sizeBinaryFile && counter < rrn){
		fseek(binaryFile, 64, SEEK_CUR);
		for(i=0;i<4;i++){
			fread(&sizeField, sizeof(int), 1, binaryFile);
			fseek(binaryFile, sizeField, SEEK_CUR);
		}

		fseek(binaryFile, 1, SEEK_CUR);
		counter++;
	}

	printField(binaryFile, field);

	fclose(binaryFile);
}

void printAll_RDR(char *fileNameBinary){
	FILE *binaryFile = fopen(fileNameBinary, "rb");
	char delimin;
	int sizeBinaryFile;

	fseek(binaryFile, 0, SEEK_END);
	sizeBinaryFile = ftell(binaryFile);
	rewind(binaryFile);

	system("clear");

	while(ftell(binaryFile) != sizeBinaryFile){		
		printReg(binaryFile);
		fread(&delimin, sizeof(char), 1, binaryFile);
	}

	fclose(binaryFile);
}