#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "type.h"
#include "memhalf.h"


void print_bucket(memmap_free_t* head){
    memmap_free_t* tmp_free = head;
    memmap_t* tmp_alloc = NULL;
    while (tmp_free){
        tmp_alloc = (memmap_t*) tmp_free;
        printf("[%d] --> ", get_block_size(tmp_alloc));
        if (is_last_in_bucket(tmp_free)) break;
        tmp_free = get_next_free(tmp_free);
    }
    printf("\n");
}

void print_buckets(memmap_free_t* buckets[], short size){
    short i;
    printf("==================== START MEMORY LAYOUT ====================\n");
    for (i=0; i<size; i++) {
        printf("%d (%d -- %d ): ", i, 1 << i+5, (1 << i+6) -1);
        print_bucket(buckets[i]);
    }
    printf("===================== END MEMORY LAYOUT =====================\n");
}
    
void main(void){
    half_init();
    void* dummy1 = half_alloc_2(1000);
    void* dummy2 = half_alloc_2(1000);
    void* dummy3 = half_alloc_2(1000);
    print_buckets(mprgmmap, 10);
    half_free(dummy1);
    print_buckets(mprgmmap, 10);
    half_free(dummy2);
    print_buckets(mprgmmap, 10);
    half_free(dummy3);
    print_buckets(mprgmmap, 10);
    printf("%p\n", base_ptr);
}