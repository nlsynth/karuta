/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "src/fe/parser.ypp"

#include "base/status.h"
#include "base/sym.h"
#include "fe/builder.h"
#include "fe/emitter.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/scanner_interface.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "karuta/annotation_builder.h"

extern int yylex();
extern void yyerror(const char *msg);


#line 88 "src/fe/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_SRC_FE_PARSER_H
# define YY_SRC_FE_PARSER_H
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_ADD_SUB = 258,
    K_ALWAYS = 259,
    K_AS = 260,
    K_ASSIGN = 261,
    K_BOOL = 262,
    K_BREAK = 263,
    K_CASE = 264,
    K_CHANNEL = 265,
    K_CONST = 266,
    K_CONTINUE = 267,
    K_DEFAULT = 268,
    K_DO = 269,
    K_ELSE = 270,
    K_ENUM = 271,
    K_EQ_COMPARE = 272,
    K_FUNC = 273,
    K_FOR = 274,
    K_GOTO = 275,
    K_IF = 276,
    K_IMPORT = 277,
    K_INC_DEC = 278,
    K_INT = 279,
    K_UINT = 280,
    K_TYPE = 281,
    K_LG_COMPARE = 282,
    K_MAILBOX = 283,
    K_OBJECT = 284,
    K_PROCESS = 285,
    K_RETURN = 286,
    K_SHARED = 287,
    K_SHIFT = 288,
    K_STRING = 289,
    K_SWITCH = 290,
    K_THREAD = 291,
    K_INPUT = 292,
    K_OUTPUT = 293,
    K_VAR = 294,
    K_WHILE = 295,
    K_WITH = 296,
    K_MODULE = 297,
    NUM = 298,
    SYM = 299,
    STR = 300,
    K_LOGIC_OR = 301,
    K_LOGIC_AND = 302,
    K_BIT_CONCAT = 303,
    SIGN = 304,
    ADDRESS = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "src/fe/parser.ypp"

  class ArrayInitializer *array;
  class ArrayShape *shape;
  class Expr *expr;
  class ExprSet *expr_set;
  class EnumDecl *enum_decl;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  iroha::NumericLiteral num;
  int id;
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 212 "src/fe/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_SRC_FE_PARSER_H  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   905

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  300

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    69,     2,     2,    54,     2,
      66,    67,    55,     2,    46,     2,    61,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    70,
       2,     2,     2,    47,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    62,     2,    63,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,    52,    65,    58,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    49,    50,    51,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   100,   100,   102,   103,   104,   104,   106,
     106,   106,   108,   110,   115,   117,   119,   121,   125,   125,
     125,   127,   129,   131,   135,   137,   139,   143,   145,   149,
     153,   155,   159,   161,   165,   165,   169,   171,   173,   178,
     178,   178,   180,   184,   185,   188,   200,   200,   200,   200,
     200,   202,   202,   216,   217,   220,   222,   224,   226,   228,
     232,   235,   239,   249,   257,   260,   265,   267,   269,   275,
     279,   283,   288,   288,   288,   292,   295,   303,   317,   319,
     321,   323,   325,   327,   332,   336,   340,   342,   344,   345,
     346,   348,   350,   352,   353,   354,   355,   356,   357,   358,
     360,   361,   362,   363,   367,   371,   375,   375,   379,   381,
     385,   385,   389,   389,   393,   394,   398,   403,   409,   413,
     416,   421,   425,   427,   431,   436,   451,   460,   466,   473,
     477,   485,   488,   489,   492,   495,   499,   504,   508,   510,
     514,   517,   524,   526,   528,   530,   532,   534,   536,   538,
     540,   542,   544,   546,   548,   550,   552,   554,   556,   558,
     560,   562,   564,   566,   568,   568,   570,   572,   574,   577,
     585,   587,   592,   594,   598,   600,   604,   608,   613,   615
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_ADD_SUB", "K_ALWAYS", "K_AS",
  "K_ASSIGN", "K_BOOL", "K_BREAK", "K_CASE", "K_CHANNEL", "K_CONST",
  "K_CONTINUE", "K_DEFAULT", "K_DO", "K_ELSE", "K_ENUM", "K_EQ_COMPARE",
  "K_FUNC", "K_FOR", "K_GOTO", "K_IF", "K_IMPORT", "K_INC_DEC", "K_INT",
  "K_UINT", "K_TYPE", "K_LG_COMPARE", "K_MAILBOX", "K_OBJECT", "K_PROCESS",
  "K_RETURN", "K_SHARED", "K_SHIFT", "K_STRING", "K_SWITCH", "K_THREAD",
  "K_INPUT", "K_OUTPUT", "K_VAR", "K_WHILE", "K_WITH", "K_MODULE", "NUM",
  "SYM", "STR", "','", "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND",
  "K_BIT_CONCAT", "'|'", "'^'", "'&'", "'*'", "'/'", "'!'", "'~'", "SIGN",
  "ADDRESS", "'.'", "'['", "']'", "'{'", "'}'", "'('", "')'", "'@'", "'#'",
  "';'", "$accept", "input", "FUNC_DECL_OR_STMT_LIST", "FUNC_DECL_OR_STMT",
  "$@1", "MODULE_HEAD", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE",
  "ANNOTATION_KEY", "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY",
  "SYM_OR_EMPTY", "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC",
  "FUNC_DECL", "$@2", "FUNC_DECL_HEAD", "FUNC_DECL_KW", "FUNC_DECL_NAME",
  "STMT_LIST", "VAR_DECL_TAIL", "VAR_OR_SHARED", "VAR_DECL", "$@3",
  "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC",
  "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "$@4", "$@5", "VAR_DECL_STMT", "TYPE_NAME", "LABEL",
  "RETURN", "STMT", "EOS", "GOTO_HEAD", "IMPORT_STMT", "$@6",
  "IMPORT_SPEC_OR_EMPTY", "CHANNEL_DECL_STMT", "$@7", "MAILBOX_DECL_STMT",
  "$@8", "ASSIGN_OR_EMPTY", "IF_COND_PART", "IF_WITH_ELSE", "IF_STMT",
  "FOR_HEAD", "FOR_HEAD_PART", "FOR_COND_PART", "FOR_STMT",
  "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD", "DO_WHILE_BODY",
  "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE", "BLOCK",
  "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "EXPR", "$@9", "NUM_EXPR",
  "VAR", "VAR_LIST", "FUNCALL_HEAD", "FUNCALL", "ARG_LIST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    44,    63,    58,   301,
     302,   303,   124,    94,    38,    42,    47,    33,   126,   304,
     305,    46,    91,    93,   123,   125,    40,    41,    64,    35,
      59
};
# endif

