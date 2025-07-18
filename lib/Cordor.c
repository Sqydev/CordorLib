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
    size_t* Type;
    void** Data;
} EffQueue;

typedef struct {
    int Max_Size;
    int Size;
    size_t Type;
    void** Data;
} Queue;

//Effi
#define CreateEffIntQueue(name, In_Max_Size) \
    EffQueue name; \
    InitEffQueue(&name, 0, In_Max_Size)

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


//Normal
#define CreateIntQueue(name, In_Max_Size) \
    Queue name; \
    InitQueue(&name, 0, In_Max_Size)

#define CreateFloatQueue(name, In_Max_Size) \
    Queue name; \
    InitQueue(&name, 1, In_Max_Size)

#define CreateCharQueue(name, In_Max_Size) \
    Queue name; \
    InitQueue(&name, 2, In_Max_Size)

#define CreateDoubleQueue(name, In_Max_Size) \
    Queue name; \
    InitQueue(&name, 3, In_Max_Size)

#define CreateLongQueue(name, In_Max_Size) \
    Queue name; \
    InitQueue(&name, 4, In_Max_Size)



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

void InitQueue(Queue* queue, int In_Type, int Input_Max_Size) {
    queue->Type = In_Type == 0 ? sizeof(int) :
                  In_Type == 1 ? sizeof(float) :
                  In_Type == 2 ? sizeof(char) :
                  In_Type == 3 ? sizeof(double) :
                  In_Type == 4 ? sizeof(long) : 0;

    queue->Size = 0;

    queue->Max_Size = Input_Max_Size;

	if(queue->Max_Size > 0) {
    	queue->Data = malloc(queue->Type * queue->Max_Size);
	}
	else {
		queue->Data = malloc(queue->Type * (queue->Max_Size + 1));
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

#define EffEnqueue(queue, val) ( \
    *(queue)->Type == sizeof(int) ? Eff_Advanced_Enqueue(queue, &(int){val}) : \
    *(queue)->Type == sizeof(float) ? Eff_Advanced_Enqueue(queue, &(float){val}) : \
    *(queue)->Type == sizeof(char) ? Eff_Advanced_Enqueue(queue, &(char){val}) : \
    *(queue)->Type == sizeof(double) ? Eff_Advanced_Enqueue(queue, &(double){val}) : \
    *(queue)->Type == sizeof(long) ? Eff_Advanced_Enqueue(queue, &(long){val}) : 0 \
    )

#define Enqueue(queue, val) ( \
    (queue)->Type == sizeof(int) ? Advanced_Enqueue(queue, &(int){val}) : \
    (queue)->Type == sizeof(float) ? Advanced_Enqueue(queue, &(float){val}) : \
    (queue)->Type == sizeof(char) ? Advanced_Enqueue(queue, &(char){val}) : \
    (queue)->Type == sizeof(double) ? Advanced_Enqueue(queue, &(double){val}) : \
    (queue)->Type == sizeof(long) ? Advanced_Enqueue(queue, &(long){val}) : 0 \
    )

