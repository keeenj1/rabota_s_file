#include <iostream>
#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Book {
    std::string Author;
    std::string Title;
    int Year;
};
void saveToFile(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "error";
    }
    else {
        for (const std::string& word : data) {
            file << word << " ";
        }
    }
    file.close();
}
void saveToFile(const std::string& filename, std::vector<Book>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "error";
    }
    else {
        for (int i = 0; i < data.size();++i) {
            file << data[i].Author << " " << data[i].Title << " " << data[i].Year << "\n";
        }    
    }
    file.close();
}
void loadFromFile(const std::string& filename, std::vector<std::string>& outData) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "error";
    }
    else {
        std::string word;
        while (file >> word) {
            outData.push_back(word);
        }
    }
    file.close();
}
void loadFromFile(const std::string& filename, std::vector<Book> outData) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "error";
    }
    else {
        std::string str;
        std::string str1;
        while (getline(file, str)) {
            std::istringstream ss(str);
            while (getline(ss, str1, ',')) {
                std::cout << str1 << std::endl;
            }
        }
    }
    file.close();
}
enum Score {
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};
struct Student {
    std::string Name;
    int Year;
    std::map<std::string, Score> RecordBook;
};
using Groups = map<string,vector<Student>>;
void saveToFile(const string& filename, const Groups& groups) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& group : groups) {
            file << group.first << endl;
            for (const auto& student : group.second) {
                file << student.Name << " " << student.Year << endl;
                for (const auto& record : student.RecordBook) {
                    file << record.first << " " << record.second << endl;
                }
            }
        }
        file.close();
    }
    else {
        std::cout << "ERROR 404" << endl;
    }
}
void loadFromFile(const string& filename, Groups& outGroups) {
    ifstream file(filename);
    if (file.is_open()) {
        string groupName;
        while (getline(file, groupName)) {
            vector<Student> students;
            string studentName;
            int studentYear;
            while (file >> studentName >> studentYear) {
                Student student;
                student.Name = studentName;
                student.Year = studentYear;

                string subject;
                int score;
                while (file >> subject >> score) {
                    student.RecordBook[subject] = static_cast<Score>(score);
                }

                students.push_back(student);
            }

            outGroups[groupName] = students;
        }
        file.close();
    }
    else {
        cout << "ERROR 404" << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    // Задание 1
    std::vector<std::string> data;
    std::vector<std::string> outdata;
    std::vector<std::string> bookdata;
    std::string filename = "myFile";
    data.push_back("Hello ");
    data.push_back("future ");
    data.push_back("world!");
    saveToFile(filename,data);
    loadFromFile(filename, outdata);
    // Задание 2
    Book book1; Book book2; Book book3;
    book1.Author = "Маяковский"; book2.Author = "Пушкин"; book3.Author = "Блок";
    book1.Title = "Повесть об Орхане на Исо"; book2.Title = "Исповедь лоутаба"; book3.Title = "Диана люблю тебя";
    book1.Year = 1897; book2.Year = 2021; book3.Year = 2000;
    std::vector<Book> List_of_books;
    std::vector<Book> List_of_books1;
    List_of_books.push_back(book1);
    List_of_books.push_back(book2);
    List_of_books.push_back(book3);
    saveToFile(filename,List_of_books);
    loadFromFile(filename, List_of_books);  
    // Задание 3
    Groups group1;
    Groups group2;
    Student st1;
    st1.Name = "Max"; st1.Year = 1; st1.RecordBook["IZO"] = Satisfactorily; st1.RecordBook["MATHS"] = Excellent;
    Student st2;
    st2.Name = "Jenya"; st2.Year = 2; st2.RecordBook["MATHS"] = Unsatisfactorily;
    vector <Student> studens1;
    vector <Student> studens2;
    studens1.push_back(st1);
    studens1.push_back(st2);
    group1["IU8-14"] = studens1;
    string filename1 = "students.txt";
    saveToFile(filename1, group1);
    loadFromFile(filename1, group2);
    for (const auto& group : group2) {
        std::cout << "Group: " << group.first << std::endl;
        for (const auto& student : group.second) {
            std::cout << "Name: " << student.Name << student.Year << std::endl;
            for (const auto& record : student.RecordBook) {
                std::cout << "Subject: " << record.first << ", Score: " << record.second << std::endl;
            }
        }
    }


    return 0;
}