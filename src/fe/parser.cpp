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
    K_SPAWN = 282,
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
#define K_SPAWN 282
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
  class AnnotationValue *annotation_value;
  class AnnotationValueSet *annotation_value_set;

#line 227 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 244 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   861

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  147
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

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
       2,     2,     2,    48,     2,    60,     2,     2,    46,     2,
      55,    56,    47,     2,    38,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    61,
       2,     2,     2,    39,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    44,    59,    49,     2,     2,     2,
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
      35,    36,    37,    41,    42,    43,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    97,    98,   101,   103,   108,   110,   114,
     116,   118,   122,   124,   128,   132,   134,   138,   140,   144,
     144,   148,   155,   155,   157,   161,   162,   165,   177,   177,
     182,   183,   186,   188,   190,   192,   197,   200,   204,   214,
     222,   224,   228,   230,   234,   238,   242,   247,   247,   247,
     251,   254,   262,   276,   278,   280,   282,   287,   290,   294,
     296,   298,   299,   300,   301,   303,   305,   306,   307,   308,
     309,   310,   311,   313,   314,   314,   316,   316,   318,   319,
     320,   324,   328,   328,   332,   332,   336,   336,   340,   345,
     351,   355,   358,   363,   368,   373,   388,   397,   403,   410,
     414,   422,   425,   426,   429,   432,   436,   441,   445,   447,
     451,   454,   456,   458,   460,   462,   464,   466,   468,   470,
     472,   474,   476,   478,   480,   482,   484,   486,   488,   490,
     492,   494,   496,   498,   500,   502,   504,   507,   512,   514,
     519,   521,   525,   527,   531,   535,   540,   542
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
  "K_RETURN", "K_GOTO", "K_FOR", "K_SPAWN", "K_WHILE", "K_DO",
  "K_CONTINUE", "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM",
  "STR", "','", "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT",
  "'|'", "'^'", "'&'", "'*'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'",
  "'['", "']'", "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept",
  "input", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "RETURN_TYPE",
  "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@1", "FUNC_DECL_HEAD",
  "FUNC_DECL_NAME", "STMT_LIST", "VAR_DECL_TAIL", "VAR_DECL", "$@2",
  "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC",
  "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "$@3", "$@4", "VAR_DECL_STMT", "TYPE_NAME", "LABEL",
  "RETURN", "STMT", "$@5", "$@6", "EOS", "THREAD_DECL_STMT", "$@7",
  "CHANNEL_DECL_STMT", "$@8", "MAILBOX_DECL_STMT", "$@9", "IF_COND_PART",
  "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD", "FOR_COND_PART", "FOR_STMT",
  "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD", "DO_WHILE_BODY",
  "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE", "BLOCK",
  "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "EXPR", "NUM_EXPR", "VAR",
  "VAR_LIST", "FUNCALL_HEAD", "FUNCALL", "ARG_LIST", YY_NULLPTR
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
      58,   293,   294,   295,   124,    94,    38,    42,    33,   126,
     296,   297,    46,    91,    93,    40,    41,    64,   123,   125,
      35,    59
};
# endif

#define YYPACT_NINF -149

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-149)))

