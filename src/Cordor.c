#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int Max_Size;
    char Type;
    int Front;
    int Back;
    void* Data;
} Queue;

#define CreateQueue(name, In_Type, In_Max_Size) \
    Queue name; \
    InitQueue(&name, In_Type, In_Max_Size)

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

#define Enqueue(queue, val) ( \
    (queue)->Type == 'i' ? Without_Macro_Enqueue(queue, &(int){val}) : \
    (queue)->Type == 'f' ? Without_Macro_Enqueue(queue, &(float){val}) : \
    (queue)->Type == 'c' ? Without_Macro_Enqueue(queue, &(char){val}) : \
    (queue)->Type == 'd' ? Without_Macro_Enqueue(queue, &(double){val}) : \
    (queue)->Type == 'l' ? Without_Macro_Enqueue(queue, &(long){val}) : 0 \
    )

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
    if (IsEmpty(queue) == false) {
        size_t elem_size =
            queue->Type == 'i' ? sizeof(int) :
            queue->Type == 'f' ? sizeof(float) :
            queue->Type == 'c' ? sizeof(char) :
            queue->Type == 'd' ? sizeof(double) :
            queue->Type == 'l' ? sizeof(long) : 0;

            memmove(queue->Data, (char*)queue->Data + elem_size, (queue->Back - 1) * elem_size);
            queue->Back--;
    }
}


#define Peek(queue) ( \
    (queue)->Type == 'i' ? *(int *)Without_Macro_Peek(queue) : \
    (queue)->Type == 'f' ? *(float *)Without_Macro_Peek(queue) : \
    (queue)->Type == 'c' ? *(char *)Without_Macro_Peek(queue) : \
    (queue)->Type == 'd' ? *(double *)Without_Macro_Peek(queue) : \
    (queue)->Type == 'l' ? *(long *)Without_Macro_Peek(queue) : 0 \
)

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

void CleanQueue(Queue* queue) {
    queue->Front = 0;
    queue->Back = 0;
    memset(queue->Data, 0, sizeof(queue->Data));
}

int WaitingQueueCount(Queue* queue) {
    return queue->Back;
}

void DeleteQueue(Queue* queue) {
    free(queue->Data);
}

void PrintQueue(Queue* queue, int Mode) {
    if(IsEmpty(queue) == false) {
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
    else {
        printf("It's empty\n");
    }
}

void UNITEST() {
    CreateQueue(qi, 'i', 4);
    CreateQueue(qf, 'f', 4);
    CreateQueue(qc, 'c', 4);
    CreateQueue(qd, 'd', 4);
    CreateQueue(ql, 'l', 4);


}


int main() {
    UNITEST();

    return 0;
}
