#include <iostream>
#include <vector>
using namespace std;

void ford_fulkerson(int g_size,int **graph,int s,int t){
    //cout<<"start"<<endl;
    int **remain,**flow;
    remain=new int*[g_size];
    flow=new int*[g_size];
    int i,j;
    for(i=0;i<g_size;i++) {
        remain[i] = new int[g_size];
        flow[i] = new int[g_size];
    }

    for(i=0;i<g_size;i++)
        for(j=0;j<g_size;j++)
            remain[i][j]=graph[i][j],flow[i][j]=0;

    vector<int> path;
    int visit[g_size];
    int top;
    bool back;
    bool jump=false;
    int bottleneck;
    while(!jump){
        memset(visit,0,sizeof(visit));
        path.clear();
        path.push_back(s);
        while(true){
            top=path.back();
            visit[top]=1;
            //cout<<top<<endl;
            if(top==t)
                break;
            back=true;
            for(i=0;i<g_size;i++) {
                if (remain[top][i] > 0&&visit[i]==0) {
                    path.push_back(i);
                    back=false;
                    break;
                }
            }
            if(back) {
                path.pop_back();
                if (path.empty()) {
                    jump = true;
                    break;
                }
            }
        }

        if(!jump) {
            bottleneck = 0x7fffffff;
            for (i = 0; i < path.size() - 1; i++)
                if (remain[path[i]][path[i + 1]] < bottleneck)
                    bottleneck = remain[path[i]][path[i + 1]];
            //cout << bottleneck << endl;
            for (i = 0; i < path.size() - 1; i++)
                flow[path[i]][path[i + 1]] += bottleneck;
            for (i = 0; i < g_size; i++)
                for (j = 0; j < g_size; j++)
                    if (flow[i][j] > 0) {
                        remain[i][j] = graph[i][j] - flow[i][j];
                        remain[j][i] = flow[i][j];
                    }
        }
    }
    int max_flow=0;
    for(i=0;i<g_size;i++)
        max_flow+=flow[0][i];
    cout<<max_flow<<endl;
    for(i=0;i<g_size;i++)
        for(j=0;j<g_size;j++)
            if(flow[i][j]>0)
                cout<<i<<' '<<j<<' '<<flow[i][j]<<endl;
}

int main(){
    int g_size;
    cin>>g_size;
    int **graph=new int*[g_size];
    int i,j;
    for(i=0;i<g_size;i++)
        graph[i]=new int[g_size];
    for(i=0;i<g_size;i++)
        for(j=0;j<g_size;j++)
            cin>>graph[i][j];

    ford_fulkerson(g_size,graph,0,g_size-1);
    return 0;
}

/*
input:
6
0 6 5 0 0 0
0 0 0 9 0 0
0 5 0 0 6 0
0 0 9 0 3 2
0 0 0 0 0 8
0 0 0 0 0 0

output:
10
0 1 6
0 2 4
1 3 9
2 1 3
2 3 1
2 4 6
3 2 6
3 4 2
3 5 2
4 5 8
 *
 *
 */