#define YYPACT_NINF (-207)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -207,    36,   143,  -207,   252,  -207,   198,  -207,   252,  -207,
    -207,  -207,     1,   252,    56,    56,    39,     5,  -207,   252,
     252,  -207,   252,    71,  -207,  -207,    21,   423,  -207,   134,
      74,  -207,   132,  -207,  -207,   101,  -207,    74,    74,    84,
      -9,  -207,   334,   252,    79,  -207,    84,  -207,    84,   120,
    -207,  -207,  -207,  -207,   -18,    41,  -207,   252,  -207,    16,
     -19,  -207,  -207,  -207,  -207,  -207,  -207,  -207,    56,   -33,
     706,   117,   252,   252,   706,   106,   106,   128,  -207,  -207,
     129,   -19,   -19,   370,   113,   115,  -207,  -207,  -207,  -207,
      45,    99,   469,  -207,  -207,    41,   -25,    74,  -207,  -207,
     167,  -207,  -207,  -207,   121,    56,   313,   706,   252,  -207,
    -207,   126,   247,  -207,   106,   252,   252,   252,  -207,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,  -207,   706,   137,   106,   149,   151,   201,
     -19,   412,  -207,  -207,  -207,   297,  -207,    56,    56,  -207,
    -207,  -207,  -207,    42,    43,  -207,  -207,  -207,  -207,  -207,
      56,  -207,  -207,   706,  -207,  -207,  -207,  -207,  -207,  -207,
     514,   252,  -207,   184,  -207,    -5,   748,   708,   349,     4,
     748,   652,   803,   664,   568,   763,   843,   525,   -19,   -19,
    -207,   556,  -207,  -207,  -207,    93,   155,    74,   207,  -207,
    -207,  -207,   215,   -32,  -207,   218,   -21,   194,     0,     0,
     263,  -207,   106,  -207,    56,  -207,   106,   127,   183,  -207,
     454,   252,   252,  -207,   186,  -207,  -207,  -207,  -207,   207,
    -207,    38,   188,  -207,   199,   297,  -207,  -207,  -207,   319,
     319,  -207,  -207,   161,   185,   174,   176,    56,    89,   187,
    -207,  -207,  -207,   200,  -207,   788,   610,  -207,  -207,  -207,
    -207,   202,  -207,  -207,  -207,  -207,  -207,   182,    56,   210,
     212,   106,  -207,  -207,    87,  -207,  -207,   183,   189,  -207,
    -207,   319,   193,  -207,  -207,  -207,   208,  -207,  -207,  -207,
    -207,    31,  -207,  -207,   203,   319,  -207,   229,  -207,  -207
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,     0,   128,     0,   105,     0,   106,
     164,    85,     0,     0,     0,    11,   170,   140,   168,     0,
       0,   136,     0,    27,   104,     4,     0,    51,     5,    75,
       0,   100,     0,     6,    86,     0,   101,     0,     0,     0,
       0,    94,    24,     0,     0,    95,     0,    96,     0,     0,
      97,    98,    93,    43,     0,     0,   169,   178,   147,   140,
     166,    80,    79,    78,    81,    83,    82,   172,     0,     0,
     116,     0,     0,     0,   126,     9,    10,     0,    84,   176,
       0,   148,   149,     0,    26,     0,     7,   110,   121,   112,
       0,     0,     0,    99,    92,     0,     0,     0,   102,   103,
     118,   120,   119,    51,     0,     0,     0,   124,     0,   127,
     129,     0,    24,    88,    54,     0,     0,     0,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,   179,     0,    53,     0,     0,   109,
     165,     0,   171,   141,   142,    21,     3,     0,     0,    41,
      39,    40,    43,     0,     0,    48,    47,    49,    50,    46,
       0,    72,    77,    76,    91,    90,    89,   117,   123,   122,
       0,     0,   135,    51,    44,   150,   154,   156,   155,   153,
     145,     0,   161,   162,   157,   159,   160,   158,   151,   152,
     146,     0,   177,   173,   138,     0,     0,     0,     0,    18,
      19,    20,     0,     0,    22,     0,     0,    24,   114,   114,
      24,    38,    42,    37,    60,    52,   174,     0,     0,   125,
       0,     0,     0,   143,     0,   137,   108,   107,   134,   131,
     132,     0,     0,    17,     0,     0,    25,     8,   115,     0,
       0,    35,    62,     0,    61,    78,     0,     0,     0,    66,
      55,    69,    70,    73,   130,   167,     0,   139,   133,    16,
      14,     0,    13,    15,    23,   111,   113,    32,     0,     0,
       0,   175,    57,    59,     0,    67,    45,     0,     0,   144,
      12,     0,     0,    63,    56,    58,     0,    68,    71,    74,
      30,     0,    29,    36,    64,     0,    33,     0,    65,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -207,  -207,   130,  -207,  -207,  -207,  -207,    46,  -207,  -207,
     -40,  -207,   -22,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
     122,  -192,  -207,  -207,  -207,  -206,  -207,  -207,   -14,  -207,
      11,  -207,  -207,  -207,  -207,   251,   283,  -207,  -207,  -109,
     -17,  -207,  -207,  -207,  -207,  -207,  -207,  -207,  -207,    90,
    -207,  -207,   260,  -207,  -207,  -207,  -207,  -207,  -207,  -207,
    -207,  -207,  -207,  -207,    72,   -16,  -207,   272,  -207,    -3,
    -207,  -207,    -6,  -207,  -207,   267,  -207
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    25,   146,    26,   203,   204,   205,   206,
      27,    85,   290,   291,   282,    28,    90,   152,   153,   154,
     112,   215,   160,    29,    91,   292,   243,   244,   275,   276,
     252,   253,   162,   218,   278,    30,   250,    31,    32,    33,
      34,    35,    36,    71,   197,    37,   147,    38,   148,   239,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,   229,   230,    52,    53,    54,   195,    55,
      72,    56,   216,   217,    57,    58,   135
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    60,   103,   174,   118,    70,   238,   115,    75,    76,
      74,   249,     8,    93,   232,    94,    81,    82,   118,    83,
      98,    99,   242,   100,   102,   235,    67,   118,   137,    95,
     109,   138,   110,   265,   266,   233,     3,   113,   133,   106,
     107,    79,   131,   132,   115,    24,   236,   116,   114,   149,
     129,   130,    24,    78,   134,    21,   131,   132,   117,   129,
     130,   137,   136,   150,   118,   131,   132,    73,   119,   140,
     141,    79,   173,    80,   120,   151,   283,   295,   164,   165,
     166,   259,    79,   260,    80,    86,    67,   121,   122,   163,
     123,   124,   125,   126,   127,   128,   129,   130,   296,   114,
      67,   174,   131,   132,   261,   170,   211,   213,    77,   214,
     155,    24,   175,   176,   177,    84,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     286,   156,   272,   273,    61,     4,   157,   158,   159,   224,
      92,   208,   209,    -2,    24,    96,     4,   212,    21,   108,
     287,    62,   245,   246,   219,    10,    64,     5,   225,     6,
     111,    65,   139,     7,     8,     9,    10,   137,   220,    66,
     173,   142,   143,   247,    11,    16,    59,    18,    12,   -28,
     227,   145,   167,    13,    14,    15,    16,    17,    18,    19,
      20,   168,   171,   193,    87,   194,   248,     4,    22,   226,
      19,    20,    24,    88,   192,    61,   196,    21,     5,    22,
       6,    23,    89,    24,     7,     8,     9,    10,   255,   256,
     228,   231,    62,    63,   234,    11,   251,    64,   267,    12,
     257,   268,    65,   262,    13,    14,    15,    16,    17,    18,
      66,   271,    67,   269,   263,   270,   277,   280,   281,   274,
       4,    19,    20,   284,   289,     4,   285,   293,    21,   237,
      22,     5,    23,     6,    24,   297,     4,     7,     8,     9,
      10,   294,   286,   299,   210,    10,   207,     5,    11,     6,
     298,   264,    12,     7,     8,     9,    10,    13,   288,    68,
      16,    17,    18,   104,    11,    16,    59,    18,    12,   240,
     101,   258,    97,    13,    19,    20,    16,    17,    18,    19,
      20,    21,   172,    22,   105,    23,   115,    24,    22,   116,
      19,    20,     0,     0,     0,     0,    61,    21,   241,    22,
     117,    23,     0,    24,   199,   200,   118,     4,     0,   201,
     119,   202,     0,    62,   245,   246,   120,     0,    64,     0,
       6,     0,   115,    65,     0,     0,     0,    10,     0,   121,
     122,    66,   123,   124,   125,   126,   127,   128,   129,   130,
       0,     0,   118,   115,   131,   132,   116,    16,    59,    18,
       0,     0,   120,   169,     0,     0,     0,   117,   248,     0,
       0,    19,    20,   118,     0,     0,     0,   119,     0,     0,
      22,     0,    23,   120,   129,   130,     0,     0,     0,     0,
     131,   132,     0,     0,     0,   115,   121,   122,   116,   123,
     124,   125,   126,   127,   128,   129,   130,   -34,     0,   117,
       0,   131,   132,    87,     0,   118,     0,   144,     0,   119,
       0,   -34,    88,     0,     0,   120,     0,     0,     0,     0,
       0,    89,     0,   -34,     0,     0,     0,   115,   121,   122,
     116,   123,   124,   125,   126,   127,   128,   129,   130,     0,
       0,   117,     4,   131,   132,     0,     0,   118,     0,   198,
       0,   119,     0,     0,     0,     0,     0,   120,     0,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
     121,   122,     0,   123,   124,   125,   126,   127,   128,   129,
     130,     0,    16,    59,    18,   131,   132,   115,     0,     0,
     116,   254,     0,     0,     0,     0,    19,    20,   115,     0,
       0,   117,     0,   161,     0,    22,     0,   118,     0,     0,
       0,   119,   117,     0,     0,     0,     0,   120,   118,     0,
       0,     0,   119,     0,     0,     0,     0,     0,   120,   115,
     121,   122,   116,   123,   124,   125,   126,   127,   128,   129,
     130,   115,     0,   117,     0,   131,   132,     0,    21,   118,
     129,   130,     0,   119,     0,   117,   131,   132,     0,   120,
       0,   118,     0,     0,     0,   119,     0,     0,     0,     0,
       0,   120,   121,   122,   222,   123,   124,   125,   126,   127,
     128,   129,   130,   115,     0,     0,   116,   131,   132,   223,
     126,   127,   128,   129,   130,     0,     0,   117,     0,   131,
     132,     0,     0,   118,     0,     0,     0,   119,     0,     0,
       0,     0,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   121,   122,   116,   123,
     124,   125,   126,   127,   128,   129,   130,   115,     0,   117,
       0,   131,   132,   279,     0,   118,     0,     0,     0,   119,
       0,   117,     0,     0,     0,   120,     0,   118,     0,     0,
       0,   119,     0,     0,     0,     0,     0,   120,   121,   122,
     221,   123,   124,   125,   126,   127,   128,   129,   130,   115,
       0,   115,   116,   131,   132,   125,   126,   127,   128,   129,
     130,     0,     0,   117,     0,   131,   132,     0,     0,   118,
       0,   118,     0,   119,     0,   119,     0,     0,     0,   120,
       0,   120,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   121,   122,   116,   123,   124,   125,   126,   127,
     128,   129,   130,   129,   130,   117,   115,   131,   132,   131,
     132,   118,     0,     0,     0,   119,     0,     0,     0,     0,
     117,   120,     0,     0,     0,     0,   118,     0,     0,     0,
     119,   115,     0,     0,     0,   122,   120,   123,   124,   125,
     126,   127,   128,   129,   130,   117,   115,     0,     0,   131,
     132,   118,     0,     0,     0,   119,   127,   128,   129,   130,
     117,   120,     0,     0,   131,   132,   118,     0,     0,     0,
     119,     0,     0,     0,     0,   122,   120,   123,   124,   125,
     126,   127,   128,   129,   130,     0,   115,     0,     0,   131,
     132,     0,     0,   124,   125,   126,   127,   128,   129,   130,
     117,     0,     0,     0,   131,   132,   118,     0,     0,     0,
     119,     0,     0,     0,     0,     0,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,   129,   130,
       0,     0,     0,     0,   131,   132
};

