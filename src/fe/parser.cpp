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
#include "fe/scanner.h"
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
#define YYLAST   937

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  291

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
     307,   309,   314,   318,   322,   324,   326,   327,   328,   330,
     332,   334,   335,   336,   337,   338,   339,   340,   342,   343,
     344,   345,   346,   350,   354,   358,   358,   362,   364,   368,
     368,   372,   372,   376,   376,   380,   381,   385,   390,   396,
     400,   403,   408,   412,   414,   418,   423,   438,   447,   453,
     460,   464,   472,   475,   476,   479,   482,   486,   491,   495,
     497,   501,   504,   511,   513,   515,   517,   519,   521,   523,
     525,   527,   529,   531,   533,   535,   537,   539,   541,   543,
     545,   547,   549,   551,   553,   555,   557,   559,   561,   564,
     572,   574,   579,   581,   585,   587,   591,   595,   600,   602
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

#define YYPACT_NINF -179

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-179)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -179,    38,   148,  -179,   151,  -179,   255,  -179,   151,  -179,
     151,  -179,   -13,  -179,   151,    42,    42,     1,    93,  -179,
     151,   151,  -179,   151,    58,  -179,  -179,    45,   636,  -179,
     107,    86,  -179,     5,  -179,  -179,    77,  -179,    86,    86,
      86,    76,    -9,  -179,   397,   151,    97,  -179,    76,  -179,
      76,   124,  -179,  -179,  -179,  -179,   -11,   326,  -179,   151,
    -179,    94,    -4,  -179,  -179,  -179,  -179,  -179,    42,    90,
     720,   125,    -4,   151,    42,   720,   115,   115,   134,  -179,
    -179,   136,    -4,    -4,   440,   114,   116,  -179,  -179,  -179,
    -179,    75,    74,    24,  -179,  -179,   326,    72,    86,  -179,
    -179,  -179,   165,  -179,  -179,  -179,   117,    42,   376,   720,
     151,  -179,  -179,   132,   252,  -179,   115,   151,   151,   151,
    -179,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   151,  -179,   720,   133,   115,   155,
     157,   195,   476,    26,  -179,  -179,  -179,   121,  -179,    42,
      42,  -179,  -179,  -179,   140,    42,    42,  -179,  -179,    42,
    -179,  -179,   720,  -179,  -179,  -179,  -179,  -179,  -179,   548,
     151,  -179,    80,  -179,   170,   756,   357,   617,    88,   756,
     684,   828,   647,   864,   879,   867,   453,    -4,    -4,  -179,
     584,  -179,  -179,  -179,   -18,   163,    86,   194,   169,   206,
     213,     6,  -179,    10,   203,    28,    28,  -179,    51,  -179,
     166,   178,   115,    68,  -179,   191,  -179,   512,   151,   151,
    -179,   193,  -179,  -179,  -179,  -179,   194,  -179,   172,  -179,
     190,   -26,   204,  -179,   121,  -179,  -179,  -179,    70,    70,
     301,  -179,   173,    42,    42,   102,   188,  -179,  -179,  -179,
     205,  -179,   792,   634,  -179,  -179,  -179,  -179,  -179,   207,
    -179,  -179,  -179,  -179,  -179,    70,  -179,  -179,   115,  -179,
    -179,    -2,  -179,  -179,   191,   189,  -179,  -179,  -179,    33,
    -179,   192,  -179,  -179,  -179,    70,  -179,   196,  -179,   210,
    -179
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    21,     1,     0,   119,     0,    94,     0,    95,
       0,    73,     0,    99,     0,     0,    11,   160,   131,   158,
       0,     0,   127,     0,    24,    93,     4,     0,    31,     5,
      65,     0,    88,     0,     6,    74,     0,    89,     0,     0,
       0,     0,     0,    82,    21,     0,     0,    83,     0,    84,
       0,     0,    85,    86,    81,    38,     0,     0,   159,   168,
     138,   131,   156,    69,    68,    70,    71,   162,     0,     0,
     107,     0,   155,     0,     0,   117,     9,    10,     0,    72,
     166,     0,   139,   140,     0,    23,     0,     7,   101,   112,
     103,     0,     0,     0,    87,    80,     0,     0,     0,    90,
      91,    92,   109,   111,   110,    43,     0,     0,     0,   115,
       0,   118,   120,     0,    21,    76,    46,     0,     0,     0,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,   169,     0,    45,     0,
       0,    98,     0,     0,   161,   132,   133,    18,     3,     0,
       0,    34,    35,    36,     0,     0,    50,    42,    41,     0,
      62,    67,    66,    79,    78,    77,   108,   114,   113,     0,
       0,   126,    43,    39,   141,   145,   147,   146,   144,   136,
       0,   152,   153,   148,   150,   151,   149,   142,   143,   137,
       0,   167,   163,   129,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,    21,   105,   105,    38,     0,    52,
       0,    51,   164,     0,    44,     0,   116,     0,     0,     0,
     134,     0,   128,    97,    96,   125,   122,   123,     0,   100,
       0,     0,     0,    17,     0,    22,     8,   106,     0,     0,
      21,    37,    29,     0,     0,     0,    56,    47,    59,    60,
      63,   121,   157,     0,   130,   124,    15,    16,    14,     0,
      13,    20,   102,   104,    32,     0,    33,    53,   165,    48,
      49,     0,    57,    40,     0,     0,   135,    12,    27,     0,
      26,     0,    58,    61,    64,     0,    30,    54,    28,     0,
      55
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,   104,  -179,  -179,  -179,  -179,    19,  -179,   -42,
    -179,   -27,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    52,
    -155,  -179,  -179,  -179,  -178,  -179,  -179,   -25,  -179,   -14,
    -179,  -179,  -179,  -179,   226,   265,  -179,  -179,  -108,   -17,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
      71,  -179,  -179,   234,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,    54,   -16,  -179,   239,  -179,
      -3,  -179,    -6,  -179,  -179,   -33,  -179
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   148,    27,   201,   202,   203,    28,
      86,   278,   279,   266,    29,    91,   154,   155,   156,   114,
     209,   159,    30,    92,   280,   210,   211,   272,   273,   249,
     250,   161,   215,   275,    31,   247,    32,    33,    34,    35,
      36,    37,    71,   196,    38,    74,    39,   149,    40,   150,
     238,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   226,   227,    54,    55,    56,   194,
      57,    58,   212,   213,    59,    60,   137
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    62,   105,    98,   214,    70,   173,    72,     4,    76,
      77,    75,     8,   257,    94,   258,    95,    82,    83,   120,
      84,    99,   100,   101,   221,   102,   104,     4,    10,    67,
      96,   198,   111,   237,   112,   246,   259,   281,     3,   115,
     135,   108,   109,   222,    17,    61,    19,    10,   232,    73,
     116,    22,   234,   133,   134,    25,   136,   282,    20,    21,
     262,   263,   138,    17,    61,    19,    78,    23,   143,   233,
     142,    25,   172,   235,    63,   285,    63,    20,    21,   163,
     164,   165,    67,   139,   160,   139,    23,   151,   267,    88,
     162,   117,    64,   152,    64,    65,   286,    65,    85,    89,
      66,   116,    66,   153,   157,    87,    90,   169,   139,   158,
     244,   120,    93,   241,   174,   175,   176,    97,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   173,   245,    80,   245,    22,    79,    25,   131,
     132,   269,   270,   205,   206,   133,   134,   139,    -2,   208,
     140,     4,    25,   216,     4,    80,    80,    81,    81,   199,
     113,   200,     5,   110,     6,   229,   141,   217,     7,     8,
       9,    10,   139,   144,    10,   145,   -25,    11,   147,   224,
     166,    12,    13,   167,    14,    15,    16,    17,    18,    19,
      17,    61,    19,   120,   170,   192,   191,   193,   172,   195,
     207,    20,    21,   223,    20,    21,     4,   225,    22,   228,
      23,   230,    24,    23,    25,   252,   253,     5,   231,     6,
     243,   131,   132,     7,     8,     9,    10,   133,   134,   242,
     248,   256,    11,   254,    80,   265,    12,    13,   268,    14,
      15,    16,    17,    18,    19,   260,   271,   274,   277,   281,
     284,   287,   204,   261,   289,     4,    20,    21,   288,   240,
     283,    63,   290,    22,   236,    23,     5,    24,     6,    25,
     106,    68,     7,     8,     9,    10,   103,   239,     0,    64,
     255,    11,    65,   107,     0,    12,    13,    66,    14,     0,
       0,    17,    18,    19,     0,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     4,    20,    21,     0,     0,     0,
       0,     0,    22,   171,    23,     5,    24,     6,    25,     0,
       0,     7,     8,     9,    10,     0,     0,     0,     0,   117,
      11,   118,     0,     0,    12,    13,     0,    14,     0,     0,
      17,    18,    19,   119,     0,     0,     0,     0,     0,   120,
       0,   121,     0,     0,    20,    21,     0,   122,     0,     0,
     117,    22,   264,    23,     0,    24,     0,    25,   123,   124,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   117,
     120,   118,   121,   133,   134,     0,     0,     0,   122,     0,
       0,     0,    25,   119,     0,     0,     0,     0,     0,   120,
       4,   121,     0,     0,     0,     0,     0,   122,   131,   132,
       0,     0,     0,     6,   133,   134,     0,     0,   123,   124,
      10,   125,   126,   127,   128,   129,   130,   131,   132,     0,
       0,     0,     0,   133,   134,     0,    17,    61,    19,     0,
       0,     0,   168,   117,     0,   118,     0,     0,     0,     0,
      20,    21,     0,     0,     0,     0,   117,   119,     0,    23,
       0,    24,     0,   120,     0,   121,     0,     0,     0,     0,
     119,   122,     0,     0,     0,     0,   120,     0,   121,   117,
       0,   118,   123,   124,   122,   125,   126,   127,   128,   129,
     130,   131,   132,   119,     0,     0,     0,   133,   134,   120,
       0,   121,     0,   146,   131,   132,     0,   122,     0,     0,
     133,   134,     0,     0,     0,   117,     0,   118,   123,   124,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   119,
       0,     0,     0,   133,   134,   120,     0,   121,     0,   197,
       0,     0,     0,   122,     0,     0,     0,     0,     0,     0,
       0,   117,     0,   118,   123,   124,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   119,     0,     0,     0,   133,
     134,   120,     0,   121,     0,   251,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   117,     0,   118,
     123,   124,     0,   125,   126,   127,   128,   129,   130,   131,
     132,   119,     0,     0,     0,   133,   134,   120,    22,   121,
       0,     0,     0,     0,     0,   122,     0,     0,     0,     0,
     117,     0,     0,     0,     0,     0,   123,   124,   219,   125,
     126,   127,   128,   129,   130,   131,   132,   117,     0,   118,
     120,   133,   134,   220,     0,    88,     0,     0,   122,     0,
     117,   119,     0,     0,     0,    89,     0,   120,     0,   121,
       0,     0,    90,     0,   119,   122,   -43,     0,   131,   132,
     120,   -43,   121,     0,   133,   134,   123,   124,   122,   125,
     126,   127,   128,   129,   130,   131,   132,   117,     0,   118,
       0,   133,   134,   276,   127,   128,   129,   130,   131,   132,
       0,   119,     0,     0,   133,   134,     0,   120,     0,   121,
       0,     0,     0,     0,     0,   122,     0,     0,     0,     0,
       0,     0,     0,   117,     0,   118,   123,   124,   218,   125,
     126,   127,   128,   129,   130,   131,   132,   119,     0,     0,
       0,   133,   134,   120,     0,   121,     0,     0,     0,     0,
       0,   122,     0,     0,     0,     0,     0,     0,     0,   117,
       0,   118,   123,   124,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   119,     0,     0,     0,   133,   134,   120,
       0,   121,     0,     0,     0,     0,     0,   122,     0,     0,
       0,     0,     0,     0,     0,   117,     0,     0,     0,   124,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   119,
       0,     0,     0,   133,   134,   120,     0,   121,     0,     0,
       0,     0,     0,   122,     0,     0,     0,     0,     0,     0,
       0,   117,     0,     0,     0,   124,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   119,     0,     0,     0,   133,
     134,   120,     0,   121,     0,     0,     0,     0,     0,   122,
       0,     0,     0,     0,     0,     0,     0,   117,     0,     0,
     117,     0,     0,     0,   126,   127,   128,   129,   130,   131,
     132,   119,   117,     0,   119,   133,   134,   120,     0,   121,
     120,     0,   121,     0,     0,   122,   119,     0,   122,     0,
       0,     0,   120,     0,   121,     0,     0,     0,     0,     0,
     122,     0,   128,   129,   130,   131,   132,   130,   131,   132,
       0,   133,   134,     0,   133,   134,     0,     0,   129,   130,
     131,   132,     0,     0,     0,     0,   133,   134
};

