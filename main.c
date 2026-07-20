
#include <stdio.h>
#include <string.h>
#include "structures.h"

Movie movies[NUM_MOVIES];

void viewShowtimes();
void viewSeatMap();
void bookSeat();
void cancelBooking();
void searchBooking();
void revenueReport();

void initData() {
    strcpy(movies[0].title, "Avatar 3");
    strcpy(movies[0].showtimes[0].time, "10:00 AM");
    strcpy(movies[0].showtimes[1].time, "02:00 PM");

    strcpy(movies[1].title, "Superman");
    strcpy(movies[1].showtimes[0].time, "01:00 PM");
    strcpy(movies[1].showtimes[1].time, "06:00 PM");

    strcpy(movies[2].title, "Avengers: Doomsday");
    strcpy(movies[2].showtimes[0].time, "11:30 AM");
    strcpy(movies[2].showtimes[1].time, "07:30 PM");
}

int getValidInt() {
    int num;
    char ch;
    while (scanf("%d", &num) != 1) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid input! Enter a number: ");
    }
    return num;
}

int main() {
    initData();
    int choice;

    while (1) {
        printf("\n--- Movie Ticket Booking System ---\n");
        printf("1. View Showtimes\n");
        printf("2. View Seat Map\n");
        printf("3. Book a Seat\n");
        printf("4. Cancel a Booking\n");
        printf("5. Search Booking\n");
        printf("6. View Revenue Report\n");
        printf("7. Exit\n");
        printf("Enter choice: ");

        choice = getValidInt();

        switch (choice) {
            case 1: viewShowtimes(); break;
            case 2: viewSeatMap(); break;
            case 3: bookSeat(); break;
            case 4: cancelBooking(); break;
            case 5: searchBooking(); break;
            case 6: revenueReport(); break;
            case 7: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
