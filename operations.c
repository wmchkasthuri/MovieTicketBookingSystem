
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"

double calculatePrice(int row, int isStudent, int isSenior, int isGroup);

void viewShowtimes() {
    printf("\n--- Available Movies & Showtimes ---\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("Movie %d: %s\n", i + 1, movies[i].title);
        for (int j = 0; j < NUM_SHOWTIMES; j++) {
            printf("  Showtime %d: %s\n", j + 1, movies[i].showtimes[j].time);
        }
    }
}

void viewSeatMap() {
    viewShowtimes();
    printf("Select Movie (1-%d): ", NUM_MOVIES);
    int m = getValidInt() - 1;
    printf("Select Showtime (1-%d): ", NUM_SHOWTIMES);
    int s = getValidInt() - 1;

    if (m < 0 || m >= NUM_MOVIES || s < 0 || s >= NUM_SHOWTIMES) {
        printf("Error: Invalid Selection!\n");
        return;
    }

    printf("\n--- Seat Map [R=Regular, P=Premium, V=VIP] ---\n      ");
    for (int c = 0; c < COLS; c++) printf("%2d ", c + 1);
    printf("\n");

    for (int r = 0; r < ROWS; r++) {
        char tier = (r < 2) ? 'R' : (r < 4) ? 'P' : 'V';
        printf("Row %c: ", 'A' + r);
        for (int c = 0; c < COLS; c++) {
            if (movies[m].showtimes[s].seats[r][c].isBooked) {
                printf("[X] ");
            } else {
                printf("[%c] ", tier);
            }
        }
        printf("\n");
    }
    printf("([X] = Booked)\n");
}

void bookSeat() {
    viewShowtimes();
    printf("Select Movie (1-%d): ", NUM_MOVIES);
    int m = getValidInt() - 1;
    printf("Select Showtime (1-%d): ", NUM_SHOWTIMES);
    int s = getValidInt() - 1;

    if (m < 0 || m >= NUM_MOVIES || s < 0 || s >= NUM_SHOWTIMES) {
        printf("Error: Invalid Selection!\n");
        return;
    }

    printf("How many seats to book? ");
    int numSeats = getValidInt();
    if (numSeats <= 0) return;

    int isGroup = (numSeats >= 4) ? 1 : 0;
    int selectedRows[50], selectedCols[50];

    for (int i = 0; i < numSeats; i++) {
        char rowChar;
        printf("Enter Row letter for seat %d (A-E): ", i + 1);
        scanf(" %c", &rowChar);
        rowChar = toupper(rowChar);
        int r = rowChar - 'A';

        printf("Enter Column number for seat %d (1-10): ", i + 1);
        int c = getValidInt() - 1;

        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
            printf("Error: Seat out of range!\n");
            return;
        }
        if (movies[m].showtimes[s].seats[r][c].isBooked) {
            printf("Error: Seat %c%d is already taken!\n", rowChar, c + 1);
            return;
        }
        selectedRows[i] = r;
        selectedCols[i] = c;
    }

    char custName[MAX_NAME];
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", custName);
    printf("Is student? (1=Yes, 0=No): ");
    int isStud = getValidInt();
    printf("Is senior citizen? (1=Yes, 0=No): ");
    int isSen = getValidInt();

    double totalCost = 0;
    for (int i = 0; i < numSeats; i++) {
        int r = selectedRows[i];
        int c = selectedCols[i];
        Seat *seat = &movies[m].showtimes[s].seats[r][c];

        seat->isBooked = 1;
        strcpy(seat->customerName, custName);
        seat->isStudent = isStud;
        seat->isSenior = isSen;

        double price = calculatePrice(r, isStud, isSen, isGroup);
        seat->pricePaid = price;
        totalCost += price;

        movies[m].showtimes[s].totalTicketsSold++;
        movies[m].showtimes[s].totalRevenue += price;
    }
    printf("\nBooking Successful! Total Paid: Rs. %.2f\n", totalCost);
}

void cancelBooking() {
    viewShowtimes();
    printf("Select Movie: ");
    int m = getValidInt() - 1;
    printf("Select Showtime: ");
    int s = getValidInt() - 1;

    if (m < 0 || m >= NUM_MOVIES || s < 0 || s >= NUM_SHOWTIMES) return;

    char rowChar;
    printf("Enter Row (A-E): ");
    scanf(" %c", &rowChar);
    int r = toupper(rowChar) - 'A';
    printf("Enter Column (1-10): ");
    int c = getValidInt() - 1;

    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) return;

    Seat *seat = &movies[m].showtimes[s].seats[r][c];
    if (!seat->isBooked) {
        printf("Error: Seat is not booked!\n");
        return;
    }

    movies[m].showtimes[s].totalRevenue -= seat->pricePaid;
    movies[m].showtimes[s].totalTicketsSold--;

    seat->isBooked = 0;
    seat->pricePaid = 0.0;
    strcpy(seat->customerName, "");

    printf("Booking successfully cancelled and refunded.\n");
}

void searchBooking() {
    char name[MAX_NAME];
    printf("Enter Customer Name: ");
    scanf(" %[^\n]", name);
    int found = 0;

    for (int m = 0; m < NUM_MOVIES; m++) {
        for (int s = 0; s < NUM_SHOWTIMES; s++) {
            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    Seat seat = movies[m].showtimes[s].seats[r][c];
                    if (seat.isBooked && strcasecmp(seat.customerName, name) == 0) {
                        printf("Movie: %s | Show: %s | Seat: %c%d | Paid: Rs. %.2f\n",
                               movies[m].title, movies[m].showtimes[s].time, 'A' + r, c + 1, seat.pricePaid);
                        found = 1;
                    }
                }
            }
        }
    }
    if(!found) {
        printf("No bookings found.\n");
    }
}

void revenueReport() {
    double grandRevenue = 0;
    int grandTickets = 0;
    printf("\n================ REVENUE REPORT ================\n");
    for (int m = 0; m < NUM_MOVIES; m++) {
        printf("Movie: %s\n", movies[m].title);
        for (int s = 0; s < NUM_SHOWTIMES; s++) {
            Showtime st = movies[m].showtimes[s];
            printf("  Show: %s -> Tickets: %d | Revenue: Rs. %.2f\n", st.time, st.totalTicketsSold, st.totalRevenue);
            grandRevenue += st.totalRevenue;
            grandTickets += st.totalTicketsSold;
        }
    }
    printf("GRAND TOTAL TICKETS SOLD: %d\n", grandTickets);
    printf("GRAND TOTAL REVENUE: Rs. %.2f\n================================================\n", grandRevenue);
}
