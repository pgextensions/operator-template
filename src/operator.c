#include "postgres.h"

#if PG_VERSION_NUM >= 160000
#include "varatt.h"
#endif

#include "fmgr.h"

#include "soundex.h"

/* Set up the extension. */
PG_MODULE_MAGIC;

/* Define the functions. */
PG_FUNCTION_INFO_V1(soundex_eq);
PG_FUNCTION_INFO_V1(soundex_ne);

Datum soundex_eq(PG_FUNCTION_ARGS) {
  /* Get the first 2 arguments as text. */
  text *left  = PG_GETARG_TEXT_PP(0);
  text *right = PG_GETARG_TEXT_PP(1);

  /* Create soundex copies of the arguments, using the pointer to the
     string along with the length. */
  char left_soundex[ 5 ];
  char right_soundex[ 5 ];
  bool result;

  soundex(VARDATA_ANY(left), VARSIZE_ANY_EXHDR(left), left_soundex);
  soundex(VARDATA_ANY(right), VARSIZE_ANY_EXHDR(right), right_soundex);
  result = (strcmp(left_soundex, right_soundex) == 0);

  /* Free up any results we should be responsible for. */
  PG_FREE_IF_COPY(left, 0);
  PG_FREE_IF_COPY(right, 1);

  /* Return the result as a Datum. */
  PG_RETURN_BOOL(result);
}

Datum soundex_ne(PG_FUNCTION_ARGS) {
  /* Get the first 2 arguments as text. */
  text *left  = PG_GETARG_TEXT_PP(0);
  text *right = PG_GETARG_TEXT_PP(1);

  /* Create soundex copies of the arguments, using the pointer to the
     string along with the length. */
  char left_soundex[ 5 ];
  char right_soundex[ 5 ];
  bool result;

  soundex(VARDATA_ANY(left), VARSIZE_ANY_EXHDR(left), left_soundex);
  soundex(VARDATA_ANY(right), VARSIZE_ANY_EXHDR(right), right_soundex);
  result = (strcmp(left_soundex, right_soundex) != 0);

  /* Free up any results we should be responsible for. */
  PG_FREE_IF_COPY(left, 0);
  PG_FREE_IF_COPY(right, 1);

  /* Return the result as a Datum. */
  PG_RETURN_BOOL(result);
}
