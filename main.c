#include <stdio.h>
#include "client.h"
#include "book.h"




int main()
{
    Client client;
    int choice;
    do {
        printf("Wybierz operacje:\n");
        printf("1. Klienci\n");
        printf("2. Książki\n");
        printf("3. Zamówienia\n");
        printf("4. Wyjście\n");
        printf("Twoj wybor: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                clientsMenu();
                break;
            case 2:
                BooksMenu();
                break;
            case 3:
                
                break;
            case 4:
                exit(0);
                break;
           
            default:
                printf("Zły wybor\n");
                break;
        }
    } while(choice != 4);

    return 0;
}