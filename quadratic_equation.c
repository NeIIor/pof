#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cerrno>
#include <cstring>

#define RED "\x1B[31m"
#define WHITE "\x1B[37m"
#define GREEN "\x1B[32m"
#define PRINT_RED(s, ...) printf(RED s WHITE, ##__VA_ARGS__)
#define PRINT_GREEN(s, ...) printf(GREEN s WHITE,   ##__VA_ARGS__)

/// accuracy for equal numbers
const double ACCURACY = 1e-6;

enum numbers {
    MINUS_INF = -1, ///< -inf for output, if root = -inf
    PLUS_INF = 1    ///< inf for output, if root = inf
};

/// enum for any solutions of quadratic equation
enum num_roots {
    INVALID = -2,  ///< enum for errors and initialization
    NO_ROOTS = 0,  ///< enum for no roots
    ONE_ROOT = 1,  ///< enum for one root
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
    double root1; ///<           root1 of quadratic equation
    double root2; ///<           root2 of quadratic equation
    num_roots num_of_roots; ///< number of roots
} roots_t;

/// just parameters for tests
typedef struct test {
    coeffs_t coeffs; ///<        coefficients of quadratic equation
    roots_t roots_expected; ///< structure with right roots and number of roots of quadratic equation
} test_t;


/*!
    \brief      solves linear equation
    \param[in]  coeffs structure that includes coefficients
    \param[out] roots  pointer on structure that includes roots
    \return     number of roots
*/
num_roots linear_equation(const coeffs_t coeffs, roots_t* roots);

 /*!
    \brief      solves the quadratic equation only if a != 0
    \param[in]  coeffs structure that includes coefficients
    \param[out] roots  pointer on structure that includes roots
    \return     number of roots
 */
num_roots solve_square(const coeffs_t coeffs, roots_t* roots);

/*!
    \brief      accepts only one input of coefficients
    \param[out] coeffs pointer on structure that includes coefficients
    \return     one if input is wrong, else zero
*/
bool input_quadr_coeffs(coeffs_t* coeffs);

/*!
    \brief     output the roots and their number
    \param[in] roots structure that includes roots
    \return    void
*/
void output_quadr_roots(const roots_t roots);

/*!
    \brief      run tests
    \param[in]  test  structure that includes number of test,  coefficients, expected roots,
                      expected number of roots
    \param[out] roots pointer on structure that includes roots
    \return     1 if true, else 0 if false
*/
int run_test(const test_t test, roots_t* roots);

/*!
    \brief     comparing two numbers (equal or not)
    \param[in] num1 the first number
               num2 the second number
               fallibility for equal numbers
    \return    true or false
*/
bool equality_check(const double num1, const double num2, const double accuracy);

/*!
    \brief      starting function run_test for all tests

    \param[in]  num_of_tests number of tests
    \param[out] test         array of structures that includes number of test,  coefficients, expected roots,
                             expected number of roots
    \return     void
*/
void start_of_tests(test_t* test, const size_t num_of_tests);

/*!
    \brief  clears stdin
    \return void
*/
void clear_stdin();

/*!
    \brief      accepts coefficients of quadratic equal until they are right
    \param[out] coeffs pointer on structure that includes coefficients
    \return     void
*/
void total_input_quadr_coeffs(coeffs_t* coeffs);

/*!
    \brief      checks finite root or not
    \param[out] root + or - inf if root is infinite and does nothing if root is finite
    \return     void
*/
void change_root_to_infinite(double* root);

/*!
    \brief      records str from stream to lineptr and counts number of recording chars
    \param[in]  n_chars_max max number of chars that lineptr can record
    \param[out] stream  stream for reading, where chars for record
                lineptr str that will be recorded by chars from stream
    \return     number of recorded chars
*/
ssize_t my_getline(char* lineptr, const size_t n_chars_max, FILE* stream);


