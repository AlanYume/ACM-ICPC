/******* 强大减枝 ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 5;
const int kMaxTickSize = (kMaxN + 1) * kMaxN * 2 + 10;
const int kMaxBlockSize = 55 + 10;

int n, m;
int block_size[kMaxN + 1];
vector<int> Tick[kMaxN + 1][kMaxTickSize], Block[kMaxN + 1][kMaxBlockSize];
int can_used_tick_size;
vector<int> CanUesedTick;
int MaxTickIdBelongToBlock[kMaxBlockSize];
bool destroy_tick[kMaxBlockSize];

void GetTickAndBlock(int n) {
    block_size[n] = 0;
    for (int size = n; size >= 1; size--) {
        for (int i = 1; i <= size; i++) {
            int tmp_u = 1 + (i - 1) * (2 * n + 1);
            int tmp_l = tmp_u + n;
            int tmp_d = tmp_u + (2 * n + 1) * (n - size + 1);
            int tmp_r = tmp_l + (n - size + 1);
            for (int j = 1; j <= size; j++) {
                ++block_size[n];
                for (int len = 0; len < n - size + 1; len++) {
                    Tick[n][tmp_u + len].push_back(block_size[n]);
                    Block[n][block_size[n]].push_back(tmp_u + len);

                    Tick[n][tmp_l + len * (2 * n + 1)].push_back(block_size[n]);
                    Block[n][block_size[n]].push_back(tmp_l + len * (2 * n + 1));

                    Tick[n][tmp_d + len].push_back(block_size[n]);
                    Block[n][block_size[n]].push_back(tmp_d + len);

                    Tick[n][tmp_r + len * (2 * n + 1)].push_back(block_size[n]);
                    Block[n][block_size[n]].push_back(tmp_r + len * (2 * n + 1));
                }
                tmp_u++;
                tmp_l++;
                tmp_d++;
                tmp_r++;
            }
        }
    }
}

inline void InitTickAndBlock() {
    for (int i = 1; i <= kMaxN; i++) GetTickAndBlock(i);
}

inline int GetTickSize(int n) {
    return (n + 1) * n * 2;
}

int Hstar(int p, vector<bool> state) {
    vector<pair<int, int> > ps;
    for (int i = 1; i <= block_size[n]; i++) {
        if (state[i] == false) {
            int block_id = i;
            int num = 0;
            for (int j = 0; j < Block[n][block_id].size(); j++) {
                if (destroy_tick[Block[n][block_id][j]] == false && Block[n][block_id][j] >= p)
                    num++;
            }
            if (num > 0) ps.push_back(make_pair(num, block_id));
        }
    }
    sort(ps.begin(), ps.end());
    int res = 0;
    vector<bool> used(kMaxTickSize + 1, false);
    for (int i = 0; i < ps.size(); i++) {
        int id = ps[i].second;
        bool ok = true;
        for (int j = 0; j < Block[n][id].size(); j++) {
            if (destroy_tick[Block[n][id][j]] == false && used[Block[n][id][j]] == true) ok = false;
        }
        if (ok) {
            res++;
            for (int j = 0; j < Block[n][id].size(); j++) {
                used[Block[n][id][j]] = true;
            }
        }
    }
    return res;
}

int min_res;

int Dfs(int p, int num, vector<bool> state) {
    if (p == can_used_tick_size) return min_res = num;
    if (num + Hstar(p, state) >= min_res) return kINF;

    bool use = false, notuse = true;
    int tick_id = CanUesedTick[p];
    for (int i = 0; i < Tick[n][tick_id].size(); i++) {
        if (state[Tick[n][tick_id][i]] == false) {
            notuse = false;
            if (MaxTickIdBelongToBlock[Tick[n][tick_id][i]] == tick_id) use = true;
        }
    }
    int res = kINF;
    if (!use) res = min(res, Dfs(p + 1, num, state));
    if (!notuse) {
        for (int i = 0; i < Tick[n][tick_id].size(); i++) {
            state[Tick[n][tick_id][i]] = true;
        }
        res = min(res, Dfs(p + 1, num + 1, state));
    }
    return res;
}

int main() {
    InitTickAndBlock();
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &m);
        int tick_size = GetTickSize(n);
        for (int i = 1; i <= tick_size; i++) destroy_tick[i] = false;

        vector<bool> destroy_block(block_size[n] + 1, false);
        while (m--) {
            int tmp_tick_id;
            scanf("%d", &tmp_tick_id);
            destroy_tick[tmp_tick_id] = true;
            for (int j = 0; j < Tick[n][tmp_tick_id].size(); j++) {
                destroy_block[Tick[n][tmp_tick_id][j]] = true;
            }
        }
        CanUesedTick.clear();
        memset(MaxTickIdBelongToBlock, 0, sizeof(MaxTickIdBelongToBlock));
        for (int i = 1; i <= tick_size; i++) {
            if (destroy_tick[i] == false) {
                CanUesedTick.push_back(i);
                for (int j = 0; j < Tick[n][i].size(); j++) {
                    MaxTickIdBelongToBlock[Tick[n][i][j]] = i;
                }
            }
        }
        can_used_tick_size = CanUesedTick.size();
        min_res = kINF;
        printf("%d\n", Dfs(0, 0, destroy_block));
    }
    return 0;
}
