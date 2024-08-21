#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int solve_square(const double coeff_a, const double coeff_b, const double coeff_c, double* root1, double* root2);
void input(double* a, double* b, double* c);
void output(const int num_of_roots, const double root1, const double root2);
bool run_test(const int test, const double a, const double b, const double c, const double root1_pending,
              const double root2_pending, const int num_of_rootsPending);
bool compare(const double num1, const double num2);

enum num_roots {
    no_roots = 0,
    no_root = 0,
    one_root = 1,
    two_roots = 2,
    inf_roots = -1
};

typedef struct coefficients {
    double coeff_a, coeff_b, coeff_c;
} coe;

typedef struct roots {
    double root1, root2;
} roo;


int main() {
    coe coeffs;
    roo* roots = (roo*) malloc (sizeof(double) * 2);
    coeffs.coeff_a = NAN;
    coeffs.coeff_b = NAN;
    coeffs.coeff_c = NAN;
    roots->root1 = NAN;
    roots->root2 = NAN;

    input(&coeffs.coeff_a, &coeffs.coeff_b, &coeffs.coeff_c);
    int num_of_roots = solve_square(coeffs.coeff_a, coeffs.coeff_b, coeffs.coeff_c, &roots->root1, &roots->root2);

    run_test(1, 0, 0, 0, inf_roots, inf_roots, inf_roots);
    run_test(2, 1, 2, 1, -1, no_root, one_root);
    run_test(3, 2, 4, 2, -1, no_root, one_root);
    run_test(4, 0, 0, 1, no_root, no_root, no_roots);
    run_test(5, 1, 0, 0, 0, no_root, one_root);
    run_test(6, 0, 1, 0, 0, no_root, one_root);
    run_test(7, 0, 1, 1, -1, no_root, one_root);
    run_test(8, 1e100, 1, 1, no_root, no_root, no_roots);
    run_test(9, 0, 1e-40, 1e40, 1e80, no_root, one_root);

    output(num_of_roots, roots->root1, roots->root2);
    return 0;
}

bool compare(const double num1, const double num2) {
    const double close_to_zero = 1e-6;
    if (fabs(num1 - num2) < close_to_zero) {
        return true;
    }
    else {
        return false;
    }
}

int solve_square(const double coeff_a, const double coeff_b, const double coeff_c,
                 double* root1, double* root2) {
    double discriminant = NAN;
    discriminant = coeff_b*coeff_b - 4 * coeff_a * coeff_c;

    if (compare(coeff_a, 0) &&
        compare(coeff_b, 0) &&
        compare(coeff_c, 0))
    {
        *root1 = -1;
        *root2 = -1;
        return inf_roots;
    }
    else if ((compare(coeff_a, 0) && compare(coeff_b, 0)) || discriminant < 0) {
        *root1 = no_root;
        *root2 = no_root;
        return no_roots;
    }
    else if (compare(coeff_a, 0)) {
        *root1 = -coeff_c/coeff_b;
        *root2 = no_root;
        return one_root;
        }
    else {
        if (compare(discriminant, 0)) {
            *root1 = -coeff_b/(2*coeff_a);
            *root2 = no_root;
            return one_root;
        }
        else {
            *root1 = (-coeff_b - sqrt(discriminant))/(2*coeff_a);
            *root2 = (-coeff_b + sqrt(discriminant))/(2*coeff_a);
            return two_roots;
        }
    }
}

void input(double* a, double* b, double* c) {
    while (scanf("%lf %lf %lf", a, b, c) != 3) {
        int symbol = 0;
        while (symbol != '\n' && symbol != EOF) {
            symbol = getchar();
        }
        printf("Input other coefficients\n");
    }
}

bool run_test(const int test_num, const double a, const double b, const double c,
             const double root1_pending, const double root2_pending, const int num_of_rootsPending) {
    double root1 = 0, root2 = 0;
    const int num_of_roots = solve_square(a, b, c, &root1, &root2);

    if (num_of_roots != num_of_rootsPending || !compare(root1, root1_pending) || !compare(root2, root2_pending)) {
        printf("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf"
               " root1 = %lf, root2 = %lf, num_of_roots = %d\n"
               "Pending num_of_roots root1 = %lf, root2 = %lf, num_of_roots = %d\n",
                test_num, a, b, c, root1, root2, num_of_roots,
                root1_pending, root2_pending, num_of_rootsPending);
        return false;
    } else {
        return true;
    }
}

void output(const int num_of_roots, const double root1, const double root2) {
    switch(num_of_roots) {
        case no_roots:
            printf("No Roots\n");
            break;
        case inf_roots:
            printf("Infinity of roots\n");
            break;
        case one_root:
            printf("%d %lf\n", num_of_roots, root1);
            break;
        case two_roots:
            printf("%d %lf %lf\n", num_of_roots, root1, root2);
            break;
        default:
            printf("ERROR\n");
    }
}


/*
0 0 0
1 2 1
2 4 2 Габисов
0 0 1
1 0 0
0 1 0
0 1 1
1e100 1 1
0 1e-40 1e40
1) фикс
2) буквенный ввод
3)
ДЗ
'функция сравнения'
'Выбрать кодстайл'
что-то новое название переменной, кодстайл, конст не коснт
структуры
*/


