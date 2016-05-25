package cf.a666;
/**
 * Created by yume on 2016/5/25.
 */

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.TreeSet;

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

    static class TaskA{
        public void solve(InputReader in, PrintWriter out) {
            String s = in.next();
            int sLen = s.length();
            boolean[][] can = new boolean[sLen + 1][2];
            can[sLen - 2][0] = can[sLen - 3][1] = true;
            for (int pos = sLen - 4; pos >= 5; pos--) {
                for (int len = 2; len <= 3; len++) {
                    for (int nLen = 2; nLen <= 3 && pos + len + nLen <= sLen; nLen++) {
                        if (can[pos + len][nLen - 2]) {
                            boolean ok = true;
                            if (len == nLen) {
                                ok = false;
                                for (int i = 0; i < len; i++) {
                                    if (s.charAt(pos + i) != s.charAt(pos + len + i)) {
                                        ok = true;
                                    }
                                }
                            }
                            if (ok) {
                                can[pos][len - 2] = true;
                            }
                        }
                    }
                }
            }
            TreeSet<String> suffixes = new TreeSet<>();
            for (int pos = sLen; pos >= 5; pos--) {
                for (int len = 2; len <= 3; len++) {
                    if (can[pos][len - 2]) {
                        suffixes.add(s.substring(pos, pos + len));
                    }
                }
            }
            out.println(suffixes.size());
//            suffixes.stream().forEach(suffix -> out.println(suffix));
            for(String suffix : suffixes) {
                out.println(suffix);
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