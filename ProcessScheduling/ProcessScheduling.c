/**
* @file ProcessScheduling.c
*
* @author Leonardo Vencovsky (https://github.com/LeoVen)
* @date 06/09/2018
*
* Process Queue
*
*/

/* ----------------------------------------------------------------------------------------------------
 *
 *                                                                                         Header Files
 *
 * ---------------------------------------------------------------------------------------------------- */

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define FILE_NAME "process.txt"

/* ---------------------------------------------------------------------------------------------------- Core.h */

#define CLEAR_SCREEN "cls"
//#define CLEAR_SCREEN "clear"

/**
* @brief Status code returned by functions
*
* These status codes are returned by almost all functions in the project.
* They are used to prevent unwanted results when a function fails and can
* also be used by the user to control his/her own program flow.
*
*/
typedef enum Status {
	DS_OK = 0, /**< Returned by a function when all operations were successful */
	DS_ERR_INVALID_POSITION = 1, /**< When an invalid position is passed as argument */
	DS_ERR_INVALID_OPERATION = 2, /**< When an invalid operation is made (e.g. remove element of an empty list ) */
	DS_ERR_INVALID_SIZE = 3, /**< When an invalid size is given */
	DS_ERR_NOT_FOUND = 4, /**< When a search fails to find a value */
	DS_ERR_ALLOC = 5, /**< When a function fails to allocate memory  */
	DS_ERR_UNEXPECTED_RESULT = 6, /**< When an unexpected result happens. Contact developers. */
	DS_ERR_ITER = 7, /**< When an iteration reaches an unexpected value */
	DS_ERR_NULL_POINTER = 8, /**< When a @c NULL parameter is passed to a function */
	DS_ERR_FULL = 9, /**< When a structure reaches its maximum capacity */
	DS_ERR_INVALID_ARGUMENT = 10  /**< When an argument passed is invalid for that operation */
} Status;

char * status_repr(Status status);

void print_status_repr(Status status);

/* ---------------------------------------------------------------------------------------------------- Core.h */

/* ---------------------------------------------------------------------------------------------------- String.h */

#ifndef STRING_SPEC
#define STRING_SPEC

#define STRING_INIT_SIZE 8
#define STRING_GROW_RATE 2

#endif

typedef struct String
{
	char *buffer;		/*!< Character buffer */
	size_t len;			/*!< Word length */
	size_t capacity;	/*!< Buffer capacity */
	size_t growth_rate; /*!< Buffer capacity growth rate */
} String;

Status str_init(String **str);
Status str_make(String **str, char *content);

Status str_get_string(String *str, char **result);

Status str_push_char_front(String *str, char ch);
Status str_push_char_at(String *str, char ch, size_t index);
Status str_push_char_back(String *str, char ch);

Status str_push_front(String *str, char *ch);
Status str_push_at(String *str, char *ch, size_t index);
Status str_push_back(String *str, char *ch);

Status str_prepend(String *str1, String *str2);
Status str_add(String *str1, String *str2, size_t index);
Status str_append(String *str1, String *str2);

Status str_pop_char_front(String *str);
Status str_pop_char_at(String *str, size_t index);
Status str_pop_char_back(String *str);

Status str_display(String *str);
Status str_display_raw(String *str);

Status str_delete(String **str);
Status str_erase(String **str);

Status str_back(String *str, char *result);
Status str_front(String *str, char *result);

size_t str_length(String *str);
size_t str_len(char *ch);

Status str_compare(String *str1, String *str2, int *result);
bool str_greater(String *str1, String *str2);
bool str_equals(String *str1, String *str2);
bool str_lesser(String *str1, String *str2);

bool str_equals_str(String *str, char *string);

Status str_copy(String *str, String **result);
Status str_swap(String **str1, String **str2);

bool str_buffer_full(String *str);
bool str_buffer_empty(String *str);
bool str_buffer_fits(String *str, size_t str_len);

Status str_realloc(String *str);


/* ---------------------------------------------------------------------------------------------------- String.h */

/* ---------------------------------------------------------------------------------------------------- Process.h */

typedef struct Process
{
	struct String *name;
	size_t pid;
	size_t cpu;
	size_t io;
	size_t pri;
} Process;

Status prc_init(Process **prc, String *name, size_t pid, size_t cpu, size_t io, size_t pri);

Status prc_delete(Process **prc);

Status prc_display(Process *prc);

int prc_compare(Process *prc1, Process *prc2);

Status prc_copy(Process *prc, Process **result);

/* ---------------------------------------------------------------------------------------------------- Process.h */

/* ---------------------------------------------------------------------------------------------------- QueueArray.h */

