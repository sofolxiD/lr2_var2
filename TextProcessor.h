#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>

class TextProcessor {
public:
    // Статический метод - можно вызывать без создания объекта
    // Ищет предложения содержащие слово word в файле text.txt
    static void findSentencesWithWord(const std::string& word);
};

#endif