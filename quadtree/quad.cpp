#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

template<class T> //coordenadas
struct Punto {
	T x;
	T y;
	Punto() {
		x = 0;
		y = 0;
	}
	Punto(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

template<class T >
struct Nodo {
	Punto<T> IzquierdaSup, DerechaInf;
	vector<Punto<T>> puntos;
	Nodo() {
		IzquierdaSup = NULL;
		DerechaInf = NULL;
	}
	Nodo(Punto<T> IzquierdaSup, Punto<T> DerechaInf) {
		this->IzquierdaSup = IzquierdaSup;
		this->DerechaInf = DerechaInf;
	}
};

template<class T>
class QuadTree {
	int profundidad;
	int n;
	vector<Punto<T>> puntos;
	Punto<T> LimiteIzquierdoSup;
	Punto<T> LimiteDerechoInf;
	QuadTree* DivisionIzquierdaSupe;
	QuadTree* DivisionDerechaSupe;
	QuadTree* DivisionIzquierdaInf;
	QuadTree* DivisionDerechaInf;
	
public:
	void insert(Punto<T>,int);
	void search(Punto<T>,int);
	bool check(Punto<T>);
	
	QuadTree() {
		n = 0;
		LimiteIzquierdoSup = Punto<T>(0, 0);
		LimiteDerechoInf = Punto<T>(0, 0);
		puntos = NULL;
		DivisionIzquierdaSupe = NULL;
		DivisionDerechaSupe = NULL;
		DivisionIzquierdaInf = NULL;
		DivisionDerechaInf = NULL;
		profundidad = 0;
	}
	QuadTree(Punto<T> LimiteIzquierdoSup, Punto<T>  LimiteDerechoInf, int profundidad) {
		
		n = 0;
		DivisionIzquierdaSupe = NULL;
		DivisionDerechaSupe = NULL;
		DivisionIzquierdaInf = NULL;
		DivisionDerechaInf = NULL;
		this->LimiteIzquierdoSup = LimiteIzquierdoSup;
		this->LimiteDerechoInf = LimiteDerechoInf;
		this->profundidad = profundidad;
		
		if (profundidad <= 0) {
			return;
		}
		DivisionIzquierdaSupe = new QuadTree(LimiteIzquierdoSup,Punto<T>((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2.0,(LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2.0), profundidad-1);
		DivisionDerechaSupe = new QuadTree(Punto<T>((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2.0, LimiteIzquierdoSup.y), Punto<T>(LimiteDerechoInf.x, (LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2.0), profundidad - 1);
		DivisionIzquierdaInf = new QuadTree(Punto<T>(LimiteIzquierdoSup.x , (LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2.0), Punto<T>((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2.0,  LimiteDerechoInf.y), profundidad - 1);
		DivisionDerechaInf = new QuadTree(Punto<T>((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2.0, (LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2.0), LimiteDerechoInf, profundidad - 1);
		//cout << "profundidad: " << profundidad << endl;
	}
};




template<class T>
bool QuadTree<T>::check(Punto<T> p){
	for (int i = 0; i < n; i++) {
		if (puntos[i].x == p.x && puntos[i].y == p.y) return 1;
	}
	return 0;
}

template<class T>
void QuadTree<T>::insert(Punto<T> p, int prof) {
	if (prof <= 0) {
		puntos.push_back(p);
		n++;
		cout << "inserto en el cuadrante: " << LimiteIzquierdoSup.x << ", " << LimiteIzquierdoSup.y << " y " << LimiteDerechoInf.x << ", " << LimiteDerechoInf.y << endl;
		return;
	}
	
	if ((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2 <= p.x) {
		if ((LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2 <= p.y) {
			return DivisionDerechaSupe->insert(p, prof - 1);
		}
		
		else {
			return DivisionDerechaInf->insert(p, prof - 1);
		}
	}
	else {
		if ((LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2 <= p.y) {
			return DivisionIzquierdaSupe->insert(p, prof - 1);
		}
		
		else {
			return DivisionIzquierdaInf->insert(p, prof - 1);
		}
	}
}


template<class T>
void QuadTree<T>::search(Punto<T> p,int prof) {
	if (prof <= 0) {
		if (check(p)) {
			cout << "El punto: " << p.x <<","<< p.y << " si esta" << endl;
			cout << "Lim Sup Izquierdo: " << LimiteIzquierdoSup.x << ", " << LimiteIzquierdoSup.y << endl;
			cout << "Lim Inf Derecho: " << LimiteDerechoInf.x << ", " << LimiteDerechoInf.y << endl;
		}
		else cout << "El punto: "<< p.x << p.y <<" NO se encuentra el punto" << endl;
		return;
	}
	if ((LimiteIzquierdoSup.x + LimiteDerechoInf.x) / 2 <= p.x) {
		if ((LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2 <= p.y) {
			return DivisionDerechaSupe->search(p, prof - 1);
		}
		
		else {
			return DivisionDerechaInf->search(p, prof - 1);
		}
	}
	else {
		if ((LimiteIzquierdoSup.y + LimiteDerechoInf.y) / 2 <= p.y) {
			return DivisionIzquierdaSupe->search(p, prof - 1);
		}
		
		else {
			return DivisionIzquierdaInf->search(p, prof - 1);
		}
	}
}



int main() {
	int profundidad = 2;
	Punto<double> limiteSupIzquierdo(-200.0, 100.0);
	Punto<double> limiteInfDerecho(200.0, -100.0);
	
	QuadTree<double> quad(limiteSupIzquierdo, limiteInfDerecho, profundidad);
	
	quad.insert(Punto<double>(2.0, 2.0), profundidad);
	
	
	
	double num = 0.0;
	double x, y;
	quad.search(Punto<double>(1.0, 1.0), 1);
	
	
	
	
	return 0;
}
