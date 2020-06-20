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
    K_INPUT = 290,
    K_OUTPUT = 291,
    K_VAR = 292,
    K_WHILE = 293,
    K_WITH = 294,
    K_MODULE = 295,
    NUM = 296,
    SYM = 297,
    STR = 298,
    K_LOGIC_OR = 299,
    K_LOGIC_AND = 300,
    K_BIT_CONCAT = 301,
    SIGN = 302,
    ADDRESS = 303
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
#define K_INPUT 290
#define K_OUTPUT 291
#define K_VAR 292
#define K_WHILE 293
#define K_WITH 294
#define K_MODULE 295
#define NUM 296
#define SYM 297
#define STR 298
#define K_LOGIC_OR 299
#define K_LOGIC_AND 300
#define K_BIT_CONCAT 301
#define SIGN 302
#define ADDRESS 303

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

#line 241 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 258 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   932

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    67,     2,     2,    52,     2,
      64,    65,    53,     2,    44,     2,    59,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    68,
       2,     2,     2,    45,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    50,    63,    56,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    47,
      48,    49,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   101,   101,   103,   104,   105,   105,   107,
     107,   107,   109,   111,   116,   118,   120,   122,   126,   126,
     126,   128,   130,   132,   136,   138,   140,   144,   146,   150,
     154,   156,   160,   162,   166,   166,   170,   177,   177,   177,
     179,   183,   184,   187,   199,   199,   199,   199,   201,   201,
     214,   215,   218,   220,   222,   226,   229,   233,   243,   251,
     254,   259,   261,   263,   269,   273,   277,   282,   282,   282,
     286,   289,   297,   311,   313,   315,   317,   319,   324,   328,
     332,   334,   336,   337,   338,   340,   342,   344,   345,   346,
     347,   348,   349,   350,   352,   353,   354,   355,   356,   360,
     364,   368,   368,   372,   374,   378,   378,   382,   382,   386,
     386,   390,   391,   395,   400,   406,   410,   413,   418,   422,
     424,   428,   433,   448,   457,   463,   470,   474,   482,   485,
     486,   489,   492,   496,   501,   505,   507,   511,   514,   521,
     523,   525,   527,   529,   531,   533,   535,   537,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   557,   559,   561,
     563,   565,   567,   569,   571,   574,   582,   584,   589,   591,
     595,   597,   601,   605,   610,   612
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
  "K_SHARED", "K_SHIFT", "K_STRING", "K_SWITCH", "K_THREAD", "K_INPUT",
  "K_OUTPUT", "K_VAR", "K_WHILE", "K_WITH", "K_MODULE", "NUM", "SYM",
  "STR", "','", "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT",
  "'|'", "'^'", "'&'", "'*'", "'/'", "'!'", "'~'", "SIGN", "ADDRESS",
  "'.'", "'['", "']'", "'{'", "'}'", "'('", "')'", "'@'", "'#'", "';'",
  "$accept", "input", "FUNC_DECL_OR_STMT_LIST", "FUNC_DECL_OR_STMT", "$@1",
  "MODULE_HEAD", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE", "ANNOTATION_KEY",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "SYM_OR_EMPTY",
  "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@2",
  "FUNC_DECL_HEAD", "FUNC_DECL_KW", "FUNC_DECL_NAME", "STMT_LIST",
  "VAR_DECL_TAIL", "VAR_OR_SHARED", "VAR_DECL", "$@3", "WIDTH_SPEC",
  "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC",
  "ARRAY_ELM", "ARRAY_ELM_LIST", "ARRAY_INITIALIZER", "$@4", "$@5",
  "VAR_DECL_STMT", "TYPE_NAME", "LABEL", "RETURN", "STMT", "EOS",
  "GOTO_HEAD", "IMPORT_STMT", "$@6", "IMPORT_SPEC_OR_EMPTY",
  "THREAD_DECL_STMT", "$@7", "CHANNEL_DECL_STMT", "$@8",
  "MAILBOX_DECL_STMT", "$@9", "ASSIGN_OR_EMPTY", "IF_COND_PART",
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
     295,   296,   297,   298,    44,    63,    58,   299,   300,   301,
     124,    94,    38,    42,    47,    33,   126,   302,   303,    46,
      91,    93,   123,   125,    40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF -191

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-191)))

