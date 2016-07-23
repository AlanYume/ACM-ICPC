package cf.a226;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.StringTokenizer;

/**
 * Created by yume on 7/22/2016.
 */

public class Main {
    public static void main(final String[] args) {
        final InputStream inputStream = System.in;
        final OutputStream outputStream = System.out;
        final InputReader in = new InputReader(inputStream);
        final PrintWriter out = new PrintWriter(outputStream);
        final TaskC solver = new TaskC();
        solver.solve(in, out);
        out.close();
    }

    static class TaskC {
        public void solve(final InputReader in, final PrintWriter out) {
            final BigInteger n = in.nextBigInteger();
            final BigInteger m = in.nextBigInteger();
            final BigInteger ans = (new BigInteger("3").modPow(n, m)).subtract(BigInteger.ONE).mod(m);
            out.println(ans);
        }
    }

    static class InputReader {
        private final BufferedReader buffer;
        private StringTokenizer tok;

        InputReader(final InputStream stream) {
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

        protected BigInteger nextBigInteger() {
            return new BigInteger(next());
        }
    }
}