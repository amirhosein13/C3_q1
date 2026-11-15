// Adaptive greedy: lay out the current chains so that each chain end is followed by a not-yet-tested start.
// Uses about n..1.3n placements in the worst case (fine for q=2n, not for q=n or q=n-1).
#include <bits/stdc++.h>
using namespace std;
int n,q;bool T[205][205];int nx[205],pv[205];mt19937 rng(12345);
void ask(const vector<int>&b){printf("?");for(int x:b)printf(" %d",x);printf("\n");fflush(stdout);char s[205];if(scanf("%s",s)!=1||s[0]=='-')exit(0);
    for(int i=0;i+1<n;i++){T[b[i]][b[i+1]]=1;if(s[i]=='1')nx[b[i]]=b[i+1],pv[b[i+1]]=b[i];}}
vector<vector<int>> chains(){vector<vector<int>> P;for(int x=1;x<=n;x++)if(!pv[x]){vector<int> c;for(int y=x;y;y=nx[y])c.push_back(y);P.push_back(c);}return P;}
int main(){
    int tc;if(scanf("%d",&tc)!=1)exit(0);
    while(tc--){
        if(scanf("%d %d",&n,&q)!=2||n<0)exit(0);memset(T,0,sizeof T);memset(nx,0,sizeof nx);memset(pv,0,sizeof pv);
        while(true){
            auto P=chains();int k=P.size();if(k==1)break;
            if(k==2){
                if(T[P[0].back()][P[1][0]]){nx[P[1].back()]=P[0][0];pv[P[0][0]]=P[1].back();continue;}
                if(T[P[1].back()][P[0][0]]){nx[P[0].back()]=P[1][0];pv[P[1][0]]=P[0].back();continue;}
            }
            vector<int> used(k,0),ord;int cur=rng()%k;ord.push_back(cur);used[cur]=1;
            for(int s=1;s<k;s++){int b=-1;for(int j=0;j<k;j++)if(!used[j]&&!T[P[cur].back()][P[j][0]]){b=j;break;}
                if(b<0)for(int j=0;j<k;j++)if(!used[j]){b=j;break;}ord.push_back(b);used[b]=1;cur=b;}
            vector<int> b;for(int i:ord)for(int x:P[i])b.push_back(x);ask(b);
        }
        auto P=chains();printf("!");for(int x:P[0])printf(" %d",x);printf("\n");fflush(stdout);
    }
}