#define YYTABLE_NINF -35

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -191,    28,    45,  -191,   154,  -191,   327,  -191,   154,  -191,
     154,  -191,   -29,  -191,   154,    16,    16,   -31,   100,  -191,
     154,   154,  -191,   154,    18,  -191,  -191,    10,   354,  -191,
     105,    26,  -191,   185,  -191,  -191,    76,  -191,    26,    26,
      26,    74,    -9,  -191,   362,   154,    87,  -191,    74,  -191,
      74,   122,  -191,  -191,  -191,  -191,    -4,   287,  -191,   154,
    -191,   -20,    -8,  -191,  -191,  -191,  -191,  -191,  -191,    16,
     116,   685,   118,    -8,   154,    16,   685,   117,   117,   140,
    -191,  -191,   142,    -8,    -8,   391,   123,   136,  -191,  -191,
    -191,  -191,   135,    69,    34,  -191,  -191,   287,   -37,    26,
    -191,  -191,  -191,   186,  -191,  -191,  -191,   134,    16,   339,
     685,   154,  -191,  -191,   147,   209,  -191,   117,   154,   154,
     154,  -191,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,  -191,   685,   155,   117,
     174,   182,   229,   429,     3,  -191,  -191,  -191,   163,  -191,
      16,    16,  -191,  -191,  -191,   172,    16,    16,  -191,  -191,
    -191,  -191,    16,  -191,  -191,   685,  -191,  -191,  -191,  -191,
    -191,  -191,   505,   154,  -191,   160,  -191,    80,   723,   872,
     856,    89,   723,   647,   776,   814,   607,   829,   853,   868,
      -8,    -8,  -191,   543,  -191,  -191,  -191,    51,   193,    26,
     224,   197,  -191,  -191,  -191,   240,    93,  -191,   241,    94,
     151,    38,    38,  -191,   -40,  -191,   183,   211,   117,   281,
    -191,   215,  -191,   467,   154,   154,  -191,   216,  -191,  -191,
    -191,  -191,   224,  -191,   195,  -191,     6,   217,  -191,   218,
     163,  -191,  -191,  -191,   230,   230,   260,  -191,   202,    16,
      16,   110,   207,  -191,  -191,  -191,   225,  -191,   761,   595,
    -191,  -191,  -191,  -191,   235,  -191,  -191,  -191,  -191,  -191,
    -191,   230,  -191,  -191,   117,  -191,  -191,   -28,  -191,  -191,
     215,   205,  -191,  -191,  -191,    97,  -191,   223,  -191,  -191,
    -191,   230,  -191,   219,  -191,   244,  -191
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,     0,   125,     0,   100,     0,   101,
       0,    79,     0,   105,     0,     0,    11,   166,   137,   164,
       0,     0,   133,     0,    27,    99,     4,     0,    48,     5,
      70,     0,    94,     0,     6,    80,     0,    95,     0,     0,
       0,     0,     0,    88,    24,     0,     0,    89,     0,    90,
       0,     0,    91,    92,    87,    41,     0,     0,   165,   174,
     144,   137,   162,    74,    73,    75,    77,    76,   168,     0,
       0,   113,     0,   161,     0,     0,   123,     9,    10,     0,
      78,   172,     0,   145,   146,     0,    26,     0,     7,   107,
     118,   109,     0,     0,     0,    93,    86,     0,     0,     0,
      96,    97,    98,   115,   117,   116,    48,     0,     0,     0,
     121,     0,   124,   126,     0,    24,    82,    51,     0,     0,
       0,   160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,   175,     0,    50,
       0,     0,   104,     0,     0,   167,   138,   139,    21,     3,
       0,     0,    37,    38,    39,     0,     0,    55,    45,    46,
      47,    44,     0,    67,    72,    71,    85,    84,    83,   114,
     120,   119,     0,     0,   132,    48,    42,   147,   151,   153,
     152,   150,   142,     0,   158,   159,   154,   156,   157,   155,
     148,   149,   143,     0,   173,   169,   135,     0,     0,     0,
       0,     0,    18,    19,    20,     0,     0,    22,     0,     0,
      24,   111,   111,    41,     0,    57,     0,    56,   170,     0,
      49,     0,   122,     0,     0,     0,   140,     0,   134,   103,
     102,   131,   128,   129,     0,   106,     0,     0,    17,     0,
       0,    25,     8,   112,     0,     0,    24,    40,    32,     0,
       0,     0,    61,    52,    64,    65,    68,   127,   163,     0,
     136,   130,    16,    14,     0,    13,    15,    23,   108,   110,
      35,     0,    36,    58,   171,    53,    54,     0,    62,    43,
       0,     0,   141,    12,    30,     0,    29,     0,    63,    66,
      69,     0,    33,    59,    31,     0,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,   137,  -191,  -191,  -191,  -191,    48,  -191,  -191,
     -42,  -191,     0,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
      82,  -156,  -191,  -191,  -191,  -190,  -191,  -191,     7,  -191,
      19,  -191,  -191,  -191,  -191,   252,   300,  -191,  -191,  -111,
     -17,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,    95,  -191,  -191,   267,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,    79,   -16,  -191,   270,
    -191,    -3,  -191,    -6,  -191,  -191,   -33,  -191
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   149,    27,   206,   207,   208,   209,
      28,    87,   284,   285,   272,    29,    92,   155,   156,   157,
     115,   215,   162,    30,    93,   286,   216,   217,   278,   279,
     255,   256,   164,   221,   281,    31,   253,    32,    33,    34,
      35,    36,    37,    72,   199,    38,    75,    39,   150,    40,
     151,   244,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   232,   233,    54,    55,    56,
     197,    57,    58,   218,   219,    59,    60,   138
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    62,   106,    99,   176,    71,   220,    73,   201,    77,
      78,    76,     8,   287,    95,   121,    96,    83,    84,   140,
      85,   100,   101,   102,   247,   103,   105,    81,     3,   252,
      97,    25,   112,   288,   113,    74,    79,     4,    68,   116,
     136,   109,   110,   243,    81,    -2,    82,   262,     4,   263,
     117,   134,   135,    22,   268,   269,   137,    10,    68,     5,
      86,     6,   140,   139,    25,     7,     8,     9,    10,   144,
     264,   143,    88,   175,    11,    17,    61,    19,    12,    13,
     166,   167,   168,    14,    15,    16,    17,    18,    19,    20,
      21,   165,   118,   273,    25,   227,   163,   140,    23,   158,
      20,    21,   117,   121,   159,   160,   161,    22,   172,    23,
      94,    24,   121,    25,   228,   177,   178,   179,    98,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   132,   133,   176,    22,   237,   240,   134,
     135,   291,   132,   133,   211,   212,    80,   152,   134,   135,
     214,   275,   276,   153,     4,   111,   222,     4,   238,   241,
     114,   142,   292,   154,    81,     5,    82,     6,   235,    89,
     223,     7,     8,     9,    10,   140,   140,    10,   141,    90,
      11,   145,   230,   146,    12,    13,    91,   -28,     4,    14,
      15,    16,    17,    18,    19,    17,    61,    19,   202,   203,
     148,   169,   170,   204,   175,   205,    20,    21,    10,    20,
      21,   173,     4,    22,   242,    23,   195,    24,    23,    25,
     194,   258,   259,     5,   196,     6,    17,    61,    19,     7,
       8,     9,    10,   198,   213,   229,    63,   231,    11,   234,
      20,    21,    12,    13,   274,   236,   239,    14,   248,    23,
      17,    18,    19,    25,    64,   249,   254,    65,   260,    81,
     265,   266,    66,     4,    20,    21,   271,   277,   290,   280,
      67,    22,   174,    23,     5,    24,     6,    25,   283,   295,
       7,     8,     9,    10,   293,   287,   210,    63,   267,    11,
     118,   294,   119,    12,    13,   246,   107,   251,    14,   289,
     296,    17,    18,    19,   120,    64,    69,   245,    65,   104,
     121,   261,   122,    66,   108,    20,    21,     0,   123,     0,
       0,    67,    22,   270,    23,   250,    24,     0,    25,     0,
       0,   124,   125,    63,   126,   127,   128,   129,   130,   131,
     132,   133,   118,     0,   119,     0,   134,   135,   251,     0,
       0,    64,     0,     0,    65,    25,   120,     0,     0,    66,
       0,     0,   121,    89,   122,     4,   -34,    67,     0,    68,
     123,     0,   -34,    90,     0,     0,     0,     0,     6,     0,
      91,     0,   -34,   124,   125,    10,   126,   127,   128,   129,
     130,   131,   132,   133,   118,     0,   119,     0,   134,   135,
       0,     0,     0,    17,    61,    19,     0,   171,   120,     0,
       0,     0,     0,     0,   121,     0,   122,    20,    21,     0,
       0,     0,   123,     0,     0,     0,    23,     0,    24,     0,
       0,     0,   118,     0,   119,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   120,     0,     0,     0,
     134,   135,   121,     0,   122,     0,   147,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     118,     0,   119,   124,   125,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   120,     0,     0,     0,   134,   135,
     121,     0,   122,     0,   200,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     119,   124,   125,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   120,     0,     0,     0,   134,   135,   121,     0,
     122,     0,   257,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,   119,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,    22,   122,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   124,   125,   225,
     126,   127,   128,   129,   130,   131,   132,   133,   118,     0,
     119,     0,   134,   135,   226,     0,     0,     0,     0,     0,
     118,     0,   120,     0,     0,     0,     0,     0,   121,     0,
     122,     0,     0,     0,   120,     0,   123,     0,     0,     0,
     121,     0,   122,     0,     0,     0,     0,     0,   123,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     118,     0,   119,     0,   134,   135,   282,   129,   130,   131,
     132,   133,     0,     0,   120,     0,   134,   135,     0,     0,
     121,     0,   122,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     119,   124,   125,   224,   126,   127,   128,   129,   130,   131,
     132,   133,   120,     0,     0,     0,   134,   135,   121,     0,
     122,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,   119,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,     0,   122,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,     0,     0,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,   118,
       0,     0,   134,   135,   121,     0,   122,     0,     0,     0,
       0,     0,   123,   120,     0,     0,     0,     0,     0,   121,
       0,   122,     0,     0,     0,     0,   125,   123,   126,   127,
     128,   129,   130,   131,   132,   133,     0,   118,     0,     0,
     134,   135,     0,     0,   127,   128,   129,   130,   131,   132,
     133,   120,   118,     0,     0,   134,   135,   121,     0,   122,
       0,     0,     0,     0,     0,   123,   120,     0,     0,     0,
       0,     0,   121,     0,   122,     0,   118,     0,     0,   118,
     123,     0,     0,   128,   129,   130,   131,   132,   133,     0,
     120,   118,     0,   134,   135,   118,   121,     0,   122,   121,
     130,   131,   132,   133,   123,   120,     0,   123,   134,   135,
       0,   121,     0,   122,     0,   121,     0,   122,     0,   123,
       0,     0,     0,   123,     0,   131,   132,   133,     0,   132,
     133,     0,   134,   135,     0,   134,   135,     0,     0,     0,
       0,   132,   133,     0,     0,   132,   133,   134,   135,     0,
       0,   134,   135
};

