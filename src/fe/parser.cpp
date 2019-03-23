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
    K_ADD_SUB = 273,
    K_LG_COMPARE = 274,
    K_EQ_COMPARE = 275,
    K_INC_DEC = 276,
    K_CONST = 277,
    K_IF = 278,
    K_ELSE = 279,
    K_RETURN = 280,
    K_GOTO = 281,
    K_FOR = 282,
    K_WHILE = 283,
    K_DO = 284,
    K_CONTINUE = 285,
    K_SWITCH = 286,
    K_CASE = 287,
    K_DEFAULT = 288,
    K_BREAK = 289,
    NUM = 290,
    SYM = 291,
    STR = 292,
    K_LOGIC_OR = 293,
    K_LOGIC_AND = 294,
    K_BIT_CONCAT = 295,
    SIGN = 296,
    ADDRESS = 297
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
#define K_ADD_SUB 273
#define K_LG_COMPARE 274
#define K_EQ_COMPARE 275
#define K_INC_DEC 276
#define K_CONST 277
#define K_IF 278
#define K_ELSE 279
#define K_RETURN 280
#define K_GOTO 281
#define K_FOR 282
#define K_WHILE 283
#define K_DO 284
#define K_CONTINUE 285
#define K_SWITCH 286
#define K_CASE 287
#define K_DEFAULT 288
#define K_BREAK 289
#define NUM 290
#define SYM 291
#define STR 292
#define K_LOGIC_OR 293
#define K_LOGIC_AND 294
#define K_BIT_CONCAT 295
#define SIGN 296
#define ADDRESS 297

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
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 228 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   821

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    61,     2,     2,    46,     2,
      56,    57,    47,     2,    38,     2,    53,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    62,
       2,     2,     2,    39,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,    44,    60,    50,     2,     2,     2,
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
      35,    36,    37,    41,    42,    43,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    98,    99,   102,   104,   109,   111,   113,
     117,   119,   121,   125,   127,   131,   135,   137,   141,   143,
     147,   147,   151,   158,   158,   160,   164,   165,   168,   180,
     180,   185,   186,   189,   191,   193,   197,   200,   204,   214,
     222,   225,   230,   232,   234,   240,   244,   248,   253,   253,
     253,   257,   260,   268,   282,   284,   286,   288,   293,   296,
     300,   302,   304,   305,   306,   307,   309,   311,   312,   313,
     314,   315,   316,   317,   319,   320,   321,   322,   323,   327,
     331,   331,   335,   337,   341,   341,   345,   345,   349,   349,
     353,   354,   358,   363,   369,   373,   376,   381,   385,   387,
     391,   396,   411,   420,   426,   433,   437,   445,   448,   449,
     452,   455,   459,   464,   468,   470,   474,   477,   479,   481,
     483,   485,   487,   489,   491,   493,   495,   497,   499,   501,
     503,   505,   507,   509,   511,   513,   515,   517,   519,   521,
     523,   525,   527,   530,   535,   537,   542,   544,   548,   550,
     554,   558,   563,   565
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_AS", "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING", "K_OBJECT",
  "K_THREAD", "K_CHANNEL", "K_MAILBOX", "K_VAR", "K_ADD_SUB",
  "K_LG_COMPARE", "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE",
  "K_RETURN", "K_GOTO", "K_FOR", "K_WHILE", "K_DO", "K_CONTINUE",
  "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM", "STR", "','",
  "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'",
  "'&'", "'*'", "'/'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['",
  "']'", "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept",
  "input", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "RETURN_TYPE",
  "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@1", "FUNC_DECL_HEAD",
  "FUNC_DECL_NAME", "STMT_LIST", "VAR_DECL_TAIL", "VAR_DECL", "$@2",
  "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC",
  "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
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
     285,   286,   287,   288,   289,   290,   291,   292,    44,    63,
      58,   293,   294,   295,   124,    94,    38,    42,    47,    33,
     126,   296,   297,    46,    91,    93,    40,    41,    64,   123,
     125,    35,    59
};
# endif