#ifndef QUEUE_ARRAY_SPEC
#define QUEUE_ARRAY_SPEC

#define QUEUE_ARRAY_INIT_SIZE 8
#define QUEUE_ARRAY_GROW_RATE 2
#define QUEUE_T Process*
#define QUEUE_DELETE prc_delete
#define QUEUE_DISPLAY prc_display
#define QUEUE_COMPARATOR prc_compare

#endif

typedef struct QueueArray
{
	QUEUE_T *buffer;	/*!< @c QueueArray data buffer */
	size_t length;		/*!< @c QueueArray length */
	size_t capacity;	/*!< @c QueueArray total capacity */
	size_t growth_rate; /*!< @c QueueArray buffer growth rate */
} QueueArray;

Status qua_init(QueueArray **qua);

Status qua_get_length(QueueArray *qua, size_t *result);
size_t qua_length(QueueArray *qua);

Status qua_enqueue(QueueArray *qua, QUEUE_T value);

Status qua_dequeue(QueueArray *qua, QUEUE_T *value);

Status qua_display(QueueArray *qua);

Status qua_delete(QueueArray **qua); // Erases and sets to NULL
Status qua_erase(QueueArray **qua);  // Erases and inits

bool qua_is_empty(QueueArray *qua);
bool qua_is_full(QueueArray *qua);

//Status qua_copy(QueueArray *qua, QueueArray **result);

Status qua_realloc(QueueArray *qua);


/* ---------------------------------------------------------------------------------------------------- QueueArray.h */

/* ---------------------------------------------------------------------------------------------------- DynamicArray.h */

#ifndef DYNAMIC_ARRAY_SPEC
#define DYNAMIC_ARRAY_SPEC

#define DYNAMIC_ARRAY_INIT_SIZE 8	   /*!< Buffer initial size macro. */
#define DYNAMIC_ARRAY_GROW_RATE 2	   /*!< Buffer growth rate macro. */
#define DS_DAR_T Process *			   /*!< Array type. */
#define DS_DAR_INIT prc_init		   /*!< Init function of array type. */
#define DS_DAR_DELETE prc_delete	   /*!< Delete function of array type. */
#define DS_DAR_DISPLAY prc_display     /*!< Display function of array type. */
#define DS_DAR_COMPARATOR prc_compare  /*!< Comparator function of array type. */

#endif

typedef struct DynamicArray
{
	DS_DAR_T *buffer;   /*!< @c DynamicArray data buffer */
	size_t size;		/*!< @c DynamicArray size */
	size_t capacity;	/*!< @c DynamicArray total capacity */
	size_t growth_rate; /*!< @c DynamicArray buffer growth rate */
} DynamicArray;

Status dar_init(DynamicArray **dar);

Status dar_get(DynamicArray *dar, size_t index, DS_DAR_T *result);

Status dar_insert_front(DynamicArray *dar, DS_DAR_T value);
Status dar_insert_at(DynamicArray *dar, DS_DAR_T value, size_t index);
Status dar_insert_back(DynamicArray *dar, DS_DAR_T value);

Status dar_remove_front(DynamicArray *dar, DS_DAR_T *result);
Status dar_remove_at(DynamicArray *dar, size_t index, DS_DAR_T *result);
Status dar_remove_back(DynamicArray *dar, DS_DAR_T *result);

Status dar_remove_keys(DynamicArray *dar, DS_DAR_T value);

Status dar_display(DynamicArray *darr);

Status dar_delete(DynamicArray **darr);
Status dar_erase(DynamicArray **dar);

size_t dar_cap(DynamicArray *dar);
size_t dar_size(DynamicArray *dar);

bool dar_is_empty(DynamicArray *dar);
bool dar_is_full(DynamicArray *dar);

Status dar_find_max(DynamicArray *dar, DS_DAR_T *result);
Status dar_find_min(DynamicArray *dar, DS_DAR_T *result);
Status dar_find_max_pos(DynamicArray *dar, size_t *result);
Status dar_find_min_pos(DynamicArray *dar, size_t *result);

bool dar_exists(DynamicArray *dar, DS_DAR_T value);

Status dar_realloc(DynamicArray *dar);

/* ---------------------------------------------------------------------------------------------------- DynamicArray.h */

/* ----------------------------------------------------------------------------------------------------
 *
 *                                                                                         Header Files
 *
 * ---------------------------------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------------------------------
*
*                                                                                         Source Files
*
* ---------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------------------------------------- Core.c */

