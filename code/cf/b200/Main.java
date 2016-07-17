package cf.b200;

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
        TaskC solver = new TaskC();
        solver.solve(in, out);
        out.close();
    }

    static class TaskC {
        public void solve(InputReader in, PrintWriter out) {
            int n = in.nextInt();
            double sum = 0;
            for (int i = 0; i < n; i++) {
                double tmp = in.nextDouble();
                sum += tmp;
            }
            out.println(sum / n);
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