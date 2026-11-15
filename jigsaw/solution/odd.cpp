// Walecki cycles + deduction for odd n (n-1 placements); even n falls back to covering all pairs (n placements).
#include <bits/stdc++.h>
using namespace std;
int n,q;bool T[205][205];int nx[205],pv[205];
string ask(const vector<int>&b){
    printf("?");for(int x:b)printf(" %d",x);printf("\n");fflush(stdout);
    char s[205];if(scanf("%s",s)!=1||s[0]=='-')exit(0);
    for(int i=0;i+1<n;i++){T[b[i]][b[i+1]]=1;if(s[i]=='1')nx[b[i]]=b[i+1],pv[b[i+1]]=b[i];}
    return s;
}
int main(){
    int tc;if(scanf("%d",&tc)!=1)exit(0);
    while(tc--){
        if(scanf("%d %d",&n,&q)!=2||n<0)exit(0);
        memset(T,0,sizeof T);memset(nx,0,sizeof nx);memset(pv,0,sizeof pv);
        // odd part: vertices 1..m (m odd), m = "infinity"; even n: extra vertex w=n placed first
        if(n%2==0){
            int h=n/2;
            for(int i=0;i<h;i++){vector<int> z{i};for(int k=1;k<=h;k++){z.push_back((i+k)%n);if(k<h)z.push_back((i-k+n)%n);}
                for(int d=0;d<2;d++){vector<int> b;for(int x:z)b.push_back(x+1);ask(b);reverse(z.begin(),z.end());}}
        }
        int m=n,w=0,r=n%2?(m-1)/2:0;
        for(int i=0;i<r;i++){
            vector<int> z{i};
            for(int k=1;k<=r;k++){z.push_back((i+k)%(2*r));if(k<r)z.push_back((i-k+2*r)%(2*r));}
            for(int d=0;d<2;d++){
                vector<int> b;if(w)b.push_back(w);
                for(int x:z)b.push_back(x+1);
                b.push_back(m);ask(b);reverse(z.begin(),z.end());
            }
        }
        vector<vector<int>> P;
        for(int x=1;x<=n;x++)if(!pv[x]){vector<int> c;for(int y=x;y;y=nx[y])c.push_back(y);P.push_back(c);}
        int k=P.size();
        auto build=[&](const vector<int>&o){vector<int> b;for(int i:o)for(int x:P[i])b.push_back(x);return b;};
        auto resp=[&](const vector<int>&cand,const vector<int>&qq){
            vector<int> s(n+1,0);auto b=build(cand);for(int i=0;i+1<n;i++)s[b[i]]=b[i+1];
            string r;for(int i=0;i+1<n;i++)r+=s[qq[i]]==qq[i+1]?'1':'0';return r;};
        vector<int> id(k);iota(id.begin(),id.end(),0);
        vector<vector<int>> cand;
        do{bool ok=1;for(int i=0;i+1<k&&ok;i++)if(T[P[id[i]].back()][P[id[i+1]][0]])ok=0;if(ok)cand.push_back(id);}
        while(next_permutation(id.begin(),id.end()));
        vector<int> ans=build(cand[0]);
        if(cand.size()>1){
            iota(id.begin(),id.end(),0);
            do{
                auto qq=build(id);set<string> st;for(auto&c:cand)st.insert(resp(c,qq));
                if(st.size()==cand.size()){string s=ask(qq);for(auto&c:cand)if(resp(c,qq)==s)ans=build(c);break;}
            }while(next_permutation(id.begin(),id.end()));
        }
        printf("!");for(int x:ans)printf(" %d",x);printf("\n");fflush(stdout);
    }
}
