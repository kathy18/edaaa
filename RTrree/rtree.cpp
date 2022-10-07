#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iterator>

#define INF 1024

typedef std::pair<int, int> par_int;
typedef std::vector<int> vec_int;
typedef std::vector<par_int> vec_par_int;

using namespace std;

class Nodo
{
    vec_par_int pts;
    std::vector<Nodo*> hijos;

    int M, m, Cant = 0;
    vec_int LimiteX;
    vec_int LimiteY;

    bool es_hoja;
    bool es_padre;
    bool isTheRoot = false;
public:
    Nodo* padre = 0;//nullptr;
    Nodo(int M, vec_int Lx, vec_int Ly);
    Nodo();
    ~Nodo();

    void cambiarIzquierda(bool);
    void cambiarM(int m);
    void cambiar_padre(bool);
    void cambiarLimite(std::size_t i, par_int ps);

    void añadir_limite(par_int li);
    void añadir_punto(par_int p);
    void añadir_hijo(Nodo*& x);

    void obtener_padre(Nodo& pa);
    void doRoot();
    void dismiss();

    int obtener_cantidad();
    int getM();
    int getm();
    par_int obtener_punto(int i);
    Nodo* obtener_hijo(int i);
    Nodo* obtener_Parent();
    par_int getLimite(std::size_t i);
    vec_par_int obtner_todos_pts();
    std::vector<Nodo*> getAllChilds();

    int areaEnlarged(par_int p);
    int areaEnlarged(Nodo* n);

    void removePoint(int i);
    void removeChild(int i);
    void clean();

    bool knowIsLeaf();
    bool knowIsParent();
    bool knowIsTheRoot();

    void Reajustar();
    void Ajustar();

};

Nodo::Nodo(int M, vec_int Lx, vec_int Ly) {
    this->M = M;
    this->m = std::ceil((double)M / 2);
    this->LimiteX = Lx;
    this->LimiteY = Ly;
    this->es_hoja = this->es_padre = false;
}

Nodo::Nodo() {
    this->M = 0;
    this->m = 0;
    this->es_hoja = this->es_padre = false;
}

Nodo::~Nodo() {
    this->pts.clear();
    this->hijos.clear();
}

void Nodo::cambiarIzquierda(bool b) {
    this->es_hoja = b;
}

void Nodo::cambiar_padre(bool b) {
    this->es_padre = b;
}

void Nodo::cambiarLimite(std::size_t i, par_int ps) {
    std::size_t sizeLimite = this->LimiteX.size();
    if (i >= sizeLimite)
        return;
    this->LimiteX[i] = ps.first;
    this->LimiteY[i] = ps.second;
}

void Nodo::añadir_limite(par_int li) {
    this->LimiteX.push_back(li.first);
    this->LimiteY.push_back(li.second);
}

void Nodo::añadir_punto(par_int p) {
    this->pts.push_back(p);
    this->Cant = this->Cant + 1;
    this->Ajustar();
}

void Nodo::añadir_hijo(Nodo*& x) {
    //x->setParent(*this);
    x->padre = this;
    this->hijos.push_back(x);
    this->Cant = this->Cant + 1;
    if (this->isTheRoot)return;
    this->Reajustar();
}

void Nodo::obtener_padre(Nodo& pa) {
    *(this->padre) = pa;
}

void Nodo::doRoot() {
    this->isTheRoot = true;
}

void Nodo::dismiss() {
    this->isTheRoot = false;
}

int Nodo::obtener_cantidad() {
    return this->Cant;
}

int Nodo::getM() {
    return this->M;
}

int Nodo::getm() {
    return this->m;
}

par_int Nodo::obtener_punto(int i) {
    if (i > this->Cant)
        return std::make_pair(INF, INF);
    return this->pts[i];
}

Nodo* Nodo::obtener_hijo(int i) {
    if (i >= this->Cant)
        return 0;
    return this->hijos[i];
}

par_int Nodo::getLimite(std::size_t i) {
    std::size_t sizeLimite = this->LimiteX.size();
    if (i > sizeLimite)
        return std::make_pair(INF, INF);
    return std::make_pair(this->LimiteX[i], this->LimiteY[i]);
}

void Nodo::removePoint(int i) {
    if (i >= this->Cant)
        return;
    this->pts.erase(this->pts.begin() + i);
    this->Cant = this->Cant - 1;
}

void Nodo::removeChild(int i) {
    if (i >= this->Cant)
        return;
    this->hijos.erase(this->hijos.begin() + i);
    this->Cant = this->Cant - 1;
}

bool Nodo::knowIsLeaf() {
    return this->es_hoja;
}

bool Nodo::knowIsParent() {
    return this->es_padre;
}