char *status_repr(Status status)
{
	switch (status)
	{
	case DS_OK:
		return "DS_OK";
	case DS_ERR_INVALID_POSITION:
		return "DS_ERR_INVALID_POSITION";
	case DS_ERR_INVALID_OPERATION:
		return "DS_ERR_INVALID_OPERATION";
	case DS_ERR_INVALID_SIZE:
		return "DS_ERR_INVALID_SIZE";
	case DS_ERR_NOT_FOUND:
		return "DS_ERR_NOT_FOUND";
	case DS_ERR_ALLOC:
		return "DS_ERR_ALLOC";
	case DS_ERR_UNEXPECTED_RESULT:
		return "DS_ERR_UNEXPECTED_RESULT";
	case DS_ERR_ITER:
		return "DS_ERR_ITER";
	case DS_ERR_NULL_POINTER:
		return "DS_ERR_NULL_POINTER";
	case DS_ERR_FULL:
		return "DS_ERR_FULL";
	case DS_ERR_INVALID_ARGUMENT:
		return "DS_ERR_INVALID_ARGUMENT";
	default:
		return "DS_UNKNOWN_ERROR";
	}
}

void print_status_repr(Status status)
{
	printf("\n%s", status_repr(status));
}

/* ---------------------------------------------------------------------------------------------------- Core.c */

/* ---------------------------------------------------------------------------------------------------- String.c */

Status str_init(String **str)
{
	(*str) = malloc(sizeof(String));

	if (!(*str))
		return DS_ERR_ALLOC;

	(*str)->buffer = malloc(sizeof(char) * STRING_INIT_SIZE);

	if (!((*str)->buffer))
		return DS_ERR_ALLOC;

	(*str)->buffer[0] = '\0';

	(*str)->capacity = STRING_INIT_SIZE;
	(*str)->growth_rate = STRING_GROW_RATE;

	(*str)->len = 0;

	return DS_OK;
}

Status str_make(String **str, char *string)
{
	size_t length = str_len(string);

	if (length == 0)
		return DS_ERR_INVALID_ARGUMENT;

	Status st = str_init(str);

	if (st != DS_OK)
		return st;

	if ((*str)->capacity <= length)
	{
		size_t new_capacity = STRING_INIT_SIZE;

		while (new_capacity <= length)
		{
			new_capacity *= STRING_GROW_RATE;
		}

		char *new_buffer = realloc((*str)->buffer, sizeof(char) * new_capacity);

		if (!new_buffer)
		{
			(*str)->capacity = STRING_INIT_SIZE;

			return DS_ERR_ALLOC;
		}

		(*str)->buffer = new_buffer;

		(*str)->capacity = new_capacity;
	}

	(*str)->len = length;

	size_t i;
	for (i = 0; i < length; i++)
	{
		(*str)->buffer[i] = string[i];
	}

	(*str)->buffer[length] = '\0';

	return DS_OK;
}

Status str_get_string(String *str, char **result)
{
	(*result) = NULL;

	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	char *string = malloc(sizeof(char) * (str->len + 1));

	if (!string)
		return DS_ERR_ALLOC;

	size_t i;
	for (i = 0; i < str->len; i++)
		string[i] = str->buffer[i];

	string[str->len] = '\0';

	(*result) = string;

	return DS_OK;
}

Status str_push_char_front(String *str, char ch)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	if (str_buffer_full(str))
	{
		st = str_realloc(str);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = str->len; i > 0; i--)
	{
		str->buffer[i] = str->buffer[i - 1];
	}

	str->buffer[0] = ch;

	(str->len)++;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_push_char_at(String *str, char ch, size_t index)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > str->len)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = str_push_char_front(str, ch);

		if (st != DS_OK)
			return st;
	}
	else if (index == str->len)
	{
		st = str_push_char_front(str, ch);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (str_buffer_full(str))
		{
			st = str_realloc(str);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = str->len; i > index; i--)
		{
			str->buffer[i] = str->buffer[i - 1];
		}

		str->buffer[index] = ch;

		(str->len)++;

		str->buffer[str->len] = '\0';
	}

	return DS_OK;
}

