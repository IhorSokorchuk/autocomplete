#include "completer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

char **get_completions(const char *prefix, int *count) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char **results = NULL;
    int capacity = 10;
    *count = 0;

    if (sqlite3_open("db/words.db", &db) != SQLITE_OK) {
        fprintf(stderr, "cannot open database\n");
        return NULL;
    }

    const char *sql = "SELECT word FROM words WHERE word LIKE ? ORDER BY word LIMIT 100;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "failed to prepare statement\n");
        sqlite3_close(db);
        return NULL;
    }

    char pattern[256];
    snprintf(pattern, sizeof(pattern), "%s%%", prefix);
    sqlite3_bind_text(stmt, 1, pattern, -1, SQLITE_STATIC);

    results = malloc(capacity * sizeof(char *));
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *res = (const char *)sqlite3_column_text(stmt, 0);
        if (*count >= capacity) {
            capacity *= 2;
            results = realloc(results, capacity * sizeof(char *));
        }
        results[*count] = strdup(res);
        (*count)++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return results;
}

char *longest_common_prefix(char **list, int count) {
    if (count == 0) return NULL;
    static char output[256];
    strncpy(output, list[0], sizeof(output) - 1);
    output[sizeof(output) - 1] = '\0';

    for (int i = 1; i < count; ++i) {
        int j = 0;
        while (output[j] && list[i][j] && output[j] == list[i][j]) j++;
        output[j] = '\0';
    }
    return output;
}
