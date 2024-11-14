#pragma once

class CFontManager {
public:
	void AddFontFromFile(const std::string& fontName, const std::string& filePath, int minSize, int maxSize);
	void AddFontFromMemory(const std::string& fontName, void* fontData, size_t fontDataSize, int minSize, int maxSize);

	ImFont* GetFont(const std::string& fontName, float fontSize);

private:
	std::unordered_map<std::string, ImFont*> m_mFonts;
};

extern std::unique_ptr<CFontManager> g_pFontManager;