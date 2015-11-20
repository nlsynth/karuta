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
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "dfg/imported_resource.h"

extern int yylex();
extern void yyerror(const char *msg);


#line 89 "src/fe/libparse_la-parser.cpp" /* yacc.c:339  */

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
    K_ENUM = 259,
    K_IMPORT = 260,
    K_STRUCT = 261,
    K_ASSIGN = 262,
    K_SHIFT = 263,
    K_INT = 264,
    K_BOOL = 265,
    K_STRING = 266,
    K_OBJECT = 267,
    K_THREAD = 268,
    K_CHANNEL = 269,
    K_ADD_SUB = 270,
    K_LG_COMPARE = 271,
    K_EQ_COMPARE = 272,
    K_INC_DEC = 273,
    K_CONST = 274,
    K_IF = 275,
    K_ELSE = 276,
    K_RETURN = 277,
    K_GOTO = 278,
    K_FOR = 279,
    K_SPAWN = 280,
    K_WHILE = 281,
    K_DO = 282,
    K_CONTINUE = 283,
    K_SWITCH = 284,
    K_CASE = 285,
    K_DEFAULT = 286,
    K_BREAK = 287,
    NUM = 288,
    SYM = 289,
    STR = 290,
    K_LOGIC_OR = 291,
    K_LOGIC_AND = 292,
    K_BIT_CONCAT = 293,
    SIGN = 294,
    ADDRESS = 295
  };
#endif
/* Tokens.  */
#define K_DEF 258
#define K_ENUM 259
#define K_IMPORT 260
#define K_STRUCT 261
#define K_ASSIGN 262
#define K_SHIFT 263
#define K_INT 264
#define K_BOOL 265
#define K_STRING 266
#define K_OBJECT 267
#define K_THREAD 268
#define K_CHANNEL 269
#define K_ADD_SUB 270
#define K_LG_COMPARE 271
#define K_EQ_COMPARE 272
#define K_INC_DEC 273
#define K_CONST 274
#define K_IF 275
#define K_ELSE 276
#define K_RETURN 277
#define K_GOTO 278
#define K_FOR 279
#define K_SPAWN 280
#define K_WHILE 281
#define K_DO 282
#define K_CONTINUE 283
#define K_SWITCH 284
#define K_CASE 285
#define K_DEFAULT 286
#define K_BREAK 287
#define NUM 288
#define SYM 289
#define STR 290
#define K_LOGIC_OR 291
#define K_LOGIC_AND 292
#define K_BIT_CONCAT 293
#define SIGN 294
#define ADDRESS 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 16 "parser.ypp" /* yacc.c:355  */

  class ArrayInitializer *array;
  class Expr *expr;
  class Stmt *stmt;
  class VarDecl *var_decl;
  class VarDeclSet *var_decl_set;
  class NstBlock *block;
  const char *str;
  sym_t sym;
  uint64_t num;
  const class numeric::Width *width;
  class ImportParam *import_param;
  class ImportParamSet *import_params;

#line 224 "src/fe/libparse_la-parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE z_yylval;

int z_yyparse (void);

#endif /* !YY_Z_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 239 "src/fe/libparse_la-parser.cpp" /* yacc.c:358  */

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
#define YYLAST   828

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  261

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,    57,     2,     2,    44,     2,
      53,    54,    45,     2,    36,     2,    50,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    58,
       2,     2,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,    42,    56,    47,     2,     2,     2,
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
      35,    39,    40,    41,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    90,    93,    95,   100,   102,   106,
     108,   112,   113,   117,   121,   123,   127,   129,   133,   137,
     142,   146,   147,   150,   152,   154,   158,   160,   162,   165,
     167,   169,   171,   175,   178,   182,   184,   186,   192,   194,
     198,   200,   204,   208,   212,   217,   221,   224,   227,   231,
     234,   238,   240,   242,   244,   249,   252,   254,   256,   257,
     258,   260,   262,   264,   266,   267,   268,   269,   270,   271,
     272,   274,   275,   277,   279,   280,   283,   287,   291,   296,
     302,   306,   309,   314,   319,   324,   339,   348,   354,   358,
     361,   362,   365,   368,   372,   377,   381,   383,   387,   390,
     393,   394,   397,   399,   401,   403,   405,   407,   409,   411,
     413,   415,   417,   419,   421,   423,   425,   427,   429,   431,
     433,   435,   437,   439,   441,   443,   445,   447,   449,   453,
     455,   459,   463,   467,   469
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_ENUM", "K_IMPORT",
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
  "WHILE_STMT", "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE",
  "BLOCK", "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "STRUCT_DECL",
  "STRUCT_DECL_HEAD", "STRUCT_ELEMENT_LIST", "EXPR", "VAR", "FUNCALL_HEAD",
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
     285,   286,   287,   288,   289,   290,    44,    63,    58,   291,
     292,   293,   124,    94,    38,    42,    33,   126,   294,   295,
      46,    91,    93,    40,    41,   123,   125,    35,    59
};
# endif