bool Nodo::knowIsTheRoot() {
    return this->isTheRoot;
}

vec_par_int Nodo::obtner_todos_pts() {
    return this->pts;
}

std::vector<Nodo*> Nodo::getAllChilds() {
    return this->hijos;
}

void Nodo::clean() {
    this->hijos.clear();
    this->pts.clear();
    this->Cant = 0;
}

int Nodo::areaEnlarged(par_int punto) {
    int x = this->LimiteX[0], y = this->LimiteY[0];
    int X = this->LimiteX[1], Y = this->LimiteY[1];

    int areaR = std::abs(X - x) * std::abs(Y - y);

    if (punto.first >= X)
        X = punto.first;
    else if (punto.first <= x)
        x = punto.first;

    if (punto.second >= Y)
        Y = punto.second;
    else if (punto.second <= y)
        y = punto.second;

    int areaRp = std::abs(X - x) * std::abs(Y - y);
    return areaRp - areaR;
}

int Nodo::areaEnlarged(Nodo* nodin) {
    int x = this->LimiteX[0], y = this->LimiteY[0];
    int X = this->LimiteX[1], Y = this->LimiteY[1];

    par_int n = nodin->getLimite(0), N = nodin->getLimite(1);
    int areaR = std::abs(X - x) * std::abs(Y - y);

    if (N.first >= X)
        X = N.first;
    else if (n.first <= x)
        x = n.first;

    if (N.second >= Y)
        Y = N.second;
    else if (n.second <= y)
        y = n.second;

    int areaRp = std::abs(X - x) * std::abs(Y - y);
    return areaRp - areaR;
}

void Nodo::Reajustar() {
    if (this->es_hoja)return;
    par_int r, R, aux;
    r = this->hijos[0]->getLimite(0);
    R = this->hijos[0]->getLimite(1);
    for (int i = 1; i < this->Cant; ++i) {
        aux = this->hijos[i]->getLimite(0);
        if (aux.first < r.first)
            r.first = aux.first;
        if (aux.second < r.second)
            r.second = aux.second;
        aux = this->hijos[i]->getLimite(1);
        if (aux.first > R.first)
            R.first = aux.first;
        if (aux.second > R.second)
            R.second = aux.second;
    }
    this->LimiteX.clear();
    this->LimiteY.clear();
    this->añadir_limite(r);
    this->añadir_limite(R);
}

void Nodo::Ajustar() {
    if (this->isTheRoot || this->es_padre) return;
    int x = INF, X = -1000;
    int y = INF, Y = -1000;
    int px, py;
    for (int i = 0; i < this->Cant; ++i) {
        px = this->pts[i].first;
        py = this->pts[i].second;
        if (px < x) x = px;
        if (px > X) X = px;
        if (py < y) y = py;
        if (py > Y) Y = py;
    }
    this->LimiteX.clear();
    this->LimiteY.clear();
    this->añadir_limite(std::make_pair(x, y));
    this->añadir_limite(std::make_pair(X, Y));
}

void Nodo::cambiarM(int m) {
    this->M = m;
    this->m = std::ceil((double)m / 2);
}

Nodo* Nodo::obtener_Parent() {
    return this->padre;
}

typedef std::vector<Nodo*> vec_pnodo;

class Rtree
{
    Nodo* root;

    Nodo* Choose(Nodo*& R, par_int& punto);
    Nodo* SplitLeaf(Nodo*& R);
    Nodo* SplitNode(Nodo*& R);
    Nodo* AdjusTree(Nodo*& R, Nodo*& RR);

    void PickSeed_toPoints(vec_par_int& Puntos, Nodo*& GroupA, Nodo*& GroupB);
    par_int PickNext_toPoints(vec_par_int& Puntos, Nodo*& GroupA, Nodo*& GroupB);

    void PickSeed_toRegion(vec_pnodo& Regiones, Nodo*& GroupA, Nodo*& GroupB);
    Nodo* PickNext_toRegion(vec_pnodo& Regiones, Nodo*& GroupA, Nodo*& GroupB);

public:
    Rtree();
    Rtree(int M, int x, int X, int y, int Y);
    ~Rtree();

    void inertar(par_int x);
    
 
};

Rtree::Rtree() {
    this->root = 0;
}

Rtree::Rtree(int M, int x, int X, int y, int Y) {
    vec_int Xs = { x , X };
    vec_int Ys = { y , Y };
    this->root = new Nodo(M, Xs, Ys);
    this->root->doRoot();
    this->root->cambiarIzquierda(1);
}

Rtree::~Rtree() {
    this->root->~Nodo();
}

