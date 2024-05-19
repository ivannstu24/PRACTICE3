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





using namespace std;

pair<double, string> calculating_average_score(unordered_map<string, int>& marks) {
    double middle_ball = 0;

    // Вычисление среднего балла
    for (const auto& pair : marks) {
        middle_ball += pair.second;
    }
    middle_ball /= marks.size();

    // Определение академического статуса
    string status;
    if (middle_ball >= 90) {
        status = "Отличник";
    } else if (middle_ball >= 70) {
        status = "Хорошист";
    } else if (middle_ball >= 50) {
        status = "Удовлетворительно";
    } else {
        status = "Неудовлетворительно";
    }

    return {middle_ball, status};
}





// Структура для хранения предметов и их времени
struct Subject {
    string name;
    int time;
};

// Функция для планирования расписания
vector<string> planSchedule(vector<Subject>& subjects, int availableTimePerWeek) {
    vector<string> schedule;

    // Сортировка предметов по времени в порядке возрастания
    sort(subjects.begin(), subjects.end(), [](const Subject& a, const Subject& b) {
        return a.time < b.time;
    });

    // Добавление предметов в расписание до исчерпания доступного времени
    int remainingTime = availableTimePerWeek;
    for (const auto& subject : subjects) {
        if (remainingTime >= subject.time) {
            schedule.push_back(subject.name);
            remainingTime -= subject.time;
        }
    }

    return schedule;
}





// Функция для построения префикс-функции (массив lps)
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int length = 0;
    lps[0] = 0; // lps[0] всегда равно 0

    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Функция для поиска подстроки с использованием KMP алгоритма
void KMPsearch(const string& text, const string& pattern) {
    int M = pattern.length();
    int N = text.length();

    vector<int> lps(M);

    // Построение lps массива
    computeLPSArray(pattern, lps);

    int i = 0; // индекс для text[]
    int j = 0; // индекс для pattern[]
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}





//Жадный продавец


vector<int> getChange(int amount, const vector<int>& denominations) {
    vector<int> change;

    for (int coin : denominations) {
        while (amount >= coin) {
            amount -= coin;
            change.push_back(coin);
        }
    }

    return change;
}



// Структура для хранения предметов
struct Item {
    int weight;
    int value;
};

// Функция для нахождения максимальной ценности рюкзака
int knapsack(int maxWeight, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= maxWeight; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][maxWeight];
}



// Функция для нахождения максимального количества групп, которые могут разместиться
int maxGroupsThatCanBeSeated(vector<int>& tableCapacities, vector<int>& groupSizes) {
    sort(tableCapacities.begin(), tableCapacities.end());
    sort(groupSizes.begin(), groupSizes.end());

    int i = 0, j = 0;
    int count = 0;

    while (i < tableCapacities.size() && j < groupSizes.size()) {
        if (tableCapacities[i] >= groupSizes[j]) {
            count++;
            i++;
            j++;
        } else {
            i++;
        }
    }

    return count;
}




// Структура для хранения заказов
struct Order {
    int requestTime;
    int deliveryTime;
};

// Функция для сравнения заказов по времени доставки
bool compareOrders(const Order& a, const Order& b) {
    return a.deliveryTime < b.deliveryTime;
}

// Функция для нахождения максимального количества заказов, которые можно доставить в срок
int maxOrdersDelivered(vector<Order>& orders) {
    sort(orders.begin(), orders.end(), compareOrders);

    int count = 0;
    int currentTime = 0;

    for (const auto& order : orders) {
        if (order.requestTime >= currentTime) {
            count++;
            currentTime = order.deliveryTime;
        }
    }

    return count;
}



// Функция для сжатия строки
string compressString(const string& str) {
    if (str.empty()) {
        return str;
    }

    string compressed = "";
    int countConsecutive = 0;

    for (size_t i = 0; i < str.length(); ++i) {
        countConsecutive++;

        // Если следующий символ отличается от текущего или это конец строки, добавляем текущий символ и его количество
        if (i + 1 >= str.length() || str[i] != str[i + 1]) {
            compressed += str[i];
            compressed += to_string(countConsecutive);
            countConsecutive = 0;
        }
    }

    // Возвращаем либо сжатую строку, либо исходную, если сжатая не короче
    return compressed.length() < str.length() ? compressed : str;
}




