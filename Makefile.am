AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -DNLI_DIR=\"$(sysconfdir)\" -Isrc -Iiroha/src

SUBDIRS = iroha lib docs tests
CCRT_FILES = ccrt.h ccrt_main.cpp
EXAMPLES_FILES= \
 examples/hello.n examples/top.n examples/tb_top.v \
 examples/handshake.n examples/tb_handshake.v \
 examples/md5.n examples/led.n \
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


synth_SOURCES= \
 src/synth/common.h \
 src/synth/synth.cpp src/synth/synth.h \
 src/synth/channel_synth.cpp src/synth/channel_synth.h \
 src/synth/design_synth.cpp src/synth/design_synth.h \
 src/synth/insn_walker.cpp src/synth/insn_walker.h \
 src/synth/method_context.cpp src/synth/method_context.h \
 src/synth/method_expander.cpp src/synth/method_expander.h \
 src/synth/method_scanner.cpp src/synth/method_scanner.h \
 src/synth/method_synth.cpp src/synth/method_synth.h \
 src/synth/object_method.cpp src/synth/object_method.h \
 src/synth/object_method_names.h \
 src/synth/object_synth.cpp src/synth/object_synth.h \
 src/synth/shared_resource_set.cpp src/synth/shared_resource_set.h \
 src/synth/resource_params.cpp src/synth/resource_params.h \
 src/synth/resource_set.cpp src/synth/resource_set.h \
 src/synth/thread_synth.cpp src/synth/thread_synth.h \
 src/synth/tool.cpp src/synth/tool.h

vm_SOURCES = \
 src/vm/common.h \
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
 src/vm/mailbox_wrapper.cpp src/vm/mailbox_wrapper.h \
 src/vm/numeric_object.cpp src/vm/numeric_object.h \
 src/vm/string_wrapper.cpp src/vm/string_wrapper.h \
 src/vm/thread.cpp src/vm/thread.h \
 src/vm/thread_wrapper.cpp src/vm/thread_wrapper.h \
 src/vm/vm.cpp src/vm/vm.h

nli_bin_SOURCES = \
 src/main.cpp \
 src/nli.cpp src/nli.h src/pool.h src/stl_util.h \
 src/initializer.cpp src/initializer.h \
 src/dump_stream.cpp src/dump_stream.h \
 src/logging.cpp src/logging.h \
 src/status.cpp src/status.h \
 src/sym.cpp src/sym.h \
 $(compiler_SOURCES) \
 $(fe_SOURCES) \
 $(numeric_SOURCES) \
 $(synth_SOURCES) \
 $(vm_SOURCES)


nli_bin_LDADD = libparse.la iroha/libiroha.la
nli_bin_YFLAGS = -d -g
nli_bin_CXXFLAGS = -Wall -g

noinst_LTLIBRARIES = libparse.la
libparse_la_YFLAGS = -d -g -p z_yy
libparse_la_SOURCES = src/fe/parser.ypp
