#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perms.h"


int arrayIndexOf(int a[], int n, int val) {
	for (int i = 0; i < n; i++)
		if (a[i] == val) return i;
	return -1;
}


void copyArray(int src[], int dst[], int len) {
	for (int i = 0; i < len; i++) dst[i] = src[i];
}


void printArray(int a[], int len) {
	for (int i = 0; i < len; i++) printf("%i ", a[i]);
	printf("\n");
}


void printArraySlice(int a[], int start, int end) {
	while (start <= end) printf("%i ", a[start++]);
	printf("\n");
}


int* readArray(int *length) {
    if (*length <= 0) *length = 1000;
    int* a = malloc(*length * sizeof(int));
    int count = 0;

    int val;
    while (scanf("%d", &val) > 0) {
        if (count >= *length) {
            *length *= 2;
            a = realloc(a, *length * sizeof(int));
        }
        a[count++] = val;
    }
    *length = count;
    return realloc(a, count * sizeof(int));
}


int checkArraySorted(int a[], int n) {
    for (int i = 0; i < n-1; i++)
        if (a[i] > a[i+1]) return i;
    return -1;
}


const char* perms[] = {
    "None",
    "Rand",
    "Zig", "ZigRev", "ZigRevFront", "ZigRevBack",
    "Sort", "SortRev",
    "Dither",
    NULL
};


perm_t str2perm(const char* str) {
    for (int i = 0; perms[i] != NULL; i++)
        if (strcasecmp(perms[i], str) == 0) return (perm_t)i;
    return None;
}


const char* perm2str(const perm_t perm) {
    return perms[perm];
}


void printPerms(const char *prefix) {
    printf("%s", prefix);
    for (perm_t i = Rand; i <= Dither; i++) printf("%s ", perm2str(i));
    printf("\n");
}


int cmpInt(const void *a, const void *b) {
	return *(const int*)a - *(const int *)b;
}


int cmpIntRev(const void *a, const void *b) {
	return *(const int*)b - *(const int *)a;
}


void generatePerm(int a[], int len, int modulo, perm_t kind) {
	// gelenerate
	for (int i = 0; i < len; i++) a[i] = i % modulo;
	// permute
	switch (kind) {
        case Rand:
            while (--len > 0) swap(a, len, random() % (len + 1));
            break;
        case Zig:
            break;
        case ZigRev:
			for (int i = 0; i < len / 2; i++) swap(a, i, len-1-i);
            break;
        case ZigRevFront:
            for (int i = 0; i < len / 4; i++) swap(a, i, len/2-i);
            break;
        case ZigRevBack:
            for (int i = 0; i < len / 4; i++) swap(a, len/2+i, len-i);
            break;
        case Sort:
            qsort(a, len, sizeof(int), cmpInt);
            break;
        case SortRev:
            qsort(a, len, sizeof(int), cmpIntRev);
            break;
        case Dither:
			for (int i = 0; i < len; i++) a[i] += i % 5;
            break;
        default:
            fprintf(stderr, "Wrong permutation pattern (%d).\n", kind);
            exit(42);
	}
}
