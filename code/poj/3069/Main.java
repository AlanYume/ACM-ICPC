package com.alanyume.acm.poj3069;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static Scanner scan = new Scanner();
    static int n;
    static char[] s;

    static void read() {
        n = scan.nextInt();
        s = new char[n];
        for (int i = 0; i < n; i++) {
            s[i] = scan.next().charAt(0);
        }
    }

    static void solve() {
        int printCharCnt = 0;
        int leftIndex = 0, rightIndex = n - 1;
        while (leftIndex <= rightIndex) {
            boolean chooseLeft = false;
            for (int addIndex = 0; leftIndex + addIndex <= rightIndex; addIndex++) {
                if (s[leftIndex + addIndex] < s[rightIndex - addIndex]) {
                    chooseLeft = true;
                    break;
                } else if (s[leftIndex + addIndex] > s[rightIndex - addIndex]) {
                    chooseLeft = false;
                    break;
                }
            }

            System.out.print(chooseLeft ? s[leftIndex++] : s[rightIndex--]);
             if((++printCharCnt) % 80 == 0) {
                System.out.println();
            }
        }

        if (printCharCnt % 80 != 0) {
            System.out.println();
        }
    }

    public static void main(String[] args) {
        read();
        solve();
    }
}

class Scanner {
    BufferedReader buffer;
    StringTokenizer tok;

    Scanner () {
        buffer = new BufferedReader(new InputStreamReader(System.in));
    }

    private boolean haveNext() {
        while(tok == null || !tok.hasMoreElements()) {
            try {
                tok = new StringTokenizer(buffer.readLine());
            } catch (Exception e) {
                return false;
            }
        }
        return true;
    }

    String next() {
        if (haveNext()) {
           return tok.nextToken();
        }
        return null;
    }

   String nextLine() {
       if (haveNext()) {
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