
#ifndef STRUCTURES_H
#define STRUCTURES_H

#define ROWS 5
#define COLS 10
#define NUM_MOVIES 3
#define NUM_SHOWTIMES 2
#define MAX_NAME 50

typedef struct {
    int isBooked;
    char customerName[MAX_NAME];
    double pricePaid;
    int isStudent;
    int isSenior;
} Seat;

typedef struct {
    char time[10];
    Seat seats[ROWS][COLS];
    int totalTicketsSold;
    double totalRevenue;
} Showtime;

typedef struct {
    char title[MAX_NAME];
    Showtime showtimes[NUM_SHOWTIMES];
} Movie;

extern Movie movies[NUM_MOVIES];

int getValidInt();

#endif
