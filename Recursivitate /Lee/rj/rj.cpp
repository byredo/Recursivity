#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

ifstream fin("rj.in");
ofstream fout("rj.out");

#define DM 101

int n,m;
char mat[DM][DM];
int di[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dj[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int drom[DM][DM],djul[DM][DM];
queue < pair < int, int > > r,j;
pair < int, int > cr,cj;
pair < int, int > cans;
int ans;

bool inside(int i, int j) {
    return(i >= 1 && i <= n && j >= 1 && j <= m);
}

int main() {
    fin >> n >> m;
    fin.get();
    for(int i = 1; i <= n; i++ ) {
        fin.getline(mat[i] + 1, DM);
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(mat[i][j] == 'R') {
                cr.first = i;
                cr.second = j;
            }
            if(mat[i][j] == 'J') {
                cj.first = i;
                cj.second = j;
            }
        }
    }
    
    drom[cr.first][cr.second] = 1;
    djul[cj.first][cj.second] = 1;
    r.push(make_pair(cr.first, cr.second));
    j.push(make_pair(cj.first, cj.second));
    
    while(!r.empty()) {
        int nodi = r.front().first;
        int nodj = r.front().second;
        r.pop();
        for(int i = 0; i < 8; i++) {
            int newi = nodi + di[i];
            int newj = nodj + dj[i];
            if(inside(newi, newj) && (mat[newi][newj] == ' ' || mat[newi][newj] == 'J') && !drom[newi][newj]) {
                r.push(make_pair(newi, newj));
                drom[newi][newj] = drom[nodi][nodj] + 1;
            }
        }
    }
    
    while(!j.empty()) {
        int nodi = j.front().first;
        int nodj = j.front().second;
        j.pop();
        for(int i = 0; i < 8; i++) {
            int newi = nodi + di[i];
            int newj = nodj + dj[i];
            if(inside(newi, newj) && (mat[newi][newj] == ' ' || mat[newi][newj] == 'R') && !djul[newi][newj]) {
                j.push(make_pair(newi, newj));
                djul[newi][newj] = djul[nodi][nodj] + 1;
            }
        }
    }
    
    ans = 999999999;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(drom[i][j] == djul[i][j] && drom[i][j]) {
                if(ans > drom[i][j]) {
                    ans = drom[i][j];
                    cans.first = i;
                    cans.second = j;
                }
            }
        }
    }
    
    fout << ans << " " << cans.first << " " << cans.second;
    
    
    
    
}
