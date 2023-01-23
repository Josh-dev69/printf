#include "main.h"

/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}
/**
 * write_unsigned - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */
int write_unsigned(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';
	int j;
	
	UNUSED(is_negative);
	UNUSED(size);
	/* Check if precision is 0 and buffer value is 0, in which case return 0 and don't print anything */
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	/* Add padding if precision is greater than the length of the buffer */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	/* If F_ZERO flag is set and F_MINUS flag is not set, use '0' as padding */
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	/* Add extra padding to the buffer if width is greater than length */
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		/* If F_MINUS flag is set, output buffer first followed by padding */
		if (flags & F_MINUS) 
		{
			for (j = ind; j < length; j++)
				_putchar(buffer[j]);
			for (j = 0; j < i; j++)
				_putchar(buffer[j]);
			return (length + i);
		}
		else /* If F_MINUS flag is not set, output padding first followed by buffer */
		{
			for (j = 0; j < i; j++)
				_putchar(buffer[j]);
			for (j = ind; j < length; j++)
				_putchar(buffer[j]);
			return (length + i);
		}
	}
	/* Output the buffer without extra padding */
	for (j = ind; j < length; j++)
		_putchar(buffer[j]);
	return (length);
}

/**
 * write_pointer - Write a string to a buffer
 * buffer: the character array that the string will be written to
 * ind: the current index of the buffer
 * length: the length of the string that will be written to the buffer
 * width: the desired width of the final string
 * flags: a bitfield of flags that indicate certain formatting options
 * padd: the character that will be used to pad the string.
 * extra_c: an extra character that will be added to the string
 * padd_start: the starting index for padding the string
 * Return: Number of written chars
 */

int write_pointer(char buffer[], int ind, int length, int width,
		int flags, char padd, char extra_c, int padd_start)
{
	int i;
	/* Check if width is greater than length */
	if (width > length)
	{
		/* Pad the buffer with the padd character */
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		/* Check if the string should be left-justified */
		if (flags & F_MINUS && padd == ' ') /* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			/* Write the final string to the buffer using _putchar function */
			for (i = ind; i < length; i++)
				_putchar(buffer[i]);
			for (i = 3; i < width - length + 3; i++)
				_putchar(buffer[i]);
			return (length + width - length + 3);
		}
		/* Check if the string should be right-justified and extra_c should be added before the padding */
		else if (!(flags & F_MINUS) && padd == ' ') /* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			/* Write the final string to the buffer using _putchar function */
			for (i = 3; i < width - length + 3; i++)
				_putchar(buffer[i]);
			for (i = ind; i < length; i++)
				_putchar(buffer[i]);
			return (length + width - length + 3);
		}
		/* Check if the string should be right-justified and extra_c should be added after the padding */
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			/* Write the final string to the buffer using putchar function */
			for (i = padd_start; i < i - padd_start; i++)
				_putchar(buffer[i]);
			for (i = ind; i < length - (1 - padd_start) - 2; i++)
				_putchar(buffer[i]);
			return (i - padd_start + length - (1 - padd_start) - 2);
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	/* Write the final string to the buffer using putchar function */
	for (i = ind; i < BUFF_SIZE - ind - 1; i++)
		putchar(buffer[i]);
	return (BUFF_SIZE - ind - 1);
}

