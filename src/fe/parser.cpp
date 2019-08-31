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
    K_RETURN = 283,
    K_SHARED = 284,
    K_SHIFT = 285,
    K_STRING = 286,
    K_SWITCH = 287,
    K_THREAD = 288,
    K_VAR = 289,
    K_WHILE = 290,
    K_WITH = 291,
    NUM = 292,
    SYM = 293,
    STR = 294,
    K_LOGIC_OR = 295,
    K_LOGIC_AND = 296,
    K_BIT_CONCAT = 297,
    SIGN = 298,
    ADDRESS = 299
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
#define K_RETURN 283
#define K_SHARED 284
#define K_SHIFT 285
#define K_STRING 286
#define K_SWITCH 287
#define K_THREAD 288
#define K_VAR 289
#define K_WHILE 290
#define K_WITH 291
#define NUM 292
#define SYM 293
#define STR 294
#define K_LOGIC_OR 295
#define K_LOGIC_AND 296
#define K_BIT_CONCAT 297
#define SIGN 298
#define ADDRESS 299

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

#line 233 "src/fe/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_FE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "src/fe/parser.cpp" /* yacc.c:358  */

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
#define YYLAST   951

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  280

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    63,     2,     2,    48,     2,
      60,    61,    49,     2,    40,     2,    55,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    64,
       2,     2,     2,    41,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    46,    59,    52,     2,     2,     2,
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
      35,    36,    37,    38,    39,    43,    44,    45,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    97,    97,    99,    99,   101,   102,   103,   103,   106,
     108,   113,   115,   117,   121,   123,   125,   129,   131,   135,
     139,   141,   145,   147,   151,   151,   155,   162,   162,   164,
     168,   169,   172,   184,   184,   186,   186,   195,   196,   199,
     201,   203,   207,   210,   214,   224,   232,   235,   240,   242,
     244,   250,   254,   258,   263,   263,   263,   267,   270,   278,
     292,   294,   296,   298,   303,   307,   311,   313,   315,   316,
     317,   319,   321,   323,   324,   325,   326,   327,   328,   329,
     331,   332,   333,   334,   335,   339,   343,   347,   347,   351,
     353,   357,   357,   361,   361,   365,   365,   369,   370,   374,
     379,   385,   389,   392,   397,   401,   403,   407,   412,   427,
     436,   442,   449,   453,   461,   464,   465,   468,   471,   475,
     480,   484,   486,   490,   493,   495,   497,   499,   501,   503,
     505,   507,   509,   511,   513,   515,   517,   519,   521,   523,
     525,   527,   529,   531,   533,   535,   537,   539,   541,   543,
     546,   551,   553,   558,   560,   564,   566,   570,   574,   579,
     581
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
  "K_LG_COMPARE", "K_MAILBOX", "K_OBJECT", "K_RETURN", "K_SHARED",
  "K_SHIFT", "K_STRING", "K_SWITCH", "K_THREAD", "K_VAR", "K_WHILE",
  "K_WITH", "NUM", "SYM", "STR", "','", "'?'", "':'", "K_LOGIC_OR",
  "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'", "'&'", "'*'", "'/'", "'!'",
  "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'", "'{'", "'}'", "'('",
  "')'", "'@'", "'#'", "';'", "$accept", "input", "FUNC_DECL_OR_STMT_LIST",
  "FUNC_DECL_OR_STMT", "$@1", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "RETURN_TYPE",
  "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@2", "FUNC_DECL_HEAD",
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
      44,    63,    58,   295,   296,   297,   124,    94,    38,    42,
      47,    33,   126,   298,   299,    46,    91,    93,   123,   125,
      40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF -147

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-147)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -147,    23,   149,  -147,   507,  -147,   124,  -147,  -147,   507,
    -147,   507,  -147,    71,  -147,   507,    65,    80,    51,  -147,
     507,   507,  -147,   507,   107,  -147,  -147,   169,  -147,   145,
      93,  -147,    36,  -147,  -147,   123,  -147,    93,    93,    93,
     117,   -10,  -147,   384,   507,   115,  -147,   117,  -147,   117,
     157,  -147,  -147,  -147,  -147,   -29,   321,  -147,   507,  -147,
     133,    10,  -147,  -147,  -147,  -147,  -147,    65,     5,   710,
     155,    10,   507,    65,   710,   125,   165,  -147,  -147,    10,
      10,   424,   144,  -147,  -147,    40,    60,    39,  -147,  -147,
     321,    38,    93,  -147,  -147,  -147,   193,  -147,  -147,  -147,
     150,    65,   369,   710,   507,  -147,  -147,   160,   243,  -147,
     166,   507,   507,   507,  -147,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   507,   507,   507,  -147,
     710,   161,   166,   185,   187,   222,   458,     2,  -147,  -147,
    -147,   192,    65,    65,  -147,  -147,    -2,    65,  -147,  -147,
      65,  -147,  -147,   710,  -147,  -147,  -147,  -147,  -147,  -147,
     546,   507,  -147,    28,  -147,    83,   744,   104,   333,   141,
     744,   676,   812,   846,   640,   880,   883,   895,    10,    10,
    -147,   580,  -147,  -147,  -147,    88,   198,    93,   224,   200,
    -147,   234,    11,  -147,    31,     9,     9,  -147,    86,  -147,
     179,   201,   166,     7,  -147,   205,  -147,   492,   507,   507,
    -147,   206,  -147,  -147,  -147,  -147,   224,  -147,   133,  -147,
     196,    -7,   204,  -147,   192,  -147,  -147,    19,    19,   290,
    -147,   189,    65,    65,   136,   194,  -147,  -147,  -147,   211,
    -147,   778,   628,  -147,  -147,  -147,  -147,  -147,   213,  -147,
    -147,  -147,  -147,  -147,    19,  -147,  -147,   166,  -147,  -147,
      48,  -147,  -147,   205,   186,  -147,  -147,  -147,    43,  -147,
     210,  -147,  -147,  -147,    19,  -147,   197,  -147,   231,  -147
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    17,     1,     0,   111,     0,   104,    86,     0,
      87,     0,    65,     0,    91,     0,     0,   151,   123,   149,
       0,     0,   119,     0,     0,    85,     4,    24,     5,    57,
       0,    80,     0,     6,    66,     0,    81,     0,     0,     0,
       0,     0,    74,    17,     0,     0,    75,     0,    76,     0,
       0,    77,    78,    73,    30,     0,     0,   150,   159,   129,
     123,   147,    61,    60,    62,    63,   153,     0,     0,    99,
       0,   146,     0,     0,   109,     0,     0,    64,   157,   130,
     131,     0,     0,    93,    95,     0,     0,     0,    79,    72,
       0,     0,     0,    82,    83,    84,   101,   103,   102,    35,
       0,     0,     0,   107,     0,   110,   112,     0,    17,    68,
      38,     0,     0,     0,   145,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    67,
     160,     0,    37,     0,     0,    90,     0,     0,     7,   152,
     124,    14,     0,     0,    27,    28,     0,    42,    34,    33,
       0,    54,    59,    58,    71,    70,    69,   100,   106,   105,
       0,     0,   118,    35,    31,   132,   136,   138,   137,   135,
     127,     0,   143,   144,   139,   141,   142,   140,   133,   134,
     128,     0,   158,   154,   121,     0,     0,     0,     0,     0,
       3,     0,     0,    15,     0,    97,    97,    30,     0,    44,
       0,    43,   155,     0,    36,     0,   108,     0,     0,     0,
     125,     0,   120,    89,    88,   117,   114,   115,     0,    92,
      17,     0,     0,    13,     0,    18,    98,     0,     0,    17,
      29,    22,     0,     0,     0,    48,    39,    51,    52,    55,
     113,   148,     0,   122,   116,     8,    12,    11,     0,    10,
      16,    94,    96,    25,     0,    26,    45,   156,    40,    41,
       0,    49,    32,     0,     0,   126,     9,    20,     0,    19,
       0,    50,    53,    56,     0,    23,    46,    21,     0,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,    79,  -147,  -147,  -147,    37,  -147,   -40,    -4,
    -147,  -147,  -147,  -147,  -147,  -147,    75,  -146,  -147,  -147,
    -147,   -61,  -147,  -147,     1,  -147,    16,  -147,  -147,  -147,
    -147,   230,   268,  -147,  -147,  -103,   -11,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,    87,  -147,  -147,
     244,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,    68,   -25,  -147,   245,  -147,    -3,  -147,    -6,
    -147,  -147,   -33,  -147
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   190,   192,   193,   194,    27,   267,
     268,   255,    28,    85,   146,   147,   108,   199,   150,    29,
      86,   269,   200,   201,   261,   262,   238,   239,   152,   205,
     264,    30,   236,    31,    32,    33,    34,    35,    36,    70,
     187,    37,    73,    38,   142,    39,   143,   227,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,   216,   217,    53,    54,    55,   185,    56,    57,   202,
     203,    58,    59,   131
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    61,    92,    99,   204,   164,    69,   189,    71,    66,
      75,     9,    74,    62,   226,    96,    98,    79,    80,    88,
      81,    89,   105,     3,   106,    62,    93,    94,    95,    90,
     246,    63,   247,   114,    64,    25,    66,    83,    65,     4,
     102,   103,     4,    63,   109,   129,    64,   233,    22,   110,
      65,   222,   144,   248,    84,   130,   197,   133,   145,    11,
     133,   132,    11,   134,   133,   127,   128,   137,   163,   136,
     234,   224,   223,    17,    60,    19,    17,    60,    19,   154,
     155,   156,   234,   274,   153,   270,   256,    20,    21,   148,
      20,    21,   225,    77,   149,   110,    23,   151,    78,    23,
      25,   160,    25,    66,   275,   271,   114,   111,   165,   166,
     167,    78,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   164,   114,   211,   115,
      62,    72,   125,   126,   116,   206,   195,   196,   127,   128,
     198,   133,   235,    76,   111,    82,   230,   212,    63,    -2,
      87,    64,     4,   125,   126,    65,   219,    25,   207,   127,
     128,    91,    66,     5,   114,     6,   251,   252,     7,     8,
       9,    10,    11,   258,   259,    22,   214,    12,    83,   104,
     133,    13,    14,   138,    15,    16,    17,    18,    19,   163,
     125,   126,   107,    78,   135,    84,   127,   128,   -35,     4,
      20,    21,   139,   -35,   141,   241,   242,    22,   157,    23,
       5,    24,     6,    25,   158,     7,     8,     9,    10,    11,
     161,   133,   182,   183,    12,   184,   186,   257,    13,    14,
     191,    15,    16,    17,    18,    19,   213,   215,   218,   221,
     231,   232,   237,   249,   243,   273,     4,    20,    21,   254,
     260,   263,   266,   278,    22,   245,    23,     5,    24,     6,
      25,   250,     7,     8,     9,    10,    11,   276,   270,   220,
     277,    12,   229,   100,    67,    13,    14,   279,    15,   272,
      17,    18,    19,   228,   244,    97,     0,     0,   101,     0,
       0,     0,     0,     4,    20,    21,     0,     0,     0,     0,
       0,    22,   162,    23,     5,    24,     6,    25,     0,     7,
       8,     9,    10,    11,     0,     0,     0,     0,    12,     0,
       0,     0,    13,    14,   111,    15,   112,    17,    18,    19,
       0,     0,     0,     0,     0,     0,   111,     0,   113,     0,
       0,    20,    21,     0,   114,     0,   115,     0,    22,   253,
      23,   116,    24,     0,    25,     0,   114,     0,     0,     0,
       0,   117,   118,   116,   119,   120,   121,   122,   123,   124,
     125,   126,   111,     0,   112,     0,   127,   128,     0,     0,
       0,     0,   125,   126,     0,    25,   113,     4,   127,   128,
       0,     0,   114,     0,   115,     0,     0,     0,     0,   116,
       6,     0,     0,     0,     0,     0,     0,    11,     0,   117,
     118,     0,   119,   120,   121,   122,   123,   124,   125,   126,
       0,    17,    60,    19,   127,   128,     0,   111,     0,   112,
       0,     0,     0,   159,     0,    20,    21,     0,     0,     0,
       0,   113,     0,     0,    23,     0,    24,   114,     0,   115,
       0,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,   111,     0,   112,   117,   118,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   113,     0,     0,     0,   127,
     128,   114,     0,   115,     0,   140,     0,     0,   116,     0,
       0,     0,     0,     0,     0,   111,     0,   112,   117,   118,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   113,
       4,     0,     0,   127,   128,   114,     0,   115,     0,   188,
       0,     0,   116,     0,     0,     0,     0,     0,     0,     0,
      11,     0,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,     0,    17,    60,    19,   127,   128,   111,
       0,   112,     0,   240,     0,     0,     0,     0,    20,    21,
       0,     0,     0,   113,     0,     0,     0,    23,     0,   114,
       0,   115,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,   111,     0,   112,   117,   118,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   113,     0,     0,
       0,   127,   128,   114,    22,   115,     0,     0,     0,     0,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,   209,   119,   120,   121,   122,   123,   124,   125,
     126,   111,     0,   112,     0,   127,   128,   210,     0,     0,
       0,     0,     0,   111,     0,   113,     0,     0,     0,     0,
       0,   114,     0,   115,     0,     0,     0,   113,   116,     0,
       0,     0,     0,   114,     0,   115,     0,     0,   117,   118,
     116,   119,   120,   121,   122,   123,   124,   125,   126,   111,
       0,   112,     0,   127,   128,   265,   122,   123,   124,   125,
     126,     0,     0,   113,     0,   127,   128,     0,     0,   114,
       0,   115,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,   111,     0,   112,   117,   118,   208,   119,
     120,   121,   122,   123,   124,   125,   126,   113,     0,     0,
       0,   127,   128,   114,     0,   115,     0,     0,     0,     0,
     116,     0,     0,     0,     0,     0,     0,   111,     0,   112,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   113,     0,     0,     0,   127,   128,   114,     0,   115,
       0,     0,     0,     0,   116,     0,     0,     0,     0,     0,
       0,   111,     0,     0,     0,   118,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   113,     0,     0,     0,   127,
     128,   114,     0,   115,     0,     0,     0,     0,   116,     0,
       0,     0,     0,     0,     0,   111,     0,     0,     0,   118,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   113,
       0,     0,     0,   127,   128,   114,     0,   115,     0,     0,
       0,     0,   116,     0,     0,     0,     0,     0,     0,   111,
       0,     0,     0,     0,     0,     0,   120,   121,   122,   123,
     124,   125,   126,   113,     0,     0,     0,   127,   128,   114,
       0,   115,     0,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,   111,     0,     0,   111,     0,     0,     0,
       0,   121,   122,   123,   124,   125,   126,   113,   111,     0,
     113,   127,   128,   114,     0,   115,   114,     0,   115,     0,
     116,     0,   113,   116,     0,     0,     0,     0,   114,     0,
     115,     0,     0,     0,     0,   116,     0,   123,   124,   125,
     126,   124,   125,   126,     0,   127,   128,     0,   127,   128,
       0,     0,     0,     0,   125,   126,     0,     0,     0,     0,
     127,   128
};

