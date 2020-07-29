#define headerPageNum 0
#define SUCCESS 0
#define FAIL -1
#define LEAF_ORDER 31
#define INTERNAL_ORDER 248

#include "bpt.h"
#include "file.h"
#include <string.h>
// GLOBALS.

int open_table(char *pathname) {
   
}
int startNewTree(int64_t key, char* value) {
    page_t* page = (page_t*)malloc(sizeof(struct page_t));
    page_t* headerPage = (page_t*)malloc(sizeof(struct page_t));

    ((leafPage_t*)page) -> isLeaf = 1;
    ((leafPage_t*)page) -> record[0].key = key;
    strcpy(((leafPage_t*)page) -> record[0].value, value);
    ((leafPage_t*)page) -> numOfKeys = 1;
    ((leafPage_t*)page) -> parentPageNum = 0;
    //update headerpage
    file_read_page(headerPageNum, headerPage);
    (((headerPage_t*)headerPage) -> numOfPages)++;
    ((headerPage_t*)headerPage) -> rootPageNum = 1;

    file_write_page(headerPageNum, headerPage);
    file_write_page(((headerPage_t*)headerPage) -> rootPageNum, page);

    free(page);
    free(headerPage);

    return SUCCESS;
}

int insertIntoLeaf(pagenum_t leafPageNum, int64_t key, char* value) {

}

// Insert input ‘key/value’ (record) to data file at the right place.
// If success, return 0. Otherwise, return non-zero value.
int db_insert(int64_t key, char * value) {
    page_t* page = (page_t*)malloc(sizeof(struct page_t));
    pagenum_t leafPageNum;
    char* tmp = (char*)malloc(sizeof(char) * 120);

    //check if key is already in the tree
    if (db_find(key, tmp) == 0) {
        printf("key is already in the tree\n");
        printf("db_insert fail");
        free(tmp);
        free(page);
        return FAIL;
    }
    free(tmp);
    
    file_read_page(headerPageNum, page);

    //there's no rootpage
    if (((headerPage_t*)page) -> rootPageNum == 0) {
        free(page);
        return startNewTree(key, value);
    }

    leafPageNum = findLeaf(key);

    file_read_page(leafPageNum, page);

    if (((leafPage_t*)page) -> numOfKeys < LEAF_ORDER - 1) {

    }



    free(page);
}

// Find the record containing input ‘key’.
// • If found matching ‘key’, store matched ‘value’ string in ret_val and return 0. Otherwise, return
// non-zero value.
int db_find(int64_t key, char * ret_val) {
    pagenum_t pageNum;
    int i = 0;
    pageNum = findLeaf(key);
    page_t* page = (page_t*)malloc(sizeof(struct page_t));
    file_read_page(pageNum, page);

    while (i < ((leafPage_t*)page) -> numOfKeys) {
        if (((leafPage_t*)page) -> record[i].key == key) {
            break;
        }
        i++;
    }

    if (i == ((leafPage_t*)page) -> numOfKeys) {
        free(page);
        return FAIL; // fail
    } else {
        strcpy(ret_val, ((leafPage_t*)page) -> record[i].value);
        free(page);
        return SUCCESS; // success
    }
}
int db_delete(int64_t key) {

}


pagenum_t findLeaf(int64_t key) {
    page_t* page = (page_t*)malloc(sizeof(struct page_t));
    pagenum_t leafPageNum;
    file_read_page(headerPageNum, page);
    pagenum_t rootPageNum = ((headerPage_t*)page) -> rootPageNum;
    file_read_page(rootPageNum, page);
    int i = 0;

    leafPageNum = rootPageNum;
    while (((internalPage_t*)page) -> isLeaf) {
        i = 0;
        while (i < ((internalPage_t*)page) -> numOfKeys) {
            if (key < ((internalPage_t*)page) -> record[i].key) {
                break;
            } else {
                i++;
            }
        }
        if (i == 0) {
            leafPageNum = ((internalPage_t*)page) -> leftMostPageNum;
        } else {
            leafPageNum = ((internalPage_t*)page) -> record[i - 1].pageNum;
        }
        file_read_page(leafPageNum, page);
    }
    free(page);
    return leafPageNum;
}