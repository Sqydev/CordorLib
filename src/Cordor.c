#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int Max_Size;
    int Front;
    int Back;
    int Data[];
} Queue;

void InitQueue(Queue* queue, int Max_Size);
bool IsFull(Queue* queue);
bool IsEmpty(Queue* queue);
void Enqueue(Queue* queue, int value);
void Dequeue(Queue* queue);
void PrintQueue(Queue* queue, int Mode);

int main() {
    Queue q;
    InitQueue(&q);

    Enqueue(&q, 10);
    Enqueue(&q, 12);
    Enqueue(&q, 16);
    Enqueue(&q, 11);

    PrintQueue(&q, 3);

    printf("\n");

    Dequeue(&q);

    PrintQueue(&q, 3);

    return 0;
}

void InitQueue(Queue* queue, int Max_Size) {
    queue->Front = 0;
    queue->Back = 0;
    queue->Max_Size = Max_Size;
}

bool IsEmpty(Queue* queue) {
    if(queue->Back - 1 == queue->Front) {
        return true;
    }
    else {
        return false;
    }
}

bool IsFull(Queue* queue) {
    if() {
        return true;
    }
    else {
        return false;
    }
}

void Enqueue(Queue* queue, int value) {
    queue->Data[queue->Back] = value;
    queue->Back++;
}

void Dequeue(Queue* queue) {
    if(IsEmpty(queue) == false) {
        queue->Data[queue->Front] = 0;
        queue->Front++;
    }
    else {
        printf("Queue is empty");
    }
}

void PrintQueue(Queue* queue, int Mode) {
    for(int i = queue->Front; i < queue->Back; i++) {
        printf("%d", queue->Data[i]);

        if(Mode == 1 || Mode == 3) {
            printf(" ");
        }
        else if(Mode == 2) {
            printf("\n");
        }
    }
    if(Mode == 3) {
        printf("\n");
    }
}