static const yytype_int16 yycheck[] =
{
       6,     4,    35,    43,   150,   108,     9,     5,    11,    38,
      16,    21,    15,     6,     5,    40,    41,    20,    21,    30,
      23,    32,    47,     0,    49,     6,    37,    38,    39,    32,
      37,    24,    39,    23,    27,    64,    38,     9,    31,     3,
      43,    44,     3,    24,    55,    56,    27,    40,    58,    55,
      31,    40,    12,    60,    26,    58,    58,    55,    18,    23,
      55,    67,    23,    58,    55,    55,    56,    73,   108,    72,
      63,    40,    61,    37,    38,    39,    37,    38,    39,    90,
      91,    92,    63,    40,    87,    37,   232,    51,    52,    29,
      51,    52,    61,    42,    34,   101,    60,    58,    60,    60,
      64,   104,    64,    38,    61,    57,    23,     3,   111,   112,
     113,    60,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   229,    23,    40,    25,
       6,    60,    49,    50,    30,   160,   142,   143,    55,    56,
     146,    55,   203,    63,     3,    38,    60,    59,    24,     0,
       5,    27,     3,    49,    50,    31,   189,    64,   161,    55,
      56,    38,    38,    14,    23,    16,   227,   228,    19,    20,
      21,    22,    23,    37,    38,    58,   187,    28,     9,    64,
      55,    32,    33,    58,    35,    36,    37,    38,    39,   229,
      49,    50,    35,    60,    39,    26,    55,    56,    29,     3,
      51,    52,    37,    34,    60,   208,   209,    58,    15,    60,
      14,    62,    16,    64,    64,    19,    20,    21,    22,    23,
      60,    55,    61,    38,    28,    38,     4,   233,    32,    33,
      38,    35,    36,    37,    38,    39,    38,    13,    38,     5,
      61,    40,    37,    39,    38,    59,     3,    51,    52,    60,
      56,    40,    39,    56,    58,    59,    60,    14,    62,    16,
      64,   224,    19,    20,    21,    22,    23,    57,    37,   190,
     274,    28,   197,    43,     6,    32,    33,   276,    35,   263,
      37,    38,    39,   196,   216,    41,    -1,    -1,    43,    -1,
      -1,    -1,    -1,     3,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    14,    62,    16,    64,    -1,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    32,    33,     3,    35,     5,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    17,    -1,
      -1,    51,    52,    -1,    23,    -1,    25,    -1,    58,    59,
      60,    30,    62,    -1,    64,    -1,    23,    -1,    -1,    -1,
      -1,    40,    41,    30,    43,    44,    45,    46,    47,    48,
      49,    50,     3,    -1,     5,    -1,    55,    56,    -1,    -1,
      -1,    -1,    49,    50,    -1,    64,    17,     3,    55,    56,
      -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    30,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    40,
      41,    -1,    43,    44,    45,    46,    47,    48,    49,    50,
      -1,    37,    38,    39,    55,    56,    -1,     3,    -1,     5,
      -1,    -1,    -1,    64,    -1,    51,    52,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    60,    -1,    62,    23,    -1,    25,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,    40,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    17,    -1,    -1,    -1,    55,
      56,    23,    -1,    25,    -1,    61,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    40,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    17,
       3,    -1,    -1,    55,    56,    23,    -1,    25,    -1,    61,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    40,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    37,    38,    39,    55,    56,     3,
      -1,     5,    -1,    61,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    60,    -1,    23,
      -1,    25,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,    40,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    50,    17,    -1,    -1,
      -1,    55,    56,    23,    58,    25,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     3,    -1,     5,    -1,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    25,    -1,    -1,    -1,    17,    30,    -1,
      -1,    -1,    -1,    23,    -1,    25,    -1,    -1,    40,    41,
      30,    43,    44,    45,    46,    47,    48,    49,    50,     3,
      -1,     5,    -1,    55,    56,    57,    46,    47,    48,    49,
      50,    -1,    -1,    17,    -1,    55,    56,    -1,    -1,    23,
      -1,    25,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    17,    -1,    -1,
      -1,    55,    56,    23,    -1,    25,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
      40,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,    17,    -1,    -1,    -1,    55,    56,    23,    -1,    25,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,    17,    -1,    -1,    -1,    55,
      56,    23,    -1,    25,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    50,    17,
      -1,    -1,    -1,    55,    56,    23,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    17,    -1,    -1,    -1,    55,    56,    23,
      -1,    25,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    17,     3,    -1,
      17,    55,    56,    23,    -1,    25,    23,    -1,    25,    -1,
      30,    -1,    17,    30,    -1,    -1,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    -1,    30,    -1,    47,    48,    49,
      50,    48,    49,    50,    -1,    55,    56,    -1,    55,    56,
      -1,    -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    66,    67,     0,     3,    14,    16,    19,    20,    21,
      22,    23,    28,    32,    33,    35,    36,    37,    38,    39,
      51,    52,    58,    60,    62,    64,    68,    73,    77,    84,
      96,    98,    99,   100,   101,   102,   103,   106,   108,   110,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   128,   129,   130,   132,   133,   136,   137,
      38,   132,     6,    24,    27,    31,    38,    97,   134,   132,
     104,   132,    60,   107,   132,   134,    63,    42,    60,   132,
     132,   132,    38,     9,    26,    78,    85,     5,   101,   101,
     132,    38,   137,   101,   101,   101,   128,   115,   128,    73,
      96,   130,   132,   132,    64,   128,   128,    35,    81,   101,
     134,     3,     5,    17,    23,    25,    30,    40,    41,    43,
      44,    45,    46,    47,    48,    49,    50,    55,    56,   101,
     132,   138,   134,    55,    58,    39,   132,   134,    58,    37,
      61,    60,   109,   111,    12,    18,    79,    80,    29,    34,
      83,    58,    93,   132,   101,   101,   101,    15,    64,    64,
     132,    60,    59,    73,   100,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,    61,    38,    38,   131,     4,   105,    61,     5,
      69,    38,    70,    71,    72,   134,   134,    58,   134,    82,
      87,    88,   134,   135,    82,    94,   128,   132,    42,    42,
      57,    40,    59,    38,   101,    13,   126,   127,    38,   137,
      67,     5,    40,    61,    40,    61,     5,   112,   112,    81,
      60,    61,    40,    40,    63,    86,    97,    37,    91,    92,
      61,   132,   132,    38,   127,    59,    37,    39,    60,    39,
      71,    86,    86,    59,    60,    76,    82,   134,    37,    38,
      56,    89,    90,    40,    95,    57,    39,    74,    75,    86,
      37,    57,    91,    59,    40,    61,    57,    74,    56,    89
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    68,    69,    68,    70,
      70,    71,    71,    71,    72,    72,    72,    73,    73,    74,
      75,    75,    76,    76,    78,    77,    79,    79,    79,    80,
      81,    81,    82,    83,    83,    85,    84,    84,    84,    86,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    91,    92,    92,    94,    95,    93,    96,    96,    96,
      97,    97,    97,    97,    98,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   102,   104,   103,   105,
     105,   107,   106,   109,   108,   111,   110,   112,   112,   113,
     114,   115,   115,   115,   116,   117,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   126,   127,   128,   129,
     130,   131,   131,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   137,   138,
     138
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     6,     4,
       3,     3,     3,     2,     0,     1,     3,     0,     5,     1,
       1,     3,     0,     3,     0,     6,     4,     1,     1,     3,
       0,     2,     3,     1,     1,     0,     4,     3,     2,     1,
       2,     2,     0,     1,     1,     3,     3,     4,     0,     1,
       2,     1,     1,     3,     0,     0,     5,     1,     3,     3,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     3,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     2,     1,     1,     0,     5,     2,
       0,     0,     5,     0,     6,     0,     6,     0,     1,     2,
       3,     2,     2,     2,     1,     3,     3,     2,     4,     2,
       2,     1,     2,     5,     5,     1,     2,     1,     3,     1,
       5,     1,     3,     1,     3,     4,     6,     3,     3,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     5,     1,
       1,     1,     3,     1,     3,     1,     3,     2,     3,     0,
       1
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
    { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(); }
#line 1681 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "src/fe/parser.ypp" /* yacc.c:1646  */
    { Emitter::EndBlock(); }
#line 1687 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1695 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1704 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 113 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1712 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 115 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1720 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 117 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1728 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 121 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1736 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 123 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1744 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 125 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1752 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 129 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation(sym_null, nullptr);
}
#line 1760 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 131 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.annotation) = Emitter::SetAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1768 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 135 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1776 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 139 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1784 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 141 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1792 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 145 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1800 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 147 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1808 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 151 "src/fe/parser.ypp" /* yacc.c:1646  */
    {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1814 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndFunction();
}
#line 1822 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 155 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1832 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 164 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginFunction((yyvsp[-1].expr));
}
#line 1840 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 168 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1847 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 169 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1854 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 172 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1870 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_VAR;}
#line 1876 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 184 "src/fe/parser.ypp" /* yacc.c:1646  */
    {(yyval.id) = K_SHARED;}
