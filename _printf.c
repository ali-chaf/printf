#include "main.h"

/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...);
int _printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;

	va_start(args, format);

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;
			if (*format == 'c')
			{
				char c = va_arg(args, int);

				printed_chars += write(1, &c, 1);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);

				if (!str)
					str = "(null)";
				while (*str)
				{
					printed_chars += write(1, str, 1);
					str++;
				}
			}
			else if (*format == '%')
			{
				printed_chars += write(1, "%", 1);
			}
		}
		else
		{
			printed_chars += write(1, format, 1);
		}
		format++;
	}

	va_end(args);
	return (printed_chars);
}
