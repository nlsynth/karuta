/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "src/fe/parser.ypp"

#include "base/status.h"
#include "base/sym.h"
#include "fe/builder.h"
#include "fe/emitter.h"
#include "fe/enum_decl.h"
#include "fe/expr.h"
#include "fe/nodecode.h"
#include "fe/scanner_interface.h"
#include "fe/stmt.h"
#include "fe/var_decl.h"
#include "karuta/annotation_builder.h"

extern int yylex();
extern void yyerror(const char *msg);


#line 88 "src/fe/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_SRC_FE_PARSER_H
# define YY_SRC_FE_PARSER_H
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
    K_INPUT = 290,
    K_OUTPUT = 291,
    K_VAR = 292,
    K_WHILE = 293,
    K_WITH = 294,
    K_MODULE = 295,
    NUM = 296,
    SYM = 297,
    STR = 298,
    K_LOGIC_OR = 299,
    K_LOGIC_AND = 300,
    K_BIT_CONCAT = 301,
    SIGN = 302,
    ADDRESS = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "src/fe/parser.ypp"

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
  iroha::NumericLiteral num;
  int id;
  int sub_op;
  struct WidthSpec width_spec;
  class Annotation *annotation;
  class AnnotationKeyValue *annotation_value;
  class AnnotationKeyValueSet *annotation_value_set;

