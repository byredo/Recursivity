#include <fstream>
#include <queue>
#define DIM 1001
using namespace std;
ifstream fi("barbar.in");
ofstream fo("barbar.out");
int n,m;
char A[DIM][DIM];
int D[DIM][DIM];
int VIZ[DIM][DIM];
int x1,y1,x2,y2;
queue<pair<int,int> >Q;
int dl[]={-1,0,1,0},dc[]={0,1,0,-1};
bool ins(int l,int c)
{
    return 1<=l&&l<=n&&1<=c&&c<=m;
}
void bfs(int V[DIM][DIM],int mn)
{
    while(!Q.empty())
    {
        int l=Q.front().first,c=Q.front().second;
        Q.pop();
        for(int d=0;d<4;d++)
        {
            int ln=l+dl[d],cn=c+dc[d];
            if(ins(ln,cn)&&!V[ln][cn]&&D[ln][cn]>=mn&&A[ln][cn]!='*')
            {
                V[ln][cn]=V[l][c]+1;
                Q.push(make_pair(ln,cn));
            }
        }
    }
}
int cautbin()
{
    int st=-1,dr=n*m;
    while(st<dr)
    {
        int mid=(st+dr+1)/2;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                VIZ[i][j]=0;
        VIZ[x1][y1]=1;
        Q.push(make_pair(x1,y1));
        bfs(VIZ,mid);
        if(VIZ[x2][y2]&&D[x1][y1]>=mid)
            st=mid;
        else
            dr=mid-1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            VIZ[i][j]=0;
    VIZ[x1][y1]=1;
    Q.push(make_pair(x1,y1));
    bfs(VIZ,st);
    if(!VIZ[x2][y2])
        return -1;
    return st;
}
int main()
{
    fi>>n>>m;
    for(int i=1;i<=n;i++)
        fi>>A[i]+1;
    //bagam dragoni
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(A[i][j]=='D')
            {
                Q.push(make_pair(i,j));
                D[i][j]=1;
            }
            else
                if(A[i][j]=='I')
                    x1=i,y1=j;
                else
                    if(A[i][j]=='O')
                        x2=i,y2=j;
    
    bfs(D,-1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            D[i][j]--;
    fo<<cautbin();
    fi.close();
    fo.close();
    return 0;
}
