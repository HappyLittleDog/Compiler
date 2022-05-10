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
#line 7 "/root/compiler/src/parser.y"

#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"
#include "logger.hpp"

using namespace std;
int yylex();
void yyerror(std::unique_ptr<BaseAst> &ast, const char *s);

#line 82 "/root/compiler/build/parser.tab.cpp"

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
#ifndef YY_YY_ROOT_COMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
# define YY_YY_ROOT_COMPILER_BUILD_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/root/compiler/src/parser.y"

  #include <memory>
  #include <string>
  #include "ast.hpp"
  #include "logger.hpp"

#line 132 "/root/compiler/build/parser.tab.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    RETURN = 259,
    PLUS = 260,
    MINUS = 261,
    MULT = 262,
    DIV = 263,
    MOD = 264,
    EQQ = 265,
    NEQ = 266,
    LT = 267,
    GT = 268,
    LEQ = 269,
    GEQ = 270,
    NOT = 271,
    AND = 272,
    OR = 273,
    EQ = 274,
    CONST = 275,
    IF = 276,
    ELSE = 277,
    WHILE = 278,
    BREAK = 279,
    CONTINUE = 280,
    VOID = 281,
    IDENT = 282,
    INT_CONST = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "/root/compiler/src/parser.y"

    int int_val;
    std::string* str_val;
    BaseAst* ast_val;

#line 178 "/root/compiler/build/parser.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (std::unique_ptr<BaseAst> &ast);

#endif /* !YY_YY_ROOT_COMPILER_BUILD_PARSER_TAB_HPP_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   174

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

