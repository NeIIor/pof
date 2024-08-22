/*!
    \file
    \brief Заголовочный файл с описанием классов

    Данный файл содержит в себе определения основных
    классов, используемых в демонстрационной программе
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

const double ACCURACY = 1e-6;

enum num_roots {
    NO_ROOT = 0,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1
};

/// ax^2 + bx + c = 0
typedef struct coefficients {
    double coeff_a; ///< Example KEKKEKEKEKEKE
    double coeff_b, coeff_c;
} coeffs_t;

typedef struct roots {
    double root1, root2;
} roots_t;

typedef struct test {
    int num_of_test;
    coeffs_t coeffs;
    double root1_pending, root2_pending;
    int n_roots_pending;
} test_t;
 /*!
    \brief Solves the quadratic equation
    \param[in] Coeffs Structure that includes coefficients pointer on structure that includes roots
    \param[out] Pointer on structure that includes roots.
    \return Number of roots
 */
num_roots solve_square(const coeffs_t coeffs, roots_t* roots);

/*!
    \brief Accepts input of coefficients
    \param[in] Void
    \param Pointer on structure that includes coefficients
    \return Void
*/
void input_quadr_coeffs(coeffs_t* coeffs);

/*!
    \brief Output the roots and their number
    \param[in] Number of roots and structure that includes roots
    \param[out] Void
    \return Void
*/
void output_quadr_roots(const num_roots num_of_roots, const roots_t roots);

/*!
    \brief Run tests
    \param[in] Structures that includes number of test,  coefficients, expected roots,
               expected number of roots and structure that includes roots
    \param[out] Void
    \return True or False
*/
bool run_test(test_t test, roots_t roots);

/*!
    \brief Comparing two numbers (equal or not)
    \param[in] Two numbers and accuracy
    \param[out]
    \return True or False
*/
bool compare(const double num1, const double num2, const double accuracy);

/*!
    \brief Starting function run_test for all tests
    \param[in] Number of tests and structure that includes roots
    \param[out] Array of structures that includes number of test,  coefficients, expected roots,
           expected number of roots
    \return Void
*/
void start_of_tests(test_t* test, int num_of_tests, roots_t roots);

/*!
    \brief Clears stdin
    \param[in] Void
    \param[out] Void
    \return Void
*/
void clear_stdin();

/*!
    \brief Initialize tests
    \param[in] Structure of tests
    \param[out] Void
    \return Void
*/
void init_tests(test_t tests);

int main() {
    coeffs_t coeffs;
    roots_t roots;

    coeffs.coeff_a = NAN;
    coeffs.coeff_b = NAN;
    coeffs.coeff_c = NAN;
    roots.root1 = NAN;
    roots.root2 = NAN;

    input_quadr_coeffs(&coeffs);
    num_roots num_of_roots = solve_square(coeffs, &roots);
    test_t* tests;
    init(tests);

    int num_of_tests = sizeof(tests)/sizeof(tests[0]);

    start_of_tests(tests, num_of_tests, roots);

    output_quadr_roots(num_of_roots, roots);
    return 0;
}

void init_tests(test_t* tests) {
    tests = {
        {1, 0, 0, 0, INF_ROOTS, INF_ROOTS, INF_ROOTS},
        {2, 1, 2, 1, -1, NO_ROOTS, ONE_ROOT},
        {3, 2, 4, 2, -1, NO_ROOTS, ONE_ROOT},
        {4, 0, 0, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS},
        {5, 1, 0, 0, 0, NO_ROOTS, ONE_ROOT},
        {6, 0, 1, 0, 0, NO_ROOTS, ONE_ROOT},
        {7, 0, 1, 1, -1, NO_ROOTS, ONE_ROOT},
        {8, 1e100, 1, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS},
        {9, 0, 1e-40, 1e40, -1e80, NO_ROOTS, ONE_ROOT}
    };


void start_of_tests(test_t* test, int num_of_tests, roots_t roots) {
    assert(test != 0);
    for (int i = 0; i < num_of_tests; i++) {
        printf("%d\n", run_test(test[i], roots));
    }
}

bool compare(const double num1, const double num2, const double accuracy) {
    return fabs(num1 - num2) < accuracy;
}

num_roots solve_square(const coeffs_t coeffs, roots_t* roots) {
    assert(roots != 0);
    double discriminant = NAN;
    discriminant = coeffs.coeff_b*coeffs.coeff_b - 4 * coeffs.coeff_a * coeffs.coeff_c;

    if (compare(coeffs.coeff_a, 0, ACCURACY) &&
        compare(coeffs.coeff_b, 0, ACCURACY) &&
        compare(coeffs.coeff_c, 0, ACCURACY))
    {
        roots->root1 = -1;
        roots->root2 = -1;
        return INF_ROOTS;
    }
    else if ((compare(coeffs.coeff_a, 0, ACCURACY) && compare(coeffs.coeff_b, 0, ACCURACY))
              || discriminant < 0) {
        roots->root1 = NO_ROOTS;
        roots->root2 = NO_ROOTS;
        return NO_ROOTS;
    }
    else if (compare(coeffs.coeff_a, 0, ACCURACY)) {
        roots->root1 = -coeffs.coeff_c/coeffs.coeff_b;
        roots->root2 = NO_ROOTS;
        return ONE_ROOT;
        }
    else {
        if (compare(discriminant, 0, ACCURACY)) {
            roots->root1 = -coeffs.coeff_b/(2*coeffs.coeff_a);
            roots->root2 = NO_ROOTS;
            return ONE_ROOT;
        }
        else {
            roots->root1 = (-coeffs.coeff_b - sqrt(discriminant))/(2*coeffs.coeff_a);
            roots->root2 = (-coeffs.coeff_b + sqrt(discriminant))/(2*coeffs.coeff_a);
            return TWO_ROOTS;
        }
    }
}

void clear_stdin(){
    int symbol = 0;
    while (symbol != '\n' && symbol != EOF) {
            symbol = getchar();
    }
}

void input_quadr_coeffs(coeffs_t* coeffs) {
    assert(coeffs != 0);
    while (scanf("%lf %lf %lf", &coeffs->coeff_a, &coeffs->coeff_b, &coeffs->coeff_c) != 3) {
        clear_stdin();
        printf("enter other coefficients\n");
    }
}

bool run_test(test_t test, roots_t roots) {
    const num_roots num_of_roots = solve_square(test.coeffs, &roots);

    if (num_of_roots != test.n_roots_pending || !compare(roots.root1, test.root1_pending, ACCURACY)
        || !compare(roots.root2, test.root2_pending, ACCURACY)) {
        printf("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf"
               " root1 = %lf, root2 = %lf, num_of_roots = %d\n"
               "Pending num_of_roots root1 = %lf, root2 = %lf, num_of_roots = %d\n",
                test.num_of_test, test.coeffs.coeff_a, test.coeffs.coeff_b, test.coeffs.coeff_c,
                roots.root1, roots.root2, num_of_roots,test.root1_pending, test.root2_pending, test.n_roots_pending);
        return false;
    }

    return true;
}

void output_quadr_roots(const num_roots num_of_roots, const roots_t roots) {
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
            fprintf(stderr, "Unreachable\n");
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

ДЗ
1) clear stdin!!!
2) init tests!!!
3) argc argv env (kerni)!!!
4) ascii color codes
5) if a == 0  отдельная функия для линейного уравнения (на лекции деда)
6) options g++ warning, etc.
*/


