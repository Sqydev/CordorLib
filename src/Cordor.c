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
} EffQueue;

typedef struct {

} Queue;

//Effi
#define CreateEffIntQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 1, In_Max_Size)

#define CreateEffFloatQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 1, In_Max_Size)

#define CreateEffCharQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 2, In_Max_Size)

#define CreateEffDoubleQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 3, In_Max_Size)

#define CreateEffLongQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 4, In_Max_Size)


//Fast
#define CreateFastIntQueue(name, In_Max_Size) \
    typedef struct { \
        int Max_Size; \
        int Size; \
        int iData[In_Max_Size]; \
    } FastQueue; \
    FastQueue name; \
    InitFastQueue(&name, 0, In_Max_Size)

#define CreateFastFloatQueue(name, In_Max_Size) \
    typedef struct { \
        int Max_Size; \
        int Size; \
        float fData[In_Max_Size]; \
    } FastQueue; \
    FastQueue name; \
    InitFastQueue(&name, 1, In_Max_Size)

#define CreateFastCharQueue(name, In_Max_Size) \
    typedef struct { \
        int Max_Size; \
        int Size; \
        char cData[In_Max_Size]; \
    } FastQueue; \
    FastQueue name; \
    InitFastQueue(&name, 2, In_Max_Size)

#define CreateFastDoubleQueue(name, In_Max_Size) \
    typedef struct { \
        int Max_Size; \
        int Size; \
        double dData[In_Max_Size]; \
    } FastQueue; \
    FastQueue name; \
    InitFastQueue(&name, 3, In_Max_Size)

#define CreateFastLongQueue(name, In_Max_Size) \
    typedef struct { \
        int Max_Size; \
        int Size; \
        long lData[In_Max_Size]; \
    } FastQueue; \
    FastQueue name; \
    InitFastQueue(&name, 4, In_Max_Size)


void InitEffQueue(EffQueue* queue, int In_Type, int Input_Max_Size) {
    queue->Type = malloc(sizeof(size_t));
    *queue->Type = In_Type == 0 ? sizeof(int) :
                   In_Type == 1 ? sizeof(float) :
                   In_Type == 2 ? sizeof(char) :
                   In_Type == 3 ? sizeof(double) :
                   In_Type == 4 ? sizeof(long) : 0;

    queue->Max_Size = malloc(sizeof(int));
    *queue->Max_Size = Input_Max_Size;

    queue->Size = malloc(sizeof(int));
    *queue->Size = 0;

    queue->Data = malloc(*queue->Type * *queue->Size);
}

void InitQueue() {

}

void InitFastQueue(FastQueue* queue, int In_Type, int Input_Max_Size) {

}

