#include <stdio.h>
#include <math.h>

int SolveSquare(double coeff_a, double coeff_b, double coeff_c, double* x1, double* x2);
void input(double* a, double* b, double* c);
void Output(int nRoots, double x1, double x2);
bool RunTest(int Test, double a, double b, double c, double x1pending, double x2pending, int nRootsPending);

enum NumRoots {
    NoRoots = 0,
    NoRoot = 0,
    OneRoot = 1,
    TwoRoots = 2,
    InfRoots = -1
};


int main() {
    double coeff_a = NAN, coeff_b = NAN, coeff_c = NAN, x1 = NAN, x2 = NAN;
    input(&coeff_a, &coeff_b, &coeff_c);
    int nRoots = SolveSquare(coeff_a, coeff_b, coeff_c, &x1, &x2);

    RunTest(1, 0, 0, 0, InfRoots, InfRoots, InfRoots);
    RunTest(2, 1, 2, 1, -1, NoRoot, OneRoot);
    RunTest(3, 2, 4, 2, -1, NoRoot, OneRoot);
    RunTest(4, 0, 0, 1, NoRoot, NoRoot, NoRoots);
    RunTest(5, 1, 0, 0, 0, NoRoot, OneRoot);
    RunTest(6, 0, 1, 0, 0, NoRoot, OneRoot);
    RunTest(7, 0, 1, 1, -1, NoRoot, OneRoot);
    RunTest(8, 1e100, 1, 1, NoRoot, NoRoot, NoRoots);
    RunTest(9, 0, 1e-40, 1e40, 1e80, NoRoot, OneRoot);

    Output(nRoots, x1, x2);
    return 0;
}

int SolveSquare(double coeff_a, double coeff_b, double coeff_c, double* x1, double* x2) {
    double discriminant = NAN, close_to_zero = 1e-6;
    discriminant = coeff_b*coeff_b - 4 * coeff_a * coeff_c;

    if (fabs(coeff_a) < close_to_zero &&
        fabs(coeff_b) < close_to_zero &&
        fabs(coeff_c) < close_to_zero)
    {
        *x1 = -1;
        *x2 = -1;
        return InfRoots;
    }
    else if ((fabs(coeff_a) < close_to_zero && fabs(coeff_b) < close_to_zero) || discriminant < 0) {
        *x1 = NoRoot;
        *x2 = NoRoot;
        return NoRoots;
    }
    else if (fabs(coeff_a) < close_to_zero) {
        *x1 = -coeff_c/coeff_b;
        *x2 = NoRoot;
        return OneRoot;
        }
    else {
        if (discriminant < close_to_zero) {
            *x1 = -coeff_b/(2*coeff_a);
            *x2 = NoRoot;
            return OneRoot;
        }
        else {
            *x1 = (-coeff_b - sqrt(discriminant))/(2*coeff_a);
            *x2 = (-coeff_b + sqrt(discriminant))/(2*coeff_a);
            return TwoRoots;
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

bool RunTest(const int TestNum, const double a, const double b, const double c,
             const double x1Pending, const double x2Pending, const int nRootsPending) {
    double x1 = 0, x2 = 0;
    const int nRoots = SolveSquare(a, b, c, &x1, &x2);

    if (nRoots != nRootsPending || x1 != x1Pending || x2 != x2Pending) {
        printf("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf"
               " x1 = %lf, x2 = %lf, nRoots = %d\n"
               "Pending nRoots x1 = %lf, x2 = %lf, nRoots = %d\n",
                TestNum, a, b, c, x1, x2, nRoots, x1Pending, x2Pending, nRootsPending);
        return false;
    } else {
        return true;
    }
}

void Output(int nRoots, double x1, double x2) {
    switch(nRoots) {
        case NoRoots:
            printf("No Roots\n");
            break;
        case InfRoots:
            printf("Infinity of roots\n");
            break;
        case OneRoot:
            printf("%d %lf\n", nRoots, x1);
            break;
        case TwoRoots:
            printf("%d %lf %lf\n", nRoots, x1, x2);
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
функция сравнения
Выбрать кодстайл
что-то новое название переменной, кодстайл, конст не коснт
структуры
*/


