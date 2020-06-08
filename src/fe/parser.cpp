/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "src/fe/parser.ypp" /* yacc.c:339  */

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


#line 84 "src/fe/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_SRC_FE_PARSER_H_INCLUDED
# define YY_YY_SRC_FE_PARSER_H_INCLUDED
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
    K_AS = 259,
    K_ASSIGN = 260,
    K_BOOL = 261,
    K_BREAK = 262,
    K_CASE = 263,
    K_CHANNEL = 264,
    K_CONST = 265,
    K_CONTINUE = 266,
    K_DEF = 267,
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
    K_LG_COMPARE = 280,
    K_MAILBOX = 281,
    K_OBJECT = 282,
    K_PROCESS = 283,
    K_RETURN = 284,
    K_SHARED = 285,
    K_SHIFT = 286,
    K_STRING = 287,
    K_SWITCH = 288,
    K_THREAD = 289,
    K_VAR = 290,
    K_WHILE = 291,
    K_WITH = 292,
    K_MODULE = 293,
    NUM = 294,
    SYM = 295,
    STR = 296,
    K_LOGIC_OR = 297,
    K_LOGIC_AND = 298,
    K_BIT_CONCAT = 299,
    SIGN = 300,
    ADDRESS = 301
  };
#endif
/* Tokens.  */
#define K_ADD_SUB 258
#define K_AS 259
#define K_ASSIGN 260
#define K_BOOL 261
#define K_BREAK 262
#define K_CASE 263
#define K_CHANNEL 264
#define K_CONST 265
#define K_CONTINUE 266
#define K_DEF 267
#define K_DEFAULT 268
#define K_DO 269
#define K_ELSE 270
#define K_ENUM 271
#define K_EQ_COMPARE 272
#define K_FUNC 273
#define K_FOR 274
#define K_GOTO 275
#define K_IF 276
#define K_IMPORT 277
#define K_INC_DEC 278
#define K_INT 279
#define K_LG_COMPARE 280
#define K_MAILBOX 281
#define K_OBJECT 282
#define K_PROCESS 283
#define K_RETURN 284
#define K_SHARED 285
#define K_SHIFT 286
#define K_STRING 287
#define K_SWITCH 288
#define K_THREAD 289
#define K_VAR 290
#define K_WHILE 291
#define K_WITH 292
#define K_MODULE 293
#define NUM 294
#define SYM 295
#define STR 296
#define K_LOGIC_OR 297
#define K_LOGIC_AND 298
#define K_BIT_CONCAT 299
#define SIGN 300
#define ADDRESS 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "src/fe/parser.ypp" /* yacc.c:355  */

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