static const yytype_int16 yycheck[] =
{
       6,     4,    44,    36,   159,     8,   114,    10,     3,    15,
      16,    14,    21,    39,    31,    41,    33,    20,    21,    23,
      23,    38,    39,    40,    42,    41,    42,     3,    23,    40,
      33,     5,    48,     5,    50,   213,    62,    39,     0,    56,
      57,    44,    45,    61,    39,    40,    41,    23,    42,    62,
      56,    60,    42,    57,    58,    66,    59,    59,    53,    54,
     238,   239,    68,    39,    40,    41,    65,    62,    74,    63,
      73,    66,   114,    63,     6,    42,     6,    53,    54,    96,
      97,    98,    40,    57,    60,    57,    62,    12,   243,     9,
      93,     3,    24,    18,    24,    27,    63,    27,    40,    19,
      32,   107,    32,    28,    30,    60,    26,   110,    57,    35,
      42,    23,     5,    62,   117,   118,   119,    40,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   240,    65,    62,    65,    60,    44,    66,    51,
      52,    39,    40,   149,   150,    57,    58,    57,     0,   155,
      60,     3,    66,   169,     3,    62,    62,    64,    64,    38,
      36,    40,    14,    66,    16,   198,    41,   170,    20,    21,
      22,    23,    57,    39,    23,    39,    62,    29,    62,   196,
      15,    33,    34,    66,    36,    37,    38,    39,    40,    41,
      39,    40,    41,    23,    62,    40,    63,    40,   240,     4,
      60,    53,    54,    40,    53,    54,     3,    13,    60,    40,
      62,     5,    64,    62,    66,   218,   219,    14,     5,    16,
      42,    51,    52,    20,    21,    22,    23,    57,    58,    63,
      39,    41,    29,    40,    62,    62,    33,    34,   244,    36,
      37,    38,    39,    40,    41,    41,    58,    42,    41,    39,
      61,    59,   148,   234,    58,     3,    53,    54,   285,   207,
     274,     6,   287,    60,    61,    62,    14,    64,    16,    66,
      44,     6,    20,    21,    22,    23,    42,   206,    -1,    24,
     226,    29,    27,    44,    -1,    33,    34,    32,    36,    -1,
      -1,    39,    40,    41,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    53,    54,    -1,    -1,    -1,
      -1,    -1,    60,    61,    62,    14,    64,    16,    66,    -1,
      -1,    20,    21,    22,    23,    -1,    -1,    -1,    -1,     3,
      29,     5,    -1,    -1,    33,    34,    -1,    36,    -1,    -1,
      39,    40,    41,    17,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    25,    -1,    -1,    53,    54,    -1,    31,    -1,    -1,
       3,    60,    61,    62,    -1,    64,    -1,    66,    42,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,     3,
      23,     5,    25,    57,    58,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    66,    17,    -1,    -1,    -1,    -1,    -1,    23,
       3,    25,    -1,    -1,    -1,    -1,    -1,    31,    51,    52,
      -1,    -1,    -1,    16,    57,    58,    -1,    -1,    42,    43,
      23,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    39,    40,    41,    -1,
      -1,    -1,    66,     3,    -1,     5,    -1,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    -1,     3,    17,    -1,    62,
      -1,    64,    -1,    23,    -1,    25,    -1,    -1,    -1,    -1,
      17,    31,    -1,    -1,    -1,    -1,    23,    -1,    25,     3,
      -1,     5,    42,    43,    31,    45,    46,    47,    48,    49,
      50,    51,    52,    17,    -1,    -1,    -1,    57,    58,    23,
      -1,    25,    -1,    63,    51,    52,    -1,    31,    -1,    -1,
      57,    58,    -1,    -1,    -1,     3,    -1,     5,    42,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    17,
      -1,    -1,    -1,    57,    58,    23,    -1,    25,    -1,    63,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,    42,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    17,    -1,    -1,    -1,    57,
      58,    23,    -1,    25,    -1,    63,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
      42,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    17,    -1,    -1,    -1,    57,    58,    23,    60,    25,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,     3,    -1,     5,
      23,    57,    58,    59,    -1,     9,    -1,    -1,    31,    -1,
       3,    17,    -1,    -1,    -1,    19,    -1,    23,    -1,    25,
      -1,    -1,    26,    -1,    17,    31,    30,    -1,    51,    52,
      23,    35,    25,    -1,    57,    58,    42,    43,    31,    45,
      46,    47,    48,    49,    50,    51,    52,     3,    -1,     5,
      -1,    57,    58,    59,    47,    48,    49,    50,    51,    52,
      -1,    17,    -1,    -1,    57,    58,    -1,    23,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    17,    -1,    -1,
      -1,    57,    58,    23,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,     5,    42,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    17,    -1,    -1,    -1,    57,    58,    23,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    17,
      -1,    -1,    -1,    57,    58,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    -1,    43,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    17,    -1,    -1,    -1,    57,
      58,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
       3,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    17,     3,    -1,    17,    57,    58,    23,    -1,    25,
      23,    -1,    25,    -1,    -1,    31,    17,    -1,    31,    -1,
      -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    48,    49,    50,    51,    52,    50,    51,    52,
      -1,    57,    58,    -1,    57,    58,    -1,    -1,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58
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
     142,    40,   137,     6,    24,    27,    32,    40,   102,   139,
     137,   109,   137,    62,   112,   137,   139,   139,    65,    44,
      62,    64,   137,   137,   137,    40,    77,    60,     9,    19,
      26,    82,    90,     5,   106,   106,   137,    40,   142,   106,
     106,   106,   133,   120,   133,    76,   101,   135,   137,   137,
      66,   133,   133,    36,    86,   106,   139,     3,     5,    17,
      23,    25,    31,    42,    43,    45,    46,    47,    48,    49,
      50,    51,    52,    57,    58,   106,   137,   143,   139,    57,
      60,    41,   137,   139,    39,    39,    63,    62,    71,   114,
     116,    12,    18,    28,    83,    84,    85,    30,    35,    88,
      60,    98,   137,   106,   106,   106,    15,    66,    66,   137,
      62,    61,    76,   105,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,    63,    40,    40,   136,     4,   110,    63,     5,    38,
      40,    73,    74,    75,    69,   139,   139,    60,   139,    87,
      92,    93,   139,   140,    87,    99,   133,   137,    44,    44,
      59,    42,    61,    40,   106,    13,   131,   132,    40,   142,
       5,     5,    42,    63,    42,    63,    61,     5,   117,   117,
      86,    62,    63,    42,    42,    65,    91,   102,    39,    96,
      97,    63,   137,   137,    40,   132,    41,    39,    41,    62,
      41,    74,    91,    91,    61,    62,    80,    87,   139,    39,
      40,    58,    94,    95,    42,   100,    59,    41,    78,    79,
      91,    39,    59,    96,    61,    42,    63,    59,    78,    58,
      94
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
     102,   102,   103,   104,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   106,   107,   109,   108,   110,   110,   112,
     111,   114,   113,   116,   115,   117,   117,   118,   119,   120,
     120,   120,   121,   122,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   131,   132,   133,   134,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     138,   138,   139,   139,   140,   140,   141,   142,   143,   143
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
       1,     1,     2,     1,     1,     2,     2,     3,     3,     3,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     2,     1,     1,     0,     5,     2,     0,     0,
       5,     0,     6,     0,     6,     0,     1,     2,     3,     2,
       2,     2,     2,     3,     3,     2,     4,     2,     2,     1,
       2,     5,     5,     1,     2,     1,     3,     1,     5,     1,
       3,     1,     3,     3,     4,     6,     3,     3,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     5,     1,     1,
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
#line 1689 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::EndBlock(); }
#line 1695 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1701 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1707 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = nullptr; }
#line 1713 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1721 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 109 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1730 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 114 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
 }
