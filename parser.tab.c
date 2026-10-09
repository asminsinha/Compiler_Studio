/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

/* =========================================================
   NODE STRUCTURE FOR BACKPATCH LISTS
   ========================================================= */

typedef struct Node Node;

struct Node {
    int quad_index;
    Node *next;
};


/* =========================================================
   QUADRUPLE / THREE-ADDRESS CODE STRUCTURE
   ========================================================= */

typedef struct {
    char op[10];
    char arg1[32];
    char arg2[32];
    char result[32];
} Quad;


/* =========================================================
   GLOBAL CODE GENERATION TABLE
   ========================================================= */

Quad quad_table[500];

int quad_count = 0;
int temp_var_count = 0;

typedef struct {
    int from_quad;
    int target_quad;
} BackpatchLog;

BackpatchLog bp_logs[200];
int bp_log_count = 0;

/* =========================================================
   HELPER FUNCTION DECLARATIONS
   ========================================================= */

int nextquad();

void emit(
    const char *op,
    const char *arg1,
    const char *arg2,
    const char *result
);

char* newtemp();

Node* makelist(int index);

Node* merge(Node *l1, Node *l2);

void backpatch(Node *list, int target_quad);

void print_tac();

void print_quads();

void execute_tac();



#line 150 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_FOR = 7,                        /* FOR  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_PRINT = 10,                     /* PRINT  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NE = 14,                        /* NE  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_ASSIGN = 17,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 18,                      /* PLUS  */
  YYSYMBOL_MINUS = 19,                     /* MINUS  */
  YYSYMBOL_MULT = 20,                      /* MULT  */
  YYSYMBOL_DIV = 21,                       /* DIV  */
  YYSYMBOL_SEMI = 22,                      /* SEMI  */
  YYSYMBOL_LPAREN = 23,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 24,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 25,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 26,                    /* RBRACE  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_PROG = 28,                      /* PROG  */
  YYSYMBOL_S_LIST = 29,                    /* S_LIST  */
  YYSYMBOL_M = 30,                         /* M  */
  YYSYMBOL_N = 31,                         /* N  */
  YYSYMBOL_FOR_INIT = 32,                  /* FOR_INIT  */
  YYSYMBOL_FOR_STEP = 33,                  /* FOR_STEP  */
  YYSYMBOL_S = 34,                         /* S  */
  YYSYMBOL_35_1 = 35,                      /* $@1  */
  YYSYMBOL_C = 36,                         /* C  */
  YYSYMBOL_E = 37                          /* E  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  31
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  96

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   147,   147,   168,   179,   192,   211,   229,   241,   253,
     261,   268,   279,   296,   329,   354,   353,   406,   435,   442,
     466,   490,   514,   538,   562,   592,   598,   613,   628,   643,
     658,   664
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM",
  "STRING_LITERAL", "WHILE", "FOR", "IF", "ELSE", "PRINT", "LE", "GE",
  "EQ", "NE", "LT", "GT", "ASSIGN", "PLUS", "MINUS", "MULT", "DIV", "SEMI",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "$accept", "PROG", "S_LIST", "M",
  "N", "FOR_INIT", "FOR_STEP", "S", "$@1", "C", "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-17)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       9,   -15,   -13,   -12,    -9,     8,     9,    25,    46,   -17,
       1,   -17,     5,    32,    45,    30,   -17,     9,   -17,   -17,
       1,    51,    32,    57,    36,    32,    39,    89,    54,    33,
     -17,   -17,    41,     1,     1,     1,     1,   -17,    55,     1,
     -17,    56,    75,   -17,     1,     1,     1,     1,     1,     1,
      59,    60,   -17,    24,    24,   -17,   -17,   -17,     2,    32,
     -17,    58,     2,     2,     2,     2,     2,     2,   -17,   -17,
      67,    76,     9,     9,   -17,    71,    80,   108,   103,   -17,
      96,   -17,   -17,     1,    90,   -17,     2,   -17,    91,    92,
       9,     9,    93,    94,   -17,   -17
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     5,     4,
       0,     5,     0,     0,     0,     5,     1,     0,    30,    31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     3,     0,     0,     0,     0,     0,     9,     0,     0,
       5,     0,     0,     5,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    26,    27,    28,    29,     5,     7,     0,
      18,     0,    21,    22,    23,    24,    19,    20,    11,    10,
       0,     0,     0,     0,     5,     5,     5,     0,    12,    14,
       0,    15,     6,     0,     0,     5,     8,     5,     0,     0,
       0,     0,     5,     5,    13,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -17,   -17,    -6,   -10,   -17,   -17,   -17,    98,   -17,   -16,
      -7
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,    17,    85,    24,    81,     9,    84,    26,
      27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,    22,    10,    21,    18,    19,    38,    29,    23,    41,
      11,    12,     1,    32,    13,     2,     3,     4,    42,     5,
      33,    34,    35,    36,    20,    16,    53,    54,    55,    56,
      59,    14,    58,    61,     6,    18,    19,    62,    63,    64,
      65,    66,    67,    71,    35,    36,    -2,    70,    18,    19,
      28,    33,    34,    35,    36,    25,    30,    51,    40,    33,
      34,    35,    36,    43,    77,    52,    75,    76,    20,    33,
      34,    35,    36,    37,    39,    88,    86,    89,    50,    57,
      60,    68,    69,    72,    92,    93,    44,    45,    46,    47,
      48,    49,    73,    33,    34,    35,    36,    78,    74,    52,
      44,    45,    46,    47,    48,    49,    79,    33,    34,    35,
      36,    80,    82,    83,    87,    31,    90,    91,     0,    94,
      95
};

static const yytype_int8 yycheck[] =
{
       6,    11,    17,    10,     3,     4,    22,    14,     3,    25,
      23,    23,     3,    20,    23,     6,     7,     8,    25,    10,
      18,    19,    20,    21,    23,     0,    33,    34,    35,    36,
      40,    23,    39,    43,    25,     3,     4,    44,    45,    46,
      47,    48,    49,    59,    20,    21,     0,    57,     3,     4,
       5,    18,    19,    20,    21,    23,    26,    24,    22,    18,
      19,    20,    21,    24,    74,    24,    72,    73,    23,    18,
      19,    20,    21,    22,    17,    85,    83,    87,    24,    24,
      24,    22,    22,    25,    90,    91,    11,    12,    13,    14,
      15,    16,    25,    18,    19,    20,    21,    26,    22,    24,
      11,    12,    13,    14,    15,    16,    26,    18,    19,    20,
      21,     3,     9,    17,    24,    17,    25,    25,    -1,    26,
      26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     6,     7,     8,    10,    25,    28,    29,    34,
      17,    23,    23,    23,    23,    29,     0,    30,     3,     4,
      23,    37,    30,     3,    32,    23,    36,    37,     5,    37,
      26,    34,    37,    18,    19,    20,    21,    22,    36,    17,
      22,    36,    37,    24,    11,    12,    13,    14,    15,    16,
      24,    24,    24,    37,    37,    37,    37,    24,    37,    30,
      24,    30,    37,    37,    37,    37,    37,    37,    22,    22,
      30,    36,    25,    25,    22,    29,    29,    30,    26,    26,
       3,    33,     9,    17,    35,    31,    37,    24,    30,    30,
      25,    25,    29,    29,    26,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    29,    30,    31,    32,    33,    34,
      34,    34,    34,    34,    34,    35,    34,    34,    36,    36,
      36,    36,    36,    36,    36,    37,    37,    37,    37,    37,
      37,    37
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     0,     0,     3,     3,     4,
       5,     5,     8,    14,     9,     0,    15,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* PROG: S_LIST  */
