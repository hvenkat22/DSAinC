#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100
struct Task {
    char name[20];
    int priority;
};
struct Queue {
    struct Task items[MAX_SIZE];
    int front, rear, size;
};
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->size = 0;
    queue->rear = MAX_SIZE - 1;
    return queue;
}
bool isFull(struct Queue* queue) {
    return (queue->size == MAX_SIZE);
}
bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}
void enqueue(struct Queue* queue, struct Task task) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->items[queue->rear] = task;
    queue->size++;
}
void executeTask(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. No task to execute.\n");
        return;
    }
    int highestPriority = -1;
    int highestPriorityIndex = -1;
    for (int i = 0; i < queue->size; i++) {
        if (queue->items[i].priority > highestPriority) {
            highestPriority = queue->items[i].priority;
            highestPriorityIndex = i;
        }
    }
    printf("Executing task: %s\n", queue->items[highestPriorityIndex].name);
    for (int i = highestPriorityIndex; i < queue->size - 1; i++) {
        queue->items[i] = queue->items[i + 1];
    }
    queue->rear = (queue->rear - 1 + MAX_SIZE) % MAX_SIZE;
    queue->size--;
}
int main() {
  struct Queue* taskQueue = createQueue();
  int numTasks;
  printf("Enter the number of tasks: ");
  scanf("%d", &numTasks);
  for (int i = 0; i < numTasks; i++) {
    struct Task task;
    printf("Enter name for Task %d: ", i + 1);
    scanf("%s", task.name);
    printf("Enter priority for Task %d: ", i + 1);
    scanf("%d", &task.priority);
    enqueue(taskQueue, task);
  }
  printf("\nTask Execution Order:\n");
  while (!isEmpty(taskQueue)) {
    executeTask(taskQueue);
  }
    return 0;
}