#line 210 "src/fe/parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_SRC_FE_PARSER_H  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   911

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  298

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    67,     2,     2,    52,     2,
      64,    65,    53,     2,    44,     2,    59,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    68,
       2,     2,     2,    45,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,    51,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,    50,    63,    56,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    47,
      48,    49,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   100,   100,   102,   103,   104,   104,   106,
     106,   106,   108,   110,   115,   117,   119,   121,   125,   125,
     125,   127,   129,   131,   135,   137,   139,   143,   145,   149,
     153,   155,   159,   161,   165,   165,   169,   176,   176,   176,
     178,   182,   183,   186,   198,   198,   198,   198,   200,   200,
     213,   214,   217,   219,   221,   225,   228,   232,   242,   250,
     253,   258,   260,   262,   268,   272,   276,   281,   281,   281,
     285,   288,   296,   310,   312,   314,   316,   318,   323,   327,
     331,   333,   335,   336,   337,   339,   341,   343,   344,   345,
     346,   347,   348,   349,   351,   352,   353,   354,   355,   359,
     363,   367,   367,   371,   373,   377,   377,   381,   381,   385,
     385,   389,   390,   394,   399,   405,   409,   412,   417,   421,
     423,   427,   432,   447,   456,   462,   469,   473,   481,   484,
     485,   488,   491,   495,   500,   504,   506,   510,   513,   520,
     522,   524,   526,   528,   530,   532,   534,   536,   538,   540,
     542,   544,   546,   548,   550,   552,   554,   556,   558,   560,
     562,   564,   564,   566,   568,   570,   573,   581,   583,   588,
     590,   594,   596,   600,   604,   609,   611
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
  "K_SHARED", "K_SHIFT", "K_STRING", "K_SWITCH", "K_THREAD", "K_INPUT",
  "K_OUTPUT", "K_VAR", "K_WHILE", "K_WITH", "K_MODULE", "NUM", "SYM",
  "STR", "','", "'?'", "':'", "K_LOGIC_OR", "K_LOGIC_AND", "K_BIT_CONCAT",
  "'|'", "'^'", "'&'", "'*'", "'/'", "'!'", "'~'", "SIGN", "ADDRESS",
  "'.'", "'['", "']'", "'{'", "'}'", "'('", "')'", "'@'", "'#'", "';'",
  "$accept", "input", "FUNC_DECL_OR_STMT_LIST", "FUNC_DECL_OR_STMT", "$@1",
  "MODULE_HEAD", "IMPORT_PARAM_HEAD", "ANNOTATION_VALUE", "ANNOTATION_KEY",
  "ANNOTATION_VALUE_LIST", "ANNOTATION_OR_EMPTY", "SYM_OR_EMPTY",
  "RETURN_TYPE", "RETURN_TYPE_LIST", "RETURN_SPEC", "FUNC_DECL", "$@2",
  "FUNC_DECL_HEAD", "FUNC_DECL_KW", "FUNC_DECL_NAME", "STMT_LIST",
  "VAR_DECL_TAIL", "VAR_OR_SHARED", "VAR_DECL", "$@3", "WIDTH_SPEC",
  "ARG_DECL", "ARG_DECL_LIST", "ARRAY_SPEC", "EMPTY_OR_ARRAY_SPEC",
  "ARRAY_ELM", "ARRAY_ELM_LIST", "ARRAY_INITIALIZER", "$@4", "$@5",
  "VAR_DECL_STMT", "TYPE_NAME", "LABEL", "RETURN", "STMT", "EOS",
  "GOTO_HEAD", "IMPORT_STMT", "$@6", "IMPORT_SPEC_OR_EMPTY",
  "THREAD_DECL_STMT", "$@7", "CHANNEL_DECL_STMT", "$@8",
  "MAILBOX_DECL_STMT", "$@9", "ASSIGN_OR_EMPTY", "IF_COND_PART",
  "IF_WITH_ELSE", "IF_STMT", "FOR_HEAD", "FOR_HEAD_PART", "FOR_COND_PART",
  "FOR_STMT", "WHILE_COND_PART", "WHILE_STMT", "DO_WHILE_HEAD",
  "DO_WHILE_BODY", "DO_WHILE_STMT", "SWITCH_STMT", "CASES_LIST", "CASE",
  "BLOCK", "BLOCK_HEAD", "ENUM_DECL", "ENUM_ITEM_LIST", "EXPR", "$@10",
  "NUM_EXPR", "VAR", "VAR_LIST", "FUNCALL_HEAD", "FUNCALL", "ARG_LIST", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    44,    63,    58,   299,   300,   301,
     124,    94,    38,    42,    47,    33,   126,   302,   303,    46,
      91,    93,   123,   125,    40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -192,    36,    45,  -192,   248,  -192,    20,  -192,   248,  -192,
    -192,  -192,     0,  -192,   248,    52,    52,    43,   114,  -192,
     248,   248,  -192,   248,    70,  -192,  -192,    73,   175,  -192,
     153,    94,  -192,   176,  -192,  -192,   123,  -192,    94,    94,
      94,   108,    -9,  -192,   345,   248,   117,  -192,   108,  -192,
     108,   144,  -192,  -192,  -192,  -192,   -10,   270,  -192,   248,
    -192,    40,    82,  -192,  -192,  -192,  -192,  -192,  -192,    52,
      85,   683,   143,   248,   248,    52,   683,   129,   129,   150,
    -192,  -192,   151,    82,    82,   374,   145,   146,  -192,  -192,
    -192,  -192,   224,    -2,    34,  -192,  -192,   270,   -37,    94,
    -192,  -192,  -192,   189,  -192,  -192,  -192,   139,    52,   322,
     683,   248,  -192,  -192,   147,   192,  -192,   129,   248,   248,
     248,  -192,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,  -192,   683,   155,   129,
     174,   182,   223,    82,   412,    33,  -192,  -192,  -192,   300,
    -192,    52,    52,  -192,  -192,  -192,   166,    52,    52,  -192,
    -192,  -192,  -192,    52,  -192,  -192,   683,  -192,  -192,  -192,
    -192,  -192,  -192,   503,   248,  -192,   140,  -192,    80,   721,
     482,   836,   391,   721,   645,   774,   812,   605,   827,   851,
     514,    82,    82,  -192,   541,  -192,  -192,  -192,    55,   187,
      94,   225,   195,  -192,  -192,  -192,   234,   -19,  -192,   236,
      49,   134,    38,    38,  -192,   -40,  -192,   178,   205,   129,
     452,  -192,   209,  -192,   450,   248,   248,  -192,   211,  -192,
    -192,  -192,  -192,   225,  -192,   197,  -192,     8,   219,  -192,
     226,   300,  -192,  -192,  -192,   325,   325,   243,  -192,   203,
      52,    52,   111,   208,  -192,  -192,  -192,   230,  -192,   759,
     593,  -192,  -192,  -192,  -192,   227,  -192,  -192,  -192,  -192,
    -192,  -192,   325,  -192,  -192,   129,  -192,  -192,   120,  -192,
    -192,   209,   215,  -192,  -192,  -192,    99,  -192,   218,  -192,
    -192,  -192,   325,  -192,   220,  -192,   241,  -192
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,     0,   125,     0,   100,     0,   101,
     161,    79,     0,   105,     0,     0,    11,   167,   137,   165,
       0,     0,   133,     0,    27,    99,     4,     0,    48,     5,
      70,     0,    94,     0,     6,    80,     0,    95,     0,     0,
       0,     0,     0,    88,    24,     0,     0,    89,     0,    90,
       0,     0,    91,    92,    87,    41,     0,     0,   166,   175,
     144,   137,   163,    74,    73,    75,    77,    76,   169,     0,
       0,   113,     0,     0,     0,     0,   123,     9,    10,     0,
      78,   173,     0,   145,   146,     0,    26,     0,     7,   107,
     118,   109,     0,     0,     0,    93,    86,     0,     0,     0,
      96,    97,    98,   115,   117,   116,    48,     0,     0,     0,
     121,     0,   124,   126,     0,    24,    82,    51,     0,     0,
       0,   160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,   176,     0,    50,
       0,     0,   104,   162,     0,     0,   168,   138,   139,    21,
       3,     0,     0,    37,    38,    39,     0,     0,    55,    45,
      46,    47,    44,     0,    67,    72,    71,    85,    84,    83,
     114,   120,   119,     0,     0,   132,    48,    42,   147,   151,
     153,   152,   150,   142,     0,   158,   159,   154,   156,   157,
     155,   148,   149,   143,     0,   174,   170,   135,     0,     0,
       0,     0,     0,    18,    19,    20,     0,     0,    22,     0,
       0,    24,   111,   111,    41,     0,    57,     0,    56,   171,
       0,    49,     0,   122,     0,     0,     0,   140,     0,   134,
     103,   102,   131,   128,   129,     0,   106,     0,     0,    17,
       0,     0,    25,     8,   112,     0,     0,    24,    40,    32,
       0,     0,     0,    61,    52,    64,    65,    68,   127,   164,
       0,   136,   130,    16,    14,     0,    13,    15,    23,   108,
     110,    35,     0,    36,    58,   172,    53,    54,     0,    62,
      43,     0,     0,   141,    12,    30,     0,    29,     0,    63,
      66,    69,     0,    33,    59,    31,     0,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,   133,  -192,  -192,  -192,  -192,    47,  -192,  -192,
     -42,  -192,     2,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
      78,  -155,  -192,  -192,  -192,  -191,  -192,  -192,     3,  -192,
      15,  -192,  -192,  -192,  -192,   256,   296,  -192,  -192,  -111,
     -17,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,    95,  -192,  -192,   268,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,    83,   -35,  -192,   269,
    -192,    -3,  -192,  -192,    -6,  -192,  -192,   -33,  -192
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   150,    27,   207,   208,   209,   210,
      28,    87,   285,   286,   273,    29,    92,   156,   157,   158,
     115,   216,   163,    30,    93,   287,   217,   218,   279,   280,
     256,   257,   165,   222,   282,    31,   254,    32,    33,    34,
      35,    36,    37,    72,   200,    38,    75,    39,   151,    40,
     152,   245,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   233,   234,    54,    55,    56,
     198,    57,    73,    58,   219,   220,    59,    60,   138
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    62,   106,    99,   177,    71,   103,   105,   221,    77,
      78,    76,     8,   112,    95,   113,    96,    83,    84,   140,
      85,   100,   101,   102,   248,   238,    63,    81,   159,   253,
      97,    25,    68,   160,   161,   162,     3,     4,   202,   116,
     136,   109,   110,   244,    64,    -2,   239,    65,     4,   263,
     117,   264,    66,    22,   269,   270,   137,    10,    25,     5,
      67,     6,    68,   139,    74,     7,     8,     9,    10,   145,
     143,   144,   265,   176,    11,    17,    61,    19,    12,    13,
     167,   168,   169,    14,    15,    16,    17,    18,    19,    20,
      21,   166,   140,   241,    68,   274,   164,   140,    23,   228,
      20,    21,   117,   121,    81,   121,    82,    22,   173,    23,
      79,    24,    86,    25,   242,   178,   179,   180,   229,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   132,   133,    88,   177,     4,   223,   134,
     135,   134,   135,   292,   140,   212,   213,   141,     5,    89,
       6,   215,   276,   277,     7,     8,     9,    10,    94,    90,
      80,   288,    25,    11,   293,    98,    91,    12,    13,   236,
      22,   224,    14,    15,    16,    17,    18,    19,    81,     4,
      82,   289,   114,   231,    89,   111,   142,   -34,   140,    20,
      21,   146,   147,   -34,    90,     4,    22,   243,    23,    10,
      24,    91,    25,   -34,   170,   176,     5,   171,     6,   -28,
     149,   174,     7,     8,     9,    10,   196,    17,    61,    19,
     195,    11,   259,   260,   197,    12,    13,   199,   214,   230,
      14,    20,    21,    17,    18,    19,   153,   235,   232,   237,
      23,   240,   154,   249,    25,   275,     4,    20,    21,   250,
     255,     4,   155,   261,    22,   175,    23,     5,    24,     6,
      25,    81,   266,     7,     8,     9,    10,   272,   278,   267,
     284,    10,    11,   118,   281,   119,    12,    13,   291,   294,
     296,    14,   288,   211,    17,    18,    19,   120,   268,    17,
      61,    19,   247,   121,   295,   122,   290,   297,    20,    21,
     107,   123,    69,    20,    21,    22,   271,    23,   246,    24,
     104,    25,    23,   108,   124,   125,   262,   126,   127,   128,
     129,   130,   131,   132,   133,   118,     0,   119,     0,   134,
     135,    63,     0,     0,     0,   203,   204,     0,    25,   120,
     205,     0,   206,     0,     0,   121,     0,   122,     4,    64,
       0,     0,    65,   123,     0,     0,     0,    66,     0,     0,
       0,     6,     0,     0,     0,    67,   124,   125,    10,   126,
     127,   128,   129,   130,   131,   132,   133,   118,     0,   119,
       0,   134,   135,     0,     0,     0,    17,    61,    19,     0,
     172,   120,   252,     0,   118,     0,     0,   121,     0,   122,
      20,    21,     0,     0,     0,   123,     0,     0,     0,    23,
       0,    24,     0,     0,   121,   118,     0,   119,   124,   125,
       0,   126,   127,   128,   129,   130,   131,   132,   133,   120,
       0,     0,     0,   134,   135,   121,     0,   122,     0,   148,
       0,     0,     0,   123,   132,   133,     0,     0,     0,     0,
     134,   135,     0,   118,     0,   119,   124,   125,    63,   126,
     127,   128,   129,   130,   131,   132,   133,   120,     0,     0,
       0,   134,   135,   121,     0,   122,    64,   201,     0,    65,
       0,   123,     0,     0,    66,   118,     0,     0,     0,     0,
       0,     0,    67,     0,   124,   125,   251,   126,   127,   128,
     129,   130,   131,   132,   133,   121,   118,   122,   119,   134,
     135,     0,     0,   123,     0,   258,     0,   118,     0,   252,
     120,     0,     0,     0,     0,     0,   121,     0,   122,     0,
       0,   120,     0,     0,   123,   132,   133,   121,     0,   122,
       0,   134,   135,     0,   118,   123,   119,   124,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,    22,   122,   132,   133,     0,
       0,     0,   123,   134,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   124,   125,   226,   126,   127,
     128,   129,   130,   131,   132,   133,   118,     0,   119,     0,
     134,   135,   227,     0,     0,     0,     0,     0,   118,     0,
     120,     0,     0,     0,     0,     0,   121,     0,   122,     0,
       0,     0,   120,     0,   123,     0,     0,     0,   121,     0,
     122,     0,     0,     0,     0,     0,   123,   124,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   118,     0,
     119,     0,   134,   135,   283,   129,   130,   131,   132,   133,
       0,     0,   120,     0,   134,   135,     0,     0,   121,     0,
     122,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,     0,   119,   124,
     125,   225,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,     0,   122,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,   119,   124,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,     0,   122,     0,     0,     0,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   120,   118,     0,     0,
     134,   135,   121,     0,   122,     0,     0,     0,     0,     0,
     123,   120,     0,     0,     0,     0,     0,   121,     0,   122,
       0,     0,     0,     0,   125,   123,   126,   127,   128,   129,
     130,   131,   132,   133,     0,   118,     0,     0,   134,   135,
       0,     0,   127,   128,   129,   130,   131,   132,   133,   120,
     118,     0,     0,   134,   135,   121,     0,   122,     0,   118,
       0,     0,     0,   123,   120,     0,     0,     0,     0,     0,
     121,     0,   122,     0,   118,     0,     0,     0,   123,   121,
       0,   128,   129,   130,   131,   132,   133,   123,   120,     0,
       0,   134,   135,     0,   121,     0,   122,     0,   130,   131,
     132,   133,   123,     0,     0,     0,   134,   135,     0,   132,
     133,     0,     0,     0,     0,   134,   135,     0,     0,     0,
       0,     0,     0,   131,   132,   133,     0,     0,     0,     0,
     134,   135
};

