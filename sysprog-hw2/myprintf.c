#ifdef COMPILETIME
#include <stdio.h>
#include <stdarg.h>

int myprintf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	fputs("[Interpositioning]", stdout);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int num = va_arg(args, int);

				char a[100];

				if (num < 0)
				{
					putchar('-');
					num = -num;
				}

				int i = 0;

				if (num == 0)
				{
					a[i] = '0';
					i++;
				}
				else
				{
					while (num != 0)
					{
						a[i] = num % 10 + '0';
						i++;
						num /= 10;
					}
				}

				for (int j = i - 1; j >= 0; j--)
				{
					putchar(a[j]);
				}
			}

			else if (*format == 'c')
			{
				char c = va_arg(args, int);
				putchar(c);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);
				fputs(str, stdout);
			}
			else if (*format == 'x')
			{
				unsigned int num = va_arg(args, int);
				char hex[100];
				int i = 0;

				if (num == 0)
				{
					hex[i] = '0';
					i++;
				}
				else
				{
					while (num != 0)
					{

						int temp = num % 16;
						if (temp < 10)
						{
							hex[i] = temp + '0';
							i++;
						}
						else
						{
							hex[i] = (temp - 10) + 'a';
							i++;
						}
						num /= 16;
					}
				}

				for (int j = i - 1; j >= 0; j--)
				{
					putchar(hex[j]);
				}
			}
		}

		else
		{
			putchar(*format);
		}
		format++;
	}

	va_end(args);
	return 0;
}
#endif

#ifdef LINKTIME

#include <stdio.h>
#include <stdarg.h>

int __real_printf(const char *format, ...);

int __wrap_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	fputs("[Interpositioning]", stdout);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'd')
			{
				int num = va_arg(args, int);

				char a[100];

				if (num < 0)
				{
					putchar('-');
					num = -num;
				}

				int i = 0;

				if (num == 0)
				{
					a[i] = '0';
					i++;
				}
				else
				{
					while (num != 0)
					{
						a[i] = num % 10 + '0';
						i++;
						num /= 10;
					}
				}

				for (int j = i - 1; j >= 0; j--)
				{
					putchar(a[j]);
				}
			}

			else if (*format == 'c')
			{
				char c = va_arg(args, int);
				putchar(c);
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);
				fputs(str, stdout);
			}
			else if (*format == 'x')
			{
				unsigned int num = va_arg(args, int);
				char hex[100];
				int i = 0;

				if (num == 0)
				{
					hex[i] = '0';
					i++;
				}
				else
				{
					while (num != 0)
					{

						int temp = num % 16;
						if (temp < 10)
						{
							hex[i] = temp + '0';
							i++;
						}
						else
						{
							hex[i] = (temp - 10) + 'a';
							i++;
						}
						num /= 16;
					}
				}

				for (int j = i - 1; j >= 0; j--)
				{
					putchar(hex[j]);
				}
			}
		}

		else
		{
			putchar(*format);
		}
		format++;
	}

	va_end(args);
	return 0;
}
#endif
