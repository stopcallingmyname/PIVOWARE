#include "includes.h"

std::string CUtils::ws2s(const std::wstring& wstr) {
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

std::wstring CUtils::s2ws(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string CUtils::get_random_string(size_t length) {
	std::string str(xorstr_("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"));
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(str.begin(), str.end(), generator);
	return str.substr(0, length);
}

std::string CUtils::string_to_hex(const std::string& sInput) {
	const char* const lut = xorstr_("0123456789ABCDEF");
	const size_t len = sInput.length();

	std::string sOutput;
	sOutput.reserve(2 * len);

	for (size_t i = 0; i < len; ++i) {
		const unsigned char c = sInput[i];
		sOutput.push_back(lut[c >> 4]);
		sOutput.push_back(lut[c & 15]);
	}
	return sOutput;
}

std::string CUtils::replace_all(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

std::wstring CUtils::replace_all(std::wstring str, const std::wstring& from, const std::wstring& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

std::string CUtils::replace_escapes(std::string& str) {
	str = replace_all(str, xorstr_("\\r"), xorstr_("\r"));
	str = replace_all(str, xorstr_("\\n"), xorstr_("\n"));
	str = replace_all(str, xorstr_("\\t"), xorstr_("\t"));
	str = replace_all(str, xorstr_("\\v"), xorstr_("\v"));
	return str;
}

std::wstring CUtils::replace_escapes(std::wstring& str) {
	str = replace_all(str, xorstr_(L"\\r"), xorstr_(L"\r"));
	str = replace_all(str, xorstr_(L"\\n"), xorstr_(L"\n"));
	str = replace_all(str, xorstr_(L"\\t"), xorstr_(L"\t"));
	str = replace_all(str, xorstr_(L"\\v"), xorstr_(L"\v"));
	return str;
}

std::string CUtils::remove_escapes(std::string& str) {
	str = replace_all(str, xorstr_("\r"), xorstr_(""));
	str = replace_all(str, xorstr_("\n"), xorstr_(""));
	str = replace_all(str, xorstr_("\t"), xorstr_(""));
	str = replace_all(str, xorstr_("\v"), xorstr_(""));
	return str;
}

std::wstring CUtils::remove_escapes(std::wstring& str) {
	str = replace_all(str, xorstr_(L"\r"), xorstr_(L""));
	str = replace_all(str, xorstr_(L"\n"), xorstr_(L""));
	str = replace_all(str, xorstr_(L"\t"), xorstr_(L""));
	str = replace_all(str, xorstr_(L"\v"), xorstr_(L""));
	return str;
}

std::vector<std::string> CUtils::utf8_split(const std::string& str, const std::string& delim) {
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();

	} while (pos < str.length() && prev < str.length());

	return tokens;
}

std::vector<std::wstring> CUtils::utf16_split(const std::wstring& str, const std::wstring& delim) {
	std::vector<std::wstring> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == std::wstring::npos) pos = str.length();
		std::wstring token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();

	} while (pos < str.length() && prev < str.length());

	return tokens;
};

std::string CUtils::xor_endec(const std::string sInput) {
	const char szKey[] = { 'v','z','8','o','y','4','I','E','K','e','t','i','7','d','j','2','E','v','c','m','V','D','q','M','Q','S','k','C','y','l','W','F' };

	std::string sOutput = sInput;

	for (size_t i = 0; i < sInput.size(); ++i)
		sOutput[i] = sInput[i] ^ szKey[i % (sizeof(szKey) / sizeof(char))];
	return sOutput;
}

std::string CUtils::joinstr(const std::vector<std::string>& elements, const std::string& separator) {
	if (elements.empty()) return "";

	std::string str;
	for (auto i : elements)
		str += i + separator;
	str = str.substr(0, str.size() - separator.size());
	return str;
}

std::string CUtils::request_to_server(std::string site, std::string param, std::string header, DWORD* outFileSize, DWORD* recvBytes, int flags) {
	HINTERNET hInternet = InternetOpenW(xorstr_(L""), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (outFileSize)
		*outFileSize = 0;

	if (recvBytes)
		*recvBytes = 0;

	if (hInternet == NULL) {
		(MessageBoxA)(NULL, xorstr_("Cannot connect to server."), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
		return NULL;
	} else {
		std::wstring wsSite = s2ws(site);
		std::wstring wsParam = s2ws(param);

		HINTERNET hConnect = (InternetConnectW)(hInternet, wsSite.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

		if (hConnect == NULL) {
			(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
			return NULL;
		} else {
			const wchar_t* parrAcceptTypes[] = { xorstr_(L"text/*"), NULL };

			HINTERNET hRequest = (HttpOpenRequestW)(hConnect, xorstr_(L"GET"), wsParam.c_str(), xorstr_(L"HTTP/1.1"), NULL, parrAcceptTypes, flags, 0);

			if (hRequest == NULL) {
				(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
				return NULL;
			} else {
				std::wstring wsHeader = s2ws(header);
				if (!header.empty()) {
					BOOL bAddRequestHeader = HttpAddRequestHeadersW(hRequest, wsHeader.c_str(), (DWORD)wsHeader.length(), HTTP_ADDREQ_FLAG_ADD);
					if (!bAddRequestHeader) {
						(MessageBoxA)(NULL, xorstr_("Error add request header"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
						return NULL;
					}
				}

				BOOL bRequestSent = (HttpSendRequestW)(hRequest, NULL, 0, NULL, 0);

				if (!bRequestSent) {
					(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
					return NULL;
				} else {

					char bufQuery[1024];
					DWORD dwLengthBufQuery;
					dwLengthBufQuery = sizeof(bufQuery);
					DWORD dwIndex;
					dwIndex = 0;

					BOOL isQuery = (HttpQueryInfoA)(
						hRequest,
						HTTP_QUERY_CONTENT_LENGTH,
						bufQuery,
						&dwLengthBufQuery,
						&dwIndex);

					if (isQuery) {
						DWORD dwFileSize;
						dwFileSize = (DWORD)atol(bufQuery);

						if (outFileSize)
							*outFileSize = dwFileSize;
					}

					std::string strResponse;
					const int nBuffSize = 1024;
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0) {
						bKeepReading = (InternetReadFile)(hRequest, buff, nBuffSize, &dwBytesRead);
						if (recvBytes)
							*recvBytes += dwBytesRead;
						strResponse.append(buff, dwBytesRead);
					}
					return strResponse;
				}
				(InternetCloseHandle)(hRequest);
			}
			(InternetCloseHandle)(hConnect);
		}
		(InternetCloseHandle)(hInternet);
	}
}

std::string CUtils::request_to_server_post(std::string site, std::string path, std::string param, std::string header, DWORD* outFileSize, DWORD* recvBytes, int flags) {
	HINTERNET hInternet = InternetOpenW(xorstr_(L""), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (outFileSize)
		*outFileSize = 0;

	if (recvBytes)
		*recvBytes = 0;

	if (hInternet == NULL) {
		(MessageBoxA)(NULL, xorstr_("Cannot connect to server."), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
		return NULL;
	} else {
		std::wstring wsSite = s2ws(site);
		std::wstring wsPath = s2ws(path);

		HINTERNET hConnect = (InternetConnectW)(hInternet, wsSite.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

		if (hConnect == NULL) {
			(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
			return NULL;
		} else {
			const wchar_t* parrAcceptTypes[] = { xorstr_(L"text/*"), NULL };

			HINTERNET hRequest = (HttpOpenRequestW)(hConnect, xorstr_(L"POST"), wsPath.c_str(), xorstr_(L"HTTP/1.1"), NULL, parrAcceptTypes, flags, 0);

			if (hRequest == NULL) {
				(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
				return NULL;
			} else {
				std::wstring wsHeader = s2ws(header);
				if (!header.empty()) {
					BOOL bAddRequestHeader = HttpAddRequestHeadersW(hRequest, wsHeader.c_str(), (DWORD)wsHeader.length(), HTTP_ADDREQ_FLAG_ADD);
					if (!bAddRequestHeader) {
						(MessageBoxA)(NULL, xorstr_("Error add request header"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
						return NULL;
					}
				}

				BOOL bRequestSent = (HttpSendRequestW)(hRequest, NULL, 0, param.data(), (DWORD)param.length());

				if (!bRequestSent) {
					(MessageBoxA)(NULL, xorstr_("Error sending message to server"), get_random_string(16).c_str(), MB_SYSTEMMODAL | MB_ICONERROR);
					return NULL;
				} else {

					char bufQuery[1024];
					DWORD dwLengthBufQuery;
					dwLengthBufQuery = sizeof(bufQuery);
					DWORD dwIndex;
					dwIndex = 0;

					BOOL isQuery = (HttpQueryInfoA)(
						hRequest,
						HTTP_QUERY_CONTENT_LENGTH,
						bufQuery,
						&dwLengthBufQuery,
						&dwIndex);

					if (isQuery) {
						DWORD dwFileSize;
						dwFileSize = (DWORD)atol(bufQuery);

						if (outFileSize)
							*outFileSize = dwFileSize;
					}

					std::string strResponse;
					const int nBuffSize = 1024;
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0) {
						bKeepReading = (InternetReadFile)(hRequest, buff, nBuffSize, &dwBytesRead);
						if (recvBytes)
							*recvBytes += dwBytesRead;
						strResponse.append(buff, dwBytesRead);
					}

					return strResponse;
				}
				(InternetCloseHandle)(hRequest);
			}
			(InternetCloseHandle)(hConnect);
		}
		(InternetCloseHandle)(hInternet);
	}
}

std::string CUtils::get_current_date_time() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), xorstr_("[%b - %d, %Y][%H:%M]"), &tstruct);

	return std::string(buf);
};


float CUtils::get_curftime() {
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::duration<float, std::milli> duration;

	static clock::time_point start = clock::now();
	duration elapsed = clock::now() - start;
	return elapsed.count() / 1000.f;
}

std::string CUtils::formatstr(const char* fmt, ...) {
	va_list argsToCheckSize;
	int n;
	std::string ret;

	va_start(argsToCheckSize, fmt);
	n = _vscprintf_p(fmt, argsToCheckSize);
	if (n == -1)
		return std::string();

	ret.resize(n + 1, 0);
	va_end(argsToCheckSize);

	va_list argsToFormat;

	va_start(argsToFormat, fmt);
	n = vsnprintf(&ret[0], ret.size(), fmt, argsToFormat);
	va_end(argsToFormat);

	assert(n < (int)ret.size());

	if (n == -1)
		return std::string();

	if (!ret.empty() && ret[ret.size() - 1] == '\0')
		ret = ret.substr(0, ret.size() - 1);

	return ret;
}

std::wstring CUtils::formatstr(const wchar_t* fmt, ...) {
	va_list argsToCheckSize;
	int n;
	std::wstring ret;

	va_start(argsToCheckSize, fmt);
	n = _vscwprintf(fmt, argsToCheckSize);
	if (n == -1)
		return std::wstring();

	ret.resize(n + 1, 0);
	va_end(argsToCheckSize);

	va_list argsToFormat;

	va_start(argsToFormat, fmt);
	n = _vsnwprintf(&ret[0], ret.size(), fmt, argsToFormat);
	va_end(argsToFormat);

	assert(n < (int)ret.size());

	if (n == -1)
		return std::wstring();

	if (!ret.empty() && ret[ret.size() - 1] == '\0')
		ret = ret.substr(0, ret.size() - 1);

	return ret;
}

void CUtils::logger(const char* fmt, ...) {
	std::ofstream fs;
	fs.open(g_pGVars->m_sLogFile, std::ios_base::out | std::ios_base::app);

	va_list argsToCheckSize;
	int n;
	std::string ret;

	va_start(argsToCheckSize, fmt);
	n = _vscprintf_p(fmt, argsToCheckSize);
	if (n == -1)
		return;

	ret.resize(n + 1, 0);
	va_end(argsToCheckSize);

	va_list argsToFormat;

	va_start(argsToFormat, fmt);
	n = vsnprintf(&ret[0], ret.size(), fmt, argsToFormat);
	va_end(argsToFormat);

	assert(n < (int)ret.size());

	if (n == -1)
		return;

	if (!ret.empty() && ret[ret.size() - 1] == '\0')
		ret = ret.substr(0, ret.size() - 1);

	auto log = formatstr(xorstr_("%s %s\n"), get_current_date_time().c_str(), ret.c_str());

	printf(log.c_str());

	if (fs.is_open())
		fs << log << std::endl;
	fs.close();
}

void CUtils::addlogterminate(const char* func, const char* err) {
	logger(xorstr_("%s: %s"), func, err);
	TerminateProcess(GetCurrentProcess(), 0);
}

void CUtils::addlog(const char* func, const char* msg) {
	logger(xorstr_("%s: %s"), func, msg);
}