#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE 25
typedef struct
{
    int year, month, day;
} Date;
typedef struct
{
    char street[SIZE], housenumber[10], zip_code[SIZE], city[SIZE];

} Address;

typedef struct Client
{

    char name[SIZE], surname[SIZE], number[SIZE];
    Date date;
    Address address;
    int id;
} Client;

typedef struct ClientNode {
    Client client;
    struct ClientNode* next;
} ClientNode;


char *fileNameP = "clients.txt";



ClientNode *createClientNode(Client client)
{
    ClientNode *newClientNode = (ClientNode *)malloc(sizeof(ClientNode));
    if (newClientNode != NULL)
    {
        newClientNode->client = client;
        newClientNode->next = NULL;
    }
    return newClientNode;
}

void insertClient(ClientNode **head, Client client)
{
    ClientNode *newClientNode = createClientNode(client);
    if (newClientNode == NULL)
    {
        printf("Błąd przy tworzeniu nowego węzła.\n");
        return;
    }
    if (*head == NULL)
    {
        newClientNode->client.id = 1;
        *head = newClientNode;
    }
    else
    {
        ClientNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        newClientNode->client.id = temp->client.id + 1;
        temp->next = newClientNode;
    }
}

void removeClient(ClientNode **head, int id)
{
    if (*head == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }

    ClientNode *temp = *head;
    ClientNode *prev = NULL;

    if (temp->client.id == id)
    {
        *head = temp->next;
        free(temp);
        printf("Klient o id %d został usunięty.\n", id);
        return;
    }

    while (temp != NULL && temp->client.id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Klient o id %d nie został znaleziony.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Klient o id %d został usunięty.\n", id);
}

void editClient(ClientNode *head, int id)
{
    ClientNode *temp = head;

    while (temp != NULL && temp->client.id != id)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Klient o id %d nie został znaleziony.\n", id);
        return;
    }

    printf("Podaj nowe wartości dla klienta o id %d:\n", id);
    printf("Nazwisko: ");
    scanf("%s", temp->client.surname);
    printf("Imie: ");
    scanf("%s", temp->client.name);
    printf("Numer telefonu: ");
    scanf("%s", temp->client.number);
    printf("\nWprowadz Adres:\n ");
    printf("Ulica: ");
    scanf("%s", temp->client.address.street);
    printf("Numer Domu: ");
    scanf("%s", temp->client.address.housenumber);
    printf("Kod poczotowy: ");
    scanf("%s", temp->client.address.zip_code);
    printf("Miasto: ");
    scanf("%s", temp->client.address.city);
    printf("Data urodzenia (dzien miesiac rok): ");
    scanf("%d %d %d", &temp->client.date.day, &temp->client.date.month, &temp->client.date.year);

    printf("Klient o id %d została zaktualizowany.\n", id);
}

void displayClients(ClientNode *head)
{
    if (head == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }

    ClientNode *temp = head;
    while (temp != NULL)
    {
        printf("%d %s %s %02d.%02d.%4d r.",temp->client.id, temp->client.surname, temp->client.name, temp->client.date.day, temp->client.date.month, temp->client.date.year);
        printf("\nAdres: \n");
        printf("%s %s %s %s\n", temp->client.address.street,temp->client.address.housenumber,temp->client.address.zip_code,temp->client.address.city);
        temp = temp->next;
    }
}

void saveToFileClients(ClientNode *head, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Błąd przy otwieraniu pliku do zapisu.\n");
        return;
    }

    ClientNode *temp = head;
    while (temp != NULL)
    {
        fwrite(&(temp->client), sizeof(Client), 1, file);
        temp = temp->next;
    }

    fclose(file);
    printf("Dane zostały zapisane do pliku %s.\n", filename);
}

void loadClientsFromFile(ClientNode **head, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Błąd przy otwieraniu pliku do odczytu.\n");
        return;
    }

    Client Client;
    while (fread(&Client, sizeof(Client), 1, file) == 1)
    {
        insertClient(head, Client);
    }

    fclose(file);
    printf("Dane zostały wczytane z pliku %s.\n", filename);
}

void ClientsMenu()
{
    ClientNode *head = NULL;
    int choice;
    char filename[100];

    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Dodaj klienta\n");
        printf("2. Usuń klienta\n");
        printf("3. Edytuj klienta\n");
        printf("4. Wyświetl klientów\n");
        printf("5. Zapisz do pliku\n");
        printf("6. Wczytaj z pliku\n");
        printf("0. Cofnij\n");
        printf("Wybierz opcję: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            Client x;

            printf("Nazwisko: ");
            scanf("%s", x.surname);
            printf("Imie: ");
            scanf("%s", x.name);
            printf("Numer telefonu: ");
            scanf("%s", x.number);
            printf("\nWprowadz Adres:\n ");
            printf("Ulica: ");
            scanf("%s", x.address.street);
            printf("Numer Domu: ");
            scanf("%s", x.address.housenumber);
            printf("Kod poczotowy: ");
            scanf("%s", x.address.zip_code);
            printf("Miasto: ");
            scanf("%s", x.address.city);
            printf("Data urodzenia (dzien miesiac rok): ");
            scanf("%d %d %d", &x.date.day, &x.date.month, &x.date.year);

            insertClient(&head, x);
            printf("Klient został dodany.\n");
            break;
        }
        case 2:
        {
            int id;
            printf("Podaj id klienta do usunięcia: ");
            scanf("%d", &id);
            removeClient(&head, id);
            break;
        }
        case 3:
        {
            int id;
            printf("Podaj id klienta do edycji: ");
            scanf("%d", &id);
            editClient(head, id);
            break;
        }
        case 4:
            displayClients(head);
            break;
        case 5:

            saveToFileClients(head, fileNameP);
            break;
        case 6:
            loadClientsFromFile(&head, fileNameP);
            break;
        case 0:
            printf("Cofam.\n");
            break;
        default:
            printf("Nieprawidłowa opcja. Spróbuj ponownie.\n");
        }
    
    }
    while(choice != 0);
    
}
