#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

#pragma pack(push, 1)

enum Speciality { KN, IT, ME, FI, T };
string speciality_str[] = { "KN","IT", "ME","FI", "T" };
//KN-компютерні науки(програмування), IT- інформатика(чисельні методи), ME-математика та економіка(педагогіка)
//FI- фізика та інформатика(педагогіка), T-трудове навчання(педагогіка)
struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_pedagogy;
    union
    {
        int grade_programming;
        int grade_numerical_methods;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
void Print_first(Students* S, const int N);
void Print_second(Students* S, const int N);
double Percentage_4or5(Students* S, const int N);
double Avarage_marks(Students* S, const int i);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print_first(S, N);
    Print_second(S, N);
    cout << "Процент студентів, які мають 5 або 4 з фізики: " << setprecision(2) << Percentage_4or5(S, N) << "%";

    return 0;
}
void Create(Students* S, const int N)
{
    int speciality;
    for (int i = 0; i < N; i++)
    {       
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність(0 - KB, 1 - RE, 2 - KN,";
        cout << "\n3 - PZ, 4 - KI): ";
        cin >> speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math;
        S[i].speciality = (Speciality)speciality;

        switch (S[i].speciality)
        {
        case KN: 
            cout << "Оцінка з програмування: "; cin >> S[i].grade_programming;
            break;
        case IT: 
            cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_numerical_methods;
            break;
        default:
            cout << "Оцінка з педагогіки: "; cin >> S[i].grade_pedagogy;
        }
        cout << endl;
    }
}
void Print_first(Students* S, const int N)
{
    cout << "==============================================================================================================================" << endl;
    cout << "|  №  |  Прізвище  |  Курс  |  Спеціальність  |  Фізика  |  Математика  |  Програмування  |";
    cout << "  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(3) << S[i].surname << setw(3);
        cout << "|" << setw(4) << S[i].course << setw(4);
        cout << "|" << setw(3) << speciality_str[S[i].speciality] << setw(3);
        cout << "|" << setw(5) << S[i].grade_physics << setw(5);
        cout << "|" << setw(7) << S[i].grade_math << setw(7);
        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(7) << S[i].grade_programming << setw(7);
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(7) << "-" << setw(7) << "|";
            break;
        case IT:
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(8) << S[i].grade_numerical_methods << setw(8);
            cout << "|" << setw(8) << "-" << setw(8) << "|";
            break;
        default:
            cout << "|" << setw(7) << "-" << setw(7);
            cout << "|" << setw(8) << "-" << setw(8);
            cout << "|" << setw(7) << S[i].grade_pedagogy << setw(7) << "|";
        }
        cout << endl;
    }
    cout << "=============================================================================================================================" << endl;
}
double Avarage_marks(Students* S, const int i)
{
    switch (S[i].speciality)
    {
    case KN:
        return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_programming * 1.) / 3.;
    case IT:
        return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_numerical_methods * 1.) / 3.;
    default:
        return (S[i].grade_math * 1. + S[i].grade_physics * 1. + S[i].grade_pedagogy *1.) / 3.;
    }
}
void Print_second(Students* S, const int N)
{
    cout << fixed;
    cout << "=====================================" << endl;
    cout << "|  №  |  Прізвище  |  Середній бал  |" << endl;
    cout << "-------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << i + 1 << setw(3);
        cout << "|" << setw(5) << S[i].surname << setw(4);
        cout << "|" << setw(7) << setprecision(2) << Avarage_marks(S, i) << setw(8) << "|";
        cout << endl;
    }
    cout << "=====================================" << endl;
}
double Percentage_4or5(Students* S, const int N)
{
    int k = 0;
    for (int i = 0; i < N; i++)
        if (S[i].grade_physics == 5 || S[i].grade_physics == 4)
            k++;
    return k / (N * 1.0) * 100;
}