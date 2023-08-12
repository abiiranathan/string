#include "string.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void test_string_init() {
  string *str = string_alloc("Hello");
  assert(str);
  printf("Str: %s\n", str->data);
  printf("Length: %zu\n", str->length);
  string_destroy(str);
}

void test_str_concat() {
  string *str1 = string_alloc("Hello");
  string_append(&str1, " World");

  assert(strcmp(str1->data, "Hello World") == 0);
  string_destroy(str1);
}

void test_str_length() {
  string *str = string_alloc("Hello");
  assert(str->length == 5);
  string_destroy(str);
}

void test_str_at() {
  string *str = string_alloc("Hello");
  char c = string_get_char(str, 2);
  assert(c != '\0');

  printf("Character at index 2: %c\n", c);
  assert(c == 'l');
  string_destroy(str);
}

void test_str_contains() {
  string *str = string_alloc("Hello, World!");
  assert(string_contains(str, "World"));
  string_destroy(str);
}

void test_str_is_empty() {
  string *str = string_alloc("");
  assert(str->length == 0);
  string_destroy(str);
}

void test_str_find() {
  string *str = string_alloc("Hello, World!");
  int index = string_find(str, "World");
  printf("Substring 'World' found at index: %d\n", index);
  assert(index == 7);
  string_destroy(str);
}

void test_str_to_upper() {
  string *str = string_alloc("hello");
  string_toupper(str);
  printf("Uppercase string: %s\n", str->data);
  assert(strcmp(str->data, "HELLO") == 0);
  string_destroy(str);
}

void test_str_to_lower() {
  string *str = string_alloc("HELLO");

  string_tolower(str);
  printf("Lowercase string: %s\n", str->data);
  assert(strcmp(str->data, "hello") == 0);
  string_destroy(str);
}

void test_str_split() {
  string *str = string_alloc("Hello,World,OpenAI");

  const char delimiter = ',';
  size_t num_substrings = 0;
  string **substrings = string_split(str, delimiter, &num_substrings);
  printf("Number of substrings: %ld\n", num_substrings);

  for (int i = 0; i < num_substrings; i++) {
    printf("Split Substring %d -> : %s\n", i, substrings[i]->data);
  }

  substring_free(substrings, num_substrings);
  string_destroy(str);
}

void test_str_match() {
  string *str = string_alloc("Hello, World!");
  bool matches = string_match(str, "Hello.*");
  printf("Matches regex: %s\n", matches ? "true" : "false");
  assert(matches);
  string_destroy(str);
}

void test_str_replace() {
  string *str = string_alloc("Hello, World!");

  string_replace(&str, "World", "John");
  printf("Replaced string: %s\n", str->data);
  assert(strcmp(str->data, "Hello, John!") == 0);
  string_destroy(str);
}

void test_str_replace_all() {
  string *str = string_alloc("Hello, World!");
  string_replace_all(&str, "o", "x");

  printf("Replaced string: %s\n", str->data);
  assert(strcmp(str->data, "Hellx, Wxrld!") == 0);
  string_destroy(str);
}

void test_str_to_camel_case() {
  string *str = string_alloc("hello world my_Dear_friends");

  string_to_camelcase(str);
  printf("Camel case string: %s\n", str->data);
  assert(strcmp(str->data, "HelloWorldMyDearFriends") == 0);
  string_destroy(str);
}

void test_str_to_titlecase() {
  string *str = string_alloc("hello world");
  assert(str);

  string_to_titlecase(str);
  printf("Title case string: %s\n", str->data);
  assert(strcmp(str->data, "Hello World") == 0);
  string_destroy(str);
}

void test_str_to_snakecase() {
  string *str = string_alloc("Hello World MyDearFriends");
  assert(str);
  string_to_snakecase(&str);

  printf("Snake case string: %s\n", str->data);
  assert(strcmp(str->data, "hello_world_my_dear_friends") == 0);

  string_destroy(str);
}

void test_str_insert() {
  string *str = string_alloc("Hello!");

  string_insert(&str, 5, " World");
  printf("Inserted string: %s\n", str->data);
  assert(strcmp(str->data, "Hello World!") == 0);

  string_destroy(str);
}