#define YYPACT_NINF -141

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-141)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -141,   127,  -141,   252,  -141,  -141,   765,   765,   765,  -141,
       0,    -9,   765,  -141,    23,    27,    37,  -141,   765,   765,
     765,    48,  -141,  -141,   193,  -141,    88,    59,  -141,   728,
    -141,  -141,  -141,    59,    59,    59,    80,   -17,  -141,    20,
     765,    73,  -141,    80,  -141,    80,   123,  -141,  -141,  -141,
    -141,   -19,   248,  -141,   765,  -141,  -141,  -141,  -141,  -141,
    -141,   133,   -30,   122,   133,   114,    33,    33,   629,   112,
      59,  -141,   629,   765,   137,  -141,  -141,    33,    33,   342,
     124,  -141,  -141,     8,   161,   761,  -141,  -141,   248,  -141,
    -141,  -141,   160,  -141,  -141,  -141,   125,   133,   295,   629,
     765,  -141,  -141,   136,   176,  -141,   140,   765,   765,   765,
     765,   765,  -141,   765,   765,   765,   765,   765,   765,   765,
     765,   765,   765,   765,   765,  -141,   629,   141,   140,   164,
     178,   199,    11,  -141,  -141,   383,  -141,  -141,   179,   133,
     133,  -141,  -141,    39,   133,   133,  -141,  -141,   629,  -141,
    -141,  -141,  -141,   424,   765,  -141,    24,  -141,   645,   113,
      76,   170,   358,   645,   588,   660,   691,   707,   299,   722,
      12,    33,    33,  -141,   506,  -141,  -141,  -141,    47,   180,
      59,   183,   187,   214,    87,  -141,   100,    29,    29,  -141,
      36,  -141,   173,   189,   140,    61,  -141,   196,    80,   465,
     765,   765,  -141,   197,  -141,  -141,  -141,   114,  -141,  -141,
     187,  -141,    91,   202,  -141,   179,  -141,  -141,    40,    40,
     223,  -141,   184,   133,   133,   107,   188,  -141,  -141,  -141,
     205,  -141,  -141,   676,   547,  -141,  -141,  -141,  -141,   208,
    -141,  -141,  -141,  -141,  -141,    40,  -141,  -141,   140,  -141,
    -141,    65,  -141,  -141,   196,   195,  -141,  -141,  -141,   108,
    -141,   192,  -141,  -141,  -141,    40,  -141,   207,  -141,   218,
    -141
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    13,     1,     0,    80,    84,     0,     0,     0,    59,
       0,     0,     0,   104,     0,   144,   116,   142,     0,     0,
       0,     0,   112,    79,    20,     3,    51,     0,    74,     0,
       4,    60,    75,     0,     0,     0,     0,     0,    68,    13,
       0,     0,    69,     0,    70,     0,     0,    71,    72,    67,
      26,     0,     0,   143,   152,   122,    54,    55,    57,    56,
     146,     0,     0,     0,     0,   116,   140,   139,    92,     0,
       0,    97,   102,     0,     0,    58,   150,   123,   124,     0,
       0,    86,    88,     0,     0,     0,    73,    66,     0,    76,
      77,    78,    94,    96,    95,    29,     0,     0,     0,   100,
       0,   103,   105,     0,    13,    62,    32,     0,     0,     0,
       0,     0,   138,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,   153,     0,    31,     0,
       0,    83,     0,    64,    63,     0,   145,   117,    10,     0,
       0,    23,    24,     0,    36,     0,    48,    53,    52,    65,
      93,    99,    98,     0,     0,   111,    29,    27,   129,   128,
     125,   130,   131,   120,     0,   136,   137,   132,   134,   135,
     133,   126,   127,   121,     0,   151,   147,   114,     0,     0,
       0,     0,     0,     0,     0,    11,     0,    90,    90,    26,
       0,    38,     0,    37,   148,     0,    30,     0,     0,     0,
       0,     0,   118,     0,   113,    82,    81,     0,    85,   110,
     107,   108,     0,     0,     9,     0,    14,    91,     0,     0,
      13,    25,    18,     0,     0,     0,    42,    33,    45,    46,
      49,   101,   106,   141,     0,   115,   109,     8,     7,     0,
       6,    12,    87,    89,    21,     0,    22,    39,   149,    34,
      35,     0,    43,    28,     0,     0,   119,     5,    16,     0,
      15,     0,    44,    47,    50,     0,    19,    40,    17,     0,
      41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,  -141,    55,  -141,     7,     6,  -141,  -141,  -141,
    -141,  -141,  -141,    85,  -140,  -141,  -141,  -128,  -141,  -141,
       9,  -141,    21,  -141,  -141,  -141,  -141,   238,   275,  -141,
    -141,   279,    -7,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,    96,  -141,  -141,   260,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,    89,   -27,  -141,
     259,  -141,    -5,  -141,    -3,  -141,  -141,    -6,  -141
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   184,   185,   186,   156,   258,   259,   246,    25,
      83,   143,   144,   104,   191,    26,    84,   260,   192,   193,
     252,   253,   229,   230,   147,   197,   255,    27,   227,    28,
      29,   157,    31,    32,    63,   180,    33,    64,    34,   139,
      35,   140,   218,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,   210,   211,    49,    50,
      51,   178,    52,    53,   194,   195,    54,    55,   127
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    66,    67,    68,    70,   196,     8,    72,    24,    92,
      94,   141,   142,    77,    78,    79,   101,    60,   102,   181,
      86,   108,    87,   129,    88,     3,    89,    90,    91,   130,
     109,   110,   111,   112,    98,    99,    69,   217,     6,    81,
      82,     7,    22,    23,   105,   125,    95,    71,   106,   126,
      56,    57,    58,    59,   112,    15,    65,    17,   128,   121,
     122,   132,   133,   134,   129,   123,   124,   226,   135,    18,
      19,    56,    57,    58,    59,    60,    20,    75,    21,    73,
     148,   149,   129,   247,    80,   203,   123,   124,    74,   129,
     242,   243,   221,    76,   106,   153,    85,   112,   189,   224,
     261,   225,   158,   159,   160,   161,   162,   204,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     262,    23,   225,   121,   122,   213,   237,     2,   238,   123,
     124,   109,     3,     4,   112,   100,   187,   188,   215,    22,
     190,     5,   249,   250,   214,     6,   265,   239,     7,   199,
       8,   103,     9,    10,    11,    12,    13,   216,    14,   131,
     121,   122,    15,    16,    17,   266,   123,   124,    76,    60,
      76,   231,   136,   206,    23,   208,    18,    19,   145,   108,
     138,     3,     4,    20,   150,    21,    22,   151,   109,    23,
       5,   112,   154,   129,     6,   233,   234,     7,   175,     8,
     176,     9,    10,    11,    12,    13,   179,    14,    81,    82,
     -29,    15,    16,    17,   177,   183,   205,   121,   122,   207,
     209,   248,   212,   123,   124,    18,    19,   223,     3,     4,
     222,   228,    20,   235,    21,    22,   155,     5,    23,   240,
     245,     6,   251,   254,     7,   257,     8,   267,     9,    10,
      11,    12,    13,   261,    14,   264,   107,   108,    15,    16,
      17,   269,    56,    57,    58,    59,   109,   110,   111,   112,
     241,   268,    18,    19,   220,   263,   270,    96,    61,    20,
      30,    21,    22,   244,   219,    23,   113,   114,    60,   115,
     116,   117,   118,   119,   120,   121,   122,    93,    97,   236,
       0,   123,   124,   107,   108,     0,     0,     0,   108,     0,
      23,     0,     0,   109,   110,   111,   112,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   119,   120,   121,   122,   123,   124,
     107,   108,   123,   124,     0,     0,     0,   152,     0,     0,
     109,   110,   111,   112,     0,     0,     0,   108,     0,     0,
       0,     0,     0,     0,     0,     0,   109,   110,     0,   112,
     113,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     122,   107,   108,     0,     0,   123,   124,     0,     0,   137,
       0,   109,   110,   111,   112,   121,   122,     0,     0,     0,
       0,   123,   124,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,     0,   115,   116,   117,   118,   119,   120,
     121,   122,   107,   108,     0,     0,   123,   124,     0,     0,
     182,     0,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   122,   107,   108,     0,     0,   123,   124,     0,
       0,   198,     0,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,     0,   115,   116,   117,   118,
     119,   120,   121,   122,   107,   108,     0,     0,   123,   124,
       0,     0,   232,     0,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   201,   115,   116,   117,
     118,   119,   120,   121,   122,   107,   108,     0,     0,   123,
     124,   202,     0,     0,     0,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   122,   107,   108,     0,     0,
     123,   124,   256,     0,     0,     0,   109,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   200,   115,
     116,   117,   118,   119,   120,   121,   122,   107,   108,     0,
       0,   123,   124,     0,     0,     0,     0,   109,   110,   111,
     112,     0,     0,   107,   108,     0,     0,     0,     0,     0,
       0,     0,     0,   109,   110,   111,   112,   113,   114,   108,
     115,   116,   117,   118,   119,   120,   121,   122,   109,   110,
     111,   112,   123,   124,   114,   108,   115,   116,   117,   118,
     119,   120,   121,   122,   109,   110,   111,   112,   123,   124,
     108,     0,   116,   117,   118,   119,   120,   121,   122,   109,
     110,   111,   112,   123,   124,   114,   108,   115,   116,   117,
     118,   119,   120,   121,   122,   109,   110,   111,   112,   123,
     124,   108,     0,     0,   117,   118,   119,   120,   121,   122,
     109,   110,   111,   112,   123,   124,     6,     0,     0,     7,
       0,   118,   119,   120,   121,   122,     0,     0,     0,     0,
     123,   124,     0,    15,    65,    17,     0,     0,   120,   121,
     122,     0,     0,     0,     0,   123,   124,    18,    19,     6,
       0,     0,     7,     6,    20,     0,     7,     0,     0,     0,
      23,     0,     0,     0,     0,     0,    15,    65,    17,     0,
      15,    65,    17,     0,     0,     0,     0,     0,     0,     0,
      18,    19,     0,     0,    18,    19,     0,    20,     0,     0,
     146,    20
};

