#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct Node {

    T data;
    Node<T>* next;
};

template <typename T>
struct Queue {

    int size;
    Node<T>* head;
    Node<T>* tail;
};

template <typename T>
void init_queue(Queue<T>& Q, const T& data) {

    Node<T>* new_node = new Node<T>();
    new_node->data = data;
    Q.head = new_node;
    Q.tail = new_node;
    Q.size = 1;
}


template <typename T>
void pushBack(Queue<T>& Q, const T& data) {

    Node<T>* new_node = new Node<T>();
    Q.size++;
    new_node->data = data;
    new_node->next = nullptr;
    Q.tail->next = new_node;
    Q.tail = new_node;
}

template <typename T>
void new_queue(Queue<T>& Q, int n) {

    T data;
    cout << "Введите элемент 1: "; cin >> data;
    init_queue(Q, data);
    for (int i = 2; i <= n; i++)
    {
        cout << "Введите элемент " << i << ": "; cin >> data;
        pushBack(Q, data);
    }
}


template <typename T>
void Pop(Queue<T>& Q) {
    
    Node<T>* temp = Q.head;
    Q.head = temp->next;
    Q.size--;
    delete temp;
}

template <typename T>
void deleteElement(Queue<T>& Q, const T& key) {
    
    Node<T>* current_node = Q.head;
    Node<T>* prev_node = nullptr;

    while (current_node != nullptr) {
        if (current_node->data == key) {
            if (prev_node == nullptr) {
                Q.head = current_node->next;
            }
            else {
                prev_node->next = current_node->next;
            }

            Node<T>* temp = current_node;
            current_node = current_node->next;
            delete temp;
            Q.size--;

            break; 
        }
        else {
            prev_node = current_node;
            current_node = current_node->next;
        }
    }
}

template <typename T>
void pushFront(Queue <T>& Q, const T& key) {

    Node<T>* new_node = new Node<T>();
    new_node->data = key;
    new_node->next = Q.head;
    Q.head = new_node;
    Q.size++;
    print(Q);
}

template <typename T>
void print(Queue <T>& Q)
{
    Node<T>* current_node = Q.head;
    cout << "\nНачало -> ";
    while (current_node != nullptr) {
        cout << current_node->data << " -> ";
        current_node = current_node->next;
    }
    cout << "Конец\n";
}

template <typename T>
void clear(Queue<T>& Q) {
    Node<T>* current_node = Q.head;
    while (current_node != nullptr) {
        Node<T>* temp = current_node;
        current_node = current_node->next;
        delete temp;
    }
    Q.head = nullptr;
    Q.size = 0;
}

template <typename T>
void writeQueueToFile(Queue<T>& Q, const string& filename) {

    ofstream outFile(filename);
    if (outFile.is_open()) {
        Node<T>* current_node = Q.head;
        while (current_node != nullptr) {
            outFile << current_node->data << endl;
            current_node = current_node->next;
        }
        outFile.close();
        cout << "\nОчередь была записана в файл " << filename << endl;
    }
    else {
        cout << "\nНевозможно открыть файл: " << filename << endl;
    }
}

int main() {

    system("chcp 1251 > Null");

    Queue<string> MyQ;
    int size, k;
    string data;

    cout << "Введите кол-во элементов: "; cin >> size;

    new_queue(MyQ, size);

    print(MyQ);

    cout << "\nВведите кол-вл элементов для добавления: "; cin >> k;

    cout << endl;
    for (int i = 0; i < k; i++) {

        cout << "Введите элемент " << i + 1 << " в начало: "; cin >> data;

        pushFront(MyQ, data);
    }
    for (int i = 0; i < k; i++) {

        cout << "Введите элемент " << i + 1 << " в конец: "; cin >> data;

        pushBack(MyQ, data);
        print(MyQ);
    }

    cout << "\nВведите ключ, по которому удалить: "; cin >> data;
    deleteElement(MyQ, data);

    cout << "\nОчередь после удаления: ";
    print(MyQ);

    writeQueueToFile(MyQ, "queue.txt");

    clear(MyQ);

    return 0;
}
