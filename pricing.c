
#include <stdio.h>
#include "structures.h"

double calculatePrice(int row, int isStudent, int isSenior, int isGroup, int foodChoice) {
    double basePrice = 0.0;

    // Base pricing by row tier (Rows A-B: 500, C-D: 750, E: 1000)
    if (row == 0 || row == 1) {
        basePrice = 500.0;
    } else if (row == 2 || row == 3) {
        basePrice = 750.0;
    } else if (row == 4) {
        basePrice = 1000.0;
    }

    // Category discount (Student: 10%, Senior: 20%)
    double discount = 0.0;
    if (isStudent) {
        discount = 0.10;
    } else if (isSenior) {
        discount = 0.20;
    }

    double finalPrice = basePrice * (1.0 - discount);

    // Group discount (10% off base ticket price, stacks with student/senior)
    if (isGroup) {
        finalPrice = finalPrice * 0.90;
    }

    // Snack combo cost
    double foodCost = 0.0;
    if (foodChoice == 1) {
        foodCost = 300.0;
    } else if (foodChoice == 2) {
        foodCost = 500.0; // FIX: Changed '==' comparison operator to '=' assignment operator
    }

    return finalPrice + foodCost;
}