int main(int argc, char* argv[]) {
    printf("Hello! Enter your coefficients for quadratic equation.\n");
    coeffs_t coeffs;
    roots_t roots;
    coeffs.coeff_a = NAN;
    coeffs.coeff_b = NAN;
    coeffs.coeff_c = NAN;
    roots.root1 = NAN;
    roots.root2 = NAN;

    if (argc != 2) {
        PRINT_RED("Enter only name of file! Nothing more!\n");
        return 1;
    }

    char *line_buf = NULL;
    const size_t line_buf_size = 0;
    const char* file_name = argv[1];

    struct stat stbuf;
    stat(argv[1], &stbuf);
    const off_t size_of_file = stbuf.st_size;

    FILE* data_for_tests = fopen(file_name, "r");
    if (data_for_tests == NULL) {
        PRINT_RED("This file doesn't exist.\n");
        return 1;
    }

    bool last_flag = false;
    int num_of_structs = 0;
    int help = 0;
    ssize_t line_size = my_getline(line_buf, line_buf_size, data_for_tests);

    test_t* tests = (test_t*) calloc(size_of_file, sizeof(test_t));//exit
    assert(tests == NULL);

    while (1) {
        if (line_buf[line_size-1] != '\n') {
            last_flag = true;
        }
        if (line_size > 1) {
            tests = (test_t*) realloc(tests, (++num_of_structs) * sizeof(test_t));
            assert(tests = NULL);
            sscanf(line_buf, "%lf %lf %lf %lf %lf %d", &tests[num_of_structs-1].coeffs.coeff_a,
                   &tests[num_of_structs-1].coeffs.coeff_b, &tests[num_of_structs-1].coeffs.coeff_c,
                   &tests[num_of_structs-1].roots_expected.root1,
                   &tests[num_of_structs-1].roots_expected.root2,
                   &help);
            tests[num_of_structs-1].roots_expected.num_of_roots = (num_roots) help;
        }
        if (last_flag == true) {
            break;
        }
        line_size = my_getline(line_buf, line_buf_size, data_for_tests);
    }

    total_input_quadr_coeffs(&coeffs);
    roots.num_of_roots = solve_square(coeffs, &roots);
    start_of_tests(tests, num_of_structs);
    output_quadr_roots(roots);

    fclose(data_for_tests);
    free(line_buf);
    free(tests);
    return 0;
}

ssize_t my_getline(char* lineptr, const size_t n_chars_max, FILE* stream) {
    ssize_t i = 0;
    if (n_chars_max) {
        int c = 0;
        while ((i < n_chars_max - 1) && (c = fgetc(stream)) != EOF && c != '\n') {
            lineptr[i++] = c;
        }
    }

    lineptr = '\0';

    return i;
}


void start_of_tests(test_t* test, const size_t num_of_tests) {
    assert(test != 0);
    roots_t roots = {
        NAN,
        NAN,
        INVALID
    };
    for (size_t i = 0; i < num_of_tests; i++) {
        if (run_test(test[i], &roots) == 1) {
            PRINT_GREEN("Test %d is True.\n", i + 1);
        } else {
            PRINT_RED("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf "
                      "root1 = %lf, root2 = %lf, num_of_roots = %d\n"
                      "Expected num_of_roots root1 = %lf, root2 = %lf, num_of_roots = %d.\n",
                      i + 1, test[i].coeffs.coeff_a, test[i].coeffs.coeff_b, test[i].coeffs.coeff_c,
                      roots.root1, roots.root2, roots.num_of_roots,
                      test[i].roots_expected.root1,
                      test[i].roots_expected.root2, test[i].roots_expected.num_of_roots);
        }
    }
}

bool equality_check(const double num1, const double num2, const double accuracy) {
    return fabs(num1 - num2) <= accuracy;
}
void change_root_to_infinite(double* root) {
    assert(root);
    if (isfinite(*root) && *root > 0) {
            *root = (numbers) PLUS_INF;
    } else if (isfinite(*root) && *root < 0){
        *root = (numbers) MINUS_INF;
    }
}


