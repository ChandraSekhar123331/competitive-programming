/*
problem is just asking for maximum flow / maximum edge on paths of max flow

if at first we found path that maximize  minimum edge on path, with modified bellman, then minimum edge on this path
will be our max edge on path of max flow

so just run max flow with modified bellman to find max edge on path
*/
#include<set>
#include<map>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<numeric>
#include<sstream>
#include<iostream>
#include<algorithm>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repit(i, c)       	for(it(c) i = (c).begin(); i != (c).end(); ++i)
#define repi(i, j, n) 		for(int i=(j);i<(int)(n);++i)
#define repd(i, j, n) 		for(int i=(j);i>=(int)(n);--i)
#define repa(v)				repi(i, 0, sz(v)) repi(j, 0, sz(v[i]))
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back

typedef vector<int>       vi;
typedef vector<double>    vd;
typedef vector<string>    vs;
typedef long long         ll;
typedef long double   	  ld;

const int OO = (int)1e8;	// Note, IF Small may be WRONG, Large may generate OVERFLOW

struct edge {
	int from, to, w;

	edge(int from, int to, int w) : from(from), to(to), w(w) {}

	bool operator < (const edge & e) const {
		return w > e.w;	// STL priority_queue need it > , or modify data -ve, or use paprmeter less
	}
};

bool BellmanPrcoessing(vector<edge> & edgeList, int n, vi &dist, vi &prev, vi &pos) {
	if (sz(edgeList) == 0)	return false;
	for (int it = 0, r = 0; it < n + 1; ++it, r = 0) {
		for (int j = 0; j < sz(edgeList); ++j) {
			edge ne = edgeList[j];
			if (dist[ne.from] >= OO || ne.w >= OO)	continue;
			// find minimum edge on path
			if (dist[ne.to] > max(dist[ne.from], ne.w)) {
				dist[ne.to] = max(dist[ne.from], ne.w);
				prev[ne.to] = ne.from, pos[ne.to] = j, r++;
				if (it == n)		return true;
			}
		}
		if (!r)	break;
	}
	return false;
}
vi buildPath(vi prev, int src) {
	vi path;	// make sure to test case self edge. E.g. 2 --> 2
	for (int i = src; i > -1 && sz(path) <= sz(prev); i = prev[i])
		path.push_back(i);
	reverse(all(path));
	return path;
}

pair<vi, vi> BellmanFord(vector<edge> & edgeList, int n, int src, int dest)	// O(NE)
{
	vi dist(n, OO), prev(n, -1), reachCycle(n), path, pos(n);	// To use pos: edgeList[pos[path[i]]].w
	dist[src] = -OO;

	bool cycle = BellmanPrcoessing(edgeList, n, dist, prev, pos);

	if (cycle) {
		vi odist = dist;
		BellmanPrcoessing(edgeList, n, dist, prev, pos);
		for (int i = 0; i < n; ++i)	// find all nodes that AFFECTED by negative cycle
			reachCycle[i] = (odist[i] != dist[i]);
	}
	else
		path = buildPath(prev, dest);

	return make_pair(dist, path);
}


// Set cost & cap arr to ZERO
// Make sure that for each cost[i][j] += c there exist cost[j][i] -= c and cap[i][j] += flow
// lp(i, r)	cap[0][i+1]=1;	lp(j, c) cap[j+r+1][r+c+1]=1;	lp() cap[i+1][j+r+1] = 1
// MaxCostMaxFlow can be obtained by multiplying cost matrix(initially zeros) by -1.
// The algo will not work if there is negative cycle reachble on road from src to dest [not tested]
pair<int, int> mcmf(vector< vi > capMax, vector< vi > tcapMax, vector< vector<int> > & costMax, int src, int dest)
{
	int maxFlow = 0, maxEdge = 0;
	while (true) {
		vector<edge> edgeList;
		repa(capMax) if (capMax[i][j] > 0) edgeList.push_back(edge(i, j, -costMax[i][j]));
		printf("");
		pair<vi, vi> p = BellmanFord(edgeList, sz(capMax), src, dest);
		if (p.first[dest] <= -OO || p.first[dest] >= +OO)	break;

		int bottleNeck = OO;
		lp(i, sz(p.second) - 1) {
			int f = p.second[i], t = p.second[i + 1];
			bottleNeck = min(bottleNeck, capMax[f][t]);
		}
		lp(i, sz(p.second) - 1) {
			int f = p.second[i], t = p.second[i + 1];
			capMax[f][t] -= bottleNeck, capMax[t][f] += bottleNeck;
		}
		if (maxFlow == 0){// if this first maxflow path, then this max edge 
			maxEdge = bottleNeck;
		}
		maxFlow += bottleNeck;
	}
	return make_pair(maxFlow, maxEdge);
}

int main(){
	int tc; scanf("%d", &tc);
	while (tc--){
		int n, m, A, B;
		int da;
		scanf("%d%d%d%d%d", &da, &n, &m, &A, &B);
		vector< vi > capMax(n, vi(n, 0)), tcapMax(n, vi(n, 0));
		vector< vector<int> > costMax(n, vi(n, 0));
		for (int i = 0; i < m; i++){
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			capMax[u][v] = c;
			tcapMax[u][v] = c;
			costMax[u][v] = c;
		}
		auto ret = mcmf(capMax, tcapMax, costMax, A, B);
		printf("%d %.3lf\n", da, (ret.first*1.) / double(ret.second));
	}
}

