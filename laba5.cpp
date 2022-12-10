#include <iostream>
#include <iomanip>
// iomanip либа для постановки незначащих нулей через cout, нужна для красивого вывода даты.

using namespace std;

// возвращает true если год вискосный и false если нет
bool isALeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}


// структура даты. Состоит из дня, месяца и года даты.
struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

// перечесление месяцов, отсчёт начинается с января как с первого месяца, до декабря как двенадцатого месяца.
enum Months {
    Jan = 1,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

// Подсчёт дней в месяце
unsigned int countMonthsDays(Date date) {
    if (date.month > 12 || date.month < 1) {
        return 0;
    }
    else {
        if (date.month == Months::Feb) {
            if (isALeapYear(date.year)) {
                return 29;
            }
            else {
                return 28;
            }
        }
        else if ( date.month == Months::Jan || date.month == Months::Mar || date.month == Months::May ||
                date.month == Months::Jul || date.month == Months::Aug || date.month == Months::Oct || date.month == Months::Dec ) {
            return 31;
        }
        else {
            return 30;
        }
    }
}

// функция возвращает true если месяц введен корректно и false если нет
bool isDateCorrectlyEntered(Date date) {
    if ((date.month >= 1 && date.month <= 12) && date.year >= 1) {
        if (date.day <= countMonthsDays(date) && date.day >= 1) {
            return true;
        }
        return false;
    }
    return false;
}


// посчитать дни от 01.01.0001 года до переданной в функцию даты.
unsigned long int countDaysTillDate(Date date) {
    unsigned long int sum = 0;
    for (unsigned int y = 1; y < date.year; y++) {
        if (isALeapYear(y)) sum += 366;
        else sum += 365;
    }

    for (unsigned int m = 1; m < date.month; m++) {
        sum += countMonthsDays({ 1, m, date.year });
    }

    sum += date.day;

    return sum;
}

// очистка памяти динамического массива структур date
void clearMemory(Date* date) {
    delete[] date;
}

// Вывод общей информации о пользовании командами для ввода в консоль
void printInformation() {
    cout << "Here's what you can do with dates you have just typed in:" << endl;
    cout << "1. Check max days in your particular date's month:" << endl;
    cout << "2. Check if date entered correctly (also works for future dates):" << endl;
    cout << "3. Count how many days have passed from the beginning of calendar until the date you have entered:" << endl;
    cout << "4. Add date to the pool" << endl;
    cout << "5. Remove date from the pool" << endl;
    cout << "6. Print all dates in the pool" << endl;
    cout << "7. Clear console outputs" << endl;
    cout << "F. Finish the program" << endl;
}

// очистить консоль (директивы использованы из-за теста на онлайн компиляторе. Так как там стоял сервер на линуксе,
// пришлось добавить проверку системы машины на которой запускается код)
void clearConsole()
{
    // проверка на окна
#if defined _WIN32
    system("cls");
    // прроверка на пингвина
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // проверка на яблоко
#elif defined (__APPLE__)
    system("clear");
#endif
}


int main()
{
    unsigned int size = 1;
    cout << "Enter how much dates are you going to work with" << endl;
    cin >> size;
    
    // массив дат
    Date* dates = new Date[size];

    cout << "Enter date/dates. Format: | dd/mm/yyyy or dd.mm.yyyy | (date per line)" << endl;
    
    // введение даты, с учетом что она введена в соответствии требуемому формату
    for (int i = 0; i < size; i++) {
        unsigned int d, m, y;

        cin >> d;
        cin.get();
        cin >> m;
        cin.get();
        cin >> y;

        dates[i] = { d, m, y };
    }

    // вывод общей информации
    printInformation();

    char command;
    // запрос на введение команды для работы с датами, для завершения нужно ввести F.
    do {
        cout << "Enter your command:" << endl;
        cin >> command;
        cout << endl;

        switch (command)
        {
        case '1':  // посчитать дни для всех дат в массиве по номеру.
            for (int i = 0; i < size; i++) {
                cout << i + 1 << ". " << countMonthsDays(dates[i]) << " days." << endl;
            }
            break;
        case '2':  // посмотреть корректно ли введены все даты в массиве по номеру.
            for (int i = 0; i < size; i++) {
                if (isDateCorrectlyEntered(dates[i])) {
                    cout << i + 1 << ". " << "Date entered correctly." << endl;
                }
                else {
                    cout << i + 1 << ". " << "Date entered wrongly." << endl;
                }
            }
            break;
        case '3':  // посчитать дни от 01.01.0001 до всех введенных дат в массве по номеру
            for (int i = 0; i < size; i++) {
                if (isDateCorrectlyEntered(dates[i])) {
                    cout << i + 1 << ". " << countDaysTillDate(dates[i]) << " days from the beginning of calendar until date." << endl;
                }
            }
            break;
        case '4':  // Добавить дату в массив дат
            cout << "Enter date. Format: | dd/mm/yyyy or dd.mm.yyyy" << endl;
            unsigned int d, m, y;

            cin >> d;
            cin.get();
            cin >> m;
            cin.get();
            cin >> y;

            // блок, в котором довыделяется память для новой даты и эта дата добавляется в конец массива.
            {
                Date* tmpDates = new Date[size];
                for (int i = 0; i < size; i++) {
                    tmpDates[i] = dates[i];
                }
                clearMemory(dates);
                dates = new Date[size + 1];
                for (int i = 0; i < size; i++) {
                    dates[i] = tmpDates[i];
                }
                dates[size] = { d, m, y };
                clearMemory(tmpDates);
                size++;
            }

            break;
        case '5':  // удалить дату из массива
            if (size != 0) {
                unsigned int elemToDelete;
                cout << "Which element do you want to delete?" << endl;
                cin >> elemToDelete;
                // блок в котором удаляется выбранный элемент из массива, размер массива при этом уменьшается на один
                {
                    for (unsigned int i = elemToDelete - 1; i < size - 1; i++) {
                        Date tmpdate = dates[i];
                        dates[i] = dates[i + 1];
                        dates[i + 1] = tmpdate;
                    }
                    Date* tmpDates = new Date[size - 1];
                    for (int i = 0; i < size - 1; i++) {
                        tmpDates[i] = dates[i];
                    }
                    delete[] dates;
                    dates = new Date[size - 1];
                    for (int i = 0; i < size - 1; i++) {
                        dates[i] = tmpDates[i];
                    }
                    delete[] tmpDates;
                }
                size--;
            }
            else {
                cout << "There are no dates in list" << endl;
            }
            break;
        case '6':  // вывести все даты в стандартном формате.
            cout << "All dates you have entered:" << endl;
            for (int i = 0; i < size; i++) {
                cout << i + 1 << ". " << setfill('0') << setw(2) << dates[i].day << "." << setfill('0') << setw(2) << dates[i].month << "." << setfill('0') << setw(4) << dates[i].year << endl;
            }
            break;
        case '7':  // очистить консоль и вывести список команд
            clearConsole();
            printInformation();
            break;
        default:
            break;
        }
    } while (command != 'F');
    // очищаем память массива дат перед завершением выполнения программы.
    clearMemory(dates);
    return 0;
}
