package poj.q1852;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    static int length, ants, pos[];
    static Scan scan = new Scan();

    public static void main(final String[] args) {
        int testCases = scan.nextInt();
        while (testCases-- != 0) {
            reader();
            solve();
        }
    }

    static void reader() {
        length = scan.nextInt();
        ants = scan.nextInt();
        pos = new int[ants];
        for (int i = 0; i < ants; i++) {
            pos[i] = scan.nextInt();
        }
    }

    static void solve() {
        int minTime = Integer.MIN_VALUE, maxTime = Integer.MIN_VALUE;
        for (final int position : pos) {
            minTime = Math.max(minTime, Math.min(position, length - position));
            maxTime = Math.max(maxTime, Math.max(position, length - position));
        }
        System.out.println(minTime + " " + maxTime);
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
        while (tok == null || !tok.hasMoreElements()) {
            try {
                tok = new StringTokenizer(buffer.readLine());
            } catch (final Exception e) {
                return false;
            }
        }
        return true;
    }

    private String next() {
        if (hasNext()) {
            return tok.nextToken();
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