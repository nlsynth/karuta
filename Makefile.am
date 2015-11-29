AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -DNLI_DIR=\"$(sysconfdir)\" -Isrc

SUBDIRS = lib docs tests
CCRT_FILES = ccrt.h ccrt_main.cpp
EXAMPLES_FILES= \
 examples/hello.n examples/top.n examples/tb_top.v \
 examples/handshake.n examples/tb_handshake.v \
 examples/md5.n \
 examples/mt.n examples/mt_test.n examples/mt_ref.cpp
EXTRA_DIST = $(CCRT_FILES) $(EXAMPLES_FILES) nli run-file README.md .gitignore

pkgdata_DATA = $(CCRT_FILES)

bin_PROGRAMS = nli-bin

compiler_SOURCES = \
 src/compiler/compiler.cpp src/compiler/compiler.h

fe_SOURCES = \
 src/fe/nodecode.cpp src/fe/nodecode.h \
 src/fe/fe.cpp src/fe/fe.h \
 src/fe/common.cpp src/fe/common.h \
 src/fe/builder.cpp src/fe/builder.h \
 src/fe/emitter.cpp src/fe/emitter.h \
 src/fe/enum_decl.cpp src/fe/enum_decl.h \
 src/fe/expr.cpp src/fe/expr.h \
 src/fe/scanner.cpp src/fe/scanner.h \
 src/fe/stmt.cpp src/fe/stmt.h \
 src/fe/method.cpp src/fe/method.h \
 src/fe/var_decl.cpp src/fe/var_decl.h

numeric_SOURCES = \
 src/numeric/numeric.cpp src/numeric/numeric.h

opt_SOURCES = \
 src/opt/opt.cpp src/opt/opt.h \
 src/opt/opt_context.cpp src/opt/opt_context.h \
 src/opt/opt_phase.cpp src/opt/opt_phase.h \
 src/opt/constants.h \
 src/opt/basic_block.cpp src/opt/basic_block.h \
 src/opt/constant_insn.cpp src/opt/constant_insn.h \
 src/opt/dfc.cpp src/opt/dfc.h \
 src/opt/dominator.cpp src/opt/dominator.h \
 src/opt/misc.cpp src/opt/misc.h \
 src/opt/temp_var.cpp src/opt/temp_var.h \
 src/opt/reg_share.cpp src/opt/reg_share.h \
 src/opt/resource_alloc.cpp src/opt/resource_alloc.h \
 src/opt/resource_annotation.cpp src/opt/resource_annotation.h \
 src/opt/ssa.cpp src/opt/ssa.h \
 src/opt/ssa_assorted.cpp src/opt/ssa_assorted.h \
 src/opt/ssa_cleaner.cpp src/opt/ssa_cleaner.h \
 src/opt/ssa_converter.cpp src/opt/ssa_converter.h \
 src/opt/ssa_misc.cpp src/opt/ssa_misc.h \
 src/opt/wire_insn.cpp src/opt/wire_insn.h

dfg_SOURCES = \
 src/dfg/dfg.cpp src/dfg/dfg.h \
 src/dfg/dfg_util.cpp src/dfg/dfg_util.h \
 src/dfg/dfg_dump.cpp src/dfg/dfg_dump.h \
 src/dfg/d_graph.cpp src/dfg/d_graph.h \
 src/dfg/d_graph_annotation.cpp src/dfg/d_graph_annotation.h \
 src/dfg/d_graph_util.cpp src/dfg/d_graph_util.h \
 src/dfg/d_insn.cpp src/dfg/d_insn.h \
 src/dfg/d_module.cpp src/dfg/d_module.h \
 src/dfg/d_resource.cpp src/dfg/d_resource.h \
 src/dfg/resource_params.cpp src/dfg/resource_params.h

synth_SOURCES = \
 src/synth/interface.cpp src/synth/interface.h \
 src/synth/resource_set.cpp src/synth/resource_set.h \
 src/synth/synth.cpp src/synth/synth.h \
 src/synth/channel_synth.cpp src/synth/channel_synth.h \
 src/synth/method_synth.cpp src/synth/method_synth.h \
 src/synth/object_synth.cpp src/synth/object_synth.h \
 src/synth/thread_synth.cpp src/synth/thread_synth.h

vm_SOURCES = \
 src/vm/array_wrapper.cpp src/vm/array_wrapper.h \
 src/vm/opcode.cpp src/vm/opcode.h \
 src/vm/int_array.cpp src/vm/int_array.h \
 src/vm/channel.cpp src/vm/channel.h \
 src/vm/executor.cpp src/vm/executor.h \
 src/vm/executor_toplevel.cpp src/vm/executor_toplevel.h \
 src/vm/gc.cpp src/vm/gc.h \
 src/vm/insn.cpp src/vm/insn.h \
 src/vm/insn_annotator.cpp src/vm/insn_annotator.h \
 src/vm/register.cpp src/vm/register.h \
 src/vm/value.cpp src/vm/value.h \
 src/vm/method.cpp src/vm/method.h \
 src/vm/native_methods.cpp src/vm/native_methods.h \
 src/vm/object.cpp src/vm/object.h \
 src/vm/dmodule_wrapper.cpp src/vm/dmodule_wrapper.h \
 src/vm/string_wrapper.cpp src/vm/string_wrapper.h \
 src/vm/thread.cpp src/vm/thread.h \
 src/vm/thread_wrapper.cpp src/vm/thread_wrapper.h \
 src/vm/vm.cpp src/vm/vm.h

writer_SOURCES = \
 src/writer/writer.cpp src/writer/writer.h \
 src/writer/writer_util.cpp src/writer/writer_util.h \
 src/writer/module_template.cpp src/writer/module_template.h \
 src/writer/vl_writer.cpp src/writer/vl_writer.h \
 src/writer/vl_module.cpp src/writer/vl_module.h \
 src/writer/vl_channel.cpp src/writer/vl_channel.h \
 src/writer/vl_graph.cpp src/writer/vl_graph.h \
 src/writer/vl_state.cpp src/writer/vl_state.h \
 src/writer/vl_util.cpp src/writer/vl_util.h \
 src/writer/cc_writer.cpp src/writer/cc_writer.h \
 src/writer/cc_class.cpp src/writer/cc_class.h \
 src/writer/cc_graph.cpp src/writer/cc_graph.h \
 src/writer/cc_module.cpp src/writer/cc_module.h \
 src/writer/cc_state.cpp src/writer/cc_state.h

nli_bin_SOURCES = \
 src/main.cpp \
 src/nli.cpp src/nli.h src/pool.h src/stl_util.h \
 src/initializer.cpp src/initializer.h \
 src/dump_stream.cpp src/dump_stream.h \
 src/logging.cpp src/logging.h \
 src/status.cpp src/status.h \
 src/sym.cpp src/sym.h \
 $(compiler_SOURCES) \
 $(dfg_SOURCES) \
 $(fe_SOURCES) \
 $(numeric_SOURCES) \
 $(opt_SOURCES) \
 $(synth_SOURCES) \
 $(vm_SOURCES) \
 $(writer_SOURCES)


nli_bin_LDADD = libparse.la
nli_bin_YFLAGS = -d -g
nli_bin_CXXFLAGS = -Wall -g

noinst_LTLIBRARIES = libparse.la
libparse_la_YFLAGS = -d -g -p z_yy
libparse_la_SOURCES = src/fe/parser.ypp