void Rtree::inertar(par_int x) {
    par_int l = this->root->getLimite(0);
    par_int L = this->root->getLimite(1);
    Nodo* Rptr = this->root;
    Nodo* Leaff = Choose(Rptr, x);
    par_int li = Leaff->getLimite(0);
    par_int Li = Leaff->getLimite(1);
    Nodo* LL = 0;
    Leaff->añadir_punto(x);
    if (Leaff->obtener_cantidad() > Leaff->getM()) {
        LL = SplitLeaf(Leaff);
        vec_par_int ll = LL->obtner_todos_pts();
        vec_par_int le = Leaff->obtner_todos_pts();
    }
    Nodo* RR = AdjusTree(Leaff, LL);
    if (RR) {
        Nodo* newroot = new Nodo();
        newroot->doRoot();
        newroot->añadir_limite(l);
        newroot->añadir_limite(L);
        newroot->cambiarM(this->root->getM());
        newroot->cambiar_padre(1);
        newroot->añadir_hijo(this->root);
        this->root->dismiss();
        this->root->Reajustar();
        newroot->añadir_hijo(RR);
        this->root = newroot;
    }
}

Nodo* Rtree::Choose(Nodo*& R, par_int& punto) {
    Nodo* Raux = R;
    while (!Raux->knowIsLeaf()) {
        int n = Raux->obtener_cantidad(), iesimo, major = 361201;
        for (int i = 0; i < n; ++i) {
            int area = Raux->obtener_hijo(i)->areaEnlarged(punto);
            if (major >= area) {
                iesimo = i;
                major = area;
            }
        }
        Raux = Raux->obtener_hijo(iesimo);
    }
    par_int a = Raux->getLimite(0), b = Raux->getLimite(1);
    return Raux;
}

Nodo* Rtree::SplitLeaf(Nodo*& R) {
    Nodo* RR = new Nodo();
    RR->cambiarM(R->getM());
    vec_par_int puntos(R->obtner_todos_pts());
    R->clean();
    R->cambiarIzquierda(1);
    RR->cambiarIzquierda(1);
    PickSeed_toPoints(puntos, R, RR);
    while (!puntos.empty()) {
        par_int next = PickNext_toPoints(puntos, R, RR);
        int areaA = R->areaEnlarged(next);
        int areaB = RR->areaEnlarged(next);
        (areaA < areaB) ? R->añadir_punto(next) : RR->añadir_punto(next);
    }
    while (RR->obtener_cantidad() < RR->getm()) {
        int aux = R->obtener_cantidad() - 1;
        par_int temp = R->obtener_punto(aux);
        RR->añadir_punto(temp);
        R->removePoint(aux);
    }
    while (R->obtener_cantidad() < R->getm()) {
        int aux = RR->obtener_cantidad() - 1;
        par_int temp = RR->obtener_punto(aux);
        R->añadir_punto(temp);
        RR->removePoint(aux);
    }
    R->Ajustar();
    RR->Ajustar();
    return RR;
}

Nodo* Rtree::SplitNode(Nodo*& R) {
    Nodo* RR = new Nodo();
    RR->cambiarM(R->getM());
    vec_pnodo sons(R->getAllChilds());
    R->clean();
    R->cambiar_padre(1);
    RR->cambiar_padre(1);
    PickSeed_toRegion(sons, R, RR);
    while (!sons.empty()) {
        Nodo* next = PickNext_toRegion(sons, R, RR);
        par_int a = next->getLimite(0), b = next->getLimite(1);
        int areaA = R->areaEnlarged(next);
        int areaB = RR->areaEnlarged(next);
        (areaA < areaB) ? R->añadir_hijo(next) : RR->añadir_hijo(next);
    }
    while (RR->obtener_cantidad() < RR->getm()) {
        int aux = R->obtener_cantidad() - 1;
        Nodo* temp = R->obtener_hijo(aux);
        RR->añadir_hijo(temp);
        R->removeChild(aux);
    }
    while (R->obtener_cantidad() < R->getm()) {
        int aux = RR->obtener_cantidad() - 1;
        Nodo* temp = RR->obtener_hijo(aux);
        R->añadir_hijo(temp);
        RR->removeChild(aux);
    }
    return RR;
}

Nodo* Rtree::AdjusTree(Nodo*& R, Nodo*& RR) {
    while (R) {
        Nodo* papa = R->obtener_Parent();
        if (papa == 0)break;
        if (RR) {
            papa->añadir_hijo(RR);
            if (papa->obtener_cantidad() > papa->getM())
                RR = SplitNode(papa);
            else
                RR = 0;
        }
        R = papa;
    }
    return RR;
}