#define YYUNDEFTOK  2
#define YYMAXUTOK   283


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,     2,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    31,    31,    39,    43,    52,    58,    67,    78,    91,
      95,   101,   110,   118,   131,   135,   141,   150,   160,   164,
     173,   180,   190,   196,   205,   215,   225,   229,   236,   242,
     251,   264,   268,   277,   284,   295,   299,   305,   314,   323,
     329,   338,   347,   360,   368,   379,   383,   389,   398,   405,
     415,   422,   428,   436,   442,   449,   456,   465,   473,   479,
     488,   496,   505,   516,   526,   535,   547,   556,   568,   577,
     586,   598,   607,   616,   625,   634,   646,   655,   664,   676,
     685,   694,   703,   715,   723,   731,   739,   747,   759,   767,
     775,   786,   798,   802,   811
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "RETURN", "PLUS", "MINUS", "MULT",
  "DIV", "MOD", "EQQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "NOT", "AND", "OR",
  "EQ", "CONST", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "VOID",
  "IDENT", "INT_CONST", "'('", "')'", "';'", "','", "'['", "']'", "'{'",
  "'}'", "$accept", "Program", "CompUnits", "CompUnit", "FuncDef",
  "FuncFParams", "FuncFParam", "FuncRParams", "Block", "BlockItems",
  "BlockItem", "Decl", "ConstDecl", "VarDecl", "BType", "ConstDefs",
  "ConstDef", "ArraySize", "ConstInitVal", "ConstInitVals", "ConstExp",
  "VarDefs", "VarDef", "InitVal", "InitVals", "Stmt", "Closed_If_Stmt",
  "Open_If_Stmt", "Exp", "LOrExp", "LAndExp", "EqExp", "RelExp", "AddExp",
  "MulExp", "UnaryExp", "PrimaryExp", "LVal", "ArrayIndex", "Number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    40,
      41,    59,    44,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -135,    29,    13,  -135,  -135,    14,  -135,  -135,  -135,  -135,
    -135,  -135,    10,    21,    48,   -22,  -135,  -135,    38,  -135,
      14,   -12,  -135,    33,   -11,  -135,    21,    25,  -135,    63,
      70,   145,  -135,  -135,    96,  -135,    16,    14,    19,   145,
     145,   145,    71,  -135,   145,    70,  -135,  -135,    49,    79,
       9,    67,    40,    80,  -135,  -135,  -135,  -135,    72,  -135,
      96,  -135,  -135,  -135,  -135,  -135,  -135,    77,  -135,  -135,
    -135,   145,    82,    74,  -135,    17,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,  -135,
    -135,    22,   113,  -135,    31,  -135,   145,  -135,    70,  -135,
      79,     9,    67,    67,    40,    40,    40,    40,    80,    80,
    -135,  -135,  -135,    96,  -135,   140,    84,    91,    95,    99,
    -135,  -135,  -135,  -135,  -135,    33,  -135,  -135,  -135,   101,
     108,   102,  -135,   145,   109,  -135,  -135,  -135,   116,   145,
     145,  -135,  -135,  -135,   145,  -135,  -135,  -135,   122,   123,
     124,     7,     7,  -135,  -135,   132,  -135,  -135,     7,  -135,
    -135
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    27,     0,    26,     4,     5,     6,
      22,    23,     0,     0,    31,     0,    39,    31,     0,    28,
       9,    41,    25,     0,     0,    24,     0,     0,    10,     0,
       0,     0,    31,    40,     0,    29,     0,     0,    12,     0,
       0,     0,    92,    94,     0,    45,    42,    43,    63,    64,
      66,    68,    71,    76,    79,    86,    90,    89,     0,    38,
      35,    30,    33,     8,    18,     7,    11,     0,    83,    84,
      85,    14,    91,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      36,     0,     0,    31,     0,    15,     0,    88,     0,    44,
      65,    67,    69,    70,    72,    73,    74,    75,    77,    78,
      80,    81,    82,     0,    34,     0,     0,     0,     0,     0,
      53,    17,    55,    19,    20,     0,    21,    49,    48,     0,
      90,    13,    87,     0,     0,    47,    37,    51,     0,     0,
       0,    58,    59,    54,     0,    16,    93,    50,     0,     0,
       0,     0,     0,    52,    60,    49,    57,    62,     0,    56,
      61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,  -135,  -135,  -135,   120,  -135,   126,  -135,
    -135,    66,  -135,  -135,    -1,  -135,   133,   -15,   -57,  -135,
     129,  -135,   141,   -39,  -135,    15,  -108,  -134,   -30,  -135,
      87,    88,     5,    12,    23,   -14,  -135,   -87,  -135,  -135
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,    27,    28,    94,   122,    92,
     123,     9,    10,    11,    29,    18,    19,    21,    61,    91,
      62,    15,    16,    46,    75,   126,   127,   128,    59,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    72,    57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    12,    24,    90,    13,   130,    74,    30,    34,    22,
      23,   115,    39,    40,    73,    47,     4,     4,   157,    78,
      79,    31,    31,    41,   160,    68,    69,    70,   116,     3,
     117,   118,   119,     5,    42,    43,    44,    14,   120,     6,
       6,    95,    64,   155,   156,    84,    85,    63,    17,    98,
     159,    64,    67,    99,   113,    36,   136,    37,   114,   135,
      32,   132,   129,   133,   130,   130,   134,    76,    47,    25,
      26,   130,   110,   111,   112,    39,    40,    20,   131,    80,
      81,    82,    83,   102,   103,   138,    41,    86,    87,    88,
      38,   125,   104,   105,   106,   107,    77,    42,    43,    44,
      71,    39,    40,   145,    97,    45,    89,   108,   109,   148,
     149,    93,    41,   139,   150,    96,     4,   115,    39,    40,
     140,   129,   129,    42,    43,    44,   141,   144,   129,    41,
     142,    60,   143,     5,   116,    31,   117,   118,   119,     6,
      42,    43,    44,   146,   120,    39,    40,   147,    64,   121,
      39,    40,   151,   152,   158,   153,    41,    66,   124,    35,
      58,    41,    65,   100,    33,   101,   154,    42,    43,    44,
       0,   137,    42,    43,    44
};

