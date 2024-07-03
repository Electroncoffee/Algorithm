#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

long format_time(string str) {
	long HH = stoi(str.substr(0, 2)), MM= stoi(str.substr(3, 2)), SS= stoi(str.substr(6, 2));
	return (((HH * 60) + MM) * 60) + SS;
}
string format_times(long t) {
	long SS = t % 60, MM = (t - SS) / 60 % 60, HH = t / 3600;
	string result = HH >= 10 ? to_string(HH) : ("0" + to_string(HH));
	result += ":";
	result += MM >= 10 ? to_string(MM) : ("0" + to_string(MM));
	result += ":";
	result += SS >= 10 ? to_string(SS) : ("0" + to_string(SS));

	return result;
}

string solution(string play_time, string adv_time, vector<string> logs) {
	long pt = format_time(play_time), at = format_time(adv_time);
	vector<long> lt(pt + 2, 0);//<열기-닫기>

	map<long, long> start;
	map<long, long> end;
	//중복제거(n)
	for (long i = 0; i < logs.size(); i++) {
		long start_t = format_time(logs[i].substr(0, 8));
		long end_t = format_time(logs[i].substr(9, 8));
		if (start.find(start_t) != start.end())
			start[start_t] += 1;
		else
			start.insert({ start_t, 1 });
		if (end.find(end_t) != end.end())
			end[end_t] += 1;
		else
			end.insert({ end_t, 1 });
	}
	//vector에 넣기(그때그때 다름, 거의 n에 근접할때가 많음)
	for (auto iter : start) { lt[iter.first + 1] = iter.second; }
	for (auto iter : end) { lt[iter.first + 1] -= iter.second; }

	//누적합으로 만들기(n)
	for (long i = 1; i < lt.size(); i++) {
		lt[i] += lt[i - 1];
	}

	//구간합으로 최대 구간 찾기(n)
	pair<long,long> max(-1,-1);
	long dup_begin = 0;
	long dup_end = 0;
	for (long i = 1; i <= at; i++) {
		dup_end += lt[i];//최초 구간합(0초부터at초까지의 합)
	}
	for (long i = 1; i < lt.size() - at; i++) {
		if (max.second < (dup_end - dup_begin))
			max = make_pair(i, dup_end - dup_begin);
		dup_begin += lt[i];
		dup_end += lt[i + at];
	}
	return format_times(max.first-1);
	//대충 시간복잡도 5n --> O(n)
}

int main(void) {
	string play_time = "00:01:00";
	string adv_time = "00:00:10";
	vector<string> logs = { "00:00:00-00:00:10", "00:00:05-00:00:24", "00:00:14-00:00:24", "00:00:14-00:00:38", "00:00:35-00:00:40" };

	cout << solution(play_time, adv_time, logs);
}