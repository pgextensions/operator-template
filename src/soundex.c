/*
 * soundex.c
 *
 * Implementation of the soundex algorithm.  Soundex takes a word and breaks
 * it into phonetic parts.  It is meant to be used in English to find possible
 * homophones so they can be matched regardless of possible spellings.  Note
 * that the algorithm relies on ASCII characters.
 *
 * Some examples include:
 *  "there", "their", "they're"
 *  "John", "Jon", "Joan"
 *
 * More information can be found at https://en.wikipedia.org/wiki/Soundex
 */

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

#include "soundex.h"

/* Values of A-Z in soundex. '0' is a vowel. */
static const char *soundex_table = "01230120022455012623010202";

/*
 * soundex_code(char letter)
 *
 * Returns the code from the table, or if outside the ASCII values of
 * A - Z, it simply returns the value of the letter passed.
 */
static const char soundex_code(char letter) {
  letter = toupper((unsigned char)letter);

  /* ASCII representation of the letter is between A and Z, look it up. */
  if (letter >= 'A' && letter <= 'Z') {
    return soundex_table[ letter - 'A' ];
  }

  /* Otherwise return its current value. */
  return letter;
}

/*
 * soundex(const char *word, uint8_t length, char *output)
 *
 * Creates a copy of the Soundex from a word, and returns the result in the
 * pre-allocated output.
 */
void soundex(const char *word, int32_t length, char *output) {
  char c, prev;
  int32_t i, j;

  /* Check the length, if it is 0, set output to be empty. */
  if (length == 0) {
    output[ 0 ] = '\0';
    return;
  }

  /* Save the first character, and set the previous character to its Soundex. */
  output[ 0 ] = toupper(word[ 0 ]);
  prev        = soundex_code(word[ 0 ]);

  /* Iterate through the rest of the letters until we have 4 characters. */
  for (i = j = 1; j < length && i < 4; j++) {
    c = soundex_code(word[ j ]);

    /* If it is the same code, skip it and continue. */
    if (c == prev) {
      continue;
    }

    if (c <= '0' || c > '6') {
      /* If it's a vowel, or outside our table, consider it a vowel. */
      prev = '0';
    } else {
      /* Otherwise, add it and set the new previous value. */
      output[ i ] = c;
      prev        = c;
      i++;
    }
  }

  /* If there are any slots left in the Soundex, fill it with vowels. */
  while (i < 4) {
    output[ i ] = '0';
    i++;
  }

  /* Set the last character to the string terminator. */
  output[ 4 ] = '\0';
}
