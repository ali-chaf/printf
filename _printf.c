#include "main.h"

void cleanUpPrintf(va_list arguments, buffer_t *output);
int executePrintf(const char *format, va_list arguments, buffer_t *output);
int _printf(const char *format, ...);
/**
 * cleanUpPrintf - Performs cleanup operations for customPrintf.
 * @arguments: A va_list of arguments provided to customPrintf.
 * @output: A buffer_t struct.
 */
void cleanUpPrintf(va_list arguments, buffer_t *output)
{
	va_end(arguments);
	write(1, output->start, output->len);
	freeBuffer(output);
}

/**
 * executePrintf - Processes the format string for customPrintf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @arguments: A va_list of arguments.
 *
 * Return: The number of characters stored in output.
 */
int executePrintf(const char *format, va_list arguments, buffer_t *output)
{
	int i, width, precision, result = 0;
	char temp;
	unsigned char flags, length;
	unsigned int (*formatter)(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

	i = 0;
	while (format[i])
	{
		length = 0;
		if (format[i] == '%')
		{
			temp = 0;
			flags = handleFlags(format + i + 1, &temp);
			width = handleWidth(arguments, format + i + temp + 1, &temp);
			precision = handlePrecision(arguments, format + i + temp + 1,
				&temp);
			length = handleLength(format + i + temp + 1, &temp);

			formatter = handleSpecifiers(format + i + temp + 1);
			if (formatter != NULL)
			{
				i += temp + 1;
				result += formatter(arguments, output, flags, width, precision, length);
				continue;
			}
			else if (format[i + temp + 1] == '\0')
			{
				result = -1;
				break;
			}
		}
		result += copyToBuffer(output, (format + i), 1);
		i += (length != 0) ? 1 : 0;
	}
	cleanUpPrintf(arguments, output);
	return (result);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list arguments;
	int result;

	if (format == NULL)
		return (-1);
	output = initializeBuffer();
	if (output == NULL)
		return (-1);

	va_start(arguments, format);

	result = executePrintf(format, arguments, output);

	return (result);
}

