#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


//zmień type na size_t

typedef struct {
    int Max_Size;
    int Size;
    size_t Type;
    int Front;
    int Back;
    void** Data;
} Queue;

#define CreateQueue(name, In_Type, In_Max_Size) \
    Queue name; \
    InitQueue(&name, In_Type, In_Max_Size)

void InitQueue(Queue* queue, char In_Type, int Input_Max_Size) {
    queue->Type = In_Type == 'i' ? sizeof(int) :
                  In_Type == 'f' ? sizeof(float) :
                  In_Type == 'c' ? sizeof(char) :
                  In_Type == 'd' ? sizeof(double) :
                  In_Type == 'l' ? sizeof(long) : 0;

    queue->Max_Size = Input_Max_Size;
    queue->Front = 0;
    queue->Back = 0;
    queue->Size = 0;

    queue->Data = malloc(queue->Type * queue->Size);
}

bool IsEmpty(Queue* queue) {
    if(queue->Size == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool IsFull(Queue* queue) {
    if(queue->Size == queue->Max_Size) {
        return true;
    }
    else {
        return false;
    }
}

#define Enqueue(queue, val) ( \
    (queue)->Type == sizeof(int) ? Without_Macro_Enqueue(queue, &(int){val}) : \
    (queue)->Type == sizeof(float) ? Without_Macro_Enqueue(queue, &(float){val}) : \
    (queue)->Type == sizeof(char) ? Without_Macro_Enqueue(queue, &(char){val}) : \
    (queue)->Type == sizeof(double) ? Without_Macro_Enqueue(queue, &(double){val}) : \
    (queue)->Type == sizeof(long) ? Without_Macro_Enqueue(queue, &(long){val}) : 0 \
    )

void Without_Macro_Enqueue(Queue* queue, void* value) {
    if(IsFull(queue) == false || queue->Max_Size < 1) {
        queue->Size++;

        if(queue->Type == sizeof(int)) {
            queue->Data = realloc(queue->Data, sizeof(int) * queue->Size);
            ((int*)queue->Data)[queue->Back] = *(int*)value;
        }
        else if(queue->Type == sizeof(float)) {
            queue->Data = realloc(queue->Data, sizeof(float) * queue->Size);
            ((float*)queue->Data)[queue->Back] = *(float*)value;
        }
        else if(queue->Type == sizeof(char)) {
            queue->Data = realloc(queue->Data, sizeof(char) * queue->Size);
            ((char*)queue->Data)[queue->Back] = *(char*)value;
        }
        else if(queue->Type == sizeof(double)) {
            queue->Data = realloc(queue->Data, sizeof(double) * queue->Size);
            ((double*)queue->Data)[queue->Back] = *(double*)value;
        }
        else if(queue->Type == sizeof(long)) {
            queue->Data = realloc(queue->Data, sizeof(long) * queue->Size);
            ((long*)queue->Data)[queue->Back] = *(long*)value;
        }

        queue->Back++;
    }
}

void Dequeue(Queue* queue) {
    if (IsEmpty(queue) == false) {
        queue->Back--;
        queue->Size--;

        memmove(queue->Data, (char *)queue->Data + queue->Type, queue->Type * (queue->Size));

        queue->Data = realloc(queue->Data, queue->Size * queue->Type);
    }
}


#define Peek(queue) ( \
    (queue)->Type == sizeof(int) ? *(int *)Without_Macro_Peek(queue) : \
    (queue)->Type == sizeof(float) ? *(float *)Without_Macro_Peek(queue) : \
    (queue)->Type == sizeof(char) ? *(char *)Without_Macro_Peek(queue) : \
    (queue)->Type == sizeof(double) ? *(double *)Without_Macro_Peek(queue) : \
    (queue)->Type == sizeof(long) ? *(long *)Without_Macro_Peek(queue) : 0 \
)

void* Without_Macro_Peek(Queue* queue) {
    if (IsEmpty(queue) == false) {
        if(queue->Type == sizeof(int)) {
            return ((int *)queue->Data + queue->Front);
        }
        else if(queue->Type == sizeof(float)) {
            return ((float *)queue->Data + queue->Front);
        }
        else if(queue->Type == sizeof(char)) {
            return ((char *)queue->Data + queue->Front);
        }
        else if(queue->Type == sizeof(double)) {
            return ((double *)queue->Data + queue->Front);
        }
        else if(queue->Type == sizeof(long)) {
            return ((long *)queue->Data + queue->Front);
        }
    }
    return NULL;
}

void CleanQueue(Queue* queue) {
    queue->Front = 0;
    queue->Back = 0;
    queue->Size = 0;
    free(queue->Data);
}

int QueueCount(Queue* queue) {
    return queue->Size;
}

void DeleteQueue(Queue* queue) {
    free(queue->Data);
}

void PrintQueue(Queue* queue, int Mode) {
    if(IsEmpty(queue) == false) {
        for(int i = queue->Front; i < queue->Back; i++) {
            if(queue->Type == sizeof(int)) {
                printf("%d", ((int *)queue->Data)[i]);
            }
            else if(queue->Type == sizeof(float)) {
                printf("%f", ((float *)queue->Data)[i]);
            }
            else if(queue->Type == sizeof(char)) {
                printf("%c", ((char *)queue->Data)[i]);
            }
            else if(queue->Type == sizeof(double)) {
                printf("%f", ((double *)queue->Data)[i]);
            }
            else if(queue->Type == sizeof(long)) {
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
    else {
        printf("It's empty\n");
    }
}

int main() {
    CreateQueue(q, 'i', 0);

    for(int i = 1; i <= 100; i++) {
        Enqueue(&q, i);
    }

    PrintQueue(&q, 3);

    printf("\n");

    printf("%d\n\n", (int)Peek(&q));

    Dequeue(&q);

    PrintQueue(&q, 3);

    printf("\n");

    printf("%d\n\n", (int)Peek(&q));

    CleanQueue(&q);

    PrintQueue(&q, 3);

    return 0;
}