#line 237 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 254 "src/fe/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   951

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  292

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    65,     2,     2,    50,     2,
      62,    63,    51,     2,    42,     2,    57,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    66,
       2,     2,     2,    43,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    48,    61,    54,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    45,    46,    47,
      55,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    99,    99,   101,   102,   103,   103,   105,
     105,   105,   107,   109,   114,   116,   118,   120,   124,   126,
     128,   132,   134,   136,   140,   142,   146,   150,   152,   156,
     158,   162,   162,   166,   173,   173,   173,   175,   179,   180,
     183,   195,   195,   197,   197,   206,   207,   210,   212,   214,
     218,   221,   225,   235,   243,   246,   251,   253,   255,   261,
     265,   269,   274,   274,   274,   278,   281,   289,   303,   305,
     307,   309,   311,   316,   320,   324,   326,   328,   329,   330,
     332,   334,   336,   337,   338,   339,   340,   341,   342,   344,
     345,   346,   347,   348,   352,   356,   360,   360,   364,   366,
     370,   370,   374,   374,   378,   378,   382,   383,   387,   392,
     398,   402,   405,   410,   414,   416,   420,   425,   440,   449,
     455,   462,   466,   474,   477,   478,   481,   484,   488,   493,
     497,   499,   503,   506,   513,   515,   517,   519,   521,   523,
     525,   527,   529,   531,   533,   535,   537,   539,   541,   543,
     545,   547,   549,   551,   553,   555,   557,   559,   561,   563,
     566,   574,   576,   581,   583,   587,   589,   593,   597,   602,
     604
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_ADD_SUB", "K_AS", "K_ASSIGN",
  "K_BOOL", "K_BREAK", "K_CASE", "K_CHANNEL", "K_CONST", "K_CONTINUE",
  "K_DEF", "K_DEFAULT", "K_DO", "K_ELSE", "K_ENUM", "K_EQ_COMPARE",
  "K_FUNC", "K_FOR", "K_GOTO", "K_IF", "K_IMPORT", "K_INC_DEC", "K_INT",
  "K_LG_COMPARE", "K_MAILBOX", "K_OBJECT", "K_PROCESS", "K_RETURN",
  "K_SHARED", "K_SHIFT", "K_STRING", "K_SWITCH", "K_THREAD", "K_VAR",
  "K_WHILE", "K_WITH", "K_MODULE", "NUM", "SYM", "STR", "','", "'?'",
  "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'", "'&'",
  "'*'", "'/'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'",
  "'{'", "'}'", "'('", "')'", "'@'", "'#'", "';'", "$accept", "input",
  "FUNC_DECL_OR_STMT_LIST", "FUNC_DECL_OR_STMT", "$@1", "MODULE_HEAD",
  "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE", "ANNOTATION_VALUE_LIST",
  "ANNOTATION_OR_EMPTY", "SYM_OR_EMPTY", "RETURN_TYPE", "RETURN_TYPE_LIST",
  "RETURN_SPEC", "FUNC_DECL", "$@2", "FUNC_DECL_HEAD", "FUNC_DECL_KW",
  "FUNC_DECL_NAME", "STMT_LIST", "VAR_DECL_TAIL", "VAR_OR_SHARED",
  "VAR_DECL", "$@3", "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST",
  "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "$@4", "$@5", "VAR_DECL_STMT", "TYPE_NAME", "LABEL",
  "RETURN", "STMT", "EOS", "GOTO_HEAD", "IMPORT_STMT", "$@6",
  "IMPORT_SPEC_OR_EMPTY", "THREAD_DECL_STMT", "$@7", "CHANNEL_DECL_STMT",
  "$@8", "MAILBOX_DECL_STMT", "$@9", "ASSIGN_OR_EMPTY", "IF_COND_PART",
  "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD", "FOR_HEAD_PART", "FOR_COND_PART",
  "FOR_STMT", "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD",
  "DO_WHILE_BODY", "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE",
  "BLOCK", "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "EXPR", "NUM_EXPR",
  "VAR", "VAR_LIST", "FUNCALL_HEAD", "FUNCALL", "ARG_LIST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    44,    63,    58,   297,   298,   299,   124,    94,
      38,    42,    47,    33,   126,   300,   301,    46,    91,    93,
     123,   125,    40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF -203

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-203)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -203,    36,   149,  -203,   258,  -203,   321,  -203,   258,  -203,
     258,  -203,   -18,  -203,   258,    17,    17,     2,    95,  -203,
     258,   258,  -203,   258,    37,  -203,  -203,    -1,   362,  -203,
      90,    44,  -203,    12,  -203,  -203,    74,  -203,    44,    44,
      44,    58,    10,  -203,    45,   258,    70,  -203,    58,  -203,
      58,   101,  -203,  -203,  -203,  -203,   -21,   327,  -203,   258,
    -203,   -35,    32,  -203,  -203,  -203,  -203,  -203,  -203,    17,
     104,   693,   110,    32,   258,    17,   693,   116,   116,   138,
    -203,  -203,   140,    32,    32,   413,   119,   122,  -203,  -203,
    -203,  -203,   130,    71,   152,  -203,  -203,   327,   -19,    44,
    -203,  -203,  -203,   180,  -203,  -203,  -203,   131,    17,   377,
     693,   258,  -203,  -203,   139,   253,  -203,   116,   258,   258,
     258,  -203,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,  -203,   693,   133,   116,
     158,   160,   200,   449,     1,  -203,  -203,  -203,   136,  -203,
      17,    17,  -203,  -203,  -203,   148,    17,    17,  -203,  -203,
      17,  -203,  -203,   693,  -203,  -203,  -203,  -203,  -203,  -203,
     521,   258,  -203,   134,  -203,   171,   729,   893,   590,    89,
     729,   657,   801,   620,   837,   852,   840,   890,    32,    32,
    -203,   557,  -203,  -203,  -203,    52,   170,    44,   206,   181,
     225,   226,    20,  -203,    30,   204,    19,    19,  -203,   105,
    -203,   169,   192,   116,    22,  -203,   196,  -203,   485,   258,
     258,  -203,   207,  -203,  -203,  -203,  -203,   206,  -203,   174,
    -203,   205,    94,   208,  -203,   136,  -203,  -203,  -203,    73,
      73,   302,  -203,   186,    17,    17,    64,   193,  -203,  -203,
    -203,   210,  -203,   765,   607,  -203,  -203,  -203,  -203,  -203,
     209,  -203,  -203,  -203,  -203,  -203,    73,  -203,  -203,   116,
    -203,  -203,   -26,  -203,  -203,   196,   194,  -203,  -203,  -203,
      33,  -203,   195,  -203,  -203,  -203,    73,  -203,   201,  -203,
     214,  -203
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    21,     1,     0,   120,     0,    95,     0,    96,
       0,    74,     0,   100,     0,     0,    11,   161,   132,   159,
       0,     0,   128,     0,    24,    94,     4,     0,    31,     5,
      65,     0,    89,     0,     6,    75,     0,    90,     0,     0,
       0,     0,     0,    83,    21,     0,     0,    84,     0,    85,
       0,     0,    86,    87,    82,    38,     0,     0,   160,   169,
     139,   132,   157,    69,    68,    70,    72,    71,   163,     0,
       0,   108,     0,   156,     0,     0,   118,     9,    10,     0,
      73,   167,     0,   140,   141,     0,    23,     0,     7,   102,
     113,   104,     0,     0,     0,    88,    81,     0,     0,     0,
      91,    92,    93,   110,   112,   111,    43,     0,     0,     0,
     116,     0,   119,   121,     0,    21,    77,    46,     0,     0,
       0,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,   170,     0,    45,
       0,     0,    99,     0,     0,   162,   133,   134,    18,     3,
       0,     0,    34,    35,    36,     0,     0,    50,    42,    41,
       0,    62,    67,    66,    80,    79,    78,   109,   115,   114,
       0,     0,   127,    43,    39,   142,   146,   148,   147,   145,
     137,     0,   153,   154,   149,   151,   152,   150,   143,   144,
     138,     0,   168,   164,   130,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,    21,   106,   106,    38,     0,
      52,     0,    51,   165,     0,    44,     0,   117,     0,     0,
       0,   135,     0,   129,    98,    97,   126,   123,   124,     0,
     101,     0,     0,     0,    17,     0,    22,     8,   107,     0,
       0,    21,    37,    29,     0,     0,     0,    56,    47,    59,
      60,    63,   122,   158,     0,   131,   125,    15,    16,    14,
       0,    13,    20,   103,   105,    32,     0,    33,    53,   166,
      48,    49,     0,    57,    40,     0,     0,   136,    12,    27,
       0,    26,     0,    58,    61,    64,     0,    30,    54,    28,
       0,    55
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,  -203,   111,  -203,  -203,  -203,  -203,    27,  -203,   -42,
    -203,   -23,  -203,  -203,  -203,  -203,  -203,  -203,  -203,    63,
    -156,  -203,  -203,  -203,  -202,  -203,  -203,   -11,  -203,     3,
    -203,  -203,  -203,  -203,   228,   273,  -203,  -203,  -107,   -17,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
      76,  -203,  -203,   238,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,    57,   -16,  -203,   241,  -203,
      -3,  -203,    -6,  -203,  -203,   -33,  -203
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   149,    27,   202,   203,   204,    28,
      87,   279,   280,   267,    29,    92,   155,   156,   157,   115,
     210,   160,    30,    93,   281,   211,   212,   273,   274,   250,
     251,   162,   216,   276,    31,   248,    32,    33,    34,    35,
      36,    37,    72,   197,    38,    75,    39,   150,    40,   151,
     239,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   227,   228,    54,    55,    56,   195,
      57,    58,   213,   214,    59,    60,   138
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    62,   106,    99,   215,    71,   199,    73,   174,    77,
      78,    76,   247,   282,    95,     4,    96,    83,    84,    68,
      85,   100,   101,   102,   238,   103,   105,    81,    63,    82,
      97,     8,   112,   283,   113,    10,     3,   263,   264,   116,
     136,   109,   110,    81,    74,    25,    64,    25,     4,    65,
     117,    17,    61,    19,    66,   121,   137,    68,   140,    88,
      67,     6,   233,   139,   245,    20,    21,    79,    10,   144,
      22,   143,   235,   173,    23,   286,   140,    86,    25,    63,
     164,   165,   166,   234,    17,    61,    19,   246,   268,   134,
     135,   163,   118,   236,   222,    94,   287,    64,    20,    21,
      65,   158,   117,   270,   271,    66,   159,    23,   170,    24,
      25,    67,   121,   223,    98,   175,   176,   177,    22,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   258,   174,   259,   111,   114,   246,    80,
     132,   133,   152,    89,   206,   207,   134,   135,   153,    -2,
     209,   142,     4,    90,   217,     4,   260,    81,   154,    82,
      91,   140,   140,     5,   141,     6,   230,   242,   218,     7,
       8,     9,    10,   140,   200,    10,   201,   145,    11,   146,
     225,   -25,    12,    13,   148,    14,    15,    16,    17,    18,
      19,    17,    61,    19,   121,   167,   192,   168,   193,   173,
     194,   171,    20,    21,   196,    20,    21,     4,   208,    22,
     224,    23,   161,    24,    23,    25,   253,   254,     5,   226,
       6,   229,   132,   133,     7,     8,     9,    10,   134,   135,
     231,   232,   243,    11,   244,   249,    81,    12,    13,   269,
      14,    15,    16,    17,    18,    19,   257,   255,   266,   261,
     278,   272,   275,   282,   288,   285,     4,    20,    21,   290,
     205,     4,   262,   289,    22,   237,    23,     5,    24,     6,
      25,   241,   107,     7,     8,     9,    10,   291,   284,    69,
     104,    10,    11,   240,   256,   108,    12,    13,     0,    14,
       0,     0,    17,    18,    19,     0,     0,    17,    61,    19,
       0,     0,     0,     0,     0,     4,    20,    21,     0,     0,
       0,    20,    21,    22,   172,    23,     5,    24,     6,    25,
      23,     0,     7,     8,     9,    10,     0,    63,     0,     0,
     118,    11,   119,     0,     0,    12,    13,     0,    14,     0,
       0,    17,    18,    19,   120,    64,     0,     0,    65,     0,
     121,     0,   122,    66,     0,    20,    21,     0,   123,    67,
       0,    68,    22,   265,    23,     0,    24,     0,    25,   124,
     125,    89,   126,   127,   128,   129,   130,   131,   132,   133,
     118,    90,   119,     0,   134,   135,     0,     0,    91,     0,
       0,     0,   -43,    25,   120,     0,     0,   -43,     0,     0,
     121,     0,   122,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,   118,     0,   119,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,     0,   122,     0,
       0,     0,     0,   169,   123,     0,     0,     0,     0,     0,
       0,     0,   118,     0,   119,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   120,     0,     0,     0,
     134,   135,   121,     0,   122,     0,   147,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     119,   124,   125,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   120,     0,     0,     0,   134,   135,   121,     0,
     122,     0,   198,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,   118,     0,   119,   124,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,     0,   122,     0,   252,     0,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
     118,     0,   119,   124,   125,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   120,     0,     0,     0,   134,   135,
     121,    22,   122,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,   118,     0,     0,     0,     0,     0,   124,
     125,   220,   126,   127,   128,   129,   130,   131,   132,   133,
     118,     0,   119,   121,   134,   135,   221,     0,     0,     0,
       0,   123,     0,   118,   120,     0,     0,     0,     0,     0,
     121,     0,   122,     0,     0,     0,     0,   120,   123,     0,
       0,   132,   133,   121,     0,   122,     0,   134,   135,   124,
     125,   123,   126,   127,   128,   129,   130,   131,   132,   133,
     118,     0,   119,     0,   134,   135,   277,   128,   129,   130,
     131,   132,   133,     0,   120,     0,     0,   134,   135,     0,
     121,     0,   122,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,   118,     0,   119,   124,
     125,   219,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,     0,   122,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,   118,     0,   119,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   120,     0,     0,     0,
     134,   135,   121,     0,   122,     0,     0,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,   118,     0,
       0,     0,   125,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   120,     0,     0,     0,   134,   135,   121,     0,
     122,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,   118,     0,     0,     0,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,     0,   122,     0,     0,     0,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
     118,     0,     0,   118,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,   120,   118,     0,   120,   134,   135,
     121,     0,   122,   121,     0,   122,     0,     0,   123,   120,
       0,   123,     0,     0,     0,   121,     0,   122,     0,     0,
       0,     0,     0,   123,     0,   129,   130,   131,   132,   133,
     131,   132,   133,   118,   134,   135,   118,   134,   135,     0,
       0,   130,   131,   132,   133,     0,     0,   120,     0,   134,
     135,     0,     0,   121,     0,   122,   121,     0,   122,     0,
       0,   123,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,   133,     0,   132,   133,     0,   134,   135,     0,
     134,   135
};

