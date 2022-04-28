#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "big_numbers.h"
int getvalue(const char *number)
{
    int result = 0;
    for(int i = 0 ; i < (int)strlen(number) ; i++)
    {
        if(isdigit(*(number + i)))
        {
            result *= 10;
            result += (int)(*(number + i) - '0');
        }
        if(result > 1000)   return result;
    }
    return result;
}
void negate(char **result)
{
    int size1 = 0;
    for(int i = 0 ; i < (int)strlen(*result) ; i++)
    {
        if(isdigit(*(*result + i))) size1++;
    }
    for(int i = size1  ; i > 0 ; i--)
    {
        *(*result + i) = *(*result + i-1);
    }
    **result = '-';
}
int validate(const char *number)
{
    if(!number) return -1;
    if((int)strlen(number) == 1 && (*number >= '0' && *number <= '9'))  return 0;
    if((int)strlen(number) == 1 && (*number < '0' || *number > '9'))  return 2;
    if((*number < '1' || *number > '9') && *number != '-')  return 2;
    if(*number == '-' && *(number + 1) == '0')    return 2;
    for(int i = 1; i < (int)strlen(number) ; i++)
    {
        if(*(number + i) < '0' || *(number + i) > '9')  return 2;
    }
    return 0;
}
int compare(const char* number1, const char* number2)
{
    if(!number1 || !number2)    return 2;
    if(validate(number2) != 0 || validate(number1) != 0)    return 3;
    int negative1 = 0 , negative2 = 0;
    if(*number1 == '-') negative1 = 1;
    if(*number2 == '-') negative2 = 1;
    if(negative1 && negative2)
    {
        if(strlen(number1) == strlen(number2))
        {
            if(*(number1 + 1) == *(number2 + 1))
            {
                for(int i = 2 ; i < (int)strlen(number2) ; i++)
                {
                    if(*(number1 + i) < *(number2 + i)) return 1;
                    if(*(number1 + i) > *(number2 + i)) return -1;
                }
                return 0;
            }
            if(*(number1 + 1) < *(number2 + 1)) return 1;
            if(*(number1 + 1) > *(number2 + 1)) return -1;
        }
        else if(strlen(number1) > strlen(number2))  return -1;
        else if(strlen(number1) < strlen(number2))  return 1;
    }
    if(negative1 && !negative2) return -1;
    if(!negative1 && negative2) return 1;
    if(!negative1 && !negative2)
    {
        if(strlen(number1) == strlen(number2))
        {
            if(*(number1) == *(number2))
            {
                for(int i = 1 ; i < (int)strlen(number2) ; i++)
                {
                    if(*(number1 + i) < *(number2 + i)) return -1;
                    if(*(number1 + i) > *(number2 + i)) return 1;
                }
                return 0;
            }
            if(*(number1) < *(number2)) return -1;
            if(*(number1) > *(number2)) return 1;
        }
        else if(strlen(number1) > strlen(number2))  return 1;
        else if(strlen(number1) < strlen(number2))  return -1;
    }
    return 2;
}
int subtract(const char* number1, const char* number2, char** result)
{
    if (!number1 || !number2 || !result) return 1;
    if (validate(number2) != 0 || validate(number1) != 0) return 2;
    int com = compare(number1, number2);
    int size1 = 0;
    int size2 = 0;
    if (com == 2) return 1;
    if (com == 3) return 2;
    for(int i = 0 ; i < (int)strlen(number1) ; i++) if(isdigit(*(number1 + i))) size1++;
    for(int i = 0 ; i < (int)strlen(number2) ; i++) if(isdigit(*(number2 + i))) size2++;
    if(*number1 == '-' && *number2 == '-')  return subtract(number2 + 1,number1 + 1,result);
    if(*number1 == '-' && *number2 != '-')
    {
        int res = add(number2,number1 + 1,result);
        if(res == 0)
        {
            negate(result);
            return res;
        }
        return res;
    }
    if(*number1 != '-' && *number2 == '-')  return add(number1,number2 + 1,result);
    if(com == -1)
    {
        int res = subtract(number2,number1,result);
        if(res == 0)
        {
            negate(result);
            return res;
        }
        return res;
    }
    if(com == 0)
    {
        *result = malloc(2 * sizeof(char));
        if(!*result)    return 3;
        **result = '0';
        *(*result + 1) = '\0';
        return 0;
    }
    if (size1 >= size2) {
        *result = calloc((size1 + 3), sizeof(char));
        if (!*result) return 3;
    } else{
        *result = calloc((size2 + 3), sizeof(char));
        if (!*result) return 3;
    }
    int i;
    if(size1 == size2)
    {
        int sum = 0;
        int dalej = 0;
        for(i = 0 ; i < size1  ; i++)
        {
            sum = (int)(*(number1 + size1 - i - 1) - '0') - (int)(*(number2 + size2 - i - 1) - '0') - dalej;
            if(sum < 0)
            {
                dalej = 1;
                sum = 10 + sum;
            }else   dalej = 0;
            *(*result + i) = sum + '0';
        }
    }
    if(size1 > size2 && size1 > 0 && size2 > 0)
    {
        int sum = 0;
        int dalej = 0;
        for(i = 0 ; i < size1  ; i++)
        {
            if(i >= size2)
            {
                sum = (int)(*(number1 + size1 - i - 1) - '0')  - dalej;
                if(sum < 0)
                {
                    dalej = 1;
                    sum = 10 + sum;
                }else   dalej = 0;
                *(*result + i) = sum + '0';
            }else{
                sum = (int)(*(number1 + size1 - i - 1) - '0') - (int)(*(number2 + size2 - i - 1) - '0') - dalej;
                if(sum < 0)
                {
                    dalej = 1;
                    sum = 10 + sum;
                }else   dalej = 0;
                *(*result + i) = sum + '0';
            }
        }
    }
    int k;
    for(k = size1 + 2; k > 0  ; k--)
    {
        if(isdigit(*(*result + k))==0 || *(*result + k) == '0') *(*result + k) = '\0';
        else break;
    }
    for(int j = 0 ; j <= k/2 ; j++)
    {
        char temp = *(*result + j);
        *(*result + j) = *(*result +k - j);
        *(*result + k- j) = temp;
    }
    return 0;
}
int add(const char* number1, const char* number2, char** result)
{
    if (!number1 || !number2 || !result) return 1;
    if (validate(number2) != 0 || validate(number1) != 0) return 2;
    int com = compare(number1, number2);
    if(com == -1) return add(number2,number1,result);
    int size1 = 0;
    int size2 = 0;
    if (com == 2) return 1;
    if (com == 3) return 2;
    for(int i = 0 ; i < (int)strlen(number1) ; i++)
    {
        if(isdigit(*(number1 + i))) size1++;
    }
    for(int i = 0 ; i < (int)strlen(number2) ; i++)
    {
        if(isdigit(*(number2 + i))) size2++;
    }
    if(*number1 == '-' && *number2 == '-')
    {
        int res = add(number2+1,number1+1,result);
        if(res == 0)
        {
            negate(result);
            return res;
        }
        return res;
    }
    if(*number1 == '-' && *number2 != '-')  return subtract(number2,number1 + 1,result);
    if(*number1 != '-' && *number2 == '-')  return subtract(number1,number2 + 1,result);
    if (size1 >= size2) {
        *result = calloc((size1 + 3), sizeof(char));
        if (!*result) return 3;
    } else {
        *result = calloc((size2 + 3), sizeof(char));
        if (!*result) return 3;
    }
    int i;
    if(size1 == size2)
    {
        int sum = 0;
        int dalej = 0;
        for(i = 0 ; i <= (int)strlen(number1) + 2 ; i++)
        {
            if(i >= size2)
            {
                if(dalej > 0)
                {
                    *(*result + i) = dalej + '0';
                }
                break;
            }
            else{
                sum = *(number1 + size1 - i - 1) - '0' + *(number2 + size2 - i - 1) - '0' + dalej;
                if(sum >= 10)
                {
                    dalej = sum / 10;
                    sum = sum % 10;
                }else   dalej = 0;
                *(*result + i) = sum + '0';
            }
        }
    }
    if(size1 > size2)
    {
        int sum = 0;
        int dalej = 0;
        for(i = 0 ; i < size1  ; i++)
        {
            if(i >= size2)
            {
                sum = *(number1 + size1 - i - 1) - '0'  + dalej;
                if(sum >= 10)
                {
                    dalej = sum / 10;
                    sum = sum % 10;
                }else dalej = 0;
                *(*result + i) = sum + '0';
            }
            else{
                sum = *(number1 + size1 - i - 1) - '0' + *(number2 + size2 - i - 1) - '0' + dalej;
                if(sum >= 10)
                {
                    dalej = sum / 10;
                    sum = sum % 10;
                }else   dalej = 0;
                *(*result + i) = sum + '0';
            }
        }
        if(dalej > 0)
        {
            *(*result + i) = dalej + '0';
        }
    }
    int k;
    for(k = size1 + 2; k > 0  ; k--)
    {
        if(isdigit(*(*result + k))==0) *(*result + k) = '\0';
        else break;
    }
    for(int j = 0 ; j <= k/2 ; j++)
    {
        char temp = *(*result + j);
        *(*result + j) = *(*result +k - j);
        *(*result + k- j) = temp;
    }
    return 0;
}

