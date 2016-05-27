package cf.a668;
/**
 * Created by yume on 2016/5/27.
 */

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class Main {
    public static void main(final String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskA solver = new TaskA();
        solver.solve(in, out);
        out.close();
    }

    static class TaskA {
        public void solve(InputReader in, PrintWriter out) {
            int h = in.nextInt();
            int w = in.nextInt();
            int q = in.nextInt();
            int[] t = new int[q];
            int[] r = new int[q];
            int[] c = new int[q];
            int[] x = new int[q];
            for (int i = 0; i < q; i++) {
                t[i] = in.nextInt();
                switch (t[i]) {
                case 1:
                    r[i] = in.nextInt() - 1;
                    break;
                case 2:
                    c[i] = in.nextInt() - 1;
                    break;
                case 3:
                    r[i] = in.nextInt() - 1;
                    c[i] = in.nextInt() - 1;
                    x[i] = in.nextInt();
                    break;
                }
            }

            // make answer matrix
            int[][] matrix = new int[h][w];
            for (int i = 0; i < q; i++) {
                if (t[i] == 3) {
                    int curR = r[i];
                    int curC = c[i];
                    for (int j = i; j >= 0; j--) {
                        if (t[j] == 1 && r[j] == curR) {
                            curC = (curC + 1) % w;
                        } else if (t[j] == 2 && c[j] == curC) {
                            curR = (curR + 1) % h;
                        }
                    }
                    matrix[curR][curC] = x[i];
                }
            }


            // print answer
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (j != 0) out.print(" ");
                    out.print(matrix[i][j]);
                }
                out.println();
            }
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