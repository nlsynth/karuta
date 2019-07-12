#include "synth/dot_output.h"

#include "iroha/dot.h"

namespace synth {

DotOutput::DotOutput(ObjectTree *tree) : tree_(tree) {
  dot_.reset(new iroha::Dot());
}

DotOutput::~DotOutput() {
}

void DotOutput::Write(const string &fn) {
  dot_->Write(fn);
}

}  // namespace synth
