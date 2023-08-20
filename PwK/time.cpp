#include "pch.h"
#include "time.h"

std::wstring getCurrentDateTime()
{
	tm				timeptr{};
	wchar_t			dest[32]{};
	time_t			temp{};
	size_t			size_{};
	const size_t	size_w = wcsnlen_s(dest, size_);

	temp = time(NULL);
	localtime_s(&timeptr, &temp);
	wcsftime(dest, size_w - 1, L"%d/%m %X", &timeptr);

	return dest;
}