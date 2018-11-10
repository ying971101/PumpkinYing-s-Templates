const int V=1005;
const int INF=1e9;

struct Edge{
	int to,cap,cost,rev;
};
vector<Edge>G[V];

//h[i]表示s到i的实际最短距离，dist表示优化后的最短距离（正）
int h[V],dist[V];
int pv[V],pree[V];

void add_edge(int from,int to,int cap,int cost){
	G[from].push_back((Edge){to,cap,cost,G[to].size()});
	G[to].push_back((Edge){from,0,-cost,G[from].size()-1});
}

priority_queue<pii,vector<pii>,greater<pii> >que;
int min_cost_flow(int s,int t,int f){
	int res=0;
	mem(h,0);
	while(f){
		for(int i=0;i<V;i++) dist[i]=INF;
		dist[s]=0;
		que.push(pii(0,s));
		while(!que.empty()){
			pii p=que.top();
			que.pop();
			int v=p.second;
			if(dist[v]<p.first) continue;
			for(int i=0;i<G[v].size();i++){
				Edge& e=G[v][i];
				if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
					dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
					pv[e.to]=v;
					pree[e.to]=i;
					que.push(pii(dist[e.to],e.to));
				}
			}
		}
		if(dist[t]==INF) return -1;
		for(int i=0;i<V;i++) h[i]+=dist[i];
		int d=f;
		for(int i=t;i!=s;i=pv[i]){
			d=min(d,G[pv[i]][pree[i]].cap);
		}
		f-=d;
		res+=d*h[t];
		for(int i=t;i!=s;i=pv[i]){
			Edge& e=G[pv[i]][pree[i]];
			e.cap-=d,G[i][e.rev].cap+=d;
		}
	}
	return res;
}

