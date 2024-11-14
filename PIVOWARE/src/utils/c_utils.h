#pragma once

class CUtils {
public:
	static std::string                       ws2s(const std::wstring& wstr);
	static std::wstring                      s2ws(const std::string& str);
	static std::string                       get_random_string(size_t length);
	static std::string                       string_to_hex(const std::string& sInput);
	static std::string                       replace_all(std::string str, const std::string& from, const std::string& to);
	static std::wstring                      replace_all(std::wstring str, const std::wstring& from, const std::wstring& to);
	static std::string                       replace_escapes(std::string& str);
	static std::wstring                      replace_escapes(std::wstring& str);
	static std::string                       remove_escapes(std::string& str);
	static std::wstring                      remove_escapes(std::wstring& str);
	static std::vector<std::string>          utf8_split(const std::string& str, const std::string& delim);
	static std::vector<std::wstring>         utf16_split(const std::wstring& str, const std::wstring& delim);
	static std::string                       xor_endec(const std::string sInput);
	static std::string                       joinstr(const std::vector<std::string>& elements, const std::string& separator);


	static std::string                       request_to_server(std::string site, std::string param, std::string header = "", DWORD* outFileSize = nullptr, DWORD* recvBytes = nullptr,
		int flags = INTERNET_FLAG_SECURE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE);

	static std::string                       request_to_server_post(std::string site, std::string path, std::string param, std::string header = "", DWORD* outFileSize = nullptr, DWORD* recvBytes = nullptr,
		int flags = INTERNET_FLAG_SECURE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE);

	static std::string                       get_current_date_time();

	static float                             get_curftime();

	static std::string                       formatstr(const char* fmt, ...);
	static std::wstring                      formatstr(const wchar_t* fmt, ...);

	static void                              logger(const char* fmt, ...);
	static void                              addlogterminate(const char*, const char*);
	static void                              addlog(const char*, const char*);
};