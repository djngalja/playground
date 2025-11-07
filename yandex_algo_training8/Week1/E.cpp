#include <iostream>
#include <vector>

/*
long calc_x(long n, long k) {
    std::vector<long> table(k + 1);
    table[0] = n;
    for (int i = 0; i != k; ++i) {
        table[i + 1] = table[i] + (table[i] % 10);
    }
    return table[k];
}
    */

long calc_res(const std::vector<int>& pat, int add, long k, long n) {
    long res{};
    int rem = (k - 1) % 4;
    for (int i = 0; i < rem; ++i) {
        res += pat[i];
    }
    res += n + add + 20 * ((k - 1) / 4);
    return res;
}

long calc_res(const std::vector<int>& pat, long k, long n) {
    long res{};
    int rem = k % 4;
    for (int i = 0; i < rem; ++i) {
        res += pat[i];
    }
    res += n + 20 * (k / 4);
    return res;
}

int main() {
    long n{};
    long k{};
    std::cin >> n >> k; 
    long res{};
    if (k == 0) {
        res = n;
    } else {
        int mod = n % 10;
        if (mod == 1 || mod == 6) {
            res = calc_res({2, 4, 8, 6}, mod, k, n);
        } else if (mod == 9) {
            res = calc_res({8, 6, 2, 4}, mod, k, n);
        } else if (mod == 3) {
            res = calc_res({6, 2, 4, 8}, mod, k, n);
        } else if (mod == 7) {
            res = calc_res({4, 8, 6, 2}, mod, k, n);
        } else if (mod == 2) {
            res = calc_res({2, 4, 8, 6}, k, n);
        } else if (mod == 4) {
            res = calc_res({4, 8, 6, 2}, k, n);
        } else if (mod == 8) {
            res = calc_res({8, 6, 2, 4}, k, n);
        } else if (mod == 5) {
            res = mod + n;
        } else { // mod == 0
        res = n;
        }
    }
    
    //std::cout << res << "   " << calc_x(n, k);
    std::cout << res;

	return 0;
}
