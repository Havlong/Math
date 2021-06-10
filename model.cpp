#include <bits/stdc++.h>

/**
 * 06.03.2021
 * model
 *
 * @author Havlong
 * @version v1.0
 */

#define double long double
#define line vector<double>
#define matrix vector<vector<double>>
#define ALL(x) x.begin(), x.end()

using namespace std;

matrix createRiskMatrix(const matrix &a) {
    matrix b(a.size(), line(a.front().size()));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            double maxA = 0;
            for (const auto &k : a) {
                maxA = max(maxA, k[j]);
            }
            b[i][j] = maxA - a[i][j];
        }
    }
    return b;
}

int solveBayes(const matrix &a, const line &p) {
    return max_element(ALL(a), [&](const line &first, const line &second) {
        double vFirst = 0;
        double vSecond = 0;
        for (int i = 0; i < first.size(); ++i) {
            vFirst += first[i] * p[i];
            vSecond += second[i] * p[i];
        }
        return vFirst < vSecond;
    }) - a.begin();
}

int solveWald(const matrix &a) {
    return max_element(ALL(a), [](const line &a, const line &b) {
        return *min_element(ALL(a)) < *min_element(ALL(b));
    }) - a.begin();
}

int solveSavage(const matrix &a) {
    matrix b = createRiskMatrix(a);
    return min_element(ALL(b), [](const line &a, const line &b) {
        return *max_element(ALL(a)) < *max_element(ALL(b));
    }) - b.begin();
}

int solveHurwitz(const matrix &a, const double &k) {
    return max_element(ALL(a), [&](const line &first, const line &second) {
        double gFirst = k * (*min_element(ALL(first))) + (1 - k) * (*max_element(ALL(first)));
        double gSecond = k * (*min_element(ALL(second))) + (1 - k) * (*max_element(ALL(second)));
        return gFirst < gSecond;
    }) - a.begin();
}

int main() {
    ofstream fout("protocol.log", ios::app);
    fout << "--Dialog start" << endl;
    int n, m;
    puts("Enter production units count:");
    fout << "Enter production units count:" << endl;
    cin >> m;
    fout << m << endl;
    puts("Enter solutions count:");
    fout << "Enter solutions count:" << endl;
    cin >> n;
    fout << n << endl;
    puts("Enter efficiency matrix:");
    fout << "Enter efficiency matrix:" << endl;
    matrix a(n, line(m));
    line p(m);
    for (auto &row: a) {
        for (auto &x: row) {
            cin >> x;
            fout << x << ' ';
        }
        fout << '\n';
    }
    puts("Enter probabilities of production units:");
    fout << "Enter probabilities of production units:" << endl;
    for (auto &x: p) {
        cin >> x;
        fout << x << ' ';
    }
    fout << endl;
    double optimismCoefficient;
    puts("Enter optimism coefficient:");
    fout << "Enter optimism coefficient:" << endl;
    cin >> optimismCoefficient;
    fout << optimismCoefficient << endl;

    cout << "Best Bayes solution: " << solveBayes(a, p) + 1 << '\n';
    fout << "Best Bayes solution: " << solveBayes(a, p) + 1 << '\n';
    cout << "Best Wald solution: " << solveWald(a) + 1 << '\n';
    fout << "Best Wald solution: " << solveWald(a) + 1 << '\n';
    cout << "Best Savage solution: " << solveSavage(a) + 1 << '\n';
    fout << "Best Savage solution: " << solveSavage(a) + 1 << '\n';
    cout << "Best Hurwitz solution: " << solveHurwitz(a, optimismCoefficient) + 1 << endl;
    fout << "Best Hurwitz solution: " << solveHurwitz(a, optimismCoefficient) + 1 << endl;
    fout << "--Dialog end\n" << endl;
}