#line 148 "parser.y"
      {
          /*
           * Any unresolved nextlist at the end of the
           * program is patched to the first quad after
           * the program.
           */
          backpatch((yyvsp[0].stmt).nextlist, quad_count);

          printf(
              "\n--- GENERATING INTERMEDIATE CODE ---\n"
          );
      }
#line 1239 "parser.tab.c"
    break;

  case 3: /* S_LIST: S_LIST M S  */
#line 169 "parser.y"
      {
          /*
           * The previous statement's unresolved jumps
           * continue at the beginning of the current statement.
           */
          backpatch((yyvsp[-2].stmt).nextlist, (yyvsp[-1].quad_num));

          (yyval.stmt).nextlist = (yyvsp[0].stmt).nextlist;
      }
#line 1253 "parser.tab.c"
    break;

  case 4: /* S_LIST: S  */
#line 180 "parser.y"
      {
          (yyval.stmt).nextlist = (yyvsp[0].stmt).nextlist;
      }
#line 1261 "parser.tab.c"
    break;

  case 5: /* M: %empty  */
#line 192 "parser.y"
      {
          /*
           * M records the current quad number.
           *
           * This is the key mechanism used to remember
           * control-flow destinations during translation.
           */
          (yyval.quad_num) = nextquad();
      }
