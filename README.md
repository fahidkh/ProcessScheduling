# ProcessScheduling

Process Scheduling
Write a program that implements a process scheduler based on priority. Your program should
have the following:
- Create a linked list with 10 objects. Each object will represent a process. At the
beginning, all objects are basically empty (Null).
- Process creation: when creating a process, the program should ask for the process
name and duration, then your program should assign an ID to the process that is
different than all current processes available. (Hint: to make it easier to work with
next steps, let the duration of the process be around 30 seconds).
- Sort the created processes into a queue (linked list) based on the process name (i.e.,
sort alphabetically).
- The program should extract the process at the head of the queue and assign to the
CPU (virtual one, not physically assign it) for the duration specified in the process.
When the process is finished, your scheduler should extract the next process from the
linked list, and so on.
- When a process is finished executing, the process should be deleted, and the process
ID can be used again for a later process.
- If the queue is empty (i.e., no process is available), the scheduler should check
periodically (every 5 second) if there are any new processes.
- In order to avoid process starvation, a process that remains at the tail of the queue
while creating 3 new processes should be moved to the head of the queue.
- if a new process with higher priority is
created while a process is currently running, context switch needs to be done
