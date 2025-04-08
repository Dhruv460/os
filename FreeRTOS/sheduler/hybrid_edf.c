#include <stdio.h>

#define MAX_TASKS 10

typedef struct
{
    int id;
    int arrival_time;
    int execution_time;
    int deadline;
    int priority; // Added priority field
} Task;

void sort_by_deadline(Task tasks[], int n)
{
    Task temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (tasks[i].deadline > tasks[j].deadline)
            {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void sort_by_priority(Task tasks[], int n)
{
    Task temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Higher priority value means higher priority
            if (tasks[i].priority < tasks[j].priority)
            {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void edf_schedule(Task tasks[], int n)
{
    int time = 0;
    Task sorted_tasks[MAX_TASKS];
    // Make a copy of the tasks array
    for (int i = 0; i < n; i++)
    {
        sorted_tasks[i] = tasks[i];
    }

    sort_by_deadline(sorted_tasks, n);
    printf("\nEDF Scheduling:\n");
    printf("Execution Order:\n");
    for (int i = 0; i < n; i++)
    {
        if (time < sorted_tasks[i].arrival_time)
        {
            time = sorted_tasks[i].arrival_time;
        }
        printf("Time %d: Task %d (Arrival: %d, Execution: %d, Deadline: %d, Priority: %d)\n",
               time, sorted_tasks[i].id, sorted_tasks[i].arrival_time,
               sorted_tasks[i].execution_time, sorted_tasks[i].deadline,
               sorted_tasks[i].priority);
        time += sorted_tasks[i].execution_time;
        if (time > sorted_tasks[i].deadline)
        {
            printf("Task %d missed its deadline.\n", sorted_tasks[i].id);
        }
    }
}

void priority_schedule(Task tasks[], int n)
{
    int time = 0;
    Task sorted_tasks[MAX_TASKS];
    // Make a copy of the tasks array
    for (int i = 0; i < n; i++)
    {
        sorted_tasks[i] = tasks[i];
    }

    sort_by_priority(sorted_tasks, n);
    printf("\nPriority Scheduling:\n");
    printf("Execution Order:\n");
    for (int i = 0; i < n; i++)
    {
        if (time < sorted_tasks[i].arrival_time)
        {
            time = sorted_tasks[i].arrival_time;
        }
        printf("Time %d: Task %d (Arrival: %d, Execution: %d, Deadline: %d, Priority: %d)\n",
               time, sorted_tasks[i].id, sorted_tasks[i].arrival_time,
               sorted_tasks[i].execution_time, sorted_tasks[i].deadline,
               sorted_tasks[i].priority);
        time += sorted_tasks[i].execution_time;
        if (time > sorted_tasks[i].deadline)
        {
            printf("Task %d missed its deadline.\n", sorted_tasks[i].id);
        }
    }
}

void hybrid_schedule(Task tasks[], int n)
{
    int time = 0;
    int remaining_tasks = n;
    Task ready_queue[MAX_TASKS];
    int num_ready_tasks = 0;

    // Create copies of tasks to track completion
    Task task_copies[MAX_TASKS];
    for (int i = 0; i < n; i++)
    {
        task_copies[i] = tasks[i];
    }

    printf("\nHybrid Scheduling (Priority + EDF):\n");
    printf("Execution Order:\n");

    // Continue until all tasks are completed
    while (remaining_tasks > 0)
    {
        // Find arrived tasks and put them in the ready queue
        num_ready_tasks = 0;
        for (int i = 0; i < n; i++)
        {
            if (task_copies[i].execution_time > 0 && task_copies[i].arrival_time <= time)
            {
                ready_queue[num_ready_tasks++] = task_copies[i];
            }
        }

        if (num_ready_tasks == 0)
        {
            // No tasks ready yet, advance time to the next arrival
            int next_arrival = __INT_MAX__;
            for (int i = 0; i < n; i++)
            {
                if (task_copies[i].execution_time > 0 && task_copies[i].arrival_time < next_arrival)
                {
                    next_arrival = task_copies[i].arrival_time;
                }
            }
            time = next_arrival;
            continue;
        }

        // Apply hybrid scheduling: First by priority, then by deadline for ties
        Task *selected_task = &ready_queue[0];
        for (int i = 1; i < num_ready_tasks; i++)
        {
            // First compare by priority
            if (ready_queue[i].priority > selected_task->priority)
            {
                selected_task = &ready_queue[i];
            }
            // If priority is the same, select by earliest deadline
            else if (ready_queue[i].priority == selected_task->priority &&
                     ready_queue[i].deadline < selected_task->deadline)
            {
                selected_task = &ready_queue[i];
            }
        }

        // Update the state for the selected task
        printf("Time %d: Task %d (Arrival: %d, Execution: %d, Deadline: %d, Priority: %d)\n",
               time, selected_task->id, selected_task->arrival_time,
               selected_task->execution_time, selected_task->deadline,
               selected_task->priority);

        // Update the time and mark task as executed
        time += selected_task->execution_time;

        // Check if deadline is missed
        if (time > selected_task->deadline)
        {
            printf("Task %d missed its deadline.\n", selected_task->id);
        }

        // Mark this task as completed in task_copies
        for (int i = 0; i < n; i++)
        {
            if (task_copies[i].id == selected_task->id)
            {
                task_copies[i].execution_time = 0;
                remaining_tasks--;
                break;
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Task tasks[MAX_TASKS];
    int n;
    int scheduling_type;

    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        tasks[i].id = i + 1;
        printf("Enter arrival time for Task %d: ", tasks[i].id);
        scanf("%d", &tasks[i].arrival_time);
        printf("Enter execution time for Task %d: ", tasks[i].id);
        scanf("%d", &tasks[i].execution_time);
        printf("Enter deadline for Task %d: ", tasks[i].id);
        scanf("%d", &tasks[i].deadline);
        printf("Enter priority for Task %d (higher number = higher priority): ", tasks[i].id);
        scanf("%d", &tasks[i].priority);
    }

    printf("\nScheduling Options:\n");
    printf("1. EDF Scheduling\n");
    printf("2. Priority Scheduling\n");
    printf("3. Hybrid Scheduling (Priority + EDF)\n");
    printf("Enter scheduling type (1-3): ");
    scanf("%d", &scheduling_type);

    switch (scheduling_type)
    {
    case 1:
        edf_schedule(tasks, n);
        break;
    case 2:
        priority_schedule(tasks, n);
        break;
    case 3:
        hybrid_schedule(tasks, n);
        break;
    default:
        printf("Invalid scheduling type. Using Hybrid Scheduling.\n");
        hybrid_schedule(tasks, n);
    }

    return 0;
}