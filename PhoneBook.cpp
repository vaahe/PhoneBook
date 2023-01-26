#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <windows.h>

struct Record {
    int id;
    std::string name;
    std::string surname = "";
    std::string num_code; // Phone number code
    std::string separator;
    Record(int id, std::string name, std::string surname, std::string separator, std::string num_code) : id(id), name(name), surname(surname), separator(separator), num_code(num_code) {}
};

std::wstring xePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    return buffer;

}

std::vector<Record> insertionSortAsc(std::vector<Record>& vec, int size, std::string criteria) {
    int j;
    std::string key, key1, key2;

    if (criteria == "name") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].name;
            key1 = vec[i].surname;
            key2 = vec[i].num_code;
            while (j >= 0 && vec[j].name > key) {
                vec[j + 1].name = vec[j].name;
                vec[j + 1].surname = vec[j].surname;
                vec[j + 1].num_code = vec[j].num_code;
                --j;
            }
            vec[j + 1].name = key;
            vec[j + 1].surname = key1;
            vec[j + 1].num_code = key2;
        }
    }
    else if (criteria == "surname") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].surname;
            key1 = vec[i].name;
            key2 = vec[i].num_code;
            while (j >= 0 && vec[j].surname > key) {
                vec[j + 1].surname = vec[j].surname;
                vec[j + 1].name = vec[j].name;
                vec[j + 1].num_code = vec[j].num_code;
                --j;
            }
            vec[j + 1].surname = key;
            vec[j + 1].name = key1;
            vec[j + 1].num_code = key2;
        }
    }
    else if (criteria == "phonenumbercode") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].num_code;
            key1 = vec[i].name;
            key2 = vec[i].surname;
            while (j >= 0 && vec[j].num_code > key) {
                vec[j + 1].num_code = vec[j].num_code;
                vec[j + 1].name = vec[j].name;
                vec[j + 1].surname = vec[j].surname;
                --j;
            }
            vec[j + 1].num_code = key;
            vec[j + 1].name = key1;
            vec[j + 1].surname = key2;
        }
    }

    return vec;
}

std::vector<Record> insertionSortDesc(std::vector<Record>& vec, int size, std::string criteria) {
    int j;
    std::string key, key1, key2;

    if (criteria == "name") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].name;
            key1 = vec[i].surname;
            key2 = vec[i].num_code;
            while (j >= 0 && vec[j].name < key) {
                vec[j + 1].name = vec[j].name;
                vec[j + 1].surname = vec[j].surname;
                vec[j + 1].num_code = vec[j].num_code;
                --j;
            }
            vec[j + 1].name = key;
            vec[j + 1].surname = key1;
            vec[j + 1].num_code = key2;
        }
    }
    else if (criteria == "surname") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].surname;
            key1 = vec[i].name;
            key2 = vec[i].num_code;
            while (j >= 0 && vec[j].surname < key) {
                vec[j + 1].surname = vec[j].surname;
                vec[j + 1].name = vec[j].name;
                vec[j + 1].num_code = vec[j].num_code;
                --j;
            }
            vec[j + 1].surname = key;
            vec[j + 1].name = key1;
            vec[j + 1].num_code = key2;
        }
    }
    else if (criteria == "phonenumbercode") {
        for (int i = 1; i < size; ++i) {
            j = i - 1;
            key = vec[i].num_code;
            key1 = vec[i].name;
            key2 = vec[i].surname;
            while (j >= 0 && vec[j].num_code < key) {
                vec[j + 1].num_code = vec[j].num_code;
                vec[j + 1].name = vec[j].name;
                vec[j + 1].surname = vec[j].surname;
                --j;
            }
            vec[j + 1].num_code = key;
            vec[j + 1].name = key1;
            vec[j + 1].surname = key2;
        }
    }

    return vec;
}


void validate(std::vector<Record>& vec) {
    std::cout << "Validations:" << std::endl;
    for (Record& record : vec) {
        if (record.num_code.length() != 9 && (record.separator != "-" && record.separator != ":")) {
            std::cout << "Line " << record.id << " phone number should be with 9 digits, the separator should be `:` or `-`";
            std::cout << std::endl;
        }
        else if (record.num_code.length() != 9) {
            std::cout << "Line " << record.id << " phone number should be 9 digits." << std::endl;
        }
        else if (record.separator != "-" && record.separator != ":") {
            std::cout << "Line " << record.id << " separator should be `:` or `-`." << std::endl;
        }
    }
}

void driver() {
    std::ifstream input_file;
    std::string path;
    std::cout << "Input file path(instead of '\' insert '\\')" << std::endl;
    std::cin >> path;

    input_file.open(path);

    std::string order, criteria;
    std::cout << "please choose an ordering to sort : ascending or descending\n";
    std::cin >> order;
    std::transform(order.begin(), order.end(), order.begin(), ::tolower);

    std::cout << "please choose criteria : Name, Surname or PhoneNumberCode\n";
    std::cin >> criteria;
    std::transform(criteria.begin(), criteria.end(), criteria.begin(), ::tolower);

    std::vector<Record> phone_book;


    if (input_file.is_open()) { // check whether the file is open
        int id = 0;
        while (!input_file.eof()) {
            id++;
            std::string name, surname, separator, num_code;
            input_file >> name >> surname >> separator >> num_code;
            phone_book.push_back(Record(id, name, surname, separator, num_code));
        }
    }

    if (order == "ascending") {
        insertionSortAsc(phone_book, phone_book.size(), criteria);
    }
    else if (order == "descending") {
        insertionSortDesc(phone_book, phone_book.size(), criteria);
    }
    else {
        std::cerr << "Unknown command";
    }

    for (Record& record : phone_book) {
        std::cout << record.id << " " << record.name << " " 
            << record.surname << " " << record.separator << " " << record.num_code << '\n';
    }

    std::cout << std::endl;

    validate(phone_book);
}


int main() {
    driver();

    return 0;
}