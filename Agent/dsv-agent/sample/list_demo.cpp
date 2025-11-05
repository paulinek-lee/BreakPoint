#include <cstdio>
#include <cstdlib>

int main() {
  std::puts("sample app: starting");
  void* p = std::malloc(32);
  std::printf("sample app: allocated p=%p\n", p);
  std::puts("sample app: press Enter to exit");
  getchar();
  std::free(p);
  std::puts("sample app: bye");
  return 0;
}
