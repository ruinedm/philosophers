# 🧑‍🍳 Philosophers

This project simulates the classic **Dining Philosophers** problem using threads and mutexes for the mandatory part, and processes and semaphores for the bonus part. The simulation aims to solve synchronization issues related to philosophers sharing forks, ensuring no deadlock or resource contention.

## 🚀 Project Overview

The project is split into two parts:

- **Mandatory Part (philo)**: Implement the philosophers' problem using threads and mutexes to manage forks.
- **Bonus Part (philo_bonus)**: Extend the simulation by using processes and semaphores to manage forks, making the program more robust and handling multiple processes concurrently.

## 🧑‍🍳 Problem Description

- There are `n` philosophers sitting around a table.
- Each philosopher has a fork on their left and right side.
- Philosophers alternate between thinking and eating. To eat, they need both forks.
- If a philosopher is eating, they hold both forks.
- Philosophers must avoid deadlock while eating and must not starve.

### Arguments

Both programs take the following arguments:

- `number_of_philosophers` — the number of philosophers sitting at the table.
- `time_to_die` — the time (in milliseconds) before a philosopher dies of starvation.
- `time_to_eat` — the time (in milliseconds) a philosopher spends eating.
- `time_to_sleep` — the time (in milliseconds) a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` — optional, specifies how many times each philosopher must eat.

## ⚙️ How to Build and Run

### Mandatory Part (`philo`)

This part uses **threads** and **mutexes** to simulate the philosophers' problem.

1. **Build the project**:

```bash
make
```

2. **Run the program**:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Bonus Part (`philo_bonus`)

This part uses **processes** and **semaphores** for a more advanced solution, where each philosopher is a process, and the forks are represented by semaphores.

1. **Build the bonus project**:

```bash
make bonus
```

2. **Run the program**:

```bash
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

## 🧠 How It Works

- **Mutexes (Mandatory)**: Each fork is protected by a mutex to ensure that only one philosopher can use it at a time.
- **Semaphores (Bonus)**: The number of available forks is represented by a semaphore, and philosophers must wait for a semaphore to become available before eating.
- **Processes vs Threads**: In the bonus part, each philosopher is a process, while in the mandatory part, philosophers are threads.

## 📁 File Structure

```
philosophers/
├── philo/
│   ├── Makefile
│   ├── philo.c
│   ├── philo.h
│   └── ...
├── philo_bonus/
│   ├── Makefile
│   ├── philo_bonus.c
│   ├── philo_bonus.h
│   └── ...
└── README.md
```

## 🧩 Key Functions

- **`pthread_create()`**: Used to create threads for each philosopher.
- **`pthread_mutex_init()`**: Initializes mutexes for the forks.
- **`pthread_mutex_lock()`**: Locks a mutex before using a fork.
- **`pthread_mutex_unlock()`**: Unlocks a mutex after using a fork.
- **`sem_open()`**: Used to create a semaphore for managing fork availability (bonus part).
- **`sem_wait()` / `sem_post()`**: Used to acquire and release semaphores for forks (bonus part).

## 📜 License

This project is part of the **42 School Curriculum**. It is designed for educational purposes. All content is expected to be original and comply with 42’s academic integrity policy.

---

Feel free to reach out or open issues if you have any questions about the implementation or if you'd like to contribute.
