
#include<iostream>
#include<locale>
#include <fstream>

using namespace std;

// Структура для односвязного списка
struct SL {
    int number;
    SL* Next;
};

// Функция добавления элемента в конец односвязного списка
SL* Make_list(SL* Head, int num1) {
    SL* NewItem = new SL; // Создаем новый элемент списка
    NewItem->number = num1; // Записываем переданное значение
    NewItem->Next = NULL; // Устанавливаем указатель на следующий элемент как NULL
    if (Head == NULL) { // Если список пустой
        Head = NewItem; // Теперь он содержит только созданный элемент
    }
    else { // Иначе
        SL* Current = Head; // Указатель на текущий элемент
        while (Current->Next != NULL) {
            Current = Current->Next; // Переходим к следующему элементу
        }
        Current->Next = NewItem; // Добавляем новый элемент в конец списка
    }
    return Head; // Возвращаем начало списка
}

// Функция печати элементов односвязного списка
void Print_Single_List(SL* Head) {
    SL* Current = Head; // Текущий элемент для обхода списка
    while (Current != NULL) {
        cout << Current->number << " "; // Вывод значения текущего элемента
        Current = Current->Next; // Переход к следующему элементу
       
    }
    cout << endl; // Печать новой строки после завершения списка
}


// Функция удаления одинаковых элементов в списках абитуриентов на ПОВТ и ИП
SL* Delet(SL* Head_two, SL* Head) {
    SL* Current = Head_two; // Указатель для обхода списка абитуриентов на ИП
    SL* Current_two = Head; // Указатель для обхода списка абитуриентов на ПОВТ
    SL* Pred_povt = NULL; // Указатель на предыдущий элемент списка абитуриентов на ПОВТ
    while (Current != NULL) { // Пока не кончится список абитуриентов на ИП
        Current_two = Head; // Сбрасываем указатель на начало списка абитуриентов на ПОВТ
        Pred_povt = NULL; // Сбрасываем указатель на предыдущий элемент списка абитуриентов на ПОВТ

        while (Current_two != NULL) { // Пока не кончится список абитуриентов на ПОВТ
            if (Current->number == Current_two->number) { // Если номера абитуриентов совпадают
                if (Pred_povt == NULL) { // Если удаляемый элемент первый в списке на ПОВТ
                    Head = Current_two->Next; // Переназначаем начало списка на следующий элемент
                    delete Current_two; // Удаляем элемент
                    Current_two = Head; // Обновляем указатель на текущий элемент
                }
                else {
                    Pred_povt->Next = Current_two->Next; // Убираем удаляемый элемент из списка на ПОВТ
                    SL* temp = Current_two; // Сохраняем указатель на удаляемый элемент
                    Current_two = Current_two->Next; // Переходим к следующему элементу
                    delete temp; // Удаляем элемент
                }
            }
            else {
                Pred_povt = Current_two; // Сохраняем указатель на текущий элемент как предыдущий
                Current_two = Current_two->Next; // Переходим к следующему элементу
            }
        }
        Current = Current->Next; // Переходим к следующему абитуриенту на ИП
    }

    return Head; // Возвращаем указатель на начало списка абитуриентов на ПОВТ после удаления
}
        


// Функция проверки наличия общих элементов в двух списках и добавления их в третий список
SL* proverka(SL* Head_ip, int n_ip, int n_povt, SL* Head_povt, SL* Head_two) {
    int i = 0;
    int j = 0;
    SL* Current_ip = Head_ip; // Указатель для обхода списка абитуриентов на ИП
    SL* Current_povt = Head_povt; // Указатель для обхода списка абитуриентов на ПОВТ
    while (Current_ip != NULL ) { // Пока не кончится список абитуриентов на ИП
        Current_povt = Head_povt; // Сбрасываем указатель на начало списка абитуриентов на ПОВТ
        while (Current_povt != NULL) { // Пока не кончится список абитуриентов на ПОВТ
            if (Current_ip->number == Current_povt->number) {// Если номера абитуриентов совпадают
                Head_two = Make_list(Head_two,Current_povt->number);// Добавляем общего абитуриента в третий список
                break; // Прерываем внутренний цикл, так как дальше проверять абитуриента на ПОВТ не имеет смысла
            }
            Current_povt = Current_povt->Next; // Переходим к следующему абитуриенту на ПОВТ
            
        }
        Current_ip = Current_ip->Next; // Переходим к следующему абитуриенту на ИП
        
    }
    return Head_two;
}

