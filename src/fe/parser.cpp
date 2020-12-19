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
    K_ALWAYS = 259,
    K_AS = 260,
    K_ASSIGN = 261,
    K_BOOL = 262,
    K_BREAK = 263,
    K_CASE = 264,
    K_CHANNEL = 265,
    K_CONST = 266,
    K_CONTINUE = 267,
    K_DEF = 268,
    K_DEFAULT = 269,
    K_DO = 270,
    K_ELSE = 271,
    K_ENUM = 272,
    K_EQ_COMPARE = 273,
    K_FUNC = 274,
    K_FOR = 275,
    K_GOTO = 276,
    K_IF = 277,
    K_IMPORT = 278,
    K_INC_DEC = 279,
    K_INT = 280,
    K_LG_COMPARE = 281,
    K_MAILBOX = 282,
    K_OBJECT = 283,
    K_PROCESS = 284,
    K_RETURN = 285,
    K_SHARED = 286,
    K_SHIFT = 287,
    K_STRING = 288,
    K_SWITCH = 289,
    K_THREAD = 290,
    K_INPUT = 291,
    K_OUTPUT = 292,
    K_VAR = 293,
    K_WHILE = 294,
    K_WITH = 295,
    K_MODULE = 296,
    NUM = 297,
    SYM = 298,
    STR = 299,
    K_LOGIC_OR = 300,
    K_LOGIC_AND = 301,
    K_BIT_CONCAT = 302,
    SIGN = 303,
    ADDRESS = 304
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

#line 211 "src/fe/parser.cpp"

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
#define YYLAST   965

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  299

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


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
       2,     2,     2,    56,     2,    68,     2,     2,    53,     2,
      65,    66,    54,     2,    45,     2,    60,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    69,
       2,     2,     2,    46,    67,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,    51,    64,    57,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      48,    49,    50,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    98,    98,   100,   100,   102,   103,   104,   104,   106,
     106,   106,   108,   110,   115,   117,   119,   121,   125,   125,
     125,   127,   129,   131,   135,   137,   139,   143,   145,   149,
     153,   155,   159,   161,   165,   165,   169,   176,   176,   176,
     176,   178,   183,   184,   187,   199,   199,   199,   199,   201,
     201,   214,   215,   218,   220,   222,   226,   229,   233,   243,
     251,   254,   259,   261,   263,   269,   273,   277,   282,   282,
     282,   286,   289,   297,   311,   313,   315,   317,   319,   324,
     328,   332,   334,   336,   337,   338,   340,   342,   344,   345,
     346,   347,   348,   349,   350,   352,   353,   354,   355,   356,
     360,   364,   368,   368,   372,   374,   378,   378,   382,   382,
     386,   386,   390,   391,   395,   400,   406,   410,   413,   418,
     422,   424,   428,   433,   448,   457,   463,   470,   474,   482,
     485,   486,   489,   492,   496,   501,   505,   507,   511,   514,
     521,   523,   525,   527,   529,   531,   533,   535,   537,   539,
     541,   543,   545,   547,   549,   551,   553,   555,   557,   559,
     561,   563,   565,   565,   567,   569,   571,   574,   582,   584,
     589,   591,   595,   597,   601,   605,   610,   612
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_ADD_SUB", "K_ALWAYS", "K_AS",
  "K_ASSIGN", "K_BOOL", "K_BREAK", "K_CASE", "K_CHANNEL", "K_CONST",
  "K_CONTINUE", "K_DEF", "K_DEFAULT", "K_DO", "K_ELSE", "K_ENUM",
  "K_EQ_COMPARE", "K_FUNC", "K_FOR", "K_GOTO", "K_IF", "K_IMPORT",
  "K_INC_DEC", "K_INT", "K_LG_COMPARE", "K_MAILBOX", "K_OBJECT",
  "K_PROCESS", "K_RETURN", "K_SHARED", "K_SHIFT", "K_STRING", "K_SWITCH",
  "K_THREAD", "K_INPUT", "K_OUTPUT", "K_VAR", "K_WHILE", "K_WITH",
  "K_MODULE", "NUM", "SYM", "STR", "','", "'?'", "':'", "K_LOGIC_OR",
  "K_LOGIC_AND", "K_BIT_CONCAT", "'|'", "'^'", "'&'", "'*'", "'/'", "'!'",
  "'~'", "SIGN", "ADDRESS", "'.'", "'['", "']'", "'{'", "'}'", "'('",
  "')'", "'@'", "'#'", "';'", "$accept", "input", "FUNC_DECL_OR_STMT_LIST",
  "FUNC_DECL_OR_STMT", "$@1", "MODULE_HEAD", "IMPORT_PARAM_HEAD",
  "ANNOTATION_VALUE", "ANNOTATION_KEY", "ANNOTATION_VALUE_LIST",
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
     295,   296,   297,   298,   299,    44,    63,    58,   300,   301,
     302,   124,    94,    38,    42,    47,    33,   126,   303,   304,
      46,    91,    93,   123,   125,    40,    41,    64,    35,    59
};
# endif