Status str_push_char_back(String *str, char ch)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	if (str_buffer_full(str))
	{
		st = str_realloc(str);

		if (st != DS_OK)
			return st;
	}

	str->buffer[str->len] = ch;

	(str->len)++;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_push_front(String *str, char *ch)
{
	if (str == NULL || ch == NULL)
		return DS_ERR_NULL_POINTER;

	size_t len = str_len(ch);

	if (len == 0)
		return DS_ERR_INVALID_ARGUMENT;

	Status st;

	while (!str_buffer_fits(str, len))
	{
		st = str_realloc(str);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = str->len; i > 0; i--)
	{
		str->buffer[i + len - 1] = str->buffer[i - 1];
	}

	for (i = 0; i < len; i++)
	{
		str->buffer[i] = ch[i];
	}

	str->len += len;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_push_at(String *str, char *ch, size_t index)
{
	if (str == NULL || ch == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	if (index == 0)
	{
		st = str_push_front(str, ch);

		if (st != DS_OK)
			return st;
	}
	else if (index == str->len)
	{
		st = str_push_back(str, ch);

		if (st != DS_OK)
			return st;
	}
	else
	{
		size_t len = str_len(ch);

		if (len == 0)
			return DS_ERR_INVALID_ARGUMENT;

		while (!str_buffer_fits(str, len))
		{
			st = str_realloc(str);

			if (st != DS_OK)
				return st;
		}

		size_t i, j;
		for (i = str->len; i >= index; i--)
		{
			str->buffer[i + len] = str->buffer[i];
		}

		for (i = index, j = 0; i < index + len; i++, j++)
		{
			str->buffer[i] = ch[j];
		}

		str->len += len;

		str->buffer[str->len] = '\0';
	}

	return DS_OK;
}

Status str_push_back(String *str, char *ch)
{
	if (str == NULL || ch == NULL)
		return DS_ERR_NULL_POINTER;

	size_t len = str_len(ch);

	if (len == 0)
		return DS_ERR_INVALID_ARGUMENT;

	Status st;

	while (!str_buffer_fits(str, len))
	{
		st = str_realloc(str);

		if (st != DS_OK)
			return st;
	}

	size_t i, j;
	for (i = str->len, j = 0; i < len + str->len; i++, j++)
	{
		str->buffer[i] = ch[j];
	}

	str->len += len;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_prepend(String *str1, String *str2)
{
	if (str1 == NULL || str2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str2))
		return DS_OK;

	Status st;

	while (!str_buffer_fits(str1, str2->len))
	{
		st = str_realloc(str1);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = str1->len; i > 0; i--)
	{
		str1->buffer[i + str2->len - 1] = str1->buffer[i - 1];
	}

	for (i = 0; i < str2->len; i++)
	{
		str1->buffer[i] = str2->buffer[i];
	}

	str1->len += str2->len;

	str1->buffer[str1->len] = '\0';

	return DS_OK;
}

Status str_add(String *str1, String *str2, size_t index)
{
	if (str1 == NULL || str2 == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	if (index == 0)
	{
		st = str_prepend(str1, str2);

		if (st != DS_OK)
			return st;
	}
	else if (index == str1->len)
	{
		st = str_append(str1, str2);

		if (st != DS_OK)
			return st;
	}
	else
	{
		while (!str_buffer_fits(str1, str2->len))
		{
			st = str_realloc(str1);

			if (st != DS_OK)
				return st;
		}

		size_t i, j;
		for (i = str1->len; i >= index; i--)
		{
			str1->buffer[i + str2->len] = str1->buffer[i];
		}

		for (i = index, j = 0; i < index + str2->len; i++, j++)
		{
			str1->buffer[i] = str2->buffer[j];
		}

		str1->len += str2->len;

		str1->buffer[str1->len] = '\0';
	}

	return DS_OK;
}

Status str_append(String *str1, String *str2)
{
	if (str1 == NULL || str2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str2))
		return DS_OK;

	Status st;

	while (!str_buffer_fits(str1, str2->len))
	{
		st = str_realloc(str1);

		if (st != DS_OK)
			return st;
	}

	size_t i, j;
	for (i = str1->len, j = 0; i < str1->len + str2->len; i++, j++)
	{
		str1->buffer[i] = str2->buffer[j];
	}

	str1->len += str2->len;

	str1->buffer[str1->len] = '\0';

	return DS_OK;
}

Status str_pop_char_front(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < str->len; i++)
	{
		str->buffer[i] = str->buffer[i + 1];
	}

	(str->len)--;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_pop_char_at(String *str, size_t index)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	if (index >= str->len)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = str_pop_char_front(str);

		if (st != DS_OK)
			return st;
	}
	else if (index == str->len - 1)
	{
		st = str_pop_char_back(str);

		if (st != DS_OK)
			return st;
	}
	else
	{
		size_t i;
		for (i = index; i < str->len; i++)
		{
			str->buffer[i] = str->buffer[i + 1];
		}

		(str->len)--;

		str->buffer[str->len] = '\0';
	}

	return DS_OK;
}

