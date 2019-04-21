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
    K_AS = 262,
    K_ASSIGN = 263,
    K_SHIFT = 264,
    K_INT = 265,
    K_BOOL = 266,
    K_STRING = 267,
    K_OBJECT = 268,
    K_THREAD = 269,
    K_CHANNEL = 270,
    K_MAILBOX = 271,
    K_VAR = 272,
    K_LOCAL = 273,
    K_ADD_SUB = 274,
    K_LG_COMPARE = 275,
    K_EQ_COMPARE = 276,
    K_INC_DEC = 277,
    K_CONST = 278,
    K_IF = 279,
    K_ELSE = 280,
    K_RETURN = 281,
    K_GOTO = 282,
    K_FOR = 283,
    K_WHILE = 284,
    K_DO = 285,
    K_CONTINUE = 286,
    K_SWITCH = 287,
    K_CASE = 288,
    K_DEFAULT = 289,
    K_BREAK = 290,
    NUM = 291,
    SYM = 292,
    STR = 293,
    K_LOGIC_OR = 294,
    K_LOGIC_AND = 295,
    K_BIT_CONCAT = 296,
    SIGN = 297,
    ADDRESS = 298
  };
#endif
/* Tokens.  */
#define K_DEF 258
#define K_FUNC 259
#define K_ENUM 260
#define K_IMPORT 261
#define K_AS 262
#define K_ASSIGN 263
#define K_SHIFT 264
#define K_INT 265
#define K_BOOL 266
#define K_STRING 267
#define K_OBJECT 268
#define K_THREAD 269
#define K_CHANNEL 270
#define K_MAILBOX 271
#define K_VAR 272
#define K_LOCAL 273
#define K_ADD_SUB 274
#define K_LG_COMPARE 275
#define K_EQ_COMPARE 276
#define K_INC_DEC 277
#define K_CONST 278
#define K_IF 279
#define K_ELSE 280
#define K_RETURN 281
#define K_GOTO 282
#define K_FOR 283
#define K_WHILE 284
#define K_DO 285
#define K_CONTINUE 286
#define K_SWITCH 287
#define K_CASE 288
#define K_DEFAULT 289
#define K_BREAK 290
#define NUM 291
#define SYM 292
#define STR 293
#define K_LOGIC_OR 294
#define K_LOGIC_AND 295
#define K_BIT_CONCAT 296
#define SIGN 297
#define ADDRESS 298

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

#line 231 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 248 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   867

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    62,     2,     2,    47,     2,
      57,    58,    48,     2,    39,     2,    54,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,    63,
       2,     2,     2,    40,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,    45,    61,    51,     2,     2,     2,
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
      35,    36,    37,    38,    42,    43,    44,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   101,   102,   105,   107,   112,   114,   116,
     120,   122,   124,   128,   130,   134,   138,   140,   144,   146,
     150,   150,   154,   161,   161,   163,   167,   168,   171,   183,
     183,   185,   185,   194,   195,   198,   200,   202,   206,   209,
     213,   223,   231,   234,   239,   241,   243,   249,   253,   257,
     262,   262,   262,   266,   269,   277,   291,   293,   295,   297,
     302,   305,   309,   311,   313,   314,   315,   316,   318,   320,
     321,   322,   323,   324,   325,   326,   328,   329,   330,   331,
     332,   336,   340,   340,   344,   346,   350,   350,   354,   354,
     358,   358,   362,   363,   367,   372,   378,   382,   385,   390,
     394,   396,   400,   405,   420,   429,   435,   442,   446,   454,
     457,   458,   461,   464,   468,   473,   477,   479,   483,   486,
     488,   490,   492,   494,   496,   498,   500,   502,   504,   506,
     508,   510,   512,   514,   516,   518,   520,   522,   524,   526,
     528,   530,   532,   534,   536,   539,   544,   546,   551,   553,
     557,   559,   563,   567,   572,   574
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_AS", "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING", "K_OBJECT",
  "K_THREAD", "K_CHANNEL", "K_MAILBOX", "K_VAR", "K_LOCAL", "K_ADD_SUB",
  "K_LG_COMPARE", "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE",
  "K_RETURN", "K_GOTO", "K_FOR", "K_WHILE", "K_DO", "K_CONTINUE",
  "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM", "STR", "','",
  "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'",
  "'&'", "'*'", "'/'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['",
  "']'", "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept",
  "input", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "RETURN_TYPE",
  "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@1", "FUNC_DECL_HEAD",
  "FUNC_DECL_NAME", "STMT_LIST", "VAR_DECL_TAIL", "VAR_OR_LOCAL",
  "VAR_DECL", "$@2", "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST",
  "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "$@3", "$@4", "VAR_DECL_STMT", "TYPE_NAME", "LABEL",
  "RETURN", "STMT", "EOS", "IMPORT_STMT", "$@5", "IMPORT_SPEC_OR_EMPTY",
  "THREAD_DECL_STMT", "$@6", "CHANNEL_DECL_STMT", "$@7",
  "MAILBOX_DECL_STMT", "$@8", "ASSIGN_OR_EMPTY", "IF_COND_PART",
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,    44,
      63,    58,   294,   295,   296,   124,    94,    38,    42,    47,
      33,   126,   297,   298,    46,    91,    93,    40,    41,    64,
     123,   125,    35,    59
};
# endif