#line 1275 "parser.tab.c"
    break;

  case 6: /* N: %empty  */
#line 211 "parser.y"
      {
          /*
           * Create a list containing the current quad.
           * The actual target will be determined later
           * through backpatching.
           */
          (yyval.stmt).nextlist = makelist(nextquad());

          emit("goto", "", "", "_");
      }
#line 1290 "parser.tab.c"
    break;

  case 7: /* FOR_INIT: ID ASSIGN E  */
#line 230 "parser.y"
      {
          emit("=", (yyvsp[0].str), "", (yyvsp[-2].str));
      }
#line 1298 "parser.tab.c"
    break;

  case 8: /* FOR_STEP: ID ASSIGN E  */
#line 242 "parser.y"
      {
          emit("=", (yyvsp[0].str), "", (yyvsp[-2].str));
      }
#line 1306 "parser.tab.c"
    break;

  case 9: /* S: ID ASSIGN E SEMI  */
#line 254 "parser.y"
      {
          emit("=", (yyvsp[-1].str), "", (yyvsp[-3].str));

          (yyval.stmt).nextlist = NULL;
      }
#line 1316 "parser.tab.c"
    break;

  case 10: /* S: PRINT LPAREN E RPAREN SEMI  */
#line 262 "parser.y"
      {
          emit("print", (yyvsp[-2].str), "", "");

          (yyval.stmt).nextlist = NULL;
      }
#line 1326 "parser.tab.c"
    break;

  case 11: /* S: PRINT LPAREN STRING_LITERAL RPAREN SEMI  */
#line 269 "parser.y"
      {
          emit("print_str", (yyvsp[-2].str), "", "");
          (yyval.stmt).nextlist = NULL;
      }
#line 1335 "parser.tab.c"
    break;

  case 12: /* S: IF LPAREN C RPAREN M LBRACE S_LIST RBRACE  */
#line 280 "parser.y"
      {
          /*
           * TRUE  -> beginning of IF body
           * FALSE -> statement following the IF
           */
          backpatch((yyvsp[-5].expr).truelist, (yyvsp[-3].quad_num));

          (yyval.stmt).nextlist =
              merge((yyvsp[-5].expr).falselist, (yyvsp[-1].stmt).nextlist);
      }
#line 1350 "parser.tab.c"
    break;

  case 13: /* S: IF LPAREN C RPAREN M LBRACE S_LIST RBRACE ELSE N M LBRACE S_LIST RBRACE  */
#line 298 "parser.y"
      {
          /*
           * TRUE condition -> IF body
           */
          backpatch((yyvsp[-11].expr).truelist, (yyvsp[-9].quad_num));

          /*
           * FALSE condition -> ELSE body
           */
          backpatch((yyvsp[-11].expr).falselist, (yyvsp[-3].quad_num));

          /*
           * Combine:
           *
           * 1. Jumps leaving the IF body
           * 2. Jumps created by N that skip ELSE
           */
          Node *temp =
              merge((yyvsp[-7].stmt).nextlist, (yyvsp[-4].stmt).nextlist);

          /*
           * Then combine those with the ELSE body's
           * unresolved nextlist.
           */
          (yyval.stmt).nextlist =
              merge(temp, (yyvsp[-1].stmt).nextlist);
      }
#line 1382 "parser.tab.c"
    break;

  case 14: /* S: WHILE LPAREN M C RPAREN M LBRACE S_LIST RBRACE  */
#line 330 "parser.y"
      {          
          backpatch((yyvsp[-5].expr).truelist, (yyvsp[-3].quad_num));
          char loop_target[16];

          sprintf(loop_target, "%d", (yyvsp[-6].quad_num));

          emit("goto", "", "", loop_target);

          /*
           * Any unresolved jump inside the loop body
           * continues to the condition.
           */
          backpatch((yyvsp[-1].stmt).nextlist, (yyvsp[-6].quad_num));

          /*
           * FALSE exits the loop.
           */
          (yyval.stmt).nextlist = (yyvsp[-5].expr).falselist;
      }