#line 1882 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 186 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 1888 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 186 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1903 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1910 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 196 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 1917 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 199 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 1925 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 201 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 1933 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 203 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 1941 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 207 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 1950 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 210 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 1958 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 214 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 1974 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 224 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 1986 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 232 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 1995 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 235 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2004 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 240 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = nullptr;
}
#line 2012 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 242 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2020 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 244 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2030 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 250 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2038 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 254 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2048 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 258 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2057 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    { ScannerInterface::InArrayElmDecl(); }
#line 2063 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::EndArrayElmDecl(); }
#line 2069 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 263 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2077 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 267 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2086 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 270 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2100 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 278 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2118 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 292 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_int;
}
#line 2126 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 294 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_bool;
}
#line 2134 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 296 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_object;
}
#line 2142 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 298 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_string;
}
#line 2150 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 303 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2158 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 307 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2166 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 311 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* empty stmt */
}
#line 2174 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 313 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2182 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 315 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2189 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 316 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2196 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 317 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2204 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 319 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2212 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 321 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2220 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 323 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2227 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 324 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2234 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 325 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2241 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 326 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2248 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 327 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2255 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 328 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2262 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 329 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2270 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 333 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2277 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 334 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2284 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 335 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2291 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 339 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::EndSemiColonStatement();
}
#line 2299 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 343 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
}
#line 2307 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2313 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 347 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2321 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 351 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2329 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 353 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.sym) = sym_null;
}
#line 2337 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 357 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2343 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 357 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2351 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 361 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2357 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 361 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2365 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 365 "src/fe/parser.ypp" /* yacc.c:1646  */
    {ScannerInterface::InSemiColonStatement();}