#define YYPACT_NINF -142

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-142)))

#define YYTABLE_NINF -32

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -142,   132,  -142,   208,  -142,  -142,   810,   810,   810,  -142,
     -25,  -142,   810,  -142,   -32,    -9,    33,  -142,   810,   810,
     810,    35,  -142,  -142,   209,  -142,    69,    23,  -142,   673,
    -142,  -142,  -142,    23,    23,    23,    22,   -18,  -142,    14,
     810,    70,  -142,    22,  -142,    22,    55,  -142,  -142,  -142,
    -142,   -16,   252,  -142,   810,  -142,  -142,  -142,  -142,  -142,
    -142,   104,    80,   110,   104,    98,    37,    37,   642,    86,
      23,   642,   810,   121,  -142,  -142,    37,    37,   390,   116,
    -142,  -142,    96,   148,   785,  -142,  -142,   252,  -142,  -142,
    -142,   142,  -142,  -142,  -142,   112,   104,   300,   642,   810,
    -142,  -142,   124,   179,  -142,   134,   810,   810,   810,   810,
     810,  -142,   810,   810,   810,   810,   810,   810,   810,   810,
     810,   810,   810,   810,  -142,   642,   128,   134,   157,   165,
     197,     0,  -142,  -142,   432,  -142,  -142,   173,   104,   104,
    -142,  -142,   -14,   104,  -142,  -142,   104,  -142,  -142,   642,
    -142,  -142,  -142,  -142,   348,   810,  -142,   164,  -142,   658,
     123,    21,   367,   771,   658,   600,    76,   713,   754,   304,
     763,   352,    37,    37,  -142,   516,  -142,  -142,  -142,    17,
     175,    23,   176,   180,   215,     2,  -142,    48,     3,     3,
    -142,   133,  -142,   170,   192,   134,    27,  -142,   198,  -142,
     474,   810,   810,  -142,   200,  -142,  -142,  -142,    98,  -142,
    -142,   180,  -142,    90,   205,  -142,   173,  -142,  -142,    19,
      19,   227,  -142,   178,   104,   104,   163,   189,  -142,  -142,
    -142,   211,  -142,   699,   558,  -142,  -142,  -142,  -142,   210,
    -142,  -142,  -142,  -142,  -142,    19,  -142,  -142,   134,  -142,
    -142,    32,  -142,  -142,   198,   186,  -142,  -142,  -142,   105,
    -142,   196,  -142,  -142,  -142,    19,  -142,   203,  -142,   226,
    -142
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    13,     1,     0,    82,    86,     0,     0,     0,    61,
       0,    99,     0,   106,     0,   146,   118,   144,     0,     0,
       0,     0,   114,    81,    20,     3,    53,     0,    76,     0,
       4,    62,    77,     0,     0,     0,     0,     0,    70,    13,
       0,     0,    71,     0,    72,     0,     0,    73,    74,    69,
      26,     0,     0,   145,   154,   124,    56,    57,    59,    58,
     148,     0,     0,     0,     0,   118,   142,   141,    94,     0,
       0,   104,     0,     0,    60,   152,   125,   126,     0,     0,
      88,    90,     0,     0,     0,    75,    68,     0,    78,    79,
      80,    96,    98,    97,    31,     0,     0,     0,   102,     0,
     105,   107,     0,    13,    64,    34,     0,     0,     0,     0,
       0,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,   155,     0,    33,     0,     0,
      85,     0,    66,    65,     0,   147,   119,    10,     0,     0,
      23,    24,     0,    38,    29,    30,     0,    50,    55,    54,
      67,    95,   101,   100,     0,     0,   113,    31,    27,   131,
     130,   127,   132,   133,   122,     0,   138,   139,   134,   136,
     137,   135,   128,   129,   123,     0,   153,   149,   116,     0,
       0,     0,     0,     0,     0,     0,    11,     0,    92,    92,
      26,     0,    40,     0,    39,   150,     0,    32,     0,   103,
       0,     0,     0,   120,     0,   115,    84,    83,     0,    87,
     112,   109,   110,     0,     0,     9,     0,    14,    93,     0,
       0,    13,    25,    18,     0,     0,     0,    44,    35,    47,
      48,    51,   108,   143,     0,   117,   111,     8,     7,     0,
       6,    12,    89,    91,    21,     0,    22,    41,   151,    36,
      37,     0,    45,    28,     0,     0,   121,     5,    16,     0,
      15,     0,    46,    49,    52,     0,    19,    42,    17,     0,
      43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,    50,  -142,    16,     4,  -142,  -142,  -142,
    -142,  -142,  -142,    77,  -141,  -142,  -142,  -142,   -67,  -142,
    -142,     1,  -142,    25,  -142,  -142,  -142,  -142,   231,   272,
    -142,  -142,   275,    -7,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,    91,  -142,  -142,   244,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,    71,   -27,
    -142,   246,  -142,    -5,  -142,    -3,  -142,  -142,    -6,  -142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   185,   186,   187,   157,   258,   259,   246,    25,
      82,   142,   143,   103,   192,   146,    26,    83,   260,   193,
     194,   252,   253,   230,   231,   148,   198,   255,    27,   228,
      28,    29,   158,    31,    32,    63,   181,    33,    64,    34,
     138,    35,   139,   219,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,   211,   212,    49,
      50,    51,   179,    52,    53,   195,   196,    54,    55,   126
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    66,    67,    68,    70,   197,     8,    71,   182,    91,
      93,   218,    69,    76,    77,    78,   100,    24,   101,     3,
      85,    60,    86,    60,    87,    72,    88,    89,    90,    56,
      57,    58,    59,     6,    97,    98,     7,    56,    57,    58,
      59,   214,    22,   111,   104,   124,   190,    23,   105,   125,
      15,    65,    17,    73,   128,    94,   204,   128,   127,   111,
     215,   131,   132,   133,    18,    19,   225,   134,   261,   120,
     121,    20,    79,    21,    74,   122,   123,    84,   205,   149,
     150,   226,    22,   247,   102,   107,    23,   216,   262,   226,
      75,   122,   123,   105,   154,   108,   109,   110,   111,   140,
     141,   159,   160,   161,   162,   163,   217,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   115,
     116,   117,   118,   119,   120,   121,   237,   199,   238,   227,
     122,   123,     2,    99,   128,   188,   189,     3,     4,   191,
     129,    60,   108,    75,   265,   111,     5,   239,   130,    23,
     200,     6,   242,   243,     7,    75,     8,   135,     9,    10,
      11,    12,    13,   266,    14,   144,   145,   151,    15,    16,
      17,   120,   121,   137,   207,   152,   209,   122,   123,    80,
      81,   155,    18,    19,     3,     4,   176,   128,   128,    20,
     222,    21,    22,     5,   177,    23,   233,   234,     6,   249,
     250,     7,   178,     8,   180,     9,    10,    11,    12,    13,
     184,    14,   206,   208,   210,    15,    16,    17,    56,    57,
      58,    59,   248,   213,    80,    81,   -31,   -31,   223,    18,
      19,   224,     3,     4,   229,   245,    20,   235,    21,    22,
     156,     5,    23,   240,   251,    60,     6,   264,   257,     7,
     254,     8,   267,     9,    10,    11,    12,    13,   269,    14,
     106,   107,   261,    15,    16,    17,   241,   221,   270,   268,
      95,   108,   109,   110,   111,    61,    30,    18,    19,   263,
     220,    92,   236,     0,    20,    96,    21,    22,   244,     0,
      23,   112,   113,     0,   114,   115,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,   122,   123,   106,   107,
       0,     0,     0,   107,     0,    23,     0,     0,     0,   108,
     109,   110,   111,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,   114,   115,   116,   117,   118,   119,   120,   121,
     118,   119,   120,   121,   122,   123,   106,   107,   122,   123,
       0,   107,     0,   153,     0,     0,     0,   108,   109,   110,
     111,   108,   109,   110,   111,     0,   107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   112,   113,   111,
     114,   115,   116,   117,   118,   119,   120,   121,   106,   107,
     120,   121,   122,   123,     0,     0,   122,   123,    22,   108,
     109,   110,   111,     0,     0,   120,   121,     0,     0,     0,
       0,   122,   123,     0,     0,     0,     0,     0,     0,   112,
     113,     0,   114,   115,   116,   117,   118,   119,   120,   121,
     106,   107,     0,     0,   122,   123,     0,     0,   136,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   106,   107,     0,     0,   122,   123,     0,     0,
     183,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,     0,   114,   115,   116,   117,
     118,   119,   120,   121,   106,   107,     0,     0,   122,   123,
       0,     0,   232,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   202,   114,   115,
     116,   117,   118,   119,   120,   121,   106,   107,     0,     0,
     122,   123,   203,     0,     0,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   106,   107,
       0,     0,   122,   123,   256,     0,     0,     0,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   201,   114,   115,   116,   117,   118,   119,   120,   121,
     106,   107,     0,     0,   122,   123,     0,     0,     0,     0,
       0,   108,   109,   110,   111,     0,   106,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,   109,   110,
     111,   112,   113,     0,   114,   115,   116,   117,   118,   119,
     120,   121,     6,     0,     0,     7,   122,   123,   113,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   107,    15,
      65,    17,   122,   123,     0,     0,     0,     0,   108,   109,
     110,   111,   107,    18,    19,     0,     0,     0,     0,     0,
      20,     0,   108,   109,   110,   111,    23,     0,     0,   113,
       0,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   122,   123,     0,     0,   116,   117,   118,
     119,   120,   121,   107,     0,     0,     0,   122,   123,     0,
       0,     0,   107,   108,   109,   110,   111,     0,     0,     0,
     107,     0,   108,   109,   110,   111,     0,     0,     0,     0,
     108,   109,     0,   111,     0,     0,     0,     0,     0,   117,
     118,   119,   120,   121,     6,     0,     0,     7,   122,   123,
     119,   120,   121,     0,     0,     0,     0,   122,   123,   120,
     121,    15,    65,    17,     0,   122,   123,     0,     0,     6,
       0,     0,     7,     0,     0,    18,    19,     0,     0,     0,
       0,     0,    20,     0,     0,   147,    15,    65,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,     0,     0,     0,     0,     0,    20
};

