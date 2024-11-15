#include "date.h"

//лабораторная работа 2 номер 9
//Автор: Козлов Иван
//Создать класс Date для работы с датами в формате «дд.мм.гггг».Дата
//представляется структурой с тремя полями типа unsigned short int: для года месяца
//и дня.Класс должен включать не менее трех способов инициализации : числами,
//строкой вида «дд.мм.гггг»(например, «02.08.2023») и встроенным типом
//для работы с датой.Обязательно должны быть реализованы : вычисление даты чeрез
//заданное количество дней, вычитание заданного количества дней из даты,
//определение високосности года, присвоение и получение отдельных частей (год,месяц, день),
//сравнение дат (до, после, равно), вычисление количества дней между датами.



// Основная функция меню
void menu() {
    int option;
    Date current_date;
    do {
        std::cout << "\nМеню:\n"
            << "1. Ввести дату (числами)\n"
            << "2. Ввести дату (строкой)\n"
            << "3. Ввести дату (встроенный тип данных)\n"
            << "4. Ввод даты из файла\n"
            << "5. Сохранить дату в файл\n"
            << "6. Вывести дату на экран\n"
            << "7. Сложить дни с датой\n"
            << "8. Вычесть дни из даты\n"
            << "9. Проверить високосность года\n"
            << "10. Сравнить даты\n"
            << "0. Выход\n";

        while (true) {
            std::cout << "Выберите пункт меню: ";
            std::cin >> option;

            if (!std::cin.fail()) {
                break;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Пропуск неверного ввода
                std::cout << "Некорректный ввод. Пожалуйста, введите число.\n";
            }
        }

        switch (option) {
        case 1: {
            unsigned short d, m, y;
            std::cout << "Введите день: ";
            std::cin >> d;
            std::cout << "Введите месяц: ";
            std::cin >> m;
            std::cout << "Введите год: ";
            std::cin >> y;
            current_date = Date(d, m, y);
            if (!current_date.is_initialized_check()) {
                std::cout << "Некорректная дата.\n";
            }
            break;
        }
        case 2: {
            std::string date_str;
            std::cout << "Введите дату в формате дд.мм.гггг: ";
            std::cin >> date_str;
            current_date = Date(date_str);
            if (!current_date.is_initialized_check()) {
                std::cout << "Некорректная дата.\n";
            }
            break;
        }
        case 3: {
            unsigned short y, m, d;
            std::cout << "Введите год, месяц и день: ";
            std::cin >> y >> m >> d;
            current_date = Date(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d));
            if (!current_date.is_initialized_check()) {
                std::cout << "Некорректная дата.\n";
            }
            break;
        }
        case 4: {
            std::string filename;
            std::cout << "Введите имя файла для чтения даты: ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (infile.is_open()) {
                std::string date_str;
                infile >> date_str;
                current_date = Date(date_str);
                infile.close();
                if (current_date.is_initialized_check()) {
                    std::cout << "Дата загружена: " << current_date << '\n';
                }
                else {
                    std::cout << "Некорректная дата в файле.\n";
                }
            }
            else {
                std::cerr << "Ошибка открытия файла.\n";
            }
            break;
        }
        case 5: {
            std::string filename;
            std::cout << "Введите имя файла для записи даты: ";
            std::cin >> filename;
            current_date.save_to_file(filename);
            std::cout << "Дата сохранена в файл.\n";
            break;
        }
        case 6:
            std::cout << "Текущая дата: " << current_date << '\n';
            break;
        case 7: {
            int days_to_add;
            std::cout << "Введите количество дней для добавления: ";
            std::cin >> days_to_add;
            current_date = current_date + days_to_add;
            std::cout << "Новая дата: " << current_date << '\n';
            break;
        }
        case 8: {
            int days_to_subtract;
            std::cout << "Введите количество дней для вычитания: ";
            std::cin >> days_to_subtract;
            current_date = current_date - days_to_subtract;
            std::cout << "Новая дата: " << current_date << '\n';
            break;
        }
        case 9: {
            if (current_date.is_leap_year()) {
                std::cout << "Год " << current_date.get_year() << " является високосным.\n";
            }
            else {
                std::cout << "Год " << current_date.get_year() << " не является високосным.\n";
            }
            break;
        }
        case 10: {
            std::string compare_date_str;
            std::cout << "Введите дату для сравнения (дд.мм.гггг): ";
            std::cin >> compare_date_str;
            Date compare_date(compare_date_str);
            if (!compare_date.is_initialized_check()) {
                std::cout << "Некорректная дата для сравнения.\n";
            }
            else {
                if (current_date < compare_date) {
                    std::cout << "Текущая дата раньше введенной.\n";
                }
                else if (current_date > compare_date) {
                    std::cout << "Текущая дата позже введенной.\n";
                }
                else {
                    std::cout << "Даты равны.\n";
                }
                int days_between = current_date.days_between(compare_date);
                std::cout << "Количество дней между датами: " << days_between << '\n';
            }
            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, выберите другой пункт.\n";
            break;
        }
    } while (option != 0);
}

int main() {
    setlocale(LC_ALL, "ru");
    menu();
    return 0;
}
