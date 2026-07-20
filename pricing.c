
#include <stdio.h>
#include "structures.h"

double calculatePrice(int row, int isStudent, int isSenior, int isGroup) {
    double basePrice = 0;

    if (row == 0 || row == 1) {
        basePrice = 500.0;
    } else if (row == 2 || row == 3) {
        basePrice = 750.0;
    } else if (row == 4) {
        basePrice = 1000.0;
    }

    double discount = 0.0;
    if (isStudent) {
        discount = 0.10;
    } else if (isSenior) {
        discount = 0.20;
    }

    double finalPrice = basePrice * (1.0 - discount);

    if (isGroup) {
        finalPrice = finalPrice * 0.90;
    }

    return finalPrice;
}