void test_str_remove() {
  string *str = string_alloc("Hello, World!");

  string_remove(&str, 5, 7);

  printf("Removed string: %s\n", str->data);
  assert(strcmp(str->data, "Hello!") == 0);
  assert(str->length == 6);
  string_destroy(str);
}

void test_str_join() {
  const char *substrings[3] = {"Hello", "World", "Uganda"};
  int count = 3;
  char *delimiter = "-";

  string *str = string_join(substrings, count, delimiter);

  printf("Joined string: %s\n", str->data);
  assert(strcmp(str->data, "Hello-World-Uganda") == 0);
  string_destroy(str);
}

void test_str_substring() {
  string *str = string_alloc("Hello, World!");
  string *s = string_substr(str, 7, 5);

  printf("Substring: %s\n", s->data);
  string_destroy(s);

  assert(strcmp(str->data, "Hello, World!") == 0);
  string_destroy(str);
}

void test_str_reverse() {
  string *str = string_alloc("Hello, World!");
  string_reverse(str);

  printf("Reversed string: %s\n", str->data);
  assert(strcmp(str->data, "!dlroW ,olleH") == 0);
  string_destroy(str);
}

void test_str_startswith() {
  string *str = string_alloc("Hello, World!");
  bool result1 = string_startswith(str, "Hello");
  bool result2 = string_startswith(str, "World");

  printf("Starts with 'Hello': %d\n", result1);
  printf("Starts with 'World': %d\n", result2);
  assert(result1);
  assert(!result2);

  string_destroy(str);
}

void test_str_endswith() {
  string *str = string_alloc("Hello, World!");

  bool result1 = string_endswith(str, "World!");
  bool result2 = string_endswith(str, "Hello");

  printf("Ends with 'World!': %d\n", result1);
  printf("Ends with 'Hello': %d\n", result2);
  assert(result1);
  assert(!result2);
  string_destroy(str);
}

void test_regex_sub_match() {
  const char *str1 = "Hello, World!";
  const char *regex1 = "Hello, (\\w+)!";
  int capture_group1 = 1;

  char *sub_match1 = regex_sub_match(str1, regex1, capture_group1);
  assert(sub_match1 != NULL);
  assert(strcmp(sub_match1, "World") == 0);
  free(sub_match1);

  const char *str2 = "Hello, Uganda!";
  const char *regex2 = "Hello, (\\w+)!";

  int capture_group2 = 1;
  char *sub_match2 = regex_sub_match(str2, regex2, capture_group2);

  assert(sub_match2 != NULL);
  assert(strcmp(sub_match2, "Uganda") == 0);
  free(sub_match2);
}

void test_string_trimspace() {
  // Test string_trimspace
  {
    string *str = string_alloc("   Hello, World!   ");
    assert(str);

    string_trimspace(str);
    printf("\"%s\"\n", str->data);
    assert(strcmp(str->data, "Hello, World!") == 0);

    string_destroy(str);
  }

  // Test string_ltrimspace
  {
    string *str = string_alloc("   Hello, World!   ");
    assert(str);

    string_ltrimspace(str);
    printf("\"%s\"\n", str->data);

    assert(strcmp(str->data, "Hello, World!   ") == 0);

    string_destroy(str);
  }

  // Test string_rtrimspace
  {
    string *str = string_alloc("   Hello, World!   ");
    assert(str);

    string_rtrimspace(str);
    printf("\"%s\"\n", str->data);

    assert(strcmp(str->data, "   Hello, World!") == 0);

    string_destroy(str);
  }
}

int main() {
  test_string_init();
  test_str_concat();
  test_str_length();
  test_str_at();
  test_str_contains();
  test_str_is_empty();
  test_str_find();
  test_str_replace();
  test_str_to_upper();
  test_str_to_lower();
  test_str_split();
  test_str_match();
  test_str_replace_all();
  test_str_to_camel_case();
  test_str_to_titlecase();
  test_str_to_snakecase();
  test_str_insert();
  test_str_remove();
  test_str_join();
  test_str_substring();
  test_str_reverse();
  test_str_startswith();
  test_str_endswith();
  test_regex_sub_match();
  test_string_trimspace();
  return 0;
}