#define YYPACT_NINF (-196)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-50)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -196,    60,    44,  -196,   155,  -196,    21,  -196,   155,  -196,
    -196,  -196,   -32,  -196,   155,    90,    90,   -36,    47,  -196,
     155,   155,  -196,   155,   107,  -196,  -196,    40,   927,  -196,
     151,    92,  -196,   352,  -196,  -196,   125,  -196,    92,    92,
      92,   108,   -10,  -196,   376,   155,   109,  -196,   108,  -196,
     108,   138,  -196,  -196,  -196,  -196,   -24,   282,  -196,   155,
    -196,    95,    82,  -196,  -196,  -196,  -196,  -196,  -196,    90,
      91,   688,   136,   155,   155,    90,   688,   121,   121,   141,
    -196,  -196,   143,    82,    82,   404,   123,   124,  -196,  -196,
    -196,  -196,   134,   199,    33,  -196,  -196,   282,    79,    92,
    -196,  -196,  -196,   174,  -196,  -196,  -196,   131,    90,   320,
     688,   155,  -196,  -196,   137,   210,  -196,   121,   155,   155,
     155,  -196,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,  -196,   688,   135,   121,
     160,   161,   200,    82,   442,    32,  -196,  -196,  -196,   -12,
    -196,    90,    90,  -196,  -196,  -196,  -196,   144,    90,    90,
    -196,  -196,  -196,  -196,    90,  -196,  -196,   688,  -196,  -196,
    -196,  -196,  -196,  -196,   518,   155,  -196,   139,  -196,    80,
     726,   806,   891,   536,   726,   650,   802,   818,   856,   872,
     888,   618,    82,    82,  -196,   556,  -196,  -196,  -196,    54,
     167,    92,   204,   171,  -196,  -196,  -196,   216,   -18,  -196,
     220,   -11,   152,    37,    37,  -196,    45,  -196,   162,   184,
     121,   357,  -196,   196,  -196,   480,   155,   155,  -196,   198,
    -196,  -196,  -196,  -196,   204,  -196,   177,  -196,    -7,   195,
    -196,   203,   -12,  -196,  -196,  -196,   261,   261,   248,  -196,
     178,    90,    90,   122,   187,  -196,  -196,  -196,   205,  -196,
     764,   609,  -196,  -196,  -196,  -196,   211,  -196,  -196,  -196,
    -196,  -196,  -196,   261,  -196,  -196,   121,  -196,  -196,    94,
    -196,  -196,   196,   192,  -196,  -196,  -196,    27,  -196,   197,
    -196,  -196,  -196,   261,  -196,   201,  -196,   215,  -196
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    24,     1,     0,   126,     0,   101,     0,   102,
     162,    80,     0,   106,     0,     0,    11,   168,   138,   166,
       0,     0,   134,     0,    27,   100,     4,     0,    34,     5,
      71,     0,    95,     0,     6,    81,     0,    96,     0,     0,
       0,     0,     0,    89,    24,     0,     0,    90,     0,    91,
       0,     0,    92,    93,    88,    42,     0,     0,   167,   176,
     145,   138,   164,    75,    74,    76,    78,    77,   170,     0,
       0,   114,     0,     0,     0,     0,   124,     9,    10,     0,
      79,   174,     0,   146,   147,     0,    26,     0,     7,   108,
     119,   110,     0,     0,     0,    94,    87,     0,     0,     0,
      97,    98,    99,   116,   118,   117,    49,     0,     0,     0,
     122,     0,   125,   127,     0,    24,    83,    52,     0,     0,
       0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,   177,     0,    51,
       0,     0,   105,   163,     0,     0,   169,   139,   140,    21,
       3,     0,     0,    40,    37,    38,    39,     0,     0,    56,
      46,    47,    48,    45,     0,    68,    73,    72,    86,    85,
      84,   115,   121,   120,     0,     0,   133,    49,    43,   148,
     152,   154,   153,   151,   143,     0,   159,   160,   155,   157,
     158,   156,   149,   150,   144,     0,   175,   171,   136,     0,
       0,     0,     0,     0,    18,    19,    20,     0,     0,    22,
       0,     0,    24,   112,   112,    42,     0,    58,     0,    57,
     172,     0,    50,     0,   123,     0,     0,     0,   141,     0,
     135,   104,   103,   132,   129,   130,     0,   107,     0,     0,
      17,     0,     0,    25,     8,   113,     0,     0,    24,    41,
      32,     0,     0,     0,    62,    53,    65,    66,    69,   128,
     165,     0,   137,   131,    16,    14,     0,    13,    15,    23,
     109,   111,    35,     0,    36,    59,   173,    54,    55,     0,
      63,    44,     0,     0,   142,    12,    30,     0,    29,     0,
      64,    67,    70,     0,    33,    60,    31,     0,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,   110,  -196,  -196,  -196,  -196,    16,  -196,  -196,
     -42,  -196,   -29,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
      46,  -156,  -196,  -196,  -196,  -195,  -196,  -196,   -19,  -196,
      -2,  -196,  -196,  -196,  -196,   237,   278,  -196,  -196,  -111,
     -17,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,    81,  -196,  -196,   251,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,    62,   -35,  -196,   253,
    -196,    -3,  -196,  -196,    -6,  -196,  -196,   -33,  -196
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,   150,    27,   208,   209,   210,   211,
      28,    87,   286,   287,   274,    29,    92,   157,   158,   159,
     115,   217,   164,    30,    93,   288,   218,   219,   280,   281,
     257,   258,   166,   223,   283,    31,   255,    32,    33,    34,
      35,    36,    37,    72,   201,    38,    75,    39,   151,    40,
     152,   246,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,   234,   235,    54,    55,    56,
     199,    57,    73,    58,   220,   221,    59,    60,   138
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    62,   106,    99,   178,    71,   103,   105,   222,    77,
      78,    76,     8,   112,    95,   113,    96,    83,    84,    68,
      85,   100,   101,   102,   204,   205,   254,   239,    63,   206,
      97,   207,    79,    74,   242,   264,     4,   265,   203,   116,
     136,   109,   110,   245,    -2,    25,    64,     4,   240,    65,
     117,   270,   271,    22,    66,   243,   137,    10,   266,     5,
       3,     6,    67,   139,    68,     7,     8,     9,    10,   145,
     143,   144,   293,   177,    11,    17,    61,    19,    12,    13,
     168,   169,   170,    14,    15,    16,    17,    18,    19,    20,
      21,   167,   140,   294,    80,   275,   165,   140,    23,   229,
      20,    21,   117,    88,   121,   140,   121,    22,   174,    23,
     249,    24,    81,    25,    82,   179,   180,   181,   230,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,    68,   132,   133,   289,   178,   153,   224,
     134,   135,   134,   135,    81,   213,   214,   154,    25,    89,
      86,   140,   216,   155,   141,     4,   290,    94,     4,    90,
      81,    25,    82,   156,   277,   278,    91,     5,    98,     6,
     237,    22,   225,     7,     8,     9,    10,   114,   111,    10,
     142,   140,    11,   146,   232,   147,    12,    13,   -28,   149,
     171,    14,    15,    16,    17,    18,    19,    17,    61,    19,
     172,   196,   175,   197,   198,   200,   177,   215,    20,    21,
     231,    20,    21,     4,   236,    22,   244,    23,   233,    24,
      23,    25,   238,   260,   261,     5,   241,     6,   250,   251,
     160,     7,     8,     9,    10,   161,   162,   163,   256,   267,
      11,   262,    81,   273,    12,    13,   276,   268,   279,    14,
     282,     4,    17,    18,    19,   285,   292,   289,   269,   295,
     212,   248,   297,     5,   296,     6,    20,    21,    63,     7,
       8,     9,    10,    22,   176,    23,   298,    24,    11,    25,
     291,   107,    12,    13,    69,   118,    64,    14,   119,    65,
      17,    18,    19,   104,    66,   247,   263,   108,     0,     0,
     120,     0,    67,     0,    20,    21,   121,     0,   122,     0,
       0,    22,   272,    23,   123,    24,     0,    25,     0,     0,
       0,     0,     0,   118,     0,     0,   119,   124,   125,   253,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,     0,   122,     0,     0,     0,
       0,    25,   123,     0,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,    63,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,    10,     0,     0,     4,
     134,   135,    64,     0,     0,    65,     0,     0,     0,   173,
      66,     0,     0,     6,    17,    61,    19,     0,    67,     0,
      10,     0,   252,     0,     0,     0,     0,   118,    20,    21,
     119,     0,     0,     0,     0,     0,     0,    23,    17,    61,
      19,    25,   120,     0,     0,   253,     0,     0,   121,     0,
     122,     0,    20,    21,     0,     0,   123,     0,     0,     0,
       0,    23,     0,    24,     0,   118,     0,     0,   119,   124,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     120,     0,     0,     0,   134,   135,   121,     0,   122,     0,
     148,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,   118,     0,     0,   119,   124,   125,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   120,     0,
       0,     0,   134,   135,   121,     0,   122,     0,   202,     0,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
       0,   118,     0,     0,   119,   124,   125,     0,   126,   127,
     128,   129,   130,   131,   132,   133,   120,     0,     0,   118,
     134,   135,   121,     0,   122,     0,   259,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     121,     0,   119,   124,   125,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   120,     0,     0,     0,   134,   135,
     121,    22,   122,     0,     0,     0,     0,     0,   123,     0,
     132,   133,     0,     0,     0,     0,   134,   135,     0,     0,
       0,   124,   125,   227,   126,   127,   128,   129,   130,   131,
     132,   133,   118,     0,     0,   119,   134,   135,   228,     0,
       0,   118,     0,     0,     0,     0,     0,   120,     0,     0,
       0,     0,     0,   121,     0,   122,   120,     0,     0,     0,
       0,   123,   121,     0,   122,     0,     0,     0,     0,     0,
     123,     0,     0,   118,   124,   125,   119,   126,   127,   128,
     129,   130,   131,   132,   133,     0,     0,     0,   120,   134,
     135,   284,   132,   133,   121,     0,   122,     0,   134,   135,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
       0,   118,     0,     0,   119,   124,   125,   226,   126,   127,
     128,   129,   130,   131,   132,   133,   120,     0,     0,     0,
     134,   135,   121,     0,   122,     0,     0,     0,     0,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,   118,
       0,     0,   119,   124,   125,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   120,     0,     0,     0,   134,   135,
     121,     0,   122,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,     0,     0,   118,     0,     0,
       0,     0,   125,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   120,     0,     0,     0,   134,   135,   121,     0,
     122,     0,     0,     0,     0,     0,   123,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,     0,     0,   118,
     125,     0,   126,   127,   128,   129,   130,   131,   132,   133,
     120,   118,     0,     0,   134,   135,   121,     0,   122,     0,
     121,     0,   122,     0,   123,     0,   120,     0,   123,     0,
       0,     0,   121,     0,   122,     0,     0,     0,     0,     0,
     123,   127,   128,   129,   130,   131,   132,   133,     0,   118,
     132,   133,   134,   135,     0,     0,   134,   135,   128,   129,
     130,   131,   132,   133,   120,   118,     0,     0,   134,   135,
     121,     0,   122,     0,     0,     0,     0,     0,   123,     0,
     120,   118,     0,     0,   118,     0,   121,     0,   122,     0,
       0,     0,     0,     0,   123,     0,   120,   129,   130,   131,
     132,   133,   121,     0,   122,   121,   134,   135,     0,     0,
     123,     0,     0,   123,   130,   131,   132,   133,     0,     0,
       0,     0,   134,   135,     0,     0,     0,    89,     0,     0,
       0,   131,   132,   133,     0,   132,   133,    90,   134,   135,
       0,   134,   135,     0,    91,     0,     0,     0,   -49,     0,
       0,     0,     0,   -49,   -49,   -49
};

