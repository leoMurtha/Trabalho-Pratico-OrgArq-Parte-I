#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <rff.h>
#include <rsi.h>
#include <filestrings.h>


//Function to read file from user
char new_file(){
        char name;
        printf("Write file name => " );
        name = getchar();
        return name;
}
//Function to select the way to work whit registers
int field_type(){
        int option;
        printf("Select the type of file organization ");
        printf("1 - Records with variable sizes and indicators");
        printf("2 - Reords with variable sizes and field delimiters");
        printf("3 - Records with variable sizes and fixed number in field ");
        scanf("%d", option);
        return option;

}
//Function to display the menu for the user to select the task to performe
int menu(){
        int option;
        printf("Select the operation to performe");
        printf("1 - Display data from file");
        printf("2 - Display data by criteria (Domain)");
        printf("3 - Display data from specific register");
        printf("4 - Display data from specific register and specific field");
        printf("5 - Exit");
        scanf("%d",option);
        return option;
}
//Function to display the diferents field that exist for the case 5
int campos(){
        int campo;
        printf("1 - Domain ");
        printf("2 - Document ");
        printf("3 - Name ");
        printf("4 - Uf ");
        printf("5 - City ");
        printf("6 - Date of register ");
        printf("7 - Date of Update ");
        printf("8 - Ticket ");
        scanf("%d",campo );
        return campo;
}


int main (){

  printf("Hola\n" );

        char file_name, output_file;
        bool stop = false;
        int menu, field;

        field = field_type();

        file_name = new_file();



        while (!stop) {

                menu = menu()
                       switch (menu) {
                case 1: // Show data from file


                        break;

                case 2:// Search by given domain
                        printf("Name of domain");
                        scanf("%s",/*variabel */ );


                        break;

                case 3: // Show data from a registerç
                        printf("Register number");
                        scanf("%d", /*variabel */);

                        break;

                case 4:// Show data frome a given register and field
                        printf("Register number");
                        scanf("%d", /*variabel */);
                        int campo = campos();//Select field to search by

                        break;

                case 5:// Exit program
                        stop = true;//Stop while and exit
                        break;

                default:
                        printf("Option was not selected");
                        break;
                }
        }

        return EXIT_SUCCESS;
}
