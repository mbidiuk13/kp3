#include <stdio.h>
#include <math.h>
#include "func.h"

int main() {
    printf("This program calculates the K-th root of an X with precision (E).\n");

    double k = 0, x = 0, e = 0, y = 0;
    int n = 0;

    do {
        k = val_double_input("Enter the root degree (k): ");
        if (k < 0) {
            if ((int)k % 2 == 0) {
                x = rootexp_val(1);  //x>0
            } else {
                x = rootexp_val(2);  //x!=0
            }
        } else {
            if ((int)k % 2 == 0) {
                x = rootexp_val(3);  //x>=0
            } else {
                x = val_double_input("Enter the radical (x): ");
            }
        }

        e = set_accuracy();
        y = calculate_root(x, k, e);

        n = fabs(log10(e));
        printf("y = %.*lf (with accuracy = %e)\n", n, y, e);

        printf("\nPress '0' to quit or any other key to continue...\n");
        fflush(stdin);
    } while (getchar() != 48);

    return 0;
}
