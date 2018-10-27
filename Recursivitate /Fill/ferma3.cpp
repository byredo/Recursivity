#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

ifstream fin("ferma3.in");
ofstream fout("ferma3.out");

#define DM 401

int n,m,v;
char ferma[DM][DM];
int el, maxel;
int crn = 1;
long long numbered[DM][DM];
int dim[DM * DM];
vector < char > colors;
int fr[DM];
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

bool inside (int i, int j) {
    return (i >= 1 && i <= n && j >= 1 && j <= m);
}

bool diff (int i, int j, int val, int it) {
    for(int k = 0; k < it; k++) {
        int newi = i + di[k];
        int newj = j + dj[k];
        
        if(numbered[newi][newj] == val) {
            return false;
        }
        
    }
    
    return true;
}

void fill (int i, int j) {
    numbered[i][j] = crn;
    el++;
    
    for(int k = 0; k < 4; k++) {
        int newi = i + di[k];
        int newj = j + dj[k];
        
        if(inside(newj, newj) && ferma[i][j] == ferma[newi][newj] && !numbered[newi][newj]) {
            fill(newi, newj);
        }
        
    }
    
}

int main () {
    fin >> v;
    fin >> n >> m;
    fin.get();
    
    for(int i = 1; i <= n; i++) {
        fin.getline(ferma[i] + 1, DM);
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            
            if(!fr[ferma[i][j] - 'a']) {
                fr[ferma[i][j] - 'a'] = 1;
                colors.push_back(ferma[i][j]);
            }
            
            if(!numbered[i][j]) {
                el = 0;
                
                fill(i, j);
                
                dim[crn++] = el;
                maxel = max(el , maxel);
            }
            
        }
    }
    
    if(v == 1) {
        fout << maxel;
    } else {
        int size = 0;
        int lin = 0, col = 0;
        char culoare;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                for(int k = 0; k < colors.size(); k++) {
                    if(colors[k] != ferma[i][j]) {
                        int td = 1;
                        
                        for(int l = 0; l < 4; l++) {
                            int newi = i + di[l];
                            int newj = j + dj[l];
                            
                            if(inside(newi, newj) && (colors[k] == ferma[newi][newj]) && diff(i, j, numbered[newi][newj], l)) {
                                td += dim[numbered[newi][newj]];
                            }
                            
                        }
                        
                        if(td > size) {
                            size = td;
                            lin = i;
                            col = j;
                            culoare = colors[k];
                        }
                        
                    }
                    
                }
                
            }
        }
        
        fout << lin << " " << col << '\n' << culoare;
    }
}