#line 1406 "parser.tab.c"
    break;

  case 15: /* $@1: %empty  */
#line 354 "parser.y"
      {
          

          char cond_target[16];

          sprintf(cond_target, "%d", (yyvsp[-4].quad_num));

          emit(
              "goto",
              "",
              "",
              cond_target
          );
      }
#line 1425 "parser.tab.c"
    break;

  case 16: /* S: FOR LPAREN FOR_INIT SEMI M C SEMI M FOR_STEP $@1 RPAREN M LBRACE S_LIST RBRACE  */
#line 369 "parser.y"
      {
          

          backpatch(
              (yyvsp[-9].expr).truelist,
              (yyvsp[-3].quad_num)
          );

          
          backpatch(
              (yyvsp[-1].stmt).nextlist,
              (yyvsp[-7].quad_num)
          );

          
          char step_target[16];

          sprintf(
              step_target,
              "%d",
              (yyvsp[-7].quad_num)
          );
          emit(
              "goto",
              "",
              "",
              step_target
          );
          
          (yyval.stmt).nextlist =
              (yyvsp[-9].expr).falselist;
      }
#line 1462 "parser.tab.c"
    break;

  case 17: /* S: LBRACE S_LIST RBRACE  */
#line 407 "parser.y"
      {
          (yyval.stmt).nextlist = (yyvsp[-1].stmt).nextlist;
      }
#line 1470 "parser.tab.c"
    break;

  case 18: /* C: LPAREN C RPAREN  */
#line 436 "parser.y"
    {
        /* Pass the truth and falsity lists up directly */
        (yyval.expr).truelist = (yyvsp[-1].expr).truelist;
        (yyval.expr).falselist = (yyvsp[-1].expr).falselist;
    }
#line 1480 "parser.tab.c"
    break;

  case 19: /* C: E LT E  */
#line 443 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              "<",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1506 "parser.tab.c"
    break;

  case 20: /* C: E GT E  */
#line 467 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              ">",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1532 "parser.tab.c"
    break;

  case 21: /* C: E LE E  */
#line 491 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              "<=",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1558 "parser.tab.c"
    break;

  case 22: /* C: E GE E  */
#line 515 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              ">=",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1584 "parser.tab.c"
    break;

  case 23: /* C: E EQ E  */
#line 539 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              "==",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1610 "parser.tab.c"
    break;

  case 24: /* C: E NE E  */
#line 563 "parser.y"
      {
          (yyval.expr).truelist =
              makelist(nextquad());

          (yyval.expr).falselist =
              makelist(nextquad() + 1);

          emit(
              "!=",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              "_"
          );

          emit(
              "goto",
              "",
              "",
              "_"
          );
      }
#line 1636 "parser.tab.c"
    break;

  case 25: /* E: LPAREN E RPAREN  */
#line 593 "parser.y"
    {
        /* Simply pass up the expression attributes */
        (yyval.str) = (yyvsp[-1].str);
    }
#line 1645 "parser.tab.c"
    break;

  case 26: /* E: E PLUS E  */
#line 599 "parser.y"
      {
          char *temp = newtemp();

          emit(
              "+",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              temp
          );

          (yyval.str) = temp;
      }
#line 1662 "parser.tab.c"
    break;

  case 27: /* E: E MINUS E  */
#line 614 "parser.y"
      {
          char *temp = newtemp();

          emit(
              "-",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              temp
          );

          (yyval.str) = temp;
      }
#line 1679 "parser.tab.c"
    break;

  case 28: /* E: E MULT E  */
#line 629 "parser.y"
      {
          char *temp = newtemp();

          emit(
              "*",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              temp
          );

          (yyval.str) = temp;
      }
#line 1696 "parser.tab.c"
    break;

  case 29: /* E: E DIV E  */
#line 644 "parser.y"
      {
          char *temp = newtemp();

          emit(
              "/",
              (yyvsp[-2].str),
              (yyvsp[0].str),
              temp
          );

          (yyval.str) = temp;
      }
#line 1713 "parser.tab.c"
    break;

  case 30: /* E: ID  */
