#include <bits/stdc++.h>

/**
 * 11.03.2021
 * simplex
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

line solveSimplex(map<int, line > &resources, line &values) {

    while (!all_of(ALL(values), [](const double &x) { return x >= 0; })) {
        int toBasis = min_element(ALL(values)) - values.begin();
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
        printTable(resources, values);
    }
    line x(values.size(), 0);
    for (int i = 0; i < values.size(); ++i) {
        if (resources.count(i))
            x[i] = resources[i].back();
    }
    return x;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cin >> n >> m;

    cout << setprecision(2) << fixed;
    map<int, line> resources;

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

    line x = solveSimplex(resources, values);
    if (x.empty())
        return 0;

    for (int i = 0; i < x.size(); ++i) {
        cout << "x[" << i + 1 << "] = " << x[i] << '\n';
    }
    cout << "Z(x) = " << values.back();
    return 0;
}