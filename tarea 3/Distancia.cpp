#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <math.h>
#include <random>

using namespace std;

template<class T>
class V{
public:
	int n;
	vector<T> v;
	V(int n) {
		this->n = n;
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		uniform_real_distribution<> dis(1.0, 2.0);
		for (int i = 0; i < n; i++) {
			v.push_back(dis(gen));
		}
	}
	void mostrar() {
		for (int i = 0; i < n; i++) {
			cout << v[i] << " ";
		}
		cout << endl;
	}

	

};

template<class T>
double distancia(V<T> v1, V<T> v2,int n) {
    double d=0;
    for (int i = 0; i < n; i++) {
        d+= pow(v1.v[i] - v2.v[i], 2);
    }
    d = sqrt(d);
    return d;
}

int main(){
    int dim = 15;
    int n = 25000;
    
    //cout << distancia(v1, v2, dim);
    vector<V<double>> vv;
    //vv.reserve(n);
    //V<double> *vvv;
    for (int i = 0; i < n; i++) {
        V<double> v1(dim);
        //vvv[i]=v1;
        vv.push_back(v1);
    }
    
    chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            //cout<<distancia(vv[i], vv[j], dim)<< endl;
            distancia(vv[i], vv[j], dim);
        }
    }
    end = chrono::high_resolution_clock::now();
    int64_t duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); // duration is holding the elapsed time.
    cout << "time: "<< duration << endl;
    return 0;
}
