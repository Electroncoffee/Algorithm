#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

vector<tuple<int, int, int>> map; // <노드,노드,가중치,유니온>
vector<int> umap, urank; //유니온맵

bool compare(const tuple<int, int, int>& a, const tuple<int, int, int>& b)
{
	if (get<2>(a) < get<2>(b))
		return true;
	else
		return false;
}

int Find(int a) {
	while (true) {
		if (umap[a] == a)
			return a;
		a = umap[a];
	}
}

void Union(int a, int b) {
	int A = Find(a);
	int B = Find(b);
	if (A == B) return;
	if (urank[A] < urank[B])
		umap[A] = B;
	else if (urank[A] < urank[B])
		umap[B] = A;
	else {
		umap[B] = A;
		urank[A] += 1;
	}
}

int Kruskal() {
	vector<int> MST;
	int result = 0;
	for (tuple<int, int, int> node : map) {
		if (Find(get<0>(node)) != Find(get<1>(node))) {
			MST.push_back(get<2>(node));
			//유니온
			Union(get<0>(node), get<1>(node));
		}
	}
	sort(MST.begin(), MST.end());
	MST.erase(MST.end() - 1);
	for (int n : MST) {
		result += n;
	}
	return result;
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M, a, b, c;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		map.push_back(make_tuple(a, b, c));
	}
	for (int i = 0; i < N + 1; i++) {
		umap.push_back(i);
		urank.push_back(0);
	}

	sort(map.begin(), map.end(), compare);

	cout << Kruskal();
	return 0;
}