static const yytype_int16 yycheck[] =
{
       6,     4,    44,    36,   115,     8,    41,    42,   164,    15,
      16,    14,    22,    48,    31,    50,    33,    20,    21,    43,
      23,    38,    39,    40,    36,    37,   221,    45,     7,    41,
      33,    43,    68,    65,    45,    42,     3,    44,     6,    56,
      57,    44,    45,     6,     0,    69,    25,     3,    66,    28,
      56,   246,   247,    63,    33,    66,    59,    24,    65,    15,
       0,    17,    41,    69,    43,    21,    22,    23,    24,    75,
      73,    74,    45,   115,    30,    42,    43,    44,    34,    35,
      97,    98,    99,    39,    40,    41,    42,    43,    44,    56,
      57,    94,    60,    66,    47,   251,    63,    60,    65,    45,
      56,    57,   108,    63,    24,    60,    24,    63,   111,    65,
      65,    67,    65,    69,    67,   118,   119,   120,    64,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,    43,    54,    55,    42,   248,     4,   174,
      60,    61,    60,    61,    65,   151,   152,    13,    69,    10,
      43,    60,   158,    19,    63,     3,    62,     6,     3,    20,
      65,    69,    67,    29,    42,    43,    27,    15,    43,    17,
     203,    63,   175,    21,    22,    23,    24,    39,    69,    24,
      44,    60,    30,    42,   201,    42,    34,    35,    65,    65,
      16,    39,    40,    41,    42,    43,    44,    42,    43,    44,
      69,    66,    65,    43,    43,     5,   248,    63,    56,    57,
      43,    56,    57,     3,    43,    63,    64,    65,    14,    67,
      65,    69,     6,   226,   227,    15,     6,    17,    66,    45,
      31,    21,    22,    23,    24,    36,    37,    38,    42,    44,
      30,    43,    65,    65,    34,    35,   252,    44,    61,    39,
      45,     3,    42,    43,    44,    44,    64,    42,   242,    62,
     150,   215,    61,    15,   293,    17,    56,    57,     7,    21,
      22,    23,    24,    63,    64,    65,   295,    67,    30,    69,
     282,    44,    34,    35,     6,     3,    25,    39,     6,    28,
      42,    43,    44,    42,    33,   214,   234,    44,    -1,    -1,
      18,    -1,    41,    -1,    56,    57,    24,    -1,    26,    -1,
      -1,    63,    64,    65,    32,    67,    -1,    69,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,     6,    45,    46,    68,
      48,    49,    50,    51,    52,    53,    54,    55,    18,    -1,
      -1,    -1,    60,    61,    24,    -1,    26,    -1,    -1,    -1,
      -1,    69,    32,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     7,    45,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    24,    -1,    -1,     3,
      60,    61,    25,    -1,    -1,    28,    -1,    -1,    -1,    69,
      33,    -1,    -1,    17,    42,    43,    44,    -1,    41,    -1,
      24,    -1,    45,    -1,    -1,    -1,    -1,     3,    56,    57,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    65,    42,    43,
      44,    69,    18,    -1,    -1,    68,    -1,    -1,    24,    -1,
      26,    -1,    56,    57,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    65,    -1,    67,    -1,     3,    -1,    -1,     6,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      18,    -1,    -1,    -1,    60,    61,    24,    -1,    26,    -1,
      66,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,     6,    45,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    18,    -1,
      -1,    -1,    60,    61,    24,    -1,    26,    -1,    66,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,     6,    45,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    18,    -1,    -1,     3,
      60,    61,    24,    -1,    26,    -1,    66,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      24,    -1,     6,    45,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    18,    -1,    -1,    -1,    60,    61,
      24,    63,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      54,    55,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,     3,    -1,    -1,     6,    60,    61,    62,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    26,    18,    -1,    -1,    -1,
      -1,    32,    24,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,     3,    45,    46,     6,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    18,    60,
      61,    62,    54,    55,    24,    -1,    26,    -1,    60,    61,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    -1,    -1,     6,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    18,    -1,    -1,    -1,
      60,    61,    24,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,     6,    45,    46,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    18,    -1,    -1,    -1,    60,    61,
      24,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    -1,    46,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    18,    -1,    -1,    -1,    60,    61,    24,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,     3,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      18,     3,    -1,    -1,    60,    61,    24,    -1,    26,    -1,
      24,    -1,    26,    -1,    32,    -1,    18,    -1,    32,    -1,
      -1,    -1,    24,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    49,    50,    51,    52,    53,    54,    55,    -1,     3,
      54,    55,    60,    61,    -1,    -1,    60,    61,    50,    51,
      52,    53,    54,    55,    18,     3,    -1,    -1,    60,    61,
      24,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      18,     3,    -1,    -1,     3,    -1,    24,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    18,    51,    52,    53,
      54,    55,    24,    -1,    26,    24,    60,    61,    -1,    -1,
      32,    -1,    -1,    32,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    10,    -1,    -1,
      -1,    53,    54,    55,    -1,    54,    55,    20,    60,    61,
      -1,    60,    61,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    71,    72,     0,     3,    15,    17,    21,    22,    23,
      24,    30,    34,    35,    39,    40,    41,    42,    43,    44,
      56,    57,    63,    65,    67,    69,    73,    75,    80,    85,
      93,   105,   107,   108,   109,   110,   111,   112,   115,   117,
     119,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   137,   138,   139,   141,   143,   146,
     147,    43,   141,     7,    25,    28,    33,    41,    43,   106,
     144,   141,   113,   142,    65,   116,   141,   144,   144,    68,
      47,    65,    67,   141,   141,   141,    43,    81,    63,    10,
      20,    27,    86,    94,     6,   110,   110,   141,    43,   147,
     110,   110,   110,   137,   124,   137,    80,   105,   139,   141,
     141,    69,   137,   137,    39,    90,   110,   144,     3,     6,
      18,    24,    26,    32,    45,    46,    48,    49,    50,    51,
      52,    53,    54,    55,    60,    61,   110,   141,   148,   144,
      60,    63,    44,   141,   141,   144,    42,    42,    66,    65,
      74,   118,   120,     4,    13,    19,    29,    87,    88,    89,
      31,    36,    37,    38,    92,    63,   102,   141,   110,   110,
     110,    16,    69,    69,   141,    65,    64,    80,   109,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,    66,    43,    43,   140,
       5,   114,    66,     6,    36,    37,    41,    43,    76,    77,
      78,    79,    72,   144,   144,    63,   144,    91,    96,    97,
     144,   145,    91,   103,   137,   141,    47,    47,    62,    45,
      64,    43,   110,    14,   135,   136,    43,   147,     6,    45,
      66,     6,    45,    66,    64,     6,   121,   121,    90,    65,
      66,    45,    45,    68,    95,   106,    42,   100,   101,    66,
     141,   141,    43,   136,    42,    44,    65,    44,    44,    77,
      95,    95,    64,    65,    84,    91,   144,    42,    43,    61,
      98,    99,    45,   104,    62,    44,    82,    83,    95,    42,
      62,   100,    64,    45,    66,    62,    82,    61,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    74,    73,    75,
      75,    75,    76,    76,    77,    77,    77,    77,    78,    78,
      78,    79,    79,    79,    80,    80,    80,    81,    81,    82,
      83,    83,    84,    84,    86,    85,    87,    88,    88,    88,
      88,    89,    90,    90,    91,    92,    92,    92,    92,    94,
      93,    93,    93,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,    99,   100,   101,   101,   103,   104,
     102,   105,   105,   105,   106,   106,   106,   106,   106,   107,
     108,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     110,   111,   113,   112,   114,   114,   116,   115,   118,   117,
     120,   119,   121,   121,   122,   123,   124,   124,   124,   125,
     126,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   135,   136,   137,   138,   139,   140,   140,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   142,   141,   141,   141,   141,   141,   143,   143,
     144,   144,   145,   145,   146,   147,   148,   148
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     5,     2,
       2,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       1,     0,     1,     3,     0,     5,     2,     0,     1,     1,
       1,     3,     0,     3,     0,     6,     4,     1,     1,     1,
       1,     3,     0,     2,     3,     1,     1,     1,     1,     0,
       4,     3,     2,     1,     2,     2,     0,     1,     1,     3,
       3,     4,     0,     1,     2,     1,     1,     3,     0,     0,
       5,     1,     3,     3,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     2,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     2,     2,
       1,     1,     0,     5,     2,     0,     0,     5,     0,     6,
       0,     6,     0,     1,     2,     3,     2,     2,     2,     2,
       3,     3,     2,     4,     2,     2,     1,     2,     5,     5,
       1,     2,     1,     3,     1,     5,     1,     3,     1,     3,
       3,     4,     6,     3,     3,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     0,     3,     2,     5,     1,     1,     1,     3,
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
#line 1753 "src/fe/parser.cpp"
    break;

  case 8:
#line 104 "src/fe/parser.ypp"
                                                                                                         { Emitter::EndBlock(); }
#line 1759 "src/fe/parser.cpp"
    break;

  case 9:
#line 106 "src/fe/parser.ypp"
                         { (yyval.expr) = (yyvsp[0].expr); }
#line 1765 "src/fe/parser.cpp"
    break;

  case 10:
#line 106 "src/fe/parser.ypp"
                                                     { (yyval.expr) = (yyvsp[0].expr); }
#line 1771 "src/fe/parser.cpp"
    break;

  case 11:
#line 106 "src/fe/parser.ypp"
                                                                             { (yyval.expr) = nullptr; }
#line 1777 "src/fe/parser.cpp"
    break;

  case 12:
#line 108 "src/fe/parser.ypp"
                                         {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-3].sym), (yyvsp[0].str));
}
#line 1785 "src/fe/parser.cpp"
    break;

  case 13:
#line 110 "src/fe/parser.ypp"
                              {
  AnnotationBuilder::AddStrParam((yyvsp[-2].annotation_value), (yyvsp[0].str));
  (yyval.annotation_value) = (yyvsp[-2].annotation_value);
}
#line 1794 "src/fe/parser.cpp"
    break;

  case 14:
#line 115 "src/fe/parser.ypp"
                                    {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1802 "src/fe/parser.cpp"
    break;

  case 15:
#line 117 "src/fe/parser.ypp"
                                                                          {
  (yyval.annotation_value) = AnnotationBuilder::BuildStrParam((yyvsp[-2].sym), (yyvsp[0].str));
}
#line 1810 "src/fe/parser.cpp"
    break;

  case 16:
#line 119 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value) = AnnotationBuilder::BuildIntParam((yyvsp[-2].sym), (yyvsp[0].num).value);
}
#line 1818 "src/fe/parser.cpp"
    break;

  case 17:
#line 121 "src/fe/parser.ypp"
                          {
  (yyval.annotation_value) = (yyvsp[-1].annotation_value);
}
#line 1826 "src/fe/parser.cpp"
    break;

  case 18:
#line 125 "src/fe/parser.ypp"
                         { (yyval.sym) = sym_input; }
#line 1832 "src/fe/parser.cpp"
    break;

  case 19:
#line 125 "src/fe/parser.ypp"
                                                        { (yyval.sym) = sym_output; }
#line 1838 "src/fe/parser.cpp"
    break;

  case 20:
#line 125 "src/fe/parser.ypp"
                                                                                        { (yyval.sym) = sym_module; }
#line 1844 "src/fe/parser.cpp"
    break;

  case 21:
#line 127 "src/fe/parser.ypp"
                        {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, nullptr);
}
#line 1852 "src/fe/parser.cpp"
    break;

  case 22:
#line 129 "src/fe/parser.ypp"
                     {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet(nullptr, (yyvsp[0].annotation_value));
}
#line 1860 "src/fe/parser.cpp"
    break;

  case 23:
#line 131 "src/fe/parser.ypp"
                                               {
  (yyval.annotation_value_set) = AnnotationBuilder::BuildParamSet((yyvsp[-2].annotation_value_set), (yyvsp[0].annotation_value));
}
#line 1868 "src/fe/parser.cpp"
    break;

  case 24:
#line 135 "src/fe/parser.ypp"
                      {
  (yyval.annotation) = Emitter::SetCurrentAnnotation(sym_null, nullptr);
}
#line 1876 "src/fe/parser.cpp"
    break;

  case 25:
#line 137 "src/fe/parser.ypp"
                                                   {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[-3].sym), (yyvsp[-1].annotation_value_set));
}
#line 1884 "src/fe/parser.cpp"
    break;

  case 26:
#line 139 "src/fe/parser.ypp"
            {
  (yyval.annotation) = Emitter::SetCurrentAnnotation((yyvsp[0].sym), nullptr);
}
#line 1892 "src/fe/parser.cpp"
    break;

  case 27:
#line 143 "src/fe/parser.ypp"
               {
  (yyval.sym) = sym_lookup("");
}
#line 1900 "src/fe/parser.cpp"
    break;

  case 28:
#line 145 "src/fe/parser.ypp"
        {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 1908 "src/fe/parser.cpp"
    break;

  case 29:
#line 149 "src/fe/parser.ypp"
                         {
  (yyval.var_decl) = Builder::ReturnType((yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 1916 "src/fe/parser.cpp"
    break;

  case 30:
#line 153 "src/fe/parser.ypp"
                               {
 (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, (yyvsp[0].var_decl));
}
#line 1924 "src/fe/parser.cpp"
    break;

  case 31:
#line 155 "src/fe/parser.ypp"
                                     {
 (yyval.var_decl_set) = Builder::ReturnDeclList((yyvsp[-2].var_decl_set), (yyvsp[0].var_decl));
}
#line 1932 "src/fe/parser.cpp"
    break;

  case 32:
#line 159 "src/fe/parser.ypp"
              {
  (yyval.var_decl_set) = Builder::ReturnDeclList(nullptr, nullptr);
}
#line 1940 "src/fe/parser.cpp"
    break;

  case 33:
#line 161 "src/fe/parser.ypp"
                             {
  (yyval.var_decl_set) = (yyvsp[-1].var_decl_set);
}
#line 1948 "src/fe/parser.cpp"
    break;

  case 34:
#line 165 "src/fe/parser.ypp"
                                {Emitter::SetCurrentFunctionAnnotation((yyvsp[0].annotation));}
#line 1954 "src/fe/parser.cpp"
    break;

  case 35:
#line 165 "src/fe/parser.ypp"
                                                                                                              {
  Emitter::EndFunction();
}
#line 1962 "src/fe/parser.cpp"
    break;

  case 36:
#line 169 "src/fe/parser.ypp"
                                                         {
  Emitter::SetCurrentFunctionParams();
  Emitter::SetCurrentFunctionArgs((yyvsp[-2].var_decl_set));
  Emitter::SetCurrentFunctionReturns((yyvsp[0].var_decl_set));
}
#line 1972 "src/fe/parser.cpp"
    break;

  case 37:
#line 176 "src/fe/parser.ypp"
                     { (yyval.id) = K_DEF; }
#line 1978 "src/fe/parser.cpp"
    break;

  case 38:
#line 176 "src/fe/parser.ypp"
                                              { (yyval.id) = K_FUNC; }
#line 1984 "src/fe/parser.cpp"
    break;

  case 39:
#line 176 "src/fe/parser.ypp"
                                                                           { (yyval.id) = K_PROCESS; }
#line 1990 "src/fe/parser.cpp"
    break;

  case 40:
#line 176 "src/fe/parser.ypp"
                                                                                                          { (yyval.id) = K_ALWAYS; }
#line 1996 "src/fe/parser.cpp"
    break;

  case 41:
#line 178 "src/fe/parser.ypp"
                                      {
  bool process = ((yyvsp[-2].id) == K_PROCESS) || ((yyvsp[-2].id) == K_ALWAYS);
  Emitter::BeginFunction((yyvsp[-1].expr), process, ((yyvsp[-2].id) == K_ALWAYS));
}
#line 2005 "src/fe/parser.cpp"
    break;

  case 42:
#line 183 "src/fe/parser.ypp"
            {
}
#line 2012 "src/fe/parser.cpp"
    break;

  case 43:
#line 184 "src/fe/parser.ypp"
                   {
}
#line 2019 "src/fe/parser.cpp"
    break;

  case 44:
#line 187 "src/fe/parser.ypp"
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
#line 2035 "src/fe/parser.cpp"
    break;

  case 45:
#line 199 "src/fe/parser.ypp"
                      {(yyval.id) = K_VAR;}
#line 2041 "src/fe/parser.cpp"
    break;

  case 46:
#line 199 "src/fe/parser.ypp"
                                               {(yyval.id) = K_SHARED;}
#line 2047 "src/fe/parser.cpp"
    break;

  case 47:
#line 199 "src/fe/parser.ypp"
                                                                          {(yyval.id) = K_INPUT;}
#line 2053 "src/fe/parser.cpp"
    break;

  case 48:
#line 199 "src/fe/parser.ypp"
                                                                                                     {(yyval.id) = K_OUTPUT;}
#line 2059 "src/fe/parser.cpp"
    break;

  case 49:
#line 201 "src/fe/parser.ypp"
                               {ScannerInterface::InSemiColonStatement();}
#line 2065 "src/fe/parser.cpp"
    break;

  case 50:
#line 201 "src/fe/parser.ypp"
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
#line 2084 "src/fe/parser.cpp"
    break;

  case 51:
#line 214 "src/fe/parser.ypp"
                         {
}
#line 2091 "src/fe/parser.cpp"
    break;

  case 52:
#line 215 "src/fe/parser.ypp"
                  {
}
#line 2098 "src/fe/parser.cpp"
    break;

  case 53:
#line 218 "src/fe/parser.ypp"
                       {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), true);
}
#line 2106 "src/fe/parser.cpp"
    break;

  case 54:
#line 220 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Int(false, (yyvsp[0].num).value);
}
#line 2114 "src/fe/parser.cpp"
    break;

  case 55:
#line 222 "src/fe/parser.ypp"
            {
  (yyval.width_spec) = WidthSpec::Name((yyvsp[0].sym), false);
}
#line 2122 "src/fe/parser.cpp"
    break;

  case 56:
#line 226 "src/fe/parser.ypp"
           {
  /* no arguments */
  (yyval.var_decl_set) = nullptr;
}
#line 2131 "src/fe/parser.cpp"
    break;

  case 57:
#line 229 "src/fe/parser.ypp"
                  {
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2139 "src/fe/parser.cpp"
    break;

  case 58:
#line 233 "src/fe/parser.ypp"
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
#line 2155 "src/fe/parser.cpp"
    break;

  case 59:
#line 243 "src/fe/parser.ypp"
                                    {
  VarDeclSet *vds = (yyvsp[-2].var_decl_set);
  for (VarDecl *vd : (yyvsp[0].var_decl_set)->decls) {
    vds = Builder::ArgDeclList((yyvsp[-2].var_decl_set), vd);
  }
  (yyval.var_decl_set) = vds;
}
#line 2167 "src/fe/parser.cpp"
    break;

  case 60:
#line 251 "src/fe/parser.ypp"
                         {
  ArrayShape *shape = new ArrayShape((yyvsp[-1].num).value);
  (yyval.shape) = shape;
}
#line 2176 "src/fe/parser.cpp"
    break;

  case 61:
#line 254 "src/fe/parser.ypp"
                           {
  (yyvsp[0].shape)->length.push_back((yyvsp[-2].num).value);
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2185 "src/fe/parser.cpp"
    break;

  case 62:
#line 259 "src/fe/parser.ypp"
                      {
  (yyval.shape) = nullptr;
}
#line 2193 "src/fe/parser.cpp"
    break;

  case 63:
#line 261 "src/fe/parser.ypp"
               {
  (yyval.shape) = (yyvsp[0].shape);
}
#line 2201 "src/fe/parser.cpp"
    break;

  case 64:
#line 263 "src/fe/parser.ypp"
            {
  // length will be determined by the value initializer.
  ArrayShape *shape = new ArrayShape(0);
  (yyval.shape) = shape;
}
#line 2211 "src/fe/parser.cpp"
    break;

  case 65:
#line 269 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[0].num);
}
#line 2219 "src/fe/parser.cpp"
    break;

  case 66:
#line 273 "src/fe/parser.ypp"
                           {
  ArrayInitializer *array = new ArrayInitializer;
  array->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = array;
}
#line 2229 "src/fe/parser.cpp"
    break;

  case 67:
#line 277 "src/fe/parser.ypp"
                                 {
  (yyvsp[-2].array)->num_.push_back((yyvsp[0].num).value);
  (yyval.array) = (yyvsp[-2].array);
}
#line 2238 "src/fe/parser.cpp"
    break;

  case 68:
#line 282 "src/fe/parser.ypp"
                        { ScannerInterface::InArrayElmDecl(); }
#line 2244 "src/fe/parser.cpp"
    break;

  case 69:
#line 282 "src/fe/parser.ypp"
                                                                               {ScannerInterface::EndArrayElmDecl(); }
#line 2250 "src/fe/parser.cpp"
    break;

  case 70:
#line 282 "src/fe/parser.ypp"
                                                                                                                           {
  (yyval.array) = (yyvsp[-2].array);
}
#line 2258 "src/fe/parser.cpp"
    break;

  case 71:
#line 286 "src/fe/parser.ypp"
                         {
  ScannerInterface::InSemiColonStatement();
  (yyval.var_decl_set) = (yyvsp[0].var_decl_set);
}
#line 2267 "src/fe/parser.cpp"
    break;

  case 72:
#line 289 "src/fe/parser.ypp"
                           {
  ScannerInterface::InSemiColonStatement();
  if ((yyvsp[-2].var_decl_set)->decls.size() > 1) {
    yyerror("More than 1 LHS to initialize");
    YYABORT;
  }
  (yyvsp[-2].var_decl_set)->decls[0]->SetInitialVal((yyvsp[0].expr));
  (yyval.var_decl_set) = Builder::VarDeclList(nullptr, (yyvsp[-2].var_decl_set)->decls[0]);
}
#line 2281 "src/fe/parser.cpp"
    break;

  case 73:
#line 297 "src/fe/parser.ypp"
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
#line 2299 "src/fe/parser.cpp"
    break;

  case 74:
#line 311 "src/fe/parser.ypp"
                  {
  (yyval.sym) = sym_int;
}
#line 2307 "src/fe/parser.cpp"
    break;

  case 75:
#line 313 "src/fe/parser.ypp"
           {
  (yyval.sym) = sym_bool;
}
#line 2315 "src/fe/parser.cpp"
    break;

  case 76:
#line 315 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_object;
}
#line 2323 "src/fe/parser.cpp"
    break;

  case 77:
#line 317 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_module;
}
#line 2331 "src/fe/parser.cpp"
    break;

  case 78:
#line 319 "src/fe/parser.ypp"
             {
  (yyval.sym) = sym_string;
}
#line 2339 "src/fe/parser.cpp"
    break;

  case 79:
#line 324 "src/fe/parser.ypp"
                {
  Emitter::EmitLabel((yyvsp[-1].sym));
}
#line 2347 "src/fe/parser.cpp"
    break;

  case 80:
#line 328 "src/fe/parser.ypp"
                  {
  ScannerInterface::InSemiColonStatement();
}
#line 2355 "src/fe/parser.cpp"
    break;

  case 81:
#line 332 "src/fe/parser.ypp"
           {
  /* empty stmt */
}
#line 2363 "src/fe/parser.cpp"
    break;

  case 82:
#line 334 "src/fe/parser.ypp"
             {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2371 "src/fe/parser.cpp"
    break;

  case 83:
#line 336 "src/fe/parser.ypp"
                  {
}
#line 2378 "src/fe/parser.cpp"
    break;

  case 84:
#line 337 "src/fe/parser.ypp"
                          {
}
#line 2385 "src/fe/parser.cpp"
    break;

  case 85:
#line 338 "src/fe/parser.ypp"
                      {
  Emitter::EmitGoto((yyvsp[-1].sym));
}
#line 2393 "src/fe/parser.cpp"
    break;

  case 86:
#line 340 "src/fe/parser.ypp"
                    {
  Emitter::EmitReturnStmt((yyvsp[-1].expr));
}
#line 2401 "src/fe/parser.cpp"
    break;

  case 87:
#line 342 "src/fe/parser.ypp"
               {
  Emitter::EmitReturnStmt(nullptr);
}
#line 2409 "src/fe/parser.cpp"
    break;

  case 88:
#line 344 "src/fe/parser.ypp"
          {
}
#line 2416 "src/fe/parser.cpp"
    break;

  case 89:
#line 345 "src/fe/parser.ypp"
            {
}
#line 2423 "src/fe/parser.cpp"
    break;

  case 90:
#line 346 "src/fe/parser.ypp"
             {
}
#line 2430 "src/fe/parser.cpp"
    break;

  case 91:
#line 347 "src/fe/parser.ypp"
               {
}
#line 2437 "src/fe/parser.cpp"
    break;

  case 92:
#line 348 "src/fe/parser.ypp"
                  {
}
#line 2444 "src/fe/parser.cpp"
    break;

  case 93:
#line 349 "src/fe/parser.ypp"
                {
}
#line 2451 "src/fe/parser.cpp"
    break;

  case 94:
#line 350 "src/fe/parser.ypp"
                      {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2459 "src/fe/parser.cpp"
    break;

  case 97:
#line 354 "src/fe/parser.ypp"
                         {
}
#line 2466 "src/fe/parser.cpp"
    break;

  case 98:
#line 355 "src/fe/parser.ypp"
                          {
}
#line 2473 "src/fe/parser.cpp"
    break;

  case 99:
#line 356 "src/fe/parser.ypp"
                          {
}
#line 2480 "src/fe/parser.cpp"
    break;

  case 100:
#line 360 "src/fe/parser.ypp"
          {
  ScannerInterface::EndSemiColonStatement();
}
#line 2488 "src/fe/parser.cpp"
    break;

  case 101:
#line 364 "src/fe/parser.ypp"
                   {
  ScannerInterface::InSemiColonStatement();
}
#line 2496 "src/fe/parser.cpp"
    break;

  case 102:
#line 368 "src/fe/parser.ypp"
                       {ScannerInterface::InSemiColonStatement();}
#line 2502 "src/fe/parser.cpp"
    break;

  case 103:
#line 368 "src/fe/parser.ypp"
                                                                                                {
  Emitter::EmitImportStmt((yyvsp[-2].str), (yyvsp[-1].sym));
}
#line 2510 "src/fe/parser.cpp"
    break;

  case 104:
#line 372 "src/fe/parser.ypp"
                                {
  (yyval.sym) = (yyvsp[0].sym);
}
#line 2518 "src/fe/parser.cpp"
    break;

  case 105:
#line 374 "src/fe/parser.ypp"
    {
  (yyval.sym) = sym_null;
}
#line 2526 "src/fe/parser.cpp"
    break;

  case 106:
#line 378 "src/fe/parser.ypp"
                            {ScannerInterface::InSemiColonStatement();}
#line 2532 "src/fe/parser.cpp"
    break;

  case 107:
#line 378 "src/fe/parser.ypp"
                                                                                             {
  Emitter::EmitThreadDeclStmt((yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 2540 "src/fe/parser.cpp"
    break;

  case 108:
#line 382 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2546 "src/fe/parser.cpp"
    break;

  case 109:
#line 382 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitChannelDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2554 "src/fe/parser.cpp"
    break;

  case 110:
#line 386 "src/fe/parser.ypp"
                                                  {ScannerInterface::InSemiColonStatement();}
#line 2560 "src/fe/parser.cpp"
    break;

  case 111:
#line 386 "src/fe/parser.ypp"
                                                                                                                             {
  Emitter::EmitMailboxDeclStmt((yyvsp[-2].expr), (yyvsp[0].width_spec).is_primitive, (yyvsp[0].width_spec).name, (yyvsp[0].width_spec).width);
}
#line 2568 "src/fe/parser.cpp"
    break;

  case 112:
#line 390 "src/fe/parser.ypp"
                  {
}
#line 2575 "src/fe/parser.cpp"
    break;

  case 113:
#line 391 "src/fe/parser.ypp"
             {
  // Maybe remove this syntax later.
}
#line 2583 "src/fe/parser.cpp"
    break;

  case 114:
#line 395 "src/fe/parser.ypp"
                         {
  (yyval.stmt) = Emitter::EmitIfStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2592 "src/fe/parser.cpp"
    break;

  case 115:
#line 400 "src/fe/parser.ypp"
                                         {
  (yyval.stmt) = (yyvsp[-2].stmt);
  Emitter::EmitGoto((yyvsp[-2].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-2].stmt)->GetLabel(false, false));
}
#line 2602 "src/fe/parser.cpp"
    break;

  case 116:
#line 406 "src/fe/parser.ypp"
                             {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2612 "src/fe/parser.cpp"
    break;

  case 117:
#line 410 "src/fe/parser.ypp"
                       {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2621 "src/fe/parser.cpp"
    break;

  case 118:
#line 413 "src/fe/parser.ypp"
                         {
  (yyval.block) = nullptr;
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(true, false));
}
#line 2630 "src/fe/parser.cpp"
    break;

  case 119:
#line 418 "src/fe/parser.ypp"
                                     {
  Emitter::BeginBlock((yyvsp[-1].annotation));
}
#line 2638 "src/fe/parser.cpp"
    break;

  case 120:
#line 422 "src/fe/parser.ypp"
                                  {
  Emitter::EmitExprStmt((yyvsp[-1].expr));
}
#line 2646 "src/fe/parser.cpp"
    break;

  case 121:
#line 424 "src/fe/parser.ypp"
                               {
  Emitter::EmitVarDeclStmtSet((yyvsp[-1].var_decl_set));
}
#line 2654 "src/fe/parser.cpp"
    break;

  case 122:
#line 428 "src/fe/parser.ypp"
                                   {
  (yyval.stmt) = Emitter::EmitForStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2663 "src/fe/parser.cpp"
    break;

  case 123:
#line 433 "src/fe/parser.ypp"
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
#line 2682 "src/fe/parser.cpp"
    break;

  case 124:
#line 448 "src/fe/parser.ypp"
                               {
  Emitter::BeginBlock(nullptr);
  // Emit a dummy insn before label_join so that compiler can
  // find a insn after the label.
  Emitter::EmitNop();
  (yyval.stmt) = Emitter::EmitWhileStmt((yyvsp[0].expr));
  Emitter::EmitLabel((yyval.stmt)->GetLabel(false, true));
}
#line 2695 "src/fe/parser.cpp"
    break;

  case 125:
#line 457 "src/fe/parser.ypp"
                                   {
  Emitter::EmitGoto((yyvsp[-1].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-1].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2705 "src/fe/parser.cpp"
    break;

  case 126:
#line 463 "src/fe/parser.ypp"
                     {
  Emitter::BeginBlock(nullptr);
  Emitter::EmitNop();
  (yyval.stmt) = Builder::DoWhileStmt();
  Emitter::EmitLabel((yyval.stmt)->GetLabel(true, false));
}
#line 2716 "src/fe/parser.cpp"
    break;

  case 127:
#line 470 "src/fe/parser.ypp"
                                    {
  (yyval.stmt) = (yyvsp[-1].stmt);
}
#line 2724 "src/fe/parser.cpp"
    break;

  case 128:
#line 474 "src/fe/parser.ypp"
                                                   {
  Emitter::EmitDoWhileStmt((yyvsp[-4].stmt), (yyvsp[-1].expr));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, true));
  Emitter::EmitGoto((yyvsp[-4].stmt)->GetLabel(true, false));
  Emitter::EmitLabel((yyvsp[-4].stmt)->GetLabel(false, false));
  Emitter::EndBlock();
}
#line 2736 "src/fe/parser.cpp"
    break;

  case 129:
#line 482 "src/fe/parser.ypp"
                                               {
}
#line 2743 "src/fe/parser.cpp"
    break;

  case 130:
#line 485 "src/fe/parser.ypp"
                  {
}
#line 2750 "src/fe/parser.cpp"
    break;

  case 131:
#line 486 "src/fe/parser.ypp"
                    {
}
#line 2757 "src/fe/parser.cpp"
    break;

  case 132:
#line 489 "src/fe/parser.ypp"
                 {
}
#line 2764 "src/fe/parser.cpp"
    break;

  case 133:
#line 492 "src/fe/parser.ypp"
                                 {
  Emitter::EndBlock();
}
#line 2772 "src/fe/parser.cpp"
    break;

  case 134:
#line 496 "src/fe/parser.ypp"
                 {
  /* open new bindings */
  Emitter::BeginBlock(nullptr);
}
#line 2781 "src/fe/parser.cpp"
    break;

  case 135:
#line 501 "src/fe/parser.ypp"
                                              {
  Emitter::EmitEnumTypeDeclStmt((yyvsp[-3].expr), (yyvsp[-1].enum_decl));
}
#line 2789 "src/fe/parser.cpp"
    break;

  case 136:
#line 505 "src/fe/parser.ypp"
                     {
  (yyval.enum_decl) = Builder::EnumItemList(nullptr, (yyvsp[0].sym));
}
#line 2797 "src/fe/parser.cpp"
    break;

  case 137:
#line 507 "src/fe/parser.ypp"
                           {
  (yyval.enum_decl) = Builder::EnumItemList((yyvsp[-2].enum_decl), (yyvsp[0].sym));
}
#line 2805 "src/fe/parser.cpp"
    break;

  case 138:
#line 511 "src/fe/parser.ypp"
           {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 2814 "src/fe/parser.cpp"
    break;

  case 139:
#line 514 "src/fe/parser.ypp"
                {
  ScannerInterface::InSemiColonStatement();
  Expr *num = Builder::NumExpr((yyvsp[0].num));
  if (num == nullptr) {
    YYABORT;
  }
  (yyval.expr) = Builder::ArrayRefExpr(Builder::SymExpr((yyvsp[-2].sym)), num);
}
#line 2827 "src/fe/parser.cpp"
    break;

  case 140:
#line 521 "src/fe/parser.ypp"
                 {
  (yyval.expr) = (yyvsp[-1].expr);
}
#line 2835 "src/fe/parser.cpp"
    break;

  case 141:
#line 523 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::ArrayRefExpr((yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2843 "src/fe/parser.cpp"
    break;

  case 142:
#line 525 "src/fe/parser.ypp"
                               {
  (yyval.expr) = Builder::BitRangeRefExpr((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
}
#line 2851 "src/fe/parser.cpp"
    break;

  case 143:
#line 527 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_COMMA);
}
#line 2859 "src/fe/parser.cpp"
    break;

  case 144:
#line 529 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_ELM_REF);
}
#line 2867 "src/fe/parser.cpp"
    break;

  case 145:
#line 531 "src/fe/parser.ypp"
            {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 2875 "src/fe/parser.cpp"
    break;

  case 146:
#line 533 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::LogicInvertExpr((yyvsp[0].expr));
}
#line 2883 "src/fe/parser.cpp"
    break;

  case 147:
#line 535 "src/fe/parser.ypp"
             {
  (yyval.expr) = Builder::BitInvertExpr((yyvsp[0].expr));
}
#line 2891 "src/fe/parser.cpp"
    break;

  case 148:
#line 537 "src/fe/parser.ypp"
                        {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2899 "src/fe/parser.cpp"
    break;

  case 149:
#line 539 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_MUL);
}
#line 2907 "src/fe/parser.cpp"
    break;

  case 150:
#line 541 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_DIV);
}
#line 2915 "src/fe/parser.cpp"
    break;

  case 151:
#line 543 "src/fe/parser.ypp"
                      {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2923 "src/fe/parser.cpp"
    break;

  case 152:
#line 545 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2931 "src/fe/parser.cpp"
    break;

  case 153:
#line 547 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2939 "src/fe/parser.cpp"
    break;

  case 154:
#line 549 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].sub_op));
}
#line 2947 "src/fe/parser.cpp"
    break;

  case 155:
#line 551 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_CONCAT);
}
#line 2955 "src/fe/parser.cpp"
    break;

  case 156:
#line 553 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_AND);
}
#line 2963 "src/fe/parser.cpp"
    break;

  case 157:
#line 555 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_OR);
}
#line 2971 "src/fe/parser.cpp"
    break;

  case 158:
#line 557 "src/fe/parser.ypp"
                  {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_XOR);
}
#line 2979 "src/fe/parser.cpp"
    break;

  case 159:
#line 559 "src/fe/parser.ypp"
                         {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LOR);
}
#line 2987 "src/fe/parser.cpp"
    break;

  case 160:
#line 561 "src/fe/parser.ypp"
                          {
  (yyval.expr) = Builder::BinopExpr((yyvsp[-2].expr), (yyvsp[0].expr), BINOP_LAND);
}
#line 2995 "src/fe/parser.cpp"
    break;

  case 161:
#line 563 "src/fe/parser.ypp"
                   {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[-1].expr), (yyvsp[0].sub_op), true);
}
#line 3003 "src/fe/parser.cpp"
    break;

  case 162:
