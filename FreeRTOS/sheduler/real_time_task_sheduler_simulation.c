
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include <sstream>

using namespace std;
using namespace std::chrono;

struct Task
{
    int id;
    int arrivalTime;
    int executionTime;
    int deadline;
    int priority;
    int remainingTime;
    bool completed;

    Task(int i, int at, int et, int d, int p)
        : id(i), arrivalTime(at), executionTime(et), deadline(d), priority(p),
          remainingTime(et), completed(false) {}
};

mutex mtx;
vector<Task> taskList;
int currentTime = 0;
int nextTaskID = 1;
bool stopExecution = false;
int shared_memory = -1; // Simulated shared memory (task ID being executed)

void simulateTaskInput()
{
    while (!stopExecution)
    {
        this_thread::sleep_for(seconds(5));
        lock_guard<mutex> lock(mtx);
        int et = 2 + rand() % 4;
        int deadline = currentTime + et + (rand() % 5 + 5);
        int prio = rand() % 5 + 1;
        taskList.emplace_back(nextTaskID++, currentTime, et, deadline, prio);
    }
}

void displayTasksNcurses(WINDOW *win, const vector<Task> &tasks, Task *runningTask)
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "EDF + Priority Scheduler | Time: %d", currentTime);
    mvwprintw(win, 2, 2, "Running Task: %s", runningTask ? ("ID " + to_string(runningTask->id)).c_str() : "None");
    mvwprintw(win, 3, 2, "Shared Memory (Task ID): %d", shared_memory);

    int row = 5;
    mvwprintw(win, row++, 2, "ID  | Arr | Exec | Left | DL | Prio | Status");
    mvwprintw(win, row++, 2, "----------------------------------------------");

    for (const auto &task : tasks)
    {
        string status = task.completed ? "Done" : "Pending";
        if (&task == runningTask)
            status = "Running";
        mvwprintw(win, row++, 2, "%-3d | %-3d | %-4d | %-4d | %-2d | %-4d | %s",
                  task.id, task.arrivalTime, task.executionTime, task.remainingTime,
                  task.deadline, task.priority, status.c_str());
    }

    mvwprintw(win, row + 1, 2, "Press 'i' to input task | Press 'q' to quit");
    wrefresh(win);
}

void edfPriorityScheduler(WINDOW *win)
{
    while (!stopExecution)
    {
        this_thread::sleep_for(seconds(1));
        currentTime++;

        lock_guard<mutex> lock(mtx);
        vector<Task *> readyQueue;
        for (auto &task : taskList)
        {
            if (!task.completed && task.arrivalTime <= currentTime)
            {
                readyQueue.push_back(&task);
            }
        }

        sort(readyQueue.begin(), readyQueue.end(),
             [](Task *a, Task *b)
             {
                 if (a->priority == b->priority)
                     return a->deadline < b->deadline;
                 return a->priority < b->priority;
             });

        Task *currentTask = nullptr;
        if (!readyQueue.empty())
        {
            currentTask = readyQueue.front();
            currentTask->remainingTime--;
            shared_memory = currentTask->id; // IPC simulation

            if (currentTask->remainingTime <= 0)
            {
                currentTask->completed = true;
            }
        }
        else
        {
            shared_memory = -1; // No task running
        }

        displayTasksNcurses(win, taskList, currentTask);
    }
}

void getUserInputTask(WINDOW *win)
{
    echo();
    curs_set(1);
    WINDOW *inputWin = newwin(6, 50, 35, 2);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 1, 2, "Enter ExecutionTime Deadline Priority:");
    wrefresh(inputWin);

    char input[100];
    mvwgetnstr(inputWin, 3, 2, input, 90);
    istringstream iss(input);
    int et, dl, pr;
    if (iss >> et >> dl >> pr)
    {
        lock_guard<mutex> lock(mtx);
        taskList.emplace_back(nextTaskID++, currentTime, et, dl, pr);
    }

    delwin(inputWin);
    curs_set(0);
    noecho();
}

void getInitialTasksFromUser()
{
    echo();
    curs_set(1);

    WINDOW *inputWin = newwin(10, 50, 5, 5);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 1, 2, "How many tasks to add?");
    wrefresh(inputWin);

    char numInput[10];
    mvwgetnstr(inputWin, 2, 2, numInput, 8);
    int n = atoi(numInput);

    for (int i = 0; i < n; ++i)
    {
        werase(inputWin);
        box(inputWin, 0, 0);
        mvwprintw(inputWin, 1, 2, "Task %d - Enter ExecTime Deadline Priority:", i + 1);
        wrefresh(inputWin);

        char input[100];
        mvwgetnstr(inputWin, 3, 2, input, 90);
        istringstream iss(input);
        int et, dl, pr;
        if (iss >> et >> dl >> pr)
        {
            lock_guard<mutex> lock(mtx);
            taskList.emplace_back(nextTaskID++, currentTime, et, dl, pr);
        }
    }

    delwin(inputWin);
    curs_set(0);
    noecho();
}

int main()
{
    initscr();
    noecho();
    curs_set(0);
    timeout(0);

    int height = 40, width = 70;
    WINDOW *win = newwin(height, width, 1, 2);
    box(win, 0, 0);
    refresh();

    getInitialTasksFromUser(); // 👈 Step 1: get N tasks manually

    thread inputThread(simulateTaskInput);             // 👈 Step 2: automatic generation
    thread schedulerThread(edfPriorityScheduler, win); // 👈 Step 3: scheduler starts

    while (!stopExecution)
    {
        int ch = getch();
        if (ch == 'q' || ch == 'Q')
        {
            stopExecution = true;
        }
        else if (ch == 'i' || ch == 'I')
        {
            getUserInputTask(win); // 👈 Add task anytime
        }
        this_thread::sleep_for(milliseconds(100));
    }

    inputThread.join();
    schedulerThread.join();

    delwin(win);
    endwin();
    return 0;
}