static const yytype_int16 yycheck[] =
{
       6,     4,    44,    36,   115,     8,    41,    42,   163,    15,
      16,    14,    21,    48,    31,    50,    33,    20,    21,    59,
      23,    38,    39,    40,    64,    44,     6,    64,    30,   220,
      33,    68,    42,    35,    36,    37,     0,     3,     5,    56,
      57,    44,    45,     5,    24,     0,    65,    27,     3,    41,
      56,    43,    32,    62,   245,   246,    59,    23,    68,    14,
      40,    16,    42,    69,    64,    20,    21,    22,    23,    75,
      73,    74,    64,   115,    29,    41,    42,    43,    33,    34,
      97,    98,    99,    38,    39,    40,    41,    42,    43,    55,
      56,    94,    59,    44,    42,   250,    62,    59,    64,    44,
      55,    56,   108,    23,    64,    23,    66,    62,   111,    64,
      67,    66,    42,    68,    65,   118,   119,   120,    63,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    53,    54,    62,   247,     3,   173,    59,
      60,    59,    60,    44,    59,   151,   152,    62,    14,     9,
      16,   157,    41,    42,    20,    21,    22,    23,     5,    19,
      46,    41,    68,    29,    65,    42,    26,    33,    34,   202,
      62,   174,    38,    39,    40,    41,    42,    43,    64,     3,
      66,    61,    38,   200,     9,    68,    43,    12,    59,    55,
      56,    41,    41,    18,    19,     3,    62,    63,    64,    23,
      66,    26,    68,    28,    15,   247,    14,    68,    16,    64,
      64,    64,    20,    21,    22,    23,    42,    41,    42,    43,
      65,    29,   225,   226,    42,    33,    34,     4,    62,    42,
      38,    55,    56,    41,    42,    43,    12,    42,    13,     5,
      64,     5,    18,    65,    68,   251,     3,    55,    56,    44,
      41,     3,    28,    42,    62,    63,    64,    14,    66,    16,
      68,    64,    43,    20,    21,    22,    23,    64,    60,    43,
      43,    23,    29,     3,    44,     5,    33,    34,    63,    61,
      60,    38,    41,   150,    41,    42,    43,    17,   241,    41,
      42,    43,   214,    23,   292,    25,   281,   294,    55,    56,
      44,    31,     6,    55,    56,    62,    63,    64,   213,    66,
      42,    68,    64,    44,    44,    45,   233,    47,    48,    49,
      50,    51,    52,    53,    54,     3,    -1,     5,    -1,    59,
      60,     6,    -1,    -1,    -1,    35,    36,    -1,    68,    17,
      40,    -1,    42,    -1,    -1,    23,    -1,    25,     3,    24,
      -1,    -1,    27,    31,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    40,    44,    45,    23,    47,
      48,    49,    50,    51,    52,    53,    54,     3,    -1,     5,
      -1,    59,    60,    -1,    -1,    -1,    41,    42,    43,    -1,
      68,    17,    67,    -1,     3,    -1,    -1,    23,    -1,    25,
      55,    56,    -1,    -1,    -1,    31,    -1,    -1,    -1,    64,
      -1,    66,    -1,    -1,    23,     3,    -1,     5,    44,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    17,
      -1,    -1,    -1,    59,    60,    23,    -1,    25,    -1,    65,
      -1,    -1,    -1,    31,    53,    54,    -1,    -1,    -1,    -1,
      59,    60,    -1,     3,    -1,     5,    44,    45,     6,    47,
      48,    49,    50,    51,    52,    53,    54,    17,    -1,    -1,
      -1,    59,    60,    23,    -1,    25,    24,    65,    -1,    27,
      -1,    31,    -1,    -1,    32,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    44,    45,    44,    47,    48,    49,
      50,    51,    52,    53,    54,    23,     3,    25,     5,    59,
      60,    -1,    -1,    31,    -1,    65,    -1,     3,    -1,    67,
      17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,
      -1,    17,    -1,    -1,    31,    53,    54,    23,    -1,    25,
      -1,    59,    60,    -1,     3,    31,     5,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    17,    -1,
      -1,    -1,    59,    60,    23,    62,    25,    53,    54,    -1,
      -1,    -1,    31,    59,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     3,    -1,     5,    -1,
      59,    60,    61,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,
      -1,    -1,    17,    -1,    31,    -1,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,     3,    -1,
       5,    -1,    59,    60,    61,    50,    51,    52,    53,    54,
      -1,    -1,    17,    -1,    59,    60,    -1,    -1,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      17,    -1,    -1,    -1,    59,    60,    23,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,     5,    44,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    17,    -1,
      -1,    -1,    59,    60,    23,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    17,     3,    -1,    -1,
      59,    60,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      31,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,
      -1,    -1,    -1,    -1,    45,    31,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,     3,    -1,    -1,    59,    60,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    17,
       3,    -1,    -1,    59,    60,    23,    -1,    25,    -1,     3,
      -1,    -1,    -1,    31,    17,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    25,    -1,     3,    -1,    -1,    -1,    31,    23,
      -1,    49,    50,    51,    52,    53,    54,    31,    17,    -1,
      -1,    59,    60,    -1,    23,    -1,    25,    -1,    51,    52,
      53,    54,    31,    -1,    -1,    -1,    59,    60,    -1,    53,
      54,    -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,
      59,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,    71,     0,     3,    14,    16,    20,    21,    22,
      23,    29,    33,    34,    38,    39,    40,    41,    42,    43,
      55,    56,    62,    64,    66,    68,    72,    74,    79,    84,
      92,   104,   106,   107,   108,   109,   110,   111,   114,   116,
     118,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   136,   137,   138,   140,   142,   145,
     146,    42,   140,     6,    24,    27,    32,    40,    42,   105,
     143,   140,   112,   141,    64,   115,   140,   143,   143,    67,
      46,    64,    66,   140,   140,   140,    42,    80,    62,     9,
      19,    26,    85,    93,     5,   109,   109,   140,    42,   146,
     109,   109,   109,   136,   123,   136,    79,   104,   138,   140,
     140,    68,   136,   136,    38,    89,   109,   143,     3,     5,
      17,    23,    25,    31,    44,    45,    47,    48,    49,    50,
      51,    52,    53,    54,    59,    60,   109,   140,   147,   143,
      59,    62,    43,   140,   140,   143,    41,    41,    65,    64,
      73,   117,   119,    12,    18,    28,    86,    87,    88,    30,
      35,    36,    37,    91,    62,   101,   140,   109,   109,   109,
      15,    68,    68,   140,    64,    63,    79,   108,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,    65,    42,    42,   139,     4,
     113,    65,     5,    35,    36,    40,    42,    75,    76,    77,
      78,    71,   143,   143,    62,   143,    90,    95,    96,   143,
     144,    90,   102,   136,   140,    46,    46,    61,    44,    63,
      42,   109,    13,   134,   135,    42,   146,     5,    44,    65,
       5,    44,    65,    63,     5,   120,   120,    89,    64,    65,
      44,    44,    67,    94,   105,    41,    99,   100,    65,   140,
     140,    42,   135,    41,    43,    64,    43,    43,    76,    94,
      94,    63,    64,    83,    90,   143,    41,    42,    60,    97,
      98,    44,   103,    61,    43,    81,    82,    94,    41,    61,
      99,    63,    44,    65,    61,    81,    60,    97
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    71,    71,    72,    72,    73,    72,    74,
      74,    74,    75,    75,    76,    76,    76,    76,    77,    77,
      77,    78,    78,    78,    79,    79,    79,    80,    80,    81,
      82,    82,    83,    83,    85,    84,    86,    87,    87,    87,
      88,    89,    89,    90,    91,    91,    91,    91,    93,    92,
      92,    92,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    99,   100,   100,   102,   103,   101,
     104,   104,   104,   105,   105,   105,   105,   105,   106,   107,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   109,
     110,   112,   111,   113,   113,   115,   114,   117,   116,   119,
     118,   120,   120,   121,   122,   123,   123,   123,   124,   125,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     134,   135,   136,   137,   138,   139,   139,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   140,   140,   140,   140,   140,   142,   142,   143,
     143,   144,   144,   145,   146,   147,   147
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     5,     2,
       2,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       1,     0,     1,     3,     0,     5,     2,     0,     1,     1,
       1,     3,     0,     3,     0,     6,     4,     1,     1,     1,
       3,     0,     2,     3,     1,     1,     1,     1,     0,     4,
       3,     2,     1,     2,     2,     0,     1,     1,     3,     3,
       4,     0,     1,     2,     1,     1,     3,     0,     0,     5,
       1,     3,     3,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     3,     3,     3,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     2,     2,     1,
       1,     0,     5,     2,     0,     0,     5,     0,     6,     0,
       6,     0,     1,     2,     3,     2,     2,     2,     2,     3,
       3,     2,     4,     2,     2,     1,     2,     5,     5,     1,
       2,     1,     3,     1,     5,     1,     3,     1,     3,     3,
       4,     6,     3,     3,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     0,     3,     2,     5,     1,     1,     1,     3,     1,
       3,     1,     3,     2,     3,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 104 "src/fe/parser.ypp"
                  { Emitter::SetBlockVar((yyvsp[-1].expr)); Emitter::BeginBlock(nullptr); }
#line 1742 "src/fe/parser.cpp"
    break;

  case 8:
#line 104 "src/fe/parser.ypp"
                                                                                                         { Emitter::EndBlock(); }
#line 1748 "src/fe/parser.cpp"
    break;

  case 9:
#line 106 "src/fe/parser.ypp"
                         { (yyval.expr) = (yyvsp[0].expr); }
#line 1754 "src/fe/parser.cpp"
    break;

  case 10:
#line 106 "src/fe/parser.ypp"
                                                     { (yyval.expr) = (yyvsp[0].expr); }
#line 1760 "src/fe/parser.cpp"
    break;

  case 11:
#line 106 "src/fe/parser.ypp"
                                                                             { (yyval.expr) = nullptr; }
#line 1766 "src/fe/parser.cpp"
    break;

  case 12:
#line 108 "src/fe/parser.ypp"
                                         {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1774 "src/fe/parser.cpp"
    break;

  case 13:
#line 110 "src/fe/parser.ypp"
                              {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1783 "src/fe/parser.cpp"
    break;

  case 14:
#line 115 "src/fe/parser.ypp"
                                    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1791 "src/fe/parser.cpp"
    break;

  case 15:
#line 117 "src/fe/parser.ypp"
                                                                          {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1799 "src/fe/parser.cpp"
    break;

  case 16:
#line 119 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1807 "src/fe/parser.cpp"
    break;

  case 17:
#line 121 "src/fe/parser.ypp"
                          {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1815 "src/fe/parser.cpp"
    break;

  case 18:
#line 125 "src/fe/parser.ypp"
                         { (yyval.sym) = sym_input; }
#line 1821 "src/fe/parser.cpp"
    break;

  case 19:
#line 125 "src/fe/parser.ypp"
                                                        { (yyval.sym) = sym_output; }
#line 1827 "src/fe/parser.cpp"
    break;

  case 20:
#line 125 "src/fe/parser.ypp"
                                                                                        { (yyval.sym) = sym_module; }
#line 1833 "src/fe/parser.cpp"
    break;

  case 21:
#line 127 "src/fe/parser.ypp"
                        {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1841 "src/fe/parser.cpp"
    break;

  case 22:
#line 129 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1849 "src/fe/parser.cpp"
    break;

  case 23:
#line 131 "src/fe/parser.ypp"
                                               {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1857 "src/fe/parser.cpp"
    break;

  case 24:
#line 135 "src/fe/parser.ypp"
                      {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1865 "src/fe/parser.cpp"
    break;

  case 25:
#line 137 "src/fe/parser.ypp"
                                                   {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1873 "src/fe/parser.cpp"
    break;

  case 26:
#line 139 "src/fe/parser.ypp"
            {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1881 "src/fe/parser.cpp"
    break;

  case 27:
#line 143 "src/fe/parser.ypp"
               {
  (yyval.sym) = sym_lookup("");
}
#line 1889 "src/fe/parser.cpp"
    break;

  case 28:
#line 145 "src/fe/parser.ypp"
        {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1897 "src/fe/parser.cpp"
    break;

  case 29:
#line 149 "src/fe/parser.ypp"
                         {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1905 "src/fe/parser.cpp"
    break;

  case 30:
#line 153 "src/fe/parser.ypp"
                               {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1913 "src/fe/parser.cpp"
    break;

  case 31:
#line 155 "src/fe/parser.ypp"
                                     {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1921 "src/fe/parser.cpp"
    break;

  case 32:
#line 159 "src/fe/parser.ypp"
              {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1929 "src/fe/parser.cpp"
    break;

  case 33:
#line 161 "src/fe/parser.ypp"
                             {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1937 "src/fe/parser.cpp"
    break;

  case 34:
#line 165 "src/fe/parser.ypp"
                                {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1943 "src/fe/parser.cpp"
    break;

  case 35:
#line 165 "src/fe/parser.ypp"
                                                                                                              {
  Emitter::EndFunction();
}
#line 1951 "src/fe/parser.cpp"
    break;

  case 36:
#line 169 "src/fe/parser.ypp"
                                                         {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1961 "src/fe/parser.cpp"
    break;

  case 37:
#line 176 "src/fe/parser.ypp"
                     { (yyval.id) = K_DEF; }
#line 1967 "src/fe/parser.cpp"
    break;

  case 38:
#line 176 "src/fe/parser.ypp"
                                              { (yyval.id) = K_FUNC; }
#line 1973 "src/fe/parser.cpp"
    break;

  case 39:
#line 176 "src/fe/parser.ypp"
                                                                           { (yyval.id) = K_PROCESS; }
#line 1979 "src/fe/parser.cpp"
    break;

  case 40:
#line 178 "src/fe/parser.ypp"
                                      {
  Emitter::BeginFunction((yyvsp[-1].expr), ((yyvsp[-2].id) == K_PROCESS));
}
#line 1987 "src/fe/parser.cpp"
    break;

  case 41:
#line 182 "src/fe/parser.ypp"
            {
}
#line 1994 "src/fe/parser.cpp"
    break;

  case 42:
#line 183 "src/fe/parser.ypp"
                   {
}
#line 2001 "src/fe/parser.cpp"
    break;

  case 43:
#line 186 "src/fe/parser.ypp"
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
#line 2017 "src/fe/parser.cpp"
    break;

  case 44:
#line 198 "src/fe/parser.ypp"
                      {(yyval.id) = K_VAR;}
#line 2023 "src/fe/parser.cpp"
    break;

  case 45:
#line 198 "src/fe/parser.ypp"
                                               {(yyval.id) = K_SHARED;}
#line 2029 "src/fe/parser.cpp"
    break;

  case 46:
#line 198 "src/fe/parser.ypp"
                                                                          {(yyval.id) = K_INPUT;}
#line 2035 "src/fe/parser.cpp"
    break;

  case 47:
#line 198 "src/fe/parser.ypp"
                                                                                                     {(yyval.id) = K_OUTPUT;}
#line 2041 "src/fe/parser.cpp"
    break;

  case 48:
#line 200 "src/fe/parser.ypp"
                               {ScannerInterface::InSemiColonStatement();}
#line 2047 "src/fe/parser.cpp"
    break;

  case 49:
#line 200 "src/fe/parser.ypp"
                                                                                                       {
  bool is_input = ((yyvsp[-1].id) == K_INPUT);
  bool is_output = ((yyvsp[-1].id) == K_OUTPUT);
  bool is_io = (is_input || is_output);
  bool is_shared = ((yyvsp[-1].id) == K_SHARED) || is_io;
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    Builder::SetVarDeclAnnotation(vd, (yyvsp[-3].annotation));
    if (is_shared) {
      vd->SetIsShared(true);
    }
    vd->SetIsIO(is_io, is_output);
  }
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2066 "src/fe/parser.cpp"
    break;

  case 50:
#line 213 "src/fe/parser.ypp"
                         {
}
#line 2073 "src/fe/parser.cpp"
    break;

  case 51:
#line 214 "src/fe/parser.ypp"
                  {
}
#line 2080 "src/fe/parser.cpp"
    break;

  case 52:
#line 217 "src/fe/parser.ypp"
                       {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2088 "src/fe/parser.cpp"
    break;

  case 53:
#line 219 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2096 "src/fe/parser.cpp"
    break;

  case 54:
#line 221 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2104 "src/fe/parser.cpp"
    break;

  case 55:
#line 225 "src/fe/parser.ypp"
           {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2113 "src/fe/parser.cpp"
    break;

  case 56:
#line 228 "src/fe/parser.ypp"
                  {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2121 "src/fe/parser.cpp"
    break;

  case 57:
#line 232 "src/fe/parser.ypp"
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
#line 2137 "src/fe/parser.cpp"
    break;

  case 58:
#line 242 "src/fe/parser.ypp"
                                    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2149 "src/fe/parser.cpp"
    break;

  case 59:
#line 250 "src/fe/parser.ypp"
                         {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2158 "src/fe/parser.cpp"
    break;

  case 60:
#line 253 "src/fe/parser.ypp"
                           {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2167 "src/fe/parser.cpp"
    break;

  case 61:
#line 258 "src/fe/parser.ypp"
                      {
  (yyval.shape) = nullptr;
}
#line 2175 "src/fe/parser.cpp"
    break;

  case 62:
#line 260 "src/fe/parser.ypp"
               {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2183 "src/fe/parser.cpp"
    break;

  case 63:
#line 262 "src/fe/parser.ypp"
            {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2193 "src/fe/parser.cpp"
    break;

  case 64:
#line 268 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[0].num);
}
#line 2201 "src/fe/parser.cpp"
    break;

  case 65:
#line 272 "src/fe/parser.ypp"
                           {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2211 "src/fe/parser.cpp"
    break;

  case 66:
#line 276 "src/fe/parser.ypp"
                                 {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2220 "src/fe/parser.cpp"
    break;

  case 67:
#line 281 "src/fe/parser.ypp"
                        { ScannerInterface::InArrayElmDecl(); }
#line 2226 "src/fe/parser.cpp"
    break;

  case 68:
#line 281 "src/fe/parser.ypp"
                                                                               {ScannerInterface::EndArrayElmDecl(); }
#line 2232 "src/fe/parser.cpp"
    break;

  case 69:
#line 281 "src/fe/parser.ypp"
                                                                                                                           {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2240 "src/fe/parser.cpp"
    break;

  case 70:
#line 285 "src/fe/parser.ypp"
                         {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2249 "src/fe/parser.cpp"
    break;

  case 71:
#line 288 "src/fe/parser.ypp"
                           {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2263 "src/fe/parser.cpp"
    break;

  case 72:
#line 296 "src/fe/parser.ypp"
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
#line 2281 "src/fe/parser.cpp"
    break;

  case 73:
#line 310 "src/fe/parser.ypp"
                  {
  (yyval.sym) = sym_int;
}
#line 2289 "src/fe/parser.cpp"
    break;

  case 74:
#line 312 "src/fe/parser.ypp"
           {
  (yyval.sym) = sym_bool;
}
#line 2297 "src/fe/parser.cpp"
    break;

  case 75:
#line 314 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_object;
}
#line 2305 "src/fe/parser.cpp"
    break;

  case 76:
#line 316 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_module;
}
#line 2313 "src/fe/parser.cpp"
    break;

  case 77:
#line 318 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_string;
}
#line 2321 "src/fe/parser.cpp"
    break;

  case 78:
#line 323 "src/fe/parser.ypp"
                {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2329 "src/fe/parser.cpp"
    break;

  case 79:
#line 327 "src/fe/parser.ypp"
                  {
  ScannerInterface::InSemiColonStatement();
}
#line 2337 "src/fe/parser.cpp"
    break;

  case 80:
#line 331 "src/fe/parser.ypp"
           {
  /* empty stmt */
}
#line 2345 "src/fe/parser.cpp"
    break;

  case 81:
#line 333 "src/fe/parser.ypp"
             {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2353 "src/fe/parser.cpp"
    break;

  case 82:
#line 335 "src/fe/parser.ypp"
                  {
}
#line 2360 "src/fe/parser.cpp"
    break;

  case 83:
#line 336 "src/fe/parser.ypp"
                          {
}
#line 2367 "src/fe/parser.cpp"
    break;

  case 84:
#line 337 "src/fe/parser.ypp"
                      {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2375 "src/fe/parser.cpp"
    break;

  case 85:
#line 339 "src/fe/parser.ypp"
                    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2383 "src/fe/parser.cpp"
    break;

  case 86:
#line 341 "src/fe/parser.ypp"
               {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2391 "src/fe/parser.cpp"
    break;

  case 87:
#line 343 "src/fe/parser.ypp"
          {
}
#line 2398 "src/fe/parser.cpp"
    break;

  case 88:
#line 344 "src/fe/parser.ypp"
            {
}
#line 2405 "src/fe/parser.cpp"
    break;

  case 89:
#line 345 "src/fe/parser.ypp"
             {
}
#line 2412 "src/fe/parser.cpp"
    break;

  case 90:
#line 346 "src/fe/parser.ypp"
               {
}
#line 2419 "src/fe/parser.cpp"
    break;

  case 91:
#line 347 "src/fe/parser.ypp"
                  {
}
#line 2426 "src/fe/parser.cpp"
    break;

  case 92:
#line 348 "src/fe/parser.ypp"
                {
}
#line 2433 "src/fe/parser.cpp"
    break;

  case 93:
#line 349 "src/fe/parser.ypp"
                      {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2441 "src/fe/parser.cpp"
    break;

  case 96:
#line 353 "src/fe/parser.ypp"
                         {
}
#line 2448 "src/fe/parser.cpp"
    break;

  case 97:
#line 354 "src/fe/parser.ypp"
                          {
}
#line 2455 "src/fe/parser.cpp"
    break;

  case 98:
#line 355 "src/fe/parser.ypp"
                          {
}
#line 2462 "src/fe/parser.cpp"
    break;

  case 99:
#line 359 "src/fe/parser.ypp"
          {
  ScannerInterface::EndSemiColonStatement();
}
#line 2470 "src/fe/parser.cpp"
    break;

  case 100:
#line 363 "src/fe/parser.ypp"
                   {
  ScannerInterface::InSemiColonStatement();
}
#line 2478 "src/fe/parser.cpp"
    break;

  case 101:
#line 367 "src/fe/parser.ypp"
                       {ScannerInterface::InSemiColonStatement();}
#line 2484 "src/fe/parser.cpp"
    break;

  case 102:
#line 367 "src/fe/parser.ypp"
                                                                                                {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2492 "src/fe/parser.cpp"
    break;

  case 103:
#line 371 "src/fe/parser.ypp"
                                {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2500 "src/fe/parser.cpp"
    break;

  case 104:
#line 373 "src/fe/parser.ypp"
    {
  (yyval.sym) = sym_null;
}
#line 2508 "src/fe/parser.cpp"
    break;

  case 105:
#line 377 "src/fe/parser.ypp"
                            {ScannerInterface::InSemiColonStatement();}
#line 2514 "src/fe/parser.cpp"
    break;

  case 106:
#line 377 "src/fe/parser.ypp"
                                                                                             {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2522 "src/fe/parser.cpp"
    break;

  case 107:
#line 381 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2528 "src/fe/parser.cpp"
    break;

  case 108:
#line 381 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2536 "src/fe/parser.cpp"
    break;

  case 109:
#line 385 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2542 "src/fe/parser.cpp"
    break;

  case 110:
#line 385 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2550 "src/fe/parser.cpp"
    break;

  case 111:
#line 389 "src/fe/parser.ypp"
                  {
}
#line 2557 "src/fe/parser.cpp"
    break;

  case 112:
#line 390 "src/fe/parser.ypp"
             {
  // Maybe remove this syntax later.
}
#line 2565 "src/fe/parser.cpp"
    break;

  case 113:
#line 394 "src/fe/parser.ypp"
                         {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2574 "src/fe/parser.cpp"
    break;

  case 114:
#line 399 "src/fe/parser.ypp"
                                         {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2584 "src/fe/parser.cpp"
    break;

  case 115:
#line 405 "src/fe/parser.ypp"
                             {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2594 "src/fe/parser.cpp"
    break;

  case 116:
#line 409 "src/fe/parser.ypp"
                       {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2603 "src/fe/parser.cpp"
    break;

  case 117:
#line 412 "src/fe/parser.ypp"
                         {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2612 "src/fe/parser.cpp"
    break;

  case 118:
#line 417 "src/fe/parser.ypp"
                                     {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2620 "src/fe/parser.cpp"
    break;

  case 119:
#line 421 "src/fe/parser.ypp"
                                  {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2628 "src/fe/parser.cpp"
    break;

  case 120:
#line 423 "src/fe/parser.ypp"
                               {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2636 "src/fe/parser.cpp"
    break;

  case 121:
#line 427 "src/fe/parser.ypp"
                                   {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2645 "src/fe/parser.cpp"
    break;

  case 122:
#line 432 "src/fe/parser.ypp"
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
#line 2664 "src/fe/parser.cpp"
    break;

  case 123:
#line 447 "src/fe/parser.ypp"
                               {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2677 "src/fe/parser.cpp"
    break;

  case 124:
#line 456 "src/fe/parser.ypp"
                                   {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2687 "src/fe/parser.cpp"
    break;

  case 125:
#line 462 "src/fe/parser.ypp"
                     {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2698 "src/fe/parser.cpp"
    break;

  case 126:
#line 469 "src/fe/parser.ypp"
                                    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2706 "src/fe/parser.cpp"
    break;

  case 127:
#line 473 "src/fe/parser.ypp"
                                                   {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2718 "src/fe/parser.cpp"
    break;

  case 128:
#line 481 "src/fe/parser.ypp"
                                               {
}
#line 2725 "src/fe/parser.cpp"
    break;

  case 129:
#line 484 "src/fe/parser.ypp"
                  {
}
#line 2732 "src/fe/parser.cpp"
    break;

  case 130:
#line 485 "src/fe/parser.ypp"
                    {
}
#line 2739 "src/fe/parser.cpp"
    break;

  case 131:
#line 488 "src/fe/parser.ypp"
                 {
}
#line 2746 "src/fe/parser.cpp"
    break;

  case 132:
#line 491 "src/fe/parser.ypp"
                                 {
  Emitter::EndBlock();
}
#line 2754 "src/fe/parser.cpp"
    break;

  case 133:
#line 495 "src/fe/parser.ypp"
                 {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2763 "src/fe/parser.cpp"
    break;

  case 134:
#line 500 "src/fe/parser.ypp"
                                              {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2771 "src/fe/parser.cpp"
    break;

  case 135:
#line 504 "src/fe/parser.ypp"
                     {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2779 "src/fe/parser.cpp"
    break;

  case 136:
#line 506 "src/fe/parser.ypp"
                           {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2787 "src/fe/parser.cpp"
    break;

  case 137:
#line 510 "src/fe/parser.ypp"
           {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2796 "src/fe/parser.cpp"
    break;

  case 138:
#line 513 "src/fe/parser.ypp"
                {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2809 "src/fe/parser.cpp"
    break;

  case 139:
#line 520 "src/fe/parser.ypp"
                 {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2817 "src/fe/parser.cpp"
    break;

  case 140:
#line 522 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2825 "src/fe/parser.cpp"
    break;

  case 141:
#line 524 "src/fe/parser.ypp"
                               {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2833 "src/fe/parser.cpp"
    break;

  case 142:
#line 526 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2841 "src/fe/parser.cpp"
    break;

  case 143:
#line 528 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2849 "src/fe/parser.cpp"
    break;

  case 144:
#line 530 "src/fe/parser.ypp"
            {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2857 "src/fe/parser.cpp"
    break;

  case 145:
#line 532 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2865 "src/fe/parser.cpp"
    break;

  case 146:
#line 534 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2873 "src/fe/parser.cpp"
    break;

  case 147:
#line 536 "src/fe/parser.ypp"
                        {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2881 "src/fe/parser.cpp"
    break;

  case 148:
#line 538 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2889 "src/fe/parser.cpp"
    break;

  case 149:
#line 540 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2897 "src/fe/parser.cpp"
    break;

  case 150:
#line 542 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2905 "src/fe/parser.cpp"
    break;

  case 151:
#line 544 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2913 "src/fe/parser.cpp"
    break;

  case 152:
#line 546 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2921 "src/fe/parser.cpp"
    break;

  case 153:
#line 548 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2929 "src/fe/parser.cpp"
    break;

  case 154:
#line 550 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2937 "src/fe/parser.cpp"
    break;

  case 155:
#line 552 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2945 "src/fe/parser.cpp"
    break;

  case 156:
#line 554 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2953 "src/fe/parser.cpp"
    break;

  case 157:
#line 556 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2961 "src/fe/parser.cpp"
    break;

  case 158:
#line 558 "src/fe/parser.ypp"
                         {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2969 "src/fe/parser.cpp"
    break;

  case 159:
#line 560 "src/fe/parser.ypp"
                          {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2977 "src/fe/parser.cpp"
    break;

  case 160:
#line 562 "src/fe/parser.ypp"
                   {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 2985 "src/fe/parser.cpp"
    break;

  case 161:
#line 564 "src/fe/parser.ypp"
              {ScannerInterface::InSemiColonStatement();}
#line 2991 "src/fe/parser.cpp"
    break;

  case 162:
#line 564 "src/fe/parser.ypp"
                                                                {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-2].sub_op), false);
}
#line 2999 "src/fe/parser.cpp"
    break;

  case 163:
#line 566 "src/fe/parser.ypp"
                              {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 3007 "src/fe/parser.cpp"
    break;

  case 164:
#line 568 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 3015 "src/fe/parser.cpp"
    break;

  case 165:
#line 570 "src/fe/parser.ypp"
        {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 3024 "src/fe/parser.cpp"
    break;

  case 166:
#line 573 "src/fe/parser.ypp"
             {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 3036 "src/fe/parser.cpp"
    break;

  case 167:
#line 581 "src/fe/parser.ypp"
               {
  (yyval.num) = (yyvsp[0].num);
}
#line 3044 "src/fe/parser.cpp"
    break;

  case 168:
#line 583 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 3053 "src/fe/parser.cpp"
    break;

  case 169:
#line 588 "src/fe/parser.ypp"
          {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 3061 "src/fe/parser.cpp"
    break;

  case 170:
#line 590 "src/fe/parser.ypp"
                {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 3069 "src/fe/parser.cpp"
    break;

  case 171:
#line 594 "src/fe/parser.ypp"
               {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 3077 "src/fe/parser.cpp"
    break;

  case 172:
#line 596 "src/fe/parser.ypp"
                     {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 3085 "src/fe/parser.cpp"
    break;

  case 173:
#line 600 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 3093 "src/fe/parser.cpp"
    break;

  case 174:
#line 604 "src/fe/parser.ypp"
                                     {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3102 "src/fe/parser.cpp"
    break;

  case 175:
#line 609 "src/fe/parser.ypp"
           {
  (yyval.expr) = nullptr;
}
#line 3110 "src/fe/parser.cpp"
    break;

  case 176:
#line 611 "src/fe/parser.ypp"
         {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3118 "src/fe/parser.cpp"
    break;


#line 3122 "src/fe/parser.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 615 "src/fe/parser.ypp"

