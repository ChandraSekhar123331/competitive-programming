#include<bits/stdc++.h>
using namespace std;


class Rumor {
public:
	int getMinimum(string knowledge, vector <string> graph);
};

int n;
vector<string> g;



int Rumor::getMinimum(string knowledge, vector <string> graph) {
	g = graph;
	n = g.size();
	int ret = 123456789;
	if (count(knowledge.begin(), knowledge.end(), 'Y') == n) return 0;
	for (int msk = 0; msk < (1 << n); msk++){
		queue < int > q;
		vector<int> s1(n, 0), s2(n, 0), p1(n, 0), p2(n, 0), in(n, 0);
		for (int i = 0; i < n; i++) if (knowledge[i] == 'Y'){
			q.push(i);
			p1[i] = p2[i] = 1;
			in[i] = 1;
		}
		int cnt = 0;
		do{
			queue<int> nq;
			while (!q.empty()){
				int i = q.front(); q.pop(); in[i] = 0;
				if (s1[i] && s2[i]) continue;
				if (s1[i] || s2[i]){
					if (s1[i]){
						if (!p2[i]) continue;
						for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p2[j] == 0){
							p2[j] = 1;
							if (!in[j]){
								in[j] = 1; nq.push(j);
							}
						}
						s2[i] = 1;
					}
					else{
						if (!p1[i]) continue;
						for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p1[j] == 0){
							p1[j] = 1;
							if (!in[j]){
								in[j] = 1; nq.push(j);
							}
						}
						s1[i] = 1;
					}
				}
				else{
					if (p1[i] + p2[i] == 1){
						if (p1[i] == 1){
							for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p1[j] == 0){
								p1[j] = 1;
								if (!in[j]){
									in[j] = 1; nq.push(j);
								}
							}
							s1[i] = 1;
						}
						else{
							for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p2[j] == 0){
								p2[j] = 1;
								if (!in[j]){
									in[j] = 1; nq.push(j);
								}
							}
							s2[i] = 1;
						}
					}
					else{
						if (msk&(1 << i)){
							for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p2[j] == 0){
								p2[j] = 1;
								if (!in[j]){
									in[j] = 1; nq.push(j);
								}
							}
							s2[i] = 1;
						}
						else{
							for (int j = 0; j < n; j++) if (g[i][j] == 'Y' && p1[j] == 0){
								p1[j] = 1;
								if (!in[j]){
									in[j] = 1; nq.push(j);
								}
							}
							s1[i] = 1;
						}
					}
					nq.push(i); in[i] = 1;
				}
			}
			q = nq;
			cnt++;
			bool f = 1;
			for (int i = 0; i < n; i++) if (!p1[i] || !p2[i]) f = 0;
			if (f) break;
		} while (!q.empty());
		bool f = 1;
		for (int i = 0; i < n; i++) if (!p1[i] || !p2[i]) f = 0;
		if (f) ret = min(ret, cnt);
	}
	return (ret >= 123456789) ? -1 : ret;
}

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, string p0, vector <string> p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	Rumor *obj;
	int answer;
	obj = new Rumor();
	clock_t startTime = clock();
	answer = obj->getMinimum(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
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

	string p0;
	vector <string> p1;
	int p2;

	{
		// ----- test 0 -----
		p0 = "YNN";
		string t1[] = { "NYN", "NNY", "NNN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 3;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		p0 = "YNNY";
		string t1[] = { "NYYN", "YNNY", "YNNY", "NYYN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 1;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		p0 = "YYYY";
		string t1[] = { "NYNN", "YNYN", "NYNY", "NNYN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 0;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 3 -----
		p0 = "YYYYYN";
		string t1[] = { "NYYYYN", "YNYYYN", "YYNYYN", "YYYNYN", "YYYYNN", "NNNNNN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = -1;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 4 -----
		p0 = "NNNY";
		string t1[] = { "NNNN", "YNNN", "YNNN", "NYYN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 3;
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 5 -----
		p0 = "NNNNNNNYYY";
		string t1[] = { "NYNNYNNYNN", "NNYNYNNNNY", "YYNNNYNNNN", "YNNNYNYNNN", "NNYNNYNNYN", "NNNNYNNNYY", "NYNYNYNNNN", "NNNNNNYNYY", "NNNYNNNYNY", "NYYNNNNYNN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 2;
		all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 6 -----
		p0 = "YYNNNNNNNNNNNNNN";
		string t1[] = { "NNYNNNNNNNNNNNNN", "NNNYNNNNNNNNNNNN", "NNNNYNNNNNNNNNNN", "NNNNNYNNNNNNNNNN", "NNNNNNYNNNNNNNNN", "NNNNNNNYNNNNNNNN", "NNNNNNNNYNNNNNNN", "NNNNNNNNNYNNNNNN", "NNNNNNNNNNYNNNNN", "NNNNNNNNNNNYNNNN", "NNNNNNNNNNNNYNNN", "NNNNNNNNNNNNNYNN", "NNNNNNNNNNNNNNYY", "NNNNNNNNNNNNNNYY", "NNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNN" };
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 7;
		all_right = KawigiEdit_RunTest(6, p0, p1, true, p2) && all_right;
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