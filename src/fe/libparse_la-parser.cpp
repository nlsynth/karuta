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
    K_STRUCT = 262,
    K_ASSIGN = 263,
    K_SHIFT = 264,
    K_INT = 265,
    K_BOOL = 266,
    K_STRING = 267,
    K_OBJECT = 268,
    K_THREAD = 269,
    K_CHANNEL = 270,
    K_MAILBOX = 271,
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
#define K_STRUCT 262
#define K_ASSIGN 263
#define K_SHIFT 264
#define K_INT 265
#define K_BOOL 266
#define K_STRING 267
#define K_OBJECT 268
#define K_THREAD 269
#define K_CHANNEL 270
#define K_MAILBOX 271
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

#line 230 "src/fe/libparse_la-parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE z_yylval;

int z_yyparse (void);

#endif /* !YY_Z_YY_SRC_FE_LIBPARSE_LA_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 247 "src/fe/libparse_la-parser.cpp" /* yacc.c:358  */

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
#define YYLAST   848

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  276

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
       0,    91,    91,    92,    93,    96,    98,   103,   105,   109,
     111,   115,   117,   121,   125,   127,   131,   133,   137,   141,
     148,   148,   150,   154,   155,   158,   160,   162,   166,   168,
     169,   172,   174,   176,   178,   180,   184,   187,   191,   193,
     195,   200,   202,   206,   208,   212,   216,   220,   225,   229,
     232,   235,   239,   243,   247,   249,   251,   253,   258,   261,
     263,   265,   266,   267,   268,   269,   271,   273,   274,   275,
     276,   277,   278,   279,   281,   282,   284,   286,   287,   288,
     291,   295,   299,   303,   308,   314,   318,   321,   326,   331,
     336,   351,   360,   366,   373,   377,   385,   388,   389,   392,
     395,   399,   404,   408,   410,   414,   417,   420,   421,   424,
     426,   428,   430,   432,   434,   436,   438,   440,   442,   444,
     446,   448,   450,   452,   454,   456,   458,   460,   462,   464,
     466,   468,   470,   472,   474,   476,   478,   482,   484,   488,
     492,   496,   498
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_DEF", "K_FUNC", "K_ENUM", "K_IMPORT",
  "K_STRUCT", "K_ASSIGN", "K_SHIFT", "K_INT", "K_BOOL", "K_STRING",
  "K_OBJECT", "K_THREAD", "K_CHANNEL", "K_MAILBOX", "K_ADD_SUB",
  "K_LG_COMPARE", "K_EQ_COMPARE", "K_INC_DEC", "K_CONST", "K_IF", "K_ELSE",
  "K_RETURN", "K_GOTO", "K_FOR", "K_SPAWN", "K_WHILE", "K_DO",
  "K_CONTINUE", "K_SWITCH", "K_CASE", "K_DEFAULT", "K_BREAK", "NUM", "SYM",
  "STR", "','", "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT",
  "'|'", "'^'", "'&'", "'*'", "'!'", "'~'", "SIGN", "ADDRESS", "'.'",
  "'['", "']'", "'('", "')'", "'@'", "'{'", "'}'", "'#'", "';'", "$accept",
  "input", "IMPORT_PARAM_HEAD", "IMPORT_PARAM", "IMPORT_PARAM_LIST",
  "IMPORT_SPEC", "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC",
  "FUNC_DECL", "FUNC_DECL_HEAD", "FUNC_DECL_NAME", "STMT_LIST",
  "MODIFIED_VAR", "VAR_DECL", "WIDTH_SPEC", "ARG_DECL", "ARG_DECL_LIST",
  "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC", "ARRAY_ELM", "ARRAY_ELM_LIST",
  "ARRAY_INITIALIZER", "VAR_DECL_STMT", "TYPE_NAME", "LABEL", "STMT",
  "THREAD_DECL_STMT", "CHANNEL_DECL_STMT", "MAILBOX_DECL_STMT",
  "IF_COND_PART", "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD", "FOR_COND_PART",
  "FOR_STMT", "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD",
  "DO_WHILE_BODY", "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE",
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
     285,   286,   287,   288,   289,   290,   291,   292,    44,    63,
      58,   293,   294,   295,   124,    94,    38,    42,    33,   126,
     296,   297,    46,    91,    93,    40,    41,    64,   123,   125,
      35,    59
};
# endif

