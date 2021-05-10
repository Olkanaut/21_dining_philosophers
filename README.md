# Dining_philosophers
I’ve never thought philosophy would be so deadly.

A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping. Each of them need two forks to eat. The philosophers must never be starving. Philosophers don’t know when another philosopher is about to die. The simulation stops when a philosopher dies.

Solution 1: with threads and mutex
Solution 2: with threads and semaphore
Solution 3: with processes and semaphore

Run an executable with options: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
