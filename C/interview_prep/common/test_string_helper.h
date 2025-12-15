#ifndef TEST_STRING_HELPER_H
#define TEST_STRING_HELPER_H

/**
 * @brief Generate a random string of given length.
 * @param length Length of string
 * @return Pointer to allocated null-terminated string
 */
char* generate_random_string(int length);

/**
 * @brief Generate empty string ("").
 */
char* generate_edge_case_empty_string(void);

/**
 * @brief Generate a single-character string.
 * @param c Character
 */
char* generate_edge_case_single_char(char c);

/**
 * @brief Free allocated string.
 */
void free_string(char *s);

#endif
