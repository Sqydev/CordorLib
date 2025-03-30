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

void UNITEST_Enqueue_Speed() {

    int size;
    printf("Ile_Dużo:");
    scanf("%d", &size);

    int ilep;
    printf("Ile_Prubować:");
    scanf("%d", &ilep);

    CreateQueue(qi, 'i', size);
    CreateQueue(qf, 'f', size);
    CreateQueue(qc, 'c', size);
    CreateQueue(qd, 'd', size);
    CreateQueue(ql, 'l', size);

    //Even if there's a big ass number the same thing but with printf's will be 3 times slower. conclusion: Enqueue is fucking faster then printf
    for(int i = 0; i < 100000000; i++) {
        Enqueue(&qi, i);
        Enqueue(&qf, i);
        Enqueue(&qc, 'q');
        Enqueue(&qd, i);
        Enqueue(&ql, i);
    }

    PrintQueue(&qi, 3);
    PrintQueue(&qf, 3);
    PrintQueue(&qc, 3);
    PrintQueue(&qd, 3);
    PrintQueue(&ql, 3);
}

void UNITEST_InitSpeed_and_Memeff() {

    int max;
    printf("Max_Size: ");
    scanf("%d", &max);

    char type;
    printf("Type: ");
    scanf(" %c", &type);

    Queue q;

    q.Front = 0;
    q.Back = 0;
    q.Max_Size = max;
    q.Type = type;

    if (q.Type == 'i') {
        q.Data = malloc(sizeof(int) * q.Max_Size);
    }
    else if(q.Type == 'f') {
        q.Data = malloc(sizeof(float) * q.Max_Size);
    }
    else if(q.Type == 'c') {
        q.Data = malloc(sizeof(char) * q.Max_Size);
    }
    else if(q.Type == 'd') {
        q.Data = malloc(sizeof(double) * q.Max_Size);
    }
    else if(q.Type == 'l') {
        q.Data = malloc(sizeof(long) * q.Max_Size);
    }

    char qwe;
    scanf(" %c", &qwe);
}

void UNITEST_DequeueSpeed_and_Memeff() {

    int max;
    printf("Max_Size: ");
    scanf("%d", &max);

    char type;
    printf("Type: ");
    scanf(" %c", &type);

    Queue q;

    q.Front = 0;
    q.Back = 0;
    q.Max_Size = max;
    q.Type = type;

    if (q.Type == 'i') {
        q.Data = malloc(sizeof(int) * q.Max_Size);
    }
    else if(q.Type == 'f') {
        q.Data = malloc(sizeof(float) * q.Max_Size);
    }
    else if(q.Type == 'c') {
        q.Data = malloc(sizeof(char) * q.Max_Size);
    }
    else if(q.Type == 'd') {
        q.Data = malloc(sizeof(double) * q.Max_Size);
    }
    else if(q.Type == 'l') {
        q.Data = malloc(sizeof(long) * q.Max_Size);
    }

    char qwe;
    scanf(" %c", &qwe);

    memset(q.Data, 1, sizeof(int));

    scanf(" %c", &qwe);

    for(int i = 0; i < max; i++) {
        Dequeue(&q);
    }

    scanf(" %c", &qwe);
}

void UNITEST_DeletQueue_MemEff() {
    int max;
    printf("Max_Size: ");
    scanf("%d", &max);

    char type;
    printf("Type: ");
    scanf(" %c", &type);

    Queue q;

    q.Front = 0;
    q.Back = 0;
    q.Max_Size = max;
    q.Type = type;

    if (q.Type == 'i') {
        q.Data = malloc(sizeof(int) * q.Max_Size);
    }
    else if(q.Type == 'f') {
        q.Data = malloc(sizeof(float) * q.Max_Size);
    }
    else if(q.Type == 'c') {
        q.Data = malloc(sizeof(char) * q.Max_Size);
    }
    else if(q.Type == 'd') {
        q.Data = malloc(sizeof(double) * q.Max_Size);
    }
    else if(q.Type == 'l') {
        q.Data = malloc(sizeof(long) * q.Max_Size);
    }

    char qwe;
    scanf(" %c", &qwe);

    DeleteQueue(&q);

    scanf(" %c", &qwe);
}

int main() {
    CreateQueue(q, 'i', 4);

    Enqueue(&q, 1);
    Enqueue(&q, 2);
    Enqueue(&q, 3);
    Enqueue(&q, 4);
    Enqueue(&q, 5);
    Enqueue(&q, 6);

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
