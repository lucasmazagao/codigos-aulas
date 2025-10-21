#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void)
{
    Queue *q1 = create_queue();
    Queue *q2 = create_queue();

    if (!q1 || !q2) {
        free_queue(&q1);
        free_queue(&q2);
        return 1;
    }

    int comando;

    while (scanf("%d", &comando) == 1) {
        if (comando == 0) {
            break;
        }

        if (comando == 1) {
            int x;
            if (scanf("%d", &x) == 1) {
                enqueue(q1, x);
            }

        } else if (comando == 2) {
            int x;
            if (scanf("%d", &x) == 1) {
                enqueue(q2, x);
            }

        } else if (comando == 3) {
            int v;

            if (dequeue(q2, &v) == 1) {
                printf("%d\n", v);
            } else if (dequeue(q1, &v) == 1) {
                printf("%d\n", v);
            }

            if (dequeue(q2, &v) == 1) {
                printf("%d\n", v);
            } else if (dequeue(q1, &v) == 1) {
                printf("%d\n", v);
            }

            if (dequeue(q1, &v) == 1) {
                printf("%d\n", v);
            } else if (dequeue(q2, &v) == 1) {
                printf("%d\n", v);
            }
        }
    }

    free_queue(&q1);
    free_queue(&q2);
    return 0;
}
