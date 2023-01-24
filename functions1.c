#include "main.h"

/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: A variable arguments list
 * @buffer: Buffer array to handle print
 * @flags: flags set that can be used to modify the string
 * @width: width of the formatted string.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	/* Check if str is NULL and handle accordingly */
	if (str == NULL)
	{
		str = "(nil)";
		if (precision >= 6)
			str = "      ";
	}
	/* Calculate the length of the string */
	while (str[length] != '\0')
		length++;
	/* Check if precision is less than length and adjust length if necessary */
	if (precision >= 0 && precision < length)
		length = precision;
	/* Add padding if width > length */
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			/* Write the string and add padding on the right */
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			/* Add padding on the left and write the string */
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	/* Write the string without padding */
	return (write(1, str, length));
}

/************************* PRINT CHARACTER *************************/

/**
 * print_char - Prints a char
 * @types: arguments list of variable
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT INTEGERS *************************/
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[], int flags, int width, int precision,
		int size)
{
	unsigned int n, i, m, a[32], sum;
	int count;
	char z;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	/* Get the next argument from the variable argument list */
	n = va_arg(types, unsigned int);

	/* Initialize m with (2^31) and a with the first bit */
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	/* Divide n by m and store the remainder in a */
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	/* Write the bits to the standard output and count the number of bits */
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum = sum + a[i];
		if (sum || i == 31)
		{
			z = '0' + a[i];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
