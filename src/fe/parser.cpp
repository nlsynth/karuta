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
    NUM = 293,
    SYM = 294,
    STR = 295,
    K_LOGIC_OR = 296,
    K_LOGIC_AND = 297,
    K_BIT_CONCAT = 298,
    SIGN = 299,
    ADDRESS = 300
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
#define NUM 293
#define SYM 294
#define STR 295
#define K_LOGIC_OR 296
#define K_LOGIC_AND 297
#define K_BIT_CONCAT 298
#define SIGN 299
#define ADDRESS 300

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
  NumericLiteral num;
  int id;
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 235 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 252 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   909

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  285

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    64,     2,     2,    49,     2,
      61,    62,    50,     2,    41,     2,    56,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    65,
       2,     2,     2,    42,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    58,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,    47,    60,    53,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    44,    45,    46,    54,
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    99,    99,   101,   102,   103,   103,   106,
     108,   113,   115,   117,   121,   123,   125,   129,   131,   133,
     137,   139,   143,   147,   149,   153,   155,   159,   159,   163,
     170,   170,   170,   172,   176,   177,   180,   192,   192,   194,
     194,   203,   204,   207,   209,   211,   215,   218,   222,   232,
     240,   243,   248,   250,   252,   258,   262,   266,   271,   271,
     271,   275,   278,   286,   300,   302,   304,   306,   311,   315,
     319,   321,   323,   324,   325,   327,   329,   331,   332,   333,
     334,   335,   336,   337,   339,   340,   341,   342,   343,   347,
     351,   355,   355,   359,   361,   365,   365,   369,   369,   373,
     373,   377,   378,   382,   387,   393,   397,   400,   405,   409,
     411,   415,   420,   435,   444,   450,   457,   461,   469,   472,
     473,   476,   479,   483,   488,   492,   494,   498,   501,   504,
     506,   508,   510,   512,   514,   516,   518,   520,   522,   524,
     526,   528,   530,   532,   534,   536,   538,   540,   542,   544,
     546,   548,   550,   552,   554,   557,   562,   564,   569,   571,
     575,   577,   581,   585,   590,   592
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
  "K_WHILE", "K_WITH", "NUM", "SYM", "STR", "','", "'?'", "':'",
  "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'", "'&'", "'*'",
  "'/'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'", "'{'",
  "'}'", "'('", "')'", "'@'", "'#'", "';'", "$accept", "input",
  "FUNC_DECL_OR_STMT_LIST", "FUNC_DECL_OR_STMT", "$@1",
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
     295,    44,    63,    58,   296,   297,   298,   124,    94,    38,
      42,    47,    33,   126,   299,   300,    46,    91,    93,   123,
     125,    40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF -153

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-153)))

