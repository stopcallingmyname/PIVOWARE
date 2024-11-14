#include "includes.h"

std::unique_ptr<CFontManager> g_pFontManager;

void CFontManager::AddFontFromFile(const std::string& fontName, const std::string& filePath, int minSize, int maxSize) {
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    for (int size = minSize; size <= maxSize; ++size) {
        ImFont* font = io.Fonts->AddFontFromFileTTF(filePath.c_str(), static_cast<float>(size), &config, io.Fonts->GetGlyphRangesCyrillic());
        if (font) {
            std::string key = fontName + "_" + std::to_string(size);
            m_mFonts[key] = font;
        }
    }
}

void CFontManager::AddFontFromMemory(const std::string& fontName, void* fontData, size_t fontDataSize, int minSize, int maxSize) {
    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig config;
    config.FontDataOwnedByAtlas = false;

    for (int size = minSize; size <= maxSize; ++size) {
        ImFont* font = io.Fonts->AddFontFromMemoryTTF(fontData, fontDataSize, static_cast<float>(size), &config, io.Fonts->GetGlyphRangesCyrillic());
        if (font) {
            std::string key = fontName + "_" + std::to_string(size);
            m_mFonts[key] = font;
        }
    }
}

ImFont* CFontManager::GetFont(const std::string& fontName, float fontSize) {
    std::string key = fontName + "_" + std::to_string(static_cast<int>(fontSize));
    if (m_mFonts.find(key) != m_mFonts.end()) {
        return m_mFonts[key];
    }
    return nullptr;
}