#include <unistd.h>
#include "main.h"
/**
 * _putchar
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}