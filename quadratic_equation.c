#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>


#define PRINT_RED(...) { printf(RED, __VA_ARGS__); }
#define PRINT_WHITE(...) { printf(WHITE, __VA_ARGS__); }
#define PRINT_GREEN(...) { printf(GREEN, __VA_ARGS__); }
#define RED "\x1B[31m"
#define WHITE "\x1B[37m"
#define GREEN "\x1B[32m"

/// accuracy for equal numbers
const double ACCURACY = 1e-6;

/// enum for any solutions of quadratic equation
enum num_roots {
    NO_ROOTS = 0, ///< enum for no roots
    ONE_ROOT = 1, ///< enum for one root
    TWO_ROOTS = 2, ///< enum for two roots
    INF_ROOTS = -1 ///< enum for inf roots
};

/// coefficients of quadratic equation ax^2 + bx + c = 0
typedef struct coefficients {
    double coeff_a; ///< leading coefficient
    double coeff_b; ///< coefficient at x
    double coeff_c; ///< free coefficient
} coeffs_t;

/// just roots of ax^2 + bx + c = 0
typedef struct roots {
    double root1; ///< root1 of quadratic equation
    double root2; ///< root2 of quadratic equation
} roots_t;

/// just parameters for tests
typedef struct test {
    coeffs_t coeffs; ///< coefficients of quadratic equation
    roots_t roots_expected; ///< structure right roods of quadratic equation
    int n_roots_expected; ///< right number of roots
} test_t;

 /*!
    \brief solves the quadratic equation
    \param[in] coeffs structure that includes coefficients pointer on structure that includes roots
    \param[out] roots  pointer on structure that includes roots.
    \return number of roots
 */
int solve_square(const coeffs_t coeffs, roots_t* roots);

/*!
    \brief accepts only one input of coefficients
    \param[out] coeffs pointer on structure that includes coefficients
    \return one if input is wrong, else 0
*/
int input_quadr_coeffs(coeffs_t* coeffs);

/*!
    \brief Output the roots and their number
    \param[in] num_of_roots number of roots
               roots structure that includes roots
    \return Void
*/
void output_quadr_roots(const int num_of_roots, roots_t roots);

/*!
    \brief Run tests
    \param[in] test structure that includes number of test,  coefficients, expected roots,
               expected number of roots
               roots structure that includes roots
    \return True or False
*/
int run_test(const test_t test, double root1, double root2, int* num_of_roots);

/*!
    \brief Comparing two numbers (equal or not)
    \param[in] num1 the first number
               num2 the second number
               accuracy fallibility for equal numbers
    \return True or False
*/
bool compare(const double num1, const double num2, const double accuracy);

/*!
    \brief Starting function run_test for all tests
    \param[in] num_of_tests number of tests and structure that includes roots
    \param[out] test array of structures that includes number of test,  coefficients, expected roots,
                expected number of roots
    \return Void
*/
void start_of_tests(test_t* test, const int num_of_tests);

/*!
    \brief Clears stdin
    \return Void
*/
void clear_stdin();

/*!
\brief accepts coefficients of quadratic equal until they are right
\param coeffs pointer on structure that includes coefficients
\return Void
*/
void total_input_quadr_coeffs(coeffs_t* coeffs);

test_t tests[] = {
    {0, 0, 0, INF_ROOTS, INF_ROOTS, INF_ROOTS},
    {1, 2, 1, -1, NO_ROOTS, ONE_ROOT},
    {2, 4, 2, -1, NO_ROOTS, ONE_ROOT},
    {0, 0, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS},
    {1, 0, 0, 0, NO_ROOTS, ONE_ROOT},
    {0, 1, 0, 0, NO_ROOTS, ONE_ROOT},
    {0, 1, 1, -1, NO_ROOTS, ONE_ROOT},
    {1e100, 1, 1, NO_ROOTS, NO_ROOTS, NO_ROOTS},
    {0, 1e-40, 1e40, NO_ROOTS, NO_ROOTS, NO_ROOTS}
};


int main() {
    printf("Hello! Please enter your coefficients for quadratic equation:\n");
    coeffs_t coeffs;
    roots_t roots;
    coeffs.coeff_a = NAN;
    coeffs.coeff_b = NAN;
    coeffs.coeff_c = NAN;
    roots.root1 = NAN;
    roots.root2 = NAN;

    struct stat stbuf;
    stat(tests, &stbuf);
    size_of_file = stat.st_size

    int num_of_tests = 9;


    total_input_quadr_coeffs(&coeffs);
    int num_of_roots = solve_square(coeffs, &roots);

    start_of_tests(tests, num_of_tests);

    output_quadr_roots(num_of_roots, roots);

    return 0;
}

void start_of_tests(test_t* test, const int num_of_tests) {
    assert(test != 0);
    double root1 = 0, root2 = 0;
    int* num_of_roots;
    for (int i = 0; i < num_of_tests; i++) {
        if (run_test(test[i], root1, root2, num_of_roots) == 1) {
            PRINT_GREEN("Test %d is True", i + 1);
        } else {
            PRINT_RED("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf "
                      "root1 = %lf, root2 = %lf, num_of_roots = %d\n"
                      "Expected num_of_roots root1 = %lf, root2 = %lf, num_of_roots = %d\n",
                      i + 1, test[i].coeffs.coeff_a, test[i].coeffs.coeff_b, test[i].coeffs.coeff_c,
                      root1, root2, num_of_roots,test[i].roots_expected.root1,
                      test[i].roots_expected.root2, test[i].n_roots_expected);
            PRINT_WHITE();
        }
    }
}

