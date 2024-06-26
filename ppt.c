#include <stdio.h>
#include <math.h>

double f(int n, double x);
double f1(int n, double x);
double f2(int n, double x);
int CheckConditions(int n, double a, double b);
void newton(int n, double epsilon, double x0, double a, double b, double *x, double *e, int *l, int max);

float numbers[9999] = {0};

int main()
{
    int n, l, max;
    
    printf ("Nhap so bac cua phuong trinh: ");
    scanf ("%d", &n);

    for (int i = 0; i <= n; i++)
    {
        printf ("Nhap he so cua x^%d: ", i);
        scanf("%f", &numbers[i]);
    }

    double epsilon, a, b, x0, x, e;

    printf ("Nhap khoang phan ly: ");
    scanf ("%lf %lf", &a, &b);

    printf ("Nhap sai so: ");
    scanf ("%lf", &epsilon);

    printf("Nhap toi da so lan lap (hay so lan lap mong muon): ");
    scanf("%d", &max);
    
    if (CheckConditions(n, a, b) == 1 || CheckConditions(n, a, b) == 0)
    {
        return 0;
    }
    else if (CheckConditions(n, a, b) == 2)
    {
        x0 = a;
    }
    else if (CheckConditions(n, a, b) == 3)
    {
        x0 = b;
    }

    printf("|---------|---------------|--------|\n");
    printf("| LAN LAP | GIA TRI CUA X | SAI SO |\n");
    printf("|---------|---------------|--------|\n");

    newton(n, epsilon, x0, a, b, &x, &e, &l, max);

    if (x < a || x > b)
    {
        printf ("Khong tim duoc nghiem trong khoang phan ly\n");
    }
    else
    {
        printf("Nghiem gan dung cua phuong trinh: x = %lf\n", x);
        printf("Sai so: e = %lf\n", e);
        printf("So lan lap: %d\n", l);
    }

    return 0;
}

double f(int n, double x)
{
    double f = 0;

    for (int i = 0; i <= n; i++)
    {
        f = f + pow(x, i) * numbers[i];
    }

    return f;
}

double f1(int n, double x)
{
    double f1 = 0;

    for (int i = 0; i <= n; i++)
    {
        f1 = f1 + pow(x, i - 1) * i * numbers[i];
    }

    return f1;
}

double f2(int n, double x)
{
    double f2 = 0;

    for (int i = 0; i <= n; i++)
    {
        f2 = f2 + pow(x, i - 2) * i * (i - 1) * numbers[i];
    }

    return f2;
}

int CheckConditions(int n, double a, double b)
{
    int sign = f1(n, a) >= 0;
    
    for (double i = a; i <= b; i += 0.01)
    {
        if (sign != f1(n, i) >= 0)
        {
            printf("Khong thoa man dieu kien hoi tu Furie (f' doi dau tren khoang phan ly)\n");
            
            return 1;
        }
    }

    sign = f2(n, a) >= 0;

    for (double i = a; i <= b; i += 0.01)
    {
        if (sign != f2(n, i) >= 0)
        {
            printf("Khong thoa man dieu kien hoi tu Furie (f'' doi dau tren khoang phan ly)\n");
            
            return 1;
        }
    }

    return f(n, a) * f2(n, a) > 0 ? 2 : f(n, b) * f2(n, b) > 0 ? 3 : 0; 
}

void newton(int n, double epsilon, double x0, double a, double b, double *x, double *e, int *l, int max)
{
    *x = x0;
    *l = 0;
    *e = 9999;

    while ((*e > epsilon) && (*l < max) && (*x <= b && *x >= a))
    {
        double newValue = *x - (f(n, *x) / f1(n, *x));
        *e = fabs(newValue - *x);
        *l += 1;
        *x = newValue; 

        printf("|%-9d|%-15lf|%-8lf|\n", *l, *x, *e);
        printf("|---------|---------------|--------|\n");
    }
}
