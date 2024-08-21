#include <stdio.h>
#include <math.h>

int SolveSquare(double coeff_a, double coeff_b, double coeff_c, double* x1, double* x2);
void input(double* a, double* b, double* c);
void output(int nRoots, double x1, double x2);
int RunTest(int Test, double a, double b, double c, double x1pending, double x2pending, int nRootsPending);

enum NumRoots {
    NoRoots = 0,
    OneRoot = 1,
    TwoRoots = 2,
    InfRoots = -1
};


int main() {
    double coeff_a = NAN, coeff_b = NAN, coeff_c = NAN, x1 = NAN, x2 = NAN;
    input(&coeff_a, &coeff_b, &coeff_c);
    int nRoots = SolveSquare(coeff_a, coeff_b, coeff_c, &x1, &x2);
    printf("%d %lf %lf", nRoots, x1, x2);



    RunTest(1, 1, 0, -4, -2, 2, 2);
    output(nRoots, x1, x2);
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
        *x1 = 0;
        *x2 = 0;
        return NoRoots;
    }
    else if (fabs(coeff_a) < close_to_zero) {
        *x1 = -coeff_c/coeff_b;
        return 1;
        }
    else {
        if (discriminant < close_to_zero && discriminant > 0) {
            *x1 = -coeff_b/(2*coeff_a);
            return 1;
        }
        else {
            *x1 = (-coeff_b - sqrt(discriminant))/(2*coeff_a);
            *x2 = (-coeff_b + sqrt(discriminant))/(2*coeff_a);
            return 2;
        }
    }
}

void input(double* a, double* b, double* c) {
    char d;
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        while (d != '\n') {
        d = getchar();
        }
    }
}

int RunTest(int Test, double a, double b, double c, double x1Pending, double x2Pending, int nRootsPending) {
    double x1 = 0, x2 = 0;
    int nRoot = SolveSquare(a, b, c, &x1, &x2);

    if (nRoot != nRootsPending || x1 != x1Pending || x2 != x2Pending) {
        printf("Error Test %d; coeff_a = %lf, coeff_b = %lf, coeff_c = %lf"
               "x1 = %lf, x2 = %lf, nRoots = %d\n"
               "Pending nRoots x1 = %lf, x2 = %lf, nRoots = %d\n",
                Test, a, b, c, x1, x2, nRoot, x1Pending, x2Pending, nRootsPending);
        return 1;
    } else {
        return 0;
    }
}

void output(int nRoots, double x1, double x2) {
    if (nRoots == NoRoots) {
        printf("No Roots\n");
    }
    else if (nRoots == InfRoots) {
        printf("Infinity of roots\n");
    }
    else {
        printf("%d %lf %lf\n", nRoots, x1, x2);
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
*/
