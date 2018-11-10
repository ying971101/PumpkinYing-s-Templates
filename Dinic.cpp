const int V=20005;
const int INF=1e9;

struct Edge{
	int to,cap,rev;
};
vector<Edge>G[V];
int iter[V],level[V];

void add_edge(int u,int v,int w){
	G[u].push_back((Edge){v,w,(int)G[v].size()});
	G[v].push_back((Edge){u,0,(int)G[u].size()-1});
}

queue<int>que;
void bfs(int s){
	mem(level,-1);
	level[s]=0;
	que.push(s);
	while(!que.empty()){
		int v=que.front();
		que.pop();
		for(int i=0;i<G[v].size();i++){
			Edge& e=G[v][i];
			if(level[e.to]<0 && e.cap>0) level[e.to]=level[v]+1,que.push(e.to);
		}
	}
}

int dfs(int s,int t,int f){
	if(s==t) return f;
	//弧优化
	for(int& i=iter[s];i<(int)G[s].size();i++){
		Edge& e=G[s][i];
		if(level[s]<level[e.to] && e.cap>0){
			int d=dfs(e.to,t,min(f,e.cap));
			if(d>0){
				e.cap-=d,G[e.to][e.rev].cap+=d;
				return d;
			}
		}
	}
	return 0;
}

int max_flow(int s,int t){
	int flow=0;
	while(1){
		bfs(s);
		if(level[t]<0) return flow;
		mem(iter,0);
		int f;
		while(f=dfs(s,t,INF)) flow+=f;
	}
}

