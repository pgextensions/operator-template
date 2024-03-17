CREATE EXTENSION "soundex-operator";

-- john and joan should be equal
SELECT soundex_eq('john', 'joan');

-- bob and shirley should not
SELECT soundex_eq('john', 'shirley');

-- and the inverse of each
SELECT soundex_ne('john', 'joan');
SELECT soundex_ne('john', 'shirley');

-- those should translate into the operators
SELECT 'john' >@@< 'joan';
SELECT 'john' >@@< 'shirley';

SELECT 'john' <@@> 'joan';
SELECT 'john' <@@> 'shirley';
