#include "string.h"
#include <stddef.h>

string *string_alloc(const char *initial_data) {
  size_t length = strlen(initial_data);

  string *str = malloc(sizeof(string) + length + 1);
  if (str) {
    str->length = length;
    str->capacity = length + 1;
    strcpy(str->data, initial_data);
  }
  return str;
}

void string_resize(string **str, size_t new_capacity) {
  if (new_capacity <= (*str)->capacity) {
    return;
  }

  string *new_str = realloc(*str, sizeof(string) + new_capacity);
  if (new_str) {
    new_str->capacity = new_capacity;
    *str = new_str;
  }
}

void string_destroy(string *str) { free(str); }

void string_append(string **str, const char *append_str) {
  size_t append_len = strlen(append_str);
  size_t new_len = (*str)->length + append_len;

  if (new_len + 1 > (*str)->capacity) {
    size_t new_capacity = (*str)->capacity * 2;
    while (new_capacity < new_len + 1) {
      new_capacity *= 2;
    }

    string_resize(str, new_capacity);
  }

  memcpy((*str)->data + (*str)->length, append_str, append_len);
  (*str)->length = new_len;
  (*str)->data[new_len] = '\0';
}

// Function to clear the content of the string
void string_clear(string *str) {
  str->length = 0;
  str->data[0] = '\0';
}

// Function to get the character at a specific index
char string_get_char(const string *str, size_t index) {
  if (index < str->length) {
    return str->data[index];
  }
  return '\0'; // Invalid index
}

// Function to find the index of a substring
ssize_t string_find(const string *str, const char *sub_str) {
  char *pos = strstr(str->data, sub_str);
  if (pos) {
    return pos - str->data;
  }
  return -1; // Substring not found
}

bool string_contains(const string *str, const char *substring) {
  return strstr(str->data, substring) != NULL;
}

// Function to insert a substring at a specific index
void string_insert(string **str, size_t index, const char *insert_str) {
  if (index > (*str)->length) {
    return; // Invalid index
  }

  size_t insert_len = strlen(insert_str);
  size_t new_len = (*str)->length + insert_len;

  if (new_len + 1 > (*str)->capacity) {
    size_t new_capacity = (*str)->capacity * 2;
    while (new_capacity < new_len + 1) {
      new_capacity *= 2;
    }
    string_resize(str, new_capacity);
  }

  memmove((*str)->data + index + insert_len, (*str)->data + index,
          (*str)->length - index + 1);
  memcpy((*str)->data + index, insert_str, insert_len);
  (*str)->length = new_len;
}

// Function to join an array of const char* strings with a delimiter
string *string_join(const char *strings[], size_t num_strings,
                    const char *delimiter) {
  string *result = string_alloc("");
  for (size_t i = 0; i < num_strings; i++) {
    string_append(&result, strings[i]);

    if (i < num_strings - 1) {
      string_append(&result, delimiter);
    }
  }
  return result;
}

// Function to split a string into an array of substrings using a delimiter
string **string_split(string *str, char delimiter, size_t *num_tokens) {
  size_t tokens_capacity = 8;
  string **tokens = malloc(tokens_capacity * sizeof(string *));
  if (!tokens) {
    *num_tokens = 0;
    return NULL;
  }

  size_t token_count = 0;
  char *token = strtok(str->data, &delimiter);
  while (token != NULL) {
    if (token_count >= tokens_capacity) {
      tokens_capacity *= 2;
      tokens = realloc(tokens, tokens_capacity * sizeof(string *));
      if (!tokens) {
        *num_tokens = 0;
        return NULL;
      }
    }

    tokens[token_count] = string_alloc(token);
    token_count++;
    token = strtok(NULL, &delimiter);
  }

  *num_tokens = token_count;
  return tokens;
}

void substring_free(string **substrings, size_t num_substrings) {
  if (substrings == NULL)
    return;

  for (size_t i = 0; i < num_substrings; i++) {
    if (substrings[i]) {
      free(substrings[i]);
    }
  }
  free(substrings);
}

void string_toupper(string *str) {
  for (size_t i = 0; i < str->length; i++) {
    str->data[i] = toupper(str->data[i]);
  }
}

void string_tolower(string *str) {
  for (size_t i = 0; i < str->length; i++) {
    str->data[i] = tolower(str->data[i]);
  }
}

void string_to_camelcase(string *str) {
  char *data = str->data;
  int dest_index = 0;
  int capitalize = 1;

  while (data[dest_index] != '\0') {
    if (data[dest_index] == ' ' || data[dest_index] == '_') {
      capitalize = 1; // capitalize the next character
    } else if (capitalize) {
      data[dest_index] = toupper(data[dest_index]);
      capitalize = 0; // After capitalizing a character, reset the flag
    }
    dest_index++;
  }

  // Remove spaces and underscores from the string
  int j = 0;
  for (dest_index = 0; data[dest_index] != '\0'; dest_index++) {
    if (data[dest_index] != ' ' && data[dest_index] != '_') {
      data[j] = data[dest_index];
      j++;
    }
  }
  data[j] = '\0';

  // Update the length of the string
  str->length = j;
}

void string_to_titlecase(string *str) {
  char *data = str->data;
  size_t length = str->length;

  if (length > 0) {
    data[0] = toupper(data[0]);
  }

  for (size_t i = 1; i < length; i++) {
    if (data[i - 1] == ' ') {
      data[i] = toupper(data[i]);
    } else {
      data[i] = tolower(data[i]);
    }
  }
}