#line 565 "src/fe/parser.ypp"
              {ScannerInterface::InSemiColonStatement();}
#line 3009 "src/fe/parser.cpp"
    break;

  case 163:
#line 565 "src/fe/parser.ypp"
                                                                {
  (yyval.expr) = Builder::IncDecExpr((yyvsp[0].expr), (yyvsp[-2].sub_op), false);
}
#line 3017 "src/fe/parser.cpp"
    break;

  case 164:
#line 567 "src/fe/parser.ypp"
                              {
  (yyval.expr) = Builder::SignedExpr((yyvsp[-1].sub_op), (yyvsp[0].expr));
}
#line 3025 "src/fe/parser.cpp"
    break;

  case 165:
#line 569 "src/fe/parser.ypp"
                           {
  (yyval.expr) = Builder::TriTerm((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
}
#line 3033 "src/fe/parser.cpp"
    break;

  case 166:
#line 571 "src/fe/parser.ypp"
        {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::StrExpr((yyvsp[0].str));
}
#line 3042 "src/fe/parser.cpp"
    break;

  case 167:
#line 574 "src/fe/parser.ypp"
             {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::NumExpr((yyvsp[0].num));
  if ((yyval.expr) == nullptr) {
    YYABORT;
  }
}
#line 3054 "src/fe/parser.cpp"
    break;

  case 168:
#line 582 "src/fe/parser.ypp"
               {
  (yyval.num) = (yyvsp[0].num);
}
#line 3062 "src/fe/parser.cpp"
    break;

  case 169:
#line 584 "src/fe/parser.ypp"
                {
  (yyval.num) = (yyvsp[-2].num);
  (yyval.num).width = (yyvsp[0].num).value;
}
#line 3071 "src/fe/parser.cpp"
    break;

  case 170:
#line 589 "src/fe/parser.ypp"
          {
  (yyval.expr) = Builder::SymExpr((yyvsp[0].sym));
}
#line 3079 "src/fe/parser.cpp"
    break;

  case 171:
#line 591 "src/fe/parser.ypp"
                {
  (yyval.expr) = Builder::ElmSymRefExpr((yyvsp[-2].expr), (yyvsp[0].sym));
}
#line 3087 "src/fe/parser.cpp"
    break;

  case 172:
#line 595 "src/fe/parser.ypp"
               {
  (yyval.expr_set) = Builder::ExprList(nullptr, (yyvsp[0].expr));
}
#line 3095 "src/fe/parser.cpp"
    break;

  case 173:
#line 597 "src/fe/parser.ypp"
                     {
  (yyval.expr_set) = Builder::ExprList((yyvsp[-2].expr_set), (yyvsp[0].expr));
}
#line 3103 "src/fe/parser.cpp"
    break;

  case 174:
#line 601 "src/fe/parser.ypp"
                       {
  (yyval.expr) = Builder::SymExpr((yyvsp[-1].sym));
}
#line 3111 "src/fe/parser.cpp"
    break;

  case 175:
#line 605 "src/fe/parser.ypp"
                                     {
  ScannerInterface::InSemiColonStatement();
  (yyval.expr) = Builder::FuncallExpr((yyvsp[-2].expr), (yyvsp[-1].expr));
}
#line 3120 "src/fe/parser.cpp"
    break;

  case 176:
#line 610 "src/fe/parser.ypp"
           {
  (yyval.expr) = nullptr;
}
#line 3128 "src/fe/parser.cpp"
    break;

  case 177:
#line 612 "src/fe/parser.ypp"
         {
  (yyval.expr) = (yyvsp[0].expr);
}
#line 3136 "src/fe/parser.cpp"
    break;


#line 3140 "src/fe/parser.cpp"

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
#line 616 "src/fe/parser.ypp"

