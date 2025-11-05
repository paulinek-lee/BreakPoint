#include <unistd.h>
#include <string.h>

static void dsv_safe_log(const char* s) {
  write(2, s, strlen(s));
  write(2, "\n", 1);
}

__attribute__((constructor))
static void dsv_init_ctor(void) {
  dsv_safe_log("[dsv-agent] init: agent loaded");
}

__attribute__((destructor))
static void dsv_fini_dtor(void) {
  dsv_safe_log("[dsv-agent] fini: agent unloading");
}