#line 1738 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam(sym_lookup("module"), (yyvsp[0].str));
}
#line 1746 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 118 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1754 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1762 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1770 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1778 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 128 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1786 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 132 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1794 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 134 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1802 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 136 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1810 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_lookup("");
}
#line 1818 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 142 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1826 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1834 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1842 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 152 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1850 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 156 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1858 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 158 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1866 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1872 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1880 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 166 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1890 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_DEF; }
#line 1896 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_FUNC; }
#line 1902 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_PROCESS; }
#line 1908 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 175 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr), ((yyvsp[-2].id) == K_PROCESS));
}
#line 1916 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 179 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1923 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1930 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 1946 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1952 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_SHARED;}
#line 1958 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1964 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 1979 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1986 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 207 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1993 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 210 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2001 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 212 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2009 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 214 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2017 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 218 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2026 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 221 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2034 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 2050 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 2062 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2071 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2080 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 251 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 2088 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2096 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 255 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2106 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 261 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2114 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 265 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2124 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2133 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2139 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2145 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2153 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2162 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 2176 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 2194 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 303 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2202 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2210 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2218 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2226 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2234 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 318 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2242 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 322 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2250 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2258 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 326 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2265 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 327 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2272 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2280 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 330 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2288 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2296 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 334 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2303 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 335 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2310 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2317 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2324 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 338 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2331 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 339 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2338 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2346 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 344 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2353 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 345 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2360 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 346 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2367 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 350 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2375 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 354 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2383 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2389 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2397 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 362 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2405 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 364 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2413 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 368 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2419 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 368 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2427 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 372 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2433 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 372 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2441 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 376 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2447 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 376 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2455 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 380 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2462 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 381 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2470 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2479 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 390 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2489 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 396 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2499 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 400 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2508 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 403 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2517 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 408 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2525 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 412 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2533 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 414 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2541 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 418 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2550 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 423 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2569 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 438 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2582 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 447 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2592 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 453 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2603 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 460 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2611 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2623 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 472 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2630 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 475 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2637 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 476 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2644 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 479 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2651 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 482 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 486 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2668 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 491 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2676 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 495 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2684 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 497 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2692 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2701 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 504 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2714 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 511 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2722 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 513 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2730 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 515 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2738 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 517 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2746 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2754 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2762 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 523 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2770 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2778 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2786 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 529 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2794 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 531 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2802 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 533 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2810 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2818 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 537 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2826 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 539 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2834 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 541 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2842 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 543 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2850 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 545 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2858 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 547 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2866 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 549 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2874 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 551 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2882 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 553 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2890 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 555 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2898 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 557 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2906 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 559 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2914 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 561 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2923 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 564 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 2935 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 572 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2943 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 574 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2952 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 579 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2960 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 581 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2968 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 585 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2976 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 587 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2984 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 591 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2992 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 595 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3001 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 600 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 3009 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 602 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3017 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 3021 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 606 "src/fe/parser.ypp" /* yacc.c:1906  */

