/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         z_yyparse
#define yylex           z_yylex
#define yyerror         z_yyerror
#define yydebug         z_yydebug
#define yynerrs         z_yynerrs

#define yylval          z_yylval
#define yychar          z_yychar

/* Copy the first part of user declarations.  */
#line 2 "parser.ypp" /* yacc.c:339  */

#include "sym.h"
#include "fe/builder.h"
#include "fe/emitter.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "dfg/resource_params.h"

extern int yylex();
extern void yyerror(const char *msg);


#line 90 "src/fe/libparse_la-parser.cpp" /* yacc.c:339  */

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
#ifndef YY_Z_YY_Y_TAB_H_INCLUDED
# define YY_Z_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int z_yydebug;
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
    K_STRUCT = 262,
    K_ASSIGN = 263,
    K_SHIFT = 264,
    K_INT = 265,
    K_BOOL = 266,
    K_STRING = 267,
    K_OBJECT = 268,
    K_THREAD = 269,
    K_CHANNEL = 270,
    K_ADD_SUB = 271,
    K_LG_COMPARE = 272,
    K_EQ_COMPARE = 273,
    K_INC_DEC = 274,
    K_CONST = 275,
    K_IF = 276,
    K_ELSE = 277,
    K_RETURN = 278,
    K_GOTO = 279,
    K_FOR = 280,
    K_SPAWN = 281,
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
#define K_STRUCT 262
#define K_ASSIGN 263
#define K_SHIFT 264
#define K_INT 265
#define K_BOOL 266
#define K_STRING 267
#define K_OBJECT 268
#define K_THREAD 269
#define K_CHANNEL 270
#define K_ADD_SUB 271
#define K_LG_COMPARE 272
#define K_EQ_COMPARE 273
#define K_INC_DEC 274
#define K_CONST 275
#define K_IF 276
#define K_ELSE 277
#define K_RETURN 278
#define K_GOTO 279
#define K_FOR 280
#define K_SPAWN 281
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
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 17 "parser.ypp" /* yacc.c:355  */

  class ArrayInitializer *array;
  class Expr *expr;
  class EnumDecl *enum_decl;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  uint64_t num;
  const class numeric::Width *width;
  class ResourceParamValue *import_param;
  class ResourceParamValueSet *import_params;

#line 228 "src/fe/libparse_la-parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE z_yylval;

int z_yyparse (void);

#endif /* !YY_Z_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 243 "src/fe/libparse_la-parser.cpp" /* yacc.c:358  */

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
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  264

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
       2,     2,     2,    47,     2,    58,     2,     2,    45,     2,
      54,    55,    46,     2,    37,     2,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    59,
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,    43,    57,    48,     2,     2,     2,
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
       0,    91,    91,    92,    93,    96,    98,   103,   105,   109,
     111,   115,   116,   120,   124,   126,   130,   132,   136,   140,
     146,   146,   148,   152,   153,   156,   158,   160,   164,   166,
     168,   171,   173,   175,   177,   181,   184,   188,   190,   192,
     198,   200,   204,   206,   210,   214,   218,   223,   227,   230,
     233,   237,   240,   244,   246,   248,   250,   255,   258,   260,
     262,   263,   264,   266,   268,   270,   272,   273,   274,   275,
     276,   277,   278,   280,   281,   283,   285,   286,   289,   293,
     297,   302,   308,   312,   315,   320,   325,   330,   345,   354,
     360,   367,   371,   379,   382,   383,   386,   389,   393,   398,
     402,   404,   408,   411,   414,   415,   418,   420,   422,   424,
     426,   428,   430,   432,   434,   436,   438,   440,   442,   444,
     446,   448,   450,   452,   454,   456,   458,   460,   462,   464,
     466,   468,   470,   474,   476,   480,   484,   488,   490
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_STRUCT", "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING",
  "K_OBJECT", "K_THREAD", "K_CHANNEL", "K_ADD_SUB", "K_LG_COMPARE",
  "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE", "K_RETURN",
  "K_GOTO", "K_FOR", "K_SPAWN", "K_WHILE", "K_DO", "K_CONTINUE",
  "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM", "STR", "','",
  "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'",
  "'&'", "'*'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "'#'", "';'", "$accept", "input",
  "IMPORT_PARAM_HEAD", "IMPORT_PARAM", "IMPORT_PARAM_LIST", "IMPORT_SPEC",
  "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL",
  "FUNC_DECL_HEAD", "FUNC_DECL_NAME", "STMT_LIST", "MODIFIED_VAR",
  "VAR_DECL", "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC",
  "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "VAR_DECL_STMT", "TYPE_NAME", "LABEL", "STMT",
  "THREAD_DECL_STMT", "CHANNEL_DECL_STMT", "IF_COND_PART", "IF_WITH_ELSE",
  "IF_STMT", "FOR_HEAD", "FOR_COND_PART", "FOR_STMT", "WHILE_COND_PART",
  "WHILE_STMT", "DO_WHILE_HEAD", "DO_WHILE_BODY", "DO_WHILE_STMT",
  "SWITCH_STMT", "CASES_LIST", "CASE", "BLOCK", "BLOCK_HEAD", "ENUM_DECL",
  "ENUM_ITEM_LIST", "STRUCT_DECL", "STRUCT_DECL_HEAD",
  "STRUCT_ELEMENT_LIST", "EXPR", "VAR", "FUNCALL_HEAD", "FUNCALL",
  "ARG_LIST", YY_NULLPTR
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
     296,    46,    91,    93,    40,    41,   123,   125,    35,    59
};
# endif