void Eff_Advanced_Enqueue(EffQueue* queue, void* value) {
    if(EffIsQueueFull(queue) == false || EffIsQueueInfinite(queue) == true) {
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


void Advanced_Enqueue(Queue* queue, void* value) {
	if(IsQueueFull(queue) == false || IsQueueInfinite(queue) == true) {
		if(IsQueueInfinite(queue) == true) {
        	queue->Data = realloc(queue->Data, queue->Type * (queue->Size + 1));
		}

		if(queue->Type == sizeof(int)) {
            ((int*)queue->Data)[queue->Size] = *(int*)value;
		}
		else if(queue->Type == sizeof(float)) {
			((float*)queue->Data)[queue->Size] = *(float*)value;
        }
		else if(queue->Type == sizeof(char)) {
            ((char*)queue->Data)[queue->Size] = *(char*)value;
        }
		else if(queue->Type == sizeof(double)) {
            ((double*)queue->Data)[queue->Size] = *(double*)value;
        }
		else if(queue->Type == sizeof(long)) {
            ((long*)queue->Data)[queue->Size] = *(long*)value;
        }
		
		queue->Size = queue->Size + 1;
	}
}

void EffDequeue(EffQueue* queue) {
    if (EffIsQueueEmpty(queue) == false) {
        *queue->Size = *queue->Size - 1;

        memmove(queue->Data, (char *)queue->Data + *queue->Type, *queue->Type * (*queue->Size));

        queue->Data = realloc(queue->Data, *queue->Size * *queue->Type);
    }
}

void Dequeue(Queue* queue) {
    if (IsQueueEmpty(queue) == false) {
		queue->Size = queue->Size - 1;

        memmove(queue->Data, (char *)queue->Data + queue->Type, queue->Type * queue->Size);
	}
}

#define EffPeek(queue) ( \
	Eff_Advanced_Peek(queue) == NULL ? 0 : \
	*(queue)->Type == sizeof(int) ? *(int *)Eff_Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(float) ? *(float *)Eff_Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(char) ? *(char *)Eff_Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(double) ? *(double *)Eff_Advanced_Peek(queue) : \
    *(queue)->Type == sizeof(long) ? *(long *)Eff_Advanced_Peek(queue) : 0 \
    )

#define Peek(queue) ( \
	Advanced_Peek(queue) == NULL ? 0 : \
    (queue)->Type == sizeof(int) ? *(int *)Advanced_Peek(queue) : \
    (queue)->Type == sizeof(float) ? *(float *)Advanced_Peek(queue) : \
    (queue)->Type == sizeof(char) ? *(char *)Advanced_Peek(queue) : \
    (queue)->Type == sizeof(double) ? *(double *)Advanced_Peek(queue) : \
    (queue)->Type == sizeof(long) ? *(long *)Advanced_Peek(queue) : 0 \
    )

void* Eff_Advanced_Peek(EffQueue* queue) {
    if (!EffIsQueueEmpty(queue)) {
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

void* Advanced_Peek(Queue* queue) {
	if (!IsQueueEmpty(queue)) {
        if(queue->Type == sizeof(int)) {
            return (((int *)queue->Data + 0));
        }
        else if(queue->Type == sizeof(float)) {
            return ((float *)queue->Data + 0);
        }
        else if(queue->Type == sizeof(char)) {
            return ((char *)queue->Data + 0);
        }
        else if(queue->Type == sizeof(double)) {
            return ((double *)queue->Data + 0);
        }
        else if(queue->Type == sizeof(long)) {
            return ((long *)queue->Data + 0);
        }
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
    return sizeof(&queue->Data) * *queue->Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(&queue->Type);
}

size_t QueueSize(Queue* queue) {
	if(queue->Max_Size > 0) {
	    return sizeof(&queue->Data) * queue->Max_Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(&queue->Type);
	}
	else {
	    return sizeof(&queue->Data) * queue->Size + sizeof(&queue->Size) + sizeof(&queue->Max_Size) + sizeof(&queue->Type);
	}
}

void EffCleanQueue(EffQueue* queue) {
    *queue->Size = 0;
    queue->Data = realloc(queue->Data, *queue->Size * *queue->Type);
}

void CleanQueue(Queue* queue) {
    queue->Size = 0;
    queue->Data = realloc(queue->Data, queue->Max_Size * queue->Type);
}

void EffDeleteQueue(EffQueue* queue) {
    free(queue->Max_Size);
    free(queue->Size);
    free(queue->Type);
    free(queue->Data);
}

void DeleteQueue(Queue* queue) {
	free(queue->Data);
}

void EffPrintQueue(EffQueue* queue, int Mode) {
    if(EffIsQueueEmpty(queue) == false) {
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

void PrintQueue(Queue* queue, int Mode) {
    if(IsQueueEmpty(queue) == false) {
        for(int i = 0; i < queue->Size; i++) {
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