Status str_pop_char_back(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	(str->len)--;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

Status str_display(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
	{
		printf("\nString\n[ empty ]\n");
		return DS_OK;
	}

	printf("\nString\n%s\n", str->buffer);

	return DS_OK;
}

Status str_display_raw(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (str_buffer_empty(str))
		return DS_OK;

	printf("%s", str->buffer);

	return DS_OK;
}

Status str_delete(String **str)
{
	if ((*str) == NULL)
		return DS_ERR_NULL_POINTER;

	free((*str)->buffer);

	free(*str);

	*str = NULL;

	return DS_OK;
}

Status str_erase(String **str)
{
	if ((*str) == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = str_delete(str);

	if (st != DS_OK)
		return st;

	st = str_init(str);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

Status str_clear(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	str->len = 0;

	str->buffer[0] = '\0';

	return DS_OK;
}

Status str_front(String *str, char *result)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	*result = str->buffer[0];

	return DS_OK;
}

Status str_back(String *str, char *result)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_buffer_empty(str))
		return DS_ERR_INVALID_OPERATION;

	*result = str->buffer[str->len - 1];

	return DS_OK;
}

size_t str_length(String *str)
{
	if (str == NULL)
		return 0;

	return str->len;
}

size_t str_len(char *ch)
{
	char *h = ch;

	while (*ch)
		++ch;

	return ch - h;
}

Status str_compare(String *str1, String *str2, int *result)
{
	if (str1 == NULL || str2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (str_greater(str1, str2))
		*result = 1;
	else if (str_lesser(str1, str2))
		*result = -1;
	else
		*result = 0;

	return DS_OK;
}

bool str_greater(String *str1, String *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;

	size_t i, len = (str1->len > str2->len) ? str2->len : str1->len;

	for (i = 0; i < len; i++)
	{
		if (str1->buffer[i] - str2->buffer[i] < 0)
			return true;
		else if (str1->buffer[i] - str2->buffer[i] > 0)
			return false;
	}

	if (str1->len > str2->len)
		return true;

	return false;
}

bool str_equals(String *str1, String *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;

	if (str1->len != str2->len)
		return false;

	size_t i;
	for (i = 0; i < str1->len; i++)
		if (str1->buffer[i] != str2->buffer[i])
			return false;

	return true;
}

bool str_lesser(String *str1, String *str2)
{
	if (str1 == NULL || str2 == NULL)
		return false;

	size_t i, len = (str1->len > str2->len) ? str2->len : str1->len;

	for (i = 0; i < len; i++)
	{
		if (str1->buffer[i] - str2->buffer[i] > 0)
			return true;
		else if (str1->buffer[i] - str2->buffer[i] < 0)
			return false;
	}

	if (str1->len < str2->len)
		return false;

	return true;
}

bool str_equals_str(String *str, char *string)
{
	if (str == NULL || string == NULL)
		return false;

	size_t len = str_len(string);

	if (str->len != len)
		return false;

	size_t i;
	for (i = 0; i < len; i++)
		if (str->buffer[i] != string[i])
			return false;

	return true;
}

Status str_copy(String *str, String **result)
{
	*result = NULL;

	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = str_init(result);

	if (st != DS_OK)
		return st;

	while (!str_buffer_fits(*result, str->len))
	{
		st = str_realloc(*result);

		if (st != DS_OK)
			return st;
	}

	char *s1 = str->buffer, *s2 = (*result)->buffer;

	while (*s2++ = *s1++);

	(*result)->len = str->len;

	return DS_OK;
}

Status str_swap(String **str1, String **str2)
{
	String *temp = (*str1);

	(*str1) = (*str2);
	(*str2) = temp;

	return DS_OK;
}

bool str_buffer_full(String *str)
{
	return (str->len + 1) >= str->capacity;
}

bool str_buffer_empty(String *str)
{
	return str->len == 0;
}

bool str_buffer_fits(String *str, size_t str_len)
{
	return (str->len + str_len) < str->capacity;
}

Status str_realloc(String *str)
{
	if (str == NULL)
		return DS_ERR_NULL_POINTER;

	str->capacity *= str->growth_rate;

	char *new_buffer = realloc(str->buffer, sizeof(char) * str->capacity);

	if (!new_buffer)
	{
		str->capacity /= str->growth_rate;

		return DS_ERR_ALLOC;
	}

	str->buffer = new_buffer;

	str->buffer[str->len] = '\0';

	return DS_OK;
}

/* ---------------------------------------------------------------------------------------------------- String.c */

/* ---------------------------------------------------------------------------------------------------- Process.c */

Status prc_init(Process **prc, String *name, size_t pid, size_t cpu, size_t io, size_t pri)
{
	(*prc) = malloc(sizeof(Process));

	if (!(*prc))
		return DS_ERR_ALLOC;

	(*prc)->name = name;

	(*prc)->pid = pid;
	(*prc)->cpu = cpu;
	(*prc)->io = io;
	(*prc)->pri = pri;

	return DS_OK;
}

Status prc_delete(Process **prc)
{
	if (*prc == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = str_delete(&((*prc)->name));

	if (st != DS_OK)
		return st;

	free(*prc);

	*prc = NULL;

	return DS_OK;
}

Status prc_display(Process *prc)
{
	if (prc == NULL)
		return DS_ERR_NULL_POINTER;

	printf("%10s\t%zu\t%zu\t%zu\t%zu\n", prc->name->buffer, prc->pid, prc->cpu, prc->io, prc->pri);
	
	return DS_OK;
}

int prc_compare(Process *prc1, Process *prc2)
{
	if (prc1 == NULL || prc2 == NULL)
		return 0;

	if (prc1->pid > prc2->pid)
		return 1;
	else if (prc1->pid < prc2->pid)
		return -1;

	return 0;
}

Status prc_copy(Process *prc, Process **result)
{

	return DS_OK;
}

/* ---------------------------------------------------------------------------------------------------- Process.c */

/* ---------------------------------------------------------------------------------------------------- QueueArray.c */

Status qua_init(QueueArray **qua)
{
	(*qua) = malloc(sizeof(QueueArray));

	if (!(*qua))
		return DS_ERR_ALLOC;

	(*qua)->buffer = malloc(sizeof(QUEUE_T) * QUEUE_ARRAY_INIT_SIZE);

	if (!((*qua)->buffer))
		return DS_ERR_ALLOC;

	(*qua)->capacity = QUEUE_ARRAY_INIT_SIZE;
	(*qua)->growth_rate = QUEUE_ARRAY_GROW_RATE;

	(*qua)->length = 0;

	return DS_OK;
}

Status qua_get_length(QueueArray *qua, size_t *result)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	*result = qua->length;

	return DS_OK;
}

size_t qua_length(QueueArray *qua)
{
	return qua->length;
}

Status qua_enqueue(QueueArray *qua, QUEUE_T value)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_full(qua))
	{
		Status st = qua_realloc(qua);

		if (st != DS_OK)
			return st;
	}

	qua->buffer[qua->length] = value;

	(qua->length)++;

	return DS_OK;
}

