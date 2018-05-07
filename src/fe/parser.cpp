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

#include "base/annotation_builder.h"
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
    K_DEF = 258,
    K_FUNC = 259,
    K_ENUM = 260,
    K_IMPORT = 261,
    K_ASSIGN = 262,
    K_SHIFT = 263,
    K_INT = 264,
    K_BOOL = 265,
    K_STRING = 266,
    K_OBJECT = 267,
    K_THREAD = 268,
    K_CHANNEL = 269,
    K_MAILBOX = 270,
    K_VAR = 271,
    K_ADD_SUB = 272,
    K_LG_COMPARE = 273,
    K_EQ_COMPARE = 274,
    K_INC_DEC = 275,
    K_CONST = 276,
    K_IF = 277,
    K_ELSE = 278,
    K_RETURN = 279,
    K_GOTO = 280,
    K_FOR = 281,
    K_WHILE = 282,
    K_DO = 283,
    K_CONTINUE = 284,
    K_SWITCH = 285,
    K_CASE = 286,
    K_DEFAULT = 287,
    K_BREAK = 288,
    NUM = 289,
    SYM = 290,
    STR = 291,
    K_LOGIC_OR = 292,
    K_LOGIC_AND = 293,
    K_BIT_CONCAT = 294,
    SIGN = 295,
    ADDRESS = 296
  };
#endif
/* Tokens.  */
#define K_DEF 258
#define K_FUNC 259
#define K_ENUM 260
#define K_IMPORT 261
#define K_ASSIGN 262
#define K_SHIFT 263
#define K_INT 264
#define K_BOOL 265
#define K_STRING 266
#define K_OBJECT 267
#define K_THREAD 268
#define K_CHANNEL 269
#define K_MAILBOX 270
#define K_VAR 271
#define K_ADD_SUB 272
#define K_LG_COMPARE 273
#define K_EQ_COMPARE 274
#define K_INC_DEC 275
#define K_CONST 276
#define K_IF 277
#define K_ELSE 278
#define K_RETURN 279
#define K_GOTO 280
#define K_FOR 281
#define K_WHILE 282
#define K_DO 283
#define K_CONTINUE 284
#define K_SWITCH 285
#define K_CASE 286
#define K_DEFAULT 287
#define K_BREAK 288
#define NUM 289
#define SYM 290
#define STR 291
#define K_LOGIC_OR 292
#define K_LOGIC_AND 293
#define K_BIT_CONCAT 294
#define SIGN 295
#define ADDRESS 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "src/fe/parser.ypp" /* yacc.c:355  */

  class ArrayInitializer *array;
  class Expr *expr;
  class ExprSet *expr_set;
  class EnumDecl *enum_decl;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  NumericLiteral num;
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 225 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 242 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   770

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  148
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  263

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    59,     2,     2,    45,     2,
      54,    55,    46,     2,    37,     2,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    60,
       2,     2,     2,    38,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,    43,    58,    48,     2,     2,     2,
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
      35,    36,    40,    41,    42,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    97,    98,   101,   103,   108,   110,   112,
     116,   118,   120,   124,   126,   130,   134,   136,   140,   142,
     146,   146,   150,   157,   157,   159,   163,   164,   167,   179,
     179,   184,   185,   188,   190,   192,   196,   199,   203,   213,
     221,   223,   227,   229,   233,   237,   241,   246,   246,   246,
     250,   253,   261,   275,   277,   279,   281,   286,   289,   293,
     295,   297,   298,   299,   300,   302,   304,   305,   306,   307,
     308,   309,   310,   312,   313,   313,   315,   316,   317,   321,
     325,   325,   329,   329,   333,   333,   337,   338,   342,   347,
     353,   357,   360,   365,   369,   371,   375,   380,   395,   404,
     410,   417,   421,   429,   432,   433,   436,   439,   443,   448,
     452,   454,   458,   461,   463,   465,   467,   469,   471,   473,
     475,   477,   479,   481,   483,   485,   487,   489,   491,   493,
     495,   497,   499,   501,   503,   505,   507,   509,   512,   517,
     519,   524,   526,   530,   532,   536,   540,   545,   547
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING", "K_OBJECT",
  "K_THREAD", "K_CHANNEL", "K_MAILBOX", "K_VAR", "K_ADD_SUB",
  "K_LG_COMPARE", "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE",
  "K_RETURN", "K_GOTO", "K_FOR", "K_WHILE", "K_DO", "K_CONTINUE",
  "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM", "STR", "','",
  "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'",
  "'&'", "'*'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'",
  "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept", "input",
  "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE", "ANNOTATION_VALUE_LIST",
  "ANNOTATION_OR_EMPTY", "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC",
  "FUNC_DECL", "$@1", "FUNC_DECL_HEAD", "FUNC_DECL_NAME", "STMT_LIST",
  "VAR_DECL_TAIL", "VAR_DECL", "$@2", "WIDTH_SPEC", "ARG_DECL",
  "ARG_DECL_LIST", "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM",
  "ARRAY_ELM_LIST", "ARRAY_INITIALIZER", "$@3", "$@4", "VAR_DECL_STMT",
  "TYPE_NAME", "LABEL", "RETURN", "STMT", "$@5", "EOS", "THREAD_DECL_STMT",
  "$@6", "CHANNEL_DECL_STMT", "$@7", "MAILBOX_DECL_STMT", "$@8",
  "ASSIGN_OR_EMPTY", "IF_COND_PART", "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD",
  "FOR_HEAD_PART", "FOR_COND_PART", "FOR_STMT", "WHILE_COND_PART",
  "WHILE_STMT", "DO_WHILE_HEAD", "DO_WHILE_BODY", "DO_WHILE_STMT",
  "SWITCH_STMT", "CASES_LIST", "CASE", "BLOCK", "BLOCK_HEAD", "ENUM_DECL",
  "ENUM_ITEM_LIST", "EXPR", "NUM_EXPR", "VAR", "VAR_LIST", "FUNCALL_HEAD",
  "FUNCALL", "ARG_LIST", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,    44,    63,    58,
     292,   293,   294,   124,    94,    38,    42,    33,   126,   295,
     296,    46,    91,    93,    40,    41,    64,   123,   125,    35,
      59
};
# endif