#define YYPACT_NINF -180

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-180)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -180,   138,  -180,  -180,  -180,   168,   -28,    -8,  -180,  -180,
    -180,  -180,    51,    51,   767,   767,    34,    45,    66,    71,
      51,    72,  -180,    80,  -180,    97,  -180,   767,   767,   767,
     767,  -180,  -180,  -180,   104,   188,    -2,    38,   111,  -180,
    -180,    99,   112,   114,    16,  -180,   767,   116,  -180,   114,
    -180,   114,   149,  -180,  -180,  -180,  -180,    41,   123,   132,
     289,   -10,   767,  -180,  -180,     1,    73,   137,  -180,    26,
      27,    21,    21,   767,  -180,   328,   143,   -10,   145,   767,
     148,   767,   767,  -180,    21,    21,    21,   406,   156,   152,
     136,  -180,   155,   174,     1,   767,    78,   220,  -180,     1,
    -180,    -6,     1,  -180,  -180,   197,  -180,  -180,   643,   767,
    -180,  -180,   175,   211,   198,  -180,  -180,   180,  -180,   188,
     767,   767,   767,   767,   767,  -180,   767,   767,   767,   767,
     767,   767,   767,   767,   767,   767,  -180,   205,  -180,   643,
     189,  -180,   208,  -180,    51,   242,   422,  -180,  -180,  -180,
     367,  -180,   462,   478,  -180,   241,    48,  -180,   130,  -180,
    -180,   202,   305,   682,   207,  -180,   194,   253,   223,  -180,
    -180,  -180,   518,   767,  -180,  -180,    51,   180,    46,    14,
     682,   196,    43,   753,   744,   682,   630,    13,   700,   345,
     383,   578,   739,    21,   574,  -180,  -180,  -180,   -14,  -180,
     111,  -180,  -180,  -180,   231,    92,   228,  -180,   156,  -180,
     266,   242,  -180,  -180,  -180,  -180,   232,  -180,   767,   235,
     114,   534,   180,  -180,  -180,    47,   767,   767,  -180,   239,
    -180,  -180,  -180,   231,  -180,  -180,   247,  -180,  -180,  -180,
    -180,   100,   111,  -180,  -180,    37,   682,  -180,  -180,  -180,
    -180,   695,   591,  -180,  -180,  -180,   242,  -180,  -180,   232,
    -180,  -180,  -180,  -180
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    20,    21,     0,     0,     0,    53,    54,
      56,    55,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    90,     0,   132,   133,   131,     0,     0,     0,
       0,    98,    58,     3,    11,    35,    42,     0,    31,    73,
       4,     0,     0,     0,     0,    67,     0,     0,    68,     0,
      69,     0,     0,    70,    71,    66,    23,     0,     0,     0,
       0,   106,   137,   111,   133,     0,     0,     0,   103,     0,
       0,   129,   128,     0,    65,     0,   133,     0,     0,     0,
       0,     0,     0,    57,   114,   112,   113,     0,     0,     0,
       0,    37,     0,    36,     0,     0,     0,    43,    48,     0,
      72,     0,     0,    76,    77,    82,    84,    83,    86,     0,
      89,    91,     0,     0,     0,    60,    30,    25,    61,     0,
       0,     0,     0,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,     0,   135,   138,
       0,    29,     0,    74,     0,     0,     0,    64,    63,    62,
       0,    75,     0,     0,   107,     0,     0,     9,     0,    23,
      22,    16,     0,    49,     0,    40,     0,    51,    32,    34,
      28,    81,     0,     0,    97,    24,   133,    26,     0,     0,
     118,   117,   115,   119,   120,   110,     0,   125,   126,   121,
     123,   124,   122,   116,     0,   134,   136,   100,     0,    78,
      31,    80,    85,    88,     0,     0,     0,     8,     0,    12,
       0,     0,    19,    39,    38,    41,     0,    50,     0,     0,
       0,     0,    27,   104,   102,     0,     0,     0,   108,     0,
      99,    79,    96,    93,    94,     7,     0,     6,    10,    18,
      14,     0,    31,    44,    45,     0,    52,    33,    87,    92,
     105,   130,     0,   101,    95,     5,     0,    17,    13,     0,
      47,   109,    15,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,    67,  -180,  -180,    28,  -180,  -180,  -180,
    -180,  -180,   127,   -60,   -32,  -179,  -180,  -180,  -180,  -180,
      29,  -180,  -180,  -109,    -5,  -180,   294,  -180,  -180,  -180,
    -180,   255,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,    70,   -31,  -180,    10,  -180,  -180,  -180,  -180,
     -13,    33,  -180,   -11,  -180
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   156,   157,   158,    89,   240,   241,   212,    33,
      34,    35,   113,   116,    36,   102,    92,    93,    97,    98,
     244,   245,   217,    37,    38,    39,   175,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   233,   234,    55,    56,    94,   198,    58,    59,   179,
      60,    61,    62,    63,   140
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      65,    71,    72,    91,    75,   141,    95,    78,    67,    80,
     178,    57,   105,   107,    84,    85,    86,    87,   110,     5,
     111,   231,   121,   229,     8,     9,    10,    11,   168,   122,
     123,   124,   125,   108,   144,   145,    64,    16,    66,   167,
     125,   137,   170,   230,   138,    69,    70,   114,    68,   139,
      96,    77,   169,    77,   129,   130,   131,   132,   133,   134,
     146,    14,   125,   258,    15,   135,   150,    90,   152,   153,
     225,   224,    31,   135,   259,    99,    64,   137,   137,    24,
      64,    26,   163,    99,    99,   206,    64,   114,    73,   134,
     117,    27,    28,    29,   260,   135,   172,   100,   117,    30,
     115,    76,   213,   207,    74,   223,   250,   180,   181,   182,
     183,   184,   164,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,    57,   137,    79,    81,   117,   235,   142,
     214,   165,   117,   199,    82,   117,    83,   256,     2,    64,
     200,     3,     4,     5,     6,     7,   236,   177,     8,     9,
      10,    11,    12,    13,    14,   257,    88,    15,   103,    16,
     221,    17,    18,    19,    20,    21,    22,   208,    23,   101,
      31,   104,    24,    25,    26,   109,   112,    77,     8,     9,
      10,    11,   118,   209,    27,    28,    29,   137,   119,   248,
     160,   155,    30,     5,    31,   117,   143,    32,     8,     9,
      10,    11,   148,    64,   149,   246,   242,   151,   159,   222,
     161,   162,   122,   251,   252,   125,     5,     6,     7,   171,
      57,     8,     9,    10,    11,    12,    13,    14,   166,   173,
      15,   137,    16,   176,    17,    18,    19,    20,    21,    22,
     195,    23,   134,   197,   196,    24,    25,    26,   135,   205,
     216,   242,     8,     9,    10,    11,   211,    27,    28,    29,
     215,   218,   219,   232,   237,    30,   243,    31,   174,   247,
      32,     5,     6,     7,   253,   238,     8,     9,    10,    11,
      12,    13,    14,   255,   262,    15,   210,    16,   263,    17,
      18,    19,    20,    21,    22,    40,    23,   120,   121,   106,
      24,    25,    26,   254,     0,   122,   123,   124,   125,     0,
       5,     0,    27,    28,    29,     8,     9,    10,    11,     0,
      30,     0,    31,   239,     0,    32,   126,   127,     0,   128,
     129,   130,   131,   132,   133,   134,   120,   121,     0,     0,
      64,   135,     0,     0,   122,   123,   124,   125,   136,     0,
       0,   114,     0,     0,   121,     0,     0,     0,     0,     0,
       0,   122,   123,   124,   125,   126,   127,     0,   128,   129,
     130,   131,   132,   133,   134,   120,   121,     0,     0,     0,
     135,     0,     0,   122,   123,   124,   125,   147,   131,   132,
     133,   134,   121,     0,     0,     0,     0,   135,     0,   122,
     123,   124,   125,     0,   126,   127,     0,   128,   129,   130,
     131,   132,   133,   134,   120,   121,     0,     0,     0,   135,
       0,     0,   122,   123,   124,   125,   202,   132,   133,   134,
     120,   121,     0,     0,     0,   135,     0,     0,   122,   123,
     124,   125,     0,   126,   127,     0,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,     0,   135,   126,
     127,   154,   128,   129,   130,   131,   132,   133,   134,     0,
     120,   121,     0,     0,   135,     0,     0,   201,   122,   123,
     124,   125,     0,     0,     0,     0,   120,   121,     0,     0,
       0,     0,     0,     0,   122,   123,   124,   125,     0,   126,
     127,     0,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,   135,   126,   127,   203,   128,   129,
     130,   131,   132,   133,   134,     0,   120,   121,     0,     0,
     135,     0,     0,   204,   122,   123,   124,   125,     0,     0,
       0,     0,   120,   121,     0,     0,     0,     0,     0,     0,
     122,   123,   124,   125,     0,   126,   127,     0,   128,   129,
     130,   131,   132,   133,   134,     0,     0,     0,     0,     0,
     135,   126,   127,   220,   128,   129,   130,   131,   132,   133,
     134,     0,   120,   121,     0,     0,   135,   121,     0,   249,
     122,   123,   124,   125,   122,   123,   124,   125,     0,   120,
     121,     0,     0,     0,     0,     0,     0,   122,   123,   124,
     125,   126,   127,   227,   128,   129,   130,   131,   132,   133,
     134,     0,     0,   133,   134,     0,   135,   228,   126,   127,
     135,   128,   129,   130,   131,   132,   133,   134,   120,   121,
       0,     0,     0,   135,   261,     0,   122,   123,   124,   125,
       0,   120,   121,     0,     0,     0,     0,     0,     0,   122,
     123,   124,   125,     0,     0,     0,     0,   126,   127,   226,
     128,   129,   130,   131,   132,   133,   134,     0,     0,     0,
     126,   127,   135,   128,   129,   130,   131,   132,   133,   134,
     120,   121,     0,     0,     0,   135,     0,     0,   122,   123,
     124,   125,     0,     0,   121,     0,     0,     0,     0,   121,
       0,   122,   123,   124,   125,     0,   122,   123,   124,   125,
     127,     0,   128,   129,   130,   131,   132,   133,   134,     0,
       0,     0,     0,   127,   135,   128,   129,   130,   131,   132,
     133,   134,   130,   131,   132,   133,   134,   135,   121,     0,
       0,     0,   135,   121,     0,   122,   123,   124,   125,     0,
     122,   123,   121,   125,     0,     0,     0,     0,     0,   122,
       0,     0,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,   134,    15,     0,     0,     0,
     134,   135,     0,     0,     0,     0,   135,     0,     0,   134,
       0,    24,    64,    26,     0,   135,     0,     0,     0,     0,
       0,     0,     0,    27,    28,    29,     0,     0,     0,     0,
       0,    30
};

