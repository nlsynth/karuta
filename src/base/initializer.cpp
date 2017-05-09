#include "base/initializer.h"

#include "nli.h"
#include <vector>

using namespace std;
struct Functions {
  vector<void (*)()> initializers;
  vector<void (*)()> finalizers;
};
static Functions *functions;

SIEntry::SIEntry(const char *name, void (*initializer)(), void (*finalizer)()) {
  if (!functions) {
    functions = new Functions;
  }
  if (initializer) {
    functions->initializers.push_back(initializer);
  }
  if (finalizer) {
    functions->finalizers.push_back(finalizer);
  }
}

void StaticInitializer::RunInitializers() {
  for (size_t i = 0; i < functions->initializers.size(); ++i) {
    functions->initializers[i]();
  }
  functions->initializers.clear();
}

void StaticInitializer::RunFinalizers() {
  for (size_t i = 0; i < functions->finalizers.size(); ++i) {
    functions->finalizers[i]();
  }
  if (functions) {
    delete functions;
  }
  functions = NULL;
}