static const yytype_int16 yycheck[] =
{
       3,     6,     7,     8,    10,   146,    24,    12,     8,    36,
      37,     8,    37,    18,    19,    20,    43,     1,    45,     5,
      27,    37,    29,    37,    29,    57,    33,    34,    35,    10,
      11,    12,    13,    19,    39,    40,    22,    10,    11,    12,
      13,    39,    60,    22,    51,    52,    60,    63,    51,    54,
      36,    37,    38,    62,    54,    39,    39,    54,    61,    22,
      58,    64,    69,    70,    50,    51,    39,    72,    36,    48,
      49,    57,    37,    59,    41,    54,    55,     8,    61,    84,
      87,    62,    60,   224,    29,     9,    63,    39,    56,    62,
      57,    54,    55,    96,    99,    19,    20,    21,    22,     3,
       4,   106,   107,   108,   109,   110,    58,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    43,
      44,    45,    46,    47,    48,    49,    36,   154,    38,   196,
      54,    55,     0,    63,    54,   138,   139,     5,     6,   142,
      60,    37,    19,    57,    39,    22,    14,    57,    38,    63,
     155,    19,   219,   220,    22,    57,    24,    36,    26,    27,
      28,    29,    30,    58,    32,    17,    18,    25,    36,    37,
      38,    48,    49,    57,   181,    63,   182,    54,    55,    15,
      16,    57,    50,    51,     5,     6,    58,    54,    54,    57,
      57,    59,    60,    14,    37,    63,   201,   202,    19,    36,
      37,    22,    37,    24,     7,    26,    27,    28,    29,    30,
      37,    32,    37,    37,    34,    36,    37,    38,    10,    11,
      12,    13,   225,     8,    15,    16,    17,    18,    58,    50,
      51,    39,     5,     6,    36,    57,    57,    37,    59,    60,
      61,    14,    63,    38,    55,    37,    19,    61,    38,    22,
      39,    24,    56,    26,    27,    28,    29,    30,    55,    32,
       8,     9,    36,    36,    37,    38,   216,   190,   267,   265,
      39,    19,    20,    21,    22,     3,     1,    50,    51,   254,
     189,    37,   211,    -1,    57,    39,    59,    60,    61,    -1,
      63,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    -1,    54,    55,     8,     9,
      -1,    -1,    -1,     9,    -1,    63,    -1,    -1,    -1,    19,
      20,    21,    22,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
      46,    47,    48,    49,    54,    55,     8,     9,    54,    55,
      -1,     9,    -1,    63,    -1,    -1,    -1,    19,    20,    21,
      22,    19,    20,    21,    22,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    39,    40,    22,
      42,    43,    44,    45,    46,    47,    48,    49,     8,     9,
      48,    49,    54,    55,    -1,    -1,    54,    55,    60,    19,
      20,    21,    22,    -1,    -1,    48,    49,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
       8,     9,    -1,    -1,    54,    55,    -1,    -1,    58,    -1,
      -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,     8,     9,    -1,    -1,    54,    55,    -1,    -1,
      58,    -1,    -1,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,     8,     9,    -1,    -1,    54,    55,
      -1,    -1,    58,    -1,    -1,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,     8,     9,    -1,    -1,
      54,    55,    56,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,     8,     9,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
       8,     9,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    19,    -1,    -1,    22,    54,    55,    40,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,     9,    36,
      37,    38,    54,    55,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,     9,    50,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    19,    20,    21,    22,    63,    -1,    -1,    40,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    54,    55,    -1,    -1,    44,    45,    46,
      47,    48,    49,     9,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,     9,    19,    20,    21,    22,    -1,    -1,    -1,
       9,    -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      19,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    19,    -1,    -1,    22,    54,    55,
      47,    48,    49,    -1,    -1,    -1,    -1,    54,    55,    48,
      49,    36,    37,    38,    -1,    54,    55,    -1,    -1,    19,
      -1,    -1,    22,    -1,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    60,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,     0,     5,     6,    14,    19,    22,    24,    26,
      27,    28,    29,    30,    32,    36,    37,    38,    50,    51,
      57,    59,    60,    63,    69,    73,    80,    92,    94,    95,
      96,    97,    98,   101,   103,   105,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   123,
     124,   125,   127,   128,   131,   132,    10,    11,    12,    13,
      37,    93,   129,    99,   102,    37,   127,   127,   127,    37,
     132,   127,    57,    62,    41,    57,   127,   127,   127,    37,
      15,    16,    74,    81,     8,    97,    97,   127,    97,    97,
      97,   123,   110,   123,    69,    92,   125,   127,   127,    63,
     123,   123,    29,    77,    97,   129,     8,     9,    19,    20,
      21,    22,    39,    40,    42,    43,    44,    45,    46,    47,
      48,    49,    54,    55,    97,   127,   133,   129,    54,    60,
      38,   129,    97,    97,   127,    36,    58,    57,   104,   106,
       3,     4,    75,    76,    17,    18,    79,    60,    89,   127,
      97,    25,    63,    63,   127,    57,    61,    69,    96,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,    58,    37,    37,   126,
       7,   100,     8,    58,    37,    66,    67,    68,   129,   129,
      60,   129,    78,    83,    84,   129,   130,    78,    90,   123,
     127,    41,    41,    56,    39,    61,    37,    97,    37,   132,
      34,   121,   122,     8,    39,    58,    39,    58,     8,   107,
     107,    77,    57,    58,    39,    39,    62,    82,    93,    36,
      87,    88,    58,   127,   127,    37,   122,    36,    38,    57,
      38,    67,    82,    82,    61,    57,    72,    78,   129,    36,
      37,    55,    85,    86,    39,    91,    56,    38,    70,    71,
      82,    36,    56,    87,    61,    39,    58,    56,    70,    55,
      85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    65,    65,    66,    66,    67,    67,    67,
      68,    68,    68,    69,    69,    70,    71,    71,    72,    72,
      74,    73,    75,    75,    75,    76,    77,    77,    78,    79,
      79,    81,    80,    80,    80,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    86,    87,    88,    88,
      90,    91,    89,    92,    92,    92,    93,    93,    93,    93,
      94,    95,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    97,    99,    98,   100,   100,   102,   101,   104,   103,
     106,   105,   107,   107,   108,   109,   110,   110,   110,   111,
     112,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   121,   122,   123,   124,   125,   126,   126,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   132,   133,   133
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     3,     2,
       0,     1,     3,     0,     5,     1,     1,     3,     0,     3,
       0,     6,     4,     1,     1,     3,     0,     2,     3,     1,
       1,     0,     4,     3,     2,     1,     2,     2,     0,     1,
       1,     3,     3,     4,     0,     1,     2,     1,     1,     3,
       0,     0,     5,     1,     3,     3,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       2,     1,     0,     5,     2,     0,     0,     5,     0,     6,
       0,     6,     0,     1,     2,     3,     2,     2,     2,     1,
       3,     3,     2,     4,     2,     2,     1,     2,     5,     5,
       1,     2,     1,     3,     1,     5,     1,     3,     1,     3,
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
        case 2:
#line 100 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1656 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 101 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1663 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 102 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1670 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1678 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 107 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1687 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 112 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1695 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 114 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1703 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1711 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1719 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 122 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1727 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1735 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation(sym_null, nullptr);
}
#line 1743 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 130 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1751 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 134 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1759 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 138 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1767 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1775 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 144 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1783 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 146 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1791 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1797 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1805 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 154 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1815 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 163 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1823 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 167 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1830 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 168 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1837 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1853 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 183 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1859 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 183 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_LOCAL;}
#line 1865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 185 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1871 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 185 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  bool is_local = ((yyvsp[-1].id) == K_LOCAL);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
    if (is_local) {
      vd->SetIsLocal(true);
    }
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1886 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 194 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1893 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1900 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 198 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 1908 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 200 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 1916 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 202 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 1924 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 206 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1933 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 209 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1941 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 213 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1957 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 223 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1969 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 231 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 1978 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 234 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 1987 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 239 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 1995 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 241 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2003 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2013 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 249 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2021 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2031 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 257 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2040 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2046 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2052 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2060 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 266 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2069 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2083 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 277 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2101 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 291 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2109 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 293 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2117 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 295 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2125 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 297 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2133 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 302 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2140 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2148 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2156 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2164 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2171 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2178 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2185 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2193 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 318 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2201 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 320 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2208 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2215 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 322 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2222 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 323 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2229 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2236 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 325 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2243 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 326 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2251 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 330 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2258 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 331 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2265 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2272 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2280 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2286 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2294 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 344 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2302 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 346 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2310 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 350 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2316 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 350 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2324 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 354 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2330 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 354 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2338 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2344 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2352 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 362 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2359 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 363 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2367 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 367 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2376 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 372 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2386 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 378 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2396 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 382 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2405 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2414 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 390 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
}
#line 2422 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 394 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2430 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 396 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2438 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 400 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2447 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 405 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2466 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2479 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 429 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2489 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 435 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2500 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 442 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2508 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 446 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2520 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 454 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2527 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 457 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2534 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 458 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2541 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 461 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2548 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2556 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2565 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 473 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2573 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 477 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2581 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 479 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2589 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 483 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2598 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 486 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2606 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 488 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2614 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 490 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2622 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 492 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2630 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 494 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2638 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 496 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2646 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 498 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2654 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 500 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2662 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 502 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2670 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 504 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2678 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 506 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2686 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 508 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2694 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 510 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2702 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 512 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2710 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 514 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2718 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 516 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2726 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 518 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2734 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 520 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2742 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 522 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2750 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 524 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2758 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 526 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2766 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 528 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2774 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 530 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2782 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 532 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2790 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 534 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2798 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 536 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2807 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 539 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2816 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 544 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2824 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 546 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2833 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 551 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2841 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 553 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2849 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 557 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2857 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 559 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 563 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 567 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2882 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 572 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2890 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 574 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2898 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2902 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 578 "src/fe/parser.ypp" /* yacc.c:1906  */