static const yytype_int16 yycheck[] =
{
      30,     2,    17,    60,     5,    92,    45,    19,    19,    31,
      32,     4,     5,     6,    44,    45,     3,     3,   152,    10,
      11,    33,    33,    16,   158,    39,    40,    41,    21,     0,
      23,    24,    25,    20,    27,    28,    29,    27,    31,    26,
      26,    71,    35,   151,   152,     5,     6,    31,    27,    32,
     158,    35,    33,    36,    32,    30,   113,    32,    36,    98,
      27,    30,    92,    32,   151,   152,    96,    18,    98,    31,
      32,   158,    86,    87,    88,     5,     6,    29,    93,    12,
      13,    14,    15,    78,    79,   115,    16,     7,     8,     9,
      27,    92,    80,    81,    82,    83,    17,    27,    28,    29,
      29,     5,     6,   133,    30,    35,    34,    84,    85,   139,
     140,    34,    16,    29,   144,    33,     3,     4,     5,     6,
      29,   151,   152,    27,    28,    29,    31,    19,   158,    16,
      31,    35,    31,    20,    21,    33,    23,    24,    25,    26,
      27,    28,    29,    34,    31,     5,     6,    31,    35,    36,
       5,     6,    30,    30,    22,    31,    16,    37,    92,    26,
      31,    16,    36,    76,    23,    77,   151,    27,    28,    29,
      -1,    31,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    39,     0,     3,    20,    26,    40,    41,    48,
      49,    50,    51,    51,    27,    58,    59,    27,    52,    53,
      29,    54,    31,    32,    54,    31,    32,    42,    43,    51,
      19,    33,    27,    59,    19,    53,    30,    32,    27,     5,
       6,    16,    27,    28,    29,    35,    60,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    76,    57,    65,
      35,    55,    57,    31,    35,    45,    43,    33,    72,    72,
      72,    29,    75,    65,    60,    61,    18,    17,    10,    11,
      12,    13,    14,    15,     5,     6,     7,     8,     9,    34,
      55,    56,    46,    34,    44,    65,    33,    30,    32,    36,
      67,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    72,    72,    32,    36,     4,    21,    23,    24,    25,
      31,    36,    45,    47,    48,    51,    62,    63,    64,    65,
      74,    54,    30,    32,    65,    60,    55,    31,    65,    29,
      29,    31,    31,    31,    19,    65,    34,    31,    65,    65,
      65,    30,    30,    31,    62,    63,    63,    64,    22,    63,
      64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    41,    41,    42,
      42,    42,    43,    43,    44,    44,    44,    45,    46,    46,
      47,    47,    48,    48,    49,    50,    51,    51,    52,    52,
      53,    54,    54,    55,    55,    56,    56,    56,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    61,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      64,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    69,    69,    69,    70,    70,    70,    71,
      71,    71,    71,    72,    72,    72,    72,    72,    73,    73,
      73,    74,    75,    75,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     6,     6,     0,
       1,     3,     2,     5,     0,     1,     3,     3,     0,     2,
       1,     1,     1,     1,     4,     3,     1,     1,     1,     3,
       4,     0,     4,     1,     3,     0,     1,     3,     1,     1,
       3,     2,     4,     1,     3,     0,     1,     3,     1,     1,
       3,     2,     4,     1,     2,     1,     7,     5,     2,     2,
       5,     7,     5,     1,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     2,     2,     2,     1,     4,     3,     1,
       1,     2,     0,     4,     1
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
        yyerror (ast, YY_("syntax error: cannot back up")); \
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
                  Type, Value, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAst> &ast)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (ast);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAst> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, ast);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, std::unique_ptr<BaseAst> &ast)
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
                                              , ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, std::unique_ptr<BaseAst> &ast)
{
  YYUSE (yyvaluep);
  YYUSE (ast);
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
yyparse (std::unique_ptr<BaseAst> &ast)
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
  case 2:
#line 32 "/root/compiler/src/parser.y"
        {
            ast=unique_ptr<BaseAst>((yyvsp[0].ast_val));
        }
#line 1474 "/root/compiler/build/parser.tab.cpp"
    break;

  case 3:
#line 39 "/root/compiler/src/parser.y"
        {
            auto cur=new CompUnits();
            (yyval.ast_val)=cur;
        }
#line 1483 "/root/compiler/build/parser.tab.cpp"
    break;

  case 4:
#line 44 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<CompUnits*>((yyvsp[-1].ast_val));
            cur->items_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1493 "/root/compiler/build/parser.tab.cpp"
    break;

  case 5:
#line 53 "/root/compiler/src/parser.y"
        {
            auto cur=new CompUnit();
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1503 "/root/compiler/build/parser.tab.cpp"
    break;

  case 6:
#line 59 "/root/compiler/src/parser.y"
        {
            auto cur=new CompUnit();
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1513 "/root/compiler/build/parser.tab.cpp"
    break;

  case 7:
#line 68 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncDef();
            cur->functype_=int((yyvsp[-5].int_val));
            cur->ident_=*unique_ptr<string>((yyvsp[-4].str_val));
            cur->params_=shared_ptr<BaseAst>((yyvsp[-2].ast_val));
            auto blk=reinterpret_cast<Block*>((yyvsp[0].ast_val));
            blk->params_=cur->params_;
            cur->block_=unique_ptr<BaseAst>(blk);
            (yyval.ast_val)=cur;
        }
#line 1528 "/root/compiler/build/parser.tab.cpp"
    break;

  case 8:
#line 79 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncDef();
            cur->functype_=int((yyvsp[-5].int_val));
            cur->ident_=*unique_ptr<string>((yyvsp[-4].str_val));
            cur->params_=shared_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->block_=nullptr;
            (yyval.ast_val)=cur;
        }
#line 1541 "/root/compiler/build/parser.tab.cpp"
    break;

  case 9:
#line 91 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncFParams();
            (yyval.ast_val)=cur;
        }
