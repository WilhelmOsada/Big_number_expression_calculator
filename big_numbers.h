#pragma once
struct big_numbers_t {
    int size;
    int capacity;
    char **big_number;
};
int add(const char* number1, const char* number2, char** result);
int subtract(const char* number1, const char* number2, char** result);
int compare(const char* number1, const char* number2);
void negate(char **result);
int validate(const char *number);
int create(struct big_numbers_t *bn, int capacity);
int create_big_numbers(struct big_numbers_t **bn, int capacity);

void destroy(struct big_numbers_t *bn);
void destroy_big_numbers(struct big_numbers_t **bn);

int add_big_number(struct big_numbers_t *bn, const char *big_number);

void display(const struct big_numbers_t *bn);

int multiply(const char* number1, const char* number2, char** result);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);