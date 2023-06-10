#include <stdio.h>
#include <string.h>

void printLineSeparator(int length) {
    for (int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}

void printFrame(int length) {
    printf("+");
    for (int i = 0; i < length - 2; i++) {
        printf("-");
    }
    printf("+\n");
}

int main() {
    // Order details
    char customerName[50];
    int orderNumber,time;
    float orderTotal;

    // Getting input from the user
    printf("Dane klienta ");
    fgets(customerName, sizeof(customerName), stdin);
    printf("Numer zamowienia: ");
    scanf("%d", &orderNumber);
    printf("Kwota: ");
    scanf("%f", &orderTotal);
      printf("Ilość dni: ");
    scanf("%d", &time);

    // Clearing the input buffer
    while (getchar() != '\n')
        ;

    // Displaying order details with frame and line separators
    printf("\n");
    int frameLength = strlen(customerName) + 25;
    printFrame(frameLength);
    printf("| Dane wypozyczenia: |\n");
    printFrame(frameLength);
    printf("| Dane klienta : %s", customerName);
    printLineSeparator(frameLength);
    printf("| Numer wypozyczenia : %d\n", orderNumber);
    printLineSeparator(frameLength);
    printf("| Kwota : PLN %.2f\n", orderTotal);
    printFrame(frameLength);
    printf("| Czas: %d dni\n", time);
    printFrame(frameLength);

    return 0;
}
