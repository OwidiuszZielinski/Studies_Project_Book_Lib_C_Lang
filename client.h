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
    char street[SIZE],housenumber[10],zip_code[SIZE],city[SIZE];
    
} Address;


typedef struct
{
    char name[SIZE], surname[SIZE], number[SIZE];
    Date date;
    Address address;
} Client;

typedef struct Node
{
    Client client;
    struct Node *next;
} Node;


typedef Node *Queue;

Client newClient();
Client usnietyZKolejki(Queue *head);
char *fileNameP = "clients.txt";


Client newClient()
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
    return x;
}


void showClient(Client x)
{
    printf("%s %s %02d.%02d.%4d r.", x.surname, x.name, x.date.day, x.date.month, x.date.year);
    printf("\nAdres: \n");
    printf("%s %s %s %s", x.address.street,x.address.housenumber,x.address.zip_code,x.address.city);
}

void addToQueue(Queue *head, Queue *tail, Client x)
{
    Queue Q;
    Q = (Node *)malloc(sizeof(Node));
    Q->client = x;
    Q->next = NULL;
    if ((*head) == NULL)
        (*head) = Q;
    else
        (*tail)->next = Q;
        (*tail) = Q;
}

void deleteFromQueue(Queue *head, Client *x)
{
    Queue Q;
    if ((*head) == NULL)
        return;
    (*x) = (*head)->client;
    Q = (*head);
    (*head) = (*head)->next;
    free(Q);
}
void addClients(Queue *head, Queue *tail)
{
    char z;
    printf("Czy chcesz dodac nowego klienta? (T/N): ");
    do
    {
        z = toupper(getchar());
    } while (z != 'T' && z != 'N');
    printf("%c\n", z);
    if (z == 'N')
        return;
    do
    {
        printf("\nWprowadz dane klienta: \n");

        addToQueue(&(*head), &(*tail), newClient());
        printf("Czy chcesz dodac kolejnego klienta? (T/N):");
        do
        {
            z = toupper(getchar());
        } while (z != 'T' && z != 'N');
        printf("%c\n", z);
    } while (z != 'N');
}
Client deletedFromQueue(Queue *head)
{
    Queue Q;
    Client x;
    if (*head == NULL)
        return x;
    x = (*head)->client;
    Q = (*head);
    (*head) = Q;
    free(Q);
    return x;
}
void showQueue(Queue P)
{
    while (P != NULL)
    {
        showClient(P->client);
        P = P->next;
    }
}
int saveToFile(Queue Q, char *fileName)
{
    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL)
        return -1;

    while (Q != NULL)
    {
        fprintf(file, "%s\n%s\n%s\n", Q->client.surname, Q->client.name, Q->client.number);
        fprintf(file, "%s\n%s\n%s\n", Q->client.address.street, Q->client.address.zip_code, Q->client.address.city);
        fprintf(file, "%d %d %d\n", Q->client.date.day, Q->client.date.month, Q->client.date.year);

        Q = Q->next;
    }
    fclose(file);
    return 0;
}

int readFromFile(Queue *head, Queue *tail, char *fileName)
{
    FILE *file;
    Client x;
    int temp;
    file = fopen(fileName, "r");
    if (file == NULL)
        return -1;

    while (!feof(file))
    {

        fscanf(file, "%s\n", x.surname);
        fscanf(file, "%s\n", x.name);
        fscanf(file, "%s\n", x.number);
        fscanf(file, "%s\n", x.address.street);
        fscanf(file, "%s\n", x.address.zip_code);
        fscanf(file, "%s\n", x.address.city);
        fscanf(file, "%d %d %d\n", &(x.date.day), &(x.date.month), &(x.date.year));
        addToQueue(&(*head), &(*tail), x);
    }

    fclose(file);
    return 0;
}


void clientsMenu()
{
    int choice;
    Queue P, K;
    do
    {
        printf("Wybierz operacje:\n");
        printf("1. Dodaj klienta\n");
        printf("2. Usuń klienta\n");
        printf("3. Edytuj\n");
        printf("4. Wczytaj istniejących \n");
        printf("5. Cofnij \n");
        printf("Twoj wybor: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            P = NULL;
            readFromFile(&P, &K, fileNameP);
            addClients(&P, &K);
            printf("\nWprowadzone dane:\n");
            showQueue(P);
            saveToFile(P, fileNameP);
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            break;
        default:
            printf("Nieprawidłowy wybor.\n");
            break;
        }
    } while (choice != 5);
}

