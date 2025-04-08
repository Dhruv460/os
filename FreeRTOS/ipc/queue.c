#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_LENGTH 10
#define ITEM_SIZE 32 // bytes per message

typedef struct
{
    char data[ITEM_SIZE];
    int priority;
} QueueItem;

typedef struct
{
    QueueItem items[MAX_QUEUE_LENGTH];
    int count;
} PriorityQueue;

void initializeQueue(PriorityQueue *q)
{
    q->count = 0;
}

int isQueueFull(PriorityQueue *q)
{
    return q->count == MAX_QUEUE_LENGTH;
}

int isQueueEmpty(PriorityQueue *q)
{
    return q->count == 0;
}

// Insert item into queue by priority
int enqueue(PriorityQueue *q, const char *data, int priority)
{
    if (isQueueFull(q))
    {
        printf("Queue is full!\n");
        return 0;
    }

    int i = q->count - 1;
    while (i >= 0 && q->items[i].priority > priority)
    {
        q->items[i + 1] = q->items[i];
        i--;
    }

    strncpy(q->items[i + 1].data, data, ITEM_SIZE);
    q->items[i + 1].priority = priority;
    q->count++;
    return 1;
}

// Remove highest-priority item
int dequeue(PriorityQueue *q, char *buffer)
{
    if (isQueueEmpty(q))
    {
        printf("Queue is empty!\n");
        return 0;
    }

    strncpy(buffer, q->items[0].data, ITEM_SIZE);

    for (int i = 1; i < q->count; i++)
    {
        q->items[i - 1] = q->items[i];
    }

    q->count--;
    return 1;
}

void displayQueue(PriorityQueue *q)
{
    if (isQueueEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Current Queue (from highest to lowest priority):\n");
    for (int i = 0; i < q->count; i++)
    {
        printf("Data: %s | Priority: %d\n", q->items[i].data, q->items[i].priority);
    }
}

int main()
{
    PriorityQueue queue;
    initializeQueue(&queue);

    int choice;
    char input[ITEM_SIZE];
    int priority;

    while (1)
    {
        printf("\n--- Priority Queue Menu ---\n");
        printf("1. Enqueue Item\n");
        printf("2. Dequeue Item\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            fgets(input, ITEM_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // remove newline
            printf("Enter priority (lower = higher priority): ");
            scanf("%d", &priority);
            getchar();
            enqueue(&queue, input, priority);
            break;

        case 2:
            if (dequeue(&queue, input))
            {
                printf("Dequeued item: %s\n", input);
            }
            break;

        case 3:
            displayQueue(&queue);
            break;

        case 4:
            exit(0);

        default:
            printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}