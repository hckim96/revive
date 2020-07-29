#include "bpt.h"
#include "file.h"
#include "tests.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int fd;


// MAIN
int main( int argc, char ** argv ) {

    // init();
    if ((fd = open("db",O_RDWR |O_CREAT |O_EXCL,0644)) > 0) { //not exist
        headerPage_t* header = (headerPage_t*)malloc(sizeof(struct headerPage_t));
        header -> rootPageNum = 0;
        header -> numOfPages = 1;
        header -> freePageNum = 0;
        lseek(fd, 0 , SEEK_SET);
        write(fd, header, PAGESIZE);
        free(header);
    } else { //exist 
        fd = open("db", O_RDWR | O_APPEND);

    }
    tests();
    close(fd);

    // char * input_file;
    // FILE * fp;
    // node * root;
    // int input, range2;
    // char instruction;
    // char license_part;

    // root = NULL;
    // verbose_output = false;

    // if (argc > 1) {
    //     order = atoi(argv[1]);
    //     if (order < MIN_ORDER || order > MAX_ORDER) {
    //         fprintf(stderr, "Invalid order: %d .\n\n", order);
    //         usage_3();
    //         exit(EXIT_FAILURE);
    //     }
    // }

    // license_notice();
    // usage_1();  
    // usage_2();

    // if (argc > 2) {
    //     input_file = argv[2];
    //     fp = fopen(input_file, "r");
    //     if (fp == NULL) {
    //         perror("Failure  open input file.");
    //         exit(EXIT_FAILURE);
    //     }
    //     while (!feof(fp)) {
    //         fscanf(fp, "%d\n", &input);
    //         root = insert(root, input, input);
    //     }
    //     fclose(fp);
    //     print_tree(root);
    // }

    // printf("> ");
    // while (scanf("%c", &instruction) != EOF) {
    //     switch (instruction) {
    //     case 'd':
    //         scanf("%d", &input);
    //         root = delete(root, input);
    //         print_tree(root);
    //         break;
    //     case 'i':
    //         scanf("%d", &input);
    //         root = insert(root, input, input);
    //         print_tree(root);
    //         break;
    //     case 'f':
    //     case 'p':
    //         scanf("%d", &input);
    //         find_and_print(root, input, instruction == 'p');
    //         break;
    //     case 'r':
    //         scanf("%d %d", &input, &range2);
    //         if (input > range2) {
    //             int tmp = range2;
    //             range2 = input;
    //             input = tmp;
    //         }
    //         find_and_print_range(root, input, range2, instruction == 'p');
    //         break;
    //     case 'l':
    //         print_leaves(root);
    //         break;
    //     case 'q':
    //         while (getchar() != (int)'\n');
    //         return EXIT_SUCCESS;
    //         break;
    //     case 't':
    //         print_tree(root);
    //         break;
    //     case 'v':
    //         verbose_output = !verbose_output;
    //         break;
    //     case 'x':
    //         if (root)
    //             root = destroy_tree(root);
    //         print_tree(root);
    //         break;
    //     default:
    //         usage_2();
    //         break;
    //     }
    //     while (getchar() != (int)'\n');
    //     printf("> ");
    // }
    // printf("\n");

    return EXIT_SUCCESS;
}
