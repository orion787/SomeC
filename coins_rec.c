#include <stdio.h>
#include <limits.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int calc_changes(int n, int m, int *changes, int *V) {
    if (n == 0) return 0;
    if (n < 0) return INT_MAX;
    if (V[n] != INT_MAX) return V[n];

    for (int i = 0; i < m; ++i) {
        int CT = calc_changes(n - changes[i], m, changes, V);
        if (CT == INT_MAX) continue;
        V[n] = min(V[n], CT + 1);
    }

    return V[n];
}

int main() {
    int n = 10;
    int changes[] = {1, 2, 5};
    int m = sizeof(changes) / sizeof(changes[0]);

    int V[n + 1];
    V[0] = 0;

    for (int i = 1; i <= n; ++i) {
        V[i] = INT_MAX;
    }

    int result = calc_changes(n, m, changes, V);
    for(int z = 0; z < n; z++)
        printf("%d ", V[z]);
    puts("\n");
    if (result != INT_MAX) {
        printf("Min changes %d: %d\n", n, result);
    } else {
        printf("Impossible\n", n);
    }

    return 0;
}
