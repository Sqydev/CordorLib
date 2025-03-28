#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int Max_Size;
    char Type;
    int Front;
    int Back;
    void* Data;
} Queue;

void InitQueue(Queue* queue, char In_Type, int Input_Max_Size) {
    queue->Front = 0;
    queue->Back = 0;
    queue->Max_Size = Input_Max_Size;
    queue->Type = In_Type;

    if (queue->Type == 'i') {
        queue->Data = malloc(sizeof(int) * queue->Max_Size);
    }
    else if(queue->Type == 'f') {
        queue->Data = malloc(sizeof(float) * queue->Max_Size);
    }
    else if(queue->Type == 'c') {
        queue->Data = malloc(sizeof(char) * queue->Max_Size);
    }
    else if(queue->Type == 'd') {
        queue->Data = malloc(sizeof(double) * queue->Max_Size);
    }
    else if(queue->Type == 'l') {
        queue->Data = malloc(sizeof(long) * queue->Max_Size);
    }
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
    if(queue->Back == queue->Max_Size) {
        return true;
    }
    else {
        return false;
    }
}

#define Enqueue(queue, val) \
    ((queue)->Type == 'i' ? Without_Macro_Enqueue(queue, &(int){val}) : \
    (queue)->Type == 'f' ? Without_Macro_Enqueue(queue, &(float){val}) : \
    (queue)->Type == 'c' ? Without_Macro_Enqueue(queue, &(char){val}) : \
    (queue)->Type == 'd' ? Without_Macro_Enqueue(queue, &(double){val}) : \
    (queue)->Type == 'l' ? Without_Macro_Enqueue(queue, &(long){val}) : \
    (void)0)

void Without_Macro_Enqueue(Queue* queue, void* value) {
    if(IsFull(queue) == false) {
        if(queue->Type == 'i') {
            ((int*)queue->Data)[queue->Back] = *(int*)value;
        }
        else if(queue->Type == 'f') {
            ((float*)queue->Data)[queue->Back] = *(float*)value;
        }
        else if(queue->Type == 'c') {
            ((char*)queue->Data)[queue->Back] = *(char*)value;
        }
        else if(queue->Type == 'd') {
            ((double*)queue->Data)[queue->Back] = *(double*)value;
        }
        else if(queue->Type == 'l') {
            ((long*)queue->Data)[queue->Back] = *(long*)value;
        }
        queue->Back++;
    }
}

void Dequeue(Queue* queue) {
    if(IsEmpty(queue) == false) {
        queue->Front++;
    }
}


//Zrób w definie: jak "typ": typ* var = (typ *)Without_Macro_Peek(queue); a potem return var;
#define Peek(queue) \
    (((queue)->Type == 'i' ? Without_Macro_Peek(queue, &(int)) : \
    ((queue)->Type == 'f' ? Without_Macro_Peek(queue, &(float)) : \
    ((queue)->Type == 'c' ? Without_Macro_Peek(queue, &(char)) : \
    ((queue)->Type == 'd' ? Without_Macro_Peek(queue, &(double)) : \
    ((queue)->Type == 'l' ? Without_Macro_Peek(queue, &(long)) : \
    (void)0)

void* Without_Macro_Peek(Queue* queue) {
    if (IsEmpty(queue) == false) {
        if(queue->Type == 'i') {
            return ((int *)queue->Data + queue->Front);
        }
        else if(queue->Type == 'f') {
            return ((float *)queue->Data + queue->Front);
        }
        else if(queue->Type == 'c') {
            return ((char *)queue->Data + queue->Front);
        }
        else if(queue->Type == 'd') {
            return ((double *)queue->Data + queue->Front);
        }
        else if(queue->Type == 'l') {
            return ((long *)queue->Data + queue->Front);
        }
    }
    return NULL;
}

void PrintQueue(Queue* queue, int Mode) {
    for(int i = queue->Front; i < queue->Back; i++) {
        if(queue->Type == 'i') {
            printf("%d", ((int *)queue->Data)[i]);
        }
        else if(queue->Type == 'f') {
            printf("%f", ((float *)queue->Data)[i]);
        }
        else if(queue->Type == 'c') {
            printf("%c", ((char *)queue->Data)[i]);
        }
        else if(queue->Type == 'd') {
            printf("%f", ((double *)queue->Data)[i]);
        }
        else if(queue->Type == 'l') {
            printf("%ld", ((long *)queue->Data)[i]);
        }

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


int main() {
    Queue q;
    InitQueue(&q, 'i', 4);

    Enqueue(&q, 1);
    Enqueue(&q, 2);
    Enqueue(&q, 3);
    Enqueue(&q, 4);
    Enqueue(&q, 5);
    Enqueue(&q, 6);

    PrintQueue(&q, 3);

    printf("\n");

    printf("\n%d\n", Peek(&q));

    Dequeue(&q);

    PrintQueue(&q, 3);

    printf("\n%d\n", Peek(&q));

    return 0;
}
