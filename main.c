#include <stdio.h>
#include "client.h"


void clientsMenu(){
    int choice;
    do {
        printf("Wybierz operacje:\n");
        printf("1. Dodaj nowego klienta\n");
        printf("2. Usuń klienta\n");
        printf("3. Edytuj\n");
        printf("4. Wczytaj istniejących \n");
        printf("5. Cofnij \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                Queue P, K;
                P = NULL;
                readFromFile(&P, &K, fileNameP);
                addClients(&P, &K);
                printf("\nWprowadzone dane:\n");
                showQueue(P);
                saveToFile(P, fileNameP);
                break;
            case 2:
                printf("Performing subtraction...\n");
                // Call function to perform subtraction here
                break;
            case 3:
                printf("Performing multiplication...\n");
                // Call function to perform multiplication here
                break;
            case 4:
                printf("Performing division...\n");
                // Call function to perform division here
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while(choice != 5);


}


int main()
{

    int choice;
    do {
        printf("Wybierz operacje:\n");
        printf("1. Klienci\n");
        printf("2. Książki\n");
        printf("3. Zamówienia\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                clientsMenu();
                break;
            case 2:
                printf("Performing subtraction...\n");
                // Call function to perform subtraction here
                break;
            case 3:
                printf("Performing multiplication...\n");
                // Call function to perform multiplication here
                break;
            case 4:
                printf("Performing division...\n");
                // Call function to perform division here
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while(choice != 4);
    

    

    return 0;
}