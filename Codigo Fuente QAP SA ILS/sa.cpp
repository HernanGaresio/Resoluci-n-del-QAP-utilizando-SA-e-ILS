#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "libreriasqap.h"

using namespace std;

int ** Locations, ** Facilities;
long int mejorCosto;
float tempMejSol;
int *Smejor;
long int cantEvaluaciones=0, EvalMejorSol=0;
unsigned int clockMejorSol=0;


int leerInstancia(char * filename, int *Nro)
{
	char string [256];
	int fil, col;
	
	ifstream file(filename);
	if(!file) return -1;
	file >> *Nro;
	Locations = new int*[*Nro];
	for(unsigned int i = 0; i < *Nro; ++i)
	{
		Locations[i] = new int[*Nro];
		for(unsigned int j = 0; j < *Nro; ++j)
		{
			file >> Locations[i][j];
		}
	}
	
	Facilities = new int*[*Nro];
	for(unsigned int i = 0; i < *Nro; ++i)
	{
		Facilities[i] = new int[*Nro];
		for(unsigned int j = 0; j < *Nro; ++j)
		{
			file>>Facilities[i][j];
		}
	}
	return 0;
}


void mostrarMatrices(int *N){
	getchar();
	cout<<"Matriz Locaciones"<<endl;
	for(int fil = 0; fil < *N; fil++)
	{
		for(int col = 0; col < *N; col++)
		{
			cout<<Locations[fil][col]<<"  ";
		}
		cout<<endl;
	}
	
	getchar();
	cout<<"Matriz Facilities"<<endl;
	for(int fil = 0; fil < *N; fil++)
	{
		for(int col = 0; col < *N; col++)
		{
			cout<<Facilities[fil][col]<<"\t";
		}
		cout<<endl;
	}
	getchar();
}


long int evaluarCosto(int *N, int *Sol)
{
	long int costo=0;
	for(int i = 0; i < *N; i++)
	{
		for(int j = 0;j < *N; j++)
		{	
			costo += Locations[i][j]*Facilities[Sol[i]-1][Sol[j]-1];
		}
	}
	cout<<costo<<" "<<endl;
	cantEvaluaciones++;
	return costo;
}

int recocidoSimulado(int N, float tempInicial,int L,float tempFinal, unsigned int *clockMejorSol)
{
	
	float tempActual=tempInicial;
	int cpeorDelta0=0,contPeorSol=0, iter=1;
	
	long int delta, costoCand, costoActual;
	double randNumero;
	int *Sact, *Scand;
	
	EvalMejorSol=0;
	cantEvaluaciones=0;
	
	//***********************Comienza Simulated Annealling**********************************//
	Scand = new int[N];
	Sact = new int[N];
	Smejor = new int[N];

	solucionInicial(&N, Sact);
	mejorCosto = evaluarCosto(&N, Sact);
	copiarSol(&N,Sact,Smejor);
	while(tempActual >= tempFinal)
	{
		for(int i=0;i<L;i++)
		{
			copiarSol(&N,Sact,Scand);
			intercambiaRandom(&N, Scand);
			//insert(&N, Scand);
			//invert(&N, Scand);
			costoActual=evaluarCosto(&N,Sact);
			costoCand=evaluarCosto(&N,Scand);	
			delta = costoCand-costoActual;
			randNumero= generateDoubleRandomNumber();
			if(delta<=0)
			{
				copiarSol(&N,Scand,Sact);
				if(costoCand<mejorCosto)//actualizamos variables globales estadisticas
				{
					mejorCosto=costoCand;
					copiarSol(&N,Scand,Smejor);
					tempMejSol=tempActual;
					*clockMejorSol = clock();
					EvalMejorSol = cantEvaluaciones;
				}
			}
			else 	if (randNumero<exp(((-1*(double)delta))/(double)tempActual))
					{
						copiarSol(&N,Scand,Sact);
						contPeorSol++;
					}
		}
		iter++;
		tempActual=tempActual-1;
	}
	return 0;
}

int main(int argc, char * argv[])
{
	double tiempoTotal, tiempoMejorSol;
	unsigned int clockInicial=0, clockFinal=0, clockMejorSol=0;
	
	float tempInicial = atof(argv[2]), tempFinal = atof(argv[4]);
	int L=atoi(argv[3]), N, lectura;
	char * nombreInstancia = argv[1];

	lectura = leerInstancia(nombreInstancia, &N);
	if(lectura==-1)
	{
		cout<<"Error al leer el archivo de instancia"<<endl;
		return -1;
	}
	//***********************BUCLE**********************************//
		tiempoTotal = 0;
		tiempoMejorSol = 0;
		tempMejSol = 0;
		clockInicial=clock();
		recocidoSimulado(N,tempInicial, L, tempFinal,&clockMejorSol);
		clockFinal=clock();
		tiempoTotal = (double(clockFinal-clockInicial)/CLOCKS_PER_SEC);
		tiempoMejorSol = (double(clockMejorSol-clockInicial)/CLOCKS_PER_SEC);
		guardaSTATSSA(nombreInstancia, tempInicial, tempFinal, tiempoTotal, tiempoMejorSol, cantEvaluaciones, EvalMejorSol, mejorCosto, tempMejSol,Smejor, N);
	//*********************************************************//
	return 0;
}