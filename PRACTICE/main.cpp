#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include <unordered_set>


// Функция для проверки, является ли число суммой кубов своих цифр
bool isSumOfCubes(int num) {
    int originalNum = num;
    int sumOfCubes = 0;
    
    while (num > 0) {
        int digit = num % 10;
        sumOfCubes += std::pow(digit, 3);
        num /= 10;
    }
    
    return sumOfCubes == originalNum;
}


// Функция для нахождения всех чисел в заданном диапазоне, которые можно представить в виде суммы кубов своих цифр
std::vector<int> findSumOfCubesInRange(int start, int end) {
    std::vector<int> result;
    
    for (int i = start; i <= end; ++i) {
        if (isSumOfCubes(i)) {
            result.push_back(i);
        }
    }
    
    return result;
}

// Функция для проверки, является ли строка палиндромом
bool isPalindrome(const std::string& str) {
    std::string cleanedStr;
    // Убираем все небуквенные символы и переводим в нижний регистр
    for (char c : str) {
        if (std::isalnum(c)) {
            cleanedStr += std::tolower(c);
        }
    }
    
    std::string reversedStr = cleanedStr;
    std::reverse(reversedStr.begin(), reversedStr.end());
    
    return cleanedStr == reversedStr;
}

// Функция для проверки, можно ли разделить число на три тройки чисел, сумма которых равна N
bool canDivideIntoThreeTriplets(int N) {
    // Если N меньше 9, невозможно разбить его на три группы по три числа
    if (N < 9) {
        return false;
    }
    
    // Проверяем, можно ли найти три тройки чисел, сумма которых равна N
    for (int i = 1; i <= N - 6; ++i) {
        for (int j = i; j <= N - i - 3; ++j) {
            int k = N - i - j;
            if (k >= j && k < i + j + k) {
                return true;
            }
        }
    }
    
    return false;
}

// Функция для нахождения длины наибольшей возрастающей подпоследовательности
int lengthOfLIS(const std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    std::vector<int> dp(nums.size(), 1);
    
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *std::max_element(dp.begin(), dp.end());
}

// Функция для деления всех элементов массива на делитель
std::vector<int> divideArray(const std::vector<int>& nums, int divisor) {
    std::vector<int> result;
    for (int num : nums) {
        if (num % divisor == 0) {
            result.push_back(num);
        }
    }
    return result;
}

// Функция для нахождения всех троек Пифагора для n = 2
std::vector<std::vector<int>> findPythagoreanTriplets(int n) {
    std::vector<std::vector<int>> triplets;
    for (int a = 1; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            int c = std::sqrt(a * a + b * b);
            if (c * c == a * a + b * b && c <= n) {
                triplets.push_back({a, b, c});
            }
        }
    }
    return triplets;
}

// Функция для нахождения всех комбинаций чисел, сумма которых равна целевой сумме
void findCombinations(const std::vector<int>& nums, int target, std::vector<int>& combination, int index, std::vector<std::vector<int>>& result) {
    if (target == 0) {
        result.push_back(combination);
        return;
    }
    
    for (int i = index; i < nums.size(); ++i) {
        if (nums[i] <= target) {
            combination.push_back(nums[i]);
            findCombinations(nums, target - nums[i], combination, i, result);
            combination.pop_back();
        }
    }
}

std::vector<std::vector<int>> combinationSum(const std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> combination;
    findCombinations(nums, target, combination, 0, result);
    return result;
}


std::vector<std::string> findWordsFromLetters(const std::vector<char>& letters, const std::unordered_set<std::string>& dictionary) {
    std::vector<std::string> validWords;
    for (const auto& word : dictionary) {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end()); // Сортируем буквы в слове
        std::vector<char> sortedLetters = letters;
        std::sort(sortedLetters.begin(), sortedLetters.end()); // Сортируем буквы из входного массива
        if (sortedWord.size() == sortedLetters.size() && std::equal(sortedWord.begin(), sortedWord.end(), sortedLetters.begin())) {
            validWords.push_back(word);
        }
    }
    return validWords;
}





