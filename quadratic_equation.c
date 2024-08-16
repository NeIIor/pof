#include <stdio.h>
#include <math.h>

int main() {
    double a = NAN, b = NAN, c = NAN, d = NAN;
    scanf("%lf %lf %lf", &a, &b, &c);
    d = pow(b, 2) - 4 * a * c;
    if (d < 0) {
        printf("No root\n");
    }
    else if (d < 0.000000000000001 && d > 0) {
        printf("One root: %lf\n", -b/(2 * a));
    }
    else {
        printf("Two roots: %lf %lf\n", (- b - sqrt(d))/(2 * a), (- b + sqrt(d))/(2 * a));
    }
    return 0;
}
