#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // Для проверки символов (isalpha, isspace)

// Ищет в тексте предложения, содержащие заданное слово
void TextProcessor::findSentencesWithWord(const std::string& word) {
    // Проверяем, что слово не пустое
    if (word.empty()) {
        std::cout << "Слово не может быть пустым!" << std::endl;
        return;
    }
    
    // Всегда работаем с файлом text.txt
    std::ifstream file("text.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка: файл text.txt не найден!" << std::endl;
        std::cout << "Создайте файл text.txt в папке с программой" << std::endl;
        return;
    }
    
    std::cout << "\n=== Предложения со словом \"" << word << "\" ===" << std::endl;
    
    // Читаем весь файл в строку text
    std::string text;
    char ch;
    while (file.get(ch)) {
        text += ch;
    }
    file.close();
    
    // Проверяем, не пустой ли файл
    if (text.empty()) {
        std::cout << "Файл text.txt пустой!" << std::endl;
        return;
    }
    
    bool found = false;     // Нашли ли хоть одно предложение
    std::string sentence;   // Текущее предложение
    
    // Проходим по всем символам текста
    for (size_t i = 0; i < text.length(); i++) {
        sentence += text[i];  // Добавляем символ к текущему предложению
        
        // Если это конец предложения (точка, воскл., вопрос) или конец файла
        if (text[i] == '.' || text[i] == '!' || text[i] == '?' || i == text.length() - 1) {
            // Убираем пробелы в начале предложения
            while (!sentence.empty() && std::isspace(sentence[0])) {
                sentence.erase(0, 1);  // Удаляем первый пробельный символ
            }
            
            // Если предложение не пустое, ищем в нем слово
            if (!sentence.empty()) {
                // Ищем слово в предложении (регистрозависимый поиск)
                size_t pos = sentence.find(word);
                if (pos != std::string::npos) {  // Если нашли
                    // Проверяем, что это отдельное слово, а не часть другого слова
                    // Например: ищем "кот", а не "котлета"
                    bool left_ok = (pos == 0) || !std::isalpha(sentence[pos - 1]);
                    bool right_ok = (pos + word.length() >= sentence.length()) || 
                                   !std::isalpha(sentence[pos + word.length()]);
                    
                    // Если слева и справа не буквы - значит это отдельное слово
                    if (left_ok && right_ok) {
                        std::cout << "- " << sentence << std::endl;
                        found = true;  // Отмечаем, что нашли
                    }
                }
            }
            sentence.clear();  // Очищаем предложение для следующего
        }
    }
    
    // Если ни одного предложения не нашли
    if (!found) {
        std::cout << "Не найдено предложений с этим словом" << std::endl;
    }
    std::cout << "=================================" << std::endl;
}