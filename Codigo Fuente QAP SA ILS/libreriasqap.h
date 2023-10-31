#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;


double generateDoubleRandomNumber() /* Genera un número aleatorio entre [0, 1) */
{
	return ((double)rand() / ((double)(RAND_MAX)+(double)(1)));
}

int rand_int(int min, int max)
{
	int r;
	double randd = ((double)rand() / ((double)(RAND_MAX)+(double)(1)));
	r = (int) (randd * (double)(max-min+1)) + min;
	return r;
}

void solucionInicial(int *N, int *Sact)
{
	int * randNum = new int[*N];
	srand (time(NULL)); /* para inicializar con una semilla el random*/
	for(int k = 0; k < *N; k++)
	{
		int num = rand_int(0, *N * 10);
		randNum[k] = num;
		Sact[k] = k+1;
	}
	
	// ordena para lograr el vector solucion
	for(int i = 0; i < *N-1; i++)
	{
		for(int j = i+1; j < *N; j++)
		{
			if( randNum[i] > randNum[j])
			{
				int temp = randNum[i];
				randNum[i] = randNum[j];
				randNum[j] = temp;

				temp = Sact[i];
				Sact[i] = Sact[j];
				Sact[j] = temp;
			}
		}
	}
	delete [] randNum;
}

void mostrarSolucion (int *N, int *Sol){
	cout<<"Sol: "<<endl;
	for(int pos = 0; pos < *N; pos++){
		cout<<Sol[pos]<<"  ";
	}
	cout<<endl;
}

//COPIA la solucion actual en la candidata
void copiarSol(int *N, int *SolOrigen, int *SolDestino)
{
	for(int i=0; i<*N; i++)
		SolDestino[i]=SolOrigen[i];
	return;
}

void intercambiaRandom(int *N, int *Sol) //intercambia 2 valores random del vector solucion
{
	/*Ejemplo: Para el vector {0,1,2,3,4,5} con num_aleatorio1= 1 y num_aleatorio2= 4 devuelve: {0,4,2,3,1,5}*/
	int num_aleatorio1=0, num_aleatorio2=0;
	num_aleatorio1= rand_int(0,*N-1);
	do
	{		
		num_aleatorio2 = rand_int(0,*N-1);
	}while (num_aleatorio1==num_aleatorio2);	
	int temp=Sol[num_aleatorio1];
	Sol[num_aleatorio1]=Sol[num_aleatorio2];
	Sol[num_aleatorio2]=temp;
	
}

void invert(int *N, int *s) //operador de inversion - Permutaciones
{
	/*Ejemplo: Para el vector {0,1,2,3,4,5} con num_aleatorio1= 1 y num_aleatorio2= 4 devuelve: {0,5,4,3,2,1}*/
	int num_aleatorio1=0, num_aleatorio2=0;
	num_aleatorio1= rand_int(0,*N-2);
	num_aleatorio2 = rand_int(num_aleatorio1+1,*N-1);	
	while(num_aleatorio1 < num_aleatorio2)
	{
		int temp = s[num_aleatorio1];
		s[num_aleatorio1] = s[num_aleatorio2];
		s[num_aleatorio2] = temp;
		num_aleatorio1++;
		num_aleatorio2--;
	}	
}

void insert(int *N, int *s) //operador de inserción - Permutaciones
{
	/*Ejemplo: Para el vector {0,1,2,3,4,5} con num_aleatorio1= 1 y num_aleatorio2= 4 devuelve: {0,4,1,2,3,5}*/
	int num_aleatorio1=0, num_aleatorio2=0;
	num_aleatorio1= rand_int(0,*N-2);
	num_aleatorio2 = rand_int(num_aleatorio1+1,*N-1);	
	int temp = s[num_aleatorio1];
	s[num_aleatorio1]=s[num_aleatorio2];
	for(int h=num_aleatorio1+1; h<=num_aleatorio2; h++)
	{
		int temp1=s[h];
		s[h] = temp;
		temp = temp1;
	}
}



void guardaSTATSILS( string nombre_instancia, int cantIteracionesTotales,double tiempoTotal, double tiempoMejorSol, long int cantEvaluaciones, long int EvalMejorSol, long int costoMejorSol, int *solucion, int *N)
{
	cout << nombre_instancia << "\t";
	cout << cantIteracionesTotales<< "\t";
	cout << tiempoTotal << "\t";
	cout << tiempoMejorSol << "\t";
	cout << cantEvaluaciones << "\t";
	cout << EvalMejorSol << "\t";
	cout << costoMejorSol << "\t";
	for(int pos = 0; pos < *N; pos++){
		cout<<solucion[pos]<<"  ";
	}
	cout<<endl;

}

void guardaSTATSSA(string nombre_instancia, float tempInicial, float tempFinal, double tiempoTotal, double tiempoMejorSol, long int cantEvaluaciones, long int EvalMejorSol, long int costoMejorSol,long int tempMejorSol, int *solucion, int N)
{
	cout << nombre_instancia << "\t";
	cout << tempInicial << "\t";
	cout << tempFinal << "\t";
	cout << tiempoTotal << "\t";
	cout << tiempoMejorSol << "\t";
	cout << cantEvaluaciones << "\t";
	cout << EvalMejorSol << "\t";
	cout << costoMejorSol << "\t";
	cout << tempMejorSol << "\t";
	
	for(int pos = 0; pos < N; pos++){
		cout<<solucion[pos]<<"  ";
	}
	
	cout << endl;

}