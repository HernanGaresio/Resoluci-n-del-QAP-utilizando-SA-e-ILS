#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "libreriasqap.h"

using namespace std;

int ** Locations, ** Facilities;
long int mejorCostoLocal,mejorCostoGlobal;

long int cantEvaluaciones=0, EvalMejorSol=0;

int *Smejor, *SmejorGlobal;
unsigned long long int clockMejorSol=0;



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
	cantEvaluaciones++;
	return costo;
}

void busquedaLocal (int *N, int *Sact)
{
	int *Scand;
	int *Smejor;
	Scand = new int[*N];
	Smejor = new int[*N];
	int mejorCostoLocal=evaluarCosto(N, Sact);
	copiarSol(N,Sact,Scand);
	copiarSol(N,Sact,Smejor);
	int cantVecinos=0, nroVecino=0, cantDeVecindarios=0, sumaVector=0;
	long int costoCand;
	bool hayMejorSol=true;
	while(hayMejorSol)
	{	
		hayMejorSol=false;
		for(int j = 0;j<*N-1;j++)
		{
			for(int k = j+1;k<*N;k++)
			{
				Scand[j]=Sact[k];
				Scand[k]=Sact[j];
				costoCand=evaluarCosto(N,Scand);
				cantVecinos++;
				if(costoCand<mejorCostoLocal)
					{
						copiarSol(N,Scand,Smejor);
						mejorCostoLocal=costoCand;
						nroVecino=cantVecinos;
						hayMejorSol=true;
						if(mejorCostoLocal<mejorCostoGlobal)
						{
							copiarSol(N,Scand,SmejorGlobal);
							mejorCostoGlobal=mejorCostoLocal;
							clockMejorSol = clock();
							EvalMejorSol = cantEvaluaciones;
						}
					}
				copiarSol(N,Sact,Scand);
			}
		}
		copiarSol(N,Smejor,Sact);
		copiarSol(N,Smejor,Scand);
		cantDeVecindarios++;
	}
	
	delete [] Scand;
	delete [] Smejor;
}	

void busquedaLocalIterada (int N, int cantIteracionesTotales)
{
	int * Sact, cantIteraciones=0;
	
	cantEvaluaciones=0;
	Sact = new int[N];
	SmejorGlobal = new int[N];
	
	solucionInicial(&N, Sact);

	mejorCostoGlobal = evaluarCosto(&N, Sact);
	copiarSol(&N,Sact,SmejorGlobal);
	busquedaLocal(&N,Sact);
	
	while(cantIteraciones<cantIteracionesTotales)
	{
		insert(&N,Sact);	//METODO DE PERTURBACION
		insert(&N,Sact);	//Se llama 2 veces para hacer una mayor perturbacion de la solucion.
		busquedaLocal(&N,Sact);
		cantIteraciones++;
	}
}


int main(int argc, char * argv[])
{
	double tiempoTotal, tiempoMejorSol;
	unsigned long long int clockInicial=0, clockFinal=0;
	int N, lectura, cantIteracionesTotales=atoi(argv[2]);
	char * nombreInstancia = argv[1];
	double randNumero;
	lectura = leerInstancia(nombreInstancia, &N);
	if(lectura==-1)
	{
		cout<<"Error al leer el archivo"<<endl;
		return -1;
	}
		clockInicial=clock();
		busquedaLocalIterada(N,cantIteracionesTotales);
		clockFinal=clock();
		mejorCostoGlobal=evaluarCosto(&N,SmejorGlobal);
		tiempoTotal = (double(clockFinal-clockInicial)/CLOCKS_PER_SEC);
		tiempoMejorSol = (double(clockMejorSol-clockInicial)/CLOCKS_PER_SEC);
		guardaSTATSILS(nombreInstancia, cantIteracionesTotales, tiempoTotal, tiempoMejorSol, cantEvaluaciones, EvalMejorSol, mejorCostoGlobal, SmejorGlobal, &N);
	return 0;
}