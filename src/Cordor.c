#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int Size;
    int Front;
    int Back;
    int* Data;
} Queue;

void InitQueue(Queue* queue, int Max_Size);
bool IsFull(Queue* queue);
bool IsEmpty(Queue* queue);
void Enqueue(Queue* queue, int value);
void Dequeue(Queue* queue);
int Peek(Queue* queue);
void PrintQueue(Queue* queue, int Mode);

int main() {
    Queue q;
    InitQueue(&q, 4);

    Enqueue(&q, 1);
    Enqueue(&q, 2);
    Enqueue(&q, 3);
    Enqueue(&q, 4);
    Enqueue(&q, 5);
    Enqueue(&q, 5);


    PrintQueue(&q, 3);

    printf("\n");

    Dequeue(&q);

    PrintQueue(&q, 3);

    printf("\n%d\n", Peek(&q));

    return 0;
}

void InitQueue(Queue* queue, int Max_Size) {
    queue->Front = 0;
    queue->Back = 0;
    queue->Size = Max_Size;
    queue->Data = malloc(sizeof(int) * queue->Size);
}

bool IsEmpty(Queue* queue) {
    if(queue->Back == queue->Front) {
        return true;
    }
    else {
        return false;
    }
}

bool IsFull(Queue* queue) {
    if(queue->Back == queue->Size) {
        return true;
    }
    else {
        return false;
    }
}

void Enqueue(Queue* queue, int value) {
    if(IsFull(queue) == false) {
        queue->Data[queue->Back] = value;
        queue->Back++;
    }
}

void Dequeue(Queue* queue) {
    if(IsEmpty(queue) == false) {
        queue->Front++;
    }
}

int Peek(Queue* queue) {
    return queue->Data[queue->Front];
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
