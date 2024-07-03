#include <string>
#include <vector>
using namespace std;

void recur(int* hash, int idx, int stack, vector<vector<int>>* censor_id) {
	if (stack == censor_id->size()) {
		hash[idx] = 1;
		return;
	}
	for (int i = 0; i < (*censor_id)[stack].size(); i++) {
		if (idx != (idx | (1 << (*censor_id)[stack][i])))
			recur(hash, idx | (1 << (*censor_id)[stack][i]), stack + 1, censor_id);
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	vector<vector<int>> censor_id;
	censor_id.resize(banned_id.size());
	int cnt = 0;
	for (int i = 0; i < user_id.size(); i++) {
		for (int j = 0; j < banned_id.size(); j++) {
			if (user_id[i].size() != banned_id[j].size()) continue;
			cnt = 0;
			for (int k = 0; k < user_id[i].size(); k++) {
				if (banned_id[j][k] == '*' || user_id[i][k] == banned_id[j][k]) {
					cnt++;
				}
			}
			if (cnt == user_id[i].size()) censor_id[j].push_back(i);
		}
	}

	//비트마스킹+재귀
	int hash[512] = { 0, };
	recur(hash, 0, 0, &censor_id);
	int result = 0;
	for (int i = 0; i < 512; i++) {
		result += hash[i];
	}
	return result;
}