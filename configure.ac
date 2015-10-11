AC_INIT([nli], [0.1.9], [tabata.yusuke@gmail.com])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])
# see m4/m4_ax_check_compile_flag
AX_CHECK_COMPILE_FLAG([-std=c++11],[CXXFLAGS="$CXXFLAGS -std=c++11"],[],[])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_YACC
LT_INIT

AC_CONFIG_FILES([Makefile lib/Makefile lib/nli docs/Makefile tests/Makefile])
AC_OUTPUT