#define YYPACT_NINF -163

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-163)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -163,   125,  -163,   217,  -163,  -163,  -163,   716,   716,   716,
    -163,    -2,   -34,   716,  -163,     1,    13,    83,  -163,   716,
     716,   716,    57,  -163,  -163,   119,  -163,    81,    41,  -163,
     681,  -163,  -163,    41,    41,    41,    71,   -15,  -163,   285,
     716,    74,  -163,    71,  -163,    71,   114,  -163,  -163,  -163,
    -163,   -13,    33,  -163,   716,  -163,  -163,  -163,  -163,  -163,
    -163,   121,     9,   126,   121,   121,   111,    39,    39,   537,
      67,    41,  -163,   537,   716,   133,  -163,  -163,    39,    39,
     305,   117,  -163,    64,   162,   691,  -163,  -163,    33,  -163,
    -163,  -163,   157,  -163,  -163,  -163,   132,   121,   255,   537,
     716,  -163,  -163,   141,   185,  -163,   135,   716,   716,   716,
     716,   716,  -163,   716,   716,   716,   716,   716,   716,   716,
     716,   716,   716,   716,  -163,   537,   146,   135,   168,   169,
      41,     5,     6,  -163,  -163,   345,  -163,  -163,   171,   121,
    -163,  -163,   -11,   121,   121,  -163,  -163,   537,  -163,  -163,
    -163,  -163,   361,   716,  -163,   194,  -163,   577,   137,   123,
     112,   179,   577,   521,   631,   644,   648,   661,   417,   456,
      39,  -163,   441,  -163,  -163,  -163,   -28,  -163,   181,  -163,
      27,   182,   210,    28,  -163,    89,     6,  -163,   -22,  -163,
     167,   186,   135,    87,  -163,   190,    71,   401,   716,   716,
    -163,   199,  -163,   111,  -163,   142,  -163,  -163,  -163,   182,
    -163,    53,   202,  -163,   171,  -163,    27,   231,  -163,   193,
     121,   121,   183,  -163,  -163,   203,  -163,  -163,   592,   481,
    -163,  -163,  -163,  -163,  -163,  -163,   213,  -163,  -163,  -163,
    -163,    27,  -163,  -163,   135,    66,  -163,  -163,   190,   192,
    -163,  -163,  -163,   129,  -163,   201,  -163,  -163,  -163,    27,
    -163,  -163,  -163
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    13,     1,     0,    74,    80,    84,     0,     0,     0,
      58,     0,     0,     0,   100,     0,   139,   112,   137,     0,
       0,     0,     0,   108,    79,    20,     3,    50,     0,    73,
       0,     4,    59,     0,     0,     0,     0,     0,    67,    13,
       0,     0,    68,     0,    69,     0,     0,    70,    71,    66,
      26,     0,     0,   138,   147,   118,    53,    54,    56,    55,
     141,     0,     0,     0,     0,     0,   112,   135,   134,    88,
       0,     0,    93,    98,     0,     0,    57,   145,   119,   120,
       0,     0,    82,     0,     0,     0,    72,    65,     0,    76,
      77,    78,    90,    92,    91,    29,     0,     0,     0,    96,
       0,    99,   101,     0,    13,    61,    32,     0,     0,     0,
       0,     0,   133,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,   148,     0,    31,     0,     0,
       0,     0,    86,    63,    62,     0,   140,   113,    10,     0,
      23,    24,     0,    36,     0,    47,    52,    51,    64,    89,
      95,    94,     0,     0,   107,    29,    27,   124,   123,   121,
     125,   126,   116,     0,   131,   132,   127,   129,   130,   128,
     122,   117,     0,   146,   142,   110,     0,    75,     0,    87,
       0,     0,     0,     0,    11,     0,    86,    26,     0,    38,
       0,    37,   143,     0,    30,     0,     0,     0,     0,     0,
     114,     0,   109,     0,    81,     0,    85,    33,   106,   103,
     104,     0,     0,     9,     0,    14,     0,    13,    25,    18,
       0,     0,    42,    44,    45,    48,    97,   102,   136,     0,
     111,    34,    35,   105,     8,     7,     0,     6,    12,    83,
      21,     0,    22,    39,   144,     0,    43,    28,     0,     0,
     115,     5,    16,     0,    15,     0,    40,    46,    49,     0,
      19,    41,    17
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,  -163,  -163,    46,  -163,     4,    10,  -163,  -163,  -163,
    -163,  -163,  -163,    77,  -138,  -163,  -163,  -162,  -163,  -163,
    -163,  -163,    20,  -163,  -163,  -163,  -163,   232,   267,  -163,
    -163,   275,  -163,    -7,  -163,  -163,  -163,  -163,  -163,  -163,
      91,  -163,  -163,   243,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,    72,   -26,  -163,   244,  -163,
      -5,  -163,    -3,  -163,  -163,   -10,  -163
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   183,   184,   185,   155,   252,   253,   242,    26,
      83,   142,   143,   104,   189,    27,    84,   254,   190,   191,
     246,   247,   224,   225,   146,   195,   249,    28,   207,    29,
      30,   156,    63,    32,    33,    64,    34,   139,    35,    65,
     180,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,   209,   210,    49,    50,    51,   176,
      52,    53,   192,   193,    54,    55,   126
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    71,    67,    68,    69,    25,   194,     9,    73,   201,
      92,    94,   178,   179,    78,    79,    80,   101,   206,   102,
      72,    86,    60,    87,    60,    88,    89,    90,    91,   128,
     202,   222,   218,    70,    98,    99,    56,    57,    58,    59,
     107,   108,    23,    95,   105,   124,   187,    24,   106,   125,
     109,   110,   111,   112,   239,    74,   128,   128,   127,   112,
     128,   131,   132,   133,   134,   212,   129,   140,   141,   135,
     113,   114,    75,   115,   116,   117,   118,   119,   120,   121,
     147,   148,   243,   213,   122,   123,   205,   234,    85,   235,
     122,   123,    81,    24,   106,   152,    56,    57,    58,    59,
     255,    24,   157,   158,   159,   160,   161,   236,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   256,
     108,    77,    76,   177,   221,     2,   214,    24,    23,   109,
       3,     4,   112,    82,   100,   -29,   186,    77,     5,   188,
       6,   103,     7,   112,   215,     8,   205,     9,   197,    10,
      11,    12,    13,    14,   109,    15,    60,   112,   121,    16,
      17,    18,   130,   122,   123,    77,   259,   136,   204,   121,
     226,   138,    19,    20,   122,   123,   231,   232,   144,    21,
     149,    22,    23,   121,   260,    24,   128,   108,   122,   123,
       3,     4,   150,   228,   229,   153,   109,   110,     5,   112,
       6,   173,     7,   174,   175,     8,   182,     9,    82,    10,
      11,    12,    13,    14,   208,    15,   203,   211,   244,    16,
      17,    18,   219,   220,   223,   121,    56,    57,    58,    59,
     122,   123,    19,    20,   230,   245,     3,     4,   237,    21,
     248,    22,    23,   154,     5,    24,     6,   241,     7,   251,
     258,     8,    60,     9,   261,    10,    11,    12,    13,    14,
     238,    15,   107,   108,   217,    16,    17,    18,   257,   262,
      61,    96,   109,   110,   111,   112,    31,   216,    19,    20,
      93,   233,     0,    97,     0,    21,     0,    22,    23,   240,
       3,    24,   113,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     7,     0,     0,     8,   122,   123,     0,     0,
       0,     0,   107,   108,     0,   151,     0,     0,     0,    16,
      66,    18,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,    19,    20,     0,     0,     0,     0,     0,    21,
       0,    22,   113,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   107,   108,     0,     0,   122,   123,     0,     0,
     137,     0,   109,   110,   111,   112,     0,     0,   107,   108,
       0,     0,     0,     0,     0,     0,     0,     0,   109,   110,
     111,   112,   113,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,   122,   123,   113,   114,
     181,   115,   116,   117,   118,   119,   120,   121,   107,   108,
       0,     0,   122,   123,     0,     0,   196,     0,   109,   110,
     111,   112,     0,     0,     0,   108,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   110,   111,   112,   113,   114,
       0,   115,   116,   117,   118,   119,   120,   121,   107,   108,
       0,     0,   122,   123,     0,     0,   227,     0,   109,   110,
     111,   112,   120,   121,   108,     0,     0,     0,   122,   123,
       0,     0,     0,   109,   110,   111,   112,     0,   113,   114,
     199,   115,   116,   117,   118,   119,   120,   121,   107,   108,
       0,     0,   122,   123,   200,     0,     0,     0,   109,   110,
     111,   112,   121,     0,     0,     0,     0,   122,   123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
       0,   115,   116,   117,   118,   119,   120,   121,   107,   108,
       0,     0,   122,   123,   250,     0,     0,     0,   109,   110,
     111,   112,     0,     0,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   110,   111,   112,   113,   114,
     198,   115,   116,   117,   118,   119,   120,   121,     0,     0,
       0,     0,   122,   123,   113,   114,     0,   115,   116,   117,
     118,   119,   120,   121,   107,   108,     0,     0,   122,   123,
       0,     0,     0,     0,   109,   110,   111,   112,     0,     0,
     108,     0,     0,     0,     0,     0,     0,     0,     0,   109,
     110,   111,   112,     0,     0,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,     0,     0,     0,   122,   123,
     114,     0,   115,   116,   117,   118,   119,   120,   121,   108,
       0,     0,     0,   122,   123,     0,     0,     0,   109,   110,
     111,   112,   108,     0,     0,     0,   108,     0,     0,     0,
       0,   109,   110,   111,   112,   109,   110,   111,   112,   108,
       0,     0,   116,   117,   118,   119,   120,   121,   109,   110,
     111,   112,   122,   123,     0,     0,   117,   118,   119,   120,
     121,   118,   119,   120,   121,   122,   123,     0,     7,   122,
     123,     8,     0,     0,     0,   119,   120,   121,     7,     0,
       0,     8,   122,   123,     0,    16,    66,    18,     0,     0,
       0,     0,     0,     0,     0,    16,    66,    18,    19,    20,
       0,     0,     0,     7,     0,    21,     8,     0,    19,    20,
       0,    24,     0,     0,     0,    21,     0,     0,   145,     0,
      16,    66,    18,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,     0,     0,     0,     0,     0,
      21
};

