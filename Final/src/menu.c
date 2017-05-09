#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <rff.h>
#include <rsi.h>
#include <rdr.h>
#include <filestrings.h>

//Function to read file from user
char *new_file(){
        char *name;
        printf("Type the name of the file:\n>>>");
        name = readString();
        system("clear");
        return name;
}

//Function to select the way to work with records
int record_type(){
        int option;
        printf("Select the type of file organization.\n");
        printf("============================ORGANIZATION============================\n");
        printf("[1] -> Records with variable sizes with record size indicators.\n");
        printf("[2] -> Records with variable sizes with delimiters between records.\n");
        printf("[3] -> Records with variable sizes with fixed number of fields.\n");
        printf("[4] -> Exit program.\n>>>");
        scanf("%d%*c", &option);
        system("clear");
        return option;

}
//Function to display the menu for the user to select the task to perform
int menu(){
        int option;
        printf("Select the operation to perform.\n");
        printf("================OPERATIONS================\n");
        printf("[0] -> Create and read new binary file.\n");
        printf("[1] -> Display data from file.\n");
        printf("[2] -> Display data by criteria (ex:Domain).\n");
        printf("[3] -> Display data from specific record.\n");
        printf("[4] -> Display data from specific record and specific field.\n");
        printf("[5] -> Close current file.\n>>>");
        scanf("%d%*c",&option);
        system("clear");
        return option;
}
//Function to display the diferents field that exist for the case 2 and 4 of the menu
int fields(){
        int field;
        printf("Select the wanted field.\n");
        printf("================FIELDS================\n");
        printf("[1] -> Domain.\n");
        printf("[2] -> Document.\n");
        printf("[3] -> Name.\n");
        printf("[4] -> State.\n");
        printf("[5] -> City.\n");
        printf("[6] -> Date of record.\n");
        printf("[7] -> Date of Update.\n");
        printf("[8] -> Ticket.\n>>>");
        scanf("%d%*c",&field );
        system("clear");
        return field;
}


int main (int argc,char *argv[]){
        char *file_name = NULL, *output_file = NULL;
        char *key;
        bool stop = false,flag = false, close = false; //Stop program
        int menu_op, position, field, regType;

        printf("============================\n|GOVERNAMENTAL DOMAIN DATAS|\n============================\nPress ENTER to continue.\n");
        getchar();
        system("clear");
        

        while(!stop){
                //Display menu opcion
                regType = record_type();
                close = false; // Set false to enter the while loop of the display menu

                //Switch to select between RSI,RDR,RFF
                switch (regType) {

                case 1: // RSI
                        /* No file opened yet */
                        flag = false;
                        while(!close){
                                //Display menu
                                menu_op = menu();
                                switch (menu_op) {

                                case 0:
                                        //Create output file
                                        //Read the name of file
                                        if(output_file != NULL){
                                                printf("Can't open another file until you close the current one.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        file_name = new_file();
                                        output_file = createNewFile_RSI(file_name);
                                        if(output_file != NULL) flag = true; /* File is valid */
                                        break;

                                case 1: // Show data from file
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printAll_RSI(output_file);
                                        break;
                                case 2:// Search by given value
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        field = fields();//Select field to search by
                                        printf("Type the key that will be searched in the file.\n>>>" );
                                        key = readString();
                                        printViaField_RSI(output_file,field,key);
                                        break;
                                case 3: // Show data from a record
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c",&position);
                                        printViaPosition_RSI(output_file,position);
                                        break;
                                case 4: // Show data frome a given record and field
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c", &position);
                                        field = fields(); //Select field to search by
                                        printViaPosField_RSI(output_file,position,field);
                                        break;
                                case 5:// Close file
                                        if(output_file == NULL){
                                                printf("Can't close a unopended file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        free(output_file);
                                        flag = false; /* Open new file or will give errors */
                                        close = true; //Stop while and exit
                                        break;
                                default:
                                        printf("Option was not selected.\n");
                                        break;
                                }
                                
                        }
                        break;                           
                case 2: //RDR
                   /* If there is a valid file to work on */
                     flag = false;
                        while(!close){
                                //Display menu
                                menu_op = menu();
                                switch (menu_op) {

                                case 0:
                                        //Create output file
                                        //Read the name of file
                                        if(output_file != NULL){
                                                printf("Can't open another file until you close the current one.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        file_name = new_file();
                                        output_file = createNewFile_RDR(file_name);
                                        if(output_file != NULL) flag = true; /* File is valid */
                                        break;

                                case 1: // Show data from file
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printAll_RDR(output_file);
                                        break;
                                case 2:// Search by given value
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        field = fields();//Select field to search by
                                        printf("Type the key that will be searched in the file.\n>>>" );
                                        key = readString();
                                        printViaField_RDR(output_file,field,key);
                                        break;
                                case 3: // Show data from a record
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c",&position);
                                        printViaPosition_RDR(output_file,position);
                                        break;
                                case 4: // Show data frome a given record and field
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c", &position);
                                        field = fields(); //Select field to search by
                                        printViaPosField_RDR(output_file,position,field);
                                        break;
                                case 5:// Close file
                                        if(output_file == NULL){
                                                printf("Can't close a unopended file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        free(output_file);
                                        flag = false; /* Open new file or will give errors */
                                        close = true; //Stop while and exit
                                        break;
                                default:
                                        printf("Option was not selected.\n");
                                        break;
                                }
                                
                        }          
                        break;
                case 3: //RFF
                        /* If there is a valid file to work on */
                        flag = false;
                        while(!close){
                                //Display menu
                                menu_op = menu();
                                switch (menu_op) {

                                case 0:
                                        //Create output file
                                        //Read the name of file
                                        if(output_file != NULL){
                                                printf("Can't open another file until you close the current one.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        file_name = new_file();
                                        output_file = createNewFile_RFF(file_name);
                                        if(output_file != NULL) flag = true; /* File is valid */
                                        break;

                                case 1: // Show data from file
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printAll_RFF(output_file);
                                        break;
                                case 2:// Search by given value
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        field = fields();//Select field to search by
                                        printf("Type the key that will be searched in the file.\n>>>" );
                                        key = readString();
                                        printViaField_RFF(output_file,field,key);
                                        break;
                                case 3: // Show data from a record
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c",&position);
                                        printViaPosition_RFF(output_file,position);
                                        break;
                                case 4: // Show data frome a given record and field
                                        if(flag == false){
                                                printf("Can't operate if there isn't a file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        printf("Type the record number.\n>>>");
                                        scanf("%d%*c", &position);
                                        field = fields(); //Select field to search by
                                        printViaPosField_RFF(output_file,position,field);
                                        break;
                                case 5:// Close file
                                        if(output_file == NULL){
                                                printf("Can't close a unopended file.\nPress ENTER to continue.\n");
                                                getchar();
                                                break;
                                        }
                                        free(output_file);
                                        flag = false; /* Open new file or will give errors */
                                        close = true; //Stop while and exit
                                        break;
                                default:
                                        printf("Option was not selected.\n");
                                        break;
                                }
                                
                        }
                        break;   
                
                case 4: // Exit
                        stop = true;
                        break;
                }                
        }        

       
        return EXIT_SUCCESS;
}