#define YYPACT_NINF -195

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-195)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -195,   174,  -195,   135,    -1,   -33,  -195,  -195,  -195,  -195,
      56,    56,    56,   793,   793,    98,   772,    71,   102,   125,
     111,  -195,   123,  -195,    59,  -195,   793,   793,   793,   793,
     147,  -195,  -195,   189,  -195,     3,    90,    20,  -195,  -195,
     134,   143,   145,   149,   -10,  -195,   793,   152,  -195,   149,
    -195,   149,   186,  -195,  -195,  -195,  -195,    -4,   154,   160,
     319,   793,  -195,  -195,   122,   124,   158,  -195,    13,    25,
      27,   165,    48,    48,   793,  -195,   359,   101,   163,   793,
     165,   166,   793,   793,  -195,  -195,    48,    48,    48,   439,
     171,  -195,  -195,    15,   266,   793,    28,   220,  -195,   122,
    -195,   100,   122,  -195,  -195,  -195,   207,  -195,  -195,   680,
     793,  -195,  -195,   178,   238,   198,  -195,  -195,   188,  -195,
     266,   793,   793,   793,   793,   793,  -195,   793,   793,   793,
     793,   793,   793,   793,   793,   793,   793,   793,  -195,   680,
     190,  -195,   206,   211,  -195,   125,   226,   226,   455,  -195,
    -195,  -195,   399,  -195,   495,   511,  -195,   221,  -195,   -32,
    -195,   200,   223,   122,   720,   205,  -195,   212,   264,   240,
    -195,  -195,  -195,  -195,   551,   793,  -195,  -195,    56,   188,
     103,    17,   720,   120,    44,   526,    22,   720,   664,   751,
      41,    86,   376,   415,   470,    48,  -195,   607,  -195,  -195,
    -195,    43,  -195,    20,    20,  -195,  -195,  -195,   248,   274,
      52,  -195,   112,   295,  -195,   228,    42,  -195,   249,  -195,
     793,   253,   149,   567,   188,  -195,  -195,   104,   793,   793,
    -195,   254,  -195,  -195,  -195,  -195,   248,  -195,   115,   252,
    -195,   221,  -195,  -195,   226,  -195,  -195,  -195,  -195,  -195,
     116,   720,  -195,  -195,  -195,  -195,   735,   624,  -195,  -195,
    -195,   255,  -195,  -195,  -195,   121,    20,   249,  -195,  -195,
    -195,   226,  -195,  -195,  -195,  -195
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    11,     1,     0,     0,     0,    54,    55,    57,    56,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,   136,   109,   135,     0,     0,     0,     0,
       0,   101,    59,     0,     3,    43,     0,    31,    74,     4,
       0,     0,     0,     0,     0,    68,     0,     0,    69,     0,
      70,     0,     0,    71,    72,    67,    23,     0,     0,     0,
       0,   141,   115,   137,     0,     0,     0,   106,     0,     0,
       0,   109,   133,   132,     0,    66,     0,     0,     0,     0,
       0,     0,     0,     0,    58,   139,   118,   116,   117,     0,
       0,    20,    21,     0,    36,     0,     0,    44,    49,     0,
      73,     0,     0,    77,    78,    79,    85,    87,    86,    89,
       0,    92,    94,     0,     0,     0,    61,    30,    25,    62,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,   142,
       0,    29,     0,     0,    75,     0,     0,     0,     0,    65,
      64,    63,     0,    76,     0,     0,   110,     0,    23,     0,
      38,     0,    37,     0,    50,     0,    41,     0,    52,    32,
      34,    35,    28,    84,     0,     0,   100,    24,   137,    26,
       0,     0,   122,   121,   119,   123,   124,   113,     0,   129,
     130,   125,   127,   128,   126,   120,   114,     0,   140,   138,
     103,     0,    80,    31,    31,    83,    88,    91,     0,     0,
       0,     9,     0,     0,    22,    16,     0,    42,     0,    51,
       0,     0,     0,     0,    27,   107,   105,     0,     0,     0,
     111,     0,   102,    81,    82,    99,    96,    97,     0,     0,
       8,     0,    12,    18,     0,    19,    40,    39,    45,    46,
       0,    53,    33,    90,    95,   108,   134,     0,   104,    98,
       7,     0,     6,    10,    14,     0,    31,     0,    48,   112,
       5,     0,    17,    13,    47,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,  -195,    50,  -195,  -195,    23,  -195,  -195,  -195,
    -195,  -195,   137,   -61,   -87,  -194,  -195,  -195,  -195,  -195,
      31,  -195,  -195,  -115,    -3,  -195,   302,  -195,  -195,  -195,
    -195,  -195,   260,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,    77,   -25,  -195,    12,  -195,  -195,  -195,
    -195,   -12,    34,  -195,   -11,  -195
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   210,   211,   212,    33,   264,   265,   245,    34,
      93,    94,   114,   117,    35,   102,   161,   162,    97,    98,
     249,   250,   219,    36,    37,    38,   177,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   236,   237,    55,    56,   163,   201,    58,    59,
     181,    60,   118,    61,    62,   140
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      64,    72,    73,   141,    76,   180,    78,   160,    81,   233,
     234,    95,    15,    57,    86,    87,    88,    89,   106,   108,
     142,   145,     3,   214,   111,    67,   112,     6,     7,     8,
       9,   122,    63,   146,   109,   147,    66,    65,   168,   123,
     124,   172,   126,   115,    68,    69,    70,     3,    31,   139,
     122,    63,     6,     7,     8,     9,    96,   116,   123,   124,
     125,   126,   148,   165,   126,   142,   227,   152,   126,   135,
     154,   155,   273,   158,   136,   137,   226,   142,    63,   142,
     101,   231,   166,   164,   131,   132,   133,   134,   135,   115,
     239,   135,    63,   136,   137,   122,   136,   137,   174,    84,
     136,   137,   232,   123,   124,   125,   126,    77,   240,   182,
     183,   184,   185,   186,    85,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,    57,   159,    99,   247,
     132,   133,   134,   135,   202,   169,   170,   123,   136,   137,
     126,    99,    99,   203,   204,     6,     7,     8,     9,   179,
     241,   100,   260,    74,   267,   246,    85,    79,    63,   271,
     171,    80,   150,   223,   225,   255,    82,   135,   242,   115,
     261,    63,   136,   137,     2,   268,   142,   272,    83,     3,
       4,     5,   143,    90,     6,     7,     8,     9,    10,    11,
      12,    13,    91,    92,    14,   103,    15,   253,    16,    17,
      18,    19,    20,    21,   104,    22,   105,    31,   251,    23,
      24,    25,   224,   110,   113,   119,   256,   257,   120,   144,
      85,    26,    27,    28,   151,    57,   157,   153,   167,    29,
     173,    30,    31,   175,   178,    32,     6,     7,     8,     9,
     142,   266,   199,     3,     4,     5,   198,   200,     6,     7,
       8,     9,    10,    11,    12,    13,   215,   209,    14,   217,
      15,   216,    16,    17,    18,    19,    20,    21,   266,    22,
     218,     3,   220,    23,    24,    25,     6,     7,     8,     9,
     221,   235,   238,   244,   248,    26,    27,    28,   252,   262,
     258,   263,   270,    29,   275,   213,    31,   176,   274,    32,
       3,     4,     5,    39,   107,     6,     7,     8,     9,    10,
      11,    12,    13,   259,     0,    14,     0,    15,     0,    16,
      17,    18,    19,    20,    21,     0,    22,   121,   122,     0,
      23,    24,    25,     0,     0,     0,   123,   124,   125,   126,
       0,     0,    26,    27,    28,     0,     0,     0,     0,     0,
      29,     0,     0,    31,   243,     0,    32,   127,   128,     0,
     129,   130,   131,   132,   133,   134,   135,   121,   122,     0,
       0,   136,   137,     0,     0,     0,   123,   124,   125,   126,
     138,     0,     0,     0,     0,   122,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,   127,   128,     0,
     129,   130,   131,   132,   133,   134,   135,   121,   122,     0,
       0,   136,   137,     0,     0,     0,   123,   124,   125,   126,
     149,   133,   134,   135,   122,     0,     0,     0,   136,   137,
       0,     0,   123,   124,   125,   126,     0,   127,   128,     0,
     129,   130,   131,   132,   133,   134,   135,   121,   122,     0,
       0,   136,   137,     0,     0,     0,   123,   124,   125,   126,
     206,   134,   135,   121,   122,     0,     0,   136,   137,     0,
       0,     0,   123,   124,   125,   126,     0,   127,   128,   122,
     129,   130,   131,   132,   133,   134,   135,   123,   124,   125,
     126,   136,   137,   127,   128,   156,   129,   130,   131,   132,
     133,   134,   135,   121,   122,     0,     0,   136,   137,     0,
       0,   205,   123,   124,   125,   126,     0,   135,     0,   121,
     122,     0,   136,   137,     0,     0,     0,     0,   123,   124,
     125,   126,     0,   127,   128,   122,   129,   130,   131,   132,
     133,   134,   135,   123,     0,     0,   126,   136,   137,   127,
     128,   207,   129,   130,   131,   132,   133,   134,   135,   121,
     122,     0,     0,   136,   137,     0,     0,   208,   123,   124,
     125,   126,     0,   135,     0,   121,   122,     0,   136,   137,
       0,     0,     0,     0,   123,   124,   125,   126,     0,   127,
     128,     0,   129,   130,   131,   132,   133,   134,   135,     0,
       0,     0,     0,   136,   137,   127,   128,   222,   129,   130,
     131,   132,   133,   134,   135,   121,   122,     0,     0,   136,
     137,     0,     0,   254,   123,   124,   125,   126,     0,     0,
       0,     0,   121,   122,     0,     0,     0,     0,     0,     0,
       0,   123,   124,   125,   126,   127,   128,   229,   129,   130,
     131,   132,   133,   134,   135,     0,     0,     0,     0,   136,
     137,   230,   127,   128,     0,   129,   130,   131,   132,   133,
     134,   135,   121,   122,     0,     0,   136,   137,   269,     0,
       0,   123,   124,   125,   126,     0,     0,     0,   121,   122,
       0,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   228,   129,   130,   131,   132,   133,
     134,   135,     0,     0,     0,     0,   136,   137,   127,   128,
       0,   129,   130,   131,   132,   133,   134,   135,   121,   122,
       0,     0,   136,   137,     0,     0,     0,   123,   124,   125,
     126,     0,     0,     0,   122,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,     0,     0,     0,   128,
     122,   129,   130,   131,   132,   133,   134,   135,   123,   124,
     125,   126,   136,   137,   128,     0,   129,   130,   131,   132,
     133,   134,   135,     0,     0,     0,     0,   136,   137,    13,
       0,     0,    14,   130,   131,   132,   133,   134,   135,     0,
       0,     0,     0,   136,   137,     0,     0,    23,    71,    25,
      13,     0,     0,    14,     0,     0,     0,     0,     0,    26,
      27,    28,     0,     0,     0,     0,     0,    29,    23,    71,
      25,     0,     0,    75,     0,     0,     0,     0,     0,     0,
      26,    27,    28,     0,     0,     0,     0,     0,    29
};