static const yytype_int16 yycheck[] =
{
       3,    11,     7,     8,     9,     1,   144,    22,    13,    37,
      36,    37,     7,     7,    19,    20,    21,    43,   180,    45,
      54,    28,    35,    30,    35,    30,    33,    34,    35,    51,
      58,   193,    54,    35,    39,    40,     9,    10,    11,    12,
       7,     8,    57,    39,    51,    52,    57,    60,    51,    54,
      17,    18,    19,    20,   216,    54,    51,    51,    61,    20,
      51,    64,    65,    70,    71,    37,    57,     3,     4,    74,
      37,    38,    59,    40,    41,    42,    43,    44,    45,    46,
      85,    88,   220,    55,    51,    52,    59,    34,     7,    36,
      51,    52,    35,    60,    97,   100,     9,    10,    11,    12,
      34,    60,   107,   108,   109,   110,   111,    54,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    53,
       8,    54,    39,   130,    37,     0,    37,    60,    57,    17,
       5,     6,    20,    14,    60,    16,   139,    54,    13,   142,
      15,    27,    17,    20,    55,    20,    59,    22,   153,    24,
      25,    26,    27,    28,    17,    30,    35,    20,    46,    34,
      35,    36,    36,    51,    52,    54,    37,    34,   178,    46,
     196,    54,    47,    48,    51,    52,    34,    35,    16,    54,
      23,    56,    57,    46,    55,    60,    51,     8,    51,    52,
       5,     6,    60,   198,   199,    54,    17,    18,    13,    20,
      15,    55,    17,    35,    35,    20,    35,    22,    14,    24,
      25,    26,    27,    28,    32,    30,    35,     7,   221,    34,
      35,    36,    55,    37,    34,    46,     9,    10,    11,    12,
      51,    52,    47,    48,    35,    52,     5,     6,    36,    54,
      37,    56,    57,    58,    13,    60,    15,    54,    17,    36,
      58,    20,    35,    22,    53,    24,    25,    26,    27,    28,
     214,    30,     7,     8,   187,    34,    35,    36,   248,   259,
       3,    39,    17,    18,    19,    20,     1,   186,    47,    48,
      37,   209,    -1,    39,    -1,    54,    -1,    56,    57,    58,
       5,    60,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    17,    -1,    -1,    20,    51,    52,    -1,    -1,
      -1,    -1,     7,     8,    -1,    60,    -1,    -1,    -1,    34,
      35,    36,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    56,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,     7,     8,    -1,    -1,    51,    52,    -1,    -1,
      55,    -1,    17,    18,    19,    20,    -1,    -1,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    37,    38,    -1,    40,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    51,    52,    37,    38,
      55,    40,    41,    42,    43,    44,    45,    46,     7,     8,
      -1,    -1,    51,    52,    -1,    -1,    55,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    37,    38,
      -1,    40,    41,    42,    43,    44,    45,    46,     7,     8,
      -1,    -1,    51,    52,    -1,    -1,    55,    -1,    17,    18,
      19,    20,    45,    46,     8,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    17,    18,    19,    20,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,     7,     8,
      -1,    -1,    51,    52,    53,    -1,    -1,    -1,    17,    18,
      19,    20,    46,    -1,    -1,    -1,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    45,    46,     7,     8,
      -1,    -1,    51,    52,    53,    -1,    -1,    -1,    17,    18,
      19,    20,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    -1,
      -1,    -1,    51,    52,    37,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,     7,     8,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    -1,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,     8,
      -1,    -1,    -1,    51,    52,    -1,    -1,    -1,    17,    18,
      19,    20,     8,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    17,    18,    19,    20,     8,
      -1,    -1,    41,    42,    43,    44,    45,    46,    17,    18,
      19,    20,    51,    52,    -1,    -1,    42,    43,    44,    45,
      46,    43,    44,    45,    46,    51,    52,    -1,    17,    51,
      52,    20,    -1,    -1,    -1,    44,    45,    46,    17,    -1,
      -1,    20,    51,    52,    -1,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    47,    48,
      -1,    -1,    -1,    17,    -1,    54,    20,    -1,    47,    48,
      -1,    60,    -1,    -1,    -1,    54,    -1,    -1,    57,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    62,     0,     5,     6,    13,    15,    17,    20,    22,
      24,    25,    26,    27,    28,    30,    34,    35,    36,    47,
      48,    54,    56,    57,    60,    66,    70,    76,    88,    90,
      91,    92,    94,    95,    97,    99,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   117,
     118,   119,   121,   122,   125,   126,     9,    10,    11,    12,
      35,    89,   123,    93,    96,   100,    35,   121,   121,   121,
      35,   126,    54,   121,    54,    59,    39,    54,   121,   121,
     121,    35,    14,    71,    77,     7,    94,    94,   121,    94,
      94,    94,   117,   104,   117,    66,    88,   119,   121,   121,
      60,   117,   117,    27,    74,    94,   123,     7,     8,    17,
      18,    19,    20,    37,    38,    40,    41,    42,    43,    44,
      45,    46,    51,    52,    94,   121,   127,   123,    51,    57,
      36,   123,   123,    94,    94,   121,    34,    55,    54,    98,
       3,     4,    72,    73,    16,    57,    85,   121,    94,    23,
      60,    60,   121,    54,    58,    66,    92,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,    55,    35,    35,   120,    94,     7,     7,
     101,    55,    35,    63,    64,    65,   123,    57,   123,    75,
      79,    80,   123,   124,    75,    86,    55,   121,    39,    39,
      53,    37,    58,    35,   126,    59,    78,    89,    32,   115,
     116,     7,    37,    55,    37,    55,   101,    74,    54,    55,
      37,    37,    78,    34,    83,    84,   117,    55,   121,   121,
      35,    34,    35,   116,    34,    36,    54,    36,    64,    78,
      58,    54,    69,    75,   123,    52,    81,    82,    37,    87,
      53,    36,    67,    68,    78,    34,    53,    83,    58,    37,
      55,    53,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    62,    62,    63,    63,    64,    64,    64,
      65,    65,    65,    66,    66,    67,    68,    68,    69,    69,
      71,    70,    72,    72,    72,    73,    74,    74,    75,    77,
      76,    76,    76,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    84,    84,    86,    87,    85,
      88,    88,    88,    89,    89,    89,    89,    90,    91,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    93,    92,    92,    92,    92,    94,
      96,    95,    98,    97,   100,    99,   101,   101,   102,   103,
     104,   104,   104,   105,   106,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   115,   116,   117,   118,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   125,   126,   127,   127
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     3,     2,
       0,     1,     3,     0,     5,     1,     1,     3,     0,     3,
       0,     6,     4,     1,     1,     3,     0,     2,     3,     0,
       4,     3,     2,     1,     2,     2,     0,     1,     1,     3,
       2,     3,     0,     1,     1,     1,     3,     0,     0,     5,
       1,     3,     3,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     0,     4,     2,     2,     2,     1,
       0,     5,     0,     6,     0,     5,     0,     1,     2,     3,
       2,     2,     2,     2,     3,     3,     2,     5,     2,     2,
       1,     2,     5,     5,     1,     2,     1,     3,     1,     5,
       1,     3,     1,     3,     4,     6,     3,     3,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     5,     1,     1,     1,
       3,     1,     3,     1,     3,     2,     3,     0,     1
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
        case 2:
#line 96 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1625 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 97 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1632 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 98 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1639 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 101 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1647 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1656 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1664 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1672 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 112 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1680 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1688 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 118 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1696 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1704 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation(sym_null, nullptr);
}
#line 1712 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1720 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 130 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1728 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1736 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 136 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1744 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1752 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 142 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1760 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1766 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1774 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1784 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 159 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1792 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 163 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1799 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 164 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1806 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 167 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = nullptr;
  for (Expr *var : (yyvsp[-2].expr_set)->exprs) {
    VarDecl *vd = Builder::BuildVarDecl(var,
					(yyvsp[-1].width_spec).is_primitive, (yyvsp[-1].width_spec).name,
					(yyvsp[-1].width_spec).width);
    Builder::SetArrayLength(vd, (yyvsp[0].num).value);
    vds = Builder::VarDeclList(vds, vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1822 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 179 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1828 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 179 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1839 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1846 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 185 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1853 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 188 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 1861 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 190 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 1869 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 192 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 1877 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 196 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1886 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1894 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 203 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = nullptr;
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList(vds, vd);
  }
  if ((yyvsp[0].var_decl_set)->decls[0]->GetArrayLength() >= 0) {
    yyerror("Array can't be passed to a method");
    YYABORT;
  }
  (yyval.var_decl_set) = vds;
}
#line 1910 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 213 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1922 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 221 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num).value = 0;
}
#line 1930 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 223 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1938 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 227 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num).value = -1;
}
#line 1946 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 229 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1954 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 233 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1962 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 237 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 1972 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 241 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 1981 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 1987 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 1993 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2001 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 250 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2010 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2024 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 261 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  if ((yyvsp[-2].var_decl_set)->decls[0]->GetArrayLength() < 0) {
    yyerror("Array initializer to non array");
    YYABORT;
  }
  Builder::SetArrayInitializer((yyvsp[-2].var_decl_set)->decls[0], (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2042 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 275 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2050 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 277 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2058 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 279 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2066 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 281 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2074 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 286 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2081 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 289 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2089 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 293 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2097 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 295 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2105 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 297 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2112 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 298 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2119 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 299 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2126 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 300 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2134 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 302 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2142 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 304 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2149 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2156 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 306 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2163 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2170 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 308 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2177 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2184 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 310 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2192 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2198 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2206 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2213 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2220 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 317 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2227 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2235 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 325 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2241 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 325 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2249 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 329 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2255 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2263 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 333 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2269 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 333 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2277 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2284 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 338 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2292 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 342 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2301 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2311 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 353 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2321 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 357 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2330 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 360 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2339 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 365 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
}
#line 2347 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2355 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 371 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2363 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 375 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2372 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 380 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // join:
  // cond_expr
  // if (cond_expr)
  //  t:
  //  block
  //  repeat_expr
  // goto join:
  //  f:
  Emitter::EmitExprStmt((yyvsp[-2].expr));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2391 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 395 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2404 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 404 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2414 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2425 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 417 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2433 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 421 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2445 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 429 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2452 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 432 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2459 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 433 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2466 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 436 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2473 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 439 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2481 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 443 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2490 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 448 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2498 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 452 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2506 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 454 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2514 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 458 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2523 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 461 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2531 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 463 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2539 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 465 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2547 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 467 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2555 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 469 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2563 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 471 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2571 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 473 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2579 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 475 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2587 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 477 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2595 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 479 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2603 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 481 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2611 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 483 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2619 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 485 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2627 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 487 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2635 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 489 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2643 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 491 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2651 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 493 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 495 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2667 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 497 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2675 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 499 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2683 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2691 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 503 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2699 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 505 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2707 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 507 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2715 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 509 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2724 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 512 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2733 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 517 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2741 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2750 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 524 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2758 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 526 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2766 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 530 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2774 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 532 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2782 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 536 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2790 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 540 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2799 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 545 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2807 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 547 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2815 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2819 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 551 "src/fe/parser.ypp" /* yacc.c:1906  */