#define YYTABLE_NINF -40

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -153,    15,   138,  -153,   189,  -153,   123,  -153,   189,  -153,
     189,  -153,     8,  -153,   189,    41,    44,   -31,  -153,   189,
     189,  -153,   189,    56,  -153,  -153,   791,  -153,   141,    88,
    -153,    11,  -153,  -153,   118,  -153,    88,    88,    88,   107,
      31,  -153,    39,   189,   117,  -153,   107,  -153,   107,   152,
    -153,  -153,  -153,  -153,   -29,   305,  -153,   189,  -153,     4,
     -10,  -153,  -153,  -153,  -153,  -153,    41,   -35,   677,   149,
     -10,   189,    41,   677,   124,   155,  -153,  -153,   157,   -10,
     -10,   389,   135,   147,  -153,  -153,  -153,   197,    71,    35,
    -153,  -153,   305,   -20,    88,  -153,  -153,  -153,   187,  -153,
    -153,  -153,   151,    41,   354,   677,   189,  -153,  -153,   153,
     232,  -153,   163,   189,   189,   189,  -153,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,  -153,   677,   164,   163,   191,   192,   229,   424,     3,
    -153,  -153,  -153,  -153,   195,    41,    41,  -153,  -153,  -153,
     179,    41,    41,  -153,  -153,    41,  -153,  -153,   677,  -153,
    -153,  -153,  -153,  -153,  -153,   509,   189,  -153,   160,  -153,
      48,   712,   255,   576,    86,   712,   642,   782,   817,   605,
     852,   366,   521,   -10,   -10,  -153,   544,  -153,  -153,  -153,
     110,   200,    88,   227,   212,  -153,   251,    72,  -153,    87,
      28,    28,  -153,   112,  -153,   198,   216,   163,   461,  -153,
     221,  -153,   459,   189,   189,  -153,   223,  -153,  -153,  -153,
    -153,   227,  -153,   202,  -153,   184,    95,   224,  -153,   195,
    -153,  -153,    29,    29,   280,  -153,   206,    41,    41,   146,
     217,  -153,  -153,  -153,   228,  -153,   747,   593,  -153,  -153,
    -153,  -153,  -153,   233,  -153,  -153,  -153,  -153,  -153,    29,
    -153,  -153,   163,  -153,  -153,    -1,  -153,  -153,   221,   215,
    -153,  -153,  -153,   103,  -153,   218,  -153,  -153,  -153,    29,
    -153,   220,  -153,   241,  -153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    17,     1,     0,   115,     0,    90,     0,    91,
       0,    69,     0,    95,     0,     0,   156,   127,   154,     0,
       0,   123,     0,    20,    89,     4,    27,     5,    61,     0,
      84,     0,     6,    70,     0,    85,     0,     0,     0,     0,
       0,    78,    17,     0,     0,    79,     0,    80,     0,     0,
      81,    82,    77,    34,     0,     0,   155,   164,   134,   127,
     152,    65,    64,    66,    67,   158,     0,     0,   103,     0,
     151,     0,     0,   113,     0,     0,    68,   162,     0,   135,
     136,     0,    19,     0,    97,   108,    99,     0,     0,     0,
      83,    76,     0,     0,     0,    86,    87,    88,   105,   107,
     106,    39,     0,     0,     0,   111,     0,   114,   116,     0,
      17,    72,    42,     0,     0,     0,   150,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,   165,     0,    41,     0,     0,    94,     0,     0,
       7,   157,   128,   129,    14,     0,     0,    30,    31,    32,
       0,     0,    46,    38,    37,     0,    58,    63,    62,    75,
      74,    73,   104,   110,   109,     0,     0,   122,    39,    35,
     137,   141,   143,   142,   140,   132,     0,   148,   149,   144,
     146,   147,   145,   138,   139,   133,     0,   163,   159,   125,
       0,     0,     0,     0,     0,     3,     0,     0,    15,     0,
     101,   101,    34,     0,    48,     0,    47,   160,     0,    40,
       0,   112,     0,     0,     0,   130,     0,   124,    93,    92,
     121,   118,   119,     0,    96,    17,     0,     0,    13,     0,
      18,   102,     0,     0,    17,    33,    25,     0,     0,     0,
      52,    43,    55,    56,    59,   117,   153,     0,   126,   120,
       8,    12,    11,     0,    10,    16,    98,   100,    28,     0,
      29,    49,   161,    44,    45,     0,    53,    36,     0,     0,
     131,     9,    23,     0,    22,     0,    54,    57,    60,     0,
      26,    50,    24,     0,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,    92,  -153,  -153,  -153,    52,  -153,   -40,  -153,
       9,  -153,  -153,  -153,  -153,  -153,  -153,  -153,    80,  -152,
    -153,  -153,  -153,  -101,  -153,  -153,    17,  -153,    21,  -153,
    -153,  -153,  -153,   248,   293,  -153,  -153,  -104,   -11,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,   106,
    -153,  -153,   264,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,    94,   -17,  -153,   275,  -153,    -3,
    -153,    -6,  -153,  -153,   -30,  -153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    25,   195,   197,   198,   199,    26,    83,
     272,   273,   260,    27,    87,   150,   151,   152,   110,   204,
     155,    28,    88,   274,   205,   206,   266,   267,   243,   244,
     157,   210,   269,    29,   241,    30,    31,    32,    33,    34,
      35,    69,   192,    36,    72,    37,   145,    38,   146,   232,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,   221,   222,    52,    53,    54,   190,    55,
      56,   207,   208,    57,    58,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,    60,   101,   209,    94,    68,   169,    70,   194,    74,
      65,    73,    76,   116,     4,     3,    79,    80,    90,    81,
      91,   135,    98,   100,   136,    95,    96,    97,    92,   107,
      77,   108,    78,   231,    10,    61,    24,   275,     4,   104,
     105,    77,     4,   111,   131,    24,   129,   130,   112,    16,
      59,    18,     8,    62,   132,     6,    63,   276,    10,   135,
     134,    64,    10,    19,    20,    77,   139,    78,   138,    71,
     168,   116,    22,    16,    59,    18,    24,    16,    59,    18,
      65,   159,   160,   161,   135,   261,   158,    19,    20,   113,
      21,    19,    20,   239,   156,    82,    22,   112,   127,   128,
      22,   153,    23,   165,   129,   130,   154,   240,    75,   116,
     170,   171,   172,   227,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   229,    61,
     169,   256,   257,   251,   228,   252,   127,   128,    -2,   200,
     201,     4,   129,   130,   279,   203,    89,    62,   211,   230,
      63,   216,     5,    24,     6,    64,   253,    93,     7,     8,
       9,    10,    65,   212,   224,   280,    21,    11,   135,    84,
     217,    12,    13,   235,    14,    15,    16,    17,    18,    85,
     135,   219,   106,   140,   263,   264,    86,     4,   109,   137,
      19,    20,     4,   141,   168,   142,   -21,    21,     5,    22,
       6,    23,   162,    24,     7,     8,     9,    10,   144,   147,
     246,   247,    10,    11,   166,   148,   163,    12,    13,   135,
      14,    15,    16,    17,    18,   149,   187,    16,    59,    18,
     188,   189,   262,   191,   196,     4,    19,    20,   202,   218,
     220,    19,    20,    21,   250,    22,     5,    23,     6,    24,
      22,   223,     7,     8,     9,    10,   226,   237,   113,   242,
     236,    11,   248,    77,   254,    12,    13,   259,    14,   268,
      16,    17,    18,   271,   265,   278,   281,   283,   116,   275,
     117,   255,   234,     4,    19,    20,   118,   225,   282,   277,
     102,    21,   167,    22,     5,    23,     6,    24,   284,    66,
       7,     8,     9,    10,    99,   127,   128,   233,   113,    11,
     114,   129,   130,    12,    13,   249,    14,   103,    16,    17,
      18,     0,   115,     0,     0,     0,     0,     0,   116,     0,
     117,     0,    19,    20,     0,     0,   118,     0,     0,    21,
     258,    22,     0,    23,     0,    24,   119,   120,     0,   121,
     122,   123,   124,   125,   126,   127,   128,   113,     0,   114,
       0,   129,   130,     0,     0,     0,     0,     0,     0,   113,
      24,   115,     0,     0,     0,     0,     0,   116,     0,   117,
       0,     0,     0,   115,     0,   118,     0,     0,     0,   116,
       0,   117,   113,     0,   114,   119,   120,   118,   121,   122,
     123,   124,   125,   126,   127,   128,   115,     0,     0,     0,
     129,   130,   116,     0,   117,   126,   127,   128,     0,   164,
     118,     0,   129,   130,     0,     0,     0,   113,     0,   114,
     119,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   115,     0,     0,     0,   129,   130,   116,     0,   117,
       0,   143,     0,     0,     0,   118,     0,     0,     0,     0,
       0,     0,   113,     0,   114,   119,   120,    61,   121,   122,
     123,   124,   125,   126,   127,   128,   115,     0,     0,     0,
     129,   130,   116,     0,   117,    62,   193,     0,    63,     0,
     118,     0,     0,    64,     0,     0,     0,     0,     0,     0,
     119,   120,   238,   121,   122,   123,   124,   125,   126,   127,
     128,     0,   113,     0,   114,   129,   130,     0,     0,     0,
       0,   245,     0,     0,   113,   239,   115,     0,     0,     0,
       0,     0,   116,     0,   117,     0,     0,     0,   115,     0,
     118,     0,     0,     0,   116,     0,   117,   113,     0,   114,
     119,   120,   118,   121,   122,   123,   124,   125,   126,   127,
     128,   115,     0,     0,     0,   129,   130,   116,    21,   117,
       0,   127,   128,     0,     0,   118,     0,   129,   130,   113,
       0,     0,     0,     0,     0,   119,   120,   214,   121,   122,
     123,   124,   125,   126,   127,   128,   113,     0,   114,   116,
     129,   130,   215,     0,     0,     0,     0,   118,   113,     0,
     115,     0,     0,     0,     0,     0,   116,     0,   117,     0,
       0,     0,   115,     0,   118,     0,   127,   128,   116,     0,
     117,     0,   129,   130,   119,   120,   118,   121,   122,   123,
     124,   125,   126,   127,   128,   113,     0,   114,     0,   129,
     130,   270,   124,   125,   126,   127,   128,     0,     0,   115,
       0,   129,   130,     0,     0,   116,     0,   117,     0,     0,
       0,     0,     0,   118,     0,     0,     0,     0,     0,     0,
     113,     0,   114,   119,   120,   213,   121,   122,   123,   124,
     125,   126,   127,   128,   115,     0,     0,     0,   129,   130,
     116,     0,   117,     0,     0,     0,     0,     0,   118,     0,
       0,     0,     0,     0,     0,   113,     0,   114,   119,   120,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   115,
       0,     0,     0,   129,   130,   116,     0,   117,     0,     0,
       0,     0,     0,   118,     0,     0,     0,     0,     0,     0,
     113,     0,     0,     0,   120,     0,   121,   122,   123,   124,
     125,   126,   127,   128,   115,     0,     0,     0,   129,   130,
     116,     0,   117,     0,     0,     0,     0,     0,   118,     0,
       0,     0,     0,     0,     0,   113,     0,     0,     0,   120,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   115,
      84,     0,     0,   129,   130,   116,     0,   117,     0,     0,
      85,     0,     0,   118,     0,     0,     0,    86,     0,     0,
     113,   -39,     0,     0,     0,     0,   -39,   122,   123,   124,
     125,   126,   127,   128,   115,     0,     0,     0,   129,   130,
     116,     0,   117,     0,     0,     0,     0,     0,   118,     0,
       0,     0,     0,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,   127,   128,   115,
       0,     0,     0,   129,   130,   116,     0,   117,     0,     0,
       0,     0,     0,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,   128,     0,     0,     0,     0,   129,   130
};

