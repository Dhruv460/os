## Overview

[Watch the demo](./demo.mp4)

FreeRTOS offers feature stability with long term support (LTS) releases. FreeRTOS LTS libraries come with security updates and critical bug fixes to the FreeRTOS kernel and IoT libraries listed below for two years, and are maintained by AWS for the benefit of the FreeRTOS community. With FreeRTOS LTS, you get a complete set of libraries needed to build secure connected IoT and embedded products. Long term support helps reduce maintenance and testing costs associated with updating libraries on your devices already in production.

AWS also offers FreeRTOS Extended Maintenance Plan (EMP) that provides you with security patches and critical bug fixes on your chosen FreeRTOS LTS version for up to an additional 10 years. With FreeRTOS EMP, your FreeRTOS-based long-lived devices can rely on a version that has feature stability and receives security updates for years. You receive timely notification of upcoming patches on FreeRTOS libraries, so you can plan the deployment of security patches on your IoT devices. To learn more about FreeRTOS EMP, see the [FreeRTOS Features page](https://aws.amazon.com/freertos/features/).

## FreeRTOS/FreeRTOS Long Term Support

Libraries in this GitHub branch (also listed below) are part of the FreeRTOS 202406-LTS release. Learn more at https://freertos.org/lts-libraries.html.

| Library                    | Version | LTS Until  | LTS Repo URL                                                                   |
| -------------------------- | ------- | ---------- | ------------------------------------------------------------------------------ |
| FreeRTOS Kernel            | 11.1.0  | 06/30/2026 | https://github.com/FreeRTOS/FreeRTOS-Kernel/tree/V11.1.0                       |
| FreeRTOS-Plus-TCP          | 4.2.2   | 06/30/2026 | https://github.com/FreeRTOS/FreeRTOS-Plus-TCP/tree/V4.2.2                      |
| coreMQTT                   | 2.3.1   | 06/30/2026 | https://github.com/FreeRTOS/coreMQTT/tree/v2.3.1                               |
| coreHTTP                   | 3.1.1   | 06/30/2026 | https://github.com/FreeRTOS/coreHTTP/tree/v3.1.1                               |
| corePKCS11                 | 3.6.1   | 06/30/2026 | https://github.com/FreeRTOS/corePKCS11/tree/v3.6.1                             |
| coreJSON                   | 3.3.0   | 06/30/2026 | https://github.com/FreeRTOS/coreJSON/tree/v3.3.0                               |
| coreSNTP                   | 1.3.1   | 06/30/2026 | https://github.com/FreeRTOS/coreSNTP/tree/v1.3.1                               |
| Cellular Interface         | 1.4.0   | 06/30/2026 | https://github.com/FreeRTOS/FreeRTOS-Cellular-Interface/tree/v1.4.0            |
| backoffAlgorithm           | 1.4.1   | 06/30/2026 | https://github.com/FreeRTOS/backoffAlgorithm/tree/v1.4.1                       |
| SigV4                      | 1.3.0   | 06/30/2026 | https://github.com/aws/SigV4-for-AWS-IoT-embedded-sdk/tree/v1.3.0              |
| AWS IoT Device Shadow      | 1.4.1   | 06/30/2026 | https://github.com/aws/Device-Shadow-for-AWS-IoT-embedded-sdk/tree/v1.4.1      |
| AWS IoT Device Defender    | 1.4.0   | 06/30/2026 | https://github.com/aws/Device-Defender-for-AWS-IoT-embedded-sdk/tree/v1.4.0    |
| AWS IoT Jobs               | 1.5.1   | 06/30/2026 | https://github.com/aws/Jobs-for-AWS-IoT-embedded-sdk/tree/v1.5.1               |
| AWS IoT Fleet Provisioning | 1.2.1   | 06/30/2026 | https://github.com/aws/Fleet-Provisioning-for-AWS-IoT-embedded-sdk/tree/v1.2.1 |
| AWS IoT MQTT File Streams  | 1.1.0   | 06/30/2026 | https://github.com/aws/aws-iot-core-mqtt-file-streams-embedded-c/tree/v1.1.0   |

## Upgrading to FreeRTOS 202406-LTS from a previous version of FreeRTOS LTS

FreeRTOS 202406 LTS libraries are backward compatible with 202210.xx LTS, except
AWS IoT OTA and FreeRTOS-Plus-TCP libraries. AWS IoT OTA library is not included in the LTS 202406 release.
Instead, AWS IoT MQTT File Streams are included in this release, and we suggest user
reference to [Modular Over the Air Updates](https://freertos.org/freertos-core/over-the-air-updates/index.html),
which makes use of the AWS IoT MQTT File Streams library for OTA application design.
For FreeRTOS-Plus-TCP, refer to [these instructions](https://github.com/FreeRTOS/FreeRTOS-Plus-TCP/blob/main/GettingStarted.md)
on how to update your projects to use the new version.

## FreeRTOS LTS Versioning and Patches

FreeRTOS LTS releases use a date-based versioning scheme (YYYYMM) followed by a patch sequential number (.XX).
For example, FreeRTOS 202406.01 LTS means the first patch to the June-2024 FreeRTOS LTS release.
You can review the [CHANGELOG](./CHANGELOG.md) and subscribe to [GitHub notifications](https://docs.github.com/en/free-pro-team@latest/github/managing-subscriptions-and-notifications-on-github/about-notifications) to receive information on patches or other updates to this repository.

## Security

See [CONTRIBUTING](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This library is licensed under the MIT License. See the [LICENSE](LICENSE.md) file.

what we did :

we implemented edf (earliest deadline first sheduling algorithm) to customise sheduling for our RTOS

1. Task Scheduling (EDF + Priority)
   Concept:
   The scheduler combines Earliest Deadline First (EDF) and priority-based scheduling.

Implementation:

Each task has a deadline and a priority.

In edfPriorityScheduler():

It builds a readyQueue of tasks whose arrivalTime <= currentTime and are not yet completed.

Sorts this queue:

First by priority (lower is better),

Then by deadline (earlier deadline has higher urgency).

It selects the front of the queue to run.

This task executes for one time unit (remainingTime--), and if done, it's marked completed.

2. IPC Queue (Indirect)
   Concept:
   The vector taskList acts like an IPC queue. Multiple threads access it:

simulateTaskInput() adds tasks (simulated user input).

edfPriorityScheduler() reads and updates the task list.

Synchronization:
It uses std::mutex (mtx) to ensure thread-safe access. The lock_guard ensures:

No race conditions,

Safe concurrent task addition and scheduling.

3. IPC via Shared Memory (Simulated)
   Concept:
   shared_memory is a shared variable that simulates memory-mapped IPC.

Usage:

The running task sets shared_memory = task.id.

If no task is running, it sets shared_memory = -1.

This shared variable represents which task is being processed, visible globally (to other threads or systems, if expanded).

4. GUI with ncurses (Detailed)
   Concept:
   ncurses is a C/C++ terminal GUI library. It lets you build interactive CLI programs with windows, colors, input fields, etc.

Used Windows:

win – the main display window for showing tasks, time, and shared memory.

Temporary popup windows for task input.

Key GUI Elements:

Element Purpose
box(win, 0, 0) Draws a border around the window.
mvwprintw(win, y, x, ...) Prints text at a specific position inside the window.
werase(win) Clears the content of the window.
wrefresh(win) Updates the actual terminal with the changes.
mvvgetnstr() Reads user input from specific location.
curs_set(0/1) Hides/shows the cursor.
'i' key Opens an input window for dynamic task addition.
'q' key Exits the program.
Display Features:

Header: Current time, running task, shared memory.

Task Table: With ID, arrival time, execution time, remaining time, deadline, priority, and status (Pending, Running, Done).

Dynamic UI: Updated every second with task progress.

Popup for Input: Prompts user to add a task interactively.

Example Snippet:

cpp
Copy
Edit
mvwprintw(win, 1, 2, "EDF + Priority Scheduler | Time: %d", currentTime);
mvwprintw(win, 3, 2, "Shared Memory (Task ID): %d", shared_memory); 5. Summary of Features
Manual + Auto Task Input: Combine user control with real-time simulation.

Preemptive Simulation: Tasks run 1-second ticks, mimicking real CPUs.

Interactive Dashboard: Terminal-based real-time monitor.

Shared IPC Display: Simulated memory visualization.

Scalable: Easy to extend with I/O, semaphores, or real memory mapping.
