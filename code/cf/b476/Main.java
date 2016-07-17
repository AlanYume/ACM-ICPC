package cf.b476;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * Created by yume on 7/16/2016.
 */

public class Main {
    public static void main(final String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskH solver = new TaskH();
        solver.solve(in, out);
        out.close();
    }

    static class TaskH {
        public void solve(InputReader in, PrintWriter out) {
            String s1 = in.nextLine();
            String s2 = in.nextLine();

            int addNum1 = 0, subNum1 = 0;
            for (char c : s1.toCharArray()) {
                if (c == '+') {
                    addNum1++;
                } else {
                    subNum1++;
                }
            }
            int addNum2 = addNum1, subNum2 = subNum1;
            for (char c : s2.toCharArray()) {
                if (c == '+') {
                    addNum2--;
                } else if (c == '-') {
                    subNum2--;
                }
            }

            double ans;
            if (addNum2 < 0 || subNum2 < 0) {
                ans = 0;
            } else {
                long base = addNum2 + subNum2;
                ans = (double)mCn(base, addNum2) / (1 << base);
            }
            out.println(ans);
        }

        private long mCn (long m, long n) {
            long result = 1;
            long repeteCnt = Math.min(m - n, n);
            for (int i = 1; i <= repeteCnt; i++) {
                result = result * (m - i + 1) / i;
            }
            return result;
        }
    }

    static class InputReader {
        private final BufferedReader buffer;
        private StringTokenizer tok;

        InputReader(InputStream stream) {
            buffer = new BufferedReader(new InputStreamReader(stream), 32768);
        }

        private boolean haveNext() {
            while (tok == null || !tok.hasMoreElements()) {
                try {
                    tok = new StringTokenizer(buffer.readLine());
                } catch (final Exception e) {
                    throw new RuntimeException(e);
                }
            }
            return true;
        }

        protected String next() {
            if (haveNext()) {
                return tok.nextToken();
            }
            return null;
        }

        protected String nextLine() {
            if (haveNext()) {
                return tok.nextToken("\n");
            }
            return null;
        }

        protected int nextInt() {
            return Integer.parseInt(next());
        }

        protected long nextLong() {
            return Long.parseLong(next());
        }

        protected double nextDouble() {
            return Double.parseDouble(next());
        }
    }
}