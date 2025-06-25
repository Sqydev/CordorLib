//**********************************************************************************************
// Copyright (c) 2024-2025 Wojciech Kaptur (@Sqydev)
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
} EffQueue;

typedef struct {
    int Max_Size;
    int Size;
    size_t Type;
    void** Data;
} Queue;

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

#endif
