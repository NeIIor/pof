#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double ACCURACY = 1e-6;

enum num_roots {
    NO_ROOT = 0,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

typedef struct coefficients {
    double coeff_a, coeff_b, coeff_c;
} coeffs_t;

typedef struct roots {
    double root1, root2;
} roots_t;

typedef struct test {
    int num_of_test;
    coeffs_t coeffs;
    double root1_pending, root2_pending;
    int n_roots;
} test_t;



/*!
\brief Solves the quadratic equation
\param Structure, that is including coefficients and pointer on structure, that is including roots
\return Number of roots
*/
int solve_square(const coeffs_t coeffs, roots_t* roots);
/*!
\brief Accepts input of coefficients
\param Pointer on structure, that is including coefficients
\return Void
*/
void input(coeffs_t* coeffs);
/*!
\brief Output the roots and their number
\param Number of roots and structure, that is including roots
\return Void
*/
void output(const num_roots num_of_roots, const roots_t roots);
/*!
\brief Run tests
\param Structures, that are including number of test,  coefficients, pending roots
and pending number of roots
\return True or False
*/
bool run_test(test_t test);
/*!
\brief Comparing two numbers (equal or not)
\param Two numbers and accuracy
\return True or False
*/
bool compare(const double num1, const double num2, const double accuracy);
/*!
\brief Starting function run_test for all tests
\param Array of structures, that are including number of test,  coefficients, pending roots
\return Void
*/
void start_of_tests(test_t* test, int num_of_tests) {
    assert(test != 0);
    for (int i = 0; i < num_of_tests; i++) {
        printf("%b", run_test(test[i]));
    }
}


int main() {
    int num_of_tests = 9;
    coeffs_t coeffs;
    roots_t roots;
    test_t test[num_of_tests];
    coeffs.coeff_a = NAN;
    coeffs.coeff_b = NAN;
    coeffs.coeff_c = NAN;
    roots->root1 = NAN;
    roots->root2 = NAN;

    input(&coeffs);
    int num_of_roots = solve_square(coeffs, &roots);

    test[0] = {1, 0, 0, 0, INF_ROOTS, INF_ROOTS, INF_ROOTS);
    test[1] = (2, 1, 2, 1, -1, NO_ROOTS, ONE_ROOT);
    test[2] = (3, 2, 4, 2, -1, NO_ROOTS, ONE_ROOT);
    test[3] = (4, 0, 0, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS);
    test[4] =(5, 1, 0, 0, 0, NO_ROOTS, ONE_ROOT);
    test[5] =(6, 0, 1, 0, 0, NO_ROOTS, ONE_ROOT);
    test[6] =(7, 0, 1, 1, -1, NO_ROOTS, ONE_ROOT);
    test[7] =(8, 1e100, 1, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS);
    test[8] =(9, 0, 1e-40, 1e40, -1e80, NO_ROOTS, ONE_ROOT);

    start_of_tests(test, num_of_tests);

    output(num_of_roots, roots);
    return 0;
}

bool compare(const double num1, const double num2, const double accuracy) {
    return fabs(num1 - num2) < accuracy;
}

int solve_square(const coeffs_t coeffs, roots_t* roots) {
    assert(roots != 0);
    double discriminant = NAN;
    discriminant = coeffs_t.coeff_b*coeffs_t.coeff_b - 4 * coeffs_t.coeff_a * coeffs_t.coeff_c;

    if (compare(coeffs_t.coeff_a, 0, ACCURACY) &&
        compare(coeffs_t.coeff_b, 0, ACCURACY) &&
        compare(coeffs_t.coeff_c, 0, ACCURACY))
    {
        roots_t->root1 = -1;
        roots_t->root2 = -1;
        return INF_ROOTS;
    }
    else if ((compare(coeffs_t.coeff_a, 0, ACCURACY) && compare(coeffs_t.coeff_b, 0, ACCURACY))
              || discriminant < 0) {
        roots_t->root1 = NO_ROOTS;
        roots_t->root2 = NO_ROOTS;
        return NO_ROOTS;
    }
    else if (compare(coeffs_t.coeff_a, 0, ACCURACY)) {
        roots_t->root1 = -coeffs_t.coeff_c/coeffs_t.coeff_b;
        roots_t->root2 = NO_ROOTS;
        return ONE_ROOT;
        }
    else {
        if (compare(discriminant, 0, ACCURACY)) {
            roots_t->root1 = -coeffs_t.coeff_b/(2*coeffs_t.coeff_a);
            roots_t->root2 = NO_ROOTS;
            return ONE_ROOT;
        }
        else {
            roots_t->root1 = (-coeffs_t.coeff_b - sqrt(discriminant))/(2*coeffs_t.coeff_a);
            roots_t->root2 = (-coeffs_t.coeff_b + sqrt(discriminant))/(2*coeffs_t.coeff_a);
            return TWO_ROOTS;
        }
    }
}

void input(coeffs_t* coeffs) {
    assert(coeffs != 0);
    while (scanf("%lf %lf %lf", coeffs->a, coeffs->b, coeffs->c) != 3) {
        int symbol = 0;
        while (symbol != '\n' && symbol != EOF) {
            symbol = getchar();
        }
        printf("Input other coefficients\n");
    }
}

bool run_test(test_t test) {
    double root1 = 0, root2 = 0;
    const int num_of_roots = solve_square(test.coeffs, &root1, &root2);

    if (num_of_roots != num_of_rootsPending || !compare(root1, root1_pending) || !compare(root2, root2_pending)) {
        printf("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf"
               " root1 = %lf, root2 = %lf, num_of_roots = %d\n"
               "Pending num_of_roots root1 = %lf, root2 = %lf, num_of_roots = %d\n",
                test_num, test.coeffs.coeff_a, test.coeffs.coeff_b, test.coeffs.coeff_c
                root1, root2, num_of_roots,test.root1_pending, test.root2_pending, test.n_roots);
        return false;
    } else {
        return true;
    }
}

void output(const num_roots num_of_roots, const roots_t roots) {
    switch(num_of_roots) {
        case NO_ROOTS:
            printf("No Roots\n");
            break;
        case INF_ROOTS:
            printf("Infinity of roots\n");
            break;
        case ONE_ROOT:
            printf("%d %lf\n", num_of_roots, roots.root1);
            break;
        case TWO_ROOTS:
            printf("%d %lf %lf\n", num_of_roots, roots.root1, roots.root2);
            break;
        default:
            printf("Unreachable\n");
            assert(false);
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
12:43 22.08
0) assert на ненулевой указатель!!!
1) массив структур!!!
2) переменная по умолчанию!!!
3) енумы капсом!!!
4) проверка каллок на 0!!!
5) в фунцию передавать структуру или указатель на нее!!!
6) сделать clear_stdin
7) stdin, stdout, stderr | fprintf(stdout, "", ...) = printf("", ...) | fflush()
*/