bool arePermutations(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    std::unordered_map<int, int> freqMap;

    // Заполнение частотного словаря для первого массива
    for (int num : arr1) {
        freqMap[num]++;
    }

    // Уменьшение частоты для каждого элемента второго массива
    for (int num : arr2) {
        if (freqMap.find(num) == freqMap.end()) {
            // Элемент не найден в первом массиве
            return false;
        }
        freqMap[num]--;
        if (freqMap[num] == 0) {
            freqMap.erase(num);
        }
    }

    // Если все элементы второго массива обработаны, и частотный словарь пустой, то массивы - перестановки друг друга
    return freqMap.empty();
}




// Функция для проверки, можно ли из букв первого слова составить второе слово
bool canConstructWord(const std::string& word1, const std::string& word2) {
    // Массивы для подсчета частоты букв в словах
    std::array<int, 26> freq1 = {0};
    std::array<int, 26> freq2 = {0};
    
    // Подсчет частоты букв в первом слове
    for (char ch : word1) {
        if (std::isalpha(ch)) {
            freq1[std::tolower(ch) - 'a']++;
        }
    }
    
    // Подсчет частоты букв во втором слове
    for (char ch : word2) {
        if (std::isalpha(ch)) {
            freq2[std::tolower(ch) - 'a']++;
        }
    }
    
    // Проверка, можно ли из букв первого слова составить второе слово
    for (int i = 0; i < 26; ++i) {
        if (freq2[i] > freq1[i]) {
            return false; // Второе слово содержит больше букв i, чем первое слово
        }
    }
    return true;
}





