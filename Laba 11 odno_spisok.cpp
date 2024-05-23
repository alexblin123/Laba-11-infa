#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
    char data[100];
    Node* next;
};

Node* insertNode(Node* head, const char* key) {
    Node* newNode = new Node;
    strcpy_s(newNode->data, key);
    newNode->next = head;
    return newNode;
}

Node* deleteNode(Node* head, const char* key) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (strcmp(current->data, key) == 0) {
            if (prev != nullptr) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }

            delete current;
            return head;
        }

        prev = current;
        current = current->next;
    }

    cout << "Узел с ключом '" << key << "' не найден." << endl;
    return head;
}

Node* addKNodesBefore(Node* head, int k, int position, const char* key) {
    Node* current = head;
    Node* prev = nullptr;

    for (int i = 1; i < position && current != nullptr; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Позиция не найдена." << endl;
        return head;
    }

    Node* newNode = nullptr;

    for (int i = 0; i < k; ++i) {
        newNode = insertNode(newNode, key);

        if (prev != nullptr) {
            prev->next = newNode;
        }
        else {
            head = newNode;
        }

        newNode->next = current;
        prev = newNode;
    }

    return head;
}

void displayList(Node* head) {
    Node* current = head;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;
}

void writeListToFile(Node* head, const char* fileName) {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    Node* current = head;

    while (current != nullptr) {
        outputFile << current->data << " ";
        current = current->next;
    }

    cout << "Список успешно записан в файл: " << fileName << endl;

    outputFile.close();
}

int main() {
    Node* head = nullptr;

    setlocale(LC_ALL, "RU");
    system("chcp 1251>nul");

    int nodeCount, k, position;
    char keyToDelete[100], newKey[100];

    cout << "Введите количество узлов: ";
    cin >> nodeCount;

    for (int i = 0; i < nodeCount; ++i) {
        char key[100];
        cout << "Введите ключ для узла " << i + 1 << ": ";
        cin >> key;
        head = insertNode(head, key);
    }

    cout << endl << "Список до добавления: ";
    displayList(head);

    cout << endl << "Введите ключ узла для удаления: ";
    cin >> keyToDelete;
    head = deleteNode(head, keyToDelete);

    cout << endl << "Список после удаления ключа " << keyToDelete << ": ";
    displayList(head);

    cout << endl << "Введите количество узлов для добавления (K): ";
    cin >> k;

    cout << endl << "Введите позицию, перед которой добавить узлы: ";
    cin >> position;

    cout << endl << "Введите ключ для новых узлов: ";
    cin >> newKey;

    head = addKNodesBefore(head, k, position, newKey);

    cout << endl << "Список после изменений: ";
    displayList(head);

    const char* fileName = "output.txt";
    writeListToFile(head, fileName);

    return 0;
}
