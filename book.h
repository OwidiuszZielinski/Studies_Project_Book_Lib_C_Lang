#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE 25

typedef struct
{
    char title[SIZE], isbn[SIZE];
    int quantity, year;

} Book;

typedef struct NodeBook
{
    Book Book;
    struct NodeBook *next;
} NodeBook;

typedef NodeBook *QueueBook;

Book newBook()
{
    Book x;
    printf("Tytuł: ");
    scanf("%s", x.title);
    printf("13 - Liczbowy ISBN : \n");
    scanf("%s", x.isbn);
    printf("Rok: \n");
    scanf("%d", &x.year);
    printf("Ilość \n ");
    scanf("%d", &x.quantity);

   

    return x;
}

void showBook(Book x)
{
    printf("%s %s %d %d r.", x.isbn, x.title, x.quantity, x.year);
}

void addToQueueBookBook(QueueBook *head, QueueBook *tail, Book x)
{
    QueueBook Q;
    Q = (NodeBook *)malloc(sizeof(NodeBook));
    Q->Book = x;
    Q->next = NULL;
    if ((*head) == NULL)
        (*head) = Q;
    else
        (*tail)->next = Q;
    (*tail) = Q;
}

void deleteFromQueueBook(QueueBook *head, Book *x)
{
    QueueBook Q;
    if ((*head) == NULL)
        return;
    (*x) = (*head)->Book;
    Q = (*head);
    (*head) = (*head)->next;
    free(Q);
}
void addBooks(QueueBook *head, QueueBook *tail)
{
    char z;
    printf("Czy chcesz dodac nową ksiązke? (T/N): ");
    do
    {
        z = toupper(getchar());
    } while (z != 'T' && z != 'N');
    printf("%c\n", z);
    if (z == 'N')
        return;
    do
    {
        printf("\nWprowadz dane ksiązki: \n");

        addToQueueBookBook(&(*head), &(*tail), newBook());
        printf("Czy chcesz dodac kolejną ksiązke? (T/N):");
        do
        {
            z = toupper(getchar());
        } while (z != 'T' && z != 'N');
        printf("%c\n", z);
    } while (z != 'N');
}
Book deletedFromQueueBookBook(QueueBook *head)
{
    QueueBook Q;
    Book x;
    if (*head == NULL)
        return x;
    x = (*head)->Book;
    Q = (*head);
    (*head) = Q;
    free(Q);
    return x;
}
void showQueueBookBook(QueueBook P)
{
    while (P != NULL)
    {
        showBook(P->Book);
        P = P->next;
    }
}
int saveToFileBook(QueueBook Q, char *filetitle)
{
    FILE *file;
    file = fopen(filetitle, "w");
    if (file == NULL)
        return -1;

    while (Q != NULL)
    {
        fprintf(file, "%s\n%s\n%d\n%d", Q->Book.isbn, Q->Book.title, Q->Book.year,Q->Book.quantity);
        

        Q = Q->next;
    }
    fclose(file);
    return 0;
}

int readFromFileBook(QueueBook *head, QueueBook *tail, char *filetitle)
{
    FILE *file;
    Book x;
    int temp;
    file = fopen(filetitle, "r");
    if (file == NULL)
        return -1;

    while (!feof(file))
    {

        fscanf(file, "%s\n", x.isbn);
        fscanf(file, "%s\n", x.title);
        fscanf(file, "%d\n", &x.year);
        fscanf(file, "%d\n", &x.quantity);
        addToQueueBookBook(&(*head), &(*tail), x);
    }

    fclose(file);
    return 0;
}

Book newBook();
Book usnietyZKolejkiBook(QueueBook *head);
char *filetitleP = "Books.txt";

void BooksMenu()
{
    int choice;
    QueueBook P, K;
    do
    {
        printf("Wybierz operacje:\n");
        printf("1. Dodaj nową ksiązke\n");
        printf("2. Usuń ksiazke\n");
        printf("3. Edytuj\n");
        printf("4. Wczytaj istniejące \n");
        printf("5. Cofnij \n");
        printf("Twoj wybor: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            P = NULL;
            readFromFileBook(&P, &K, filetitleP);
            addBooks(&P, &K);
            printf("\nWprowadzone dane:\n");
            showQueueBookBook(P);
            saveToFileBook(P, filetitleP);
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