static const yytype_int16 yycheck[] =
{
       5,    14,    15,    35,    17,    65,     8,    18,    36,    20,
     119,     1,    43,    44,    27,    28,    29,    30,    49,     5,
      51,   200,     9,    37,    10,    11,    12,    13,    34,    16,
      17,    18,    19,    46,     8,     8,    35,    21,     5,    99,
      19,    51,   102,    57,    54,    12,    13,    46,    56,    62,
      52,    18,    58,    20,    41,    42,    43,    44,    45,    46,
      73,    16,    19,   242,    19,    52,    79,    34,    81,    82,
     179,    57,    56,    52,    37,    37,    35,    51,    51,    34,
      35,    36,    95,    37,    37,    37,    35,    46,    54,    46,
      57,    46,    47,    48,    57,    52,   109,    59,    65,    54,
      59,    35,   162,    55,    59,    59,    59,   120,   121,   122,
     123,   124,    34,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   113,    51,    54,    54,    94,    36,    56,
     162,    53,    99,   144,    54,   102,    39,    37,     0,    35,
     145,     3,     4,     5,     6,     7,    54,   114,    10,    11,
      12,    13,    14,    15,    16,    55,    52,    19,    59,    21,
     173,    23,    24,    25,    26,    27,    28,    37,    30,    58,
      56,    59,    34,    35,    36,    59,    27,   144,    10,    11,
      12,    13,    59,    53,    46,    47,    48,    51,    56,   220,
      54,    35,    54,     5,    56,   162,    59,    59,    10,    11,
      12,    13,    59,    35,    59,   218,   211,    59,    56,   176,
      55,    37,    16,   226,   227,    19,     5,     6,     7,    22,
     210,    10,    11,    12,    13,    14,    15,    16,     8,    54,
      19,    51,    21,    35,    23,    24,    25,    26,    27,    28,
      35,    30,    46,    35,    55,    34,    35,    36,    52,     8,
      56,   256,    10,    11,    12,    13,    54,    46,    47,    48,
      53,     8,    39,    32,    36,    54,    34,    56,    57,    34,
      59,     5,     6,     7,    35,   208,    10,    11,    12,    13,
      14,    15,    16,    36,   256,    19,   159,    21,   259,    23,
      24,    25,    26,    27,    28,     1,    30,     8,     9,    44,
      34,    35,    36,   233,    -1,    16,    17,    18,    19,    -1,
       5,    -1,    46,    47,    48,    10,    11,    12,    13,    -1,
      54,    -1,    56,    57,    -1,    59,    37,    38,    -1,    40,
      41,    42,    43,    44,    45,    46,     8,     9,    -1,    -1,
      35,    52,    -1,    -1,    16,    17,    18,    19,    59,    -1,
      -1,    46,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    16,    17,    18,    19,    37,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,     8,     9,    -1,    -1,    -1,
      52,    -1,    -1,    16,    17,    18,    19,    59,    43,    44,
      45,    46,     9,    -1,    -1,    -1,    -1,    52,    -1,    16,
      17,    18,    19,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,     8,     9,    -1,    -1,    -1,    52,
      -1,    -1,    16,    17,    18,    19,    59,    44,    45,    46,
       8,     9,    -1,    -1,    -1,    52,    -1,    -1,    16,    17,
      18,    19,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    37,
      38,    55,    40,    41,    42,    43,    44,    45,    46,    -1,
       8,     9,    -1,    -1,    52,    -1,    -1,    55,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    37,    38,    55,    40,    41,
      42,    43,    44,    45,    46,    -1,     8,     9,    -1,    -1,
      52,    -1,    -1,    55,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    37,    38,    55,    40,    41,    42,    43,    44,    45,
      46,    -1,     8,     9,    -1,    -1,    52,     9,    -1,    55,
      16,    17,    18,    19,    16,    17,    18,    19,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    45,    46,    -1,    52,    53,    37,    38,
      52,    40,    41,    42,    43,    44,    45,    46,     8,     9,
      -1,    -1,    -1,    52,    53,    -1,    16,    17,    18,    19,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      37,    38,    52,    40,    41,    42,    43,    44,    45,    46,
       8,     9,    -1,    -1,    -1,    52,    -1,    -1,    16,    17,
      18,    19,    -1,    -1,     9,    -1,    -1,    -1,    -1,     9,
      -1,    16,    17,    18,    19,    -1,    16,    17,    18,    19,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    38,    52,    40,    41,    42,    43,    44,
      45,    46,    42,    43,    44,    45,    46,    52,     9,    -1,
      -1,    -1,    52,     9,    -1,    16,    17,    18,    19,    -1,
      16,    17,     9,    19,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    46,    19,    -1,    -1,    -1,
      46,    52,    -1,    -1,    -1,    -1,    52,    -1,    -1,    46,
      -1,    34,    35,    36,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,     0,     3,     4,     5,     6,     7,    10,    11,
      12,    13,    14,    15,    16,    19,    21,    23,    24,    25,
      26,    27,    28,    30,    34,    35,    36,    46,    47,    48,
      54,    56,    59,    69,    70,    71,    74,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   103,   104,   105,   107,   108,
     110,   111,   112,   113,    35,    84,   111,    36,    56,   111,
     111,   110,   110,    54,    59,   110,    35,   111,   113,    54,
     113,    54,    54,    39,   110,   110,   110,   110,    52,    65,
     111,    74,    76,    77,   105,     8,    52,    78,    79,    37,
      59,    58,    75,    59,    59,   103,    91,   103,   110,    59,
     103,   103,    27,    72,    46,    59,    73,   111,    59,    56,
       8,     9,    16,    17,    18,    19,    37,    38,    40,    41,
      42,    43,    44,    45,    46,    52,    59,    51,    54,   110,
     114,    73,    56,    59,     8,     8,   110,    59,    59,    59,
     110,    59,   110,   110,    55,    35,    62,    63,    64,    56,
      54,    55,    37,   110,    34,    53,     8,    73,    34,    58,
      73,    22,   110,    54,    57,    86,    35,   111,    83,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,    35,    55,    35,   106,   113,
      84,    55,    59,    55,    55,     8,    37,    55,    37,    53,
      72,    54,    68,    73,    74,    53,    56,    82,     8,    39,
      55,   110,   111,    59,    57,    83,    39,    39,    53,    37,
      57,    75,    32,   101,   102,    36,    54,    36,    63,    57,
      66,    67,    84,    34,    80,    81,   110,    34,   103,    55,
      59,   110,   110,    35,   102,    36,    37,    55,    75,    37,
      57,    53,    66,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    67,    67,    68,    68,    69,    70,
      70,    70,    71,    72,    72,    73,    73,    73,    74,    74,
      74,    75,    75,    75,    75,    76,    76,    77,    77,    77,
      78,    78,    79,    79,    80,    81,    81,    82,    83,    83,
      83,    83,    83,    84,    84,    84,    84,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    88,
      89,    90,    91,    91,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   101,   102,   103,   104,   105,
     106,   106,   107,   108,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   113,   114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     2,     1,
       3,     0,     3,     2,     1,     3,     0,     3,     5,     4,
       1,     1,     3,     0,     2,     1,     2,     3,     3,     3,
       2,     0,     2,     4,     2,     0,     1,     1,     3,     3,
       2,     3,     0,     1,     1,     1,     3,     3,     2,     3,
       4,     3,     5,     1,     1,     1,     1,     2,     1,     2,
       2,     2,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     2,     1,     3,     3,     2,     2,     4,     5,
       4,     3,     2,     2,     2,     4,     2,     5,     4,     2,
       1,     2,     5,     5,     1,     2,     1,     3,     1,     5,
       1,     3,     4,     2,     2,     3,     1,     3,     4,     6,
       3,     1,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       5,     1,     1,     1,     3,     2,     3,     0,     1
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
#line 91 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1629 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 92 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1636 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 93 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1643 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 96 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = dfg::Importer::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1651 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 98 "parser.ypp" /* yacc.c:1646  */
    {
  dfg::Importer::AddStrParam((yyvsp[-2].import_param), (yyvsp[0].str));
  (yyval.import_param) = (yyvsp[-2].import_param);
}
#line 1660 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 103 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = dfg::Importer::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1668 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = (yyvsp[-1].import_param);
}
#line 1676 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 109 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = dfg::Importer::BuildParamSet(NULL, (yyvsp[0].import_param));
}
#line 1684 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 111 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = dfg::Importer::BuildParamSet((yyvsp[-2].import_params), (yyvsp[0].import_param));
}
#line 1692 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1699 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource((yyvsp[-1].import_params));
}
#line 1707 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 120 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[-1].sym), (yyvsp[0].width));
}
#line 1715 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 124 "parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(NULL, (yyvsp[0].var_decl));
}
#line 1723 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 126 "parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1731 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(NULL, NULL);
}
#line 1739 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1747 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 136 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1755 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1764 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 148 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1772 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 152 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1779 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 153 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1786 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 156 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), false, NULL);
}
#line 1794 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, NULL);
}
#line 1802 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 160 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, (yyvsp[-1].sym));
}
#line 1810 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 164 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::BuildVarDecl((yyvsp[-2].sym), (yyvsp[-1].width), (yyvsp[0].var_decl));
}
#line 1818 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 166 "parser.ypp" /* yacc.c:1646  */
    {
//  $$ = NULL; // NstBuilder::BuildVarDecl($2, NULL, $3);
}
#line 1826 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 168 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1833 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 171 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, 32, 0);
}
#line 1841 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 173 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, (yyvsp[0].num), 0);
}
#line 1849 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 175 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, (yyvsp[-2].num), (yyvsp[0].num));
}
#line 1857 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 177 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::Null();
}
#line 1865 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 181 "parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = NULL; // NstBuilder::ArgDeclList(NULL, NULL);
}
#line 1874 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 184 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1882 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList(NULL, (yyvsp[0].var_decl));
}
#line 1890 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 190 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1898 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 192 "parser.ypp" /* yacc.c:1646  */
    {
  /* un-typed argument */
  //  NstStmt *stmt = NstBuilder::BuildVarDecl(NULL, NULL, $3);
  (yyval.var_decl_set) = NULL; // NstBuilder::ArgDeclList($1, stmt);
}
#line 1908 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 198 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = 0;
}
#line 1916 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 200 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1924 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 204 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = -1;
}
#line 1932 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 206 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1940 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 210 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1948 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 214 "parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num));
  (yyval.array) = array;
}
#line 1958 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 218 "parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num));
  (yyval.array) = (yyvsp[-2].array);
}
#line 1967 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 223 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-1].array);
}
#line 1975 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 227 "parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-1].var_decl), (yyvsp[0].num));
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-1].var_decl));
}
#line 1984 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 230 "parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].var_decl)->initial_val = (yyvsp[0].expr);
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-2].var_decl));
}
#line 1993 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 233 "parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-3].var_decl), (yyvsp[-2].num));
  Builder::SetArrayInitializer((yyvsp[-3].var_decl), (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-3].var_decl));
}
#line 2003 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 237 "parser.ypp" /* yacc.c:1646  */
    {
  sym_t type = Builder::TypeNameFromVarDeclSet((yyvsp[-2].var_decl_set));
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-2].var_decl_set), Builder::BuildVarDecl(type, NULL, (yyvsp[0].var_decl)));
}
#line 2012 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 240 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-4].var_decl_set), (yyvsp[-2].var_decl));
}
#line 2020 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 244 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2028 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 246 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2036 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 248 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2044 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 250 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2052 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 255 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2059 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 258 "parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2067 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 260 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2075 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 262 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2082 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 263 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2089 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 264 "parser.ypp" /* yacc.c:1646  */
    {
  // NstEmitter::EmitTransition($2);
}
#line 2097 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 266 "parser.ypp" /* yacc.c:1646  */
    {
  // NstEmitter::EmitGotoStmt($2);
}
#line 2105 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 268 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2113 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 270 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(NULL);
}
#line 2121 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 272 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2128 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 273 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2135 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 274 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2142 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 275 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2149 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 276 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2156 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 277 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2163 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 278 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2171 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 281 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2179 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 283 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitSpawnStmt((yyvsp[-1].expr));
}
#line 2187 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 285 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2194 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 286 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2201 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 289 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2209 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 293 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width));
}
#line 2217 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 297 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2226 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 302 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-2].stmt)->label_f_);
}
#line 2236 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 308 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2246 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 312 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2255 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 315 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2264 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 320 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2273 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 325 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2282 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 330 "parser.ypp" /* yacc.c:1646  */
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
#line 2301 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 345 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2314 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 354 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2324 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 360 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->label_join_);
}
#line 2335 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 367 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2343 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 371 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_t_);
  Emitter::EmitGoto((yyvsp[-4].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2355 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 379 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2362 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 382 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2369 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 383 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2376 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 386 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2383 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 389 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2391 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 393 "parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2400 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 398 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2408 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 402 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(NULL, (yyvsp[0].sym));
}
#line 2416 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 404 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2424 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 408 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2431 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 411 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2438 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 414 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2445 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 415 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2452 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 418 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2460 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 420 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2468 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 422 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2476 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 424 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2484 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 426 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2492 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 428 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2500 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 430 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2508 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 432 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2516 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 434 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::RefExpr((yyvsp[0].expr));
}
#line 2524 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 436 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2532 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 438 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2540 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 440 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2548 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 442 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2556 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 444 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2564 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 446 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2572 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 448 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2580 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 450 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2588 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 452 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2596 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 454 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2604 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 456 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2612 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 458 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2620 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 460 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].num), true);
}
#line 2628 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 462 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].num), false);
}
#line 2636 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 464 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].num), (yyvsp[0].expr));
}
#line 2644 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 466 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2652 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 468 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2660 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 470 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2668 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 474 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2676 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 476 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2684 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 480 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2692 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 484 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2700 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 488 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = NULL;
}
#line 2708 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 490 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2716 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;


#line 2720 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
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
#line 494 "parser.ypp" /* yacc.c:1906  */

