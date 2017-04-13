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


/* Substitute the variable and function names.  */
#define yyparse         z_yyparse
#define yylex           z_yylex
#define yyerror         z_yyerror
#define yydebug         z_yydebug
#define yynerrs         z_yynerrs

#define yylval          z_yylval
#define yychar          z_yychar

/* Copy the first part of user declarations.  */
#line 2 "src/fe/parser.ypp" /* yacc.c:339  */

#include "sym.h"
#include "fe/builder.h"
#include "fe/emitter.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "synth/resource_params.h"

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
#ifndef YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED
# define YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED
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
    K_ASSIGN = 262,
    K_SHIFT = 263,
    K_INT = 264,
    K_BOOL = 265,
    K_STRING = 266,
    K_OBJECT = 267,
    K_THREAD = 268,
    K_CHANNEL = 269,
    K_MAILBOX = 270,
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
#define K_ASSIGN 262
#define K_SHIFT 263
#define K_INT 264
#define K_BOOL 265
#define K_STRING 266
#define K_OBJECT 267
#define K_THREAD 268
#define K_CHANNEL 269
#define K_MAILBOX 270
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

union YYSTYPE
{
#line 17 "src/fe/parser.ypp" /* yacc.c:355  */

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
  struct WidthSpec width_spec;
  class ResourceParamValue *import_param;
  class ResourceParamValueSet *import_params;

#line 228 "src/fe/libparse_la-parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE z_yylval;

int z_yyparse (void);

#endif /* !YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "src/fe/libparse_la-parser.cpp" /* yacc.c:358  */

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
#define YYLAST   810

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  262

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
       0,    90,    90,    91,    92,    95,    97,   102,   104,   108,
     110,   114,   116,   120,   124,   126,   130,   132,   136,   140,
     147,   147,   149,   153,   154,   157,   159,   161,   165,   167,
     168,   171,   173,   175,   177,   181,   184,   188,   190,   192,
     197,   199,   203,   205,   209,   213,   217,   222,   226,   229,
     232,   236,   240,   244,   246,   248,   250,   255,   258,   260,
     262,   263,   264,   265,   267,   269,   270,   271,   272,   273,
     274,   275,   277,   278,   280,   282,   283,   284,   287,   291,
     295,   299,   304,   310,   314,   317,   322,   327,   332,   347,
     356,   362,   369,   373,   381,   384,   385,   388,   391,   395,
     400,   404,   406,   410,   412,   414,   416,   418,   420,   422,
     424,   426,   428,   430,   432,   434,   436,   438,   440,   442,
     444,   446,   448,   450,   452,   454,   456,   458,   460,   462,
     464,   468,   470,   474,   478,   482,   484
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING", "K_OBJECT",
  "K_THREAD", "K_CHANNEL", "K_MAILBOX", "K_ADD_SUB", "K_LG_COMPARE",
  "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE", "K_RETURN",
  "K_GOTO", "K_FOR", "K_SPAWN", "K_WHILE", "K_DO", "K_CONTINUE",
  "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM", "STR", "','",
  "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'",
  "'&'", "'*'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'",
  "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept", "input",
  "IMPORT_PARAM_HEAD", "IMPORT_PARAM", "IMPORT_PARAM_LIST", "IMPORT_SPEC",
  "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL",
  "FUNC_DECL_HEAD", "FUNC_DECL_NAME", "STMT_LIST", "MODIFIED_VAR",
  "VAR_DECL", "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC",
  "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "VAR_DECL_STMT", "TYPE_NAME", "LABEL", "STMT",
  "THREAD_DECL_STMT", "CHANNEL_DECL_STMT", "MAILBOX_DECL_STMT",
  "IF_COND_PART", "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD", "FOR_COND_PART",
  "FOR_STMT", "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD",
  "DO_WHILE_BODY", "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE",
  "BLOCK", "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "EXPR", "VAR",
  "FUNCALL_HEAD", "FUNCALL", "ARG_LIST", YY_NULLPTR
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

#define YYPACT_NINF -178

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-178)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -178,   209,  -178,    16,    12,  -178,  -178,  -178,  -178,     3,
       3,     3,   756,   756,    37,   105,    18,    49,    52,    68,
    -178,    78,  -178,   -15,  -178,   756,   756,   756,   756,    61,
    -178,  -178,   132,  -178,     5,    23,    89,  -178,  -178,   100,
     102,   114,   118,    -1,  -178,   756,   127,  -178,   118,  -178,
     118,   169,  -178,  -178,  -178,  -178,    39,   126,   756,  -178,
    -178,     6,    33,   137,    15,    25,    26,   145,    30,    30,
     756,  -178,   342,   144,   140,   756,   145,   147,   756,   756,
    -178,  -178,    30,    30,    30,   422,   154,  -178,  -178,    92,
     237,   756,     2,   195,  -178,     6,  -178,    66,     6,  -178,
    -178,  -178,   188,  -178,  -178,   663,   756,  -178,  -178,   157,
     262,   177,  -178,  -178,   165,   756,   756,   756,   756,   756,
    -178,   756,   756,   756,   756,   756,   756,   756,   756,   756,
     756,   756,  -178,   663,   162,  -178,   191,   192,  -178,    52,
     241,   241,   438,  -178,  -178,  -178,   382,  -178,   478,   494,
    -178,   196,  -178,    35,  -178,   183,   203,     6,   703,   205,
    -178,   184,   252,  -178,  -178,  -178,  -178,  -178,   534,   756,
    -178,  -178,     3,   165,   703,   358,   142,    42,    46,   703,
     647,   138,    27,   734,   749,   398,   453,    30,  -178,   590,
    -178,  -178,  -178,   -16,  -178,    89,    89,  -178,  -178,  -178,
     228,   254,   136,  -178,   148,   318,  -178,   208,   290,  -178,
     230,  -178,   756,   118,   550,   165,   756,   756,  -178,   235,
    -178,  -178,  -178,  -178,   228,  -178,    93,   243,  -178,   196,
    -178,  -178,   241,  -178,  -178,  -178,  -178,  -178,    65,   703,
    -178,  -178,   718,   607,  -178,  -178,  -178,   244,  -178,  -178,
    -178,   158,    89,   230,  -178,  -178,  -178,   241,  -178,  -178,
    -178,  -178
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    11,     1,     0,     0,    53,    54,    56,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,   130,   103,   129,     0,     0,     0,     0,     0,
      99,    58,     0,     3,    42,     0,    31,    72,     4,     0,
       0,     0,     0,     0,    66,     0,     0,    67,     0,    68,
       0,     0,    69,    70,    65,    23,     0,     0,   135,   109,
     131,     0,     0,     0,     0,     0,     0,   103,   127,   126,
       0,    64,     0,     0,     0,     0,     0,     0,     0,     0,
      57,   133,   112,   110,   111,     0,     0,    20,    21,     0,
      35,     0,     0,    43,    48,     0,    71,     0,     0,    75,
      76,    77,    83,    85,    84,    87,     0,    90,    92,     0,
       0,     0,    60,    30,    25,     0,     0,     0,     0,     0,
     125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,   136,     0,    29,     0,     0,    73,     0,
       0,     0,     0,    63,    62,    61,     0,    74,     0,     0,
     104,     0,    23,     0,    37,     0,    36,     0,    49,     0,
      40,     0,    51,    32,    33,    34,    28,    82,     0,     0,
      98,    24,   131,    26,   116,   115,   113,   117,   118,   107,
       0,   123,   124,   119,   121,   122,   120,   114,   108,     0,
     134,   132,   101,     0,    78,    31,    31,    81,    86,    89,
       0,     0,     0,     9,     0,     0,    22,    16,     0,    41,
       0,    50,     0,     0,     0,    27,     0,     0,   105,     0,
     100,    79,    80,    97,    94,    95,     0,     0,     8,     0,
      12,    18,     0,    19,    39,    38,    44,    45,     0,    52,
      88,    93,   128,     0,   102,    96,     7,     0,     6,    10,
      14,     0,    31,     0,    47,   106,     5,     0,    17,    13,
      46,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,    53,  -178,  -178,    34,  -178,  -178,  -178,
    -178,  -178,   141,   -58,   -82,  -177,  -178,  -178,  -178,  -178,
      31,  -178,  -178,  -178,    -3,  -178,   293,  -178,  -178,  -178,
    -178,  -178,   260,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,    80,   -37,  -178,   -80,  -178,   -11,    20,
    -178,    -9,  -178
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   202,   203,   204,    32,   250,   251,   233,    33,
      89,    90,   110,   113,    34,    98,   155,   156,    93,    94,
     237,   238,   211,    35,    36,    37,   171,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   224,   225,    54,    55,    56,   193,    57,   114,
      58,    59,   134
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      61,    68,    69,   135,    72,   102,   104,    74,   154,    77,
     157,   107,    91,   108,    82,    83,    84,    85,   221,   222,
      14,   219,   139,    62,    80,     5,     6,     7,     8,    64,
      65,    66,   140,   141,   105,   116,   159,   162,    60,    81,
     166,    60,   220,   117,   118,   119,   120,   133,    63,   120,
     116,    60,   111,    73,   116,   160,    30,    92,   117,   142,
      95,   120,   117,   118,   146,   120,   136,   148,   149,   125,
     126,   127,   128,   129,    60,   259,   136,   136,   130,   131,
     158,   130,   131,    96,   136,   111,   136,    76,   129,   206,
     137,    70,   129,   130,   131,   168,    86,   130,   131,   112,
     163,   164,   253,    75,   174,   175,   176,   177,   178,   153,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    12,    78,   254,    13,   165,   235,    60,   157,   246,
     194,   173,    79,   115,   116,    87,    88,   195,   196,    22,
      67,    24,   117,   118,   119,   120,   116,   247,    97,   152,
     234,    25,    26,    27,   117,   118,   119,   120,   214,    28,
      99,   120,   100,   121,   122,    71,   123,   124,   125,   126,
     127,   128,   129,   227,   101,    30,   240,   130,   131,   124,
     125,   126,   127,   128,   129,   229,   132,   106,   129,   130,
     131,   228,   215,   130,   131,   257,   109,   138,    81,    81,
     145,   239,   161,   230,   144,   242,   243,   147,   151,     2,
     167,   169,   172,   258,     3,     4,   136,   190,     5,     6,
       7,     8,     9,    10,    11,    12,   191,   192,    13,   252,
      14,   201,    15,    16,    17,    18,    19,    20,   207,    21,
     208,   210,     3,    22,    23,    24,     5,     6,     7,     8,
       5,     6,     7,     8,   252,    25,    26,    27,   209,   212,
     223,   226,   232,    28,   236,    29,    30,     3,     4,    31,
     244,     5,     6,     7,     8,     9,    10,    11,    12,   248,
     256,    13,   249,    14,   260,    15,    16,    17,    18,    19,
      20,   261,    21,   205,    38,     3,    22,    23,    24,     5,
       6,     7,     8,   103,   245,     0,     0,     0,    25,    26,
      27,     0,     0,     0,     0,     0,    28,     0,     0,    30,
     170,     0,    31,     3,     4,    60,     0,     5,     6,     7,
       8,     9,    10,    11,    12,     0,   111,    13,     0,    14,
       0,    15,    16,    17,    18,    19,    20,     0,    21,   115,
     116,     0,    22,    23,    24,     0,     0,     0,   117,   118,
     119,   120,     0,     0,    25,    26,    27,     0,     0,     0,
       0,     0,    28,     0,   117,    30,   231,   120,    31,   121,
     122,     0,   123,   124,   125,   126,   127,   128,   129,   115,
     116,     0,     0,   130,   131,     0,     0,     0,   117,   118,
     119,   120,   143,     0,   129,     0,   116,     0,     0,   130,
     131,     0,     0,     0,   117,   118,   119,   120,     0,   121,
     122,     0,   123,   124,   125,   126,   127,   128,   129,   115,
     116,     0,     0,   130,   131,     0,     0,     0,   117,   118,
     119,   120,   198,   128,   129,   115,   116,     0,     0,   130,
     131,     0,     0,     0,   117,   118,   119,   120,     0,   121,
     122,   116,   123,   124,   125,   126,   127,   128,   129,   117,
     118,   119,   120,   130,   131,   121,   122,   150,   123,   124,
     125,   126,   127,   128,   129,   115,   116,     0,     0,   130,
     131,     0,     0,   197,   117,   118,   119,   120,     0,   129,
       0,   115,   116,     0,   130,   131,     0,     0,     0,     0,
     117,   118,   119,   120,     0,   121,   122,     0,   123,   124,
     125,   126,   127,   128,   129,     0,     0,     0,     0,   130,
     131,   121,   122,   199,   123,   124,   125,   126,   127,   128,
     129,   115,   116,     0,     0,   130,   131,     0,     0,   200,
     117,   118,   119,   120,     0,     0,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,   117,   118,   119,   120,
       0,   121,   122,     0,   123,   124,   125,   126,   127,   128,
     129,     0,     0,     0,     0,   130,   131,   121,   122,   213,
     123,   124,   125,   126,   127,   128,   129,   115,   116,     0,
       0,   130,   131,     0,     0,   241,   117,   118,   119,   120,
       0,     0,     0,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   120,   121,   122,   217,
     123,   124,   125,   126,   127,   128,   129,     0,     0,     0,
       0,   130,   131,   218,   121,   122,     0,   123,   124,   125,
     126,   127,   128,   129,   115,   116,     0,     0,   130,   131,
     255,     0,     0,   117,   118,   119,   120,     0,     0,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   120,     0,   121,   122,   216,   123,   124,   125,
     126,   127,   128,   129,     0,     0,     0,     0,   130,   131,
     121,   122,     0,   123,   124,   125,   126,   127,   128,   129,
     115,   116,     0,     0,   130,   131,     0,     0,     0,   117,
     118,   119,   120,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,     0,     0,
       0,   122,   116,   123,   124,   125,   126,   127,   128,   129,
     117,   118,   119,   120,   130,   131,   122,   116,   123,   124,
     125,   126,   127,   128,   129,   117,   118,   119,   120,   130,
     131,     0,    12,     0,     0,    13,     0,   126,   127,   128,
     129,     0,     0,     0,     0,   130,   131,     0,     0,     0,
      22,    67,    24,   127,   128,   129,     0,     0,     0,     0,
     130,   131,    25,    26,    27,     0,     0,     0,     0,     0,
      28
};

