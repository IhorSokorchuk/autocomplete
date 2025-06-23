#!/bin/bash
DB=../db/words.db
WORDS=/usr/share/dict/words

mkdir -p ../db
rm -f "$DB"

sqlite3 "$DB" <<EOF
CREATE TABLE words (word TEXT PRIMARY KEY);
.mode tabs
.import $WORDS words
CREATE INDEX idx_word ON words(word);
EOF
