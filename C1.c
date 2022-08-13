#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double silnia (unsigned n)
{
	double s=1.0;
	int i;
	for(i=2; i<=n;i++)
		s*=i;
	return s;
}

double symbolNewtona (unsigned n, unsigned k)
{
	return (silnia(n))/(silnia(k)*silnia(n-k)); 
}
double fL(double a, double b, unsigned n)
{
    return pow((a+b) , n);
}
double fP(double a, double b, unsigned n)
{
    double suma = 0;
    for(int k = 0; k<=n ; k++)
        suma += symbolNewtona(n, k) * pow(a, (n-k)) * pow(b, k);

    return suma;
}
    void main1()
{
    int n;
    double a,b;
        printf("Podaj liczbe a: ");
        scanf("%lg" , &a);
        printf("Podaj liczbe b: ");
        scanf("%lg" , &b);
        printf("Podaj liczbe n: ");
        scanf("%d" , &n);
    double L = fL(a, b, n);
    double P = fP(a, b, n);

    printf("L = %g ; P = %g\n", L , P);
}
int rkw(double a, double b, double c, double x[2])
{
	double delta = (b*b)-4*a*c;
	if(delta < 0){
		return 0;
	}
	else if(delta == 0){
		x[0] = -b/(2*a);
		return 1;
	}
	else{
		x[0] = (-b-sqrt(delta))/(2*a);
		x[1] = (-b+sqrt(delta))/(2*a);
		return 2;
	}
}
void check1(double a, double b, double c, double x[2])
{
	double d,f;
	double delta = (b*b)-4*a*c; 
	if (delta<0)
		printf("brak miejsc zerowych!\n");
	else
	{	
		if(delta==0)
		{
			d=((a*x[0]*x[0])+(b*x[0])+c);
			printf("reszta x1 = %lg (POWINNY BYC BLISKIE LUB ROWNE ZERU)\n",d);
			return;
		}
		else
		{
			d=((a*x[0]*x[0])+(b*x[0])+c);
			f=((a*x[1]*x[1])+(b*x[1])+c);
			printf("Reszta x1 = %lg , Reszta x2 = %lg (POWINNY BYC BLISKIE LUB ROWNE ZERU)\n",d,f);
			return;
		}		
	}	
}
void main2()
{
	double a, b, c;
	printf("Wypisz równanie ax^2+bx+c\n");
	scanf("%lfx^2 %lfx %lf", &a, &b, &c);
	double x[2];
	int WynikReturn = rkw(a, b, c, x);
	if(WynikReturn == 0){
		printf("Rownanie (%g)x^2+(%g)x+(%g) nie ma rozwiazania\n", a, b, c);
	}
	if(WynikReturn == 1){
		printf("Rownanie (%g)x^2+(%g)x+(%g) ma jendo rozwiazanie: x=(%g)\n", a, b, c, x[0]);
	}
	if(WynikReturn == 2){
		printf("Rownanie (%g)x^2+(%g)x+(%g) ma dwa rozwiazania: x1=(%g) i x2=(%g)\n", a, b, c, x[0], x[1]);
	}
	check1(a,b,c,x);
}
	int det2(double a[2][2])
{
	return a[0][0]*a[1][1] - a[0][1]*a[1][0];
}
	int ukl2(double a[][2], double b[], double x[])
	{
		{
		double W = det2(a);
		double tempX[2][2] = {b[0] , a[0][1] , b[1] , a[1][1]};
		double Wx = det2(tempX);
		double tempY[2][2] = {a[0][0] , b[0] , a[1][0] , b[1]};
		double Wy = det2(tempY);
		
		if(W == 0){
			if(Wx == 0 && Wy == 0){
				return 1;
			}else{
				return 2;
			}
		}
		x[0] = Wx/W;
		x[1] = Wy/W;
		return 3;
	}
}
	void check3(double a[][2], double b[], double x[], double r[])
{
	if(ukl2(a,b,x)==3)
	{
		r[0]= (a[0][0]*x[0]+a[0][1]*x[1])-b[0];
		r[1]= (a[1][0]*x[0]+a[1][1]*x[1])-b[1];
		printf("FUNKCJA SPRAWDZAJACA (powinny byc dwie liczby bliskie lub równe zeru) : %lg i %lg\n",r[0],r[1]);
	}
}
void main3()
{
	printf("Podaj wspólczynnik A, B, C, D, E, F ukladu rownan:\nAx+By=C\nDx+Ey=F\n");
	double a[2][2];
	double b[2];
	double r[2];
	scanf("%lgx %lgy=%lg", &a[0][0], &a[0][1], &b[0]);
	scanf("%lgx %lgy=%lg", &a[1][0], &a[1][1], &b[1]);
	double x[2];
	int zwrot = ukl2(a,b,x);
	printf("\nUklad (%lg)x+(%lg)y=(%lg) i (%lg)x+(%lg)y=(%lg)\n",a[0][0], a[0][1], b[0], a[1][0], a[1][1], b[1]);
	if(zwrot == 1)
	{
		printf("Jest nieskonczenie wiele rozwiazan\n");
		return;
	}else if(zwrot == 2)
	{
		printf("uklad jest sprzeczny\n");
		return;
	}else(zwrot == 3);
	{
		printf("Ma rozwiazanie x = %lg i y = %lg\n", x[0], x[1]);
	}
	check3(a,b,x,r);
}
double det3(double a[3][3])
{
	return a[0][0]*a[1][1]*a[2][2]+a[0][1]*a[1][2]*a[2][0]+a[0][2]*a[1][0]*a[2][1]-a[0][2]*a[1][1]*a[2][0]-a[0][0]*a[1][2]*a[2][1]-a[0][1]*a[1][0]*a[2][2];
}
void arrCopy(double a[][3], double b[][3])
{
	int i, j;
	for(i = 0; i<3; i++)
		for(j = 0; j<3; j++)
			b[i][j] = a[i][j];
}
int uklad3(double a[3][3], double b[3], double x[3])
{
	double W = det3(a);
	if(W == 0)
		return 2;
		
	double tempX[3][3];
	double tempY[3][3];
	double tempZ[3][3];
	arrCopy(a, tempX);
	arrCopy(a, tempY);
	arrCopy(a, tempZ);
	int i;
	for(i = 0; i<3; i++)
		tempX[i][0] = tempY[i][1] = tempZ[i][2] = b[i];
	
	double Wx = det3(tempX);
	double Wy = det3(tempY);
	double Wz = det3(tempZ);
	
	printf("W = %g , Wx = %g , Wy = %g , Wz = %g\n",W,Wx,Wy,Wz);
	x[0] = Wx/W;
	x[1] = Wy/W;
	x[2] = Wz/W;
	return 1;
}
void check6(double a[][3], double b[3], double x[3], double r[3])
{
	int i;
	for(i = 0; i<=2; i++)
	{
		r[i]=a[i][0]*x[0]+a[i][1]*x[1]+a[i][2]*x[2]-b[i];
	}
}	
void main4()
{
double a[3][3];
double b[3]; 
double x[3];
double r[3];
printf("podaj uklad rownan postaci:\n");
printf("a11*x+a12*y+a13*z=b1\n");
printf("a21*x+a22*y+a23*z=b2\n");
printf("a31*x+a32*y+a33*z=b3\n");
scanf("%lgx %lgy %lgz=%lg",&a[0][0],&a[0][1],&a[0][2],&b[0]);
scanf("%lgx %lgy %lgz=%lg",&a[1][0],&a[1][1],&a[1][2],&b[1]);
scanf("%lgx %lgy %lgz=%lg",&a[2][0],&a[2][1],&a[2][2],&b[2]);
	if(uklad3(a,b,x)==1)
	{
		printf("uklad ma jedno rozwiazanie\n x= %lg\n y= %lg\n z= %lg\n", x[0], x[1], x[2]);
		printf("SPRAWDZANIE\n");
		check6(a,b,x,r);
		printf("r1 = %g, r2 = %g, r3 = %g (MAJA BYC BLISKIE ALBO ROWNE 0)\n",r[0], r[1], r[2]);
		return;
	}else if(uklad3(a,b,x)==2);
	{
		printf("uklad nie ma rozwiazan lub ma ich nieskonczenie wiele\n");
		return;
	}
}
char menu()
{
	printf("=======================\n");
	printf("|1.Dwumian Newtona    |\n");
	printf("|2.Rownanie kwadratowe|\n");
	printf("|3.Uklad 2x2          |\n");
	printf("|4.Uklad 3x3          |\n");
	printf("|5.Koniec programu    |\n");
	printf("=======================\n");
	
	char c;
	printf("Wybierz opcje: ");
	scanf("%s",&c);
	return c;
}

int main()
{
	while(1)
	switch (menu())
	{	
		case '1':
		printf("Wybrano dwumian Newtona \n");
		main1();
		break;
		
		case '2':
		printf("Wybrano rownanie kwadratowe \n");
		main2();
		break;
		
		case '3':
		printf("Wybrano uklad 2x2 \n");
		main3();
		break;
		
		case '4':
		printf("Wybrano uklad 3x3 \n");
		main4();
		break;
		
		case '5':
		printf("Wybrano koniec programu \n");
		exit(0);
		
		default:
		printf("==Nie ma takiej opcji==\n");
	}
	return 0;
}