#line 659 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1721 "parser.tab.c"
    break;

  case 31: /* E: NUM  */
#line 665 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1729 "parser.tab.c"
    break;


#line 1733 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 671 "parser.y"



/* =========================================================
   NEXT QUAD
   ========================================================= */

int nextquad() {
    return quad_count;
}


/* =========================================================
   EMIT
   ========================================================= */

void emit(
    const char *op,
    const char *arg1,
    const char *arg2,
    const char *result
) {
    if (quad_count >= 500) {
        fprintf(
            stderr,
            "ERROR: Quadruple table overflow.\n"
        );

        exit(EXIT_FAILURE);
    }

    strcpy(
        quad_table[quad_count].op,
        op
    );

    strcpy(
        quad_table[quad_count].arg1,
        arg1
    );

    strcpy(
        quad_table[quad_count].arg2,
        arg2
    );

    strcpy(
        quad_table[quad_count].result,
        result
    );

    quad_count++;
}


/* =========================================================
   TEMPORARY VARIABLE GENERATION
   ========================================================= */

char* newtemp() {

    char *temp =
        (char*)malloc(16);

    if (temp == NULL) {
        fprintf(
            stderr,
            "ERROR: Memory allocation failed.\n"
        );

        exit(EXIT_FAILURE);
    }

    sprintf(
        temp,
        "t%d",
        temp_var_count++
    );

    return temp;
}


/* =========================================================
   CREATE BACKPATCH LIST
   ========================================================= */

Node* makelist(int index) {

    Node *node =
        (Node*)malloc(sizeof(Node));

    if (node == NULL) {
        fprintf(
            stderr,
            "ERROR: Memory allocation failed.\n"
        );

        exit(EXIT_FAILURE);
    }

    node->quad_index = index;

    node->next = NULL;

    return node;
}


/* =========================================================
   MERGE BACKPATCH LISTS
   ========================================================= */

Node* merge(Node *l1, Node *l2) {

    if (!l1)
        return l2;

    if (!l2)
        return l1;

    Node *curr = l1;

    while (curr->next)
        curr = curr->next;

    curr->next = l2;

    return l1;
}


/* =========================================================
   BACKPATCH
   =========================================================

   Instead of storing:

       "goto 19"

   inside a conditional quadruple,

   we store only:

       "19"

   The TAC printer later converts this into:

       goto L19

   This keeps the internal representation clean.
   ========================================================= */

void backpatch(
    Node *list,
    int target_quad
) {

    Node *curr = list;

    while (curr) {

        char target_str[16];

        sprintf(
            target_str,
            "%d",
            target_quad
        );

        /*
         * Display the actual backpatching operation.
         * This is useful for Review 1 / viva.
         */
        if (bp_log_count < 200) {
            bp_logs[bp_log_count].from_quad = curr->quad_index;
            bp_logs[bp_log_count].target_quad = target_quad;
            bp_log_count++;
        }

        strcpy(
            quad_table[curr->quad_index].result,
            target_str
        );

        curr = curr->next;
    }
}
/* =========================================================
   PRINT BACKPATCH LOGS
   ========================================================= */

void print_backpatch_logs() {
    printf(
        "\n--- BACKPATCHING OPERATIONS ---\n"
    );

    if (bp_log_count == 0) {
        printf("No backpatching operations recorded.\n");
        return;
    }

    for (int i = 0; i < bp_log_count; i++) {
        printf(
            "BACKPATCH: Quad %d -> Quad %d\n",
            bp_logs[i].from_quad,
            bp_logs[i].target_quad
        );
    }
}

/* =========================================================
   HUMAN-READABLE THREE-ADDRESS CODE
   ========================================================= */

