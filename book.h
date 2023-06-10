#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[100];
    char ISBN[20];
    int releaseYear;
    int quantity;
} Book;

typedef struct BookNode {
    Book book;
    struct BookNode* next;
} BookNode;

char *fileNameB = "books.txt";

BookNode* createBookNode(Book book) {
    BookNode* newBookNode = (BookNode*)malloc(sizeof(BookNode));
    if (newBookNode != NULL) {
        newBookNode->book = book;
        newBookNode->next = NULL;
    }
    return newBookNode;
}

void insertAtEnd(BookNode** head, Book book) {
    BookNode* newBookNode = createBookNode(book);
    if (newBookNode == NULL) {
        printf("Błąd przy tworzeniu nowego węzła.\n");
        return;
    }
    if (*head == NULL) {
        newBookNode->book.id = 1;
        *head = newBookNode;
    } else {
        BookNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        newBookNode->book.id = temp->book.id + 1;
        temp->next = newBookNode;
    }
}


void removeById(BookNode** head, int id) {
    if (*head == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    BookNode* temp = *head;
    BookNode* prev = NULL;

    if (temp->book.id == id) {
        *head = temp->next;
        free(temp);
        printf("Książka o id %d została usunięta.\n", id);
        return;
    }

    while (temp != NULL && temp->book.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Książka o id %d nie została znaleziona.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Książka o id %d została usunięta.\n", id);
}

void editById(BookNode* head, int id) {
    BookNode* temp = head;

    while (temp != NULL && temp->book.id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Książka o id %d nie została znaleziona.\n", id);
        return;
    }

    printf("Podaj nowe wartości dla książki o id %d:\n", id);
    printf("Tytuł: ");
    scanf("%s", temp->book.title);
    printf("ISBN: ");
    scanf("%s", temp->book.ISBN);
    printf("Rok wydania: ");
    scanf("%d", &temp->book.releaseYear);
    printf("Ilość: ");
    scanf("%d", &temp->book.quantity);

    printf("Książka o id %d została zaktualizowana.\n", id);
}

void displayList(BookNode* head) {
    if (head == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    BookNode* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Tytuł: %s, ISBN: %s, Rok wydania: %d, Ilość: %d\n",
               temp->book.id, temp->book.title, temp->book.ISBN, temp->book.releaseYear, temp->book.quantity);
        temp = temp->next;
    }
}

void saveToFileBooks(BookNode* head, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku do zapisu.\n");
        return;
    }

    BookNode* temp = head;
    while (temp != NULL) {
        fwrite(&(temp->book), sizeof(Book), 1, file);
        temp = temp->next;
    }

    fclose(file);
    printf("Dane zostały zapisane do pliku %s.\n", filename);
}

void loadFromFile(BookNode** head, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Błąd przy otwieraniu pliku do odczytu.\n");
        return;
    }

    Book book;
    while (fread(&book, sizeof(Book), 1, file) == 1) {
        insertAtEnd(head, book);
    }

    fclose(file);
    printf("Dane zostały wczytane z pliku %s.\n", filename);
}

void BooksMenu(){
    BookNode* head = NULL;
    int choice;
    char filename[100];

    do{
        printf("\nMenu:\n");
        printf("1. Dodaj książkę\n");
        printf("2. Usuń książkę\n");
        printf("3. Edytuj książkę\n");
        printf("4. Wyświetl książki\n");
        printf("5. Zapisz do pliku\n");
        printf("6. Wczytaj z pliku\n");
        printf("0. Wyjście\n");
        printf("Wybierz opcję: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Book book;
                
                printf("Podaj tytuł książki: ");
                scanf("%s", book.title);
                printf("Podaj ISBN książki: ");
                scanf("%s", book.ISBN);
                printf("Podaj rok wydania książki: ");
                scanf("%d", &book.releaseYear);
                printf("Podaj ilość książek: ");
                scanf("%d", &book.quantity);

                insertAtEnd(&head, book);
                printf("Książka została dodana.\n");
                break;
            }
            case 2: {
                int id;
                printf("Podaj id książki do usunięcia: ");
                scanf("%d", &id);
                removeById(&head, id);
                break;
            }
            case 3: {
                int id;
                printf("Podaj id książki do edycji: ");
                scanf("%d", &id);
                editById(head, id);
                break;
            }
            case 4:
                displayList(head);
                break;
            case 5:
           
                saveToFileBooks(head, fileNameB);
                break;
            case 6:
               
                loadFromFile(&head, fileNameB);
                break;
            case 0:
                printf("Cofam.\n");
                break;
            default:
                printf("Nieprawidłowa opcja. Spróbuj ponownie.\n");
        }
    }
    while(choice!=0);
}