int main() {
    int choice;
    
    std::cout << "Выберите действие:\n";
    std::cout << "1. Найти числа в диапазоне, которые являются суммой кубов своих цифр\n";
    std::cout << "2. Проверить, является ли строка палиндромом\n"; //  ТЕСТИРОВАТЬ!
    std::cout << "3. Проверить, можно ли разделить число на три тройки чисел, сумма которых равна N\n";
    std::cout << "4. Найти длину наибольшей возрастающей подпоследовательности в массиве\n";
    std::cout << "5. Найти числа в массиве, которые делятся на заданный делитель\n";
    std::cout << "6. Найти тройки чисел Пифагора для n \n"; // добавленный вариант выбора
    std::cout << "7. Найти комбинации чисел, сумма которых равна целевой сумме \n"; // новый вариант выбора
    std::cout << "8. Возвращает все слова, которые можно составить из введеных букв и существуют в словаре.\n";
    std::cout << "9. Являются ли массивы перестановками друг друга\n";
    std::cout << "10. Можно ли из букв первого слова составить второе слово\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            int start, end;
            std::cout << "Введите начало диапазона: ";
            std::cin >> start;
            std::cout << "Введите конец диапазона: ";
            std::cin >> end;
            
            std::vector<int> numbers = findSumOfCubesInRange(start, end);
            
            std::cout << "Числа в диапазоне [" << start << ", " << end << "], которые можно представить в виде суммы кубов своих цифр: ";
            for (int num : numbers) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
            break;
        }
        case 2: {
            std::cin.ignore(); // очищаем буфер ввода перед считыванием строки
            std::string input;
            std::cout << "Введите строку: ";
            std::getline(std::cin, input);
            
            if (isPalindrome(input)) {
                std::cout << "Строка является палиндромом.\n";
            } else {
                std::cout << "Строка не является палиндромом.\n";
            }
            break;
        }
        case 3: {
            int N;
            std::cout << "Введите число N: ";
            std::cin >> N;
            
            if (canDivideIntoThreeTriplets(N)) {
                std::cout << "Число можно разделить на три тройки чисел, сумма которых равна " << N << ".\n";
            } else {
                std::cout << "Число нельзя разделить на три тройки чисел, сумма которых равна " << N << ".\n";
            }
            break;
        }
        case 4: {
            std::cin.ignore(); // очищаем буфер ввода перед считыванием строки
            std::vector<int> nums;
            std::string input;
            std::cout << "Введите массив чисел, разделенных пробелом: ";
            std::getline(std::cin, input);
            std::istringstream iss(input);
            int num;
            while (iss >> num) {
                nums.push_back(num);
            }
            
            int length = lengthOfLIS(nums);
            
            std::cout << "Длина наибольшей возрастающей подпоследовательности: " << length << std::endl;
            break;
        }
        case 5: {
            std::cin.ignore(); // очищаем буфер ввода перед считыванием строки
            std::vector<int> nums;
            int divisor;
            std::string input;
            std::cout << "Введите массив чисел, разделенных пробелом: ";
            std::getline(std::cin, input);
            std::istringstream iss(input);
            int num;
            while (iss >> num) {
                nums.push_back(num);
            }
            
            std::cout << "Введите делитель: ";
            std::cin >> divisor;
            
            std::vector<int> result = divideArray(nums, divisor);
            
            std::cout << "Числа в массиве, которые делятся на " << divisor << ": ";
            for (int num : result) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
            break;
        }
        case 6: {
            int n;
            std::cout << "Введите число n: ";
            std::cin >> n;
            
            std::vector<std::vector<int>> triplets = findPythagoreanTriplets(n);
            
            std::cout << "Тройки чисел (a, b, c), удовлетворяющие a^2 + b^2 = c^2 и c <= " << n << ":\n";
            for (const auto& triplet : triplets) {
                std::cout << "(" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << ")\n";
            }
            break;
        }
        case 7: { // Добавленный вариант выбора
            int n;
            std::cout << "Введите количество чисел: ";
            std::cin >> n;
            
            std::vector<int> nums(n);
            std::cout << "Введите числа: ";
            for (int i = 0; i < n; ++i) {
                std::cin >> nums[i];
            }
            
            int target;
            std::cout << "Введите целевую сумму: ";
            std::cin >> target;
            
            std::vector<std::vector<int>> combinations = combinationSum(nums, target);
            
            std::cout << "Комбинации чисел, сумма которых равна " << target << ":\n";
            for (const auto& combination : combinations) {
                std::cout << "(";
                for (size_t i = 0; i < combination.size(); ++i) {
                    std::cout << combination[i];
                    if (i != combination.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << ")\n";
            }
            break;
        }
        case 8:{
            // Считываем словарь из файла
                std::unordered_set<std::string> dictionary;
                std::ifstream file("/Users/ivanmerzov/Desktop/PRACTICE3/PRACTICE3/ditionary.txt");
                if (file.is_open()) {
                    std::string word;
                    while (std::getline(file, word)) {
                        dictionary.insert(word);
                    }
                    file.close();
                } else {
                    std::cerr << "Не удалось открыть файл словаря.\n";
                    return 1;
                }
                
                // Ввод букв с клавиатуры
                std::vector<char> letters;
                std::string input;
                std::cout << "Введите буквы, разделенные пробелом: ";
                std::cin.ignore();
                std::getline(std::cin, input);
                std::istringstream iss(input);
                char letter;
                while (iss >> letter) {
                    letters.push_back(letter);
                }
                
                // Поиск слов
                std::vector<std::string> validWords = findWordsFromLetters(letters, dictionary);
                
                std::cout << "Слова, которые можно составить из введенных букв и существуют в словаре:\n";
                for (const auto& word : validWords) {
                    std::cout << word << std::endl;
                }
                
                return 0;
            
            
            break;
        }
            
        case 9:{
            
            int n;
                std::cout << "Введите размер массивов: ";
                std::cin >> n;

                std::vector<int> arr1(n);
                std::vector<int> arr2(n);

                std::cout << "Введите элементы первого массива: ";
                for (int i = 0; i < n; ++i) {
                    std::cin >> arr1[i];
                }

                std::cout << "Введите элементы второго массива: ";
                for (int i = 0; i < n; ++i) {
                    std::cin >> arr2[i];
                }

                if (arePermutations(arr1, arr2)) {
                    std::cout << "Массивы являются перестановками друг друга.\n";
                } else {
                    std::cout << "Массивы не являются перестановками друг друга.\n";
                }

                return 0;
            
            break;
        }
        case 10:{
            std::string word1, word2;
               
               // Ввод двух слов с клавиатуры
               std::cout << "Введите первое слово: ";
               std::cin >> word1;
               std::cout << "Введите второе слово: ";
               std::cin >> word2;
               
               // Проверка, можно ли из букв первого слова составить второе слово
               if (canConstructWord(word1, word2)) {
                   std::cout << "Из букв первого слова можно составить второе слово.\n";
               } else {
                   std::cout << "Из букв первого слова нельзя составить второе слово.\n";
               }
               
               return 0;
            break;
        }
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
    }
    
    return 0;
}
