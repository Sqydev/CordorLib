//**********************************************************************************************
// Copyright (c) 2024-2025 Wojciech Kaptur / _Sqyd_ / Sqydev / https://github.com/Sqydev
//
//This software is provided "as-is", without any express or implied warranty. In no event 
//will the authors be held liable for any damages arising from the use of this software.
//
//Permission is granted to anyone to use this software for any purpose, including commercial 
//applications, and to alter it and redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not claim that you 
//  wrote the original software. If you use this software in a product, an acknowledgment 
//  in the product documentation would be appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be misrepresented
//  as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//**********************************************************************************************

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* Max_Size;
    int* Size;
    void** Data;
} EffQueue;

typedef struct {
    int Max_Size;
    int Size;
    void** Data;
} Queue;

//Eff
#define CreateEffQueue(name, Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, Max_Size)

//Normal
#define CreateQueue(name, Max_Size) \
	Queue name; \
	InitQueue(&name, Max_Size)


void InitEffQueue(EffQueue* queue, int Max_Size) {
    queue->Max_Size = malloc(sizeof(int));
    *queue->Max_Size = Max_Size;

    queue->Size = malloc(sizeof(int));
    *queue->Size = 0;

    queue->Data = malloc(sizeof(void**) * *queue->Size);
}

void InitQueue(Queue* queue, int Max_Size) {
    queue->Size = 0;

    queue->Max_Size = Max_Size;

	if(queue->Max_Size > 0) {
    	queue->Data = malloc(sizeof(void**) * queue->Max_Size);
	}
	else {
		queue->Data = malloc(sizeof(void**) * (queue->Max_Size + 1));
	}
}

