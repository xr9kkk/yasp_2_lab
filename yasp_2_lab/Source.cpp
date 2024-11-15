#include "date.h"

//������������ ������ 2 ����� 9
//�����: ������ ����
//������� ����� Date ��� ������ � ������ � ������� ���.��.����.����
//�������������� ���������� � ����� ������ ���� unsigned short int: ��� ���� ������
//� ���.����� ������ �������� �� ����� ���� �������� ������������� : �������,
//������� ���� ���.��.����(��������, �02.08.2023�) � ���������� �����
//��� ������ � �����.����������� ������ ���� ����������� : ���������� ���� �e���
//�������� ���������� ����, ��������� ��������� ���������� ���� �� ����,
//����������� ������������ ����, ���������� � ��������� ��������� ������ (���,�����, ����),
//��������� ��� (��, �����, �����), ���������� ���������� ���� ����� ������.



// �������� ������� ����
void menu() {
    int option;
    Date current_date;
    do {
        std::cout << "\n����:\n"
            << "1. ������ ���� (�������)\n"
            << "2. ������ ���� (�������)\n"
            << "3. ������ ���� (���������� ��� ������)\n"
            << "4. ���� ���� �� �����\n"
            << "5. ��������� ���� � ����\n"
            << "6. ������� ���� �� �����\n"
            << "7. ������� ��� � �����\n"
            << "8. ������� ��� �� ����\n"
            << "9. ��������� ������������ ����\n"
            << "10. �������� ����\n"
            << "0. �����\n";

        while (true) {
            std::cout << "�������� ����� ����: ";
            std::cin >> option;

            if (!std::cin.fail()) {
                break;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ������� ��������� �����
                std::cout << "������������ ����. ����������, ������� �����.\n";
            }
        }

        switch (option) {
        case 1: {
            unsigned short d, m, y;
            std::cout << "������� ����: ";
            std::cin >> d;
            std::cout << "������� �����: ";
            std::cin >> m;
            std::cout << "������� ���: ";
            std::cin >> y;
            current_date = Date(d, m, y);
            if (!current_date.is_initialized_check()) {
                std::cout << "������������ ����.\n";
            }
            break;
        }
        case 2: {
            std::string date_str;
            std::cout << "������� ���� � ������� ��.��.����: ";
            std::cin >> date_str;
            current_date = Date(date_str);
            if (!current_date.is_initialized_check()) {
                std::cout << "������������ ����.\n";
            }
            break;
        }
        case 3: {
            unsigned short y, m, d;
            std::cout << "������� ���, ����� � ����: ";
            std::cin >> y >> m >> d;
            current_date = Date(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d));
            if (!current_date.is_initialized_check()) {
                std::cout << "������������ ����.\n";
            }
            break;
        }
        case 4: {
            std::string filename;
            std::cout << "������� ��� ����� ��� ������ ����: ";
            std::cin >> filename;
            std::ifstream infile(filename);
            if (infile.is_open()) {
                std::string date_str;
                infile >> date_str;
                current_date = Date(date_str);
                infile.close();
                if (current_date.is_initialized_check()) {
                    std::cout << "���� ���������: " << current_date << '\n';
                }
                else {
                    std::cout << "������������ ���� � �����.\n";
                }
            }
            else {
                std::cerr << "������ �������� �����.\n";
            }
            break;
        }
        case 5: {
            std::string filename;
            std::cout << "������� ��� ����� ��� ������ ����: ";
            std::cin >> filename;
            current_date.save_to_file(filename);
            std::cout << "���� ��������� � ����.\n";
            break;
        }
        case 6:
            std::cout << "������� ����: " << current_date << '\n';
            break;
        case 7: {
            int days_to_add;
            std::cout << "������� ���������� ���� ��� ����������: ";
            std::cin >> days_to_add;
            current_date = current_date + days_to_add;
            std::cout << "����� ����: " << current_date << '\n';
            break;
        }
        case 8: {
            int days_to_subtract;
            std::cout << "������� ���������� ���� ��� ���������: ";
            std::cin >> days_to_subtract;
            current_date = current_date - days_to_subtract;
            std::cout << "����� ����: " << current_date << '\n';
            break;
        }
        case 9: {
            if (current_date.is_leap_year()) {
                std::cout << "��� " << current_date.get_year() << " �������� ����������.\n";
            }
            else {
                std::cout << "��� " << current_date.get_year() << " �� �������� ����������.\n";
            }
            break;
        }
        case 10: {
            std::string compare_date_str;
            std::cout << "������� ���� ��� ��������� (��.��.����): ";
            std::cin >> compare_date_str;
            Date compare_date(compare_date_str);
            if (!compare_date.is_initialized_check()) {
                std::cout << "������������ ���� ��� ���������.\n";
            }
            else {
                if (current_date < compare_date) {
                    std::cout << "������� ���� ������ ���������.\n";
                }
                else if (current_date > compare_date) {
                    std::cout << "������� ���� ����� ���������.\n";
                }
                else {
                    std::cout << "���� �����.\n";
                }
                int days_between = current_date.days_between(compare_date);
                std::cout << "���������� ���� ����� ������: " << days_between << '\n';
            }
            break;
        }
        case 0:
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "������������ �����. ����������, �������� ������ �����.\n";
            break;
        }
    } while (option != 0);
}

int main() {
    setlocale(LC_ALL, "ru");
    menu();
    return 0;
}
