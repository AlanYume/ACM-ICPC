/********* DFS + 贪心 + 减枝 ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMaxN = 64 + 10;

int n, sum_len, enum_len;
int stick[kMaxN];
bool used_stick[kMaxN];

bool CheckLen(int used_tick_num, int now_len, int now_stick_id) {
    if (now_stick_id == -1) {
        if (now_len != enum_len) return false;
    }
    if (now_len == 0) {
        for (int i = now_stick_id; i >= 0; i--) {
            if (used_stick[i] == false) {
                used_stick[i] = true;
                if (CheckLen(used_tick_num + 1, stick[i], i - 1) == true) return true;
                used_stick[i] = false;
                return false;
            }
        }
        return false;
    } else if (now_len == enum_len) {
        if (used_tick_num == n) return true;
        return CheckLen(used_tick_num, 0, n - 1);
    } else {
        for (int i = now_stick_id; i >= 0; i--) {
            if (used_stick[i] == false && now_len + stick[i] <= enum_len) {
                if (used_stick[i + 1] == false && stick[i] == stick[i + 1]) continue;
                used_stick[i] = true;
                if (CheckLen(used_tick_num + 1, now_len + stick[i], i - 1) == true) return true;
                used_stick[i] = false;
            }
        }
        return false;
    }
}


int GetMinLen() {
    memset(used_stick, false, sizeof(used_stick));
    for (int i = stick[n - 1]; i <= sum_len; i++) {
        if (sum_len % i == 0) {
            enum_len = i;
            if (CheckLen(0, 0, n - 1) == true) return i;
        }
    }
}

int main() {
    while (~scanf("%d", &n)) {
        if (n == 0) break;
        sum_len = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &stick[i]);
            sum_len += stick[i];
        }
        sort(stick, stick + n);
        printf("%d\n", GetMinLen());
    }
    return 0;
}
