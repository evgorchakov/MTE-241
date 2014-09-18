#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "bst.h"

/* Macro for creating a bsn_t* */
#define bsn_create( val ) ({                        \
    bsn_t* tmp = malloc(sizeof(bsn_t));             \
    if (!tmp) exit(EXIT_FAILURE);                   \
    tmp->val = val;                                 \
    tmp->left = NULL;                               \
    tmp->right = NULL;                              \
    tmp;                                            \
})

static S32 value_array[100] = {
         534, 6415,  465, 4459, 6869, 4442, 5840, 4180, 7450, 9265,
          23, 2946, 3657, 3003,   29, 8922, 2199, 6973, 2344, 1802,
        9248, 5388, 2198, 2838, 1117, 5346, 4619, 8334, 9593, 2288,
        7346, 9252, 8169, 4138, 7479,  366, 5064, 6872,   -3, 8716,
        8089,   15, 5337, 8700, 8128, 6673, 5395, 7772, 5792, 3379,
        2438, 2184, 1176, 6083, 6572,  915, 1635, 6457, 3729, 7791,
        7642, 1548, 6267, 6562, 6477, 6026, 7460, 7226, 1994, 6519,
        7660, 3018, 2205,  559, 1347, 1647, 8778, 3864, 2543, 8370,
        1152,  865,  860, 8735, 4782,  574, 5858, 7089, 2096, 7449,
        1310, 3043, 8247, 6382, 2470, 3072, 1297, 7396, 7073,  140
    };

static S32 erase_array[5][20] = {
        { 915, 1802, 1994, 6083,  865, 8735, 6457, 8334, 4459, 3003,
         2198, 2470, 7642,   15, 7772, 1152,   29, 2096,  574, 6415},

        {7396, 5858, 4442, 6872, 8128, 2838,  465, 6477, 8247, 6572,
         2946, 1297, 3729, 4138, 5064, 8778, 4619, 5346,   -3, 3657},

        {1347, 2288, 7791, 7073, 5792, 3018,  366, 7449, 2543, 8089,
         4180, 6026, 3864, 5395, 7226, 1117,   23, 7089, 1635, 6267},

        {8700, 3072, 7660, 6673, 2438, 3043, 1548, 4782, 6519, 7460,
          559,  860, 6562, 9593, 1647, 1310, 3379, 8716, 8922, 7450},

        {9265, 6973, 8169, 5388,  140, 6869, 2344, 9252, 2184, 9248,
          534, 2199, 6382, 7479, 8370, 7346, 5337, 5840, 2205, 1176}
    };

void bst_init( bst_t *tree ) {
    tree->root = NULL;
    tree->size = 0;
}

void bst_destroy( bst_t *tree ) {
    // Calling recursive delete on root node
    bst_destroy_start_with_node(tree->root);
    free(tree);
}

/*
 * void bst_destroy_start_with_node(bsn_t *node)
 *
 * Destroys a (sub-)tree recursively.
 *
 * Parameters:
   bsn_t *node:
     A pointer to an arbitrary node in a tree.
 */
void bst_destroy_start_with_node( bsn_t *node ){
    if (!node) return;
    if (node->left) bst_destroy_start_with_node(node->left);
    if (node->right) bst_destroy_start_with_node(node->right);
    free(node);
    node = NULL;
}

size_t bst_size( bst_t *tree ) {
	return (tree ? tree->size : 0);
}

bool bst_insert( bst_t *tree, S32 val ) {	
	return __FALSE;
}

S32 bst_min( bst_t *tree ) {
	return 0;
}

S32 bst_max( bst_t *tree ) {
	return 0;
}

bool bst_erase( bst_t *tree, S32 val ) {
	return __FALSE;
}