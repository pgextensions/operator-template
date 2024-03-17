CREATE OR REPLACE FUNCTION soundex_eq(left TEXT, right TEXT)
  RETURNS BOOL
  AS 'MODULE_PATHNAME', 'soundex_eq'
  LANGUAGE C STRICT IMMUTABLE;

CREATE OR REPLACE FUNCTION soundex_ne(left TEXT, right TEXT)
  RETURNS BOOL
  AS 'MODULE_PATHNAME', 'soundex_ne'
  LANGUAGE C STRICT IMMUTABLE;

CREATE OPERATOR >@@< (
  LEFTARG    = TEXT,
  RIGHTARG   = TEXT,
  COMMUTATOR = >@@<,
  NEGATOR    = <@@>,
  PROCEDURE  = soundex_eq,
  RESTRICT   = eqsel,
  JOIN       = eqjoinsel,
  HASHES,
  MERGES
);

CREATE OPERATOR <@@> (
  LEFTARG    = TEXT,
  RIGHTARG   = TEXT,
  COMMUTATOR = <@@>,
  NEGATOR    = >@@<,
  PROCEDURE  = soundex_ne,
  RESTRICT   = neqsel,
  JOIN       = neqjoinsel,
  HASHES,
  MERGES
);