bool compare(const double num1, const double num2, const double accuracy) {
    return fabs(num1 - num2) <= accuracy;
}

int solve_square(const coeffs_t coeffs, double* root1, double* root2) {
    assert(root1 != 0);
    assert(root2 != 0);
    double discriminant = NAN;
    discriminant = coeffs.coeff_b*coeffs.coeff_b - 4 * coeffs.coeff_a * coeffs.coeff_c;

    if (compare(coeffs.coeff_a, 0, ACCURACY) &&
        compare(coeffs.coeff_b, 0, ACCURACY) &&
        compare(coeffs.coeff_c, 0, ACCURACY))
    {
        *root1 = INF_ROOTS;
        *root2 = INF_ROOTS;
        return INF_ROOTS;
    }
    else if ((compare(coeffs.coeff_a, 0, ACCURACY) && compare(coeffs.coeff_b, 0, ACCURACY))
              || discriminant < 0) {
        *root1 = NO_ROOTS;
        *root2 = NO_ROOTS;
        return NO_ROOTS;
    }
    else if (compare(coeffs.coeff_a, 0, ACCURACY)) {
        *root1 = -coeffs.coeff_c/coeffs.coeff_b;
        *root2 = NO_ROOTS;
        return ONE_ROOT;
        }
    else {
        if (compare(discriminant, 0, ACCURACY)) {
            *root1 = -coeffs.coeff_b/(2*coeffs.coeff_a);
            *root2 = NO_ROOTS;
            return ONE_ROOT;
        }
        else {
            *root1 = (-coeffs.coeff_b - sqrt(discriminant))/(2*coeffs.coeff_a);
            *root2 = (-coeffs.coeff_b + sqrt(discriminant))/(2*coeffs.coeff_a);
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

int input_quadr_coeffs(coeffs_t* coeffs) {
    assert(coeffs);
    if (scanf("%lf %lf %lf", &coeffs->coeff_a, &coeffs->coeff_b, &coeffs->coeff_c) != 3) {
        clear_stdin();
        PRINT_RED("Please enter numerical coefficients\n");
        PRINT_WHITE();
        return 0;
    } else if (compare(coeffs.coeff_a, 0, ACCURACY) || compare(coeffs.coeff_b, 0, ACCURACY)) ||
               compare(coeffs.coeff_c, 0, ACCURACY))) {
        PRINT_RED("Your coefficients are too small. Enter other coefficients.\n");
        PRINT_WHITE();
        return 0;
    } else if (isfinite(coeffs->coeff_a) || isfinite(coeffs->coeff_b) ||
               isfinite(coeffs->coeff_c)) {
        PRINT_RED("Your coefficients are too big. Enter other coefficients.\n");
        PRINT_WHITE();
        return 0;
    } else {
        printf("OK. Let's go.\n");
        return 1;
    }
}

void total_input_quadr_coeffs(coeffs_t* coeffs) {
    while(!input_quadr_coeffs(coeffs));
}

int run_test(const test_t test, double root1, double root2, int* num_of_roots) {
    *num_of_roots = solve_square(test.coeffs, &root1, &root2);
    if (num_of_roots != test.n_roots_expected || !compare(root1, test.roots_expected.root1, ACCURACY)
        || !compare(root2, test.roots_expected.root2, ACCURACY)) {
        return 0; //длинный принтф был здесь
    } else {
        return 1;
    }
}

void output_quadr_roots(const int num_of_roots, const roots_t roots) {
    printf("Thanks, there is your solution: ");
    switch(num_of_roots) {
        case NO_ROOTS:
            printf("no roots\n");
            break;
        case INF_ROOTS:
            printf("infinity of roots\n");
            break;
        case ONE_ROOT:
            printf("%d root: %lf\n", num_of_roots, roots.root1);
            break;
        case TWO_ROOTS:
            printf("%d roots: %lf and %lf\n", num_of_roots, roots.root1, roots.root2);
            break;
        default:
            fprintf(stderr, RED "Unreachable\n" WHITE);
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
3) argc argv getenv (kerni)!!!
4) ascii color codes
5) if a == 0  отдельная функия для линейного уравнения (на лекции деда)
6) options g++ warning, etc.



1) doc on structures and enum!!!
2) _VA_ARGS и как им пользоваться макросом
3) реализовать цвета через пункт 2 как макрос
4) тесты фикс (с цветами) через пункт 3
5) ввод тестов через другой файлик
FILE* fopen(
fscanf
fread
ДЗ
1)сделать макрос который ведет себя как принтф
2)поменять в инпуте сравнения на f и сделать whileы
3)printf из ран теста перенсти в старт ран тестс         3) = куча troubles
4)doc fix
5)структура в структуре для теста в виде roots_t roots_expected!!!
6)доделать структуру с тестами, передавая структуру одну неизменяемую, или 2 одну изменяемую, а одну нет!!!
тогда смысл в структуре roots кроме как влож.структура

Задание на поездку
1) compare в input!!!
2) макрос для цвета = страничка в яндексе!!!
3) прочитать про нахождения размеров файла, выделить память и записать freadом

1) size_t = unsigned long
2) num_of_roots добавить в стракт roots
3) передавать указатели на root1 root2

*/


