#ifndef __BPT_H__
#define __BPT_H__

// Uncomment the line below if you are compiling on Windows.
// #define WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "file.h"
#ifdef WINDOWS
#define bool char
#define false 0
#define true 1
#endif

#define SUCCESS 0
#define FAIL -1
// #define LEAF_ORDER 32
// #define INTERNAL_ORDER 249
#define LEAF_ORDER 3
#define INTERNAL_ORDER 3




int cut(int length);

int open_table(char *pathname);

int startNewTree(int64_t key, char* value);

int db_insert(int64_t key, char *value);
int insertIntoLeaf(pagenum_t leafPageNum, int64_t key, char* value);
int insertIntoNewRoot(pagenum_t leftLeafPageNum, int64_t newKey, pagenum_t rightLeafPageNum);
int insertIntoInternal(pagenum_t parentPageNum, int leftChildIndex, int64_t newKey, pagenum_t rightChildPageNum);
int insertIntoParent(pagenum_t leftChildPageNum, int64_t newKey, pagenum_t rightChildPageNum);
int getIndexOfLeft(pagenum_t parentPageNum, pagenum_t childPageNum);
int insertIntoLeafAfterSplitting(pagenum_t leafPageNum, int64_t key, char* value);
int insertIntoInternalAfterSplitting(pagenum_t parentPageNum, int leftChildIndex, int64_t newKey, pagenum_t rightChildPageNum);

int db_find(int64_t key, char *ret_val);
pagenum_t findLeaf(int64_t key);

int db_delete(int64_t key);
//delete entry from internal or leaf
int deleteEntry(pagenum_t pageNum, int64_t key);
int getNeighborIndex(pagenum_t pageNum);
void removeEntryFromPage(pagenum_t pageNum, int64_t key);
int adjustRoot(pagenum_t pageNum);
int coalescePages(pagenum_t neighborPageNum , int64_t kPrime, pagenum_t pageNum, int neighborIndex);
int redistributePages(pagenum_t neighborPageNum, int64_t kPrime, pagenum_t pageNum, int neighborIndex, int kPrimeIndex);

#endif /* __BPT_H__*/
