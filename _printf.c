#include "main.h"

void flush_buffer(char buffer[], int *buff_index);
/**
 * _printf - custom printf function
 * @format: format string
 * Return: number of printed characters
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list arg_list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_index++] = format[i];
			if (buff_index == BUFF_SIZE)
				flush_buffer(buffer, &buff_index);
			printed_chars++;
		}
		else
		{
			flush_buffer(buffer, &buff_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, arg_list);
			precision = get_precision(format, &i, arg_list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, arg_list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	flush_buffer(buffer, &buff_index);

	va_end(arg_list);

	return (printed_chars);
}

/**
 * flush_buffer - writes the contents of the buffer
 * @buffer: character array buffer to be written
 * @buff_index: index at which to add next char, represents the length
*/

void flush_buffer(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);

	*buff_index = 0;
}
