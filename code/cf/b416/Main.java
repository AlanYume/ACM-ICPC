package cf.b416;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * Created by yume on 7/15/2016.
 */

public class Main {
    public static void main(final String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskJ solver = new TaskJ();
        solver.solve(in, out);
        out.close();
    }

    static class TaskJ {
        public void solve(InputReader in, PrintWriter out) {
            int m = in.nextInt();
            int n = in.nextInt();
            int[][] t = new int[m][n];
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    t[i][j] = in.nextInt();
                }
            }

            for (int i = 0; i < m; i++) { // picture
                for (int j = 0; j < n; j++) { // painter
                    if (i == 0 && j == 0) {
                        continue;
                    } else if (i == 0) {
                        t[i][j] += t[i][j - 1];
                    } else if (j == 0) {
                        t[i][j] += t[i - 1][j];
                    } else{
                        t[i][j] += Math.max(t[i][j - 1], t[i - 1][j]);
                    }
                }
            }

            out.print(t[0][n - 1]);
            for (int i = 1; i < m; i++) {
                out.print(" " + t[i][n -1]);
            }
            out.println();
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