void string_to_snakecase(string **str) {
  if ((*str)->length == 0) {
    return;
  }

  size_t length = (*str)->length;
  string_resize(str, length * 2 + 1);

  char *data = (*str)->data;

  // Convert first character to lowercase
  data[0] = tolower(data[0]);

  size_t space_count = 0;

  for (size_t i = 1; i < length; i++) {
    // Check if current character is a space
    if (isspace(data[i])) {
      space_count++;
      continue; // Skip spaces
    }

    // Check if current character is uppercase
    if (isupper(data[i])) {
      // Insert underscore before uppercase character
      memmove(&data[i + 1 - space_count], &data[i - space_count],
              length - i + space_count);
      data[i - space_count] = '_';
      length++;

      i++; // Skip the inserted underscore
    }

    // Convert the character to lowercase
    data[i - space_count] = tolower(data[i]);
  }

  // Trim the string to the new length
  data[length - space_count] = '\0';
  (*str)->length = length - space_count;
}

/*
Removes a substring from a string object starting at the specified index
*/
void string_remove(string **s, size_t index, size_t count) {
  if (index >= (*s)->length) {
    return; // Invalid index
  }

  size_t chars_to_remove =
      (index + count > (*s)->length) ? ((*s)->length - index) : count;

  memmove((*s)->data + index, (*s)->data + index + chars_to_remove,
          (*s)->length - index - chars_to_remove + 1);
  (*s)->length -= chars_to_remove;
}

string *string_substr(const string *str, size_t start, size_t length) {
  if (start >= str->length) {
    return NULL; // Invalid start index
  }

  // make sure the requested substring does not extend beyond the end of the
  // original string
  size_t actual_length =
      (start + length > str->length) ? (str->length - start) : length;

  string *substr = string_alloc(str->data + start);
  substr->length = actual_length;
  return substr;
}

void string_reverse(string *s) {
  char *data = s->data;
  size_t length = s->length;

  for (int i = 0; i < length / 2; i++) {
    char temp = data[i];
    data[i] = data[length - i - 1];
    data[length - i - 1] = temp;
  }
}

bool string_startswith(const string *s, const char *prefix) {
  size_t prefix_length = strlen(prefix);
  if (prefix_length > s->length) {
    return false;
  }
  return strncmp(s->data, prefix, prefix_length) == 0;
}

bool string_endswith(const string *s, const char *suffix) {
  size_t suffix_length = strlen(suffix);
  if (suffix_length > s->length) {
    return false;
  }
  return strncmp(s->data + s->length - suffix_length, suffix, suffix_length) ==
         0;
}

// Function to replace the first occurrence of a substring in a string
void string_replace(string **str, const char *find_str,
                    const char *replace_str) {
  size_t find_len = strlen(find_str);
  size_t replace_len = strlen(replace_str);

  char *pos = strstr((*str)->data, find_str);
  if (pos) {
    size_t start_index = pos - (*str)->data;
    size_t new_len = (*str)->length - find_len + replace_len;

    if (replace_len != find_len) {
      string_resize(str, new_len + 1);
    }

    memmove((*str)->data + start_index + replace_len,
            (*str)->data + start_index + find_len,
            (*str)->length - start_index - find_len + 1);
    memcpy((*str)->data + start_index, replace_str, replace_len);
    (*str)->length = new_len;
  }
}

// Function to replace all occurrences of a substring in a string
void string_replace_all(string **str, const char *find_str,
                        const char *replace_str) {
  size_t find_len = strlen(find_str);
  size_t replace_len = strlen(replace_str);

  size_t start_index = 0;
  char *pos = strstr((*str)->data + start_index, find_str);
  while (pos) {
    start_index = pos - (*str)->data;
    size_t new_len = (*str)->length - find_len + replace_len;

    if (replace_len != find_len) {
      string_resize(str, new_len + 1);
    }

    memmove((*str)->data + start_index + replace_len,
            (*str)->data + start_index + find_len,
            (*str)->length - start_index - find_len + 1);
    memcpy((*str)->data + start_index, replace_str, replace_len);
    (*str)->length = new_len;

    start_index += replace_len;
    pos = strstr((*str)->data + start_index, find_str);
  }
}

bool string_match(const string *str, const char *regex) {
  regex_t compiled_regex;

  if (regcomp(&compiled_regex, regex, REG_EXTENDED | REG_NOSUB) != 0) {
    return false; // Failed to compile regex
  }

  int match_result = regexec(&compiled_regex, str->data, 0, NULL, 0);
  regfree(&compiled_regex);
  return match_result == 0;
}

char *regex_sub_match(const char *str, const char *regex, int capture_group) {
  regex_t compiled_regex;
  regmatch_t matches[2];
  int result;

  if (regcomp(&compiled_regex, regex, REG_EXTENDED) != 0) {
    return NULL;
  }

  result = regexec(&compiled_regex, str, 2, matches, 0);
  if (result != 0) {
    regfree(&compiled_regex);
    return NULL;
  }

  if (matches[capture_group].rm_so == -1) {
    regfree(&compiled_regex);
    return NULL;
  }

  int start = matches[capture_group].rm_so;
  int end = matches[capture_group].rm_eo;
  int sub_length = end - start;

  char *sub_match = malloc((sub_length + 1) * sizeof(char));
  if (sub_match == NULL) {
    regfree(&compiled_regex);
    return NULL;
  }

  strncpy(sub_match, str + start, sub_length);
  sub_match[sub_length] = '\0';

  regfree(&compiled_regex);
  return sub_match;
}
