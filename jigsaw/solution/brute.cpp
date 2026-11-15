// Brute force for small n (n<=6): keep all consistent permutations, ask the placement minimizing the largest answer class.
#include <bits/stdc++.h>
using namespace std;
int n,q;map<string,vector<int>> memo;
string resp(const vector<int>&a,const vector<int>&b){vector<int> s(n+1,0);for(int i=0;i+1<n;i++)s[a[i]]=a[i+1];string r;for(int i=0;i+1<n;i++)r+=s[b[i]]==b[i+1]?'1':'0';return r;}
int main(){
    int tc;if(scanf("%d",&tc)!=1)exit(0);
    while(tc--){
        if(scanf("%d %d",&n,&q)!=2||n<0)exit(0);
        vector<int> p(n);iota(p.begin(),p.end(),1);
        if(n>6){printf("!");for(int x:p)printf(" %d",x);printf("\n");fflush(stdout);continue;}
        vector<vector<int>> all,cur;do all.push_back(p);while(next_permutation(p.begin(),p.end()));
        cur=all;string key=to_string(n);
        while(cur.size()>1){
            vector<int> bq;
            if(memo.count(key))bq=memo[key];
            else{int best=INT_MAX;for(auto&b:all){map<string,int> m;int mx=0;for(auto&a:cur)mx=max(mx,++m[resp(a,b)]);if(mx<best)best=mx,bq=b;}memo[key]=bq;}
            printf("?");for(int x:bq)printf(" %d",x);printf("\n");fflush(stdout);
            char s[16];if(scanf("%s",s)!=1||s[0]=='-')exit(0);vector<vector<int>> nc;for(auto&a:cur)if(resp(a,bq)==s)nc.push_back(a);cur=nc;key+="|"+string(s);
        }
        printf("!");for(int x:cur[0])printf(" %d",x);printf("\n");fflush(stdout);
    }
}