#line 2371 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 365 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2379 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 369 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2386 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 370 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  // Maybe remove this syntax later.
}
#line 2394 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 374 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2403 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 379 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2413 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 385 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2423 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 389 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2432 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 392 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2441 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 397 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
}
#line 2449 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 401 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2457 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 403 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2465 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 407 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2474 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 412 "src/fe/parser.ypp" /* yacc.c:1646  */
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
#line 2493 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 427 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2506 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 436 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2516 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 442 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::BeginBlock();
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2527 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 449 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2535 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 453 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2547 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 461 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2554 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 464 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2561 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 465 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2568 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 468 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
}
#line 2575 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 471 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EndBlock();
}
#line 2583 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 475 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  /* open new bindings */
  Emitter::BeginBlock();
}
#line 2592 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 480 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2600 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 484 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2608 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 486 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2616 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 490 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2625 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 493 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2633 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 495 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2641 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 497 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2649 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 499 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2657 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 501 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2665 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 503 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2673 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 505 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2681 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 507 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2689 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 509 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2697 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 511 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2705 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 513 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2713 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 515 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2721 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 517 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2729 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 519 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2737 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 521 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2745 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 523 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2753 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 525 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2761 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 527 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2769 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 529 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2777 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 531 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2785 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 533 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2793 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 535 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2801 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 537 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-1].sub_op), false);
}
#line 2809 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 539 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 2817 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 541 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2825 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 543 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 2834 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 546 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
}
#line 2843 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 551 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[0].num);
}
#line 2851 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 553 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 2860 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 558 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2868 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 560 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 2876 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 564 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 2884 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 566 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 2892 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 570 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 2900 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 574 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 2909 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 579 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = nullptr;
}
#line 2917 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 581 "src/fe/parser.ypp" /* yacc.c:1646  */
    {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2925 "src/fe/parser.cpp" /* yacc.c:1646  */
    break;


#line 2929 "src/fe/parser.cpp" /* yacc.c:1646  */
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
#line 585 "src/fe/parser.ypp" /* yacc.c:1906  */

