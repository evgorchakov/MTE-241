#include "memhalf.h"

void* get_prev_block(memmap_t const* mmap){
	return (void*)mmap->prev_block;
}

void* get_next_block(memmap_t const* mmap){
	return (void*)mmap->next_block;
}

size_t get_block_size(memmap_t const* mmap){
	return (size_t)mmap->block_size;
}

bool get_allocated(memmap_t const* mmap){
	return mmap->alloc;
}

void* get_prev_free(memmap_free_t const* mmap){
	return (void*)mmap->prev_free;
}

void* get_next_free(memmap_free_t const* mmap){
	return (void*)mmap->next_free;
}

void memmap_init(memmap_t* const mmap, size_t size){
	// Initialize the values for the fields
	mmap->prev_block = 0;
	mmap->next_block = 0;
	mmap->block_size = size;
	mmap->alloc = false;
}

void memmap_free_init(memmap_free_t* const mmap, size_t size){
	// memmap is the first field in memmap_free_t
	memmap_t* memmap_alloc = (memmap_t*)(&mmap);
	memmap_init(memmap_alloc, size);
	mmap->memmap = (U32)memmap_alloc;
	mmap->prev_free = 0;
	mmap->next_free = 0;
}

void half_init(){
	memmap_free_t* block = (memmap_free_t*)malloc(MAX_MEMORY);
	memmap_free_init(block, MAX_MEMORY);
	mprgmmap[NUM_BUCKETS - 1] = block;
}

void* half_alloc(size_t n){
	unsigned short m = CEIL32(n + HEADER_SIZE);
	int i = 0;
	if(m > MAX_MEMORY) return NULL;
	i = get_alloc_bucket_index(m);
	if(i >= NUM_BUCKETS) return NULL; // Out of memory

	memmap_free_t* mmap = mprgmmap[i];
	memmap_t* mmap_alloc = (memmap_t*)mmap->memmap;

	void* ptr_next = get_next_free(mmap);

	// Remove allocated block from LL
	if(ptr_next){
		memmap_free_t* mmap_next_free = (memmap_free_t*)(ptr_next - sizeof(memmap_free_t));
		mmap_next_free->prev_free = NULL;
		mprgmmap[i] = mmap_next_free; 
	}

	size_t mmap_size = get_block_size(mmap_alloc);
	mmap_alloc->alloc = __TRUE;

	if(mmap_size - m > 32) {
		void* new_block = ((void*)mmap) + sizeof(memmap_free_t) + m;
		half_free(new_block);
	}

	return (((void*)mmap) + sizeof(memmap_free_t));
}

void half_free(void* ptr){

}

int main( int argc, char *argv[] ){

	printf("%d\n", CEIL32(520));
	printf("%d\n", CEIL32(28));
	printf("%d\n", get_alloc_bucket_index(1000));
	printf("%d\n", get_free_bucket_index(1000));
}