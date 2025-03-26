#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int Front;
    int Back;
    int* Data;
} Queue;

void InitQueue(Queue* queue, int Max_Size);
bool IsFull(Queue* queue);
bool IsEmpty(Queue* queue);
void Enqueue(Queue* queue, int value);
void Dequeue(Queue* queue);
void PrintQueue(Queue* queue, int Mode);

int main() {
    Queue q;
    //Może mieć o 3 za dużo kieszeni
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

    return 0;
}

void InitQueue(Queue* queue, int Max_Size) {
    queue->Front = 0;
    queue->Back = 0;
    queue->Data = (int *)malloc(Max_Size * sizeof(int));
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
    if(queue->Back == sizeof(queue->Data)) {
        return true;
    }
    else {
        return false;
    }
}

void Enqueue(Queue* queue, int value) {
    //if(IsFull(queue) == false) {
        queue->Data[queue->Back] = value;
        queue->Back++;
        //}
    //else {
        //printf("Queue is full");
        //}
}

void Dequeue(Queue* queue) {
    //if(IsEmpty(queue) == false) {
        queue->Data[queue->Front] = 0;
        queue->Front++;
        //}
    //else {
        //printf("Queue is empty");
        //}
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