// Функция для проверки, является ли число простым
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Функция для фильтрации массива по простым числам
vector<int> filterPrimes(const vector<int>& arr) {
    vector<int> result;
    for (int num : arr) {
        if (isPrime(abs(num))) {
            result.push_back(num);
        }
    }
    return result;
}


// Функция для вычисления количества битов, необходимых для представления числа
int numberOfBits(int number) {
    if (number == 0) return 1;
    return floor(log2(number)) + 1;
}

// Функция для вычисления суммарного количества битов для представления массива чисел
int totalBits(const vector<int>& numbers) {
    int total = 0;
    for (int number : numbers) {
        total += numberOfBits(number);
    }
    return total;
}




int main() {
    int choice;
    
    std::cout << "Выберите действие:\n";
    std::cout << "1. Найти числа в диапазоне, которые являются суммой кубов своих цифр\n";
    std::cout << "2. Проверить, является ли строка палиндромом\n"; //  ТЕСТИРОВАТЬ!
    std::cout << "3. Проверить, можно ли разделить число на три тройки чисел, сумма которых равна N\n";
    std::cout << "4. Найти длину наибольшей возрастающей подпоследовательности в массиве\n";
    std::cout << "5. Найти числа в массиве, которые делятся на заданный делитель\n";
    std::cout << "6. Найти тройки чисел Пифагора для n \n";
    std::cout << "7. Найти комбинации чисел, сумма которых равна целевой сумме \n";
    std::cout << "8. Возвращает все слова, которые можно составить из введеных букв и существуют в словаре.\n";
    std::cout << "9. Являются ли массивы перестановками друг друга\n";
    std::cout << "10. Можно ли из букв первого слова составить второе слово\n";
    std::cout << "11. Расчет среднего балла студента\n";
    std::cout << "12. Подбор оптимального времени для студента\n";
    std::cout << "13. Поиск подстроки (Алгоритм Кнута-Морриса-Пратта)\n";
    std::cout << "14. Алгоритм для жадного продавца\n";
    std::cout << "15. Задача о рюкзаке (Максимальная ценность, которую можно поместить в рюкзак)\n";
    std::cout << "16. Задача о распределении мест в ресторане\n";
    std::cout << "17. Оптимизация доставки пиццы\n";
    std::cout << "18. Сжатие строки\n";
    std::cout << "19. Вывод всех простых чисел из заданого массива\n";
    std::cout << "20. Минимизация количества битов для представления чисел\n";

    


    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    std::cin.ignore();
    
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
        case 11:{
            unordered_map<string, int> marks;
            int subjects;
            cout << "Введите количество предметов: ";
            cin >> subjects;

            // Ввод оценок для каждого предмета
            for (int i = 0; i < subjects; ++i) {
                string subject;
                int mark;
                cout << "Введите название предмета " << i + 1 << ": ";
                cin >> subject;
                cout << "Введите балл по предмету " << subject << ": ";
                cin >> mark;
                marks[subject] = mark;
            }

            auto [middle_ball, status] = calculating_average_score(marks);
            cout << "Средний балл: " << middle_ball << endl;
            cout << "Академический статус: " << status << endl;

            return 0;
            break;
        }
        case 12:{
            vector<Subject> subjects;
              int numberOfSubjects;
              int availableTimePerWeek;

              cout << "Введите количество предметов: ";
              cin >> numberOfSubjects;

              // Ввод предметов и их времени
              for (int i = 0; i < numberOfSubjects; ++i) {
                  Subject subject;
                  cout << "Введите название предмета " << i + 1 << ": ";
                  cin >> subject.name;
                  cout << "Введите время на предмет " << subject.name << " в часах: ";
                  cin >> subject.time;
                  subjects.push_back(subject);
              }

              cout << "Введите доступное время в неделю: ";
              cin >> availableTimePerWeek;

              // Планирование расписания
              vector<string> optimalSchedule = planSchedule(subjects, availableTimePerWeek);

              // Вывод результата
              cout << "Оптимальное расписание:" << endl;
              for (const auto& subject : optimalSchedule) {
                  cout << subject << endl;
              }

              return 0;
            break;
        }
        case 13:{
            string text;
               string pattern;

               cout << "Введите текст: ";
               cin >> text;

               cout << "Введите подстроку для поиска: ";
               cin >> pattern;

               KMPsearch(text, pattern);

               return 0;
        }
        case 14:{
            int amount;
                cout << "Введите сумму сдачи: ";
                cin >> amount;

                // Номиналы монет
                vector<int> denominations = {50, 20, 10, 5, 2, 1};

                vector<int> change = getChange(amount, denominations);

                cout << "Необходимое количество монет: " << change.size() << endl;
                cout << "Монеты: ";
                for (int coin : change) {
                    cout << coin << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 15:{
            int maxWeight;
                int numItems;

                cout << "Введите максимальный вес рюкзака: ";
                cin >> maxWeight;

                cout << "Введите количество предметов: ";
                cin >> numItems;

                vector<Item> items(numItems);
                cout << "Введите вес и ценность каждого предмета:" << endl;
                for (int i = 0; i < numItems; ++i) {
                    cin >> items[i].weight >> items[i].value;
                }

                int maxValue = knapsack(maxWeight, items);
                cout << "Максимальная ценность, которую можно поместить в рюкзак: " << maxValue << endl;

                return 0;
            break;
        }
        case 16:{
            int numTables, numGroups;

                cout << "Введите количество столиков: ";
                cin >> numTables;

                vector<int> tableCapacities(numTables);
                cout << "Введите вместимость каждого столика: ";
                for (int i = 0; i < numTables; ++i) {
                    cin >> tableCapacities[i];
                }

                cout << "Введите количество групп гостей: ";
                cin >> numGroups;

                vector<int> groupSizes(numGroups);
                cout << "Введите размер каждой группы: ";
                for (int i = 0; i < numGroups; ++i) {
                    cin >> groupSizes[i];
                }

                int maxGroups = maxGroupsThatCanBeSeated(tableCapacities, groupSizes);
                cout << "Максимальное количество групп, которые могут разместиться: " << maxGroups << endl;

                return 0;
            break;
        }
        case 17:{
            int numOrders;
               cout << "Введите количество заказов: ";
               cin >> numOrders;

               vector<Order> orders(numOrders);
               cout << "Введите время подачи заявки и желаемое время доставки для каждого заказа:" << endl;
               for (int i = 0; i < numOrders; ++i) {
                   cin >> orders[i].requestTime >> orders[i].deliveryTime;
               }

               int result = maxOrdersDelivered(orders);
               cout << "Максимальное количество доставленных заказов в срок: " << result << endl;

               return 0;
            break;
        }
        case 18:{
            string input;
               cout << "Введите строку: ";
               getline(cin, input);
            

               string compressed = compressString(input);
               cout << "Сжатая строка: " << compressed << endl;

               return 0;
            break;
        }
        case 19:{
            // Запрос пользователю ввода массива
                int n;
                cout << "Введите количество элементов массива: ";
                cin >> n;

                vector<int> array(n);
                cout << "Введите элементы массива: ";
                for (int i = 0; i < n; ++i) {
                    cin >> array[i];
                }

                // Вызов функции для фильтрации массива
                vector<int> primes = filterPrimes(array);

                // Вывод отфильтрованного массива
                cout << "Простые числа из введенного массива: ";
                for (int num : primes) {
                    cout << num << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 20:{
            int n;
               cout << "Введите количество чисел в массиве: ";
               cin >> n;

               vector<int> numbers(n);
               cout << "Введите числа: ";
               for (int i = 0; i < n; ++i) {
                   cin >> numbers[i];
               }

               int result = totalBits(numbers);
               cout << "Суммарное минимальное количество битов для представления всех чисел: " << result << endl;

               return 0;
            break;
        }
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
    }
    
    return 0;
}