Status qua_dequeue(QueueArray *qua, QUEUE_T *value)
{
	*value = 0;

	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
		return DS_ERR_INVALID_OPERATION;

	*value = qua->buffer[0];

	size_t i;

	for (i = 0; i < qua->length - 1; i++)
	{
		qua->buffer[i] = qua->buffer[i + 1];
	}

	return DS_OK;
}

Status qua_display(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	if (qua_is_empty(qua))
	{

		printf("\n[ empty ]\n");

		return DS_OK;
	}

	size_t i;
	for (i = 0; i < qua->length; i++)
		QUEUE_DISPLAY(qua->buffer[i]);

	return DS_OK;
}

Status qua_delete(QueueArray **qua)
{
	if ((*qua) == NULL)
		return DS_ERR_NULL_POINTER;
	
	Status st;

	size_t i;
	for (i = 0; i < (*qua)->length; i++)
	{
		st = QUEUE_DELETE(&((*qua)->buffer[i]));

		if (st != DS_OK)
			return st;
	}

	free((*qua)->buffer);

	free(*qua);

	*qua = NULL;

	return DS_OK;
}

Status qua_erase(QueueArray **qua)
{
	if ((*qua) == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = qua_delete(qua);

	if (st != DS_OK)
		return st;

	st = qua_init(qua);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

bool qua_is_empty(QueueArray *qua)
{
	return qua->length == 0;
}

bool qua_is_full(QueueArray *qua)
{
	return qua->length == qua->capacity;
}

//Status qua_copy(QueueArray *qua, QueueArray **result)

Status qua_realloc(QueueArray *qua)
{
	if (qua == NULL)
		return DS_ERR_NULL_POINTER;

	qua->capacity *= qua->growth_rate;

	QUEUE_T *new_buffer = realloc(qua->buffer, sizeof(QUEUE_T) * qua->capacity);

	if (!new_buffer)
	{
		qua->capacity /= qua->growth_rate;

		return DS_ERR_ALLOC;
	}

	qua->buffer = new_buffer;

	return DS_OK;
}

/* ---------------------------------------------------------------------------------------------------- QueueArray.c */

/* ---------------------------------------------------------------------------------------------------- DynamicArray.c */

Status dar_init(DynamicArray **dar)
{
	(*dar) = malloc(sizeof(DynamicArray));

	if (!(*dar))
		return DS_ERR_ALLOC;

	(*dar)->buffer = calloc(DYNAMIC_ARRAY_INIT_SIZE, sizeof(DS_DAR_T));

	if (!((*dar)->buffer))
		return DS_ERR_ALLOC;

	(*dar)->capacity = DYNAMIC_ARRAY_INIT_SIZE;
	(*dar)->growth_rate = DYNAMIC_ARRAY_GROW_RATE;

	(*dar)->size = 0;

	return DS_OK;
}

Status dar_insert_front(DynamicArray *dar, DS_DAR_T value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = dar->size; i > 0; i--)
	{
		dar->buffer[i] = dar->buffer[i - 1];
	}

	dar->buffer[0] = value;

	(dar->size)++;

	return DS_OK;
}

Status dar_insert_at(DynamicArray *dar, DS_DAR_T value, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_insert_front(dar, value);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size)
	{
		st = dar_insert_back(dar, value);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (dar_is_full(dar))
		{
			st = dar_realloc(dar);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = dar->size; i > index; i--)
		{
			dar->buffer[i] = dar->buffer[i - 1];
		}

		dar->buffer[index] = value;

		(dar->size)++;
	}

	return DS_OK;
}

