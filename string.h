#ifndef __STRING_H__
#define __STRING_H__

#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Represents a flexible string structure.
 */
typedef struct string {
  size_t length;   /**< Current length of the string. */
  size_t capacity; /**< Capacity of the allocated memory. */
  char data[];     /**< Flexible array member to hold the string data. */
} string;

/**
 * @brief Allocate and initialize a new string with the given initial data.
 *
 * @param initial_data The initial data for the string.
 * @return A pointer to the allocated string structure.
 */
string *string_alloc(const char *initial_data);

/**
 * @brief Resize the capacity of the string to the given new capacity.
 *
 * @param str Pointer to the pointer of the string structure.
 * @param new_capacity The new capacity to resize the string to.
 */
void string_resize(string **str, size_t new_capacity);

/**
 * @brief Destroy and free the memory allocated for the string.
 *
 * @param str Pointer to the string structure to be destroyed.
 */
void string_destroy(string *str);

/**
 * @brief Append the specified string to the end of the string.
 *
 * @param str Pointer to the pointer of the string structure.
 * @param append_str The string to append.
 */
void string_append(string **str, const char *append_str);

/**
 * @brief Clear the contents of the string, setting its length to 0.
 *
 * @param str Pointer to the string structure to be cleared.
 */
void string_clear(string *str);

/**
 * @brief Get the character at the specified index in the string.
 *
 * @param str Pointer to the string structure.
 * @param index The index of the character to retrieve.
 * @return The character at the given index.
 */
char string_get_char(const string *str, size_t index);

/**
 * @brief Find the first occurrence of a substring within the string.
 *
 * @param str Pointer to the string structure.
 * @param sub_str The substring to search for.
 * @return The index of the first occurrence of the substring, or -1 if not
 * found.
 */
ssize_t string_find(const string *str, const char *sub_str);

/**
 * @brief Perform regular expression matching and return the matched capture
 * group.
 *
 * @param str The input string to perform matching on.
 * @param regex The regular expression pattern to match.
 * @param capture_group The index of the capture group to retrieve.
 * @return The matched capture group, or NULL if not found.
 */
char *regex_sub_match(const char *str, const char *regex, int capture_group);

/**
 * @brief Check if the string contains a specific substring.
 *
 * @param str Pointer to the string structure.
 * @param substring The substring to check for.
 * @return True if the substring is found, false otherwise.
 */
bool string_contains(const string *str, const char *substring);

/**
 * @brief Insert the specified string at the given index within the string.
 *
 * @param str Pointer to the pointer of the string structure.
 * @param index The index at which to insert the string.
 * @param insert_str The string to insert.
 */
void string_insert(string **str, size_t index, const char *insert_str);

/**
 * @brief Convert all characters in the string to uppercase.
 *
 * @param str Pointer to the string structure to be converted.
 */
void string_toupper(string *str);

/**
 * @brief Convert all characters in the string to lowercase.
 *
 * @param str Pointer to the string structure to be converted.
 */
void string_tolower(string *str);

/**
 * @brief Convert the string to camel case format.
 *
 * @param str Pointer to the string structure to be converted.
 */
void string_to_camelcase(string *str);

/**
 * @brief Convert the first letter of each word to uppercase, making the string
 * title case.
 *
 * @param str Pointer to the string structure to be converted.
 */
void string_to_titlecase(string *str);

/**
 * @brief Convert the string to snake case format.
 *
 * @param str Pointer to the pointer of the string structure.
 */
void string_to_snakecase(string **str);

/**
 * @brief Remove a specified number of characters from the string, starting from
 * the given index.
 *
 * @param s Pointer to the pointer of the string structure.
 * @param index The starting index of removal.
 * @param count The number of characters to remove.
 */
void string_remove(string **s, size_t index, size_t count);

/**
 * @brief Reverse the characters in the string.
 *
 * @param s Pointer to the string structure to be reversed.
 */
void string_reverse(string *s);

/**
 * @brief Replace the first occurrence of a substring with another string.
 *
 * @param str Pointer to the pointer of the string structure.
 * @param find_str The substring to find.
 * @param replace_str The string to replace the substring with.
 */
void string_replace(string **str, const char *find_str,
                    const char *replace_str);

/**
 * @brief Replace all occurrences of a substring with another string.
 *
 * @param str Pointer to the pointer of the string structure.
 * @param find_str The substring to find.
 * @param replace_str The string to replace the substring with.
 */
void string_replace_all(string **str, const char *find_str,
                        const char *replace_str);

/**
 * @brief Join an array of strings using a specified delimiter.
 *
 * @param strings An array of strings to be joined.
 * @param num_strings The number of strings in the array.
 * @param delimiter The delimiter to use between joined strings.
 * @return A newly allocated string containing the joined strings.
 */
string *string_join(const char *strings[], size_t num_strings,
                    const char *delimiter);

/**
 * @brief Split the string into an array of substrings based on a delimiter.
 *
 * @param str Pointer to the string structure to be split.
 * @param delimiter The delimiter character used for splitting.
 * @param num_tokens Pointer to store the number of generated tokens.
 * @return An array of dynamically allocated string pointers.
 */
string **string_split(string *str, char delimiter, size_t *num_tokens);

/**
 * @brief Free the dynamically allocated memory for an array of substrings.
 * May be used to free memory allocated with string_split (as an example)
 *
 * @param substrings An array of string pointers to be freed.
 * @param num_substrings The number of substrings in the array.
 */
void substring_free(string **substrings, size_t num_substrings);

/**
 * @brief Extract a substring from the original string.
 *
 * @param str Pointer to the original string structure.
 * @param start The starting index of the substring.
 * @param length The length of the substring.
 * @return A newly allocated substring.
 */
string *string_substr(const string *str, size_t start, size_t length);

/**
 * @brief Check if the string starts with a specified prefix.
 *
 * @param s Pointer to the string structure.
 * @param prefix The prefix to check.
 * @return True if the string starts with the prefix, false otherwise.
 */
bool string_startswith(const string *s, const char *prefix);

/**
 * @brief Check if the string ends with a specified suffix.
 *
 * @param s Pointer to the string structure.
 * @param suffix The suffix to check.
 * @return True if the string ends with the suffix, false otherwise.
 */
bool string_endswith(const string *s, const char *suffix);

/**
 * @brief Check if the string matches a specified regular expression.
 *
 * @param str Pointer to the string structure.
 * @param regex The regular expression pattern to match.
 * @return True if the string matches the regex, false otherwise.
 */
bool string_match(const string *str, const char *regex);

/** @brief Remove leading and trailing white space from string
 * @param str Pointer to the string structure.
 */
void string_trim(string *str);

/** @brief Remove trailing white space from string
 * @param str Pointer to the string structure.
 */
void string_rtrim(string *str);

/** @brief Remove leading white space from string
 * @param str Pointer to the string structure.
 */
void string_ltrim(string *str);

#endif /* __STRING_H__ */
