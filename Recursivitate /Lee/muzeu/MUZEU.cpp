#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;

ifstream fin("muzeu.in");
ofstream fout("muzeu.out");

#define DM 251

int n;
char m[DM][DM];
int dist[DM][DM];
queue < pair < int, int > > q;
int di[4] = {0, 1, 0 , -1};
int dj[4] = {1, 0, - 1, 0};

bool inside(int i, int j) {
    return(i >= 1 && i <= n && j >= 1 && j <= n);
}

int main() {
    fin >> n;
    fin.get();
    for(int i = 1; i <= n; i++) {
        fin.getline(m[i] + 1, DM);
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(m[i][j] == 'P') {
                q.push(make_pair(i, j));
            }
        }
    }
    
    while(!q.empty()) {
        int nodi = q.front().first;
        int nodj = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int newi = nodi + di[i];
            int newj = nodj + dj[i];
            if(m[newi][newj] == 'P') {
                dist[newi][newj] = 0;
            } else if(inside(newi, newj) && m[newi][newj] == '.' && !dist[newi][newj]) {
                q.push(make_pair(newi, newj));
                dist[newi][newj] = dist[nodi][nodj] + 1;
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(m[i][j] == '#') {
                fout << "-2";
            } else if(m[i][j] == 'P') {
                fout << "0";
            } else if(dist[i][j] == 0) {
                fout << "-1";
            } else {
                fout << dist[i][j];
            }
            fout << " ";
        }
        fout << '\n';
    }
    
}