#define YYTABLE_NINF -29

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -149,   159,  -149,   126,  -149,  -149,  -149,  -149,   806,   806,
      -1,  -149,    35,    36,  -149,    42,  -149,    52,    30,   -13,
    -149,   806,   806,   806,   806,    94,  -149,  -149,   129,  -149,
     139,    87,  -149,   748,  -149,  -149,    87,    87,    87,    95,
      21,  -149,   806,    89,  -149,    95,  -149,    95,   124,  -149,
    -149,  -149,  -149,   -15,    81,  -149,   806,  -149,  -149,  -149,
    -149,  -149,  -149,   118,    34,   119,   118,   118,   118,   100,
      28,    28,   806,    32,    87,   806,   121,   806,   806,   125,
    -149,  -149,    28,    28,    28,   342,   106,    26,   147,   782,
    -149,  -149,    81,  -149,  -149,  -149,   143,  -149,  -149,   587,
     806,  -149,  -149,   114,   213,  -149,   128,   806,   806,   806,
     806,   806,  -149,   806,   806,   806,   806,   806,   806,   806,
     806,   806,   806,   806,  -149,   587,   133,   128,   141,   146,
      87,     5,     7,    25,   358,  -149,  -149,   295,   100,    87,
     399,   415,  -149,  -149,   155,  -149,  -149,   -14,   118,   118,
    -149,  -149,   587,  -149,  -149,   456,   806,  -149,  -149,  -149,
     628,   158,     0,   150,   205,   628,   571,   683,   696,   700,
     714,   754,   761,    28,  -149,   513,  -149,  -149,  -149,     3,
    -149,   121,    14,    14,  -149,  -149,  -149,  -149,   160,   185,
      -7,  -149,    83,  -149,    88,  -149,   142,   163,   128,    -2,
    -149,   169,    95,   472,   806,   806,  -149,   173,  -149,  -149,
      14,    47,  -149,  -149,  -149,  -149,   160,  -149,    92,   175,
    -149,   155,  -149,   270,  -149,   166,   118,   118,   162,  -149,
    -149,   191,  -149,  -149,   643,   530,  -149,  -149,  -149,  -149,
    -149,  -149,   194,  -149,  -149,  -149,    14,  -149,  -149,   128,
     -20,  -149,  -149,   169,   177,  -149,  -149,  -149,    93,  -149,
     178,  -149,  -149,  -149,    14,  -149,  -149,  -149
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    12,     1,     0,    74,    82,    84,    86,     0,     0,
       0,    58,     0,     0,    76,     0,    98,     0,   138,   110,
     136,     0,     0,     0,     0,     0,   106,    81,    19,     3,
      50,     0,    73,     0,     4,    59,     0,     0,     0,     0,
       0,    67,     0,     0,    68,     0,    69,     0,     0,    70,
      71,    66,    25,     0,     0,   137,   146,   116,    53,    54,
      56,    55,   140,     0,     0,     0,     0,     0,     0,   110,
     134,   133,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   144,   119,   117,   118,     0,     0,     0,     0,     0,
      72,    65,     0,    78,    79,    80,    90,    92,    91,    94,
       0,    97,    99,     0,    12,    61,    31,     0,     0,     0,
       0,     0,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,   147,     0,    30,     0,     0,
       0,     0,     0,     0,     0,    63,    62,     0,     0,     0,
       0,     0,   139,   111,     9,    22,    23,     0,    36,     0,
      47,    52,    51,    64,    89,     0,     0,   105,    28,    26,
     123,   122,   120,   124,   125,   114,     0,   130,   131,   126,
     128,   129,   127,   121,   115,     0,   145,   141,   108,     0,
      75,     0,     0,     0,    88,    93,    77,    96,     0,     0,
       0,    10,     0,    25,     0,    38,     0,    37,   142,     0,
      29,     0,     0,     0,     0,     0,   112,     0,   107,    83,
       0,     0,    85,    32,    87,   104,   101,   102,     0,     0,
       8,     0,    13,    12,    24,    17,     0,     0,    42,    44,
      45,    48,    95,   100,   135,     0,   109,    35,    33,    34,
     103,     7,     0,     6,    11,    20,     0,    21,    39,   143,
       0,    43,    27,     0,     0,   113,     5,    15,     0,    14,
       0,    40,    46,    49,     0,    18,    41,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -149,  -149,  -149,    13,  -149,   242,   -19,  -149,  -149,  -149,
    -149,  -149,  -149,    53,  -148,  -149,  -149,  -114,  -149,  -149,
    -149,  -149,    -6,  -149,  -149,  -149,  -149,  -149,   248,  -149,
    -149,   252,  -149,  -149,     2,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,   214,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,    39,   -34,  -149,  -149,  -149,    -5,
    -149,    -3,  -149,  -149,   -10,  -149
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   190,   191,   192,   158,   257,   258,   247,    29,
      87,   147,   148,   104,   195,    30,    88,   259,   196,   197,
     251,   252,   230,   231,   151,   201,   254,    31,   213,    32,
      33,   159,    65,    76,    35,    36,    66,    37,    67,    38,
      68,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   216,   217,    51,    52,    53,   179,    54,
      55,   198,   199,    56,    57,   126
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   200,    74,    70,    71,    96,    98,    58,    59,    60,
      61,   101,   181,   102,   182,   260,    82,    83,    84,    85,
     112,    62,    62,    58,    59,    60,    61,    80,    92,   145,
     146,   219,   183,    90,   261,    91,   227,    99,    93,    94,
      95,   207,    81,    10,   193,   210,    27,   121,   112,   220,
     106,   125,   122,   123,    72,   105,   124,   128,   211,   128,
     127,   210,   208,   131,   132,   133,   139,   134,   212,   214,
     137,    73,   140,   141,   211,   135,   136,   128,   248,    26,
     122,   123,   238,   239,   152,   228,   128,    81,   107,   108,
      79,    75,   129,    27,   153,   155,   237,    77,   109,   110,
     111,   112,   160,   161,   162,   163,   164,    78,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   113,
     114,   221,   115,   116,   117,   118,   119,   120,   121,   241,
      86,   264,   180,   122,   123,    58,    59,    60,    61,   222,
     128,   186,    27,   224,   194,   -28,    89,   242,    27,   265,
     100,   203,   103,    26,    62,    81,   130,   138,   108,     2,
     142,   144,    62,   149,     3,     4,   154,   109,   232,   156,
     112,   209,     5,     6,     7,   109,     8,   177,   112,     9,
     128,    10,   178,    11,    12,    13,    14,    15,    16,   176,
      17,   189,   218,   215,    18,    19,    20,   121,   225,   234,
     235,   226,   122,   123,   229,   121,    21,    22,    23,   236,
     122,   123,   243,   108,    24,   250,    25,    26,     3,     4,
      27,   246,   109,   110,   249,   112,     5,     6,     7,   253,
       8,   256,   266,     9,   244,    10,   263,    11,    12,    13,
      14,    15,    16,    28,    17,   267,   223,   262,    18,    19,
      20,    63,   121,    34,    97,   240,     0,   122,   123,     0,
      21,    22,    23,     0,     0,     0,     0,     0,    24,     0,
      25,    26,   157,     0,    27,     3,     4,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     8,     0,     0,
       9,     0,    10,     0,    11,    12,    13,    14,    15,    16,
       0,    17,   107,   108,     0,    18,    19,    20,     0,     0,
       0,     0,   109,   110,   111,   112,     0,    21,    22,    23,
       0,     0,     0,     0,     0,    24,     0,    25,    26,   245,
       0,    27,     0,   113,   114,     0,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,   122,   123,   107,
     108,     0,     0,     0,     0,     0,   185,     0,     0,   109,
     110,   111,   112,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,   109,   110,   111,   112,     0,
     113,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,     0,     0,     0,   122,   123,   113,   114,   143,   115,
     116,   117,   118,   119,   120,   121,   107,   108,     0,     0,
     122,   123,     0,     0,   184,     0,   109,   110,   111,   112,
       0,     0,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   110,   111,   112,     0,   113,   114,     0,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,   122,   123,   113,   114,   187,   115,   116,   117,   118,
     119,   120,   121,   107,   108,     0,     0,   122,   123,     0,
       0,   188,     0,   109,   110,   111,   112,     0,     0,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,   109,
     110,   111,   112,     0,   113,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,     0,     0,     0,   122,   123,
     113,   114,   202,   115,   116,   117,   118,   119,   120,   121,
     107,   108,     0,     0,   122,   123,     0,     0,   233,     0,
     109,   110,   111,   112,     0,     0,     0,   107,   108,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   110,   111,
     112,   113,   114,   205,   115,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,   122,   123,   206,   113,   114,
       0,   115,   116,   117,   118,   119,   120,   121,   107,   108,
       0,     0,   122,   123,   255,     0,     0,     0,   109,   110,
     111,   112,     0,     0,   107,   108,     0,     0,     0,     0,
       0,     0,     0,     0,   109,   110,   111,   112,     0,   113,
     114,   204,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   122,   123,   113,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   107,   108,     0,     0,   122,
     123,     0,     0,     0,     0,   109,   110,   111,   112,     0,
       0,   108,     0,     0,     0,     0,     0,     0,     0,     0,
     109,   110,   111,   112,     0,     0,     0,   114,     0,   115,
     116,   117,   118,   119,   120,   121,     0,     0,     0,     0,
     122,   123,   114,     0,   115,   116,   117,   118,   119,   120,
     121,   108,     0,     0,     0,   122,   123,     0,     0,     0,
     109,   110,   111,   112,   108,     0,     0,     0,   108,     0,
       0,     0,     0,   109,   110,   111,   112,   109,   110,   111,
     112,     0,   108,     0,     0,   116,   117,   118,   119,   120,
     121,   109,   110,   111,   112,   122,   123,     0,     0,   117,
     118,   119,   120,   121,   118,   119,   120,   121,   122,   123,
       0,     0,   122,   123,     0,     0,     0,     0,     0,   119,
     120,   121,   108,     0,     0,     8,   122,   123,     9,   108,
       0,   109,   110,   111,   112,     0,     0,     0,   109,   110,
     111,   112,     0,    18,    69,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    22,    23,     0,     8,
     120,   121,     9,    24,     0,     0,   122,   123,   121,    27,
       0,     0,     0,   122,   123,     0,     0,    18,    69,    20,
       0,     0,     0,     8,     0,     0,     9,     0,     0,    21,
      22,    23,     0,     0,     0,     0,     0,    24,     0,     0,
     150,    18,    69,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
       0,    24
};

