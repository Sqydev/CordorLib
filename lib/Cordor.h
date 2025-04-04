#ifndef Cordor_H
#define Cordor_H

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* Max_Size;
    int* Size;
    size_t* Type;
    void** Data;
} Queue;

#define CreateQueue(name, In_Type, In_Max_Size) \
    Queue name; \
    InitQueue(&name, In_Type, In_Max_Size)

void InitQueue(Queue* queue, char In_Type, int Input_Max_Size);
bool IsEmpty(Queue* queue);
bool IsFull(Queue* queue);

#define Enqueue(queue, val) ( \
    *(queue)->Type == sizeof(int) ? Advanced_Enqueue(queue, &(int){val}) : \
    *(queue)->Type == sizeof(float) ? Advanced_Enqueue(queue, &(float){val}) : \
    *(queue)->Type == sizeof(char) ? Advanced_Enqueue(queue, &(char){val}) : \
    *(queue)->Type == sizeof(double) ? Advanced_Enqueue(queue, &(double){val}) : \
    *(queue)->Type == sizeof(long) ? Advanced_Enqueue(queue, &(long){val}) : 0 \
    )

void Advanced_Enqueue(Queue* queue, void* value);
void Dequeue(Queue* queue);

#define Peek(queue) ( \
    *(queue)->Type == sizeof(int) ? *(int *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(float) ? *(float *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(char) ? *(char *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(double) ? *(double *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(long) ? *(long *)Advanced_Peek(queue) : 0 \
    )

void* Advanced_Peek(Queue* queue);
int CountQueue(Queue* queue);
void CleanQueue(Queue* queue);
void DeleteQueue(Queue* queue);
void PrintQueue(Queue* queue, int Mode);

#endif
