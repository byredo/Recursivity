#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("alee.in");
ofstream fout("alee.out");

int n,m[176][176], obs;
int dist[176][176];
int pii,pij,pfi,pfj;
int ci,cj;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

struct hpair {
    int f; int s;
} p;

int st = 1, dr;
hpair queue[200001];

void pop() {
    st++;
}

void push (int x, int y) {
    queue[++dr].f = x;
    queue[dr].s = y;
}

bool empty() {
    return (dr < st);
}

bool inside(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= n);
}

int main() {
    fin >> n >> obs;
    for(int i = 1; i <= obs; i++) {
        fin >> ci >> cj;
        m[ci][cj] = 1;
    }
    fin >> pii >> pij >> pfi >> pfj;
    
    dist[pii][pij] = 1;
    push(pii, pij);
    
    while(!empty()) {
        int nodi = queue[st].f;
        int nodj = queue[st].s;
        pop();
        for(int i = 0; i < 4; i++) {
            int newi = nodi + di[i];
            int newj = nodj + dj[i];
            if(inside(newi, newj) && !m[newi][newj] && !dist[newi][newj]) {
                push(newi, newj);
                dist[newi][newj] = dist[nodi][nodj] + 1;
            }
        }
    }
    
    fout << dist[pfi][pfj];
}
