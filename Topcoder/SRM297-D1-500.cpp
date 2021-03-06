#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class CageTheMonster {
public:
	int capture(vector <string> labyrinth);
};





int di[] = { 1, -1, 0, 0 };
int dj[] = { 0, 0, -1, 1 };
int n, m;
vector<string> gr;

bool col[64], row[64];
bool vis[64][64];
bool isValid(int i, int j){
	return (i >= 0 && j >= 0 && i < n && j < m);
}

bool out(int i, int j){
	queue < int > q;
	q.push(i), q.push(j);
	for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) vis[i][j] = 0;
	vis[i][j] = 1;
	while (!q.empty()){
		i = q.front(), q.pop();
		j = q.front(), q.pop();
		if (i == 0 || j == 0 || i + 1 == n || j + 1 == m) return 1;
		for (int k = 0; k < 4; k++){
			int ni = i + di[k];
			int nj = j + dj[k];
			if (!isValid(ni, nj) || vis[ni][nj] || gr[ni][nj] == '#' || col[nj] || row[ni]) continue;
			q.push(ni); q.push(nj);
			vis[ni][nj] = 1;
		}
	}
	return 0;
}


int CageTheMonster::capture(vector <string> labyrinth) {
	int ret = 5;
	gr = labyrinth;
	n = gr.size(); m = gr[0].size();
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)if (gr[i][j] == '^'){
		if (!out(i, j)) return 0;
		// make one
		for (int k = 0; k < 4; k++){
			int ni = i + di[k];
			int nj = j + dj[k];
			if (!isValid(ni, nj)) continue;
			if (k < 2) row[ni] = 1;
			else col[nj] = 1;
			if (!out(i, j)) ret = min(ret, 1);
			if (k < 2) row[ni] = 0;
			else col[nj] = 0;
		}
		// make two
		if (ret < 2) continue;
		for (int k = 0; k < 4; k++) for (int k2 = k + 1; k2 < 4; k2++) {
			int ni = i + di[k];
			int nj = j + dj[k];
			int ni2 = i + di[k2];
			int nj2 = j + dj[k2];
			if (!isValid(ni, nj) || !isValid(ni2, nj2)) continue;
			if (k < 2) row[ni] = 1;
			else col[nj] = 1;
			if (k2 < 2) row[ni2] = 1;
			else col[nj2] = 1;
			if (!out(i, j)) ret = min(ret, 2);
			if (k < 2) row[ni] = 0;
			else col[nj] = 0;
			if (k2 < 2) row[ni2] = 0;
			else col[nj2] = 0;
		}
		//make 3 
		if (ret < 3) continue;
		for (int k = 0; k < 4; k++) for (int k2 = k + 1; k2 < 4; k2++) for (int k3 = k2 + 1; k3 < 4; k3++){
			int ni = i + di[k];
			int nj = j + dj[k];
			int ni2 = i + di[k2];
			int nj2 = j + dj[k2];
			int ni3 = i + di[k3];
			int nj3 = j + dj[k3];
			if (!isValid(ni, nj) || !isValid(ni2, nj2) || !isValid(ni3, nj3)) continue;
			if (k < 2) row[ni] = 1;
			else col[nj] = 1;
			if (k2 < 2) row[ni2] = 1;
			else col[nj2] = 1;
			if (k3 < 2) row[ni3] = 1;
			else col[nj3] = 1;
			if (!out(i, j)) ret = min(ret, 3);
			if (k < 2) row[ni] = 0;
			else col[nj] = 0;
			if (k2 < 2) row[ni2] = 0;
			else col[nj2] = 0;
			if (k3 < 2) row[ni3] = 0;
			else col[nj3] = 0;
		}
		// make 4
		if (ret < 4) continue;
		for (int k = 0; k < 4; k++){
			int ni = i + di[k];
			int nj = j + dj[k];
			if (!isValid(ni, nj)) continue;
			if (k < 2) row[ni] = 1;
			else col[nj] = 1;
		}
		if (!out(i, j)) ret = min(ret, 4);
		for (int k = 0; k < 4; k++){
			int ni = i + di[k];
			int nj = j + dj[k];
			if (!isValid(ni, nj)) continue;
			if (k < 2) row[ni] = 0;
			else col[nj] = 0;
		}
	}
	return ret == 5 ? -1 : ret;
}

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	CageTheMonster *obj;
	int answer;
	obj = new CageTheMonster();
	clock_t startTime = clock();
	answer = obj->capture(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	}
	else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	}
	else if (hasAnswer) {
		cout << "Match :-)" << endl;
	}
	else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;

	vector <string> p0;
	int p1;

	{
		// ----- test 0 -----
		string t0[] = { ".######..", ".#^^^^#..", ".#^^^^#..", ".#^^^^#..", ".##^^##..", "...^^...." };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 1;
		all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		string t0[] = { ".....", ".^#^.", ".#^#.", "..#.." };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = 0;
		all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		string t0[] = { "#....", "^#...", "#...." };
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		p1 = -1;
		all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
		// ------------------
	}

	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	}
	else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING


//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