void Rtree::PickSeed_toPoints(vec_par_int& Puntos, Nodo*& GroupA, Nodo*& GroupB) {
    std::size_t n = Puntos.size();
    int i = 0, j = 0, d = -1000;
    for (std::size_t ii = 0; ii < n - 1; ++ii) {
        for (std::size_t jj = ii + 1; jj < n; ++jj) {
            int temp = abs(Puntos[ii].first - Puntos[jj].first) * abs(Puntos[ii].second - Puntos[jj].second);
            if (d < temp) {
                d = temp;
                i = ii;
                j = jj;
            }
        }
    }
    GroupA->añadir_punto(Puntos[i]);
    GroupB->añadir_punto(Puntos[j]);
    Puntos.erase(Puntos.begin() + i);
    Puntos.erase(Puntos.begin() + (j - 1));
}

par_int Rtree::PickNext_toPoints(vec_par_int& Puntos, Nodo*& GroupA, Nodo*& GroupB) {
    std::size_t n = Puntos.size();
    int areaA, areaB, d, D = -1000, ii;
    for (std::size_t i = 0; i < n; ++i) {
        areaA = GroupA->areaEnlarged(Puntos[i]);
        areaB = GroupB->areaEnlarged(Puntos[i]);
        d = std::abs(areaA - areaB);
        if (D < d) {
            D = d;
            ii = i;
        }
    }
    par_int entr = Puntos[ii];
    Puntos.erase(Puntos.begin() + ii);
    return entr;
}

void Rtree::PickSeed_toRegion(vec_pnodo& Regiones, Nodo*& GroupA, Nodo*& GroupB) {
    std::size_t n = Regiones.size();
    int i = 0, j = 0, d = -1000;

    for (std::size_t ii = 0; ii < n - 1; ++ii) {
        par_int r1 = Regiones[ii]->getLimite(0), R1 = Regiones[ii]->getLimite(1);
        int a1 = abs(R1.first - r1.first) * abs(R1.second - r1.second);
        for (std::size_t jj = ii + 1; jj < n; ++jj) {
            par_int r2 = Regiones[jj]->getLimite(0), R2 = Regiones[jj]->getLimite(1);
            int a2 = abs(R2.first - r2.first) * abs(R2.second - r2.second);
            int x, y, X, Y;
            (r1.first < r2.first) ? x = r1.first : x = r2.first;
            (R1.first > R2.first) ? X = r1.first : X = r2.first;
            (r1.second < r2.second) ? y = r1.second : y = r2.second;
            (R1.second > R2.second) ? Y = r1.second : Y = r2.second;

            int temp = abs(X - x) * abs(Y - y);
            temp = temp - (a1 + a2);
            if (d < temp) {
                d = temp;
                i = ii;
                j = jj;
            }
        }
    }
    GroupA->añadir_hijo(Regiones[i]);
    GroupB->añadir_hijo(Regiones[j]);
    Regiones.erase(Regiones.begin() + i);
    Regiones.erase(Regiones.begin() + (j - 1));
}

Nodo* Rtree::PickNext_toRegion(vec_pnodo& Regiones, Nodo*& GroupA, Nodo*& GroupB) {
    std::size_t n = Regiones.size();
    int areaA, areaB, d, D = -1000, ii;
    for (std::size_t i = 0; i < n; ++i) {
        areaA = GroupA->areaEnlarged(Regiones[i]);
        areaB = GroupB->areaEnlarged(Regiones[i]);
        d = std::abs(areaA - areaB);
        if (D < d) {
            D = d;
            ii = i;
        }
    }
    Nodo* entr = Regiones[ii];
    Regiones.erase(Regiones.begin() + ii);
    return entr;
}
int xx, yy;
int m = 50;
vector<pair<int, int> > pointss;
vector<pair<int, int> > points_f;
Rtree* R_tree;

int main(int argc, char** argv) {
    R_tree = new Rtree(m, 100, 100,100, 100);
    par_int a(4,5);
    par_int b(43, 56);
    par_int c(6, 3);
    par_int d(67, 31);
    par_int e(78, 22);
    par_int f(23, 34);
    par_int g(34, 24);
    par_int h(87, 57);
    par_int i(3, 3);
    par_int j(26, 32);
    par_int k(78, 8);
    par_int l(99, 4);



    R_tree->inertar(a);
    R_tree->inertar(b);
    R_tree->inertar(c);
    R_tree->inertar(d);
    R_tree->inertar(e);
    R_tree->inertar(f);
    R_tree->inertar(g);
    R_tree->inertar(h);
    R_tree->inertar(i);
    R_tree->inertar(j);
    R_tree->inertar(k);
    R_tree->inertar(l);

    //cout<<R_tree->buscar(l);



    
    

    return 0;
}