static const yytype_int16 yycheck[] =
{
       6,     4,    44,    36,   160,     8,     5,    10,   115,    15,
      16,    14,   214,    39,    31,     3,    33,    20,    21,    40,
      23,    38,    39,    40,     5,    41,    42,    62,     6,    64,
      33,    21,    48,    59,    50,    23,     0,   239,   240,    56,
      57,    44,    45,    62,    62,    66,    24,    66,     3,    27,
      56,    39,    40,    41,    32,    23,    59,    40,    57,    60,
      38,    16,    42,    69,    42,    53,    54,    65,    23,    75,
      60,    74,    42,   115,    62,    42,    57,    40,    66,     6,
      97,    98,    99,    63,    39,    40,    41,    65,   244,    57,
      58,    94,     3,    63,    42,     5,    63,    24,    53,    54,
      27,    30,   108,    39,    40,    32,    35,    62,   111,    64,
      66,    38,    23,    61,    40,   118,   119,   120,    60,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    39,   241,    41,    66,    36,    65,    44,
      51,    52,    12,     9,   150,   151,    57,    58,    18,     0,
     156,    41,     3,    19,   170,     3,    62,    62,    28,    64,
      26,    57,    57,    14,    60,    16,   199,    62,   171,    20,
      21,    22,    23,    57,    38,    23,    40,    39,    29,    39,
     197,    62,    33,    34,    62,    36,    37,    38,    39,    40,
      41,    39,    40,    41,    23,    15,    63,    66,    40,   241,
      40,    62,    53,    54,     4,    53,    54,     3,    60,    60,
      40,    62,    60,    64,    62,    66,   219,   220,    14,    13,
      16,    40,    51,    52,    20,    21,    22,    23,    57,    58,
       5,     5,    63,    29,    42,    39,    62,    33,    34,   245,
      36,    37,    38,    39,    40,    41,    41,    40,    62,    41,
      41,    58,    42,    39,    59,    61,     3,    53,    54,    58,
     149,     3,   235,   286,    60,    61,    62,    14,    64,    16,
      66,   208,    44,    20,    21,    22,    23,   288,   275,     6,
      42,    23,    29,   207,   227,    44,    33,    34,    -1,    36,
      -1,    -1,    39,    40,    41,    -1,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,     3,    53,    54,    -1,    -1,
      -1,    53,    54,    60,    61,    62,    14,    64,    16,    66,
      62,    -1,    20,    21,    22,    23,    -1,     6,    -1,    -1,
       3,    29,     5,    -1,    -1,    33,    34,    -1,    36,    -1,
      -1,    39,    40,    41,    17,    24,    -1,    -1,    27,    -1,
      23,    -1,    25,    32,    -1,    53,    54,    -1,    31,    38,
      -1,    40,    60,    61,    62,    -1,    64,    -1,    66,    42,
      43,     9,    45,    46,    47,    48,    49,    50,    51,    52,
       3,    19,     5,    -1,    57,    58,    -1,    -1,    26,    -1,
      -1,    -1,    30,    66,    17,    -1,    -1,    35,    -1,    -1,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    42,
      43,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      17,    -1,    -1,    -1,    57,    58,    23,    -1,    25,    -1,
      -1,    -1,    -1,    66,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,    42,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    17,    -1,    -1,    -1,
      57,    58,    23,    -1,    25,    -1,    63,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,    42,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    17,    -1,    -1,    -1,    57,    58,    23,    -1,
      25,    -1,    63,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,     5,    42,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    17,    -1,
      -1,    -1,    57,    58,    23,    -1,    25,    -1,    63,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,    42,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    17,    -1,    -1,    -1,    57,    58,
      23,    60,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
       3,    -1,     5,    23,    57,    58,    59,    -1,    -1,    -1,
      -1,    31,    -1,     3,    17,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    25,    -1,    -1,    -1,    -1,    17,    31,    -1,
      -1,    51,    52,    23,    -1,    25,    -1,    57,    58,    42,
      43,    31,    45,    46,    47,    48,    49,    50,    51,    52,
       3,    -1,     5,    -1,    57,    58,    59,    47,    48,    49,
      50,    51,    52,    -1,    17,    -1,    -1,    57,    58,    -1,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      17,    -1,    -1,    -1,    57,    58,    23,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,    42,    43,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    17,    -1,    -1,    -1,
      57,    58,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    17,    -1,    -1,    -1,    57,    58,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    43,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    17,    -1,
      -1,    -1,    57,    58,    23,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,     3,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    17,     3,    -1,    17,    57,    58,
      23,    -1,    25,    23,    -1,    25,    -1,    -1,    31,    17,
      -1,    31,    -1,    -1,    -1,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    48,    49,    50,    51,    52,
      50,    51,    52,     3,    57,    58,     3,    57,    58,    -1,
      -1,    49,    50,    51,    52,    -1,    -1,    17,    -1,    57,
      58,    -1,    -1,    23,    -1,    25,    23,    -1,    25,    -1,
      -1,    31,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    -1,    51,    52,    -1,    57,    58,    -1,
      57,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    68,    69,     0,     3,    14,    16,    20,    21,    22,
      23,    29,    33,    34,    36,    37,    38,    39,    40,    41,
      53,    54,    60,    62,    64,    66,    70,    72,    76,    81,
      89,   101,   103,   104,   105,   106,   107,   108,   111,   113,
     115,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   133,   134,   135,   137,   138,   141,
     142,    40,   137,     6,    24,    27,    32,    38,    40,   102,
     139,   137,   109,   137,    62,   112,   137,   139,   139,    65,
      44,    62,    64,   137,   137,   137,    40,    77,    60,     9,
      19,    26,    82,    90,     5,   106,   106,   137,    40,   142,
     106,   106,   106,   133,   120,   133,    76,   101,   135,   137,
     137,    66,   133,   133,    36,    86,   106,   139,     3,     5,
      17,    23,    25,    31,    42,    43,    45,    46,    47,    48,
      49,    50,    51,    52,    57,    58,   106,   137,   143,   139,
      57,    60,    41,   137,   139,    39,    39,    63,    62,    71,
     114,   116,    12,    18,    28,    83,    84,    85,    30,    35,
      88,    60,    98,   137,   106,   106,   106,    15,    66,    66,
     137,    62,    61,    76,   105,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,    63,    40,    40,   136,     4,   110,    63,     5,
      38,    40,    73,    74,    75,    69,   139,   139,    60,   139,
      87,    92,    93,   139,   140,    87,    99,   133,   137,    44,
      44,    59,    42,    61,    40,   106,    13,   131,   132,    40,
     142,     5,     5,    42,    63,    42,    63,    61,     5,   117,
     117,    86,    62,    63,    42,    42,    65,    91,   102,    39,
      96,    97,    63,   137,   137,    40,   132,    41,    39,    41,
      62,    41,    74,    91,    91,    61,    62,    80,    87,   139,
      39,    40,    58,    94,    95,    42,   100,    59,    41,    78,
      79,    91,    39,    59,    96,    61,    42,    63,    59,    78,
      58,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    71,    70,    72,
      72,    72,    73,    73,    74,    74,    74,    74,    75,    75,
      75,    76,    76,    76,    77,    77,    78,    79,    79,    80,
      80,    82,    81,    83,    84,    84,    84,    85,    86,    86,
      87,    88,    88,    90,    89,    89,    89,    91,    91,    91,
      92,    92,    93,    93,    94,    94,    95,    95,    95,    96,
      97,    97,    99,   100,    98,   101,   101,   101,   102,   102,
     102,   102,   102,   103,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   107,   109,   108,   110,   110,
     112,   111,   114,   113,   116,   115,   117,   117,   118,   119,
     120,   120,   120,   121,   122,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   131,   132,   133,   134,   135,
     136,   136,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   139,   139,   140,   140,   141,   142,   143,
     143
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     5,     2,
       2,     1,     4,     3,     3,     3,     3,     2,     0,     1,
       3,     0,     5,     2,     0,     1,     1,     1,     3,     0,
       3,     0,     6,     4,     1,     1,     1,     3,     0,     2,
       3,     1,     1,     0,     4,     3,     2,     1,     2,     2,
       0,     1,     1,     3,     3,     4,     0,     1,     2,     1,
       1,     3,     0,     0,     5,     1,     3,     3,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     2,     1,     1,     0,     5,     2,     0,
       0,     5,     0,     6,     0,     6,     0,     1,     2,     3,
       2,     2,     2,     2,     3,     3,     2,     4,     2,     2,
       1,     2,     5,     5,     1,     2,     1,     3,     1,     5,
       1,     3,     1,     3,     3,     4,     6,     3,     3,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     5,     1,
       1,     1,     3,     1,     3,     1,     3,     2,     3,     0,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(nullptr); }
