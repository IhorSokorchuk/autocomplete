# Makefile — AutoSuggest / Автодоповнення (GPL-3.0 License)
# Copyright (C) 2025 Ігор Сокорчук
# This file is part of the AutoSuggest project.
#
# AutoSuggest is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# AutoSuggest is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -Iinclude -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lsqlite3

SUGGEST_OBJS = src/main_suggest.o src/ui.o src/completer.o src/common.o
COMPLETE_OBJS = src/main_complete.o src/completer.o

all: suggest complete

suggest: $(SUGGEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

complete: $(COMPLETE_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f suggest complete src/*.o

.PHONY: all clean
