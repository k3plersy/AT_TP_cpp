#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("atestat.in");
ofstream fout("atestat.out");

int n , m , rep[101]; //initializare nr noduri, nr muchii, vectorul reprezentantiilor
int v[5000];

struct muchie
{
    int i,j,cost; 
};
muchie x[5000]; //initializare vector pentru muchii si costurile acestora ca si var de tip "muchie"


int citire(int &n, int &m, muchie x[]) //citirea nr de noduri, nr de muchii si apoi a muchiilor si a costurilor acestora
{
    fin >> n >> m;
    for(int i = 0 ; i < m ; i++)
        fin >> x[i].i >> x[i].j >> x[i].cost;
    return 0;
}

void sortare(int n,int m, muchie x[]) //sortare tablou x[] după campul cost
{
    for(int i = 0; i < m-1; i++) 
        for(int j = i+1; j < m; j++)
            if(x[i].cost > x[j].cost)
            {
                muchie aux = x[i];
                x[i] = x[j];
                x[j] = aux;
            }
}

int main()
{
    int cnt = 0; //contor pt verificare
    citire(n,m,x); 
    sortare(n,m,x);

    for(int i = 1 ; i <= n ; i++) rep[i] = i; //initializare reprezentanti

    //determinare APM
    int S = 0;
    for(int i = 0 ; i < m && cnt < n ; i++)
        if(rep[x[i].i] != rep[x[i].j]) // extremitatile sunt din subarbori diferiti
        {
            cnt++; v[i]=1;
            S += x[i].cost;
            //reunirea subarborilor dupa reprezentant
            int ai = rep[x[i].i], aj = rep[x[i].j];
            for(int j = 1 ; j <= n ; ++j)
                if(rep[j] == aj)
                    rep[j] = ai;
        }
    fout << S << endl; //afisare cost
    for(int i = 0; i < m; i++)
        if(v[i]==1) //afisare APM + 
            fout << x[i].i << " " << x[i].j << " " << x[i].cost << endl;
    return 0;
}