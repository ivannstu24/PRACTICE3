#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>


using namespace std;


// (1) Студенты и экзамен

struct Student {
    string name;
    int score;
};

struct FailedStudent {
    string name;
    string reason;
};



// (2) Задача жадного продавца

vector<int> make_change(int amount, const vector<int>& coins) {
    vector<int> change;
    int remaining = amount;

    // Сортируем монеты по убыванию для жадного алгоритма
    vector<int> sorted_coins = coins;
    sort(sorted_coins.begin(), sorted_coins.end(), greater<int>());

    // Жадный алгоритм для выдачи сдачи
    for (int coin : sorted_coins) {
        while (remaining >= coin) {
            change.push_back(coin);
            remaining -= coin;
        }
    }

    return change;
}

// (3) Хогвартс и совы

bool can_deliver_all_letters(const vector<int>& letters, const vector<int>& owls) {
    // Проверим, сможет ли каждая сова доставить все письма на свой факультет
    return equal(letters.begin(), letters.end(), owls.begin(), [](int l, int o) {
        return o >= l;
    });
}


// (4) Функция для проверки, являются ли два вектора перестановками друг друга

bool are_permutations(const vector<int>& vec1, const vector<int>& vec2) {
    if (vec1.size() != vec2.size()) {
        cout << "Векторы не могут быть перестановками друг друга, размеры не совпадают!\n";
        return false;// Если размеры векторов не совпадают, они не могут быть перестановками друг друга
    }

    // Создаем копии векторов для сортировки
    vector<int> sorted_vec1 = vec1;
    vector<int> sorted_vec2 = vec2;

    // Сортируем два вектора
    sort(sorted_vec1.begin(), sorted_vec1.end());
    sort(sorted_vec2.begin(), sorted_vec2.end());
    

    // Если отсортированные векторы равны, то исходные векторы являются перестановками друг друга
    return sorted_vec1 == sorted_vec2;
}

// (5) Функция проверки, можно ли составить слово из букв
bool canFormWord(const std::string& word, std::string letters) {
    for (char c : word) {
        auto it = std::find(letters.begin(), letters.end(), c);
        if (it == letters.end()) {
            return false;
        }
        letters.erase(it); // Удалить использованную букву
    }
    return true;
}

// Функция загрузки словаря из файла
std::vector<std::string> loadDictionary(const std::string& filename) {
    std::vector<std::string> dictionary;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    return dictionary;
}



// (6) можно ли из букв первого слова составить второе

bool can_form_word(const string& first, const string& second) {
    // Создаем копии строк для обработки
    string first_copy = first;
    string second_copy = second;

    // Сортируем символы в обеих строках
    sort(first_copy.begin(), first_copy.end());
    sort(second_copy.begin(), second_copy.end());

    // Проверяем, можно ли из букв первого слова составить второе слово
    return includes(first_copy.begin(), first_copy.end(), second_copy.begin(), second_copy.end());
    }


// (8) Если хотя бы один элемент вектора делится по заданому модулю без остатка, то все элементы вектора выводятся в кавдрате

void squareElements(vector<int>& vec) {
    transform(vec.begin(), vec.end(), vec.begin(), [](int num) {
        return num * num;
    });
}


// (10) Если хотя бы из одного элемента вектора можно извлечь квалрат, то все элементы вектора реверсятся

bool hasPerfectSquare(const vector<int>& nums) {
    return any_of(nums.begin(), nums.end(), [](int n) {
        int root = static_cast<int>(sqrt(n));
        return root * root == n;
    });
}

// (13) Сжатие строки

string compressString(const string& str) {
    // Удаление последовательных повторяющихся символов
    string compressed = str;
    auto it = unique(compressed.begin(), compressed.end());
    compressed.erase(it, compressed.end());

    // Подсчет количества повторений для каждого символа
    string result;
    for (char ch : compressed) {
        int count = std::count(str.begin(), str.end(), ch);
        result += ch + to_string(count);
    }

    return result;
}


// (16) Переместить все четные числа в конец вектора, сохраняя их порядок.

void moveEvenNumbersToEnd(vector<int>& nums) {
    stable_partition(nums.begin(), nums.end(), [](int num) {

        return num % 2 != 0;
    });
}



