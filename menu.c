#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <rff.h>
#include <rsi.h>
#include <filestrings.h>


//Function to read file from user
char *new_file(){
        char *name;
        printf("Write file name => " );
        name = readString();
        return name;
}
//Function to select the way to work whit registers
int field_type(){
        int option;
        printf("Select the type of file organization\n ");
        printf("1 - Records with variable sizes and indicators\n");
        printf("2 - Reords with variable sizes and field delimiters\n");
        printf("3 - Records with variable sizes and fixed number in field \n");
        scanf("%d%*c", &option);
        return option;

}
//Function to display the menu for the user to select the task to performe
int menu(){
        int option;
        printf("Select the operation to performe\n");
        printf("1 - Display data from file\n");
        printf("2 - Display data by criteria (Domain)\n");
        printf("3 - Display data from specific register\n");
        printf("4 - Display data from specific register and specific field\n");
        printf("5 - Exit\n");
        scanf("%d%*c",&option);
        return option;
}
//Function to display the diferents field that exist for the case 5
int campos(){
        int campo;
        printf("1 - Domain\n");
        printf("2 - Document\n");
        printf("3 - Name\n");
        printf("4 - Uf\n");
        printf("5 - City\n");
        printf("6 - Date of register\n");
        printf("7 - Date of Update\n");
        printf("8 - Ticket\n");
        scanf("%d%*c",&campo );
        return campo;
}


int main (){

        char *file_name, *output_file;
        char * domain;
        bool stop = false;
        int menu_op, field, position, campo;

        file_name = new_file();


        field = field_type();


        switch (field) {



        case 1: // RSI
                output_file = createNewFile_RSI(file_name);
                menu_op = menu();
                switch (menu_op) {
                case 1: // Show data from file
                        printAll_RSI(output_file);
                        break;
                case 2:// Search by given value
                        campo = campos();        //Select field to search by
                        printf("Value to search => " );
                        domain = readString();
                        printViaField_RSI(output_file,campo,domain);
                        break;

                case 3: // Show data from a register
                        printf("Register number => ");
                        scanf("%d",&position);
                        printViaPosition_RSI(output_file,position);
                        break;

                case 4: // Show data frome a given register and field
                        printf("Register number =>");
                        scanf("%d", &position);
                        campo = campos(); //Select field to search by
                        printViaPosField_RSI(output_file,position,campo);
                        break;

                case 5:// Exit program
                        stop = true; //Stop while and exit
                        break;
                default:
                        printf("Option was not selected");
                }

                break;

        case 2: //RDR
                printf("\n");
                break;

        case 3: //RFF
                output_file = createNewFile_RFF(file_name);
                menu_op = menu();
                switch (menu_op) {
                case 1:         // Show data from file
                        printAll_RFF(output_file);
                        break;

                case 2:// Search by given value
                        campo = campos();        //Select field to search by
                        printf("Value to search => " );
                        domain = readString();
                        printViaField_RFF(output_file,campo,domain);
                        break;

                case 3:         // Show data from a register
                        printf("Register number => ");
                        scanf("%d",&position);
                        printViaPosition_RFF(output_file,position);
                        break;

                case 4:        // Show data frome a given register and field
                        printf("Register number =>");
                        scanf("%d", &position);
                        int campo = campos();        //Select field to search by

                        printViaPosField_RFF(output_file,position,campo);

                        break;

                case 5:// Exit program
                        stop = true;        //Stop while and exit
                        break;

                default:
                        printf("Option was not selected");
                }
                break;

        }






        return EXIT_SUCCESS;
}
