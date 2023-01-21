#include <unistd.h>

/**
 * _putchar - writes the character of a string to stdout
 * @str: Input character
 * Return: On Success 1
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char str)
{
	return (write(1, &str, 1));
}