#line 1696 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::EndBlock(); }
#line 1702 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1708 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1714 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = nullptr; }
#line 1720 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1728 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 109 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1737 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 114 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
 }
#line 1745 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam(sym_module, (yyvsp[0].str));
}
#line 1753 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 118 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1761 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1769 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1777 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1785 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 128 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1793 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 132 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1801 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 134 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1809 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 136 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1817 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_lookup("");
}
#line 1825 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 142 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1833 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1841 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1849 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 152 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1857 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 156 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 158 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1879 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1887 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 166 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1897 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_DEF; }
#line 1903 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_FUNC; }
#line 1909 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_PROCESS; }
#line 1915 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 175 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr), ((yyvsp[-2].id) == K_PROCESS));
}
#line 1923 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 179 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1930 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1937 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 183 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1953 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1959 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_SHARED;}
#line 1965 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1971 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  bool is_shared = ((yyvsp[-1].id) == K_SHARED);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
    if (is_shared) {
      vd->SetIsShared(true);
    }
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1986 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1993 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 207 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2000 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2008 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 212 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2016 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 214 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2024 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 218 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2033 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 221 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2041 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 225 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2057 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 235 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2069 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2078 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2087 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 251 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 2095 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2103 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 255 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2113 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 261 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2121 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 265 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2131 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2140 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2146 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2152 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2160 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2169 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 281 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2183 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 289 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2201 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 303 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2209 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2217 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2225 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_module;
}
#line 2233 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2241 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2249 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 320 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2257 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2265 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 326 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2273 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2280 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 329 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2287 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 330 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2295 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2303 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 334 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2311 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2318 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2325 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 338 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2332 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 339 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2339 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2346 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 341 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2353 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 342 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2361 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 346 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2368 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2375 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 348 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2382 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 352 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2390 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 356 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2398 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 360 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2404 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 360 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2412 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 364 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2420 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 366 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2428 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 370 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2434 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 370 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2442 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 374 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2448 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 374 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2456 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2462 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2470 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 382 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2477 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 383 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2485 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 387 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2494 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 392 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2504 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 398 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2514 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 402 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2523 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 405 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2532 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2540 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 414 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2548 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 416 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2556 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2565 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 425 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2584 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 440 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2597 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 449 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2607 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 455 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2618 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 462 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2626 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 466 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2638 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2645 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 477 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2652 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 478 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 481 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2666 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 484 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2674 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 488 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2683 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 493 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2691 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 497 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2699 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 499 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2707 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 503 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2716 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 506 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2729 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 513 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2737 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 515 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2745 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 517 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2753 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2761 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2769 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 523 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2777 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2785 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2793 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 529 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2801 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 531 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2809 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 533 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2817 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2825 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 537 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2833 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 539 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2841 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 541 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2849 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 543 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2857 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 545 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 547 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 549 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2881 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 551 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2889 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 553 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2897 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 555 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2905 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 557 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2913 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 559 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2921 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 561 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2929 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 563 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2938 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 566 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 2950 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 574 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2958 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 576 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2967 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 581 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2975 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 583 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2983 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 587 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2991 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 589 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2999 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 593 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 3007 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 597 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3016 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 602 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 3024 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 604 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3032 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 3036 "src/fe/parser.cpp" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 608 "src/fe/parser.ypp" /* yacc.c:1906  */