bool IsEmpty(EffQueue* queue) {
    if(*queue->Size == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool IsFull(EffQueue* queue) {
    if(*queue->Size == *queue->Max_Size) {
        return true;
    }
    else {
        return false;
    }
}

#define Enqueue(queue, val) ( \
    *(queue)->Type == sizeof(int) ? Advanced_Enqueue(queue, &(int){val}) : \
    *(queue)->Type == sizeof(float) ? Advanced_Enqueue(queue, &(float){val}) : \
    *(queue)->Type == sizeof(char) ? Advanced_Enqueue(queue, &(char){val}) : \
    *(queue)->Type == sizeof(double) ? Advanced_Enqueue(queue, &(double){val}) : \
    *(queue)->Type == sizeof(long) ? Advanced_Enqueue(queue, &(long){val}) : 0 \
    )

void Advanced_Enqueue(EffQueue* queue, void* value) {
    if(IsFull(queue) == false || *queue->Max_Size < 1) {
        *queue->Size = *queue->Size + 1;

        queue->Data = realloc(queue->Data, *queue->Type * *queue->Size);

        if(*queue->Type == sizeof(int)) {
            ((int*)queue->Data)[*queue->Size - 1] = *(int*)value;
        }
        else if(*queue->Type == sizeof(float)) {
            ((float*)queue->Data)[*queue->Size - 1] = *(float*)value;
        }
        else if(*queue->Type == sizeof(char)) {
            ((char*)queue->Data)[*queue->Size - 1] = *(char*)value;
        }
        else if(*queue->Type == sizeof(double)) {
            ((double*)queue->Data)[*queue->Size - 1] = *(double*)value;
        }
        else if(*queue->Type == sizeof(long)) {
            ((long*)queue->Data)[*queue->Size - 1] = *(long*)value;
        }
    }
}

void Dequeue(EffQueue* queue) {
    if (IsEmpty(queue) == false) {
        *queue->Size = *queue->Size - 1;

        memmove(queue->Data, (char *)queue->Data + *queue->Type, *queue->Type * (*queue->Size));

        queue->Data = realloc(queue->Data, *queue->Size * *queue->Type);
    }
}


#define Peek(queue) ( \
    *(queue)->Type == sizeof(int) ? *(int *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(float) ? *(float *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(char) ? *(char *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(double) ? *(double *)Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(long) ? *(long *)Advanced_Peek(queue) : 0 \
    )

void* Advanced_Peek(EffQueue* queue) {
    if (IsEmpty(queue) == false) {
        if(*queue->Type == sizeof(int)) {
            return ((int *)queue->Data + 0);
        }
        else if(*queue->Type == sizeof(float)) {
            return ((float *)queue->Data + 0);
        }
        else if(*queue->Type == sizeof(char)) {
            return ((char *)queue->Data + 0);
        }
        else if(*queue->Type == sizeof(double)) {
            return ((double *)queue->Data + 0);
        }
        else if(*queue->Type == sizeof(long)) {
            return ((long *)queue->Data + 0);
        }
    }
    return NULL;
}

int CountQueue(EffQueue* queue) {
    return *queue->Size;
}

void CleanQueue(EffQueue* queue) {
    *queue->Size = 0;
    queue->Data = realloc(queue->Data, *queue->Size * *queue->Type);
}

void DeleteQueue(EffQueue* queue) {
    free(queue->Max_Size);
    free(queue->Size);
    free(queue->Type);
    free(queue->Data);
}

void PrintQueue(EffQueue* queue, int Mode) {
    if(IsEmpty(queue) == false) {
        for(int i = 0; i < *queue->Size; i++) {
            if(*queue->Type == sizeof(int)) {
                printf("%d", ((int *)queue->Data)[i]);
            }
            else if(*queue->Type == sizeof(float)) {
                printf("%f", ((float *)queue->Data)[i]);
            }
            else if(*queue->Type == sizeof(char)) {
                printf("%c", ((char *)queue->Data)[i]);
            }
            else if(*queue->Type == sizeof(double)) {
                printf("%f", ((double *)queue->Data)[i]);
            }
            else if(*queue->Type == sizeof(long)) {
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
    CreateEffIntQueue(q, 100);

    for(int i = 1; i <= 100; i++) {
        Enqueue(&q, i);
    }

    printf("After Enqueue: ");
    PrintQueue(&q, 3);

    printf("\n");

    printf("Peek: %d\n\n", (int)Peek(&q));

    printf("Size: %d\n\n", CountQueue(&q));

    Dequeue(&q);

    printf("After Dequeue: ");
    PrintQueue(&q, 3);

    printf("\n");

    printf("Peek: %d\n\n", (int)Peek(&q));

    printf("Size: %d\n\n", CountQueue(&q));

    CleanQueue(&q);

    printf("After Clean: ");
    PrintQueue(&q, 3);

    printf("\n");

    for(int i = 1; i <= 100; i++) {
        Enqueue(&q, i);
    }

    printf("After EnqueueClean: ");
    PrintQueue(&q, 3);

    printf("\n");

    printf("Peek: %d\n\n", (int)Peek(&q));

    printf("Size: %d\n\n", CountQueue(&q));

    printf("After DequeueClean: ");
    Dequeue(&q);

    PrintQueue(&q, 3);

    printf("\n");

    printf("Peek: %d\n\n", (int)Peek(&q));

    printf("Size: %d\n\n", CountQueue(&q));

    DeleteQueue(&q);

    //Should give error

    //PrintQueue(&q, 3);

    CreateEffIntQueue(y, 0);

    PrintQueue(&y, 3);

    return 0;
}