void print_tac() {

    printf(
        "\n--- THREE-ADDRESS CODE (TAC) ---\n"
    );

    printf(
        "----------------------------------------\n"
    );

    for (int i = 0; i < quad_count; i++) {

        Quad *q =
            &quad_table[i];

        /*
         * Label for every instruction.
         *
         * This makes control-flow translation easy
         * to demonstrate during the review.
         */
        printf(
            "L%d:\n",
            i
        );


        /* Assignment */

        if (strcmp(q->op, "=") == 0) {

            printf(
                "    %s = %s\n",
                q->result,
                q->arg1
            );
        }


        /* Print */

        else if (
            strcmp(q->op, "print") == 0
        ) {

            printf(
                "    print %s\n",
                q->arg1
            );
        }


        /* Unconditional jump */

        else if (
            strcmp(q->op, "goto") == 0
        ) {

            printf(
                "    goto L%s\n",
                q->result
            );
        }


        /* Conditional jump */

        else if (
            strcmp(q->op, "<") == 0 ||
            strcmp(q->op, ">") == 0 ||
            strcmp(q->op, "<=") == 0 ||
            strcmp(q->op, ">=") == 0 ||
            strcmp(q->op, "==") == 0 ||
            strcmp(q->op, "!=") == 0
        ) {

            printf(
                "    if %s %s %s goto L%s\n",
                q->arg1,
                q->op,
                q->arg2,
                q->result
            );
        }


        /* Arithmetic */

        else {

            printf(
                "    %s = %s %s %s\n",
                q->result,
                q->arg1,
                q->op,
                q->arg2
            );
        }
    }


    /*
     * If a conditional jump exits the program,
     * quad_count itself is a valid destination.
     */
    printf(
        "L%d:\n",
        quad_count
    );
}


/* =========================================================
   QUADRUPLE TABLE
   ========================================================= */

void print_quads() {

    printf(
        "\n--- QUADRUPLE TABLE ---\n"
    );

    printf(
        "%-8s %-8s %-8s %-8s %-12s\n",
        "Quad #",
        "Op",
        "Arg1",
        "Arg2",
        "Result"
    );

    printf(
        "--------------------------------------------------\n"
    );

    for (int i = 0; i < quad_count; i++) {

        printf(
            "%-8d %-8s %-8s %-8s %-12s\n",
            i,
            quad_table[i].op,
            quad_table[i].arg1,
            quad_table[i].arg2,
            quad_table[i].result
        );
    }
}


/* =========================================================
   SIMPLE TAC EXECUTION SIMULATOR
   ========================================================= */

typedef struct {

    char name[32];

    int val;

} Variable;


Variable symbol_table[100];

int sym_count = 0;


/* =========================================================
   GET VARIABLE VALUE
   ========================================================= */

int get_var(
    const char *name
) {

    /*
     * Numeric constant
     */
    if (
        (name[0] >= '0' && name[0] <= '9') ||
        (
            name[0] == '-' &&
            name[1] >= '0' &&
            name[1] <= '9'
        )
    ) {

        return atoi(name);
    }


    /*
     * Search symbol table
     */
    for (
        int i = 0;
        i < sym_count;
        i++
    ) {

        if (
            strcmp(
                symbol_table[i].name,
                name
            ) == 0
        ) {

            return symbol_table[i].val;
        }
    }


    /*
     * Undefined variables currently
     * default to zero.
     */
    return 0;
}


/* =========================================================
   SET VARIABLE VALUE
   ========================================================= */

void set_var(
    const char *name,
    int val
) {

    /*
     * Existing variable
     */
    for (
        int i = 0;
        i < sym_count;
        i++
    ) {

        if (
            strcmp(
                symbol_table[i].name,
                name
            ) == 0
        ) {

            symbol_table[i].val = val;

            return;
        }
    }


    /*
     * New variable
     */
    if (sym_count >= 100) {

        fprintf(
            stderr,
            "ERROR: Symbol table overflow.\n"
        );

        exit(EXIT_FAILURE);
    }


    strcpy(
        symbol_table[sym_count].name,
        name
    );

    symbol_table[sym_count].val = val;

    sym_count++;
}


/* =========================================================
   TAC EXECUTION
   ========================================================= */

