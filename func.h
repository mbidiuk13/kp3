#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <math.h>

double calculate_root(double root_exp, double root_value, double accuracy) {
    double y = 1.0;
    double delta = 1.0;

    if (root_exp == 0) {
        return 0.0;
    }

    do {
        if (root_value < 0) {
            root_value = -root_value;
            root_exp = 1.0 / root_exp;
        }
        delta = (1.0 / root_value) * (root_exp / pow(y, root_value - 1.0) - y);
        y += delta;
    } while (fabs(delta) >= accuracy);
    return y;
}

int val_int_input(const char *prompt) {
    int value = 0;
    int input = 0;
    do {
        printf("%s", prompt);
        input = scanf("%d", &value);
        if (input != 1 || value == 0) {
            printf("Invalid input. Please enter a valid integer.\n");
            value = 0;
        }
        fflush(stdin);
    } while (input != 1 || value == 0);
    return value;
}

double val_double_input(const char *prompt) {
    double value = 0;
    int input = 0;
    do {
        printf("%s", prompt);
        input = scanf("%lf", &value);
        if (input != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            value = 0;
        }
        fflush(stdin);
    } while (input != 1);
    return value;
}

double validate_x(const char* prompt, const char* error_msg, int (*condition)(double)) {
    double value = 0;
    do {
        value = val_double_input(prompt);
        if (!condition(value)) {
            printf("%s\n", error_msg);
        }
        fflush(stdin);
    } while (!condition(value));
    return value;
}

char greater_than_zero(double value) {
    return value > 0;
}

char not_zero(double value) {
    return value != 0;
}

char not_negative(double value) {
    return value >= 0;
}

char any_number(double value) {
    return 1;
}

double rootexp_val(int var) {
    switch (var) {
        case 1:
            return validate_x("Enter x (x > 0):\n", "Invalid input. Enter a number > 0.", greater_than_zero);
        case 2:
            return validate_x("Enter x (x != 0):\n", "Invalid input. Enter a non-zero number.", not_zero);
        case 3:
            return validate_x("Enter x (x >= 0):\n", "Invalid input. Enter a number >= 0.", not_negative);
        default:
            return validate_x("Enter x:\n", "Invalid input. Enter a valid number.", any_number);
    }
}

double set_accuracy() {
    unsigned choice = 0;
    double accuracy = 0;

    do {
        printf("Choose the accuracy type:\n");
        printf("1. Number of decimal places (e.g., 3)\n");
        printf("2. Decimal number (e.g., 0.001)\n");
        printf("3. Exponential form (e.g., 1e-3)\n");
        printf("Enter your choice (1-3): ");
        choice = abs(val_int_input(""));

        switch (choice) {
            case 1: {
                int decimal_places = 0;
                do {
                    decimal_places = abs(val_int_input("Enter the accuracy (1-12 decimal places):\n"));
                    if (decimal_places < 1 || decimal_places > 12) {
                        printf("Invalid input. Please enter a value between 1 and 12.\n");
                    }
                } while (decimal_places < 1 || decimal_places > 12);
                accuracy = pow(10.0, -decimal_places);
                break;
            }
            case 2: {
                do {
                    accuracy = val_double_input("Enter the accuracy as a decimal (1e-12 <= accuracy <= 0.1):\n");
                    if (accuracy < 1e-12 || accuracy > 0.1) {
                        printf("Invalid input. Please enter a value between 1e-12 and 0.1.\n");
                    }
                } while (accuracy < 1e-12 || accuracy > 0.1);
                break;
            }
            case 3: {
                do {
                    accuracy = val_double_input("Enter the accuracy in exponential form (range: 1e-12 to 1e-1):\n");
                    if (accuracy < 1e-12 || accuracy > 1e-1) {
                        printf("Invalid input. Please enter a value between 1e-12 and 1e-1.\n");
                    }
                } while (accuracy < 1e-12 || accuracy > 1e-1);
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
            fflush(stdin);
        }
    } while (choice < 1 || choice > 3);

    return accuracy;
}

#endif // FUNC_H