int main() {
    setlocale(LC_ALL, "ru");
    int n_ip, n_povt, a, b, s1 = 0, s2 = 0;
    ofstream infile("input.dat");
    ofstream outfile("output.dat");
    SL* Head_ip = NULL; // Начало списка абитуриентов на ИП
    SL* Head_povt = NULL; // Начало списка абитуриентов на ПОВТ
    SL* Head_two = NULL; // Начало третьего списка для общих абитуриентов
    cout << "Введите количество человек, поступивших на ИП: ";
    cin >> n_ip;
    infile << "количество человек, поступивших на ИП: ";
    infile << n_ip << endl;
    outfile << "количество человек, поступивших на ИП: ";
    outfile << n_ip << endl;
    while (s1 < n_ip) {
        cout << "Введите кодовый номер абитуриента: ";
        cin >> a;
        infile << "Кодовый номер абитуриента: ";
        infile << a << endl;
        outfile << "Кодовый номер абитуриента: ";
        outfile << a << endl;
        Head_ip = Make_list(Head_ip, a); // Добавляем абитуриента в список на ИП
        s1 += 1;
    }
    cout << "Введите количество человек, поступивших на ПОВТ: ";
    cin >> n_povt;
    infile << "количество человек, поступивших на ПОВТ: ";
    infile << n_povt << endl;
    outfile << "количество человек, поступивших на ПОВТ: ";
    outfile << n_povt << endl;
    while (s2 < n_povt) {
        cout << "Введите кодовый номер абитуриента: ";
        cin >> b;
        infile << "Кодовый номер абитуриента: ";
        infile << b << endl;
        outfile << "Кодовый номер абитуриента: ";
        outfile << b << endl;
        Head_povt = Make_list(Head_povt, b); // Добавляем абитуриента в список на ПОВТ
        s2 += 1;
    }

    cout << "Абитуриенты, поступившие на ИП: ";
    Print_Single_List(Head_ip);
    cout << "Абитуриенты, поступившие на ПОВТ: ";
    Print_Single_List(Head_povt);
    cout << "Кодовые номера абитуриентов, поступивших на два направления:";
    Head_two = proverka(Head_ip, n_ip, n_povt, Head_povt, Head_two);
    Print_Single_List(Head_two);
    Head_ip = Delet(Head_two,Head_ip);
    Head_povt = Delet(Head_two,Head_povt);
    cout << "Кодовые номера абитуриентов, поступивших только на ИП: ";
    Print_Single_List(Head_ip);
    cout << "Кодовые номера абитуриентов, поступивших только на ПОВТ: ";
    Print_Single_List(Head_povt);
    // Освобождаем выделенную память для списков

    SL * temp = NULL;
    outfile << "\n\nКодовые номера абитуриентов, поступивших на два направления:";
    while (Head_two != NULL) {
        temp = Head_two;
        outfile << temp->number << " ";
        Head_two = Head_two->Next;
        delete temp;
    }
    outfile << "\n\nКодовые номера абитуриенты, поступивших только на ИП: ";
    while (Head_ip != NULL) {
        temp = Head_ip;
        outfile << temp->number << " ";
        Head_ip = Head_ip->Next;
        delete temp;
    }
    outfile << "\n\nКодовые номера абитуриентов, поступивших только на ПОВТ: ";
    while (Head_povt != NULL) {
        temp = Head_povt;
        outfile << temp->number<< " ";
        Head_povt = Head_povt->Next;
        delete temp;
    }
    

}