static const yytype_int16 yycheck[] =
{
       6,     4,    42,   112,    23,     8,     6,     3,    14,    15,
      13,   217,    21,    30,    46,    32,    19,    20,    23,    22,
      37,    38,   214,    39,    40,    46,    44,    23,    61,    32,
      46,    64,    48,   239,   240,    67,     0,    54,    55,    42,
      43,    66,    61,    62,     3,    70,    67,     6,    54,     4,
      55,    56,    70,    48,    57,    64,    61,    62,    17,    55,
      56,    61,    68,    18,    23,    61,    62,    66,    27,    72,
      73,    66,   112,    68,    33,    30,   268,    46,    95,    96,
      97,    43,    66,    45,    68,    64,    44,    46,    47,    92,
      49,    50,    51,    52,    53,    54,    55,    56,    67,   105,
      44,   210,    61,    62,    66,   108,    64,    64,    69,    66,
      11,    70,   115,   116,   117,    44,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
      43,    32,    43,    44,     7,     3,    37,    38,    39,    46,
       6,   147,   148,     0,    70,    44,     3,   153,    64,    70,
      63,    24,    25,    26,   170,    23,    29,    14,    65,    16,
      40,    34,    45,    20,    21,    22,    23,    61,   171,    42,
     210,    43,    43,    46,    31,    43,    44,    45,    35,    66,
     197,    66,    15,    40,    41,    42,    43,    44,    45,    57,
      58,    70,    66,    44,    10,    44,    69,     3,    66,    44,
      57,    58,    70,    19,    67,     7,     5,    64,    14,    66,
      16,    68,    28,    70,    20,    21,    22,    23,   221,   222,
      13,     6,    24,    25,     6,    31,    43,    29,    67,    35,
      44,    46,    34,    45,    40,    41,    42,    43,    44,    45,
      42,   247,    44,    69,    45,    69,    46,    45,    66,    62,
       3,    57,    58,    43,    65,     3,    44,    64,    64,    65,
      66,    14,    68,    16,    70,    62,     3,    20,    21,    22,
      23,    63,    43,   295,   152,    23,   146,    14,    31,    16,
     294,   235,    35,    20,    21,    22,    23,    40,   277,     6,
      43,    44,    45,    42,    31,    43,    44,    45,    35,   209,
      40,   229,    35,    40,    57,    58,    43,    44,    45,    57,
      58,    64,    65,    66,    42,    68,     3,    70,    66,     6,
      57,    58,    -1,    -1,    -1,    -1,     7,    64,    65,    66,
      17,    68,    -1,    70,    37,    38,    23,     3,    -1,    42,
      27,    44,    -1,    24,    25,    26,    33,    -1,    29,    -1,
      16,    -1,     3,    34,    -1,    -1,    -1,    23,    -1,    46,
      47,    42,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    23,     3,    61,    62,     6,    43,    44,    45,
      -1,    -1,    33,    70,    -1,    -1,    -1,    17,    69,    -1,
      -1,    57,    58,    23,    -1,    -1,    -1,    27,    -1,    -1,
      66,    -1,    68,    33,    55,    56,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,     3,    46,    47,     6,    49,
      50,    51,    52,    53,    54,    55,    56,     4,    -1,    17,
      -1,    61,    62,    10,    -1,    23,    -1,    67,    -1,    27,
      -1,    18,    19,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    -1,    -1,    -1,     3,    46,    47,
       6,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    17,     3,    61,    62,    -1,    -1,    23,    -1,    67,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    43,    44,    45,    61,    62,     3,    -1,    -1,
       6,    67,    -1,    -1,    -1,    -1,    57,    58,     3,    -1,
      -1,    17,    -1,    64,    -1,    66,    -1,    23,    -1,    -1,
      -1,    27,    17,    -1,    -1,    -1,    -1,    33,    23,    -1,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    33,     3,
      46,    47,     6,    49,    50,    51,    52,    53,    54,    55,
      56,     3,    -1,    17,    -1,    61,    62,    -1,    64,    23,
      55,    56,    -1,    27,    -1,    17,    61,    62,    -1,    33,
      -1,    23,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    33,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     3,    -1,    -1,     6,    61,    62,    63,
      52,    53,    54,    55,    56,    -1,    -1,    17,    -1,    61,
      62,    -1,    -1,    23,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    46,    47,     6,    49,
      50,    51,    52,    53,    54,    55,    56,     3,    -1,    17,
      -1,    61,    62,    63,    -1,    23,    -1,    -1,    -1,    27,
      -1,    17,    -1,    -1,    -1,    33,    -1,    23,    -1,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    33,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     3,
      -1,     3,     6,    61,    62,    51,    52,    53,    54,    55,
      56,    -1,    -1,    17,    -1,    61,    62,    -1,    -1,    23,
      -1,    23,    -1,    27,    -1,    27,    -1,    -1,    -1,    33,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    46,    47,     6,    49,    50,    51,    52,    53,
      54,    55,    56,    55,    56,    17,     3,    61,    62,    61,
      62,    23,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      17,    33,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,     3,    -1,    -1,    -1,    47,    33,    49,    50,    51,
      52,    53,    54,    55,    56,    17,     3,    -1,    -1,    61,
      62,    23,    -1,    -1,    -1,    27,    53,    54,    55,    56,
      17,    33,    -1,    -1,    61,    62,    23,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    47,    33,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,     3,    -1,    -1,    61,
      62,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      17,    -1,    -1,    -1,    61,    62,    23,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    61,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    72,    73,     0,     3,    14,    16,    20,    21,    22,
      23,    31,    35,    40,    41,    42,    43,    44,    45,    57,
      58,    64,    66,    68,    70,    74,    76,    81,    86,    94,
     106,   108,   109,   110,   111,   112,   113,   116,   118,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   136,   137,   138,   140,   142,   145,   146,    44,
     140,     7,    24,    25,    29,    34,    42,    44,   107,   143,
     140,   114,   141,    66,   140,   143,   143,    69,    48,    66,
      68,   140,   140,   140,    44,    82,    64,    10,    19,    28,
      87,    95,     6,   111,   111,   140,    44,   146,   111,   111,
     136,   123,   136,    81,   106,   138,   140,   140,    70,   136,
     136,    40,    91,   111,   143,     3,     6,    17,    23,    27,
      33,    46,    47,    49,    50,    51,    52,    53,    54,    55,
      56,    61,    62,   111,   140,   147,   143,    61,    64,    45,
     140,   140,    43,    43,    67,    66,    75,   117,   119,     4,
      18,    30,    88,    89,    90,    11,    32,    37,    38,    39,
      93,    64,   103,   140,   111,   111,   111,    15,    70,    70,
     140,    66,    65,    81,   110,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,    67,    44,    44,   139,     5,   115,    67,    37,
      38,    42,    44,    77,    78,    79,    80,    73,   143,   143,
      91,    64,   143,    64,    66,    92,   143,   144,   104,   136,
     140,    48,    48,    63,    46,    65,    44,   111,    13,   134,
     135,     6,    46,    67,     6,    46,    67,    65,     6,   120,
     120,    65,    92,    97,    98,    25,    26,    46,    69,    96,
     107,    43,   101,   102,    67,   140,   140,    44,   135,    43,
      45,    66,    45,    45,    78,    96,    96,    67,    46,    69,
      69,   143,    43,    44,    62,    99,   100,    46,   105,    63,
      45,    66,    85,    92,    43,    44,    43,    63,   101,    65,
      83,    84,    96,    64,    63,    46,    67,    62,    99,    83
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    71,    72,    73,    73,    74,    74,    75,    74,    76,
      76,    76,    77,    77,    78,    78,    78,    78,    79,    79,
      79,    80,    80,    80,    81,    81,    81,    82,    82,    83,
      84,    84,    85,    85,    87,    86,    88,    88,    88,    89,
      89,    89,    90,    91,    91,    92,    93,    93,    93,    93,
      93,    95,    94,    94,    94,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    99,    99,   100,   100,   100,   101,
     102,   102,   104,   105,   103,   106,   106,   106,   107,   107,
     107,   107,   107,   107,   108,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   112,   114,   113,   115,   115,
     117,   116,   119,   118,   120,   120,   121,   122,   123,   123,
     123,   124,   125,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   134,   135,   136,   137,   138,   139,   139,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   141,   140,   140,   140,   140,   140,
     142,   142,   143,   143,   144,   144,   145,   146,   147,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     5,     2,
       2,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       1,     0,     1,     3,     0,     5,     2,     0,     1,     1,
       1,     3,     0,     3,     0,     5,     6,     2,     2,     1,
       1,     1,     2,     0,     2,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     2,     1,     3,     2,     3,     2,
       0,     1,     1,     3,     3,     4,     0,     1,     2,     1,
       1,     3,     0,     0,     5,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     3,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     1,     1,     0,     5,     2,     0,
       0,     6,     0,     6,     0,     1,     2,     3,     2,     2,
       2,     2,     3,     3,     2,     4,     2,     2,     1,     2,
       5,     5,     1,     2,     1,     3,     1,     5,     1,     3,
       1,     3,     3,     4,     6,     3,     3,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     0,     3,     2,     5,     1,     1,
       1,     3,     1,     3,     1,     3,     2,     3,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 7:
#line 104 "src/fe/parser.ypp"
                  { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(nullptr); }
#line 1743 "src/fe/parser.cpp"
    break;

  case 8:
#line 104 "src/fe/parser.ypp"
                                                                                                         { Emitter::EndBlock(); }
#line 1749 "src/fe/parser.cpp"
    break;

  case 9:
#line 106 "src/fe/parser.ypp"
                         { (yyval.expr) = (yyvsp[0].expr); }
#line 1755 "src/fe/parser.cpp"
    break;

  case 10:
#line 106 "src/fe/parser.ypp"
                                                     { (yyval.expr) = (yyvsp[0].expr); }
#line 1761 "src/fe/parser.cpp"
    break;

  case 11:
#line 106 "src/fe/parser.ypp"
                                                                             { (yyval.expr) = nullptr; }
#line 1767 "src/fe/parser.cpp"
    break;

  case 12:
#line 108 "src/fe/parser.ypp"
                                         {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1775 "src/fe/parser.cpp"
    break;

  case 13:
#line 110 "src/fe/parser.ypp"
                              {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1784 "src/fe/parser.cpp"
    break;

  case 14:
#line 115 "src/fe/parser.ypp"
                                    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1792 "src/fe/parser.cpp"
    break;

  case 15:
#line 117 "src/fe/parser.ypp"
                                                                          {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1800 "src/fe/parser.cpp"
    break;

  case 16:
#line 119 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1808 "src/fe/parser.cpp"
    break;

  case 17:
#line 121 "src/fe/parser.ypp"
                          {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1816 "src/fe/parser.cpp"
    break;

  case 18:
#line 125 "src/fe/parser.ypp"
                         { (yyval.sym) = sym_input; }
#line 1822 "src/fe/parser.cpp"
    break;

  case 19:
#line 125 "src/fe/parser.ypp"
                                                        { (yyval.sym) = sym_output; }
#line 1828 "src/fe/parser.cpp"
    break;

  case 20:
#line 125 "src/fe/parser.ypp"
                                                                                        { (yyval.sym) = sym_module; }
#line 1834 "src/fe/parser.cpp"
    break;

  case 21:
#line 127 "src/fe/parser.ypp"
                        {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1842 "src/fe/parser.cpp"
    break;

  case 22:
#line 129 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1850 "src/fe/parser.cpp"
    break;

  case 23:
#line 131 "src/fe/parser.ypp"
                                               {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1858 "src/fe/parser.cpp"
    break;

  case 24:
#line 135 "src/fe/parser.ypp"
                      {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1866 "src/fe/parser.cpp"
    break;

  case 25:
#line 137 "src/fe/parser.ypp"
                                                   {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1874 "src/fe/parser.cpp"
    break;

  case 26:
#line 139 "src/fe/parser.ypp"
            {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1882 "src/fe/parser.cpp"
    break;

  case 27:
#line 143 "src/fe/parser.ypp"
               {
  (yyval.sym) = sym_lookup("");
}
#line 1890 "src/fe/parser.cpp"
    break;

  case 28:
#line 145 "src/fe/parser.ypp"
        {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1898 "src/fe/parser.cpp"
    break;

  case 29:
#line 149 "src/fe/parser.ypp"
                         {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1906 "src/fe/parser.cpp"
    break;

  case 30:
#line 153 "src/fe/parser.ypp"
                               {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1914 "src/fe/parser.cpp"
    break;

  case 31:
#line 155 "src/fe/parser.ypp"
                                     {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1922 "src/fe/parser.cpp"
    break;

  case 32:
#line 159 "src/fe/parser.ypp"
              {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1930 "src/fe/parser.cpp"
    break;

  case 33:
#line 161 "src/fe/parser.ypp"
                             {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1938 "src/fe/parser.cpp"
    break;

  case 34:
#line 165 "src/fe/parser.ypp"
                                {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1944 "src/fe/parser.cpp"
    break;

  case 35:
#line 165 "src/fe/parser.ypp"
                                                                                                          {
  Emitter::EndFunction();
}
#line 1952 "src/fe/parser.cpp"
    break;

  case 36:
#line 169 "src/fe/parser.ypp"
                                                                 {
  Emitter::SetCurrentFunctionParams((yyvsp[-3].var_decl_set), (yyvsp[-1].var_decl_set));
}
#line 1960 "src/fe/parser.cpp"
    break;

  case 37:
#line 171 "src/fe/parser.ypp"
                       {
  Emitter::SetCurrentFunctionParams(nullptr, nullptr);
}
#line 1968 "src/fe/parser.cpp"
    break;

  case 38:
#line 173 "src/fe/parser.ypp"
                     {
  Emitter::BeginFunctionDecl((yyvsp[-1].id), nullptr);
  Emitter::SetCurrentFunctionParams(nullptr, nullptr);
}
#line 1977 "src/fe/parser.cpp"
    break;

  case 39:
#line 178 "src/fe/parser.ypp"
                      { (yyval.id) = K_FUNC; }
#line 1983 "src/fe/parser.cpp"
    break;

  case 40:
#line 178 "src/fe/parser.ypp"
                                                   { (yyval.id) = K_PROCESS; }
#line 1989 "src/fe/parser.cpp"
    break;

  case 41:
#line 178 "src/fe/parser.ypp"
                                                                                  { (yyval.id) = K_ALWAYS; }
#line 1995 "src/fe/parser.cpp"
    break;

  case 42:
#line 180 "src/fe/parser.ypp"
                                  {
  Emitter::BeginFunctionDecl((yyvsp[-1].id), (yyvsp[0].expr));
}
#line 2003 "src/fe/parser.cpp"
    break;

  case 43:
#line 184 "src/fe/parser.ypp"
            {
}
#line 2010 "src/fe/parser.cpp"
    break;

  case 44:
#line 185 "src/fe/parser.ypp"
                   {
}
#line 2017 "src/fe/parser.cpp"
    break;

  case 45:
#line 188 "src/fe/parser.ypp"
                                                        {
  VarDeclSet *vds = nullptr;
  for (Expr *var : (yyvsp[-2].expr_set)->exprs) {
    VarDecl *vd = Builder::BuildVarDecl(var,
					(yyvsp[-1].width_spec).is_primitive, (yyvsp[-1].width_spec).name,
					(yyvsp[-1].width_spec).width);
    Builder::SetArrayShape(vd, (yyvsp[0].shape));
    vds = Builder::VarDeclList(vds, vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2033 "src/fe/parser.cpp"
    break;

  case 46:
#line 200 "src/fe/parser.ypp"
                      {(yyval.id) = K_VAR;}
#line 2039 "src/fe/parser.cpp"
    break;

  case 47:
#line 200 "src/fe/parser.ypp"
                                               {(yyval.id) = K_SHARED;}
#line 2045 "src/fe/parser.cpp"
    break;

  case 48:
#line 200 "src/fe/parser.ypp"
                                                                          {(yyval.id) = K_CONST;}
#line 2051 "src/fe/parser.cpp"
    break;

  case 49:
#line 200 "src/fe/parser.ypp"
                                                                                                    {(yyval.id) = K_INPUT;}
#line 2057 "src/fe/parser.cpp"
    break;

  case 50:
#line 200 "src/fe/parser.ypp"
                                                                                                                               {(yyval.id) = K_OUTPUT;}
#line 2063 "src/fe/parser.cpp"
    break;

  case 51:
#line 202 "src/fe/parser.ypp"
                               {ScannerInterface::InSemiColonStatement();}
#line 2069 "src/fe/parser.cpp"
    break;

  case 52:
#line 202 "src/fe/parser.ypp"
                                                                                                       {
  bool is_input = ((yyvsp[-1].id) == K_INPUT);
  bool is_output = ((yyvsp[-1].id) == K_OUTPUT);
  bool is_io = (is_input || is_output);
  bool is_shared = ((yyvsp[-1].id) == K_SHARED) || ((yyvsp[-1].id) == K_CONST) || is_io;
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
    if (is_shared) {
      vd->SetIsShared(true);
    }
    vd->SetIsConst((yyvsp[-1].id) == K_CONST);
    vd->SetIsIO(is_io, is_output);
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2089 "src/fe/parser.cpp"
    break;

  case 53:
#line 216 "src/fe/parser.ypp"
                         {
}
#line 2096 "src/fe/parser.cpp"
    break;

  case 54:
#line 217 "src/fe/parser.ypp"
                  {
}
#line 2103 "src/fe/parser.cpp"
    break;

  case 55:
#line 220 "src/fe/parser.ypp"
                       {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2111 "src/fe/parser.cpp"
    break;

  case 56:
#line 222 "src/fe/parser.ypp"
                   {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2119 "src/fe/parser.cpp"
    break;

  case 57:
#line 224 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2127 "src/fe/parser.cpp"
    break;

  case 58:
#line 226 "src/fe/parser.ypp"
                   {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2135 "src/fe/parser.cpp"
    break;

  case 59:
#line 228 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2143 "src/fe/parser.cpp"
    break;

  case 60:
#line 232 "src/fe/parser.ypp"
           {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2152 "src/fe/parser.cpp"
    break;

  case 61:
#line 235 "src/fe/parser.ypp"
                  {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2160 "src/fe/parser.cpp"
    break;

  case 62:
#line 239 "src/fe/parser.ypp"
                              {
  VarDeclSet *vds = nullptr;
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList(vds, vd);
  }
  if ((yyvsp[0].var_decl_set)->decls[0]->GetArrayShape() != nullptr) {
    yyerror("Array can't be passed to a method");
    YYABORT;
  }
  (yyval.var_decl_set) = vds;
}
#line 2176 "src/fe/parser.cpp"
    break;

  case 63:
#line 249 "src/fe/parser.ypp"
                                    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2188 "src/fe/parser.cpp"
    break;

  case 64:
#line 257 "src/fe/parser.ypp"
                         {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2197 "src/fe/parser.cpp"
    break;

  case 65:
#line 260 "src/fe/parser.ypp"
                           {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2206 "src/fe/parser.cpp"
    break;

  case 66:
#line 265 "src/fe/parser.ypp"
                      {
  (yyval.shape) = nullptr;
}
#line 2214 "src/fe/parser.cpp"
    break;

  case 67:
#line 267 "src/fe/parser.ypp"
               {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2222 "src/fe/parser.cpp"
    break;

  case 68:
#line 269 "src/fe/parser.ypp"
            {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2232 "src/fe/parser.cpp"
    break;

  case 69:
#line 275 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[0].num);
}
#line 2240 "src/fe/parser.cpp"
    break;

  case 70:
#line 279 "src/fe/parser.ypp"
                           {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2250 "src/fe/parser.cpp"
    break;

  case 71:
#line 283 "src/fe/parser.ypp"
                                 {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2259 "src/fe/parser.cpp"
    break;

  case 72:
#line 288 "src/fe/parser.ypp"
                        { ScannerInterface::InArrayElmDecl(); }
#line 2265 "src/fe/parser.cpp"
    break;

  case 73:
#line 288 "src/fe/parser.ypp"
                                                                               {ScannerInterface::EndArrayElmDecl(); }
#line 2271 "src/fe/parser.cpp"
    break;

  case 74:
#line 288 "src/fe/parser.ypp"
                                                                                                                           {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2279 "src/fe/parser.cpp"
    break;

  case 75:
#line 292 "src/fe/parser.ypp"
                         {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2288 "src/fe/parser.cpp"
    break;

  case 76:
#line 295 "src/fe/parser.ypp"
                           {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2302 "src/fe/parser.cpp"
    break;

  case 77:
#line 303 "src/fe/parser.ypp"
                                        {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  if ((yyvsp[-2].var_decl_set)->decls[0]->GetArrayShape() == nullptr) {
    yyerror("Array initializer to non array");
    YYABORT;
  }
  Builder::SetArrayInitializer((yyvsp[-2].var_decl_set)->decls[0], (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2320 "src/fe/parser.cpp"
    break;

  case 78:
#line 317 "src/fe/parser.ypp"
                   {
  (yyval.sym) = sym_uint;
}
#line 2328 "src/fe/parser.cpp"
    break;

  case 79:
#line 319 "src/fe/parser.ypp"
          {
  (yyval.sym) = sym_uint;
}
#line 2336 "src/fe/parser.cpp"
    break;

  case 80:
#line 321 "src/fe/parser.ypp"
           {
  (yyval.sym) = sym_bool;
}
#line 2344 "src/fe/parser.cpp"
    break;

  case 81:
#line 323 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_object;
}
#line 2352 "src/fe/parser.cpp"
    break;

  case 82:
#line 325 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_module;
}
#line 2360 "src/fe/parser.cpp"
    break;

  case 83:
#line 327 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_string;
}
#line 2368 "src/fe/parser.cpp"
    break;

  case 84:
#line 332 "src/fe/parser.ypp"
                {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2376 "src/fe/parser.cpp"
    break;

  case 85:
#line 336 "src/fe/parser.ypp"
                  {
  ScannerInterface::InSemiColonStatement();
}
#line 2384 "src/fe/parser.cpp"
    break;

  case 86:
#line 340 "src/fe/parser.ypp"
           {
  /* empty stmt */
}
#line 2392 "src/fe/parser.cpp"
    break;

  case 87:
#line 342 "src/fe/parser.ypp"
             {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2400 "src/fe/parser.cpp"
    break;

  case 88:
#line 344 "src/fe/parser.ypp"
                  {
}
#line 2407 "src/fe/parser.cpp"
    break;

  case 89:
#line 345 "src/fe/parser.ypp"
                          {
}
#line 2414 "src/fe/parser.cpp"
    break;

  case 90:
#line 346 "src/fe/parser.ypp"
                      {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2422 "src/fe/parser.cpp"
    break;

  case 91:
#line 348 "src/fe/parser.ypp"
                    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2430 "src/fe/parser.cpp"
    break;

  case 92:
#line 350 "src/fe/parser.ypp"
               {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2438 "src/fe/parser.cpp"
    break;

  case 93:
#line 352 "src/fe/parser.ypp"
          {
}
#line 2445 "src/fe/parser.cpp"
    break;

  case 94:
#line 353 "src/fe/parser.ypp"
            {
}
#line 2452 "src/fe/parser.cpp"
    break;

  case 95:
#line 354 "src/fe/parser.ypp"
             {
}
#line 2459 "src/fe/parser.cpp"
    break;

  case 96:
#line 355 "src/fe/parser.ypp"
               {
}
#line 2466 "src/fe/parser.cpp"
    break;

  case 97:
#line 356 "src/fe/parser.ypp"
                  {
}
#line 2473 "src/fe/parser.cpp"
    break;

  case 98:
#line 357 "src/fe/parser.ypp"
                {
}
#line 2480 "src/fe/parser.cpp"
    break;

  case 99:
#line 358 "src/fe/parser.ypp"
                      {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2488 "src/fe/parser.cpp"
    break;

  case 101:
#line 361 "src/fe/parser.ypp"
                {
}
#line 2495 "src/fe/parser.cpp"
    break;

  case 102:
#line 362 "src/fe/parser.ypp"
                          {
}
#line 2502 "src/fe/parser.cpp"
    break;

  case 103:
#line 363 "src/fe/parser.ypp"
                          {
}
#line 2509 "src/fe/parser.cpp"
    break;

  case 104:
#line 367 "src/fe/parser.ypp"
          {
  ScannerInterface::EndSemiColonStatement();
}
#line 2517 "src/fe/parser.cpp"
    break;

  case 105:
#line 371 "src/fe/parser.ypp"
                   {
  ScannerInterface::InSemiColonStatement();
}
#line 2525 "src/fe/parser.cpp"
    break;

  case 106:
#line 375 "src/fe/parser.ypp"
                       {ScannerInterface::InSemiColonStatement();}
#line 2531 "src/fe/parser.cpp"
    break;

  case 107:
#line 375 "src/fe/parser.ypp"
                                                                                                {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2539 "src/fe/parser.cpp"
    break;

  case 108:
#line 379 "src/fe/parser.ypp"
                                {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2547 "src/fe/parser.cpp"
    break;

  case 109:
#line 381 "src/fe/parser.ypp"
    {
  (yyval.sym) = sym_null;
}
#line 2555 "src/fe/parser.cpp"
    break;

  case 110:
#line 385 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2561 "src/fe/parser.cpp"
    break;

  case 111:
#line 385 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2569 "src/fe/parser.cpp"
    break;

  case 112:
#line 389 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2575 "src/fe/parser.cpp"
    break;

  case 113:
#line 389 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2583 "src/fe/parser.cpp"
    break;

  case 114:
#line 393 "src/fe/parser.ypp"
                  {
}
#line 2590 "src/fe/parser.cpp"
    break;

  case 115:
#line 394 "src/fe/parser.ypp"
             {
  // Maybe remove this syntax later.
}
#line 2598 "src/fe/parser.cpp"
    break;

  case 116:
#line 398 "src/fe/parser.ypp"
                         {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2607 "src/fe/parser.cpp"
    break;

  case 117:
#line 403 "src/fe/parser.ypp"
                                         {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2617 "src/fe/parser.cpp"
    break;

  case 118:
#line 409 "src/fe/parser.ypp"
                             {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2627 "src/fe/parser.cpp"
    break;

  case 119:
#line 413 "src/fe/parser.ypp"
                       {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2636 "src/fe/parser.cpp"
    break;

  case 120:
#line 416 "src/fe/parser.ypp"
                         {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2645 "src/fe/parser.cpp"
    break;

  case 121:
#line 421 "src/fe/parser.ypp"
                                     {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2653 "src/fe/parser.cpp"
    break;

  case 122:
#line 425 "src/fe/parser.ypp"
                                  {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2661 "src/fe/parser.cpp"
    break;

  case 123:
#line 427 "src/fe/parser.ypp"
                               {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2669 "src/fe/parser.cpp"
    break;

  case 124:
#line 431 "src/fe/parser.ypp"
                                   {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2678 "src/fe/parser.cpp"
    break;

  case 125:
#line 436 "src/fe/parser.ypp"
                                        {
  // join:
  // cond_expr
  // if (cond_expr)
  //  t:
  //  block
  //  repeat_expr
  // goto join:
  //  f:
  Emitter::EmitExprStmt((yyvsp[-1].expr));
  Emitter::EmitGoto((yyvsp[-3].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-3].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2697 "src/fe/parser.cpp"
    break;

  case 126:
#line 451 "src/fe/parser.ypp"
                               {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2710 "src/fe/parser.cpp"
    break;

  case 127:
#line 460 "src/fe/parser.ypp"
                                   {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2720 "src/fe/parser.cpp"
    break;

  case 128:
#line 466 "src/fe/parser.ypp"
                     {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2731 "src/fe/parser.cpp"
    break;

  case 129:
#line 473 "src/fe/parser.ypp"
                                    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2739 "src/fe/parser.cpp"
    break;

  case 130:
#line 477 "src/fe/parser.ypp"
                                                   {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2751 "src/fe/parser.cpp"
    break;

  case 131:
#line 485 "src/fe/parser.ypp"
                                               {
}
#line 2758 "src/fe/parser.cpp"
    break;

  case 132:
#line 488 "src/fe/parser.ypp"
                  {
}
#line 2765 "src/fe/parser.cpp"
    break;

  case 133:
#line 489 "src/fe/parser.ypp"
                    {
}
#line 2772 "src/fe/parser.cpp"
    break;

  case 134:
#line 492 "src/fe/parser.ypp"
                 {
}
#line 2779 "src/fe/parser.cpp"
    break;

  case 135:
#line 495 "src/fe/parser.ypp"
                                 {
  Emitter::EndBlock();
}
#line 2787 "src/fe/parser.cpp"
    break;

  case 136:
#line 499 "src/fe/parser.ypp"
                 {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2796 "src/fe/parser.cpp"
    break;

  case 137:
#line 504 "src/fe/parser.ypp"
                                              {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2804 "src/fe/parser.cpp"
    break;

  case 138:
#line 508 "src/fe/parser.ypp"
                     {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2812 "src/fe/parser.cpp"
    break;

  case 139:
#line 510 "src/fe/parser.ypp"
                           {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2820 "src/fe/parser.cpp"
    break;

  case 140:
#line 514 "src/fe/parser.ypp"
           {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2829 "src/fe/parser.cpp"
    break;

  case 141:
#line 517 "src/fe/parser.ypp"
                {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2842 "src/fe/parser.cpp"
    break;

  case 142:
#line 524 "src/fe/parser.ypp"
                 {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2850 "src/fe/parser.cpp"
    break;

  case 143:
#line 526 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2858 "src/fe/parser.cpp"
    break;

  case 144:
#line 528 "src/fe/parser.ypp"
                               {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2866 "src/fe/parser.cpp"
    break;

  case 145:
#line 530 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2874 "src/fe/parser.cpp"
    break;

  case 146:
#line 532 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2882 "src/fe/parser.cpp"
    break;

  case 147:
#line 534 "src/fe/parser.ypp"
            {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2890 "src/fe/parser.cpp"
    break;

  case 148:
#line 536 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2898 "src/fe/parser.cpp"
    break;

  case 149:
#line 538 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2906 "src/fe/parser.cpp"
    break;

  case 150:
#line 540 "src/fe/parser.ypp"
                        {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2914 "src/fe/parser.cpp"
    break;

  case 151:
#line 542 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2922 "src/fe/parser.cpp"
    break;

  case 152:
#line 544 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2930 "src/fe/parser.cpp"
    break;

  case 153:
#line 546 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2938 "src/fe/parser.cpp"
    break;

  case 154:
#line 548 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2946 "src/fe/parser.cpp"
    break;

  case 155:
#line 550 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2954 "src/fe/parser.cpp"
    break;

  case 156:
#line 552 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2962 "src/fe/parser.cpp"
    break;

  case 157:
#line 554 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2970 "src/fe/parser.cpp"
    break;

  case 158:
#line 556 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2978 "src/fe/parser.cpp"
    break;

  case 159:
#line 558 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2986 "src/fe/parser.cpp"
    break;

  case 160:
#line 560 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2994 "src/fe/parser.cpp"
    break;

  case 161:
#line 562 "src/fe/parser.ypp"
                         {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 3002 "src/fe/parser.cpp"
    break;

  case 162:
#line 564 "src/fe/parser.ypp"
                          {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 3010 "src/fe/parser.cpp"
    break;

  case 163:
#line 566 "src/fe/parser.ypp"
                   {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 3018 "src/fe/parser.cpp"
    break;

  case 164:
#line 568 "src/fe/parser.ypp"
              {ScannerInterface::InSemiColonStatement();}
#line 3024 "src/fe/parser.cpp"
    break;

  case 165:
#line 568 "src/fe/parser.ypp"
                                                                {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-2].sub_op), false);
}
#line 3032 "src/fe/parser.cpp"
    break;

  case 166:
#line 570 "src/fe/parser.ypp"
                              {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 3040 "src/fe/parser.cpp"
    break;

  case 167:
#line 572 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 3048 "src/fe/parser.cpp"
    break;

  case 168:
#line 574 "src/fe/parser.ypp"
        {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 3057 "src/fe/parser.cpp"
    break;

  case 169:
#line 577 "src/fe/parser.ypp"
             {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 3069 "src/fe/parser.cpp"
    break;

  case 170:
#line 585 "src/fe/parser.ypp"
               {
  (yyval.num) = (yyvsp[0].num);
}
#line 3077 "src/fe/parser.cpp"
    break;

  case 171:
#line 587 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 3086 "src/fe/parser.cpp"
    break;

  case 172:
#line 592 "src/fe/parser.ypp"
          {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 3094 "src/fe/parser.cpp"
    break;

  case 173:
#line 594 "src/fe/parser.ypp"
                {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 3102 "src/fe/parser.cpp"
    break;

  case 174:
#line 598 "src/fe/parser.ypp"
               {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 3110 "src/fe/parser.cpp"
    break;

  case 175:
#line 600 "src/fe/parser.ypp"
                     {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 3118 "src/fe/parser.cpp"
    break;

  case 176:
#line 604 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 3126 "src/fe/parser.cpp"
    break;

  case 177:
#line 608 "src/fe/parser.ypp"
                                     {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3135 "src/fe/parser.cpp"
    break;

  case 178:
#line 613 "src/fe/parser.ypp"
           {
  (yyval.expr) = nullptr;
}
#line 3143 "src/fe/parser.cpp"
    break;

  case 179:
#line 615 "src/fe/parser.ypp"
         {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3151 "src/fe/parser.cpp"
    break;


#line 3155 "src/fe/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 619 "src/fe/parser.ypp"

