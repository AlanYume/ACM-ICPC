package cf.b666;
/**
 * Created by yume on 2016/5/25.
 */

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class Mian {
    public static void main(final String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        TaskB solver = new TaskB();
        solver.solve(in, out);
        out.close();
    }

    static class TaskB {
        public void solve(InputReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            City[] cities = new City[n];
            for (int i = 0; i < n; i++) {
                cities[i] = new City(i);
            }
            for (int i = 0; i < m; i++) {
                City a = cities[in.nextInt() - 1];
                City b = cities[in.nextInt() - 1];
                a.outgo.add(b);
            }

            // spfa
            int [][] dist = new int[n][n];
            City[] que = new City[n];
            for (int i = 0; i < n; i++) {
                for (City c : cities) {
                    c.dist = -1;
                }
                cities[i].dist = 0;
                int queTop = 0;
                int queBottom = 1;
                que[0] = cities[i];
                while (queTop < queBottom) {
                    City cur = que[queTop++];
                    for (City other : cur.outgo) {
                        if (other.dist < 0) {
                            other.dist = cur.dist + 1;
                            que[queBottom++] = other;
                        }
                    }
                }
                for (int j = 0; j < n; j++) {
                    dist[i][j] = cities[j].dist;
                }
            }

            // make city.closestIn
            int[] first = new int[n];
            int[] next = new int[n];
            for (int i = 0; i < n; i++) {
                Arrays.fill(first, -1);
                for (int j = 0; j < n; j++) {
                    int curDist = dist[i][j];  // note
                    if (curDist < 0) continue;
                    next[j] = first[curDist];
                    first[curDist] = j;
                }
                int ptr = 0;
                outer:
                for(int curDist = n - 1; curDist > 0; curDist--) {
                    int curCity = first[curDist];
                    while(curCity >= 0) {
                        cities[i].closestOut[ptr++] = cities[curCity];
                        if (ptr == 3) break outer;
                        curCity = next[curCity];
                    }
                }
            }
            // make city.closestOut
            for (int i = 0; i < n; i++) {
                Arrays.fill(first, -1);
                for (int j = 0; j < n; j++) {
                    int curDist = dist[j][i]; // note
                    if (curDist < 0) continue;
                    next[j] = first[curDist];
                    first[curDist] = j;
                }
                int ptr = 0;
                outer:
                for (int curDist = n - 1; curDist > 0; curDist--) {
                    int curCity = first[curDist];
                    while(curCity >= 0) {
                        cities[i].closestIn[ptr++] = cities[curCity];
                        if (ptr == 3) break outer;
                        curCity = next[curCity];
                    }
                }
            }

            // find four cities
            int resDist = 0;
            City[] anserCity = new City[4];
            for (City b : cities) {
                b.mark = true;
                for (City c : cities) {
                    if (!c.mark) {
                        int bcDist = dist[b.index][c.index];
                        if (bcDist < 0) continue;
                        c.mark = true;
                        for (City a : b.closestIn) {
                            if (a != null && !a.mark) {
                                int abDist = dist[a.index][b.index];
                                if (abDist < 0) continue;
                                a.mark = true;
                                for (City d : c.closestOut) {
                                    if (d != null && !d.mark) {
                                        int cdDist = dist[c.index][d.index];
                                        if (cdDist < 0) continue;
                                        d.mark = true;
                                        int curDist = abDist + bcDist + cdDist;
                                        if (curDist > resDist) {
                                            resDist = curDist;
                                            anserCity[0] = a;
                                            anserCity[1] = b;
                                            anserCity[2] = c;
                                            anserCity[3] = d;
                                        }
                                        d.mark = false;
                                    }
                                }
                                a.mark = false;
                            }
                        }
                        c.mark = false;
                    }
                }
                b.mark = false;
            }

            out.println((anserCity[0].index + 1) + " " + (anserCity[1].index + 1) + " " +
                    (anserCity[2].index + 1) + " " + (anserCity[3].index + 1));
        }

        static class City {
            int index;
            int dist;
            List<City> outgo = new ArrayList<>();
            boolean mark = false;
            City[] closestIn = new City[3];
            City[] closestOut = new City[3];

            public City(int index) {
                this.index = index;
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