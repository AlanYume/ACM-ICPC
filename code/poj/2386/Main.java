package com.alanyume.acm.poj2386;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static Scan scan = new Scan();
    static int n, m;
    static char[][] field;

    static void read() {
        n = scan.nextInt();
        m = scan.nextInt();
        field = new char[n][];
        for (int i = 0; i < n; i++) {
            field[i] = scan.nextLine().toCharArray();
        }
    }

    static void dfs(int x, int y) {
        field[x][y] = '.';
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int nx = x + dx, ny = y + dy;
                if (0 <= nx && nx < n && 0 <= ny && ny < m && field[nx][ny] == 'W') {
                    dfs(nx, ny);
                }
            }
        }
    }

    static void solve() {
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (field[i][j] == 'W') {
                    dfs(i, j);
                    res++;
                }
            }
        }
        System.out.println(res);
    }

    public static void main(String[] args) {
        read();
        solve();
    }
}

/**
 * inputClass
 */
class Scan {
    BufferedReader buffer;
    StringTokenizer tok;

    Scan() {
        buffer = new BufferedReader(new InputStreamReader(System.in));
    }

    private boolean hasNext() {
        while(tok == null || !tok.hasMoreElements()) {
            try {
                tok = new StringTokenizer(buffer.readLine());
            } catch (Exception e) {
                return false;
            }
        }
        return true;
    }

    private String next() {
        if (hasNext()) {
            return  tok.nextToken();
        }
        return null;
    }

    String nextLine() {
        if (hasNext()) {
            return tok.nextToken("\n");
        }
        return null;
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    double nextDouble() {
        return Double.parseDouble(next());
    }
}