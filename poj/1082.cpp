/*********** ״̬���� (�ҹ��ɣ�ǿ����) ************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int y, m, d;

//��ʤ̬�������п��Ƶ���״̬�����ٴ���һ�������ذ�̬
//1��(m+d)ż��ȫΪ��ʤ̬���ڿ��Ƶ���״̬��ش���һ����m+d��Ϊ���������ﲻ���Ͻ������ϡ��Ҹ�������Ӧ��״̬Ϊ�ذ�̬������
//2�� ���ڣ�m+d��Ϊ�����ģ�ֻҪ�����Ŀ��Ƶ�״̬����ڱذ�̬�����״̬��ʤ
//�ذ�̬�������п��Ƶ���״̬��ȫΪ��ʤ̬
inline bool CheckWin(){
    if((m + d) % 2 == 0) return true;
    if(d == 30 && (m == 9 || m == 11) ) return true;
    return false;
}

int main(){
    int test;
    scanf("%d", &test);
    while(test--){
        scanf("%d %d %d", &y, &m, &d);
        printf("%s\n", CheckWin() ? "YES" : "NO");
    }
    return 0;
}