int create(struct big_numbers_t *bn, int capacity)
{
    if(!bn || capacity < 1) return 1;
    bn->big_number = malloc(capacity* sizeof(char*));
    if(!bn->big_number)
    {
        bn = NULL;
        return 2;
    }
    for(int i = 0 ; i < capacity ; i++)
    {
        *(bn->big_number + i) = NULL;
    }
    bn->capacity = capacity;
    bn->size = 0;
    return 0;
}
int create_big_numbers(struct big_numbers_t **bn, int capacity)
{
    if(!bn || capacity < 1) return 1;
    *bn = malloc(sizeof(struct big_numbers_t));
    if(!*bn) return 2;
    int ret = create(*bn,capacity);
    if(ret != 0)
    {
        free(*bn);
        *bn = NULL;
        return 2;
    }
    return 0;
}
void destroy(struct big_numbers_t *bn)
{
    if(bn == NULL)    return;
    if(bn->size > 0 && bn->big_number != NULL || bn->size <= bn->capacity)
    {
        for(int i = bn->size - 1 ; i >=0  ; i--)
        {
            if(*(bn->big_number + i) != NULL)
            {
                free(*(bn->big_number+ i) );
            }
        }
    }
    if(bn->big_number != NULL)
    {
        free(bn->big_number);
        bn->big_number = NULL;
    }
}
void destroy_big_numbers(struct big_numbers_t **bn)
{
    if(!(*bn)->big_number || !*bn || (*bn)->size < 0 || (*bn)->capacity < 0 || (*bn)->size > (*bn)->capacity) return;
    if((*bn)->size > 0 && (*bn)->big_number != NULL || (*bn)->size <= (*bn)->capacity)
    {
        for(int i = (*bn)->size - 1 ; i >=0  ; i--)
        {
            if(*((*bn)->big_number + i) != NULL)
            {
                free(*((*bn)->big_number+ i) );
            }
        }
    }
    if((*bn)->big_number != NULL)
    {
        free((*bn)->big_number);
        (*bn)->big_number = NULL;
    }
    free(*bn);
}

