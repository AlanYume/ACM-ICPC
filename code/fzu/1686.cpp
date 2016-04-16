/********* 可重复覆盖（Dancing Link X) ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int N = 15;
const int kMaxN = N*N+10;
const int kMaxM = N*N+10;
const int kMaxNode = kMaxN * kMaxM;

int n, m, n1, m1;
int id[N][N];

class DLX {
private:
    int n, m, size;
    int U[kMaxNode], D[kMaxNode], L[kMaxNode], R[kMaxNode], Row[kMaxNode], Col[kMaxNode];
    int H[kMaxN], S[kMaxM];
    int ansd;

    bool v[kMaxM];
    int H_g() { //评估函数，结果必须偏大（于等于）
        int ret = 0;
        for(int c = L[0]; c != 0; c = L[c]) v[c] = true;
        for(int c = L[0]; c != 0; c = L[c]) {
            if(v[c]) {
                ret++;
                v[c] = false;
                for(int i = U[c]; i != c; i = U[i]) {
                    for(int j = L[i]; j != i; j = L[j]) {
                        v[Col[j]] = false;
                    }
                }
            }
        }
        return ret;
    }
	
	void ReMove(int c) {
        for(int i = U[c]; i !=c ; i = U[i]) {
            L[R[i]] = L[i];
            R[L[i]] = R[i];
        }
    }

    void ReSume(int c) {
        for(int i = D[c]; i != c; i = D[i]) {
            L[R[i]] = R[L[i]] = i;
        }
    }

public:
    void Init(int _n, int _m) {
        ansd = kINF;
        n = _n;
        m = _m;
        for(int i = 0; i <= m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        L[0] = m;
        R[m] = 0;
        size = m;
        for(int i = 1; i <= n; i++) H[i] = -1;
    }

    void Link(int r, int c) {
        S[c]++;
        Row[++size] = r;
        Col[size] = c;
        U[size] = U[c];
        D[U[c]] = size;
        D[size] = c;
        U[c] = size;
        if(H[r] == -1) {
            H[r] = L[size] = R[size] = size;
        } else {
            L[size] = L[H[r]];
            R[L[H[r]]] = size;
            R[size] = H[r];
            L[H[r]] = size;
        }
    }

    void Dance(int d) {
        if(d + H_g() >= ansd) return ;
        if(R[0] == 0) {
            if(d < ansd) ansd = d;
            return ;
        }
        int c = L[0];
        for(int i = L[0]; i != 0; i = L[i]) {
            if(S[i] < S[c]) c = i;
        }
        for(int i = U[c]; i != c; i = U[i]) {
            ReMove(i);
            for(int j = L[i]; j != i; j = L[j]) ReMove(j);
            Dance(d+1);
            for(int j = R[i]; j != i; j = R[j]) ReSume(j);
            ReSume(i);
        }
    }

    int GetAns() {
        return ansd;
    }
} dlx;

int main() {
    while(~scanf("%d %d", &n, &m)) {
        int tmp_size = 0;
        memset(id, 0, sizeof(id));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int tmp;
                scanf("%d", &tmp);
                if(tmp == 1) id[i][j] = (++tmp_size);
            }
        }
        dlx.Init(n*m, tmp_size);
        tmp_size = 1;
        scanf("%d %d", &n1, &m1);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int x = 0; x < n1 && i + x < n; x++) {
                    for(int y = 0; y < m1 && j + y < m; y++) {
                        if(id[i+x][j+y]) {
                            dlx.Link(tmp_size, id[i+x][j+y]);
                        }
                    }
                }
                tmp_size++;
            }
        }
        dlx.Dance(0);
        printf("%d\n", dlx.GetAns());
    }
    return 0;
}