static const yytype_int16 yycheck[] =
{
       6,     4,    42,   155,    34,     8,   110,    10,     5,    15,
      39,    14,    43,    23,     3,     0,    19,    20,    29,    22,
      31,    56,    39,    40,    59,    36,    37,    38,    31,    46,
      61,    48,    63,     5,    23,     6,    65,    38,     3,    42,
      43,    61,     3,    54,    55,    65,    56,    57,    54,    38,
      39,    40,    21,    24,    57,    16,    27,    58,    23,    56,
      66,    32,    23,    52,    53,    61,    72,    63,    71,    61,
     110,    23,    61,    38,    39,    40,    65,    38,    39,    40,
      39,    92,    93,    94,    56,   237,    89,    52,    53,     3,
      59,    52,    53,    64,    59,    39,    61,   103,    50,    51,
      61,    30,    63,   106,    56,    57,    35,   208,    64,    23,
     113,   114,   115,    41,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,    41,     6,
     234,   232,   233,    38,    62,    40,    50,    51,     0,   145,
     146,     3,    56,    57,    41,   151,     5,    24,   165,    62,
      27,    41,    14,    65,    16,    32,    61,    39,    20,    21,
      22,    23,    39,   166,   194,    62,    59,    29,    56,     9,
      60,    33,    34,    61,    36,    37,    38,    39,    40,    19,
      56,   192,    65,    59,    38,    39,    26,     3,    36,    40,
      52,    53,     3,    38,   234,    38,    61,    59,    14,    61,
      16,    63,    15,    65,    20,    21,    22,    23,    61,    12,
     213,   214,    23,    29,    61,    18,    65,    33,    34,    56,
      36,    37,    38,    39,    40,    28,    62,    38,    39,    40,
      39,    39,   238,     4,    39,     3,    52,    53,    59,    39,
      13,    52,    53,    59,    60,    61,    14,    63,    16,    65,
      61,    39,    20,    21,    22,    23,     5,    41,     3,    38,
      62,    29,    39,    61,    40,    33,    34,    61,    36,    41,
      38,    39,    40,    40,    57,    60,    58,    57,    23,    38,
      25,   229,   202,     3,    52,    53,    31,   195,   279,   268,
      42,    59,    60,    61,    14,    63,    16,    65,   281,     6,
      20,    21,    22,    23,    40,    50,    51,   201,     3,    29,
       5,    56,    57,    33,    34,   221,    36,    42,    38,    39,
      40,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      25,    -1,    52,    53,    -1,    -1,    31,    -1,    -1,    59,
      60,    61,    -1,    63,    -1,    65,    41,    42,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,     3,    -1,     5,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      65,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,
      -1,    -1,    -1,    17,    -1,    31,    -1,    -1,    -1,    23,
      -1,    25,     3,    -1,     5,    41,    42,    31,    44,    45,
      46,    47,    48,    49,    50,    51,    17,    -1,    -1,    -1,
      56,    57,    23,    -1,    25,    49,    50,    51,    -1,    65,
      31,    -1,    56,    57,    -1,    -1,    -1,     3,    -1,     5,
      41,    42,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    17,    -1,    -1,    -1,    56,    57,    23,    -1,    25,
      -1,    62,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,    41,    42,     6,    44,    45,
      46,    47,    48,    49,    50,    51,    17,    -1,    -1,    -1,
      56,    57,    23,    -1,    25,    24,    62,    -1,    27,    -1,
      31,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    41,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,     3,    -1,     5,    56,    57,    -1,    -1,    -1,
      -1,    62,    -1,    -1,     3,    64,    17,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    17,    -1,
      31,    -1,    -1,    -1,    23,    -1,    25,     3,    -1,     5,
      41,    42,    31,    44,    45,    46,    47,    48,    49,    50,
      51,    17,    -1,    -1,    -1,    56,    57,    23,    59,    25,
      -1,    50,    51,    -1,    -1,    31,    -1,    56,    57,     3,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,     3,    -1,     5,    23,
      56,    57,    58,    -1,    -1,    -1,    -1,    31,     3,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,
      -1,    -1,    17,    -1,    31,    -1,    50,    51,    23,    -1,
      25,    -1,    56,    57,    41,    42,    31,    44,    45,    46,
      47,    48,    49,    50,    51,     3,    -1,     5,    -1,    56,
      57,    58,    47,    48,    49,    50,    51,    -1,    -1,    17,
      -1,    56,    57,    -1,    -1,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    17,    -1,    -1,    -1,    56,    57,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    41,    42,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    17,
      -1,    -1,    -1,    56,    57,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    42,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    17,    -1,    -1,    -1,    56,    57,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    42,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    17,
       9,    -1,    -1,    56,    57,    23,    -1,    25,    -1,    -1,
      19,    -1,    -1,    31,    -1,    -1,    -1,    26,    -1,    -1,
       3,    30,    -1,    -1,    -1,    -1,    35,    45,    46,    47,
      48,    49,    50,    51,    17,    -1,    -1,    -1,    56,    57,
      23,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    17,
      -1,    -1,    -1,    56,    57,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    67,    68,     0,     3,    14,    16,    20,    21,    22,
      23,    29,    33,    34,    36,    37,    38,    39,    40,    52,
      53,    59,    61,    63,    65,    69,    74,    79,    87,    99,
     101,   102,   103,   104,   105,   106,   109,   111,   113,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   131,   132,   133,   135,   136,   139,   140,    39,
     135,     6,    24,    27,    32,    39,   100,   137,   135,   107,
     135,    61,   110,   135,   137,    64,    43,    61,    63,   135,
     135,   135,    39,    75,     9,    19,    26,    80,    88,     5,
     104,   104,   135,    39,   140,   104,   104,   104,   131,   118,
     131,    74,    99,   133,   135,   135,    65,   131,   131,    36,
      84,   104,   137,     3,     5,    17,    23,    25,    31,    41,
      42,    44,    45,    46,    47,    48,    49,    50,    51,    56,
      57,   104,   135,   141,   137,    56,    59,    40,   135,   137,
      59,    38,    38,    62,    61,   112,   114,    12,    18,    28,
      81,    82,    83,    30,    35,    86,    59,    96,   135,   104,
     104,   104,    15,    65,    65,   135,    61,    60,    74,   103,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,    62,    39,    39,
     134,     4,   108,    62,     5,    70,    39,    71,    72,    73,
     137,   137,    59,   137,    85,    90,    91,   137,   138,    85,
      97,   131,   135,    43,    43,    58,    41,    60,    39,   104,
      13,   129,   130,    39,   140,    68,     5,    41,    62,    41,
      62,     5,   115,   115,    84,    61,    62,    41,    41,    64,
      89,   100,    38,    94,    95,    62,   135,   135,    39,   130,
      60,    38,    40,    61,    40,    72,    89,    89,    60,    61,
      78,    85,   137,    38,    39,    57,    92,    93,    41,    98,
      58,    40,    76,    77,    89,    38,    58,    94,    60,    41,
      62,    58,    76,    57,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    70,    69,    71,
      71,    72,    72,    72,    73,    73,    73,    74,    74,    74,
      75,    75,    76,    77,    77,    78,    78,    80,    79,    81,
      82,    82,    82,    83,    84,    84,    85,    86,    86,    88,
      87,    87,    87,    89,    89,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    95,    95,    97,    98,
      96,    99,    99,    99,   100,   100,   100,   100,   101,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     105,   107,   106,   108,   108,   110,   109,   112,   111,   114,
     113,   115,   115,   116,   117,   118,   118,   118,   119,   120,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     129,   130,   131,   132,   133,   134,   134,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   140,   141,   141
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     6,     4,
       3,     3,     3,     2,     0,     1,     3,     0,     5,     2,
       0,     1,     1,     1,     3,     0,     3,     0,     6,     4,
       1,     1,     1,     3,     0,     2,     3,     1,     1,     0,
       4,     3,     2,     1,     2,     2,     0,     1,     1,     3,
       3,     4,     0,     1,     2,     1,     1,     3,     0,     0,
       5,     1,     3,     3,     1,     1,     1,     1,     2,     1,
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
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(nullptr); }
#line 1678 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::EndBlock(); }
#line 1684 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1692 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1701 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 113 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1709 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 115 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1717 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1725 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 121 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1733 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1741 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 125 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1749 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 129 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1757 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 131 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1765 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 133 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1773 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 137 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_lookup("");
}
#line 1781 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1789 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 143 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1797 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 147 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1805 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 149 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1813 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 153 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1821 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 155 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1829 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 159 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1835 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 159 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1843 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 163 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1853 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 170 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_DEF; }
#line 1859 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 170 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_FUNC; }
#line 1865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 170 "src/fe/parser.ypp" /* yacc.c:1646  */
    { (yyval.id) = K_PROCESS; }
