#include <stdio.h>
#define N 4

int bt[N] = {6, 8, 7, 3};

void run(int order[]) {
    int t = 0;
    float total_wt = 0;

    printf("Process  Burst  Waiting  Turnaround\n");

    for (int k = 0; k < N; k++) {
        int i = order[k];
        printf("P%d       %d      %d        %d\n",
               i + 1, bt[i], t, t + bt[i]);

        total_wt += t;
        t += bt[i];
    }

    printf("Average waiting time = %.2f\n\n", total_wt / N);
}

int main() {
    int order[N] = {0, 1, 2, 3};

    printf("--- FCFS ---\n");
    run(order);

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (bt[order[j]] < bt[order[i]]) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }

    printf("--- SJF ---\n");
    run(order);

    int tq = 2, t = 0, left = N, rem[N], wt[N];
    float total = 0;

    for (int i = 0; i < N; i++)
        rem[i] = bt[i];

    while (left > 0)
        for (int i = 0; i < N; i++) {
            if (rem[i] == 0)
                continue;

            int slice = rem[i] < tq ? rem[i] : tq;
            t += slice;
            rem[i] -= slice;

            if (rem[i] == 0) {
                wt[i] = t - bt[i];
                left--;
            }
        }

    printf("--- Round Robin (quantum = %d) ---\n", tq);
    printf("Process  Burst  Waiting  Turnaround\n");

    for (int i = 0; i < N; i++) {
        printf("P%d       %d      %d        %d\n",
               i + 1, bt[i], wt[i], wt[i] + bt[i]);
        total += wt[i];
    }

    printf("Average waiting time = %.2f\n", total / N);

    return 0;
}