num_roots linear_equation(const coeffs_t coeffs, roots_t* roots) {
    const bool equality_zero_coeff_b = equality_check(coeffs.coeff_b, 0, ACCURACY);
    const bool equality_zero_coeff_c = equality_check(coeffs.coeff_c, 0, ACCURACY);
    if (check_for_equality_of_zero_coeff_b) {
        if (check_for_equality_of_zero_coeff_c) {
            roots->root1 = INF_ROOTS;
            roots->root2 = INF_ROOTS;
            return INF_ROOTS;
        } else {
            roots->root1 = NO_ROOTS;
            roots->root2 = NO_ROOTS;
            return NO_ROOTS;
        }
    } else {
        roots->root1 = -coeffs.coeff_c/coeffs.coeff_b;
        roots->root2 = NO_ROOTS;
        change_root_to_infinite(&roots->root1);
        return ONE_ROOT;
    }
}


num_roots solve_square(const coeffs_t coeffs, roots_t* roots) { //const
    assert(roots);

    const double discriminant = coeffs.coeff_b * coeffs.coeff_b - 4 * coeffs.coeff_a * coeffs.coeff_c;
    if(isfinite(discriminant)) {
        PRINT_RED("Discriminant is too big. Sorry, i can't solve it.\n");
    }

    const bool check_for_equality_of_zero_d = equality_check(discriminant, 0, ACCURACY);
    const bool check_for_equality_of_zero_coeff_a = equality_check(coeffs.coeff_a, 0, ACCURACY);

    if (check_for_equality_of_zero_coeff_a) {
        return linear_equation(coeffs, roots);
    } else if (check_for_equality_of_zero_d) {
        roots->root1 = -coeffs.coeff_b/(2*coeffs.coeff_a);
        roots->root2 = NO_ROOTS;
        change_root_to_infinite(&roots->root1);
        return ONE_ROOT;
    } else if (discriminant < 0) {
        roots->root1 = NO_ROOTS;
        roots->root2 = NO_ROOTS;
        return NO_ROOTS;
    } else {
        roots->root1 = (-coeffs.coeff_b - sqrt(discriminant))/(2*coeffs.coeff_a);
        roots->root2 = (-coeffs.coeff_b + sqrt(discriminant))/(2*coeffs.coeff_a);
        change_root_to_infinite(&roots->root1);
        change_root_to_infinite(&roots->root2);
        if (equality_check(roots->root1, roots->root2, ACCURACY)) {
            roots->root2 = NO_ROOTS;
            return ONE_ROOT;
        }
        return TWO_ROOTS;
    }
}

void clear_stdin(){
    int symbol = 0;
    while (symbol != '\n' && symbol != EOF) {
        symbol = getchar();
    }
}

void check_errno(int* errno, bool* flag) {
    if (errno != 0) {
        fprintf(stderr, strerror(errno));
        errno = 0;
        *flag = false;
    }
}

bool input_quadr_coeffs(coeffs_t* coeffs) {
    assert(coeffs);
    int maximum_of_chars = 1000;
    int n_chars_max; //arg by default + global const
    char input_str[maximum_of_chars];
    fgets(input_str, maximum_of_chars, stdin);// limit

    char* end_coeff1 = NULL;
    char* end_coeff2 = NULL;
    char* end_coeff3 = NULL;

    int safe_errno = errno;
    errno = 0;
    bool flag = true;

    coeffs->coeff_a = strtod(input_str, &end_coeff1);
    if (input_str == end_coeff1) {
        PRINT_RED("The first coefficient is not numerical.\n");
        flag = false
    }
    check_errno(&errno, &flag);
    coeffs->coeff_b = strtod(end_coeff1, &end_coeff2);
    if (end_coeff1 == end_coeff2) {
        PRINT_RED("The second coefficient is not numerical.\n");
        flag = false;
    }
    check_errno(&errno, &flag);

    coeffs->coeff_c = strtod(end_coeff2, &end_coeff3);
    if (end_coeff2 == end_coeff3) {
        PRINT_RED("The third coefficient is not numerical.\n");
        flag = false;
    }
    check_errno(&errno, &flag);

    if (*end_coeff3 != '\n' && *end_coeff3 != EOF) {
        PRINT_RED("You enter too many coefficients. Enter only three.\n");
        check_errno(&errno, &flag);
    } else if (!isfinite(coeffs->coeff_a) || !isfinite(coeffs->coeff_b) || !isfinite(coeffs->coeff_c)) {
        PRINT_RED("Your coefficients are too big. Enter other coefficients.\n");
        check_errno(&errno, &flag);
    }
    if (flag) {
        return true;
    }
    errno = safe_errno;
    clear_stdin();

    return false;
}

