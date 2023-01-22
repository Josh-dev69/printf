#include <stdarg.h>
#include <stdio>
#include "main.h"
/**
 * _printf - produces output according to a format
 * @format: character string. The format string is composed of zero or more directives
 * Return: the number of characters print
 */
int _printf(const char *format, ...)
{
	int i, j, count = 0;
	va_list args;

	va_start(args, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{/*check if current char is a conversion specifier*/
			i++;
			switch (format[i])
			{
				case 'c': /* print the character increment count by 1 */
					_putchar(va_arg(args, int));
					count++;
					break;
				case 's':
					{
						char *s = va_arg(args, char *); /* get the next argument as a string */
						for (j = 0; s[j] != '\0'; j++) /* iterate through the string and print each character */
						{
							_putchar(s[j]);
							count++; /* increment count for each character */
						}
					}
					break;

					 case 'd': 
					{
						int *d = va_arg(args, int *);
						for (d = 0; d[f] != '\0'; f++)

						{
							printf(d[f]);
						       count++;
						}
				break;
						case 'i':
		double x = va_arg(args, double);
printf("%i\n" x);		
				case '%':
					_putchar('%'); /* print a literal '%' character */
					count++; /* increment count by 1 */
					break;
				default:
					_putchar(format[i]); /* print the current character */
					count++; /* increment count by 1 */
					break;
			}
		}
		else
		{
			_putchar(format[i]);
			count++;
		}
	}
	va_end(args);
	return (count);
}


