OBJS = src/soundex.o src/operator.o
MODULE_big = soundex-operator

EXTENSION = soundex-operator
DATA = soundex-operator--1.0.0.sql
PGFILEDESC = "soundex - operators for comparing strings"

REGRESS = soundex_operator
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