void execute_tac() {

    printf(
        "\n--- RUNTIME EXECUTION OUTPUT ---\n"
    );


    int pc = 0;

    int steps = 0;


    /*
     * Step limit prevents accidental infinite loops
     * during compiler development.
     */
    while (
        pc < quad_count &&
        steps < 1000
    ) {

        steps++;


        Quad q =
            quad_table[pc];


        /*
         * Default control flow:
         *
         * execute next quad.
         */
        int next_pc =
            pc + 1;


        /* -------------------------------------------------
           ASSIGNMENT
           ------------------------------------------------- */

        if (
            strcmp(q.op, "=") == 0
        ) {

            set_var(
                q.result,
                get_var(q.arg1)
            );
        }


        /* -------------------------------------------------
           ADDITION
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "+") == 0
        ) {

            set_var(
                q.result,
                get_var(q.arg1) +
                get_var(q.arg2)
            );
        }


        /* -------------------------------------------------
           SUBTRACTION
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "-") == 0
        ) {

            set_var(
                q.result,
                get_var(q.arg1) -
                get_var(q.arg2)
            );
        }


        /* -------------------------------------------------
           MULTIPLICATION
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "*") == 0
        ) {

            set_var(
                q.result,
                get_var(q.arg1) *
                get_var(q.arg2)
            );
        }


        /* -------------------------------------------------
           DIVISION
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "/") == 0
        ) {

            int denom =
                get_var(q.arg2);

            if (denom != 0) {

                set_var(
                    q.result,
                    get_var(q.arg1) /
                    denom
                );
            }
        }


        /* -------------------------------------------------
           LESS THAN
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "<") == 0
        ) {

            if (
                get_var(q.arg1) <
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           GREATER THAN
           ------------------------------------------------- */

        else if (
            strcmp(q.op, ">") == 0
        ) {

            if (
                get_var(q.arg1) >
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           LESS THAN OR EQUAL
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "<=") == 0
        ) {

            if (
                get_var(q.arg1) <=
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           GREATER THAN OR EQUAL
           ------------------------------------------------- */

        else if (
            strcmp(q.op, ">=") == 0
        ) {

            if (
                get_var(q.arg1) >=
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           EQUAL
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "==") == 0
        ) {

            if (
                get_var(q.arg1) ==
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           NOT EQUAL
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "!=") == 0
        ) {

            if (
                get_var(q.arg1) !=
                get_var(q.arg2)
            ) {

                next_pc =
                    atoi(q.result);
            }
        }


        /* -------------------------------------------------
           UNCONDITIONAL GOTO
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "goto") == 0
        ) {

            next_pc =
                atoi(q.result);
        }


        /* -------------------------------------------------
           PRINT
           ------------------------------------------------- */

        else if (
            strcmp(q.op, "print") == 0
        ) {

            printf(
                "OUTPUT: %d\n",
                get_var(q.arg1)
            );
        }

        else if (strcmp(q.op, "print_str") == 0) {
            int len = strlen(q.arg1);
            if (len >= 2 && q.arg1[0] == '"' && q.arg1[len - 1] == '"') {
                printf("OUTPUT: %.*s\n", len - 2, q.arg1 + 1);
            } else {
                printf("OUTPUT: %s\n", q.arg1);
            }
        }


        /*
         * Move to next program counter.
         */
        pc =
            next_pc;
    }


    /* -----------------------------------------------------
       LOOP SAFETY WARNING
       ----------------------------------------------------- */

    if (steps >= 1000) {

        printf(
            "\nWARNING: Execution stopped after "
            "1000 TAC steps.\n"
        );

        printf(
            "Possible infinite loop detected.\n"
        );
    }


    /* -----------------------------------------------------
       FINAL MEMORY STATE
       ----------------------------------------------------- */

    printf(
        "\nFinal Memory State (Variables):\n"
    );

    for (
        int i = 0;
        i < sym_count;
        i++
    ) {

        /*
         * Hide compiler-generated temporaries.
         */
        if (
            symbol_table[i].name[0] != 't'
        ) {

            printf(
                "  %s = %d\n",
                symbol_table[i].name,
                symbol_table[i].val
            );
        }
    }
}


/* =========================================================
   ERROR HANDLER
   ========================================================= */

void yyerror(
    const char *s
) {

    fprintf(
        stderr,
        "COMPILATION ERROR: %s\n",
        s
    );
}


/* =========================================================
   MAIN
   ========================================================= */

int main() {

    /*
     * yyparse() reads source code from stdin.
     *
     * Therefore both of these work:
     *
     *     ./compiler
     *
     * or:
     *
     *     ./compiler < input.txt
     */

    if (yyparse() == 0) {
        
        /*
         * Print backpatch log summary after input stream finishes
         */
        print_backpatch_logs();
        
        /*
         * Human-readable TAC
         */
        print_tac();

        /*
         * Internal quadruple representation
         */
        print_quads();

        /*
         * Execute generated intermediate code
         */
        execute_tac();
    }

    return 0;
}