#line 1871 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 172 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr), ((yyvsp[-2].id) == K_PROCESS));
}
#line 1879 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 176 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1886 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1893 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1909 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 192 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1915 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 192 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_SHARED;}
#line 1921 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 194 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1927 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 194 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1942 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 203 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1949 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 204 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1956 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 207 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 1964 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 209 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 1972 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 211 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 1980 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 215 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1989 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 218 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1997 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 222 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2013 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 232 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2025 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 240 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2034 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2043 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 248 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 2051 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 250 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2059 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 252 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2069 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 258 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2077 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2087 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 266 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2096 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 271 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2102 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 271 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2108 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 271 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2116 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 275 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2125 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2139 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 286 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2157 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 300 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2165 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 302 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2173 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 304 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2181 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 306 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2189 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2197 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2205 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 319 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2213 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2221 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 323 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2228 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2235 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 325 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2243 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 327 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2251 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 329 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2259 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 331 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2266 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2273 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 333 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2280 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 334 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2287 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 335 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2294 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2301 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2309 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 341 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2316 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 342 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2323 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 343 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2330 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2338 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 351 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2346 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 355 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2352 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 355 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2360 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 359 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2368 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 361 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2376 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 365 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2382 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 365 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2390 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2396 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2404 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2410 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2418 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 377 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2425 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2433 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 382 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2442 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 387 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2452 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 393 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2462 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 397 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2471 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 400 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2480 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 405 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2488 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 409 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2496 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 411 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2504 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 415 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2513 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2532 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 435 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2545 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 444 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2555 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 450 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2566 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 457 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2574 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 461 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2586 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 469 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2593 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 472 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2600 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 473 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2607 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 476 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2614 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 479 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2622 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 483 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2631 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 488 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2639 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 492 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2647 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 494 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2655 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 498 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2664 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), Builder::NumExpr((yyvsp[0].num)));
}
#line 2673 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 504 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2681 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 506 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2689 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 508 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2697 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 510 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2705 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 512 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2713 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 514 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2721 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 516 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2729 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 518 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2737 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 520 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2745 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 522 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2753 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 524 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2761 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 526 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2769 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 528 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2777 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 530 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2785 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 532 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2793 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 534 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2801 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 536 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2809 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 538 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2817 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 540 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2825 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 542 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2833 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 544 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2841 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 546 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2849 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 548 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2857 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 550 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 552 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 554 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2882 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 557 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2891 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 562 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2899 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 564 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2908 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 569 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2916 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 571 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2924 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 575 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2932 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 577 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2940 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 581 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2948 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 585 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2957 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 590 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2965 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 592 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2973 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2977 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 596 "src/fe/parser.ypp" /* yacc.c:1906  */

