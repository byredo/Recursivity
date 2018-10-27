#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

ifstream fin("panda.in");
ofstream fout("panda.out");

#define DM 501
#define INF 0x3f3f3f3f

int p;
int n,m,T;
int L,C,k,S;
pair < int, int > food [DM * DM];
int mat[DM][DM];
queue < pair < int, int > > q;
int dmin[DM][DM];
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, - 1, 0};

bool inside(int i, int j) {
    return (i >= 1 && i <= n && j >= 1 && j <= m);
}

string tobinary(int x) {
    if(x == 0) {
        return "0";
    }
    
    int it = 0;
    string s;
    int cat = x;
    
    while(cat != 0 || it < S) {
        int rest = cat % 2;
        
        char c = '0';
        c += rest;
        
        s += c;
        
        cat /= 2;
        it++;
    }
    
    return s;
}

bool complementary(string s, string c) {
    for(int i = 0; i < S; i++) {
        if(s[i] == c[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    fin >> p;
    fin >> n >> m >> T;
    fin >> L >> C >> k >> S;
    
    for(int i = 1; i <= T; i++) {
        fin >> food[i].first >> food[i].second;
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fin >> mat[i][j];
        }
    }
    
    if(p == 1) {
        int rez = -1;
        string panda = tobinary(k);
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                string actual = tobinary(mat[i][j]);
                rez += complementary(panda, actual);
            }
        }
        
        fout << rez;
    } else {
        q.push(make_pair(L, C));
        string panda = tobinary(k);
        
        while(!q.empty()) {
            int nodi = q.front().first;
            int nodj = q.front().second;
            
            q.pop();
            
            for(int i = 0; i < 4; i++) {
                int newi = nodi + di[i];
                int newj = nodj + dj[i];
                
                string actual = tobinary(mat[newi][newj]);
                
                if(inside(newi, newj) && complementary(panda, actual) && !dmin[newi][newj]) {
                    dmin[newi][newj] = dmin[nodi][nodj] + 1;
                    q.push(make_pair(newi, newj));
                }
                
            }
        }
        
        int smin = INF;
        int nrmin = 0;
        
        for(int i = 1; i <= T; i++) {
            if(dmin[food[i].first][food[i].second] == smin) {
                nrmin++;
            } else if(dmin[food[i].first][food[i].second] < smin && dmin[food[i].first][food[i].second]) {
                smin = dmin[food[i].first][food[i].second];
                nrmin = 1;
            }
        }
        
        fout << smin << " " << nrmin;
    }
    
}
