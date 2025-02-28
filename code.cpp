#include <iostream>
#include <limits>
using namespace std;

// Задание 1: Однонаправленный список
class SinglyLinkedList {
private:
    // Структура для представления узла однонаправленного списка
    struct Node {
        int data; // Данные, хранимые в узле
        Node* next; // Указатель на следующий узел
        Node(int d) : data(d), next(nullptr) {} // Конструктор для создания узла с данными
    };
    Node* head; // Указатель на голову списка

public:
    // Конструктор, который инициализирует голову списка как null
    SinglyLinkedList() : head(nullptr) {}

    // Метод для добавления элемента в конец списка
    void add(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        if (!head) { // Если список пуст, новый узел становится головой
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) { // Ищем последний узел
                temp = temp->next;
            }
            temp->next = newNode; // Присоединяем новый узел в конец списка
        }
    }

    // Метод для удаления всех элементов с заданным значением
    void remove(int value) {
        // Удаляем все вхождения элемента в начале списка
        while (head && head->data == value) {
            Node* temp = head;
            head = head->next; // Перенаправляем голову на следующий узел
            delete temp; // Освобождаем память
        }

        // Удаляем все вхождения элемента в остальной части списка
        Node* current = head;
        while (current && current->next) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next; // Пропускаем удаляемый узел
                delete temp; // Освобождаем память
            } else {
                current = current->next;
            }
        }
    }

    // Метод для вывода списка на экран
    void print() {
        Node* temp = head;
        while (temp) { // Проходим по всему списку
            cout << temp->data << " "; // Выводим данные текущего узла
            temp = temp->next; // Переходим к следующему узлу
        }
        cout << endl;
    }
};

// Задание 2: Двунаправленный список
class DoublyLinkedList {
private:
    // Структура для представления узла двунаправленного списка
    struct Node {
        int data; // Данные, хранимые в узле
        Node* prev; // Указатель на предыдущий узел
        Node* next; // Указатель на следующий узел
        Node(int d) : data(d), prev(nullptr), next(nullptr) {} // Конструктор для создания узла
    };
    Node* head; // Указатель на голову списка
    Node* tail; // Указатель на хвост списка

public:
    // Конструктор, который инициализирует голову и хвост как null
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Метод для добавления элемента в конец списка
    void add(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        if (!head) { // Если список пуст, новый узел становится и головой, и хвостом
            head = tail = newNode;
        } else {
            tail->next = newNode; // Присоединяем новый узел к концу списка
            newNode->prev = tail; // Устанавливаем указатель на предыдущий узел
            tail = newNode; // Обновляем указатель хвоста
        }
    }

    // Метод для удаления всех элементов с заданным значением
    void remove(int value) {
        Node* current = head; // Начинаем с головы списка

        // Удаление всех вхождений в начале списка
        while (current && current->data == value) {
            Node* temp = current;
            head = current->next; // Перенаправляем голову на следующий узел
            if (head) head->prev = nullptr; // Если список не пуст, обновляем указатель на предыдущий узел
            delete temp; // Освобождаем память
            current = head; // Переходим к следующему узлу
        }

        // Удаление всех вхождений после начала списка
        while (current) {
            if (current->data == value) {
                Node* temp = current;
                if (current->next) {
                    current->next->prev = current->prev; // Устанавливаем указатель на предыдущий узел для следующего
                } else { // Если удаляем последний элемент
                    tail = current->prev;
                }
                if (current->prev) {
                    current->prev->next = current->next; // Устанавливаем указатель на следующий узел для предыдущего
                }
                delete temp; // Освобождаем память
                current = current->next; // Переходим к следующему узлу
            } else {
                current = current->next; // Если элемент не совпал, просто переходим к следующему
            }
        }
    }

    // Метод для перестановки элементов между первым и последним вхождением E
    void reverseBetweenOccurrences(int E) {
        Node* first = nullptr;
        Node* last = nullptr;
        Node* current = head;

        // Поиск первого и последнего вхождения элемента E
        while (current) {
            if (current->data == E) {
                if (!first) first = current; // Запоминаем первое вхождение
                last = current; // Запоминаем последнее вхождение
            }
            current = current->next; // Переходим к следующему узлу
        }

        // Перестановка элементов, если найдены оба вхождения
        if (first && last && first != last) {
            Node* left = first->next;
            Node* right = last->prev;
            while (left && right && left != right && left->prev != right) {
                swap(left->data, right->data); // Меняем данные местами
                left = left->next; // Переходим к следующему элементу с левой стороны
                right = right->prev; // Переходим к предыдущему элементу с правой стороны
            }
        } else {
            cout << "Недостаточно вхождений элемента " << E << " для перестановки.\n";
        }
    }

    // Метод для вывода списка на экран
    void print() {
        Node* temp = head;
        while (temp) { // Проходим по всему списку
            cout << temp->data << " "; // Выводим данные текущего узла
            temp = temp->next; // Переходим к следующему узлу
        }
        cout << endl;
    }
};

// Функция для проверки вводимых данных
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) { // Если введено не целое число
            cout << "Ошибка: введите корректное целое число.\n";
            cin.clear(); // Очищаем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем оставшийся ввод
        } else {
            return value; // Если ввод корректен, возвращаем значение
        }
    }
}

// Главная функция
int main() {
    cout << "Задание 1: Однонаправленный список" << endl;
    SinglyLinkedList sList;

    // Ввод данных для однонаправленного списка
    int n1 = getValidatedInt("Введите количество элементов для однонаправленного списка: ");
    cout << "Введите элементы списка: ";
    for (int i = 0; i < n1; ++i) {
        sList.add(getValidatedInt("")); // Добавляем элементы в список
    }
    cout << "Список до удаления: ";
    sList.print(); // Выводим список

    // Удаление элементов по значению
    int valueToRemove = getValidatedInt("Введите значение для удаления из списка: ");
    sList.remove(valueToRemove); // Удаляем элементы
    cout << "Список после удаления всех " << valueToRemove << ": ";
    sList.print(); // Выводим обновленный список

    cout << "\nЗадание 2: Двунаправленный список" << endl;
    DoublyLinkedList dList;

    // Ввод данных для двунаправленного списка
    int n2 = getValidatedInt("Введите количество элементов для двунаправленного списка: ");
    cout << "Введите элементы списка: ";
    for (int i = 0; i < n2; ++i) {
        dList.add(getValidatedInt("")); // Добавляем элементы в двунаправленный список
    }
    cout << "Список до перестановки: ";
    dList.print(); // Выводим список

    // Удаление элементов по значению из двунаправленного списка
    int valueToRemoveDoubly = getValidatedInt("Введите значение для удаления из двунаправленного списка: ");
    dList.remove(valueToRemoveDoubly); // Удаляем элементы
    cout << "Список после удаления всех " << valueToRemoveDoubly << ": ";
    dList.print(); // Выводим обновленный список

    // Перестановка элементов между первым и последним вхождением E
    int E = getValidatedInt("Введите значение E для перестановки элементов между первым и последним его вхождением: ");
    dList.reverseBetweenOccurrences(E); // Переставляем элементы
    cout << "Список после перестановки: ";
    dList.print(); // Выводим обновленный список

    return 0;
}
