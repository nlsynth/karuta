#
EXTRA = ["QA", "imported_file.n", "run-test", "resource.v", "test_tb.v",
         "test_files.py"]

# see file QA to see category.
default_tests = ["fe_error/misc.n",
                 "fe_error/tbd.n",
                 "fe_error/infinite_loop.n",
                 "fe_error/parse_error.n",
                 "fe_lang/import_file.n", "fe_lang/load.n", "fe_lang/for.n",
                 "fe_lang/funcall.n", "fe_lang/if.n", "fe_lang/string.n",
                 "fe_lang/decl.n", "fe_lang/scope.n", "fe_lang/pipe.n",
                 "fe_lang/while.n",
                 "fe_misc/errors.n", "fe_misc/tb.n",
                 "fe_misc/hello.n", "fe_misc/parser.n",
                 "fe_misc/misc.n",
                 "fe_obj/object.n", "fe_obj/this_obj.n", "fe_obj/thread.n",
                 "fe_value/basic.n", "fe_value/numeric.n",
                 "fe_value/false.n", "fe_value/array.n",
                 "synth_misc/null.n", "synth_value/false.n",
                 "synth_value/basic.n",
                 "synth_value/bitops.n", "synth_value/shift.n",
                 "synth_value/array_ro.n", "synth_value/array_rw.n",
                 "synth_lang/mem.n", "synth_lang/cond.n", "synth_lang/member.n",
                 "synth_lang/import_resource.n", "synth_lang/return.n",
                 "synth_lang/pipe.n",
                 "synth_obj/sub_obj_call.n",
                 "synth_lang/funcall.n",
                 #"synth_lang/no_member_decl.n",
                 "synth_regression/t04_0_0_26.n",
                 "synth_regression/t04_0_0_30.n",
                 "synth_regression/t04_0_0_30_1.n",
                 "synth_regression/t04_0_0_30_2.n",
                 "synth_regression/t04_0_0_33.n",
                 "synth_regression/t04_0_0_33_1.n",
                 "synth_regression/t04_0_0_33_2.n",
                 "synth_regression/t04_0_0_33_3.n",
                 "synth_regression/t04_0_0_33_4.n",
                 "synth_regression/t04_0_0_33_5.n",
                 "synth_regression/t04_0_0_33_6.n",
                 "synth_regression/t04_0_0_34_1.n",
                 "synth_regression/t04_0_0_34_2.n",
                 "synth_regression/t04_0_0_35_1.n",
                 "synth_regression/t04_0_1_0_0.n",
                 "synth_regression/t04_0_1_1_0.n",
                 "synth_regression/t04_0_1_9_0.n",
                 "synth_regression/t04_0_1_9_1.n",
#                 "t91_funcall_width_infer.n",
#                 "type_inf.n",
                 ]

def GetFiles(base_dir):
    files = []
    for fn in default_tests + EXTRA:
        files.append(base_dir + fn)
    return files