// (18) Разделить вектор на два, один содержащий положительные элементы, а другой — отрицательные.
pair<vector<int>, vector<int>> divideVector(const vector<int>& vec) {
    vector<int> positiveVec;
    vector<int> negativeVec;

    partition_copy(vec.begin(), vec.end(), back_inserter(positiveVec), back_inserter(negativeVec),
                        [](int i) { return i >= 0; }); // копируем элементы, которые удовлетворяют предикату(больше или равны нулю) в положительные, те что не удовлетворяют идут в отрицательные

    return make_pair(positiveVec, negativeVec);
}

// Фейсконтроль
struct Visitor {
    string name;
    int age;
    bool is_vip;
};

struct RejectedVisitor {
    string name;
    string reason;
};


int main() {
    int choice;
    
    cout << "1. Студенты и экзамен\n";
    cout << "2. Задача жадного продавца\n";
    cout << "3. Задача про Хогвартс и сов\n";
    cout << "4. Являются ли векторы перестановками друг друга\n";
    cout << "5. Найти все слова из словаря, которые можно составить из введеных букв\n";
    cout << "6. Можно ли из букв первого слова составить второе слово\n";
    cout << "7. Нахождение количества уникальных чисел в векторе\n";
    cout << "8. Если хотя бы один элемент вектора делится по заданному модулю без остатка, то все элементы вектора выводятся в квадрате\n";
    cout << "9. Ротация вектора на K элементов\n";
    cout << "10. Если хотя бы из одного элемента вектора можно извлечь квадрат, то все элементы вектора переворачиваются\n";
    cout << "11. Нахождение разности двух множеств\n";
    cout << "12. Каждые три элемента вектора складываются в число и конвертируются в символ ASCII\n";
    cout << "13. Сжатие строки\n";
    cout << "14. Анализ пробега автомобиля\n";
    cout << "15. Фейсконтроль\n";
    cout << "16. Переместить все четные числа в конец вектора, сохраняя их порядок\n";
    cout << "17. Найти сумму квадратов элементов вектора\n";
    cout << "18. Разделить вектор на два, один содержащий положительные элементы, а другой — отрицательные.\n";
    cout << "19. Строка, которая содержит два или более одинаковых символов переворачивается\n";
    cout << "20. Заменить все четные числа в векторе на их квадраты\n";


    cout << "Выбор: ";
    cin >> choice;
    
    cin.ignore();
    
   
    
    switch (choice) {
        case 1: {
            int n;
                cout << "Введите количество студентов: ";
                cin >> n;
                
                vector<Student> students(n);
                
                cout << "Введите имя и оценку каждого студента:" << endl;
                for (int i = 0; i < n; ++i) {
                    cin >> students[i].name >> students[i].score;
                }
                
                // Разделяем студентов на сдавших и не сдавших экзамен
                auto it = partition(students.begin(), students.end(), [](const Student& s) {
                    return s.score >= 50;
                });
                
                vector<Student> passed_students(students.begin(), it);
                vector<Student> failed_students(it, students.end());
                
                vector<FailedStudent> detailed_failed_students;
                
                // Формируем список не сдавших с указанием причины
                transform(failed_students.begin(), failed_students.end(), back_inserter(detailed_failed_students), [](const Student& s) {
                    return FailedStudent{s.name, "недостаточный балл"};
                });
                
                
                cout << "Сдавшие экзамен:" << endl;
                for_each(passed_students.begin(), passed_students.end(), [](const Student& s) {
                    cout << s.name;
                    if (s.score >= 85) {
                        cout << " - отлично";
                    }
                    cout << endl;
                });
                
                cout << endl << "Провалившие экзамен:" << endl;
                for_each(detailed_failed_students.begin(), detailed_failed_students.end(), [](const FailedStudent& s) {
                    cout << s.name << " - " << s.reason << endl;
                });

                return 0;
            break;
        }
        case 2: {
            // Набор доступных монет
                vector<int> coins = {1, 10, 25, 50, 100, 300, 500};

                // Ввод суммы для выдачи сдачи
                int amount;
                cout << "Введите сумму для выдачи сдачи: ";
                cin >> amount;

                // Получение сдачи
                vector<int> change = make_change(amount, coins);

                // Вывод результата
                cout << "Сдача для " << amount << ": ";
                for (int coin : change) {
                    cout << coin << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 3:{
            
            cout << "\n";

            cout << "Есть четыре факультета в Хогвартсе, каждому из которых нужно доставить определённое количество писем. Каждый факультет получает письма от одной совы. Нужно проверить, может ли каждая сова доставить все письма на свой факультет.\n";
            cout << "\n";

            
            vector<int> letters(4);
            vector<int> owls(4);

            cout << "Введите количество писем для каждого факультета (4 числа): ";
                for (int i = 0; i < 4; ++i) {
                    cin >> letters[i];
                }

            cout << "Введите количество писем, которые может доставить каждая сова (4 числа): ";
                for (int i = 0; i < 4; ++i) {
                    cin >> owls[i];
                }

                if (can_deliver_all_letters(letters, owls)) {
                    std:: cout << "Каждая сова может доставить все письма." << endl;
                } else {
                    cout << "Не каждая сова может доставить все письма." << endl;
                }

                return 0;
            
            break;
        }
        case 4:{
                cout << "Введите размер первого вектора: ";
                int size1;
                cin >> size1;
                vector<int> vec1(size1);
                cout << "Введите элементы первого вектора: ";
                for (int i = 0; i < size1; ++i) {
                    cin >> vec1[i];
                }

               
                cout << "Введите размер второго вектора: ";
                int size2;
                cin >> size2;
                vector<int> vec2(size2);
                cout << "Введите элементы вторго вектора: ";
                for (int i = 0; i < size2; ++i) {
                    cin >> vec2[i];
                }

                // Проверка, являются ли векторы перестановками друг друга
                if (are_permutations(vec1, vec2)) {
                    cout << "Векторы перестановки друг друга.\n";
                } else {
                    cout << "Векторы не являются перестановками друг друга.\n";
                }

                return 0;
            break;
        }
        case 5:{
            std::string letters;
               std::cout << "Введите буквы: ";
               std::cin >> letters;

               // Загрузка словаря
               std::vector<std::string> dictionary = loadDictionary("/Users/ivanmerzov/Desktop/PRACTICE3.2/PRACTICE3.2/ditionary.txt");

               // Вектор для хранения подходящих слов
               std::vector<std::string> validWords;

               // Проверка слов из словаря
               std::copy_if(dictionary.begin(), dictionary.end(), std::back_inserter(validWords),
                            [&letters](const std::string& word) { return canFormWord(word, letters); });

               if (validWords.empty()) {
                   std::cout << "Нет подходящих слов.\n";
               } else {
                   std::cout << "Подходящие слова:\n";
                   for (const auto& word : validWords) {
                       std::cout << word << '\n';
                   }
               }

               return 0;
            break;
        }
        case 6:{
            string first, second;
                cout << "Введите первое слово: ";
                cin >> first;
                cout << "Введите второе слово: ";
                cin >> second;

                // Проверяем, можно ли из букв первого слова составить второе слово
                if (can_form_word(first, second)) {
                    cout << "Из букв первого слова возможно составить второе.\n";
                } else {
                    cout << "Из букв первого слова невозможно составить второе.\n";
                }

                return 0;
            break;
        }
        case 7:{
            int n;
               cout << "Введите количество элементов: ";
               cin >> n;

               vector<int> nums;
               cout << "Введите элементы:\n";
               for (int i = 0; i < n; ++i) {
                   int num;
                   cin >> num;
                   nums.push_back(num);
               }

               // сортируем введенные числа для удобства
               sort(nums.begin(), nums.end());
            // после сортировки все одинаковые элементы будут раядом, что позволит unique эффективнее удалять дубликаты

               // удаление дубликатов
               auto last = unique(nums.begin(), nums.end());

               // Вычислим количество уникальных чисел
               int unique_count = distance(nums.begin(), last);

               cout << "Количество уникальных элементов: " << unique_count << endl;

               return 0;
            break;
        }
        case 8:{
            vector<int> vec;
                int size;
                cout << "Введите размер вектора: ";
                cin >> size;

                cout << "Введите элементы вектора: ";
                for (int i = 0; i < size; ++i) {
                    int num;
                    cin >> num;
                    vec.push_back(num);
                }

                int modulo;
                cout << "Введите модуль: ";
                cin >> modulo;

                // Проверяем, есть ли хотя бы один элемент, который делится на заданный модуль без остатка
                bool divisibleByModulo = any_of(vec.begin(), vec.end(), [modulo](int num) {
                    return num % modulo == 0;
                });

                // Если есть, возводим все элементы в квадрат
                if (divisibleByModulo) {
                    squareElements(vec);
                    cout << "Все элементы вектора были возведены в квадрат." << endl;
                } else {
                    cout << "Нет элемента вектора, который делится на " << modulo << " без остатка." << endl;
                }

                cout << "Итоговый вектор: ";
                for (int num : vec) {
                    cout << num << " ";
                }
                cout << endl;

                return 0;
            break;
        }
            
        case 9:{
            int n, k;
               cout << "Введите количество элементов: ";
               cin >> n;

               vector<int> nums(n);
               cout << "Введите элементы:\n";
               for (int i = 0; i < n; ++i) {
                   cin >> nums[i];
               }

               cout << "Введите количество позиций для ротации: ";
               cin >> k;

               k = k % n; // убедиться, что k находится в пределах размера массива
               rotate(nums.begin(), nums.begin() + k, nums.end());

               cout << "Вектор после ротации: ";
               for (int num : nums) {
                   cout << num << " ";
               }
               cout << endl;

               return 0;
            break;
        }
        case 10:{
            vector<int> nums;
                int n, value;

                cout << "Введите количество элементов вектора: ";
                cin >> n;

                cout << "Введите элементы вектора: ";
                for (int i = 0; i < n; ++i) {
                    cin >> value;
                    nums.push_back(value);
                }

                // Проверяем, можно ли извлечь квадратный корень без остатка хотя бы из одного элемента
                if (hasPerfectSquare(nums)) {
                    reverse(nums.begin(), nums.end());
                }

                cout << "Результат: ";
                for (const auto& num : nums) {
                    cout << num << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 11:{
            // Первое множество
               int n1;
               cout << "Введите размер первого множества: ";
               cin >> n1;

               vector<int> set1(n1);
               cout << "Введите элементы первого множества: ";
               for (int i = 0; i < n1; ++i) {
                   cin >> set1[i];
               }

               // Второе множество
               int n2;
               cout << "Введите размер второго множества: ";
               cin >> n2;

               vector<int> set2(n2);
               cout << "Введите элементы второго множества: ";
               for (int i = 0; i < n2; ++i) {
                   cin >> set2[i];
               }

               // Результирующий вектор для разности множеств
               vector<int> difference;

               sort(set1.begin(), set1.end());
               sort(set2.begin(), set2.end());

               // Нахождение разности множеств
               set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(difference));

            
               cout << "Разность множеств: ";
               for (int num : difference) {
                   cout << num << " ";
               }
               cout << endl;

               return 0;
            break;
        }
        case 12:{
            vector<int> numbers;
                int input;

                cout << "Введите числа для вектора (-1 для завершения ввода): " << endl;
                while (cin >> input && input != -1) {
                    numbers.push_back(input);
                }

                // Проверка, что размер вектора кратен 3
                if (numbers.size() % 3 != 0) {
                    cout << "Размер вектора должен быть кратен 3." << endl;
                    return 1;
                }

                // Вектор для хранения символов
                vector<char> chars;

                // Суммирование трёх элементов и преобразование в символ ASCII
                for (size_t i = 0; i < numbers.size(); i += 3) {
                    int sum = numbers[i] + numbers[i + 1] + numbers[i + 2];
                    chars.push_back(static_cast<char>(sum));
                }

                
                cout << "Результирующие символы: ";
                for_each(chars.begin(), chars.end(), [](char c) {
                    cout << c << ' ';
                });
                cout << endl;

                return 0;
            break;
        }
        case 13:{
            string str;
               cout << "Введите строку для сжатия: ";
               cin >> str;

               string compressed = compressString(str);
               cout << "Сжатая строка: " << compressed << endl;

               return 0;
        }
        case 14:{
            vector<double> mileages;
                double input;

                
                cout << "Введите пробеги такси (введите -1 для завершения ввода): " << endl;
                while (cin >> input && input != -1) {
                    mileages.push_back(input);
                }

                // Проверка, что список не пуст
                if (mileages.empty()) {
                    cout << "Список пробегов такси пуст." << endl;
                    return 1;
                }

                // Вычисление среднего пробега
                double total_mileage = 0;
                for_each(mileages.begin(), mileages.end(), [&](double mileage) {
                    total_mileage += mileage;
                });
                double average_mileage = total_mileage / mileages.size();

                cout << "Средний пробег: " << average_mileage << endl;

                cout << "Пробеги, которые выше среднего: ";
                for_each(mileages.begin(), mileages.end(), [&](double mileage) {
                    if (mileage > average_mileage) {
                        cout << mileage << " ";
                    }
                });
                cout << endl;

                return 0;
            break;
        }
        case 15:{
            int n;
               cout << "Введите количество посетителей: ";
               cin >> n;

               vector<Visitor> visitors(n);

               cout << "Введите имя, возраст и VIP-статус (1 для VIP, 0 для обычных) каждого посетителя:" << endl;
               for (int i = 0; i < n; ++i) {
                   cin >> visitors[i].name >> visitors[i].age >> visitors[i].is_vip;
               }

               vector<Visitor> allowed_visitors;
               vector<RejectedVisitor> rejected_visitors;

               // Фильтрация посетителей
               for_each(visitors.begin(), visitors.end(), [&](const Visitor& v) {
                   if (v.age >= 18 || v.is_vip) {
                       allowed_visitors.push_back(v);
                   } else {
                       rejected_visitors.push_back({v.name, "недостаточный возраст"});
                   }
               });

               cout << "Пропущенные посетители:" << endl;
               for_each(allowed_visitors.begin(), allowed_visitors.end(), [](const Visitor& v) {
                   cout << v.name << endl;
               });

               cout << endl << "Не пропущенные посетители и причины:" << endl;
               for_each(rejected_visitors.begin(), rejected_visitors.end(), [](const RejectedVisitor& rv) {
                   cout << rv.name << " - " << rv.reason << endl;
               });

               return 0;
            break;
        }
        case 16:{
            int size;
                cout << "Введите размер вектора: ";
                cin >> size;

                vector<int> nums(size);
                cout << "Введите элементы вектора:\n";
                for (int i = 0; i < size; ++i) {
                    cin >> nums[i];
                }
                
                cout << "Исходный вектор: ";
                for (int num : nums) {
                    cout << num << " ";
                }
                cout << endl;

                moveEvenNumbersToEnd(nums);

                cout << "Модифицированный вектор: ";
                for (int num : nums) {
                    cout << num << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 17:{
            vector<int> vec;
                int num_elements;

                cout << "Введите количество элементов в векторе: ";
                cin >> num_elements;

                cout << "Введите элементы вектора: ";
                for (int i = 0; i < num_elements; ++i) {
                    int element;
                    cin >> element;
                    vec.push_back(element);
                }

                // Переменная для хранения суммы квадратов элементов
                int sum_of_squares = 0;

                // вычисление суммы квадратов элементов
                for_each(vec.begin(), vec.end(), [&sum_of_squares](int x) {
                    sum_of_squares += x * x;
                });

                cout << "Сумма квадратов элементов вектора: " << sum_of_squares << endl;

                return 0;
            break;
        }
            
        case 18:{
            
                int n;
                cout << "Введите количество элементов: ";
                cin >> n;

                
                vector<int> numbers(n);
                cout << "Введите элементы: ";
                for (int i = 0; i < n; ++i) {
                    cin >> numbers[i];
                }

                // Разделяем вектор на положительные и отрицательные значения
                auto dividedVectors = divideVector(numbers);

                // Положительный вектор
                vector<int> positiveVec = dividedVectors.first;
                // Отрицательный вектор
                vector<int> negativeVec = dividedVectors.second;

               
                cout << "Вектор положительных элементов: ";
                for (int num : positiveVec) {
                    cout << num << " ";
                }
                cout << endl;

                
                cout << "Вектор отрицательных элементов: ";
                for (int num : negativeVec) {
                    cout << num << " ";
                }
                cout << endl;

                return 0;
            break;
        }
        case 19:{
            string input;
               cout << "Введите строку: ";
               getline(cin, input);

               // Проверяем, есть ли символ, встречающийся больше двух раз или два раза
               bool has_repeating_chars = any_of(input.begin(), input.end(), [&](char c) {
                   return count(input.begin(), input.end(), c) >= 2;
               });

               if (has_repeating_chars) {

                   reverse(input.begin(), input.end());
               }

               cout << "Результат: " << input << endl;

               return 0;
            break;
        }
        case 20:{
            vector<int> vec;
               int n;

               cout << "Введите количество элементов вектора: ";
               cin >> n;

               cout << "Введите элементы вектора: ";
               for (int i = 0; i < n; ++i) {
                   int element;
                   cin >> element;
                   vec.push_back(element);
               }

               for_each(vec.begin(), vec.end(), [](int& x) {
                   if (x % 2 == 0) {
                       x = x * x;
                   }
               });

               cout << "Обработанный вектор: ";
               for (const int& x : vec) {
                   cout << x << " ";
               }
            
            cout << endl;
               return 0;
            break;
        }
       
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
    }
    
    return 0;
}
