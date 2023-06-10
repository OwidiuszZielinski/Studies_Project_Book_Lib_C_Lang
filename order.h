#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_NAME_LENGTH 50
char filename[] = "orders.bin";

typedef struct {
    int id;
    int clientId;
    int bookId;
    time_t creationTime;
} Order;

typedef struct OrderNode {
    Order order;
    struct OrderNode* next;
} OrderNode;


void insertOrder(OrderNode** head, Order order) {
    OrderNode* newOrderNode = (OrderNode*)malloc(sizeof(OrderNode));
    if (newOrderNode == NULL) {
        printf("Błąd przy alokacji pamięci.\n");
        return;
    }
    newOrderNode->order = order;
    newOrderNode->next = NULL;

    if (*head == NULL) {
        *head = newOrderNode;
    } else {
        OrderNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newOrderNode;
    }

    printf("Zamówienie dodane.\n");
}

void removeOrder(OrderNode** head, int id) {
    if (*head == NULL) {
        printf("Lista zamówień jest pusta.\n");
        return;
    }

    OrderNode* current = *head;
    OrderNode* previous = NULL;

    while (current != NULL) {
        if (current->order.id == id) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            printf("Zamówienie o ID %d zostało usunięte.\n", id);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Nie znaleziono zamówienia o ID %d.\n", id);
}

void editOrder(OrderNode* head, int id) {
    if (head == NULL) {
        printf("Lista zamówień jest pusta.\n");
        return;
    }

    OrderNode* current = head;

    while (current != NULL) {
        if (current->order.id == id) {
            printf("Podaj nowego klienta: ");
            scanf("%d", &current->order.clientId);
            printf("Podaj nową książkę: ");
            scanf("%d", &current->order.bookId);
            printf("Zamówienie o ID %d zostało zaktualizowane.\n", id);
            return;
        }

        current = current->next;
    }

    printf("Nie znaleziono zamówienia o ID %d.\n", id);
}



 void displayOrders(OrderNode* head) {
    if (head == NULL) {
        printf("Lista zamówień jest pusta.\n");
        return;
    }

    OrderNode* current = head;

    printf("+--------------------------------------------------------------------------------------+\n");
    printf("|                                        Zamówienia                                    |\n");
    printf("+----------------------+-----------------+-----------------+---------------------------+\n");
    printf("|          ID          |     Klient      |     Książka     |       Czas utworzenia     |\n");
    printf("+----------------------+-----------------+-----------------+---------------------------+\n");

    while (current != NULL) {
        printf("| %-20d | %-15d | %-15d | %s", current->order.id, current->order.clientId, current->order.bookId, ctime(&current->order.creationTime));
        current = current->next;
    }

    printf("+----------------------+-----------------+-----------------+---------------------------+\n");
 
}


void saveOrdersToFile(OrderNode* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku %s.\n", filename);
        return;
    }

    OrderNode* current = head;

    while (current != NULL) {
        fwrite(&(current->order), sizeof(Order), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Zamówienia zostały zapisane do pliku %s.\n", filename);
}

void loadOrdersFromFile(OrderNode** head, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku %s.\n", filename);
        return;
    }

    Order order;

    while (fread(&order, sizeof(Order), 1, file)) {
        insertOrder(head, order);
    }

    fclose(file);
    printf("Zamówienia zostały wczytane z pliku %s.\n", filename);
}


void OrdersMenu()
{
    OrderNode* orders = NULL;
    

    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Dodaj zamówienie\n");
        printf("2. Usuń zamówienie\n");
        printf("3. Edytuj zamówienie\n");
        printf("4. Wyświetl zamówienia\n");
        printf("5. Zapisz zamówienia do pliku\n");
        printf("6. Wczytaj zamówienia z pliku\n");
        printf("0. Cofnij\n");
        printf("Wybierz opcję: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                Order order;
                printf("Podaj id klienta: ");
                scanf("%d", &order.clientId);
                printf("Podaj id książki: ");
                scanf("%d", &order.bookId);
                order.id = time(NULL); // Unikalne id oparte na czasie
                order.creationTime = time(NULL); // Czas utworzenia zamówienia

                insertOrder(&orders, order);
                break;
            }
            case 2: {
                int id;
                printf("Podaj ID zamówienia do usunięcia: ");
                scanf("%d", &id);
                removeOrder(&orders, id);
                break;
            }
            case 3: {
                int id;
                printf("Podaj ID zamówienia do edycji: ");
                scanf("%d", &id);
                editOrder(orders, id);
                break;
            }
            case 4:
                displayOrders(orders);
                break;
            case 5:
                saveOrdersToFile(orders, filename);
                break;
            case 6:
                loadOrdersFromFile(&orders, filename);
                break;
            case 0:
                printf("Cofam.\n");
                break;
            default:
                printf("Nieprawidłowa opcja. Wybierz ponownie.\n");
        }
    } while (option != 0);
}


