#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct Node {

    T data;
    Node<T>* next_ptr;
};

template <typename T>
struct Stack {

    Node<T>* head;
    int size;
};

template <typename T>
void SetNode(Node<T>*& node, T data, Node<T>* next_ptr = nullptr) {

    node = new Node<T>();
    node->next_ptr = next_ptr;
    node->data = data;
}

template <typename T>
void SetStack(Stack<T>& tmp) {

    tmp.head = nullptr;
    tmp.size = 0;
}

template <typename T>
void Push(Stack <T>& tmp, const T& data) {

    Node<T>* new_node;
    SetNode(new_node, data, tmp.head);
    tmp.head = new_node;
    tmp.size++;
}

template <typename T>
void pop(Stack <T>& stack, const T& data) {

    if (stack.head == nullptr)
        return;

    Node<T>* temp = stack.head;
    stack.head = temp->next_ptr;
    delete temp;
    stack.size--;
}

template <typename T>
void print(Stack<T>& stack) {
    
    Node<T>* current_node = stack.head;
    while (current_node != nullptr) {
        cout << current_node->data << " ";
        current_node = current_node->next_ptr;
    }
}

template <typename T>
void clear(Stack<T>& stack) {

    Node<T>* current_node = stack.head;
    while (current_node != nullptr) {
        Node<T>* temp = current_node;
        current_node = current_node->next_ptr;
        delete temp;
    }
    stack.head = nullptr;
    stack.size = 0;
}

template <typename T>
void moveAllToHelpStack(Stack<T>& stack, Stack<T>& helpStack) { // функция для перемещения элементов в доп. стэк
    
    Node<T>* current_node = stack.head;
    while (current_node != nullptr) {
        Push(helpStack, current_node->data); 
        current_node = current_node->next_ptr; // сдвигаемся на следующий узел
    }
    clear(stack);
    stack.size = 0; // уменьшаем размер основного стэка
}

template <typename T>
void moveSeveral(Stack<T>& stack, Stack<T>& helpStack, string data) {

    Node<T>* current_node = stack.head;
    Node<T>* prev_node = nullptr;
    while (current_node != nullptr && current_node->data != data) {
        prev_node = current_node;
        current_node = current_node->next_ptr;
    }

    if (current_node != nullptr) {
        cout << "\nЭлемент " << current_node->data << " удален." << endl;

        if (prev_node == nullptr) {
            stack.head = current_node->next_ptr;
        }
        else {
            prev_node->next_ptr = current_node->next_ptr;
        }

        delete current_node;
        stack.size--;

        cout << "\nСтэк после удаления: ";
        print(stack);
    }
    else {
        cout << "\nЭлемент не найден." << endl;
    }
}

int main() {
    
    system("chcp 1251 > Null");

    Stack<string> main_stack;
    Stack<string> helpStack;
    SetStack(main_stack);
    SetStack(helpStack);
    int numberStack, k;
    string data;
    // Количество начальных элементов

    cout << "Введите кол-во элементов: "; cin >> numberStack;

    for (int i = 0; i < numberStack; i++) {
        cout << "Введите элемент " << i + 1 << ": "; cin >> data;
        Push(main_stack, data);
    }

    cout << "\nСтэк: ";
    print(main_stack);

    cout << endl;

    moveAllToHelpStack(main_stack, helpStack);

    print(main_stack);
    cout << endl;

    cout << "\nВведите, сколько элементов добавляем: "; cin >> k;

    for (int i = 0; i < k; i++) {
        cout << "Элемент " << i + 1 << " в конец: ";cin >> data;
        Push(main_stack, data);
    }

    moveAllToHelpStack(helpStack, main_stack);

    for (int i = 0; i < k; i++) {
        cout << "Элемент " << i + 1 << " в начало: "; cin >> data;
        Push(main_stack, data);
    }

    cout << "\nСтэк: ";
    print(main_stack);

    cout << "\n\nЭлемент для удаления: "; cin >> data;

    moveSeveral(main_stack, helpStack, data);

    ofstream outFile("stack.txt");
    if (outFile.is_open()) {
        Node<string>* current_node = main_stack.head;
        while (current_node != nullptr) {
            outFile << current_node->data << endl;
            current_node = current_node->next_ptr;
        }
        outFile.close();
        cout << "\n\nСтэк успешно записал в файл." << endl;
    }
    else {
        cout << "\nНе получается открыть файл." << endl;
    }

    clear(main_stack);
    clear(helpStack);

    return 0;
}