bool EffIsQueueEmpty(EffQueue* queue) {
    if(*queue->Size == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool IsQueueEmpty(Queue* queue) {
    if(queue->Size == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool EffIsQueueFull(EffQueue* queue) {
    if(*queue->Size == *queue->Max_Size) {
        return true;
    }
    else {
        return false;
    }
}

bool IsQueueFull(Queue* queue) {
    if(queue->Size == queue->Max_Size) {
        return true;
    }
    else {
        return false;
    }
}

bool EffIsQueueInfinite(EffQueue* queue) {
	if(*queue->Max_Size < 1) {
		return true;
	}
	else {
		return false;	
	}
}

bool IsQueueInfinite(Queue* queue) {
	if(queue->Max_Size < 1) {
		return true;
	}
	else {
		return false;	
	}
}

void EffEnqueue(EffQueue* queue, void* value) {
    if(EffIsQueueFull(queue) == false || EffIsQueueInfinite(queue) == true) {
        *queue->Size = *queue->Size + 1;

        queue->Data = realloc(queue->Data, sizeof(void**) * *queue->Size);

        ((void**)queue->Data)[*queue->Size - 1] = value;
    }
}


void Enqueue(Queue* queue, void* value) {
	if(IsQueueFull(queue) == false || IsQueueInfinite(queue) == true) {
		if(IsQueueInfinite(queue) == true) {
        	queue->Data = realloc(queue->Data, (sizeof(void**) * queue->Size + 1));
		}

        ((void**)queue->Data)[queue->Size] = value;
		
		queue->Size = queue->Size + 1;
	}
}

void EffDequeue(EffQueue* queue) {
    if (EffIsQueueEmpty(queue) == false) {
        *queue->Size = *queue->Size - 1;

        memmove(queue->Data, (char *)queue->Data + sizeof(void**), sizeof(void**) * (*queue->Size));

        queue->Data = realloc(queue->Data, *queue->Size * sizeof(void**));
    }
}

void Dequeue(Queue* queue) {
    if (IsQueueEmpty(queue) == false) {
		queue->Size = queue->Size - 1;

        memmove(queue->Data, (char *)queue->Data + sizeof(void**), sizeof(void**) * queue->Size);
	}
}

#define EffPeek(queue, position, type) \
	*(type *)AdvancedEffPeek(queue, position)

void* AdvancedEffPeek(EffQueue* queue, int Position) {
    if (!EffIsQueueEmpty(queue)) {
        return ((void**)queue->Data[Position]);
    }
    return NULL;
}

#define Peek(queue, position, type) \
	*(type *)AdvancedPeek(queue, position)

void* AdvancedPeek(Queue* queue, int position) {
	if(!IsQueueEmpty(queue)) {
    	return ((void**)queue->Data[position]);
    }
	return NULL;
}

int EffCountQueue(EffQueue* queue) {
    return *queue->Size;
}

int CountQueue(Queue* queue) {
    return queue->Size;
}

size_t EffQueueSize(EffQueue* queue) {
    return sizeof(&queue->Data) * *queue->Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(void**);
}

size_t QueueSize(Queue* queue) {
	if(queue->Max_Size > 0) {
	    return sizeof(&queue->Data) * queue->Max_Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(void**);
	}
	else {
	    return sizeof(&queue->Data) * queue->Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(void**);
	}
}

void EffCleanQueue(EffQueue* queue) {
    *queue->Size = 0;
    queue->Data = realloc(queue->Data, *queue->Size * sizeof(void**));
}

void CleanQueue(Queue* queue) {
    queue->Size = 0;
    queue->Data = realloc(queue->Data, queue->Max_Size * sizeof(void**));
}

void EffDeleteQueue(EffQueue* queue) {
    free(queue->Max_Size);
    free(queue->Size);
    free(queue->Data);
}

void DeleteQueue(Queue* queue) {
	free(queue->Data);
}

void EffQueueTest() {
    CreateEffQueue(q, 100);

    for(int i = 0; i < 100; i++) {
        EffEnqueue(&q, &i);
    }

    printf("After Enqueue: ");
	for(int i = 0; i < **&q.Size; i++) {	
		printf("| %d |", EffPeek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", EffPeek(&q, 0, int));

    printf("Count: %d\n\n", EffCountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", EffQueueSize(&q));

    EffDequeue(&q);

    printf("After Dequeue: ");
	for(int i = 0; i < **&q.Size; i++) {	
		printf("| %d |", EffPeek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", EffPeek(&q, 0, int));

    printf("Count: %d\n\n", EffCountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", EffQueueSize(&q));

    EffCleanQueue(&q);

    printf("After Clean: ");
	for(int i = 0; i < **&q.Size; i++) {	
		printf("| %d |", EffPeek(&q, i, int));
	}

	printf("\n");

	printf("\nSize(bytes): %lu\n", EffQueueSize(&q));

    printf("\n");

    for(int i = 0; i < 50; i++) {
        EffEnqueue(&q, &i);
    }

    printf("After EnqueueClean: ");
	for(int i = 0; i < **&q.Size; i++) {	
		printf("| %d |", EffPeek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", EffPeek(&q, 0, int));

    printf("Count: %d\n\n", EffCountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", EffQueueSize(&q));
    
	EffDequeue(&q);

    printf("After DequeueClean: ");
	for(int i = 0; i < **&q.Size; i++) {	
		printf("| %d |", EffPeek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", EffPeek(&q, 0, int));

    printf("Count: %d\n\n", EffCountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", EffQueueSize(&q));

    EffDeleteQueue(&q);

}

void QueueTest() {
	typedef struct TESTER {
		int x;
		int y;
	} TESTER; 

    CreateQueue(q, 100);

    for(int i = 0; i < 100; i++) {
        Enqueue(&q, &i);
	}

    printf("After Enqueue: ");
    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}

    printf("\n\n");
    
	printf("Peek: %d\n\n", Peek(&q, 0, int));

    printf("Count: %d\n\n", CountQueue(&q));
    
	printf("Size(bytes): %lu\n\n", QueueSize(&q));

    Dequeue(&q);

    printf("After Dequeue: ");
    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}

    printf("\n\n");

    printf("Peek: %d\n\n", Peek(&q, 0, int));

    printf("Count: %d\n\n", CountQueue(&q));

	printf("Size(bytes): %lu\n\n", QueueSize(&q));
    
	CleanQueue(&q);

    printf("After Clean: ");
    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}
	
	printf("\n");

	printf("\nSize(bytes): %lu\n", QueueSize(&q));
    
	printf("\n");

    for(int i = 1; i < 50; i++) {
        Enqueue(&q, &i);
    }

    printf("After EnqueueClean: ");
    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", Peek(&q, 0, int));

    printf("Count: %d\n\n", CountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", QueueSize(&q));

    printf("After DequeueClean: ");
    Dequeue(&q);

    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}

    printf("\n");

    printf("Peek: %d\n\n", Peek(&q, 0, int));

    printf("Count: %d\n\n", CountQueue(&q));
	
	printf("Size(bytes): %lu\n\n", QueueSize(&q));

	//Test with struct
	TESTER tester = {5, 0};
	
	CleanQueue(&q);

	Enqueue(&q, &tester);

    for(int i = 0; i < *&q.Size; i++) {
		printf("| %d |", Peek(&q, i, int));
	}

    DeleteQueue(&q);
}

//2 times slower than Normal queue
void EFF_SPEEDY_TEST() {
	CreateEffQueue(test, 1000000000);
	
	for(int i = 1; i <= 1000000000; i++) {
		EffEnqueue(&test, &i);
		//printf("w");
	};
	
	 //EffPrintQueue(&test, 3);
	printf("\n%lu bytes", EffQueueSize(&test));
}

//As fast as printf
void SPEEDY_TEST() {
	CreateQueue(test, 1000000000);
	
	for(int i = 1; i <= 1000000000; i++) {
		Enqueue(&test, &i);
		//printf("w");
	};
	
	 //PrintQueue(&test, 3);
	printf("\n%lu bytes", QueueSize(&test));
}

int main() {
	QueueTest();

	return 0;
}
