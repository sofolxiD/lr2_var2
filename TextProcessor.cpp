#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

void TextProcessor::findSentencesWithWord(const std::string& word) {
    if (word.empty()) {
        std::cout << "Слово не может быть пустым!" << std::endl;
        return;
    }
    
    // Всегда работаем с text.txt
    std::ifstream file("text.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка: файл text.txt не найден!" << std::endl;
        std::cout << "Создайте файл text.txt в папке с программой" << std::endl;
        return;
    }
    
    std::cout << "\n=== Предложения со словом \"" << word << "\" ===" << std::endl;
    
    std::string text;
    char ch;
    while (file.get(ch)) {
        text += ch;
    }
    file.close();
    
    if (text.empty()) {
        std::cout << "Файл text.txt пустой!" << std::endl;
        return;
    }
    
    bool found = false;
    std::string sentence;
    
    // Проходим по всему тексту
    for (size_t i = 0; i < text.length(); i++) {
        sentence += text[i];
        
        // Конец предложения
        if (text[i] == '.' || text[i] == '!' || text[i] == '?' || i == text.length() - 1) {
            // Убираем пробелы в начале
            while (!sentence.empty() && std::isspace(sentence[0])) {
                sentence.erase(0, 1);
            }
            
            // поиск слова в предложении
            if (!sentence.empty()) {
                // Ищем слово в предложении (регистрозависимо)
                size_t pos = sentence.find(word);
                if (pos != std::string::npos) {
                    // Проверяем, что это отдельное слово
                    bool left_ok = (pos == 0) || !std::isalpha(sentence[pos - 1]);
                    bool right_ok = (pos + word.length() >= sentence.length()) || 
                                   !std::isalpha(sentence[pos + word.length()]);
                    
                    if (left_ok && right_ok) {
                        std::cout << "- " << sentence << std::endl;
                        found = true;
                    }
                }
            }
            sentence.clear();
        }
    }
    
    if (!found) {
        std::cout << "Не найдено предложений с этим словом" << std::endl;
    }
    std::cout << "=================================" << std::endl;
}