/************  KMƥ���㷨��� ���Ȩƥ�䣨��֤������ƥ�䣩 *******************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int kINF = 0x3f3f3f3f;
const int kMaxN = 300 + 16;

int n, nx, ny;
int edge[kMaxN][kMaxN];
int link[kMaxN], lx[kMaxN], ly[kMaxN], slack[kMaxN];
bool visit_X[kMaxN], visit_Y[kMaxN];

bool Dfs(int x){ //���������㷨��Hungary��
	visit_X[x] = true;
	for(int y = 0; y < ny; y++){
		if(visit_Y[y] == true) continue;
		int tmp_val = lx[x] + ly[y] - edge[x][y];
		if(tmp_val == 0){ //���б�
			visit_Y[y] = true;
			if(link[y] == -1 || Dfs(link[y])){
				link[y] = x;
				return true;
			}
		}else if(slack[y] > tmp_val){ //�����
			slack[y] = tmp_val;
		}
	}
	return false;
}

int KM(){
	nx = ny = n;
	memset(link, -1, sizeof(link));
	for(int x = 0; x < nx; x++){
		lx[x] = -kINF;
		for(int y = 0; y < ny; y++){ //lx[x] ȡ��������Ȩ�����ֵ
			lx[x] = max(lx[x], edge[x][y]);
		}
	}
	memset(ly, 0, sizeof(ly)); //ly[y] ȡ��Ȩֵ 0

	for(int x = 0; x < nx; x++){ //Ϊ��xѰ������ƥ��
		fill(slack, slack + sizeof(slack) / sizeof(int), kINF);
		while(true){
			memset(visit_X, false, sizeof(visit_X)); //��ʼ�� S��T����Ϊ��
			memset(visit_Y, false, sizeof(visit_Y));
			if(Dfs(x)) break;  //���ɹ����ҵ�������죩����õ�������ɣ�������һ���������

			//��ʧ�ܣ�û���ҵ�����죩������Ҫ�ı�һЩ��ı�ţ�ʹ��ͼ�п��бߵ��������ӡ�
			//����Ϊ����������������У���������������б���������X����ı��ȫ����ȥһ������d��
			//������������е�Y����ı��ȫ������һ������d

			int min_d = kINF;
			for(int j = 0; j < ny; j++){ //�ҽ���������Сd
				if(visit_Y[j] == false && min_d > slack[j]){
					min_d = slack[j];
				}
			}

			for(int i = 0; i < nx; i++){ //���µ��i -d
				if(visit_X[i] == true) lx[i] -= min_d;
			}
			for(int j = 0; j < ny; j++){ //���±߱�y +d
				if(visit_Y[j] == true){
					ly[j] += min_d;
				}else{ //��Ϊy����T�����ڣ���s�ڼ����ڵģ�slack[y] = lx[x] + ly[y] - edge[x][y],��ʱl[x]��С��d������slack[y] -d
					slack[j] -= min_d;
				}
			}
		}
	}

	int res = 0;
	for(int y = 0; y < ny; y++){ //����ƥ��link[y]�������Ȩƥ��
		if(link[y] != -1) res += edge[link[y]][y];
	}
	return res;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &edge[i][j]);
			}
		}
		int ans = KM();
		printf("%d\n", ans);
	}
	return 0;
}