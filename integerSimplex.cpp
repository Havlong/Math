#include <bits/stdc++.h>

/**
 * 18.03.2021
 * doubleSimplex
 *
 * @author Havlong
 * @version v1.0
 */

#define double long double
#define line vector<double>
#define matrix vector<vector<double>>
#define ALL(x) x.begin(), x.end()

using namespace std;

void printTable(const map<int, line > &resources, const line &values) {
    for (const auto &basisLine: resources) {
        cout << "x" << basisLine.first + 1 << ' ';
        for (const auto &x: basisLine.second) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    cout << "z  ";
    for (const auto &z : values) {
        cout << z << ' ';
    }
    cout << "\n\n";
}

const double INF = 1e18;

void swapBasisVariables(map<int, line > &resources, line &values, const int &fromBasis, const int &toBasis) {
    for (auto &[basis, coeffs]: resources) {
        if (basis == fromBasis)
            continue;
        double k = -coeffs[toBasis] / resources[fromBasis][toBasis];
        for (int i = 0; i < coeffs.size(); ++i) {
            coeffs[i] += resources[fromBasis][i] * k;
        }
    }
    double k = -values[toBasis] / resources[fromBasis][toBasis];
    for (int i = 0; i < values.size(); ++i) {
        values[i] += k * resources[fromBasis][i];
    }
    resources[toBasis] = resources[fromBasis];
    for (int i = 0; i < resources[toBasis].size(); ++i) {
        resources[toBasis][i] /= resources[fromBasis][toBasis];
    }
    resources.erase(fromBasis);
}

line solveDoubleSimplex(map<int, line > &resources, line &values) {

    while (!all_of(ALL(values), [](const double &x) { return x >= 0; })) {
        if (all_of(ALL(resources), [](const pair<int, line > &x) { return x.second.back() >= 0; })) {
            int toBasis = min_element(values.begin(), values.end() - 1) - values.begin();
            int fromBasis = resources.size();
            double simplexValue = INF;
            for (auto &[basis, coeffs]: resources) {
                if (coeffs[toBasis] <= 0)
                    continue;
                double newValue = coeffs.back() / coeffs[toBasis];
                if (newValue > 0 && newValue < simplexValue) {
                    fromBasis = basis;
                    simplexValue = newValue;

                }
            }
            if (simplexValue == INF) {
                cout << "No solution";
                return line();
            }
            swapBasisVariables(resources, values, fromBasis, toBasis);
        } else {
            int fromBasis = resources.begin()->first;

            for (auto &[basis, coeffs]: resources) {
                if (coeffs.back() < resources[fromBasis].back())
                    fromBasis = basis;
            }

            double simplexValue = INF;
            int toBasis = 0;
            for (int i = 0; i < resources[fromBasis].size() - 1; ++i) {
                if (resources[fromBasis][i] < 0) {
                    double newValue = abs(values[i] / resources[fromBasis][i]);
                    if (newValue < simplexValue) {
                        simplexValue = newValue;
                        toBasis = i;
                    }
                }
            }
            if (simplexValue == INF) {
                cout << "No solution";
                return line();
            }
            swapBasisVariables(resources, values, fromBasis, toBasis);
        }
        printTable(resources, values);
    }
    line x(values.size(), 0);
    for (int i = 0; i < values.size(); ++i) {
        if (resources.count(i))
            x[i] = resources[i].back();
    }
    return x;
}

vector<int> solveInteger(map<int, line > &resources, line &values) {
    while (true) {
        line d = solveDoubleSimplex(resources, values);
        if (d.empty())
            return {};
        int v = max_element(ALL(d), [](double x, double y) { return x - (int) x < y - (int) y; }) - d.begin();
        if (d[v] - (int) v == 0) {
            vector<int> ans(d.size());
            for (int i = 0; i < d.size(); ++i) {
                ans[i] = (int) d[i];
            }
            return ans;
        }
        bool found = false;
        for (const auto &x: resources[v]) {
            if (x - (int) x != 0)
                found = true;
        }
        if (!found)
            return {};
        auto it = resources[v].end();
        it--;
        int to = max_element(resources[v].begin(), it, [](double x, double y) { return x - (int) x < y - (int) y; }) -
                 resources[v].begin();
        values.push_back(0);
        int newB = values.size();
        resources[newB] = line(newB + 1);
        for (int i = 0; i < values.size(); ++i) {
            resources[]
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    cout << setprecision(2) << fixed;
    map<int, line > resources;

    for (int i = 0; i < n; ++i) {
        resources[m + i] = line(n + m + 1, 0);
        for (int j = 0; j < m; ++j) {
            cin >> resources[m + i][j];
        }
        resources[m + i][m + i] = 1;
    }

    for (auto &[basis, coeffs]: resources)
        cin >> coeffs.back();

    line values(n + m + 1, 0);
    for (int i = 0; i < m; ++i) {
        cin >> values[i];
        values[i] = -values[i];
    }

    printTable(resources, values);

    vector<int> x = solveInteger(resources, values);
    if (x.empty())
        return 0;

    for (int i = 0; i < x.size() - 1; ++i) {
        cout << "x[" << i + 1 << "] = " << x[i] << '\n';
    }
    cout << "Z(x) = " << values.back();
    return 0;
}