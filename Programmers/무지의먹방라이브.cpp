#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
/*������ �Թ� ���̺�
* https://school.programmers.co.kr/learn/courses/30/lessons/42891
* ������ ���� ���� ������ ���� ��, ������ 1���� ���� �Դ¸�ŭ ����
*/
bool a_compare(const pair<int, int>& a, const pair<int, int>& b) {
    return b.first > a.first;
}

bool b_compare(const pair<int, int>& a, const pair<int, int>& b) {
    return b.second > a.second;
}

int solution(vector<int> food_times, long long k) {
    int n = (int)food_times.size(), i=1;
    long long edit_size=0;
    int prev_size = 0;
    vector<pair<int,int>> v;
    for (auto& a : food_times) v.push_back(pair<int, int>(a, i++));
    std::sort(v.begin(), v.end(),a_compare);
    for (i = 0; i < v.size(); i++, n--) {
        edit_size = (long long)(v[i].first - prev_size) * n;
        if (!edit_size) continue;
        else if (edit_size <= k) {
            k -= edit_size;
            prev_size = v[i].first;
        }
        else break;
    }
    if (!n) return -1;
    //k�� ���� ������ ������ ���� �ð��� ����
    std::sort(v.begin()+i, v.end(), b_compare);
    return v[i+k%n].second;
}