Status dar_insert_back(DynamicArray *dar, DS_DAR_T value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	dar->buffer[dar->size] = value;

	(dar->size)++;

	return DS_OK;
}

Status dar_remove_front(DynamicArray *dar, DS_DAR_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		dar->buffer[i] = dar->buffer[i + 1];
	}

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_at(DynamicArray *dar, size_t index, DS_DAR_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_remove_front(dar, result);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size - 1)
	{
		st = dar_remove_back(dar, result);

		if (st != DS_OK)
			return st;
	}
	else
	{
		*result = dar->buffer[index];

		size_t i;
		for (i = index; i < dar->size; i++)
		{
			dar->buffer[i] = dar->buffer[i + 1];
		}

		(dar->size)--;
	}

	return DS_OK;
}

Status dar_remove_back(DynamicArray *dar, DS_DAR_T *result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[dar->size - 1];

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_keys(DynamicArray *dar, DS_DAR_T value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	Status st;

	DS_DAR_T result;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], value) == 0)
		{
			st = dar_remove_at(dar, i, &result);

			if (st != DS_OK)
				return st;

			st = DS_DAR_DELETE(&result);

			if (st != DS_OK)
				return st;

			i--;
		}
	}

	return DS_OK;
}

Status dar_display(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (dar_is_empty(dar))
		return DS_OK;

	printf("%s\t%s\t%s\t%s\t%s\n", "Process Name", "PID", "CPU", "I/O", "PRI");
	printf("%s\t%s\t%s\t%s\t%s\n", "------------", "---", "---", "---", "---");

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		DS_DAR_DISPLAY(dar->buffer[i]);
	}

	printf("\n");

	return DS_OK;
}

Status dar_delete(DynamicArray **dar)
{
	if (*dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st;

	size_t i;
	for (i = 0; i < (*dar)->size; i++)
	{
		st = DS_DAR_DELETE(&((*dar)->buffer[i]));

		if (st != DS_OK)
			return st;
	}

	free((*dar)->buffer);
	free((*dar));

	(*dar) = NULL;

	return DS_OK;
}

Status dar_erase(DynamicArray **dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = dar_delete(dar);

	if (st != DS_OK)
		return st;

	st = dar_init(dar);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

Status dar_get(DynamicArray *dar, size_t index, DS_DAR_T *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	*result = dar->buffer[index];

	return DS_OK;
}

size_t dar_cap(DynamicArray *dar)
{
	return dar->capacity;
}

size_t dar_size(DynamicArray *dar)
{
	return dar->size;
}

bool dar_is_empty(DynamicArray *dar)
{
	return dar->size == 0;
}

bool dar_is_full(DynamicArray *dar)
{
	return dar->size == dar->capacity;
}

Status dar_find_max(DynamicArray *dar, DS_DAR_T *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], *result) > 0)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_min(DynamicArray *dar, DS_DAR_T *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], *result) < 0)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_max_pos(DynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], dar->buffer[(*result)]) > 0)
			*result = i;
	}

	return DS_OK;
}

Status dar_find_min_pos(DynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], dar->buffer[(*result)]) < 0)
			*result = i;
	}

	return DS_OK;
}

bool dar_exists(DynamicArray *dar, DS_DAR_T value)
{
	if (dar == NULL)
		return false;

	if (dar_is_empty(dar))
		return false;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (DS_DAR_COMPARATOR(dar->buffer[i], value) == 0)
			return true;
	}

	return false;
}

