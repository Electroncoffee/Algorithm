#include <iostream>
#include <vector>
using namespace std;

string a, b;
int an, bn;
vector<vector<int>> grid;

void pr(int i, int j) {
	if (grid[i][j] == 0) return;
	if (a[i - 1] == b[j - 1]) {
		pr(i - 1, j - 1);
		cout << a[i - 1];
	}
	else grid[i - 1][j] > grid[i][j - 1] ? pr(i - 1, j) : pr(i, j - 1);
}

int main(void) {
	cin >> a >> b;
	an = a.size() + 1;
	bn = b.size() + 1;

	grid.resize(an);
	for (int i = 0; i < an; i++) { grid[i].resize(bn); }

	for (int i = 1; i < an; i++) {
		for (int j = 1; j < bn; j++) {
			if (a[i - 1] == b[j - 1]) grid[i][j] = grid[i - 1][j - 1] + 1;
			else grid[i][j] = max(grid[i - 1][j], grid[i][j - 1]);
		}
	}

	cout << grid[an - 1][bn - 1] << '\n';
	pr(an - 1, bn - 1);
	return 0;
}