#line 1550 "/root/compiler/build/parser.tab.cpp"
    break;

  case 10:
#line 96 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncFParams();
            cur->params_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1560 "/root/compiler/build/parser.tab.cpp"
    break;

  case 11:
#line 102 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<FuncFParams*>((yyvsp[-2].ast_val));
            cur->params_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1570 "/root/compiler/build/parser.tab.cpp"
    break;

  case 12:
#line 111 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncFParam();
            cur->cur_derivation_=0;
            cur->type_=int((yyvsp[-1].int_val));
            cur->ident_ = *((yyvsp[0].str_val));
            (yyval.ast_val)=cur;
        }
#line 1582 "/root/compiler/build/parser.tab.cpp"
    break;

  case 13:
#line 119 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncFParam();
            cur->cur_derivation_=1;
            cur->type_=int((yyvsp[-4].int_val));
            cur->ident_ = *((yyvsp[-3].str_val));
            cur->size_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1595 "/root/compiler/build/parser.tab.cpp"
    break;

  case 14:
#line 131 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncRParams();
            (yyval.ast_val)=cur;
        }
#line 1604 "/root/compiler/build/parser.tab.cpp"
    break;

  case 15:
#line 136 "/root/compiler/src/parser.y"
        {
            auto cur=new FuncRParams();
            cur->params_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1614 "/root/compiler/build/parser.tab.cpp"
    break;

  case 16:
#line 142 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<FuncRParams*>((yyvsp[-2].ast_val));
            cur->params_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1624 "/root/compiler/build/parser.tab.cpp"
    break;

  case 17:
#line 151 "/root/compiler/src/parser.y"
        {
            auto cur=new Block();
            cur->items_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1634 "/root/compiler/build/parser.tab.cpp"
    break;

  case 18:
#line 160 "/root/compiler/src/parser.y"
        {
            auto cur=new BlockItems();
            (yyval.ast_val)=cur;
        }
#line 1643 "/root/compiler/build/parser.tab.cpp"
    break;

  case 19:
#line 165 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<BlockItems*>((yyvsp[-1].ast_val));
            cur->items_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1653 "/root/compiler/build/parser.tab.cpp"
    break;

  case 20:
#line 174 "/root/compiler/src/parser.y"
        {
            auto cur=new BlockItem();
            cur->cur_derivation_=0;
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1664 "/root/compiler/build/parser.tab.cpp"
    break;

  case 21:
#line 181 "/root/compiler/src/parser.y"
        {
            auto cur=new BlockItem();
            cur->cur_derivation_=1;
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1675 "/root/compiler/build/parser.tab.cpp"
    break;

  case 22:
#line 191 "/root/compiler/src/parser.y"
                {
            auto cur=new Decl();
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
		}
#line 1685 "/root/compiler/build/parser.tab.cpp"
    break;

  case 23:
#line 197 "/root/compiler/src/parser.y"
        {
            auto cur=new Decl();
            cur->item_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1695 "/root/compiler/build/parser.tab.cpp"
    break;

  case 24:
#line 206 "/root/compiler/src/parser.y"
                {
            auto cur=new ConstDecl();
            cur->type_=int((yyvsp[-2].int_val));
            cur->item_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
		}
#line 1706 "/root/compiler/build/parser.tab.cpp"
    break;

  case 25:
#line 216 "/root/compiler/src/parser.y"
        {
            auto cur=new VarDecl();
            cur->type_=int((yyvsp[-2].int_val));
            cur->item_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1717 "/root/compiler/build/parser.tab.cpp"
    break;

  case 26:
#line 226 "/root/compiler/src/parser.y"
        {
            (yyval.int_val)=0;
        }
#line 1725 "/root/compiler/build/parser.tab.cpp"
    break;

  case 27:
#line 230 "/root/compiler/src/parser.y"
        {
            (yyval.int_val)=1;
        }
#line 1733 "/root/compiler/build/parser.tab.cpp"
    break;

  case 28:
#line 237 "/root/compiler/src/parser.y"
                {
            auto cur=new ConstDefs();
            cur->defs_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
		}
#line 1743 "/root/compiler/build/parser.tab.cpp"
    break;

  case 29:
#line 243 "/root/compiler/src/parser.y"
                {
            auto cur=reinterpret_cast<ConstDefs*>((yyvsp[-2].ast_val));
            cur->defs_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
		}
#line 1753 "/root/compiler/build/parser.tab.cpp"
    break;

  case 30:
#line 252 "/root/compiler/src/parser.y"
                {
            auto cur=new ConstDef();
            cur->ident_ = *((yyvsp[-3].str_val));
            cur->size_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->initval_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // CurConstSymTab.insert(cur->ident_, cur->initval_->CalcVal());
            (yyval.ast_val)=cur;
		}
#line 1766 "/root/compiler/build/parser.tab.cpp"
    break;

  case 31:
#line 264 "/root/compiler/src/parser.y"
        {
            auto cur=new ArraySize();
            (yyval.ast_val)=cur;
        }
#line 1775 "/root/compiler/build/parser.tab.cpp"
    break;

  case 32:
#line 269 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<ArraySize*>((yyvsp[-3].ast_val));
            cur->size_.push_back(unique_ptr<BaseAst>((yyvsp[-1].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1785 "/root/compiler/build/parser.tab.cpp"
    break;

  case 33:
#line 278 "/root/compiler/src/parser.y"
                {
            auto cur=new ConstInitVal();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
		}
#line 1796 "/root/compiler/build/parser.tab.cpp"
    break;

  case 34:
#line 285 "/root/compiler/src/parser.y"
        {
            auto cur=new ConstInitVal();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1807 "/root/compiler/build/parser.tab.cpp"
    break;

  case 35:
#line 295 "/root/compiler/src/parser.y"
        {
            auto cur=new ConstInitVals();
            (yyval.ast_val)=cur;
        }
#line 1816 "/root/compiler/build/parser.tab.cpp"
    break;

  case 36:
#line 300 "/root/compiler/src/parser.y"
        {
            auto cur=new ConstInitVals();
            cur->exps_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1826 "/root/compiler/build/parser.tab.cpp"
    break;

  case 37:
#line 306 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<ConstInitVals*>((yyvsp[-2].ast_val));
            cur->exps_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1836 "/root/compiler/build/parser.tab.cpp"
    break;

  case 38:
#line 315 "/root/compiler/src/parser.y"
                {
            auto cur=new ConstExp();
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
		}
#line 1846 "/root/compiler/build/parser.tab.cpp"
    break;

  case 39:
#line 324 "/root/compiler/src/parser.y"
        {
            auto cur=new VarDefs();
            cur->defs_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1856 "/root/compiler/build/parser.tab.cpp"
    break;

  case 40:
#line 330 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<VarDefs*>((yyvsp[-2].ast_val));
            cur->defs_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1866 "/root/compiler/build/parser.tab.cpp"
    break;

  case 41:
#line 339 "/root/compiler/src/parser.y"
        {
            auto cur=new VarDef();
            cur->cur_derivation_=0;
            cur->ident_ = *((yyvsp[-1].str_val));
            cur->size_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // CurVarSymTab.insert(cur->ident_);
            (yyval.ast_val)=cur;
        }
#line 1879 "/root/compiler/build/parser.tab.cpp"
    break;

  case 42:
#line 348 "/root/compiler/src/parser.y"
        {
            auto cur=new VarDef();
            cur->cur_derivation_=1;
            cur->ident_ = *((yyvsp[-3].str_val));
            cur->size_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->initval_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // CurVarSymTab.insert(cur->ident_);
            (yyval.ast_val)=cur;
        }
#line 1893 "/root/compiler/build/parser.tab.cpp"
    break;

  case 43:
#line 361 "/root/compiler/src/parser.y"
        {
            auto cur=new InitVal();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 1905 "/root/compiler/build/parser.tab.cpp"
    break;

  case 44:
#line 369 "/root/compiler/src/parser.y"
        {
            auto cur=new InitVal();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1916 "/root/compiler/build/parser.tab.cpp"
    break;

  case 45:
#line 379 "/root/compiler/src/parser.y"
        {
            auto cur=new InitVals();
            (yyval.ast_val)=cur;
        }
#line 1925 "/root/compiler/build/parser.tab.cpp"
    break;

  case 46:
#line 384 "/root/compiler/src/parser.y"
        {
            auto cur=new InitVals();
            cur->exps_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1935 "/root/compiler/build/parser.tab.cpp"
    break;

  case 47:
#line 390 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<InitVals*>((yyvsp[-2].ast_val));
            cur->exps_.push_back(unique_ptr<BaseAst>((yyvsp[0].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 1945 "/root/compiler/build/parser.tab.cpp"
    break;

  case 48:
#line 399 "/root/compiler/src/parser.y"
        {
            auto cur=new Stmt();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1956 "/root/compiler/build/parser.tab.cpp"
    break;

  case 49:
#line 406 "/root/compiler/src/parser.y"
        {
            auto cur=new Stmt();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1967 "/root/compiler/build/parser.tab.cpp"
    break;

  case 50:
#line 416 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 1978 "/root/compiler/build/parser.tab.cpp"
    break;

  case 51:
#line 423 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=0;
            (yyval.ast_val)=cur;
        }
#line 1988 "/root/compiler/build/parser.tab.cpp"
    break;

  case 52:
#line 429 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-3].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2000 "/root/compiler/build/parser.tab.cpp"
    break;

  case 53:
#line 437 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=2;
            (yyval.ast_val)=cur;
        }
#line 2010 "/root/compiler/build/parser.tab.cpp"
    break;

  case 54:
#line 443 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2021 "/root/compiler/build/parser.tab.cpp"
    break;

  case 55:
#line 450 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=4;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2032 "/root/compiler/build/parser.tab.cpp"
    break;

  case 56:
#line 457 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=5;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-4].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp3_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2045 "/root/compiler/build/parser.tab.cpp"
    break;

  case 57:
#line 466 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=6;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2057 "/root/compiler/build/parser.tab.cpp"
    break;

  case 58:
#line 474 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=7;
            (yyval.ast_val)=cur;
        }
#line 2067 "/root/compiler/build/parser.tab.cpp"
    break;

  case 59:
#line 480 "/root/compiler/src/parser.y"
        {
            auto cur=new Closed_If_Stmt();
            cur->cur_derivation_=8;
            (yyval.ast_val)=cur;
        }
#line 2077 "/root/compiler/build/parser.tab.cpp"
    break;

  case 60:
#line 489 "/root/compiler/src/parser.y"
        {
            auto cur=new Open_If_Stmt();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2089 "/root/compiler/build/parser.tab.cpp"
    break;

  case 61:
#line 497 "/root/compiler/src/parser.y"
        {
            auto cur=new Open_If_Stmt();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-4].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp3_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2102 "/root/compiler/build/parser.tab.cpp"
    break;

  case 62:
#line 506 "/root/compiler/src/parser.y"
        {
            auto cur=new Open_If_Stmt();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2114 "/root/compiler/build/parser.tab.cpp"
    break;

  case 63:
#line 517 "/root/compiler/src/parser.y"
        {
            auto cur=new Exp();
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2125 "/root/compiler/build/parser.tab.cpp"
    break;

  case 64:
#line 527 "/root/compiler/src/parser.y"
        {
            auto cur=new LOrExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2138 "/root/compiler/build/parser.tab.cpp"
    break;

  case 65:
#line 536 "/root/compiler/src/parser.y"
        {
            auto cur=new LOrExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2151 "/root/compiler/build/parser.tab.cpp"
    break;

  case 66:
#line 548 "/root/compiler/src/parser.y"
        {
            auto cur=new LAndExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2164 "/root/compiler/build/parser.tab.cpp"
    break;

  case 67:
#line 557 "/root/compiler/src/parser.y"
        {
            auto cur=new LAndExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2177 "/root/compiler/build/parser.tab.cpp"
    break;

  case 68:
#line 569 "/root/compiler/src/parser.y"
        {
            auto cur=new EqExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2190 "/root/compiler/build/parser.tab.cpp"
    break;

  case 69:
#line 578 "/root/compiler/src/parser.y"
        {
            auto cur=new EqExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2203 "/root/compiler/build/parser.tab.cpp"
    break;

  case 70:
#line 587 "/root/compiler/src/parser.y"
        {
            auto cur=new EqExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2216 "/root/compiler/build/parser.tab.cpp"
    break;

  case 71:
#line 599 "/root/compiler/src/parser.y"
        {
            auto cur=new RelExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2229 "/root/compiler/build/parser.tab.cpp"
    break;

  case 72:
#line 608 "/root/compiler/src/parser.y"
        {
            auto cur=new RelExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2242 "/root/compiler/build/parser.tab.cpp"
    break;

  case 73:
#line 617 "/root/compiler/src/parser.y"
        {
            auto cur=new RelExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2255 "/root/compiler/build/parser.tab.cpp"
    break;

  case 74:
#line 626 "/root/compiler/src/parser.y"
        {
            auto cur=new RelExp();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2268 "/root/compiler/build/parser.tab.cpp"
    break;

  case 75:
#line 635 "/root/compiler/src/parser.y"
        {
            auto cur=new RelExp();
            cur->cur_derivation_=4;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2281 "/root/compiler/build/parser.tab.cpp"
    break;

  case 76:
#line 647 "/root/compiler/src/parser.y"
        {
            auto cur=new AddExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2294 "/root/compiler/build/parser.tab.cpp"
    break;

  case 77:
#line 656 "/root/compiler/src/parser.y"
        {
            auto cur=new AddExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2307 "/root/compiler/build/parser.tab.cpp"
    break;

  case 78:
#line 665 "/root/compiler/src/parser.y"
        {
            auto cur=new AddExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2320 "/root/compiler/build/parser.tab.cpp"
    break;

  case 79:
#line 677 "/root/compiler/src/parser.y"
        {
            auto cur=new MulExp();
            cur->cur_derivation_=0;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            cur->subexp2_=nullptr;
            // cur->isconst_=cur->subexp1_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2333 "/root/compiler/build/parser.tab.cpp"
    break;

  case 80:
#line 686 "/root/compiler/src/parser.y"
        {
            auto cur=new MulExp();
            cur->cur_derivation_=1;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2346 "/root/compiler/build/parser.tab.cpp"
    break;

  case 81:
#line 695 "/root/compiler/src/parser.y"
        {
            auto cur=new MulExp();
            cur->cur_derivation_=2;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2359 "/root/compiler/build/parser.tab.cpp"
    break;

  case 82:
#line 704 "/root/compiler/src/parser.y"
        {
            auto cur=new MulExp();
            cur->cur_derivation_=3;
            cur->subexp1_=unique_ptr<BaseAst>((yyvsp[-2].ast_val));
            cur->subexp2_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp1_->IsConst() && cur->subexp2_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2372 "/root/compiler/build/parser.tab.cpp"
    break;

  case 83:
#line 716 "/root/compiler/src/parser.y"
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2384 "/root/compiler/build/parser.tab.cpp"
    break;

  case 84:
#line 724 "/root/compiler/src/parser.y"
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2396 "/root/compiler/build/parser.tab.cpp"
    break;

  case 85:
#line 732 "/root/compiler/src/parser.y"
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=2;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2408 "/root/compiler/build/parser.tab.cpp"
    break;

  case 86:
#line 740 "/root/compiler/src/parser.y"
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=3;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2420 "/root/compiler/build/parser.tab.cpp"
    break;

  case 87:
#line 748 "/root/compiler/src/parser.y"
        {
            auto cur=new UnaryExp();
            cur->cur_derivation_=4;
            cur->isconst_=0;
            cur->ident_ = *((yyvsp[-3].str_val));
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2433 "/root/compiler/build/parser.tab.cpp"
    break;

  case 88:
#line 760 "/root/compiler/src/parser.y"
        {
            auto cur=new PrimaryExp();
            cur->cur_derivation_=0;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[-1].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
        }
#line 2445 "/root/compiler/build/parser.tab.cpp"
    break;

  case 89:
#line 768 "/root/compiler/src/parser.y"
        {
            auto cur=new PrimaryExp();
            // cur->isconst_=true;
            cur->cur_derivation_=1;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            (yyval.ast_val)=cur;
        }
#line 2457 "/root/compiler/build/parser.tab.cpp"
    break;

  case 90:
#line 776 "/root/compiler/src/parser.y"
                {
			auto cur=new PrimaryExp();
            cur->cur_derivation_=2;
            cur->subexp_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=cur->subexp_->IsConst();
            (yyval.ast_val)=cur;
		}
#line 2469 "/root/compiler/build/parser.tab.cpp"
    break;

  case 91:
#line 787 "/root/compiler/src/parser.y"
                {
            auto cur=new LVal();
            cur->ident_ = *((yyvsp[-1].str_val));
            cur->ndx_=unique_ptr<BaseAst>((yyvsp[0].ast_val));
            // cur->isconst_=CurConstSymTab.exists(cur->ident_);
            (yyval.ast_val)=cur;
		}
#line 2481 "/root/compiler/build/parser.tab.cpp"
    break;

  case 92:
#line 798 "/root/compiler/src/parser.y"
        {
            auto cur=new ArrayIndex();
            (yyval.ast_val)=cur;
        }
#line 2490 "/root/compiler/build/parser.tab.cpp"
    break;

  case 93:
#line 803 "/root/compiler/src/parser.y"
        {
            auto cur=reinterpret_cast<ArrayIndex*>((yyvsp[-3].ast_val));
            cur->ndx_.push_back(unique_ptr<BaseAst>((yyvsp[-1].ast_val)));
            (yyval.ast_val)=cur;
        }
#line 2500 "/root/compiler/build/parser.tab.cpp"
    break;

  case 94:
#line 812 "/root/compiler/src/parser.y"
        {
            auto cur=new Number();
            cur->int_const_=to_string((yyvsp[0].int_val));
            (yyval.ast_val)=cur;
        }
#line 2510 "/root/compiler/build/parser.tab.cpp"
    break;


#line 2514 "/root/compiler/build/parser.tab.cpp"

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
      yyerror (ast, YY_("syntax error"));
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
        yyerror (ast, yymsgp);
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
                      yytoken, &yylval, ast);
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
                  yystos[yystate], yyvsp, ast);
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
  yyerror (ast, YY_("memory exhausted"));
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
                  yytoken, &yylval, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, ast);
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
#line 818 "/root/compiler/src/parser.y"

void yyerror(std::unique_ptr<BaseAst> &ast, const char *s)
{
    LOG_ERROR("%s", s);
    ast->Print();
}