Status dar_realloc(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	dar->capacity *= dar->growth_rate;

	DS_DAR_T *new_buffer = realloc(dar->buffer, sizeof(DS_DAR_T) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity /= dar->growth_rate;

		return DS_ERR_ALLOC;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}

Status sort_selection_array_dar(DS_DAR_T *array, size_t arr_size)
{
	if (array == NULL)
		return DS_ERR_NULL_POINTER;

	if (arr_size < 2)
		return DS_ERR_INVALID_SIZE;

	size_t i, j, min;
	DS_DAR_T tmp;

	for (i = 0; i < arr_size - 1; i++)
	{
		min = i;

		for (j = i + 1; j < arr_size; j++)
			if (DS_DAR_COMPARATOR(array[j], array[min]) > 0)
				min = j;

		tmp = array[min];
		array[min] = array[i];
		array[i] = tmp;
	}

	return DS_OK;
}

/* ---------------------------------------------------------------------------------------------------- DynamicArray.c */

/* ----------------------------------------------------------------------------------------------------
 *
 *                                                                                         Source Files
 *
 * ---------------------------------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------------------------------------
 *
 *                                                                                         File IO Functions
 *
 * ---------------------------------------------------------------------------------------------------- */

Status file_load(DynamicArray *process_table)
{
	String *text;

	Status st = str_init(&text);

	if (st != DS_OK)
		return st;

	FILE *file = fopen(FILE_NAME, "r");

	if (file == NULL)
		return DS_ERR_UNEXPECTED_RESULT;

	char c;

	while (1)
	{
		c = fgetc(file);

		if (c == EOF)
			break;

		st = str_push_char_back(text, c);

		if (st != DS_OK)
			return st;
	}

	fclose(file);

	if (text->len == 0)
	{
		str_delete(&text);
		return DS_OK;
	}

	String *name, *pid_s, *cpu_s, *io_s, *pri_s;
	size_t pid, cpu, io, pri;

	while (text->len > 1)
	{
		st += str_init(&name);
		st += str_init(&pid_s);
		st += str_init(&cpu_s);
		st += str_init(&io_s);
		st += str_init(&pri_s);

		if (st != DS_OK)
			return st;

		// Find name
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(name, c);

			if (st != DS_OK)
				return st;
		}

		// Find pid_s
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(pid_s, c);

			if (st != DS_OK)
				return st;
		}

		// Find cpu_s
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(cpu_s, c);

			if (st != DS_OK)
				return st;
		}

		// Find io_s
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == ',')
				break;

			st = str_push_char_back(io_s, c);

			if (st != DS_OK)
				return st;
		}

		// Find pri_s
		while (1)
		{
			c = text->buffer[0];

			st = str_pop_char_front(text);

			if (st != DS_OK)
				return st;

			if (c == '\n')
				break;

			st = str_push_char_back(pri_s, c);

			if (st != DS_OK)
				return st;
		}

		Process *process;

		// Convert pid
		sscanf(pid_s->buffer, "%zu", &pid);

		// Convert cpu
		sscanf(cpu_s->buffer, "%zu", &cpu);

		// Convert io
		sscanf(io_s->buffer, "%zu", &io);

		// Convert priority
		sscanf(pri_s->buffer, "%zu", &pri);

		// Create process
		st = prc_init(&process, name, pid, cpu, io, pri);

		if (st != DS_OK)
			return st;

		// Add to array
		st = dar_insert_back(process_table, process);

		if (st != DS_OK)
			return st;

		process = NULL;

		name = NULL;
		str_delete(&pid_s);
		str_delete(&cpu_s);
		str_delete(&io_s);
		str_delete(&pri_s);
	}

	str_delete(&text);

	return DS_OK;
}

Status file_save(DynamicArray *content)
{
	FILE *f = fopen(FILE_NAME, "w");

	if (f == NULL)
		return DS_ERR_UNEXPECTED_RESULT;

	size_t i;
	for (i = 0; i < content->size; i++)
	{
		fprintf(f, "%s,%zu,%zu,%zu,%zu\n", content->buffer[i]->name->buffer, content->buffer[i]->pid, content->buffer[i]->cpu, content->buffer[i]->io, content->buffer[i]->pri);
	}

	fclose(f);

	return DS_OK;
}

/* ----------------------------------------------------------------------------------------------------
 *
 *                                                                                         File IO Functions
 *
 * ---------------------------------------------------------------------------------------------------- */

int main()
{
	DynamicArray *process_table;

	Status st = dar_init(&process_table);

	if (st != DS_OK)
		return st;

	st = file_load(process_table);

	if (st != DS_OK)
	{
		print_status_repr(st);

		return st;
	}

	dar_display(process_table);

	st = file_save(process_table);

	if (st != DS_OK)
	{
		print_status_repr(st);

		return st;
	}

	dar_delete(&process_table);

	return 0;
}