#define YYPACT_NINF -179

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-179)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -179,   136,  -179,    -2,   175,   -13,    -6,  -179,  -179,  -179,
    -179,    -2,    -2,   775,   775,    24,    45,    50,    32,    -2,
      40,    68,    75,  -179,   128,  -179,   775,   775,   775,   775,
    -179,  -179,  -179,    86,   242,     0,    -1,    95,  -179,  -179,
     135,   142,    68,    -7,  -179,   775,   143,  -179,    68,  -179,
    -179,  -179,  -179,  -179,    41,   148,   121,   288,   114,   775,
    -179,  -179,   176,   -25,   118,   149,  -179,    12,    16,    46,
      46,   775,  -179,   327,   159,   114,   169,   775,   173,   775,
     212,   775,  -179,    46,    46,    46,   405,   178,   185,  -179,
     187,   206,   -25,   775,   101,   240,  -179,   -25,  -179,     1,
     -25,  -179,  -179,   227,  -179,  -179,   642,   775,  -179,   210,
     216,  -179,  -179,   208,  -179,   242,   775,   775,   775,   775,
     775,  -179,   775,   775,   775,   775,   775,   775,   775,   775,
     775,   775,  -179,   225,  -179,   642,   207,  -179,  -179,   226,
    -179,    -2,   186,   421,  -179,  -179,  -179,   366,  -179,   461,
     209,   477,  -179,   257,    90,  -179,    36,  -179,   214,   168,
     681,   220,  -179,   218,   274,   244,  -179,  -179,  -179,   517,
    -179,  -179,    -2,   208,    64,    17,   681,    25,    76,    23,
     747,   681,   629,   732,   743,   344,   382,    38,   577,    46,
     573,  -179,  -179,  -179,    73,  -179,    95,  -179,  -179,  -179,
     775,   253,   122,   251,  -179,   178,  -179,   265,   186,  -179,
    -179,  -179,  -179,   260,  -179,   775,   264,    68,   208,  -179,
    -179,    66,   775,   775,  -179,   267,  -179,  -179,   533,  -179,
     253,  -179,  -179,   272,  -179,  -179,  -179,  -179,   154,    95,
    -179,  -179,    99,   681,  -179,  -179,  -179,   694,   590,  -179,
    -179,  -179,  -179,   186,  -179,  -179,   260,  -179,  -179,  -179,
    -179
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,    51,    52,    54,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   128,   129,   127,     0,     0,     0,     0,
      94,    56,     3,    11,    33,    40,     0,    29,    71,     4,
       0,     0,     0,     0,    65,     0,     0,    66,     0,    67,
      68,    69,    64,    21,     0,     0,     0,     0,   102,   133,
     107,   129,     0,     0,     0,     0,    99,     0,     0,   125,
     124,     0,    63,     0,   129,     0,     0,     0,     0,     0,
       0,     0,    55,   110,   108,   109,     0,     0,     0,    35,
       0,    34,     0,     0,     0,    41,    46,     0,    70,     0,
       0,    74,    75,    80,    82,    81,    84,     0,    87,     0,
       0,    58,    28,    23,    59,     0,     0,     0,     0,     0,
       0,   123,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,   131,   134,     0,    20,    27,     0,
      72,     0,     0,     0,    62,    61,    60,     0,    73,     0,
       0,     0,   103,     0,     0,     9,     0,    21,    16,     0,
      47,     0,    38,     0,    49,    30,    32,    26,    79,     0,
      93,    22,   129,    24,     0,     0,   114,   113,   111,   115,
     116,   106,     0,   121,   122,   117,   119,   120,   118,   112,
       0,   130,   132,    96,     0,    76,    29,    78,    83,    86,
       0,     0,     0,     0,     8,     0,    12,     0,     0,    19,
      37,    36,    39,     0,    48,     0,     0,     0,    25,   100,
      98,     0,     0,     0,   104,     0,    95,    77,     0,    92,
      89,    90,     7,     0,     6,    10,    18,    14,     0,    29,
      42,    43,     0,    50,    31,    85,   101,   126,     0,    97,
      88,    91,     5,     0,    17,    13,     0,    45,   105,    15,
      44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,    97,  -179,  -179,    55,  -179,  -179,  -179,
    -179,  -179,   152,   -58,   -28,  -178,  -179,  -179,  -179,  -179,
      57,  -179,  -179,  -104,    -4,  -179,   313,  -179,  -179,  -179,
    -179,   273,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
      85,   -18,  -179,    11,  -179,  -179,  -179,  -179,   -12,    33,
    -179,    -9,  -179
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   154,   155,   156,    88,   237,   238,   209,    32,
      33,    34,   109,   112,    35,   100,    90,    91,    95,    96,
     241,   242,   214,    36,    37,    38,   171,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,   230,
     231,    52,    53,    92,   194,    55,    56,   175,    57,    58,
      59,    60,   136
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      63,    69,    70,    80,    73,   138,    89,    93,    76,    61,
      78,   174,    54,    15,    83,    84,    85,    86,   227,   141,
     110,     4,    65,   142,   103,   105,     7,     8,     9,    10,
     108,   117,    61,   106,   165,    97,    62,    64,   118,   164,
     118,   121,   167,   121,    67,    68,   117,   135,    30,    66,
      75,    94,    75,   118,   119,   120,   121,    98,   166,   143,
      13,   255,   133,    14,   121,   147,   133,   149,   130,   151,
     130,   221,   205,   220,   131,    61,   131,    71,    23,    61,
      25,   160,   129,   130,    74,    77,   110,   113,   206,   131,
      26,    27,    28,    79,   121,   169,   113,   131,    29,   111,
      97,   210,    97,    72,   176,   177,   178,   179,   180,   225,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
      54,   130,   219,    30,   246,   113,   203,   131,    81,   226,
     113,   211,   195,   113,   161,   256,     2,    87,   196,     3,
       4,     5,     6,   173,   204,     7,     8,     9,    10,    11,
      12,    13,    99,   162,    14,   257,    15,   232,    16,    17,
      18,    19,    20,    21,   133,    22,    82,   134,   133,    23,
      24,    25,     4,   139,    75,   233,   115,     7,     8,     9,
      10,    26,    27,    28,     7,     8,     9,    10,   228,    29,
     253,    30,   113,   101,    31,     7,     8,     9,    10,   245,
     102,   107,    61,   243,   239,   218,   114,   140,   254,    61,
     247,   248,   153,   110,     4,     5,     6,   145,    54,     7,
       8,     9,    10,    11,    12,    13,   133,   146,    14,   137,
      15,   148,    16,    17,    18,    19,    20,    21,   150,    22,
     157,   158,   159,    23,    24,    25,     4,   163,   168,   239,
     172,     7,     8,     9,    10,    26,    27,    28,   133,   191,
     193,   192,   200,    29,   202,    30,   170,   208,    31,     4,
       5,     6,   212,   213,     7,     8,     9,    10,    11,    12,
      13,   215,   216,    14,   229,    15,   234,    16,    17,    18,
      19,    20,    21,   240,    22,   116,   117,   244,    23,    24,
      25,   249,   235,   118,   119,   120,   121,   252,   259,   207,
      26,    27,    28,   260,    39,   251,   104,     0,    29,     0,
      30,   236,     0,    31,   122,   123,     0,   124,   125,   126,
     127,   128,   129,   130,   116,   117,     0,     0,     0,   131,
       0,     0,   118,   119,   120,   121,   132,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,     0,   124,   125,   126,   127,
     128,   129,   130,   116,   117,     0,     0,     0,   131,     0,
       0,   118,   119,   120,   121,   144,   127,   128,   129,   130,
     117,     0,     0,     0,     0,   131,     0,   118,   119,   120,
     121,     0,   122,   123,     0,   124,   125,   126,   127,   128,
     129,   130,   116,   117,     0,     0,     0,   131,     0,     0,
     118,   119,   120,   121,   198,   128,   129,   130,   116,   117,
       0,     0,     0,   131,     0,     0,   118,   119,   120,   121,
       0,   122,   123,     0,   124,   125,   126,   127,   128,   129,
     130,     0,     0,     0,     0,     0,   131,   122,   123,   152,
     124,   125,   126,   127,   128,   129,   130,     0,   116,   117,
       0,     0,   131,     0,     0,   197,   118,   119,   120,   121,
       0,     0,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,     0,   122,   123,     0,
     124,   125,   126,   127,   128,   129,   130,     0,     0,     0,
       0,     0,   131,   122,   123,   199,   124,   125,   126,   127,
     128,   129,   130,     0,   116,   117,     0,     0,   131,     0,
       0,   201,   118,   119,   120,   121,     0,     0,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,     0,   122,   123,     0,   124,   125,   126,   127,
     128,   129,   130,     0,     0,     0,     0,     0,   131,   122,
     123,   217,   124,   125,   126,   127,   128,   129,   130,     0,
     116,   117,     0,     0,   131,   117,     0,   250,   118,   119,
     120,   121,   118,   119,   120,   121,     0,   116,   117,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   223,   124,   125,   126,   127,   128,   129,   130,     0,
       0,     0,   130,     0,   131,   224,   122,   123,   131,   124,
     125,   126,   127,   128,   129,   130,   116,   117,     0,     0,
       0,   131,   258,     0,   118,   119,   120,   121,     0,   116,
     117,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,     0,     0,     0,     0,   122,   123,   222,   124,   125,
     126,   127,   128,   129,   130,     0,     0,     0,   122,   123,
     131,   124,   125,   126,   127,   128,   129,   130,   116,   117,
       0,     0,     0,   131,     0,     0,   118,   119,   120,   121,
       0,     0,   117,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,     0,     0,     0,     0,     0,   123,     0,
     124,   125,   126,   127,   128,   129,   130,     0,     0,     0,
       0,   123,   131,   124,   125,   126,   127,   128,   129,   130,
     117,     0,     0,     0,     0,   131,     0,   118,   119,   120,
     121,   117,     0,     0,     0,   117,     0,     0,   118,   119,
     120,   121,   118,   119,     0,   121,     0,     0,     0,     0,
       0,     0,   125,   126,   127,   128,   129,   130,     0,     0,
       0,     0,     0,   131,   126,   127,   128,   129,   130,     0,
      13,     0,   130,    14,   131,     0,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,    61,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    27,    28,     0,     0,     0,     0,     0,    29
};

