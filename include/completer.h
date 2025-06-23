#ifndef COMPLETER_H
#define COMPLETER_H

char **get_completions(const char *prefix, int *count);
char *longest_common_prefix(char **list, int count);

#endif