static const yytype_int16 yycheck[] =
{
       3,     6,     7,     8,    10,   145,    23,    12,     1,    36,
      37,     3,     4,    18,    19,    20,    43,    36,    45,     8,
      27,     9,    29,    53,    29,     5,    33,    34,    35,    59,
      18,    19,    20,    21,    39,    40,    36,     8,    18,    15,
      16,    21,    59,    62,    51,    52,    39,    56,    51,    54,
      10,    11,    12,    13,    21,    35,    36,    37,    61,    47,
      48,    64,    69,    70,    53,    53,    54,   195,    73,    49,
      50,    10,    11,    12,    13,    36,    56,    40,    58,    56,
      85,    88,    53,   223,    36,    38,    53,    54,    61,    53,
     218,   219,    56,    56,    97,   100,     8,    21,    59,    38,
      35,    61,   107,   108,   109,   110,   111,    60,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      55,    62,    61,    47,    48,    38,    35,     0,    37,    53,
      54,    18,     5,     6,    21,    62,   139,   140,    38,    59,
     143,    14,    35,    36,    57,    18,    38,    56,    21,   154,
      23,    28,    25,    26,    27,    28,    29,    57,    31,    37,
      47,    48,    35,    36,    37,    57,    53,    54,    56,    36,
      56,   198,    35,   180,    62,   181,    49,    50,    17,     9,
      56,     5,     6,    56,    24,    58,    59,    62,    18,    62,
      14,    21,    56,    53,    18,   200,   201,    21,    57,    23,
      36,    25,    26,    27,    28,    29,     7,    31,    15,    16,
      17,    35,    36,    37,    36,    36,    36,    47,    48,    36,
      33,   224,     8,    53,    54,    49,    50,    38,     5,     6,
      57,    35,    56,    36,    58,    59,    60,    14,    62,    37,
      56,    18,    54,    38,    21,    37,    23,    55,    25,    26,
      27,    28,    29,    35,    31,    60,     8,     9,    35,    36,
      37,    54,    10,    11,    12,    13,    18,    19,    20,    21,
     215,   265,    49,    50,   189,   254,   267,    39,     3,    56,
       1,    58,    59,    60,   188,    62,    38,    39,    36,    41,
      42,    43,    44,    45,    46,    47,    48,    37,    39,   210,
      -1,    53,    54,     8,     9,    -1,    -1,    -1,     9,    -1,
      62,    -1,    -1,    18,    19,    20,    21,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    45,    46,    47,    48,    53,    54,
       8,     9,    53,    54,    -1,    -1,    -1,    62,    -1,    -1,
      18,    19,    20,    21,    -1,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    19,    -1,    21,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,     8,     9,    -1,    -1,    53,    54,    -1,    -1,    57,
      -1,    18,    19,    20,    21,    47,    48,    -1,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,     8,     9,    -1,    -1,    53,    54,    -1,    -1,
      57,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,     8,     9,    -1,    -1,    53,    54,    -1,
      -1,    57,    -1,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,     8,     9,    -1,    -1,    53,    54,
      -1,    -1,    57,    -1,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     8,     9,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,     8,     9,    -1,    -1,
      53,    54,    55,    -1,    -1,    -1,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,     8,     9,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    18,    19,    20,
      21,    -1,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    20,    21,    38,    39,     9,
      41,    42,    43,    44,    45,    46,    47,    48,    18,    19,
      20,    21,    53,    54,    39,     9,    41,    42,    43,    44,
      45,    46,    47,    48,    18,    19,    20,    21,    53,    54,
       9,    -1,    42,    43,    44,    45,    46,    47,    48,    18,
      19,    20,    21,    53,    54,    39,     9,    41,    42,    43,
      44,    45,    46,    47,    48,    18,    19,    20,    21,    53,
      54,     9,    -1,    -1,    43,    44,    45,    46,    47,    48,
      18,    19,    20,    21,    53,    54,    18,    -1,    -1,    21,
      -1,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      53,    54,    -1,    35,    36,    37,    -1,    -1,    46,    47,
      48,    -1,    -1,    -1,    -1,    53,    54,    49,    50,    18,
      -1,    -1,    21,    18,    56,    -1,    21,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    50,    -1,    -1,    49,    50,    -1,    56,    -1,    -1,
      59,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    64,     0,     5,     6,    14,    18,    21,    23,    25,
      26,    27,    28,    29,    31,    35,    36,    37,    49,    50,
      56,    58,    59,    62,    68,    72,    78,    90,    92,    93,
      94,    95,    96,    99,   101,   103,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   121,
     122,   123,   125,   126,   129,   130,    10,    11,    12,    13,
      36,    91,   127,    97,   100,    36,   125,   125,   125,    36,
     130,    56,   125,    56,    61,    40,    56,   125,   125,   125,
      36,    15,    16,    73,    79,     8,    95,    95,   125,    95,
      95,    95,   121,   108,   121,    68,    90,   123,   125,   125,
      62,   121,   121,    28,    76,    95,   127,     8,     9,    18,
      19,    20,    21,    38,    39,    41,    42,    43,    44,    45,
      46,    47,    48,    53,    54,    95,   125,   131,   127,    53,
      59,    37,   127,    95,    95,   125,    35,    57,    56,   102,
     104,     3,     4,    74,    75,    17,    59,    87,   125,    95,
      24,    62,    62,   125,    56,    60,    68,    94,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,    57,    36,    36,   124,     7,
      98,     8,    57,    36,    65,    66,    67,   127,   127,    59,
     127,    77,    81,    82,   127,   128,    77,    88,    57,   125,
      40,    40,    55,    38,    60,    36,    95,    36,   130,    33,
     119,   120,     8,    38,    57,    38,    57,     8,   105,   105,
      76,    56,    57,    38,    38,    61,    80,    91,    35,    85,
      86,   121,    57,   125,   125,    36,   120,    35,    37,    56,
      37,    66,    80,    80,    60,    56,    71,    77,   127,    35,
      36,    54,    83,    84,    38,    89,    55,    37,    69,    70,
      80,    35,    55,    85,    60,    38,    57,    55,    69,    54,
      83
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    64,    64,    65,    65,    66,    66,    66,
      67,    67,    67,    68,    68,    69,    70,    70,    71,    71,
      73,    72,    74,    74,    74,    75,    76,    76,    77,    79,
      78,    78,    78,    80,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    84,    85,    86,    86,    88,    89,
      87,    90,    90,    90,    91,    91,    91,    91,    92,    93,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      97,    96,    98,    98,   100,    99,   102,   101,   104,   103,
     105,   105,   106,   107,   108,   108,   108,   109,   110,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   119,
     120,   121,   122,   123,   124,   124,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   130,   131,   131
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     3,     2,
       0,     1,     3,     0,     5,     1,     1,     3,     0,     3,
       0,     6,     4,     1,     1,     3,     0,     2,     3,     0,
       4,     3,     2,     1,     2,     2,     0,     1,     1,     3,
       3,     4,     0,     1,     2,     1,     1,     3,     0,     0,
       5,     1,     3,     3,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     2,     1,
       0,     5,     2,     0,     0,     5,     0,     6,     0,     6,
       0,     1,     2,     3,     2,     2,     2,     2,     3,     3,
       2,     5,     2,     2,     1,     2,     5,     5,     1,     2,
       1,     3,     1,     5,     1,     3,     1,     3,     4,     6,
       3,     3,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     5,     1,     1,     1,     3,     1,     3,     1,     3,
       2,     3,     0,     1
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
#line 97 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1645 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 98 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1652 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 99 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 102 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1667 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 104 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1676 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 109 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1684 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 111 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1692 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 113 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1700 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 117 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1708 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 119 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1716 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 121 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1724 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 125 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation(sym_null, nullptr);
}
#line 1732 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 127 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1740 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 131 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1748 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1756 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 137 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1764 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 141 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1772 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 143 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1780 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 147 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1786 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 147 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1794 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 151 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1804 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 160 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1812 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 164 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1819 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 165 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1826 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 168 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1842 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1848 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1859 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 185 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1866 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 186 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 189 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 1881 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 191 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 1889 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 193 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 1897 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1906 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 200 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1914 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 204 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1930 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 214 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1942 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 222 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 1951 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 225 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 1960 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 230 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 1968 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 232 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 1976 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 234 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 1986 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 240 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1994 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 244 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2004 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 248 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2013 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2019 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2025 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2033 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 257 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2042 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 260 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2056 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 268 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2074 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2082 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 284 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2090 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 286 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2098 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 288 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2106 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 293 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2113 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 296 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2121 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 300 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2129 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 302 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2137 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 304 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2144 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2151 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 306 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2158 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2166 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2174 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2181 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 312 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2188 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2195 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2202 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2209 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2216 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 317 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2224 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2231 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 322 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2238 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 323 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2245 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 327 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2253 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 331 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2259 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 331 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2267 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 335 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2275 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 337 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2283 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 341 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2289 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 341 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2297 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 345 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2303 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 345 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2311 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 349 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2317 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 349 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2325 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 353 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2332 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 354 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2340 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2349 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 363 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2359 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2369 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2378 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 376 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2387 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 381 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
}
#line 2395 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2403 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 387 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2411 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 391 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2420 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 396 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2439 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 411 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2452 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2462 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 426 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2473 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 433 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2481 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 437 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2493 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 445 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2500 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 448 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2507 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 449 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2514 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 452 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2521 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 455 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2529 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 459 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2538 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2546 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2554 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 470 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2562 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2571 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 477 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2579 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 479 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2587 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 481 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2595 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 483 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2603 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 485 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2611 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 487 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2619 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 489 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2627 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 491 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2635 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 493 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2643 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 495 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2651 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 497 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 499 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2667 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2675 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 503 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2683 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 505 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2691 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 507 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2699 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 509 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2707 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 511 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2715 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 513 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2723 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 515 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2731 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 517 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2739 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2747 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2755 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 523 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2763 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2771 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2780 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 530 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2789 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2797 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 537 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2806 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 542 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2814 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 544 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2822 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 548 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2830 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 550 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2838 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 554 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2846 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 558 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2855 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 563 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2863 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 565 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2871 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2875 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 569 "src/fe/parser.ypp" /* yacc.c:1906  */

