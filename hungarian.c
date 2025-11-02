// hungarian.c
// Hungarian algorithm with double precision and perfect matching
// Author: Mamady Cheick Souare
// Date: November 2025
// Compile: gcc hungarian.c -o hungarian
// Run: ./hungarian

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define INF 1e18
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

double hungarian(int n, int m, double **cost, int *match_out) {
    int N = MAX(n, m); // square size
    double **a = (double **)malloc((N+1) * sizeof(double *));
    for (int i = 0; i <= N; i++) {
        a[i] = (double *)malloc((N+1) * sizeof(double));
        for (int j = 0; j <= N; j++) {
            if (i > 0 && j > 0 && i <= n && j <= m)
                a[i][j] = cost[i-1][j-1];
            else
                a[i][j] = 1e9; // pad with large cost
        }
    }

    double *u = (double*)calloc(N+1, sizeof(double));
    double *v = (double*)calloc(N+1, sizeof(double));
    int *p = (int*)calloc(N+1, sizeof(int));
    int *way = (int*)calloc(N+1, sizeof(int));

    for (int i = 1; i <= N; i++) {
        p[0] = i;
        double *minv = (double*)malloc((N+1)*sizeof(double));
        char *used = (char*)calloc(N+1, sizeof(char));
        for (int j = 0; j <= N; j++) minv[j] = INF;

        int j0 = 0;
        do {
            used[j0] = 1;
            int i0 = p[j0];
            double delta = INF;
            int j1 = 0;
            for (int j = 1; j <= N; j++) if (!used[j]) {
                double cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j = 0; j <= N; j++) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);

        // augment path
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);

        free(minv);
        free(used);
    }

    double result = 0;
    for (int j = 1; j <= N; j++) {
        if (p[j] > 0 && p[j] <= n && j <= m)
            result += cost[p[j]-1][j-1];
    }

    for (int j = 0; j < m; j++) match_out[j] = -1;
    for (int j = 1; j <= m; j++) {
        if (p[j] > 0 && p[j] <= n)
            match_out[j-1] = p[j]-1;
    }

    // cleanup
    for (int i = 0; i <= N; i++) free(a[i]);
    free(a); free(u); free(v); free(p); free(way);
    return result;
}

// Helper: allocate and fill matrix
double **alloc_matrix(int n, int m) {
    double **a = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        a[i] = (double *)malloc(m * sizeof(double));
    }
    return a;
}
void free_matrix(double **a, int n) {
    for (int i = 0; i < n; i++) free(a[i]);
    free(a);
}

int main() {
    int n = 3, m = 4;
    double **cost = alloc_matrix(n, m);

    double data[3][4] = {
        {9.0, 2.5, 7.1, 8.3},
        {6.2, 4.8, 3.0, 7.9},
        {5.0, 8.1, 1.5, 8.7}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cost[i][j] = data[i][j];

    int *match = (int *)malloc(m * sizeof(int));
    double best = hungarian(n, m, cost, match);

    printf("Minimum total cost = %.3f\n", best);
    for (int j = 0; j < m; j++) {
        if (match[j] != -1)
            printf("Job %d -> Worker %d (Cost = %.2f)\n",
                   j, match[j], cost[match[j]][j]);
        else
            printf("Job %d -> unassigned\n", j);
    }

    free(match);
    free_matrix(cost, n);
    return 0;
}