static const yytype_int16 yycheck[] =
{
       3,    12,    13,    61,    15,    42,    43,    16,    90,    18,
      90,    48,     7,    50,    25,    26,    27,    28,   195,   196,
      21,    37,     7,     3,    39,     9,    10,    11,    12,     9,
      10,    11,     7,     7,    45,     8,    34,    95,    35,    54,
      98,    35,    58,    16,    17,    18,    19,    58,    36,    19,
       8,    35,    46,    35,     8,    53,    57,    52,    16,    70,
      37,    19,    16,    17,    75,    19,    51,    78,    79,    42,
      43,    44,    45,    46,    35,   252,    51,    51,    51,    52,
      91,    51,    52,    60,    51,    46,    51,    35,    46,    54,
      57,    54,    46,    51,    52,   106,    35,    51,    52,    60,
      34,    35,    37,    54,   115,   116,   117,   118,   119,    89,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,    16,    54,    58,    19,    59,   208,    35,   208,    36,
     139,   111,    54,     7,     8,     3,     4,   140,   141,    34,
      35,    36,    16,    17,    18,    19,     8,    54,    59,    57,
     208,    46,    47,    48,    16,    17,    18,    19,   169,    54,
      60,    19,    60,    37,    38,    60,    40,    41,    42,    43,
      44,    45,    46,    37,    60,    57,   213,    51,    52,    41,
      42,    43,    44,    45,    46,    37,    60,    60,    46,    51,
      52,    55,   172,    51,    52,    37,    27,    60,    54,    54,
      60,   212,     7,    55,    60,   216,   217,    60,    54,     0,
      22,    54,    35,    55,     5,     6,    51,    55,     9,    10,
      11,    12,    13,    14,    15,    16,    35,    35,    19,   232,
      21,    35,    23,    24,    25,    26,    27,    28,    55,    30,
      37,    57,     5,    34,    35,    36,     9,    10,    11,    12,
       9,    10,    11,    12,   257,    46,    47,    48,    53,     7,
      32,     7,    54,    54,    34,    56,    57,     5,     6,    60,
      35,     9,    10,    11,    12,    13,    14,    15,    16,    36,
      36,    19,   229,    21,   253,    23,    24,    25,    26,    27,
      28,   257,    30,   152,     1,     5,    34,    35,    36,     9,
      10,    11,    12,    43,   224,    -1,    -1,    -1,    46,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,    57,
      58,    -1,    60,     5,     6,    35,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    46,    19,    -1,    21,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,     7,
       8,    -1,    34,    35,    36,    -1,    -1,    -1,    16,    17,
      18,    19,    -1,    -1,    46,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    16,    57,    58,    19,    60,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,     7,
       8,    -1,    -1,    51,    52,    -1,    -1,    -1,    16,    17,
      18,    19,    60,    -1,    46,    -1,     8,    -1,    -1,    51,
      52,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    45,    46,     7,
       8,    -1,    -1,    51,    52,    -1,    -1,    -1,    16,    17,
      18,    19,    60,    45,    46,     7,     8,    -1,    -1,    51,
      52,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    37,
      38,     8,    40,    41,    42,    43,    44,    45,    46,    16,
      17,    18,    19,    51,    52,    37,    38,    55,    40,    41,
      42,    43,    44,    45,    46,     7,     8,    -1,    -1,    51,
      52,    -1,    -1,    55,    16,    17,    18,    19,    -1,    46,
      -1,     7,     8,    -1,    51,    52,    -1,    -1,    -1,    -1,
      16,    17,    18,    19,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
      52,    37,    38,    55,    40,    41,    42,    43,    44,    45,
      46,     7,     8,    -1,    -1,    51,    52,    -1,    -1,    55,
      16,    17,    18,    19,    -1,    -1,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      -1,    37,    38,    -1,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    37,    38,    55,
      40,    41,    42,    43,    44,    45,    46,     7,     8,    -1,
      -1,    51,    52,    -1,    -1,    55,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    16,    17,    18,    19,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    51,    52,    53,    37,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,     7,     8,    -1,    -1,    51,    52,
      53,    -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    18,    19,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,    52,
      37,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
       7,     8,    -1,    -1,    51,    52,    -1,    -1,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    -1,    -1,
      -1,    38,     8,    40,    41,    42,    43,    44,    45,    46,
      16,    17,    18,    19,    51,    52,    38,     8,    40,    41,
      42,    43,    44,    45,    46,    16,    17,    18,    19,    51,
      52,    -1,    16,    -1,    -1,    19,    -1,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,    -1,
      34,    35,    36,    44,    45,    46,    -1,    -1,    -1,    -1,
      51,    52,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    62,     0,     5,     6,     9,    10,    11,    12,    13,
      14,    15,    16,    19,    21,    23,    24,    25,    26,    27,
      28,    30,    34,    35,    36,    46,    47,    48,    54,    56,
      57,    60,    66,    70,    75,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   105,   106,   107,   109,   111,   112,
      35,    85,   110,    36,   110,   110,   110,    35,   109,   109,
      54,    60,   109,    35,   112,    54,    35,   112,    54,    54,
      39,    54,   109,   109,   109,   109,    35,     3,     4,    71,
      72,     7,    52,    79,    80,    37,    60,    59,    76,    60,
      60,    60,   105,    93,   105,   109,    60,   105,   105,    27,
      73,    46,    60,    74,   110,     7,     8,    16,    17,    18,
      19,    37,    38,    40,    41,    42,    43,    44,    45,    46,
      51,    52,    60,   109,   113,    74,    51,    57,    60,     7,
       7,     7,   109,    60,    60,    60,   109,    60,   109,   109,
      55,    54,    57,   110,    75,    77,    78,   107,   109,    34,
      53,     7,    74,    34,    35,    59,    74,    22,   109,    54,
      58,    87,    35,   110,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
      55,    35,    35,   108,   112,    85,    85,    55,    60,    55,
      55,    35,    63,    64,    65,    73,    54,    55,    37,    53,
      57,    83,     7,    55,   109,   110,    39,    39,    53,    37,
      58,    76,    76,    32,   103,   104,     7,    37,    55,    37,
      55,    58,    54,    69,    74,    75,    34,    81,    82,   109,
     105,    55,   109,   109,    35,   104,    36,    54,    36,    64,
      67,    68,    85,    37,    58,    53,    36,    37,    55,    76,
      81,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    68,    68,    69,    69,    70,    71,
      71,    71,    72,    73,    73,    74,    74,    74,    75,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    78,    78,
      79,    79,    80,    80,    81,    82,    82,    83,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    88,    89,
      90,    91,    92,    93,    93,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   103,   104,   105,   106,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   112,   113,   113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     2,     1,
       3,     0,     5,     2,     1,     3,     0,     3,     5,     4,
       1,     1,     3,     0,     2,     1,     2,     3,     3,     3,
       2,     0,     2,     2,     2,     0,     1,     1,     3,     3,
       2,     3,     0,     1,     1,     1,     3,     3,     2,     3,
       4,     3,     5,     1,     1,     1,     1,     2,     1,     2,
       2,     3,     3,     3,     2,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     3,     2,     2,     2,     4,     5,
       5,     4,     3,     2,     2,     2,     4,     2,     5,     4,
       2,     1,     2,     5,     5,     1,     2,     1,     3,     1,
       5,     1,     3,     1,     3,     4,     6,     3,     3,     1,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     5,     1,
       1,     1,     3,     2,     3,     0,     1
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
#line 90 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1629 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 91 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1636 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 92 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1643 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 95 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = synth::Importer::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1651 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 97 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  synth::Importer::AddStrParam((yyvsp[-2].import_param), (yyvsp[0].str));
  (yyval.import_param) = (yyvsp[-2].import_param);
}
#line 1660 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 102 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = synth::Importer::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1668 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = (yyvsp[-1].import_param);
}
#line 1676 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 108 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = synth::Importer::BuildParamSet(nullptr, (yyvsp[0].import_param));
}
#line 1684 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 110 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = synth::Importer::BuildParamSet((yyvsp[-2].import_params), (yyvsp[0].import_param));
}
#line 1692 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource(nullptr);
}
#line 1700 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource((yyvsp[-1].import_params));
}
#line 1708 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 120 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 1716 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 124 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1724 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 126 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1732 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1740 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 132 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1748 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 136 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1756 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1766 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 149 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1774 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 153 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1781 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1788 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 157 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), false, nullptr);
}
#line 1796 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 159 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, nullptr);
}
#line 1804 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 161 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, (yyvsp[-1].sym));
}
#line 1812 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 165 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::BuildVarDecl((yyvsp[-2].sym), (yyvsp[-1].width_spec).width, (yyvsp[-1].width_spec).name, (yyvsp[0].var_decl));
}
#line 1820 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 167 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1827 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 168 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1834 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 171 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::MakeInt(false, 32));
}
#line 1842 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 173 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::MakeInt(false, (yyvsp[0].num)));
}
#line 1850 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 175 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym));
}
#line 1858 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 177 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::Null());
}
#line 1866 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 181 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1875 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1883 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 188 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1891 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 190 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1899 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 192 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* un-typed argument */
  (yyval.var_decl_set) = nullptr;
}
#line 1908 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 197 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = 0;
}
#line 1916 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1924 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 203 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = -1;
}
#line 1932 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 205 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1940 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 209 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1948 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 213 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num));
  (yyval.array) = array;
}
#line 1958 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 217 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num));
  (yyval.array) = (yyvsp[-2].array);
}
#line 1967 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 222 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-1].array);
}
#line 1975 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 226 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-1].var_decl), (yyvsp[0].num));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-1].var_decl));
}
#line 1984 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 229 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].var_decl)->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl));
}
#line 1993 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 232 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-3].var_decl), (yyvsp[-2].num));
  Builder::SetArrayInitializer((yyvsp[-3].var_decl), (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-3].var_decl));
}
#line 2003 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 236 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  sym_t type = Builder::TypeNameFromVarDeclSet((yyvsp[-2].var_decl_set));
  WidthSpec w = Builder::GetWidthSpecFromVarDeclSet((yyvsp[-2].var_decl_set));
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-2].var_decl_set), Builder::BuildVarDecl(type, w.width, w.name, (yyvsp[0].var_decl)));
}
#line 2013 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 240 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-4].var_decl_set), (yyvsp[-2].var_decl));
}
#line 2021 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 244 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2029 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 246 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2037 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 248 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2045 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 250 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2053 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 255 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2060 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 258 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2068 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 260 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2076 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 262 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2083 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2090 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 264 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2097 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 265 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2105 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 267 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2113 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2120 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 270 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2127 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 271 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2134 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 272 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2141 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 273 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2148 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2155 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 275 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2163 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2171 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 280 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitSpawnStmt((yyvsp[-1].expr));
}
#line 2179 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2186 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 283 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2193 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 284 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2200 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 287 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2208 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 291 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 2216 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 295 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 2224 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 299 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2233 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 304 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-2].stmt)->label_f_);
}
#line 2243 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 310 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2253 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2262 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 317 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2271 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 322 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2280 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 327 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2289 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 332 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2308 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2321 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 356 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2331 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 362 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->label_join_);
}
#line 2342 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2350 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_t_);
  Emitter::EmitGoto((yyvsp[-4].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2362 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 381 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2369 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 384 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2376 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2383 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 388 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2390 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 391 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2398 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 395 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2407 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 400 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2415 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 404 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2423 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 406 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2431 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2439 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 412 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2447 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 414 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2455 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 416 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2463 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 418 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2471 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2479 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 422 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2487 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 424 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2495 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 426 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2503 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 428 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::RefExpr((yyvsp[0].expr));
}
#line 2511 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 430 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2519 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 432 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2527 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 434 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2535 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 436 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2543 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 438 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2551 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 440 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2559 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 442 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2567 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 444 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2575 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 446 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2583 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 448 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2591 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 450 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2599 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 452 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2607 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 454 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].num), true);
}
#line 2615 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 456 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].num), false);
}
#line 2623 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 458 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].num), (yyvsp[0].expr));
}
#line 2631 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 460 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2639 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 462 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2647 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2655 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2663 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 470 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2671 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2679 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 478 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2687 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 482 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2695 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 484 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2703 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;


#line 2707 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
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
#line 488 "src/fe/parser.ypp" /* yacc.c:1906  */

