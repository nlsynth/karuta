// -*- C++ -*-
#ifndef _dfg_d_graph_util_h_
#define _dfg_d_graph_util_h_

#include "nli.h"

#include "dfg/d_graph.h"

#include <map>
#include <set>

using std::map;
using std::set;

namespace dfg {

class DGraphUtil {
public:
  static DGraph *Create(DModule *mod);
  static DRegister *FindNum(DGraph *g, uint64_t num);
  static DRegister *FindEnum(DGraph *g, const string &name, DType *type, int num);
  static DRegister *FindWidthNum(DGraph *g, uint64_t num, int width);
  static DRegister *CloneInitialValue(DGraph *g, DRegister *reg);
  static DRegister *FindSym(DGraph *g, const string &name, DType *type);
  static void ClearAnnotation(DGraph *g);
  static DRegister *AllocTmpReg(DGraph *g, DType *type);
  static DRegister *AllocWireReg(DGraph *g, DType *type);
  static DResource *FindResource(DGraph *g, sym_t sym, bool cr);
  static void FindResourceAll(DGraph *g, sym_t sym, vector<DResource *> *res);
  static DResource *AllocResource(DGraph *g, sym_t op_name);
  static DResource *CopyResource(DGraph *g, DResource *res);
  static DInsn *InsnNew(DGraph *g, DResource *r);
  static DState *AllocStateNext(DGraph *g, DState *s);
  static DState *AllocState(DGraph *g);
  static DRegister *GetNthOutput(DInsn *insn, int nth);
  static bool IsCompatibleResource(DResource *src, DResource *res);

  // TODO(yusuke): Move this to object compiler.
  static void KillIntermediateResource(DGraph *g);
private:
  static DRegister *AllocTempOrWireRegister(DGraph *graph, DType *data_type,
					    enum DRegister::RegType reg_type, const char *tmpl);
  static DRegister *AllocRegister(DGraph *g, enum DRegister::RegType type, DType *val_type);
};

class DStateUtil {
public:
  static DInsn *FindInsnByResource(DState *s, const DResource *r);
  static int GetNrInsnsByResource(DState *s, const DResource *r);
  static DInsn *FindNthInsnByResource(DState *s, const DResource *r, int nth);
  static void MoveInsn(DInsn *insn, DState *src, DState *dst);
  static void EraseInsn(DState *ds, DInsn *insn);
  static void EraseInsnByResource(DState *ds, DResource *r);
  // layer violation, to be moved
  static void SetNextState(DGraph *graph, DState *st, DState *to);
  static DState *GetNextState(DGraph *graph, DState *st);
  // includes original state
  static void CollectReachable(DGraph *g, DState *initial,
			       set<DState *> *reachable);
 private:
  static void CollectTargets(DGraph *graph, bool reverse,
			     map<DState *, set<DState *> > *targets);
};

class DTypeUtil {
public:
  static DType *GetIntType(int width);
  static DType *GetBoolType();
  static DType *FindDType(enum DType::TypeClass type, int width);
  static bool IsCompatibleType(DType *src, DType *type);
  static int GetWidth(DType *type);

  static void ReleaseTypes();
private:
  static vector<DType *> all_types;
};

class DOperatorUtil {
public:
  static DOperator *FindOperator(sym_t opr);
  static DOperator *InstallOperator(sym_t name, bool is_exclusive);
  static DOperator *InstallOperatorWithSideEffect(sym_t name);
};

}  // namespace dfg

#endif  // _dfg_d_graph_util_h_
