// Test every ordered pair: n placements. Even n: the n/2 zig-zag Hamiltonian paths in both directions.
// Odd n: Walecki cycles cut at vertex n (n-1 placements) + one more placement to "confirm" the last link.
#include <bits/stdc++.h>
using namespace std;
int n,q;int nx[205],pv[205];
void ask(const vector<int>&b){printf("?");for(int x:b)printf(" %d",x);printf("\n");fflush(stdout);char s[205];if(scanf("%s",s)!=1||s[0]=='-')exit(0);
    for(int i=0;i+1<n;i++)if(s[i]=='1')nx[b[i]]=b[i+1],pv[b[i+1]]=b[i];}
vector<vector<int>> chains(){vector<vector<int>> P;for(int x=1;x<=n;x++)if(!pv[x]){vector<int> c;for(int y=x;y;y=nx[y])c.push_back(y);P.push_back(c);}return P;}
int main(){
    int tc;if(scanf("%d",&tc)!=1)exit(0);
    while(tc--){
        if(scanf("%d %d",&n,&q)!=2||n<0)exit(0);memset(nx,0,sizeof nx);memset(pv,0,sizeof pv);
        if(n%2==0){
            int h=n/2;
            for(int i=0;i<h;i++){vector<int> z{i};for(int k=1;k<=h;k++){z.push_back((i+k)%n);if(k<h)z.push_back((i-k+n)%n);}
                for(int d=0;d<2;d++){vector<int> b;for(int x:z)b.push_back(x+1);ask(b);reverse(z.begin(),z.end());}}
        }else{
            int r=(n-1)/2;
            for(int i=0;i<r;i++){vector<int> z{i};for(int k=1;k<=r;k++){z.push_back((i+k)%(2*r));if(k<r)z.push_back((i-k+2*r)%(2*r));}
                for(int d=0;d<2;d++){vector<int> b;for(int x:z)b.push_back(x+1);b.push_back(n);ask(b);reverse(z.begin(),z.end());}}
            auto P=chains();
            if(P.size()==2){if(P[0].back()!=n)swap(P[0],P[1]);vector<int> b=P[0];b.insert(b.end(),P[1].begin(),P[1].end());ask(b);}
        }
        auto P=chains();printf("!");for(int x:P[0])printf(" %d",x);printf("\n");fflush(stdout);
    }
}