int add_big_number(struct big_numbers_t *bn, const char *big_number)
{
    if(!bn || !big_number || strlen(big_number) < 1 || bn->size < 0 || bn->capacity < 0 || !bn->big_number)  return 1;
    if(validate(big_number) != 0)  return 1;
    if(bn->size >= bn->capacity) return 3;
    *(bn->big_number+bn->size) = malloc(((int)strlen(big_number)+1));
    if(!*(bn->big_number+bn->size)) return 2;
    if(!memmove(*(bn->big_number+bn->size),big_number, strlen(big_number)))
    {
        free(*(bn->big_number+bn->size));
        return 2;
    }
    *(*(bn->big_number+bn->size) + strlen(big_number)) = '\0';
    bn->size++;
    return 0;
}

void display(const struct big_numbers_t *bn)
{
    if(bn && bn->big_number && bn->capacity > 0 && bn->size > 0 && bn->size <= bn->capacity)
    {
        int sum = 0;
        for(int i = 0 ; i < bn->capacity ; i++)
        {
            if(*(bn->big_number + i)!=NULL)
            {
                if(validate(*(bn->big_number + i)) == 0) sum++;
            }
        }
        if(sum > bn->capacity)  return;
        if(sum < bn->size)  return;
        for(int i = 0 ; i < bn->size ; i++)
        {
            if(i == sum - 1)
            {
                for(int j = 0 ; j < (int)strlen(*(bn->big_number + i)) ; j++)   printf("%c",*(*(bn->big_number + i)+j));
            } else{
                for(int j = 0 ; j < (int)strlen(*(bn->big_number + i)) ; j++)   printf("%c",*(*(bn->big_number + i)+j));
                printf("\n");
            }

        }
    }
}
int multiply(const char* number1, const char* number2, char** result)
{
    if (!number1 || !number2 || !result) return 1;
    if (validate(number2) != 0 || validate(number1) != 0) return 2;
    int com = compare(number1, number2);
    if (com == 2) return 1;
    if (com == 3) return 2;
    int times = getvalue(number2);
    int times1 = getvalue(number1);
    if(times == 0 || times1 == 0)
    {
        *result = malloc(2 * sizeof(char));
        if(!*result)    return 3;
        **result = '0';
        *(*result + 1) = '\0';
        return 0;
    }
    if(com == -1)   return multiply(number2,number1,result);
    int size1 = 0;
    int size2 = 0;
    for(int i = 0 ; i < (int)strlen(number1) ; i++)
    {
        if(isdigit(*(number1 + i))) size1++;
    }
    for(int i = 0 ; i < (int)strlen(number2) ; i++)
    {
        if(isdigit(*(number2 + i))) size2++;
    }

    if(*number1 == '-' && *number2 == '-')  return multiply(number2+1,number1+1,result);
    if(*number1 == '-' && *number2 != '-')
    {
        int res = multiply(number1 + 1,number2,result);
        if(res == 0)
        {
            negate(result);
            return res;
        }
        return res;
    }
    if(*number1 != '-' && *number2 == '-')
    {
        int res = multiply(number1,number2+1,result);
        if(res == 0)
        {
            negate(result);
            return res;
        }
        return res;
    }


    *result = calloc((size1 + size2 + 3), sizeof(char));
    if (!*result) return 3;
    if(times == 1)
    {
        if(strcpy(*result,number1)!=NULL)   return 0;
        else  return 3;
    }
    for(int i = 0 ; i < size1 ; i++)
    {
        int temp;
        for(int j = 0 ; j < size2 ; j++)
        {
            *(*result + i + j) = *(*result + i + j) + ((*(number2 + size2 - j - 1) - '0') * (*(number1 + size1 - i - 1) - '0'));
            temp = (*(*result + i + j))/10;
            *(*result + i + j) = (*(*result + i + j))%10;
            *(*result + i + 1 + j) += temp;
        }
    }
    int i;
    for(i = 0 ; i <= size2 + size1 ; i++)
    {
        *(*result + i) += '0';
    }
    int k;
    for(k = size1 + size2 + 2; k >= 0  ; k--)
    {
        if(isdigit(*(*result + k))==0 || *(*result + k) == '0') *(*result + k) = '\0';
        else break;
    }
    for(int j = 0 ; j <= k/2 ; j++)
    {
        char temp = *(*result + j);
        *(*result + j) = *(*result +k - j);
        *(*result + k- j) = temp;
    }
    return 0;
}
int validate_expression(const char *expr)
{
    if(!expr)   return 2;
    if(strlen(expr) == 0)   return 1;
    for(int i = 0 ; i < (int)strlen(expr) ; i++)
    {
        if(!isdigit(*(expr + i)))
        {
            if((i == 0 && *(expr + i) != '-') || i == (int)strlen(expr)-1)   return 1;
            if(*(expr + i) == '+' || *(expr + i) == '-' || *(expr + i) == '*')
            {
                if(*(expr + i + 1) == '-')
                {if(!isdigit(*(expr + i + 2)))   return 1;}
                else if(!isdigit(*(expr + i + 1)))    return 1;
            }else  return 1;
        }
    }
    return 0;
}
int calculate(const char* expr, char **result)
{
    if(!expr || !result)    return 1;
    if(validate_expression(expr))   return 2;
    char *num1 = malloc(501);
    if(!num1)   return 3;
    char *num2 = malloc(501);
    if(!num2)
    {
        free(num1);
        return 3;
    }
    int negative1 = 0;
    int pos;
    int ret;
    int zaalokowane = 0;
    char *mod_expr = malloc((int)strlen(expr) + 1);
    if(!mod_expr)
    {
        free(num1);
        free(num2);
        return 3;
    }
    strcpy(mod_expr,expr);
    *(mod_expr + strlen(mod_expr)) = '\0';
    if(*expr == '-')  negative1 = 1;
    char *num = strtok(mod_expr,"+-*");
    strcpy(num1,num);
    if(negative1)
    {
        for(pos = 1 ; pos < (int) strlen(expr) ; pos++)
        {
            if(!isdigit(*(expr + pos)))break;
        }
    }
    else
    {
        for(pos = 0 ; pos < (int) strlen(expr) ; pos++)
        {
            if(!isdigit(*(expr + pos)))break;
        }
    }
    if(negative1 == 1)   negate(&num1);
    *(num1 + pos) = '\0';
    int i;
    for(i = 0 ; i < (int) strlen(expr) ; i++)
    {
        if(pos >= (int) strlen(expr))
        {
            if(i == 0)
            {
                *result = calloc(strlen(expr)+1,1);
                if(!*result)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 3;
                }
                if(!strncpy(*result,expr,strlen(expr)))
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 3;
                }
            }
            free(num1);
            free(num2);
            free(mod_expr);
            return 0;
        }
        if(zaalokowane == 1)
        {
            free(*result);
            zaalokowane = 0;
        }
        if(*(expr + pos) == '-')
        {
            pos++;
            if(*(expr + pos)=='-')
            {
                pos++;
                num = strtok(NULL,"+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2,num);
                for(; pos < (int) strlen(expr) ; pos++)
                {
                    if(!isdigit(*(expr + pos)))break;
                }
                ret = add(num1,num2,result);
                if(ret == 3)
                {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
            else {
                num = strtok(NULL, "+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2, num);
                for (; pos < (int) strlen(expr); pos++) {
                    if (!isdigit(*(expr + pos)))break;
                }
                ret = subtract(num1, num2, result);
                if (ret == 3) {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
        }
        else if(*(expr + pos) == '+')
        {
            pos++;
            if(*(expr + pos)=='-')
            {
                pos++;
                num = strtok(NULL,"+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2,num);
                for(; pos < (int) strlen(expr) ; pos++)
                {
                    if(!isdigit(*(expr + pos)))break;
                }
                ret = subtract(num1,num2,result);
                if(ret == 3)
                {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
            else {
                num = strtok(NULL, "+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2, num);
                for (; pos < (int) strlen(expr); pos++) {
                    if (!isdigit(*(expr + pos)))break;
                }
                ret = add(num1, num2, result);
                if (ret == 3) {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
        }
        else if(*(expr + pos) == '*')
        {
            pos++;
            if(*(expr + pos)=='-')
            {
                pos++;
                num = strtok(NULL,"+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2,num);
                for(; pos < (int) strlen(expr) ; pos++)
                {
                    if(!isdigit(*(expr + pos)))break;
                }
                if(negative1 == 1)  ret = multiply(num1+1,num2,result);
                else ret = multiply(num1,num2,result);
                if(ret == 3)
                {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if(negative1 == 0) negate(result);
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
            else {
                num = strtok(NULL, "+-*");
                if(!num)
                {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    return 0;
                }
                strcpy(num2, num);
                for (; pos < (int) strlen(expr); pos++) {
                    if (!isdigit(*(expr + pos)))break;
                }
                ret = multiply(num1, num2, result);
                if (ret == 3) {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                if (ret == 2 || ret == 1) {
                    free(num2);
                    free(num1);
                    free(mod_expr);
                    return 3;
                }
                free(num1);
                num1 = malloc(2500);
                if(!num1)
                {
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                free(num2);
                num2 = calloc(202,1);
                if(!num2)
                {
                    free(num1);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                if (!strcpy(num1, *result)) {
                    free(num1);
                    free(num2);
                    free(mod_expr);
                    free(*result);
                    return 3;
                }
                zaalokowane = 1;
            }
        }
        if(*num1 == '-')    negative1 = 1;
        else negative1 = 0;
    }
    free(num1);
    free(num2);
    free(mod_expr);
    return 0;
}