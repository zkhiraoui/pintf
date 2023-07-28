#include "main.h"

void displayBufferContent(char buf[], int *bufIdx);

/**
 * newPrintf
 */
int newPrintf(const char *format, ...)
{
	int idx, totalCharsPrinted = 0;
	int fmtFlags, fmtWidth, fmtPrecision, fmtSize, bufIdx = 0;
	va_list vargList;
	char buf[BUFFER_SIZE];

	if (!format) return (-1);

	va_start(vargList, format);

	for (idx = 0; format && format[idx] != '\0'; idx++)
	{
		if (format[idx] != '%')
		{
			buf[bufIdx++] = format[idx];
			if (bufIdx == BUFFER_SIZE)
				displayBufferContent(buf, &bufIdx);
			totalCharsPrinted++;
		}
		else
		{
			displayBufferContent(buf, &bufIdx);
			fmtFlags = acquireFlags(format, &idx);
			fmtWidth = acquireWidth(format, &idx, vargList);
			fmtPrecision = acquirePrecision(format, &idx, vargList);
			fmtSize = acquireSize(format, &idx);
			idx++;
			int printedChars = managePrint(format, &idx, vargList, buf,
				fmtFlags, fmtWidth, fmtPrecision, fmtSize);
			if (printedChars == -1)
				return (-1);
			totalCharsPrinted += printedChars;
		}
	}

	displayBufferContent(buf, &bufIdx);

	va_end(vargList);

	return (totalCharsPrinted);
}

void displayBufferContent(char buf[], int *bufIdx)
{
	if (*bufIdx > 0)
		write(1, buf, *bufIdx);

	*bufIdx = 0;
}