void total_input_quadr_coeffs(coeffs_t* coeffs) {
    while(!input_quadr_coeffs(coeffs));
}

int run_test(const test_t test, roots_t* roots) { // ass
    roots->num_of_roots = solve_square(test.coeffs, roots);
    if (roots->num_of_roots != test.roots_expected.num_of_roots ||
       !equality_check(roots->root1, test.roots_expected.root1, ACCURACY)||
       !equality_check(roots->root2, test.roots_expected.root2, ACCURACY)) {
        return 0;
    } else {
        return 1;
    }
}

void output_quadr_roots(const roots_t roots) {
    printf("Thanks, there is your solution: ");
    switch(roots.num_of_roots) {
        case NO_ROOTS:
            printf("no roots.\n");
            break;
        case INF_ROOTS:
            printf("infinity of roots.\n");
            break;
        case ONE_ROOT:
            printf("%d root: %lf.\n", roots.num_of_roots, roots.root1);
            break;
        case TWO_ROOTS:
            printf("%d roots: %lf and %lf.\n", roots.num_of_roots, roots.root1, roots.root2);
            break;
        default:
            fprintf(stderr, RED "Unreachable.\n" WHITE); //stderr + print red
            assert(false);
    }
}

/*
0 0 0
1 2 1
2 4 2 �������
0 0 1
1 0 0
0 1 0
0 1 1
1e100 1 1
0 1e-40 1e40
1) ����
2) ��������� ����
3)

��
'������� ���������'
'������� ��������'
���-�� ����� �������� ����������, ��������, ����� �� �����
���������
12:43 22.08
0) assert �� ��������� ���������!!!
1) ������ ��������!!!
2) ���������� �� ���������!!!
3) ����� ������!!!
4) �������� ������ �� 0!!!
5) � ������ ���������� ��������� ��� ��������� �� ���!!!
6) ������� clear_stdin
7) stdin, stdout, stderr | fprintf(stdout, "", ...) = printf("", ...) | fflush()

��
1) clear stdin!!!
2) init tests!!!
3) argc argv getenv (kerni)!!!
4) ascii color codes
5) if a == 0  ��������� ������ ��� ��������� ��������� (�� ������ ����)
6) options g++ warning, etc.



1) doc on structures and enum!!!
2) _VA_ARGS � ��� �� ������������ ��������
3) ����������� ����� ����� ����� 2 ��� ������
4) ����� ���� (� �������) ����� ����� 3
5) ���� ������ ����� ������ ������
FILE* fopen(
fscanf
fread
��
1)������� ������ ������� ����� ���� ��� ������
2)�������� � ������ ��������� �� f � ������� while�
3)printf �� ��� ����� �������� � ����� ��� �����         3) = ���� troubles
4)doc fix
5)��������� � ��������� ��� ����� � ���� roots_t roots_expected!!!
6)�������� ��������� � �������, ��������� ��������� ���� ������������, ��� 2 ���� ����������, � ���� ���!!!
����� ����� � ��������� roots ����� ��� ����.���������

������� �� �������
1) equality_check � input!!!
2) ������ ��� ����� = ��������� � �������!!!
3) ��������� ��� ���������� �������� �����, �������� ������ � �������� fread��

continue
4)��������� f ��� ������� ����� ����� ������
5)��������� ��� cat!!!
6) �������� ������������!!!
7) �������� ����� ����� �������� ��������� ������

HW
1) delete lfs in git config --list --global!!!
2) setting cache credentials!!!
3) input from file
4) 5 7 8 chapters in kerni application A and b1.1-b1.8
5) linear equation (a == 0) -> (b == 0) empty equation !!!

���� �� �������
strtod �������� ��� ������ scanf
kerni f ��������� �� ���������
exit failer
exit success

last = last_struct
*/


