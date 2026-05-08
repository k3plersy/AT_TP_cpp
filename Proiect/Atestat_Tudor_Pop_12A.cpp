#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("atestat.in");
ofstream fout("atestat.out");

void alg_prim()
{
    
}

struct muchie
{
    int i,j,cost;
};
muchie x[5000]; //initializare vector pentru muchii si costurile acestora

void alg_kruskal(muchie x[])
{
    int rep[101],n,m; //initializare vectorul reprezentantiilor, nr noduri, nr muchii
    int v[5000]; //vector pt verificarea muchiilor(pt evitarea muchiilor nedorite)

    cin >> n >> m;
    for(int i = 0 ; i < m ; i++) cin >> x[i].i >> x[i].j >> x[i].cost; //citirea nr de noduri, nr de muchii si apoi a muchiilor si a costurilor acestora

    for(int i = 0; i < m-1; i++) //sortare tablou x[] după campul cost
        for(int j = i+1; j < m; j++)
            if(x[i].cost > x[j].cost)
            {
                muchie aux = x[i];
                x[i] = x[j];
                x[j] = aux;
            }

    for(int i = 1 ; i <= n ; i++) rep[i] = i; //initializare reprezentanti

    //determinare APM
    int S = 0, cnt = 0;
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
    cout << "cost APM: " << S << endl << "APM(muchii si costurile lor)" << endl; //afisare cost
    for(int i = 0; i < m; i++)
        if(v[i]==1) //afisare APM + costuri
            cout << x[i].i << " " << x[i].j << " " << x[i].cost << endl;
}

int main()
{
    int USER, T = 1;
    
    while(T != 0)
    {   
        cout << "ALGORITMI GRAFURI" << endl << "Ce program doriti sa utilizati?" << endl;
        cout << "1. Algoritmul lui Kruskal" << endl;
        cout << "2. " << endl;
        cout << "3. " << endl;
        cout << endl << "Introduceti numarul programului: "; cin>>USER;

        if(USER == 1) 
        {
            cout << "Introduceti nr de noduri, nr de muchii, si lista muchiilor cu costuri" << endl;
            alg_kruskal(x);
        }
        else if(USER == 2)
        {

        }
        else if(USER == 3)
        {

        }
        cout << "Doriti sa continuati? 1 / 0" << endl; cin>>T;
    }
    return 0;
}
