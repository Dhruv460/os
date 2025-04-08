## Overview

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

FreeRTOS Task Monitoring GUI (Windows Simulator)

This project integrates a real-time Task Monitoring GUI using LVGL (Light and Versatile Graphics Library) into the FreeRTOS Windows Simulator. It visualizes FreeRTOS task data such as CPU usage, stack remaining, and task states on a simulated GUI using SDL2.


---

Features

Real-time visualization of FreeRTOS task metrics

Displays:

Task name

CPU usage %

Remaining stack space


Refreshes every 1 second

Built on LVGL with SDL2 for Windows GUI simulation



---

Directory Structure

FreeRTOS/
├── Demo/
│   └── WIN32-MSVC/
│       ├── main.c
│       ├── task_monitor.c
│       ├── task_monitor.h
│       ├── task_monitor_gui.c
│       ├── lvgl_init_task.c
│       └── ...
├── lvgl/ (submodule)
├── lv_drivers/ (cloned)
└── FreeRTOS-Kernel/


---

Setup Instructions

1.⁠ ⁠Clone Repositories

git clone https://github.com/FreeRTOS/FreeRTOS.git
cd FreeRTOS
git submodule add https://github.com/lvgl/lvgl.git
git clone https://github.com/lvgl/lv_drivers.git


---

2.⁠ ⁠Enable Task Monitoring

Edit FreeRTOSConfig.h in FreeRTOS/Demo/WIN32-MSVC/:

#define configUSE_TRACE_FACILITY              1
#define configGENERATE_RUN_TIME_STATS         1
#define configUSE_STATS_FORMATTING_FUNCTIONS  1
#define configUSE_IDLE_HOOK                   1


---

3.⁠ ⁠Add Required Files

Place the following files in WIN32-MSVC/:

task_monitor.c / task_monitor.h: Collects task stats

lvgl_init_task.c: Initializes LVGL and SDL display

task_monitor_gui.c: Draws the GUI

Update main.c: Starts monitoring and GUI tasks



---

4.⁠ ⁠SDL2 Setup (Required for LVGL GUI on Windows)

Download SDL2 development libraries from SDL.org

Add SDL2 include path and .lib files to your Visual Studio project

Copy SDL2 dll to your build directory



---

5.⁠ ⁠Build and Run

Open the FreeRTOS.sln (or your MSVC project) and:

Include lvgl, lv_drivers, and the new source files in the project

Build the solution

Run the executable


A window should appear showing task information updating every second.
