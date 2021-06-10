#include <bits/stdc++.h>

/**
 * 10.06.2021
 * transportation
 *
 * @author Havlong
 * @version v1.0
 */

/**
 * Test

3 5

20 10 12 13 16
25 19 20 14 10
17 18 15 10 17

200 300 250
210 150 120 135 135
 */
#define VI vector<int>
#define VVI vector<VI>
#define PII pair<int, int>
#define ALL(x) x.begin(), x.end()

using namespace std;

void printSolution(VVI &solution) {
    for (auto &line: solution) {
        for (auto &x: line) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    cout << '\n' << endl;
}

bool check(const VVI &solution, const VI &a, const VI &b) {
    int count = 0;
    for (auto &line: solution) {
        for (auto &x: line) {
            count += x > 0;
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        int sum = 0;
        for (int j = 0; j < b.size(); ++j) {
            sum += solution[i][j];
        }
        if (sum != a[i]) {
            cout << "Решение не удовлетворяет ограничениям" << endl;
            return false;
        }
    }
    for (int j = 0; j < b.size(); ++j) {
        int sum = 0;
        for (int i = 0; i < a.size(); ++i) {
            sum += solution[i][j];
        }
        if (sum != b[j]) {
            cout << "Решение не удовлетворяет ограничениям" << endl;
            return false;
        }
    }
    if (count != solution.size() + solution.back().size() - 1) {
        cout << "Решение вырождено" << endl;
        return false;
    }
    return true;
}

bool initPotential(VI &u, VI &v, const VVI &c, const VVI &solution) {
    PII pos = {0, 0};
    v[0] = c[0][0] - u[0];
    for (int i = 0; i < u.size() + v.size() - 1; ++i) {
        auto &[x, y] = pos;
        if (solution[x][y + 1] != 0) {
            y++;
            u[y] = c[x][y] - v[x];
        } else {
            x++;
            v[x] = c[x][y] - u[y];
        }
    }
    for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j < c.back().size(); ++j) {
            if (solution[i][j] == 0 && u[j] + v[i] > c[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void matching(VVI &solution, const VVI &c, const PII &v) {

}

void solve(VVI &solution, const VI &a, const VI &b, const VVI &c) {
    VI u(b.size());
    VI v(a.size());
    while (!initPotential(u, v, c, solution)) {
        PII newPoint = {-1, -1};
        for (int i = 0; i < c.size(); i++) {
            for (int j = 0; j < c.back().size(); ++j) {
                auto &[x, y] = newPoint;
                if (solution[i][j] == 0 &&
                    (u[j] + v[i] - c[i][j] > u[y] + v[x] - c[x][y] || x == -1 && y == -1
                     || (u[j] + v[i] - c[i][j] == u[y] + v[x] - c[x][y] && c[i][j] < c[x][y]))) {
                    x = i, y = j;
                }
            }
        }
        matching(solution, c, newPoint);
    }
}

void init(VVI &solution, VI a, VI b, VVI &c) {
    PII pos = {0, 0};
    for (int i = 0; i < a.size() + b.size(); ++i) {
        auto &[x, y] = pos;
        if (x == a.size() - 1 || a[x] >= b[y]) {
            solution[x][y] = b[y];
            b[y] = 0;
            a[x] -= solution[x][y];
            y++;
        } else  {
            solution[x][y] = a[x];
            a[x] = 0;
            b[y] -= solution[x][y];
            x++;
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    cout << setprecision(2) << fixed;

    VVI c(n, vector<int>(m));
    VI a(n);
    VI b(m);
    for (auto &line: c) {
        for (auto &x: line) {
            cin >> x;
        }
    }

    for (auto &x: a) {
        cin >> x;
    }
    for (auto &x: b) {
        cin >> x;
    }

    if (accumulate(ALL(a), 0) != accumulate(ALL(b), 0)) {
        cout << "Balance isn't fulfilled!" << endl;
        int aSum = accumulate(ALL(a), 0), bSum = accumulate(ALL(b), 0);
        if (aSum < bSum) {
            b.push_back(bSum - aSum);
            for (auto &x: c) {
                x.push_back(0);
            }
            m++;
        } else {
            a.push_back(aSum - bSum);
            c.emplace_back(m, 0);
            n++;
        }
    }

    VVI solution(n, vector<int>(m));
    init(solution, a, b, c);
    cout << "Start solution" << endl;
    printSolution(solution);
    if (!check(solution, a, b)) {
        return 0;
    }
    solve(solution, a, b, c);
    cout << "Final solution" << endl;
    printSolution(solution);
}