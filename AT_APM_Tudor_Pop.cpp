#include <iostream>
using namespace std;

// ──────────────────────────────────────────────
//  Structuri si variabile globale
// ──────────────────────────────────────────────

struct muchie
{
    int i, j, cost;
};

muchie x[5000];          // vectorul muchiilor (Kruskal)
int    cost[101][101];   // matricea costurilor  (Prim)
int    n, m;             // noduri, muchii

// ──────────────────────────────────────────────
//  KRUSKAL
// ──────────────────────────────────────────────

void citire_kruskal()
{
    cout << "  Introduceti numarul de noduri si numarul de muchii: ";
    cin >> n >> m;
    cout << "  Introduceti muchiile (nod1 nod2 cost):\n";
    for (int i = 0; i < m; i++)
    {
        cout << "    Muchia " << i + 1 << ": ";
        cin >> x[i].i >> x[i].j >> x[i].cost;
    }
}

void sortare_kruskal()
{
    for (int i = 0; i < m - 1; i++)
        for (int j = i + 1; j < m; j++)
            if (x[i].cost > x[j].cost)
            {
                muchie aux = x[i];
                x[i] = x[j];
                x[j] = aux;
            }
}

void alg_kruskal()
{
    citire_kruskal();
    sortare_kruskal();

    int rep[101];
    int v[5000];

    for (int i = 0; i < m; i++) v[i] = 0;       // initializare explicita
    for (int i = 1; i <= n; i++) rep[i] = i;     // fiecare nod e propriul reprezentant

    int S = 0, cnt = 0;

    for (int i = 0; i < m && cnt < n - 1; i++)   // APM are exact n-1 muchii
    {
        int ri = rep[x[i].i];
        int rj = rep[x[i].j];

        if (ri != rj)   // extremitatile sunt in subarbori diferiti
        {
            cnt++;
            v[i] = 1;
            S += x[i].cost;

            // reunirea celor doi subarbori
            for (int j = 1; j <= n; j++)
                if (rep[j] == rj)
                    rep[j] = ri;
        }
    }

    if (cnt < n - 1) // dacă graful nu e conex, Kruskal va găsi o pădure parțială minimă (nu un arbore)
    {
        cout << "\n  ATENTIE: Graful nu este conex! APM nu exista.\n";
        return;
    }
    else
    {
        cout << "\n  Cost APM (Kruskal): " << S << endl;
        cout << "  Muchiile din APM:\n";
        for (int i = 0; i < m; i++)
           if (v[i] == 1)
               cout << "    " << x[i].i << " -- " << x[i].j
                   << "  (cost " << x[i].cost << ")\n";
    }
}   

// ──────────────────────────────────────────────
//  PRIM
// ──────────────────────────────────────────────

void citire_prim()
{
    for (int i = 1; i <= 100; i++)
        for (int j = 1; j <= 100; j++)
            cost[i][j] = 0;

    cout << "  Introduceti numarul de noduri si numarul de muchii: ";
    cin >> n >> m;
    cout << "  Introduceti muchiile (nod1 nod2 cost):\n";
    int u, v, c;
    for (int i = 0; i < m; i++)
    {
        cout << "    Muchia " << i + 1 << ": ";
        cin >> u >> v >> c;
        cost[u][v] = c;
        cost[v][u] = c;   // graf neorientat
    }
}

void alg_prim()
{
    citire_prim();

    int  inAPM[101];     // 1 daca nodul e deja in APM,  0 altfel
    int  minCost[101];   // costul minim al muchiei care leaga nodul de APM
    int  parinte[101];   // de unde vine muchia minima spre acest nod

    for (int i = 1; i <= n; i++)
    {
        inAPM[i]   = 0;
        minCost[i] = 999999;   // "infinit"
        parinte[i] = -1;
    }

    // pornim din nodul 1
    minCost[1] = 0;
    int S = 0;

    for (int pas = 0; pas < n; pas++)
    {
        // alegem nodul nevizitat cu costul minim
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (!inAPM[i] && (u == -1 || minCost[i] < minCost[u]))
                u = i;

        // daca costul minim e tot "infinit", graful e neconex
        if (minCost[u] == 999999 && pas > 0)
        {
            cout << "\n  ATENTIE: Graful nu este conex! APM nu exista.\n";
            return;
        }

        inAPM[u] = 1;
        S += minCost[u];

        // actualizam vecinii lui u
        for (int v = 1; v <= n; v++)
            if (cost[u][v] != 0 && !inAPM[v] && cost[u][v] <= minCost[v])
            {
                minCost[v] = cost[u][v];
                parinte[v] = u;
            }
    }

    cout << "\n  Cost APM (Prim): " << S << endl;
    cout << "  Muchiile din APM:\n";
    for (int i = 2; i <= n; i++)
        cout << "    " << parinte[i] << " -- " << i
             << "  (cost " << minCost[i] << ")\n";
}

// ──────────────────────────────────────────────
//  MENIU PRINCIPAL
// ──────────────────────────────────────────────

int main()
{
    int USER, T = 1;

    while (T != 0)
    {
        cout << "\n===================================\n";
        cout << "   ALGORITMI - ARBORE PARTIAL MINIM\n";
        cout << "===================================\n";
        cout << "  1. Algoritmul lui Kruskal\n";
        cout << "  2. Algoritmul lui Prim\n";
        cout << "-----------------------------------\n";
        cout << "  Alegeti algoritmul: ";
        cin >> USER;

        if (USER == 1)
        {
            cout << "\n  [Kruskal]\n";
            alg_kruskal();
        }
        else if (USER == 2)
        {
            cout << "\n  [Prim]\n";
            alg_prim();
        }
        else
        {
            cout << "  Optiune invalida!\n";
        }

        cout << "\n  Doriti sa continuati? (1 = Da / 0 = Nu): ";
        cin >> T;
    }

    cout << "\n  La revedere!\n";
    return 0;
}