static const yytype_int16 yycheck[] =
{
       3,   149,    12,     8,     9,    39,    40,     9,    10,    11,
      12,    45,     7,    47,     7,    35,    21,    22,    23,    24,
      20,    36,    36,     9,    10,    11,    12,    40,    33,     3,
       4,    38,     7,    31,    54,    33,    38,    42,    36,    37,
      38,    38,    55,    22,    58,    47,    61,    47,    20,    56,
      53,    56,    52,    53,    55,    53,    54,    52,    60,    52,
      63,    47,    59,    66,    67,    68,    76,    72,   182,   183,
      75,    36,    77,    78,    60,    73,    74,    52,   226,    58,
      52,    53,    35,    36,    89,   199,    52,    55,     7,     8,
      60,    55,    58,    61,    92,   100,   210,    55,    17,    18,
      19,    20,   107,   108,   109,   110,   111,    55,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    38,
      39,    38,    41,    42,    43,    44,    45,    46,    47,    37,
      36,    38,   130,    52,    53,     9,    10,    11,    12,    56,
      52,   139,    61,    55,   147,    16,     7,    55,    61,    56,
      61,   156,    28,    58,    36,    55,    37,    36,     8,     0,
      35,    55,    36,    16,     5,     6,    23,    17,   202,    55,
      20,   181,    13,    14,    15,    17,    17,    36,    20,    20,
      52,    22,    36,    24,    25,    26,    27,    28,    29,    56,
      31,    36,     7,    33,    35,    36,    37,    47,    56,   204,
     205,    38,    52,    53,    35,    47,    47,    48,    49,    36,
      52,    53,    37,     8,    55,    53,    57,    58,     5,     6,
      61,    55,    17,    18,   227,    20,    13,    14,    15,    38,
      17,    37,    54,    20,   221,    22,    59,    24,    25,    26,
      27,    28,    29,     1,    31,   264,   193,   253,    35,    36,
      37,     3,    47,     1,    40,   216,    -1,    52,    53,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      57,    58,    59,    -1,    61,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,
      20,    -1,    22,    -1,    24,    25,    26,    27,    28,    29,
      -1,    31,     7,     8,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    57,    58,    59,
      -1,    61,    -1,    38,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,     7,
       8,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    17,
      18,    19,    20,    -1,    -1,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,
      38,    39,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    38,    39,    56,    41,
      42,    43,    44,    45,    46,    47,     7,     8,    -1,    -1,
      52,    53,    -1,    -1,    56,    -1,    17,    18,    19,    20,
      -1,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    38,    39,    56,    41,    42,    43,    44,
      45,    46,    47,     7,     8,    -1,    -1,    52,    53,    -1,
      -1,    56,    -1,    17,    18,    19,    20,    -1,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    -1,    38,    39,    -1,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      38,    39,    56,    41,    42,    43,    44,    45,    46,    47,
       7,     8,    -1,    -1,    52,    53,    -1,    -1,    56,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,     7,     8,
      -1,    -1,    52,    53,    54,    -1,    -1,    -1,    17,    18,
      19,    20,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    38,    39,    -1,    41,    42,
      43,    44,    45,    46,    47,     7,     8,    -1,    -1,    52,
      53,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    39,    -1,    41,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    39,    -1,    41,    42,    43,    44,    45,    46,
      47,     8,    -1,    -1,    -1,    52,    53,    -1,    -1,    -1,
      17,    18,    19,    20,     8,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    17,    18,    19,
      20,    -1,     8,    -1,    -1,    42,    43,    44,    45,    46,
      47,    17,    18,    19,    20,    52,    53,    -1,    -1,    43,
      44,    45,    46,    47,    44,    45,    46,    47,    52,    53,
      -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,     8,    -1,    -1,    17,    52,    53,    20,     8,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    17,    18,
      19,    20,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,    17,
      46,    47,    20,    55,    -1,    -1,    52,    53,    47,    61,
      -1,    -1,    -1,    52,    53,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    17,    -1,    -1,    20,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      58,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    63,     0,     5,     6,    13,    14,    15,    17,    20,
      22,    24,    25,    26,    27,    28,    29,    31,    35,    36,
      37,    47,    48,    49,    55,    57,    58,    61,    67,    71,
      77,    89,    91,    92,    93,    96,    97,    99,   101,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   117,   118,   119,   121,   122,   125,   126,     9,    10,
      11,    12,    36,    90,   123,    94,    98,   100,   102,    36,
     121,   121,    55,    36,   126,    55,    95,    55,    55,    60,
      40,    55,   121,   121,   121,   121,    36,    72,    78,     7,
      96,    96,   121,    96,    96,    96,   117,   105,   117,   121,
      61,   117,   117,    28,    75,    96,   123,     7,     8,    17,
      18,    19,    20,    38,    39,    41,    42,    43,    44,    45,
      46,    47,    52,    53,    96,   121,   127,   123,    52,    58,
      37,   123,   123,   123,   121,    96,    96,   121,    36,   126,
     121,   121,    35,    56,    55,     3,     4,    73,    74,    16,
      58,    86,   121,    96,    23,   121,    55,    59,    67,    93,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,    56,    36,    36,   120,
      96,     7,     7,     7,    56,    61,    96,    56,    56,    36,
      64,    65,    66,    58,   123,    76,    80,    81,   123,   124,
      76,    87,    56,   121,    40,    40,    54,    38,    59,   126,
      47,    60,    79,    90,    79,    33,   115,   116,     7,    38,
      56,    38,    56,    75,    55,    56,    38,    38,    79,    35,
      84,    85,   117,    56,   121,   121,    36,    79,    35,    36,
     116,    37,    55,    37,    65,    59,    55,    70,    76,   123,
      53,    82,    83,    38,    88,    54,    37,    68,    69,    79,
      35,    54,    84,    59,    38,    56,    54,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    66,    67,    67,    68,    69,    69,    70,    70,    72,
      71,    73,    73,    73,    74,    75,    75,    76,    78,    77,
      77,    77,    79,    79,    79,    79,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    85,    85,    87,    88,    86,
      89,    89,    89,    90,    90,    90,    90,    91,    92,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    93,    95,    93,    93,    93,
      93,    96,    98,    97,   100,    99,   102,   101,   103,   104,
     105,   105,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   115,   116,   117,   118,   119,   120,   120,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   122,   122,
     123,   123,   124,   124,   125,   126,   127,   127
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     2,     0,
       1,     3,     0,     5,     1,     1,     3,     0,     3,     0,
       6,     4,     1,     1,     3,     0,     2,     3,     0,     4,
       3,     2,     1,     2,     2,     2,     0,     1,     1,     3,
       2,     3,     0,     1,     1,     1,     3,     0,     0,     5,
       1,     3,     3,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     0,     4,     0,     4,     2,     2,
       2,     1,     0,     5,     0,     5,     0,     5,     4,     3,
       2,     2,     2,     4,     2,     5,     4,     2,     1,     2,
       5,     5,     1,     2,     1,     3,     1,     5,     1,     3,
       1,     3,     4,     6,     3,     3,     1,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     5,     1,     1,     1,     3,
       1,     3,     1,     3,     2,     3,     0,     1
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
#line 1645 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 97 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1652 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 98 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1659 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 101 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1667 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1676 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 108 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1684 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1692 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 114 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1700 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1708 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 118 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1716 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 122 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation(sym_null, nullptr);
}
#line 1724 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1732 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 128 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1740 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 132 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1748 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1756 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 138 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1764 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1772 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 144 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1778 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 144 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1786 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 148 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1796 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 157 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1804 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 161 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1811 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1818 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 165 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = nullptr;
  for (Expr *var : (yyvsp[-2].expr_set)->exprs) {
    VarDecl *vd = Builder::BuildVarDecl(var,
					(yyvsp[-1].width_spec).is_primitive, (yyvsp[-1].width_spec).is_ptr, (yyvsp[-1].width_spec).name,
					(yyvsp[-1].width_spec).width);
    Builder::SetArrayLength(vd, (yyvsp[0].num).value);
    vds = Builder::VarDeclList(vds, vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1834 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1840 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1851 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 182 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1858 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 183 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1865 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 186 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true, false);
}
#line 1873 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 188 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value, false);
}
#line 1881 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 190 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false, false);
}
#line 1889 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 192 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = (yyvsp[0].width_spec);
  (yyval.width_spec).is_ptr = true;
}
#line 1898 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1907 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 200 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1915 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 204 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1931 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 1943 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 222 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num).value = 0;
}
#line 1951 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 224 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1959 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 228 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num).value = -1;
}
#line 1967 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 230 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1975 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 234 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1983 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 238 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 1993 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 242 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2002 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 247 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2008 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 247 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2014 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 247 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2022 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 251 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2031 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 254 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2045 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2063 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 276 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2071 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2079 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 280 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2087 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2095 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 287 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2102 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 290 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2110 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 294 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2118 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 296 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2126 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 298 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2133 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 299 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2140 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 300 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2147 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 301 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2155 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 303 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2163 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 305 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2170 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 306 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2177 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2184 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 308 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2191 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 309 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2198 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 310 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2205 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2213 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2219 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2227 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2233 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitSpawnStmt((yyvsp[-1].expr));
}
#line 2241 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 318 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2248 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 319 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2255 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 320 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2262 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2270 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2276 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2284 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2290 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2298 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2304 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2312 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 340 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2321 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 345 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-2].stmt)->label_f_);
}
#line 2331 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 351 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2341 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 355 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2350 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 358 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2359 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 363 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2368 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 368 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2377 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
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
  Emitter::EmitGoto((yyvsp[-4].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2396 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 388 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2409 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 397 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2419 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 403 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->label_join_);
}
#line 2430 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2438 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 414 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_t_);
  Emitter::EmitGoto((yyvsp[-4].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2450 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 422 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2457 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 425 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2464 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 426 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2471 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 429 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2478 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 432 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2486 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 436 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2495 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 441 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2503 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 445 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2511 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 447 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2519 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 451 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2528 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 454 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2536 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 456 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2544 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 458 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2552 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 460 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2560 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 462 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2568 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2576 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 466 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2584 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2592 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 470 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::RefExpr((yyvsp[0].expr));
}
#line 2600 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 472 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2608 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2616 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 476 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2624 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 478 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2632 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 480 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2640 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 482 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2648 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 484 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2656 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 486 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2664 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 488 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2672 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 490 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2680 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 492 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2688 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 494 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2696 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 496 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2704 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 498 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2712 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 500 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2720 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 502 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2728 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 504 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2737 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 507 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2746 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 512 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2754 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 514 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2763 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2771 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2779 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2787 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2795 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 531 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2803 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2812 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 540 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2820 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 542 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2828 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2832 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 546 "src/fe/parser.ypp" /* yacc.c:1906  */

