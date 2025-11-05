// agent/src/interpose.cpp
#include <unistd.h>
#include <string.h>
#include <malloc/malloc.h>
#include <stdlib.h>

// Forward declare malloc and free
extern "C" {
    void* malloc(size_t);
    void free(void*);
}

static void log_(const char* s) {
    write(2, s, strlen(s));
    write(2, "\n", 1);
}

__attribute__((constructor))
static void ctor() {
    log_("[dsv-agent] constructor called");
}

__attribute__((destructor))
static void dtor() {
    log_("[dsv-agent] dtor");
}

// Our replacement malloc
static void* my_malloc(size_t size) {
    // Use malloc_zone_malloc to bypass our interposer and get real allocation
    void* ptr = malloc_zone_malloc(malloc_default_zone(), size);
    
    // Log the allocation
    write(2, "[dsv-agent] malloc intercepted\n", 32);
    
    return ptr;
}

// Our replacement free
static void my_free(void* ptr) {
    if (!ptr) return;
    
    // Use malloc_zone_free to bypass our interposer
    malloc_zone_free(malloc_default_zone(), ptr);
    
    // Log the free
    write(2, "[dsv-agent] free intercepted\n", 30);
}

// DYLD_INTERPOSE macro - the official way to do interposing on macOS
#define DYLD_INTERPOSE(_replacement,_replacee) \
   __attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
            __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

// Interpose malloc and free
DYLD_INTERPOSE(my_malloc, malloc);
DYLD_INTERPOSE(my_free, free);