static const yytype_int16 yycheck[] =
{
       4,    13,    14,    21,    16,    63,    34,     7,    17,    34,
      19,   115,     1,    20,    26,    27,    28,    29,   196,     7,
      45,     4,    35,     7,    42,    43,     9,    10,    11,    12,
      48,     8,    34,    45,    33,    36,     3,     4,    15,    97,
      15,    18,   100,    18,    11,    12,     8,    59,    55,    55,
      17,    51,    19,    15,    16,    17,    18,    58,    57,    71,
      15,   239,    50,    18,    18,    77,    50,    79,    45,    81,
      45,   175,    36,    56,    51,    34,    51,    53,    33,    34,
      35,    93,    44,    45,    34,    53,    45,    54,    52,    51,
      45,    46,    47,    53,    18,   107,    63,    51,    53,    58,
      36,   159,    36,    58,   116,   117,   118,   119,   120,    36,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     109,    45,    58,    55,    58,    92,    36,    51,    53,    56,
      97,   159,   141,   100,    33,    36,     0,    51,   142,     3,
       4,     5,     6,   110,    54,     9,    10,    11,    12,    13,
      14,    15,    57,    52,    18,    56,    20,    35,    22,    23,
      24,    25,    26,    27,    50,    29,    38,    53,    50,    33,
      34,    35,     4,    55,   141,    53,    55,     9,    10,    11,
      12,    45,    46,    47,     9,    10,    11,    12,   200,    53,
      36,    55,   159,    58,    58,     9,    10,    11,    12,   217,
      58,    58,    34,   215,   208,   172,    58,    58,    54,    34,
     222,   223,    34,    45,     4,     5,     6,    58,   207,     9,
      10,    11,    12,    13,    14,    15,    50,    58,    18,    53,
      20,    58,    22,    23,    24,    25,    26,    27,    26,    29,
      55,    54,    36,    33,    34,    35,     4,     7,    21,   253,
      34,     9,    10,    11,    12,    45,    46,    47,    50,    34,
      34,    54,    53,    53,     7,    55,    56,    53,    58,     4,
       5,     6,    52,    55,     9,    10,    11,    12,    13,    14,
      15,     7,    38,    18,    31,    20,    35,    22,    23,    24,
      25,    26,    27,    33,    29,     7,     8,    33,    33,    34,
      35,    34,   205,    15,    16,    17,    18,    35,   253,   157,
      45,    46,    47,   256,     1,   230,    43,    -1,    53,    -1,
      55,    56,    -1,    58,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,     7,     8,    -1,    -1,    -1,    51,
      -1,    -1,    15,    16,    17,    18,    58,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,     7,     8,    -1,    -1,    -1,    51,    -1,
      -1,    15,    16,    17,    18,    58,    42,    43,    44,    45,
       8,    -1,    -1,    -1,    -1,    51,    -1,    15,    16,    17,
      18,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,     7,     8,    -1,    -1,    -1,    51,    -1,    -1,
      15,    16,    17,    18,    58,    43,    44,    45,     7,     8,
      -1,    -1,    -1,    51,    -1,    -1,    15,    16,    17,    18,
      -1,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    36,    37,    54,
      39,    40,    41,    42,    43,    44,    45,    -1,     7,     8,
      -1,    -1,    51,    -1,    -1,    54,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    17,    18,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    51,    36,    37,    54,    39,    40,    41,    42,
      43,    44,    45,    -1,     7,     8,    -1,    -1,    51,    -1,
      -1,    54,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    18,    -1,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    51,    36,
      37,    54,    39,    40,    41,    42,    43,    44,    45,    -1,
       7,     8,    -1,    -1,    51,     8,    -1,    54,    15,    16,
      17,    18,    15,    16,    17,    18,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    45,    -1,    51,    52,    36,    37,    51,    39,
      40,    41,    42,    43,    44,    45,     7,     8,    -1,    -1,
      -1,    51,    52,    -1,    15,    16,    17,    18,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    36,    37,
      51,    39,    40,    41,    42,    43,    44,    45,     7,     8,
      -1,    -1,    -1,    51,    -1,    -1,    15,    16,    17,    18,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    37,    51,    39,    40,    41,    42,    43,    44,    45,
       8,    -1,    -1,    -1,    -1,    51,    -1,    15,    16,    17,
      18,     8,    -1,    -1,    -1,     8,    -1,    -1,    15,    16,
      17,    18,    15,    16,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    -1,    51,    41,    42,    43,    44,    45,    -1,
      15,    -1,    45,    18,    51,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,     0,     3,     4,     5,     6,     9,    10,    11,
      12,    13,    14,    15,    18,    20,    22,    23,    24,    25,
      26,    27,    29,    33,    34,    35,    45,    46,    47,    53,
      55,    58,    68,    69,    70,    73,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,   100,   101,   102,   104,   105,   107,   108,   109,
     110,    34,   108,    83,   108,    35,    55,   108,   108,   107,
     107,    53,    58,   107,    34,   108,   110,    53,   110,    53,
     100,    53,    38,   107,   107,   107,   107,    51,    64,    73,
      75,    76,   102,     7,    51,    77,    78,    36,    58,    57,
      74,    58,    58,   100,    90,   100,   107,    58,   100,    71,
      45,    58,    72,   108,    58,    55,     7,     8,    15,    16,
      17,    18,    36,    37,    39,    40,    41,    42,    43,    44,
      45,    51,    58,    50,    53,   107,   111,    53,    72,    55,
      58,     7,     7,   107,    58,    58,    58,   107,    58,   107,
      26,   107,    54,    34,    61,    62,    63,    55,    54,    36,
     107,    33,    52,     7,    72,    33,    57,    72,    21,   107,
      56,    85,    34,   108,    82,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,    34,    54,    34,   103,   110,    83,    54,    58,    54,
      53,    54,     7,    36,    54,    36,    52,    71,    53,    67,
      72,    73,    52,    55,    81,     7,    38,    54,   108,    58,
      56,    82,    38,    38,    52,    36,    56,    74,   107,    31,
      98,    99,    35,    53,    35,    62,    56,    65,    66,    83,
      33,    79,    80,   107,    33,   100,    58,   107,   107,    34,
      54,    99,    35,    36,    54,    74,    36,    56,    52,    65,
      79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    69,
      70,    71,    71,    72,    72,    72,    73,    73,    73,    74,
      74,    74,    74,    75,    75,    76,    76,    76,    77,    77,
      78,    78,    79,    80,    80,    81,    82,    82,    82,    82,
      82,    83,    83,    83,    83,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    87,    88,    89,
      90,    90,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    98,    99,   100,   101,   102,   103,   103,   104,   105,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   108,
     108,   109,   110,   111,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     2,     1,
       3,     0,     3,     2,     1,     3,     0,     3,     5,     4,
       3,     0,     2,     1,     2,     3,     3,     3,     2,     0,
       2,     4,     2,     0,     1,     1,     3,     3,     2,     3,
       0,     1,     1,     1,     3,     3,     2,     3,     4,     3,
       5,     1,     1,     1,     1,     2,     1,     2,     2,     2,
       3,     3,     3,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     3,     3,     2,     2,     4,     5,     4,     3,
       2,     2,     2,     4,     2,     5,     4,     2,     6,     5,
       1,     2,     1,     3,     1,     5,     1,     3,     4,     2,
       2,     3,     1,     3,     4,     6,     3,     1,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     5,     1,     1,     1,
       3,     2,     3,     0,     1
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
#line 88 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1624 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 89 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1631 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 90 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1638 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 93 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = dfg::Importer::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1646 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 95 "parser.ypp" /* yacc.c:1646  */
    {
  dfg::Importer::AddStrParam((yyvsp[-2].import_param), (yyvsp[0].str));
  (yyval.import_param) = (yyvsp[-2].import_param);
}
#line 1655 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 100 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = dfg::Importer::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1663 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 102 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = (yyvsp[-1].import_param);
}
#line 1671 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = dfg::Importer::BuildParamSet(NULL, (yyvsp[0].import_param));
}
#line 1679 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = dfg::Importer::BuildParamSet((yyvsp[-2].import_params), (yyvsp[0].import_param));
}
#line 1687 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 112 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1694 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 113 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource((yyvsp[-1].import_params));
}
#line 1702 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[-1].sym), (yyvsp[0].width));
}
#line 1710 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 121 "parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(NULL, (yyvsp[0].var_decl));
}
#line 1718 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1726 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 127 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(NULL, NULL);
}
#line 1734 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 129 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1742 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 133 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1750 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 137 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1759 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 142 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1767 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1774 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 147 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1781 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 150 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), false, NULL);
}
#line 1789 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 152 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, NULL);
}
#line 1797 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 154 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, (yyvsp[-1].sym));
}
#line 1805 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 158 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::BuildVarDecl((yyvsp[-2].sym), (yyvsp[-1].width), (yyvsp[0].var_decl));
}
#line 1813 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 160 "parser.ypp" /* yacc.c:1646  */
    {
//  $$ = NULL; // NstBuilder::BuildVarDecl($2, NULL, $3);
}
#line 1821 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 162 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 1828 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 165 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, 32, 0);
}
#line 1836 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 167 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, (yyvsp[0].num), 0);
}
#line 1844 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 169 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::MakeInt(false, (yyvsp[-2].num), (yyvsp[0].num));
}
#line 1852 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 171 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width) = numeric::Width::Null();
}
#line 1860 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 175 "parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = NULL; // NstBuilder::ArgDeclList(NULL, NULL);
}
#line 1869 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 178 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1877 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 182 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList(NULL, (yyvsp[0].var_decl));
}
#line 1885 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 184 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1893 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 186 "parser.ypp" /* yacc.c:1646  */
    {
  /* un-typed argument */
  //  NstStmt *stmt = NstBuilder::BuildVarDecl(NULL, NULL, $3);
  (yyval.var_decl_set) = NULL; // NstBuilder::ArgDeclList($1, stmt);
}
#line 1903 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 192 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = 0;
}
#line 1911 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 194 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1919 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 198 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = -1;
}
#line 1927 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 200 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1935 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 204 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1943 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 208 "parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num));
  (yyval.array) = array;
}
#line 1953 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 212 "parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num));
  (yyval.array) = (yyvsp[-2].array);
}
#line 1962 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 217 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-1].array);
}
#line 1970 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 221 "parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-1].var_decl), (yyvsp[0].num));
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-1].var_decl));
}
#line 1979 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 224 "parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].var_decl)->initial_val = (yyvsp[0].expr);
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-2].var_decl));
}
#line 1988 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 227 "parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-3].var_decl), (yyvsp[-2].num));
  Builder::SetArrayInitializer((yyvsp[-3].var_decl), (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(NULL, (yyvsp[-3].var_decl));
}
#line 1998 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 231 "parser.ypp" /* yacc.c:1646  */
    {
  sym_t type = Builder::TypeNameFromVarDeclSet((yyvsp[-2].var_decl_set));
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-2].var_decl_set), Builder::BuildVarDecl(type, NULL, (yyvsp[0].var_decl)));
}
#line 2007 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 234 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-4].var_decl_set), (yyvsp[-2].var_decl));
}
#line 2015 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 238 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2023 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 240 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2031 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 242 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2039 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 244 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2047 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 249 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2054 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 252 "parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2062 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 254 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2070 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 256 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2077 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 257 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2084 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 258 "parser.ypp" /* yacc.c:1646  */
    {
  // NstEmitter::EmitTransition($2);
}
#line 2092 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 260 "parser.ypp" /* yacc.c:1646  */
    {
  // NstEmitter::EmitGotoStmt($2);
}
#line 2100 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 262 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2108 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 264 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(NULL);
}
#line 2116 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 266 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2123 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 267 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2130 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 268 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2137 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 269 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2144 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 270 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2151 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 271 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2158 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 272 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2166 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 275 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2174 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 277 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitSpawnStmt((yyvsp[-1].expr));
}
#line 2182 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 279 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2189 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 280 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2196 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 283 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2204 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 287 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width));
}
#line 2212 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 291 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2221 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 296 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-2].stmt)->label_f_);
}
#line 2231 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 302 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2241 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 306 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2250 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 309 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2259 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 314 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2268 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 319 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2277 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 324 "parser.ypp" /* yacc.c:1646  */
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
#line 2296 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 339 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2309 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 348 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2319 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 354 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = NULL;
}
#line 2327 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 358 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2334 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 361 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2341 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 362 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2348 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 365 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2355 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 368 "parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2363 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 372 "parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2372 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 377 "parser.ypp" /* yacc.c:1646  */
    {
  // NstEmitter::EmitEnumTypeDecl($2, $4);
}
#line 2380 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 381 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = NULL; // NstBuilder::EnumItemList(NULL, $1);
}
#line 2388 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 383 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = NULL; // NstBuilder::EnumItemList($1, $3);
}
#line 2396 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 387 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2403 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 390 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2410 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 393 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2417 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 394 "parser.ypp" /* yacc.c:1646  */
    {
}
#line 2424 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 397 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2432 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 399 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2440 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 401 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2448 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 403 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2456 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 405 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2464 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 407 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2472 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 409 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2480 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 411 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2488 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 413 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::RefExpr((yyvsp[0].expr));
}
#line 2496 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 415 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2504 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 417 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2512 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 419 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2520 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 421 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2528 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 423 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2536 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 425 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2544 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 427 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2552 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 429 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2560 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 431 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2568 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 433 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2576 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 435 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2584 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 437 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2592 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 439 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].num), true);
}
#line 2600 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 441 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].num), false);
}
#line 2608 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 443 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].num), (yyvsp[0].expr));
}
#line 2616 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 445 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2624 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 447 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2632 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 449 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2640 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 453 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2648 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 455 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2656 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 459 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2664 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 463 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2672 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 467 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = NULL;
}
#line 2680 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 469 "parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2688 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;


#line 2692 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
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
#line 473 "parser.ypp" /* yacc.c:1906  */

