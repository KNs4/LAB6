#include <iostream>
#include <limits>
using namespace std;

// Задание 1: Однонаправленный список
class SinglyLinkedList {
private:
    // Структура для представления узла однонаправленного списка
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };
    Node* head; // Указатель на голову списка

public:
    SinglyLinkedList() : head(nullptr) {}

    // Метод для добавления элемента в конец списка
    void add(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Метод для удаления всех элементов с заданным значением
    void remove(int value) {
        while (head && head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        Node* current = head;
        while (current && current->next) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }

    // Метод для вывода списка на экран
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Задание 2: Двунаправленный список
class DoublyLinkedList {
private:
    // Структура для представления узла двунаправленного списка
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head; // Указатель на голову списка
    Node* tail; // Указатель на хвост списка

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Метод для добавления элемента в конец списка
    void add(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
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
                if (!first) first = current;
                last = current;
            }
            current = current->next;
        }

        // Перестановка элементов, если найдены оба вхождения
        if (first && last && first != last) {
            Node* left = first->next;
            Node* right = last->prev;
            while (left && right && left != right && left->prev != right) {
                swap(left->data, right->data);
                left = left->next;
                right = right->prev;
            }
        } else {
            cout << "Недостаточно вхождений элемента " << E << " для перестановки.\n";
        }
    }

    // Метод для вывода списка на экран
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
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
        if (cin.fail()) {
            cout << "Ошибка: введите корректное целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
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
        sList.add(getValidatedInt(""));
    }
    cout << "Список до удаления: ";
    sList.print();

    // Удаление элементов по значению
    int valueToRemove = getValidatedInt("Введите значение для удаления из списка: ");
    sList.remove(valueToRemove);
    cout << "Список после удаления всех " << valueToRemove << ": ";
    sList.print();

    cout << "\nЗадание 2: Двунаправленный список" << endl;
    DoublyLinkedList dList;

    // Ввод данных для двунаправленного списка
    int n2 = getValidatedInt("Введите количество элементов для двунаправленного списка: ");
    cout << "Введите элементы списка: ";
    for (int i = 0; i < n2; ++i) {
        dList.add(getValidatedInt(""));
    }
    cout << "Список до перестановки: ";
    dList.print();

    // Перестановка элементов между первым и последним вхождением E
    int E = getValidatedInt("Введите значение E для перестановки элементов между первым и последним его вхождением: ");
    dList.reverseBetweenOccurrences(E);
    cout << "Список после перестановки: ";
    dList.print();

    return 0;
}