static const yytype_int16 yycheck[] =
{
       3,    13,    14,    64,    16,   120,    17,    94,    19,   203,
     204,     8,    22,     1,    26,    27,    28,    29,    43,    44,
      52,     8,     5,    55,    49,    58,    51,    10,    11,    12,
      13,     9,    36,     8,    46,     8,    37,     3,    99,    17,
      18,   102,    20,    47,    10,    11,    12,     5,    58,    61,
       9,    36,    10,    11,    12,    13,    53,    61,    17,    18,
      19,    20,    74,    35,    20,    52,   181,    79,    20,    47,
      82,    83,   266,    58,    52,    53,    59,    52,    36,    52,
      60,    38,    54,    95,    43,    44,    45,    46,    47,    47,
      38,    47,    36,    52,    53,     9,    52,    53,   110,    40,
      52,    53,    59,    17,    18,    19,    20,    36,    56,   121,
     122,   123,   124,   125,    55,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   114,    93,    38,   216,
      44,    45,    46,    47,   145,    35,    36,    17,    52,    53,
      20,    38,    38,   146,   147,    10,    11,    12,    13,   115,
      38,    61,    37,    55,    38,   216,    55,    55,    36,    38,
      60,    36,    61,   175,    61,    61,    55,    47,    56,    47,
      55,    36,    52,    53,     0,    59,    52,    56,    55,     5,
       6,     7,    58,    36,    10,    11,    12,    13,    14,    15,
      16,    17,     3,     4,    20,    61,    22,   222,    24,    25,
      26,    27,    28,    29,    61,    31,    61,    58,   220,    35,
      36,    37,   178,    61,    28,    61,   228,   229,    58,    61,
      55,    47,    48,    49,    61,   213,    55,    61,     8,    55,
      23,    57,    58,    55,    36,    61,    10,    11,    12,    13,
      52,   244,    36,     5,     6,     7,    56,    36,    10,    11,
      12,    13,    14,    15,    16,    17,    56,    36,    20,    54,
      22,    38,    24,    25,    26,    27,    28,    29,   271,    31,
      58,     5,     8,    35,    36,    37,    10,    11,    12,    13,
      40,    33,     8,    55,    35,    47,    48,    49,    35,    37,
      36,   241,    37,    55,   271,   158,    58,    59,   267,    61,
       5,     6,     7,     1,    44,    10,    11,    12,    13,    14,
      15,    16,    17,   236,    -1,    20,    -1,    22,    -1,    24,
      25,    26,    27,    28,    29,    -1,    31,     8,     9,    -1,
      35,    36,    37,    -1,    -1,    -1,    17,    18,    19,    20,
      -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    58,    59,    -1,    61,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,     8,     9,    -1,
      -1,    52,    53,    -1,    -1,    -1,    17,    18,    19,    20,
      61,    -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,     8,     9,    -1,
      -1,    52,    53,    -1,    -1,    -1,    17,    18,    19,    20,
      61,    45,    46,    47,     9,    -1,    -1,    -1,    52,    53,
      -1,    -1,    17,    18,    19,    20,    -1,    38,    39,    -1,
      41,    42,    43,    44,    45,    46,    47,     8,     9,    -1,
      -1,    52,    53,    -1,    -1,    -1,    17,    18,    19,    20,
      61,    46,    47,     8,     9,    -1,    -1,    52,    53,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    38,    39,     9,
      41,    42,    43,    44,    45,    46,    47,    17,    18,    19,
      20,    52,    53,    38,    39,    56,    41,    42,    43,    44,
      45,    46,    47,     8,     9,    -1,    -1,    52,    53,    -1,
      -1,    56,    17,    18,    19,    20,    -1,    47,    -1,     8,
       9,    -1,    52,    53,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    -1,    38,    39,     9,    41,    42,    43,    44,
      45,    46,    47,    17,    -1,    -1,    20,    52,    53,    38,
      39,    56,    41,    42,    43,    44,    45,    46,    47,     8,
       9,    -1,    -1,    52,    53,    -1,    -1,    56,    17,    18,
      19,    20,    -1,    47,    -1,     8,     9,    -1,    52,    53,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,    38,
      39,    -1,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    38,    39,    56,    41,    42,
      43,    44,    45,    46,    47,     8,     9,    -1,    -1,    52,
      53,    -1,    -1,    56,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    38,    39,    -1,    41,    42,    43,    44,    45,
      46,    47,     8,     9,    -1,    -1,    52,    53,    54,    -1,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    38,    39,
      -1,    41,    42,    43,    44,    45,    46,    47,     8,     9,
      -1,    -1,    52,    53,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    39,
       9,    41,    42,    43,    44,    45,    46,    47,    17,    18,
      19,    20,    52,    53,    39,    -1,    41,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    17,
      -1,    -1,    20,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    -1,    -1,    35,    36,    37,
      17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    55,    35,    36,
      37,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    63,     0,     5,     6,     7,    10,    11,    12,    13,
      14,    15,    16,    17,    20,    22,    24,    25,    26,    27,
      28,    29,    31,    35,    36,    37,    47,    48,    49,    55,
      57,    58,    61,    67,    71,    76,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   106,   107,   108,   110,   111,
     113,   115,   116,    36,    86,   114,    37,    58,   114,   114,
     114,    36,   113,   113,    55,    61,   113,    36,   116,    55,
      36,   116,    55,    55,    40,    55,   113,   113,   113,   113,
      36,     3,     4,    72,    73,     8,    53,    80,    81,    38,
      61,    60,    77,    61,    61,    61,   106,    94,   106,   113,
      61,   106,   106,    28,    74,    47,    61,    75,   114,    61,
      58,     8,     9,    17,    18,    19,    20,    38,    39,    41,
      42,    43,    44,    45,    46,    47,    52,    53,    61,   113,
     117,    75,    52,    58,    61,     8,     8,     8,   113,    61,
      61,    61,   113,    61,   113,   113,    56,    55,    58,   114,
      76,    78,    79,   108,   113,    35,    54,     8,    75,    35,
      36,    60,    75,    23,   113,    55,    59,    88,    36,   114,
      85,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,    56,    36,
      36,   109,   116,    86,    86,    56,    61,    56,    56,    36,
      64,    65,    66,    74,    55,    56,    38,    54,    58,    84,
       8,    40,    56,   113,   114,    61,    59,    85,    40,    40,
      54,    38,    59,    77,    77,    33,   104,   105,     8,    38,
      56,    38,    56,    59,    55,    70,    75,    76,    35,    82,
      83,   113,    35,   106,    56,    61,   113,   113,    36,   105,
      37,    55,    37,    65,    68,    69,    86,    38,    59,    54,
      37,    38,    56,    77,    82,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    69,    69,    70,    70,    71,    72,
      72,    72,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    77,    77,    77,    77,    77,    78,    78,    79,    79,
      79,    80,    80,    81,    81,    82,    83,    83,    84,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    87,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      89,    90,    91,    92,    93,    94,    94,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   104,   105,
     106,   107,   108,   109,   109,   110,   111,   112,   112,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   115,
     116,   117,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     3,     3,     2,     1,
       3,     0,     5,     2,     1,     3,     0,     3,     5,     4,
       1,     1,     3,     0,     2,     1,     2,     3,     3,     3,
       2,     0,     2,     4,     2,     2,     0,     1,     1,     3,
       3,     2,     3,     0,     1,     1,     1,     3,     3,     2,
       3,     4,     3,     5,     1,     1,     1,     1,     2,     1,
       2,     2,     2,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     3,     2,     2,     2,
       4,     5,     5,     4,     3,     2,     2,     2,     4,     2,
       5,     4,     2,     1,     2,     5,     5,     1,     2,     1,
       3,     1,     5,     1,     3,     4,     2,     2,     3,     1,
       3,     4,     6,     3,     3,     1,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     5,     1,     1,     1,     3,     2,
       3,     0,     1
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
#line 91 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1644 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 92 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1651 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 93 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1658 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 96 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = synth::Importer::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1666 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 98 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  synth::Importer::AddStrParam((yyvsp[-2].import_param), (yyvsp[0].str));
  (yyval.import_param) = (yyvsp[-2].import_param);
}
#line 1675 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = synth::Importer::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1683 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 105 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_param) = (yyvsp[-1].import_param);
}
#line 1691 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 109 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = synth::Importer::BuildParamSet(nullptr, (yyvsp[0].import_param));
}
#line 1699 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 111 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.import_params) = synth::Importer::BuildParamSet((yyvsp[-2].import_params), (yyvsp[0].import_param));
}
#line 1707 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 115 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource(nullptr);
}
#line 1715 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 117 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetImportedResource((yyvsp[-1].import_params));
}
#line 1723 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 121 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 1731 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 125 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1739 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 127 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1747 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 131 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1755 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 133 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1763 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 137 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1771 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 141 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1781 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 150 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1789 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 154 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1796 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 155 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1803 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 158 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), false, nullptr);
}
#line 1811 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 160 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, nullptr);
}
#line 1819 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 162 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ModifiedVar((yyvsp[0].expr), true, (yyvsp[-1].sym));
}
#line 1827 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 166 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::BuildVarDecl((yyvsp[-2].sym), (yyvsp[-1].width_spec).width, (yyvsp[-1].width_spec).name, (yyvsp[0].var_decl));
}
#line 1835 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 168 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1842 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 169 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1849 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 172 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::MakeInt(false, 32, 0));
}
#line 1857 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 174 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::MakeInt(false, (yyvsp[0].num), 0));
}
#line 1865 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 176 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::MakeInt(false, (yyvsp[-2].num), (yyvsp[0].num)));
}
#line 1873 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 178 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym));
}
#line 1881 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 180 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(numeric::Width::Null());
}
#line 1889 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1898 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 187 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1906 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 191 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1914 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 193 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ArgDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1922 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* un-typed argument */
  (yyval.var_decl_set) = nullptr;
}
#line 1931 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 200 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = 0;
}
#line 1939 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 202 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-1].num);
}
#line 1947 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 206 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = -1;
}
#line 1955 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 208 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1963 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 212 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 1971 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 216 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num));
  (yyval.array) = array;
}
#line 1981 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 220 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num));
  (yyval.array) = (yyvsp[-2].array);
}
#line 1990 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 225 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-1].array);
}
#line 1998 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 229 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-1].var_decl), (yyvsp[0].num));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-1].var_decl));
}
#line 2007 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 232 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].var_decl)->initial_val = (yyvsp[0].expr);
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl));
}
#line 2016 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 235 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Builder::SetArrayLength((yyvsp[-3].var_decl), (yyvsp[-2].num));
  Builder::SetArrayInitializer((yyvsp[-3].var_decl), (yyvsp[0].array));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-3].var_decl));
}
#line 2026 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 239 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  sym_t type = Builder::TypeNameFromVarDeclSet((yyvsp[-2].var_decl_set));
  WidthSpec w = Builder::GetWidthSpecFromVarDeclSet((yyvsp[-2].var_decl_set));
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-2].var_decl_set), Builder::BuildVarDecl(type, w.width, w.name, (yyvsp[0].var_decl)));
}
#line 2036 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 243 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::VarDeclList((yyvsp[-4].var_decl_set), (yyvsp[-2].var_decl));
}
#line 2044 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 247 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2052 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 249 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2060 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 251 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2068 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 253 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2076 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 258 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2083 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 261 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2091 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2099 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 265 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2106 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 266 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2113 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 267 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2120 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 268 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2127 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 269 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2135 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 271 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2143 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 273 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2150 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 274 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2157 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 275 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2164 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 276 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2171 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 277 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2178 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2185 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 279 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2193 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 282 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-1].str));
}
#line 2201 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 284 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitSpawnStmt((yyvsp[-1].expr));
}
#line 2209 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 286 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2216 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 287 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2223 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 288 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2230 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 291 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2238 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 295 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 2246 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 299 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-3].expr), (yyvsp[-1].sym), (yyvsp[0].width_spec).width, (yyvsp[0].width_spec).name);
}
#line 2254 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 303 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2263 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 308 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-2].stmt)->label_f_);
}
#line 2273 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 314 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2283 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 318 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2292 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_join_);
}
#line 2301 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 326 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2310 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 331 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2319 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 336 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2338 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 351 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[-1].expr));
  Emitter::EmitLabel((yyval.stmt)->label_t_);
}
#line 2351 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 360 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-1].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2361 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 366 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->label_join_);
}
#line 2372 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 373 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2380 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 377 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_t_);
  Emitter::EmitGoto((yyvsp[-4].stmt)->label_join_);
  Emitter::EmitLabel((yyvsp[-4].stmt)->label_f_);
  Emitter::EndBlock();
}
#line 2392 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2399 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 388 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2406 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 389 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2413 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 392 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2420 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 395 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2428 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 399 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2437 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 404 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2445 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 408 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2453 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 410 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2461 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 414 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2468 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 417 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2475 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 420 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2482 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 421 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2489 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 424 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2497 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 426 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2505 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 428 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2513 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 430 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2521 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 432 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2529 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 434 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2537 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 436 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2545 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 438 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2553 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 440 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2561 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 442 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::RefExpr((yyvsp[0].expr));
}
#line 2569 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 444 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2577 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 446 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2585 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 448 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2593 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 450 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2601 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 452 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2609 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 454 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].num));
}
#line 2617 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 456 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2625 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 458 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2633 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 460 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2641 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 462 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2649 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2657 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 466 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2665 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].num), true);
}
#line 2673 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 470 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].num), false);
}
#line 2681 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 472 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].num), (yyvsp[0].expr));
}
#line 2689 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 474 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2697 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 476 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2705 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 478 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2713 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 482 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2721 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 484 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2729 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 488 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2737 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 492 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2745 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 496 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2753 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 498 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2761 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
    break;


#line 2765 "src/fe/libparse_la-parser.cpp" /* yacc.c:1646  */
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
#line 502 "src/fe/parser.ypp" /* yacc.c:1906  */

