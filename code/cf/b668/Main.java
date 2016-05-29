package cf.b668;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * Created by yume on 5/29/2016.
 */

public class Main {
    public static void main(final String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Task solver = new Task();
        solver.solve(in, out);
        out.close();
    }

    static class Task {
        public void solve(InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int q = in.nextInt();

            int first = 0;
            int second = 1;
            for (int i = 0; i < q; i++) {
                int t = in.nextInt();
                if (t == 1) {
                    int offset = in.nextInt();
                    offset = (-offset + n) % n;
                    if ((offset & 1) == 0) {
                        first = (first + offset) % n;
                        second = (second + offset) % n;
                    } else {
                        int tmp = first;
                        first = (second + offset - 1 + n) % n;
                        second = (tmp + offset + 1) % n;
                    }
                } else {
                    int tmp = first;
                    first = second;
                    second = tmp;
                }
            }

            for (int i = 0; i * 2 < n; i++) {
                if (i != 0) out.print(" ");
                out.print((first + 2 * i) % n + 1);
                out.print(" ");
                out.print((second + 2 * i) % n + 1);
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