static const yytype_int16 yycheck[] =
{
       6,     4,    44,    36,   115,     8,   162,    10,     5,    15,
      16,    14,    21,    41,    31,    23,    33,    20,    21,    59,
      23,    38,    39,    40,    64,    41,    42,    64,     0,   219,
      33,    68,    48,    61,    50,    64,    67,     3,    42,    56,
      57,    44,    45,     5,    64,     0,    66,    41,     3,    43,
      56,    59,    60,    62,   244,   245,    59,    23,    42,    14,
      42,    16,    59,    69,    68,    20,    21,    22,    23,    75,
      64,    74,    62,   115,    29,    41,    42,    43,    33,    34,
      97,    98,    99,    38,    39,    40,    41,    42,    43,    55,
      56,    94,     3,   249,    68,    44,    62,    59,    64,    30,
      55,    56,   108,    23,    35,    36,    37,    62,   111,    64,
       5,    66,    23,    68,    63,   118,   119,   120,    42,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    53,    54,   246,    62,    44,    44,    59,
      60,    44,    53,    54,   150,   151,    46,    12,    59,    60,
     156,    41,    42,    18,     3,    68,   172,     3,    65,    65,
      38,    43,    65,    28,    64,    14,    66,    16,   201,     9,
     173,    20,    21,    22,    23,    59,    59,    23,    62,    19,
      29,    41,   199,    41,    33,    34,    26,    64,     3,    38,
      39,    40,    41,    42,    43,    41,    42,    43,    35,    36,
      64,    15,    68,    40,   246,    42,    55,    56,    23,    55,
      56,    64,     3,    62,    63,    64,    42,    66,    64,    68,
      65,   224,   225,    14,    42,    16,    41,    42,    43,    20,
      21,    22,    23,     4,    62,    42,     6,    13,    29,    42,
      55,    56,    33,    34,   250,     5,     5,    38,    65,    64,
      41,    42,    43,    68,    24,    44,    41,    27,    42,    64,
      43,    43,    32,     3,    55,    56,    64,    60,    63,    44,
      40,    62,    63,    64,    14,    66,    16,    68,    43,    60,
      20,    21,    22,    23,    61,    41,   149,     6,   240,    29,
       3,   291,     5,    33,    34,   213,    44,    67,    38,   280,
     293,    41,    42,    43,    17,    24,     6,   212,    27,    42,
      23,   232,    25,    32,    44,    55,    56,    -1,    31,    -1,
      -1,    40,    62,    63,    64,    44,    66,    -1,    68,    -1,
      -1,    44,    45,     6,    47,    48,    49,    50,    51,    52,
      53,    54,     3,    -1,     5,    -1,    59,    60,    67,    -1,
      -1,    24,    -1,    -1,    27,    68,    17,    -1,    -1,    32,
      -1,    -1,    23,     9,    25,     3,    12,    40,    -1,    42,
      31,    -1,    18,    19,    -1,    -1,    -1,    -1,    16,    -1,
      26,    -1,    28,    44,    45,    23,    47,    48,    49,    50,
      51,    52,    53,    54,     3,    -1,     5,    -1,    59,    60,
      -1,    -1,    -1,    41,    42,    43,    -1,    68,    17,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    25,    55,    56,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    64,    -1,    66,    -1,
      -1,    -1,     3,    -1,     5,    44,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    17,    -1,    -1,    -1,
      59,    60,    23,    -1,    25,    -1,    65,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,    44,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    17,    -1,    -1,    -1,    59,    60,
      23,    -1,    25,    -1,    65,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,    44,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    17,    -1,    -1,    -1,    59,    60,    23,    -1,
      25,    -1,    65,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      17,    -1,    -1,    -1,    59,    60,    23,    62,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     3,    -1,
       5,    -1,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    17,    -1,    31,    -1,    -1,    -1,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
       3,    -1,     5,    -1,    59,    60,    61,    50,    51,    52,
      53,    54,    -1,    -1,    17,    -1,    59,    60,    -1,    -1,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    17,    -1,    -1,    -1,    59,    60,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    44,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      17,    -1,    -1,    -1,    59,    60,    23,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    17,     3,
      -1,    -1,    59,    60,    23,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    17,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    25,    -1,    -1,    -1,    -1,    45,    31,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,     3,    -1,    -1,
      59,    60,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    17,     3,    -1,    -1,    59,    60,    23,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    31,    17,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    25,    -1,     3,    -1,    -1,     3,
      31,    -1,    -1,    49,    50,    51,    52,    53,    54,    -1,
      17,     3,    -1,    59,    60,     3,    23,    -1,    25,    23,
      51,    52,    53,    54,    31,    17,    -1,    31,    59,    60,
      -1,    23,    -1,    25,    -1,    23,    -1,    25,    -1,    31,
      -1,    -1,    -1,    31,    -1,    52,    53,    54,    -1,    53,
      54,    -1,    59,    60,    -1,    59,    60,    -1,    -1,    -1,
      -1,    53,    54,    -1,    -1,    53,    54,    59,    60,    -1,
      -1,    59,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,    71,     0,     3,    14,    16,    20,    21,    22,
      23,    29,    33,    34,    38,    39,    40,    41,    42,    43,
      55,    56,    62,    64,    66,    68,    72,    74,    79,    84,
      92,   104,   106,   107,   108,   109,   110,   111,   114,   116,
     118,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   136,   137,   138,   140,   141,   144,
     145,    42,   140,     6,    24,    27,    32,    40,    42,   105,
     142,   140,   112,   140,    64,   115,   140,   142,   142,    67,
      46,    64,    66,   140,   140,   140,    42,    80,    62,     9,
      19,    26,    85,    93,     5,   109,   109,   140,    42,   145,
     109,   109,   109,   136,   123,   136,    79,   104,   138,   140,
     140,    68,   136,   136,    38,    89,   109,   142,     3,     5,
      17,    23,    25,    31,    44,    45,    47,    48,    49,    50,
      51,    52,    53,    54,    59,    60,   109,   140,   146,   142,
      59,    62,    43,   140,   142,    41,    41,    65,    64,    73,
     117,   119,    12,    18,    28,    86,    87,    88,    30,    35,
      36,    37,    91,    62,   101,   140,   109,   109,   109,    15,
      68,    68,   140,    64,    63,    79,   108,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,    65,    42,    42,   139,     4,   113,
      65,     5,    35,    36,    40,    42,    75,    76,    77,    78,
      71,   142,   142,    62,   142,    90,    95,    96,   142,   143,
      90,   102,   136,   140,    46,    46,    61,    44,    63,    42,
     109,    13,   134,   135,    42,   145,     5,    44,    65,     5,
      44,    65,    63,     5,   120,   120,    89,    64,    65,    44,
      44,    67,    94,   105,    41,    99,   100,    65,   140,   140,
      42,   135,    41,    43,    64,    43,    43,    76,    94,    94,
      63,    64,    83,    90,   142,    41,    42,    60,    97,    98,
      44,   103,    61,    43,    81,    82,    94,    41,    61,    99,
      63,    44,    65,    61,    81,    60,    97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    71,    71,    72,    72,    73,    72,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    80,    80,    81,
      82,    82,    83,    83,    85,    84,    86,    87,    87,    87,
      88,    89,    89,    90,    91,    91,    91,    91,    93,    92,
      92,    92,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    99,   100,   100,   102,   103,   101,
     104,   104,   104,   105,   105,   105,   105,   105,   106,   107,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     110,   112,   111,   113,   113,   115,   114,   117,   116,   119,
     118,   120,   120,   121,   122,   123,   123,   123,   124,   125,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     134,   135,   136,   137,   138,   139,   139,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   142,   142,
     143,   143,   144,   145,   146,   146
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     5,     2,
       2,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       1,     0,     1,     3,     0,     5,     2,     0,     1,     1,
       1,     3,     0,     3,     0,     6,     4,     1,     1,     1,
       3,     0,     2,     3,     1,     1,     1,     1,     0,     4,
       3,     2,     1,     2,     2,     0,     1,     1,     3,     3,
       4,     0,     1,     2,     1,     1,     3,     0,     0,     5,
       1,     3,     3,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     2,     1,
       1,     0,     5,     2,     0,     0,     5,     0,     6,     0,
       6,     0,     1,     2,     3,     2,     2,     2,     2,     3,
       3,     2,     4,     2,     2,     1,     2,     5,     5,     1,
       2,     1,     3,     1,     5,     1,     3,     1,     3,     3,
       4,     6,     3,     3,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     5,     1,     1,     1,     3,     1,     3,
       1,     3,     2,     3,     0,     1
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
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(nullptr); }
#line 1697 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::EndBlock(); }
#line 1703 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1709 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1715 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.expr) = nullptr; }
#line 1721 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 109 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1729 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 111 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1738 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1746 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 118 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1754 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1762 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 122 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1770 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.sym) = sym_input; }
#line 1776 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.sym) = sym_output; }
#line 1782 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.sym) = sym_module; }
#line 1788 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 128 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1796 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 130 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1804 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 132 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1812 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 136 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1820 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 138 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1828 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1836 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 144 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_lookup("");
}
#line 1844 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1852 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1860 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 154 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1868 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 156 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1876 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 160 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1884 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1892 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 166 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1898 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 166 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1906 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 170 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1916 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_DEF; }
#line 1922 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_FUNC; }
#line 1928 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_PROCESS; }
#line 1934 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 179 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr), ((yyvsp[-2].id) == K_PROCESS));
}
#line 1942 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 183 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1949 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1956 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 187 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1972 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1978 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_SHARED;}
#line 1984 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_INPUT;}
#line 1990 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_OUTPUT;}
#line 1996 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 201 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2002 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 201 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  bool is_input = ((yyvsp[-1].id) == K_INPUT);
  bool is_output = ((yyvsp[-1].id) == K_OUTPUT);
  bool is_io = (is_input || is_output);
  bool is_shared = ((yyvsp[-1].id) == K_SHARED) || is_io;
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
    if (is_shared) {
      vd->SetIsShared(true);
    }
    vd->SetIsIO(is_io, is_output);
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2021 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 214 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2028 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 215 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2035 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 218 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2043 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 220 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2051 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 222 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2059 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 226 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2068 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 229 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2076 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 233 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2092 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2104 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 251 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2113 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 254 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2122 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 259 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 2130 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 261 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2138 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2148 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2156 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 273 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2166 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 277 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2175 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2181 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2187 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2195 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 286 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2204 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 289 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2218 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 297 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2236 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2244 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2252 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2260 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 317 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_module;
}
#line 2268 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 319 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2276 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2284 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2292 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2300 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 334 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2308 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2315 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2322 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 338 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2330 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2338 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 342 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2346 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 344 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2353 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 345 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2360 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 346 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2367 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2374 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 348 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2381 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 349 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2388 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 350 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2396 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 354 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2403 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 355 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2410 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 356 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2417 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 360 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2425 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 364 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2433 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 368 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2439 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 368 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2447 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 372 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2455 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 374 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2463 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2469 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2477 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 382 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2483 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 382 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2491 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 386 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2497 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 386 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2505 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 390 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2512 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 391 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2520 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 395 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2529 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 400 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2539 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 406 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2549 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2558 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 413 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2567 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 418 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2575 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 422 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2583 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 424 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2591 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 428 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2600 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 433 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2619 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 448 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2632 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 457 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2642 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 463 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2653 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 470 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2661 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2673 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 482 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2680 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 485 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2687 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 486 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2694 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 489 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2701 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 492 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2709 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 496 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2718 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2726 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 505 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2734 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 507 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2742 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 511 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2751 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 514 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2764 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2772 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 523 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2780 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2788 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2796 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 529 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2804 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 531 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2812 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 533 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2820 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2828 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 537 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2836 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 539 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2844 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 541 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2852 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 543 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2860 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 545 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2868 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 547 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2876 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 549 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2884 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 551 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2892 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 553 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2900 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 555 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2908 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 557 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2916 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 559 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2924 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 561 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2932 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 563 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2940 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 565 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2948 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 567 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2956 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 569 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2964 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 571 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2973 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 574 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 2985 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 582 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2993 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 584 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 3002 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 589 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 3010 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 591 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 3018 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 595 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 3026 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 597 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 3034 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 601 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 3042 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 605 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3051 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 610 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 3059 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 612 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3067 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 3071 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 616 "src/fe/parser.ypp" /* yacc.c:1906  */

