#include <algorithm>
#include <iostream>
#include <cstring>
#include <exception>
#include <sqlite.h>

std::string lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}

int main(int argc, char **argv) {
    std::cout << "Mini Quiz" << std::endl;
    if (argc > 1 && strcmp(argv[1], "initdb") == 0) {
        try {
            database db("quiz.db");
            command cmd(db, "CREATE TABLE quiz (id INTEGER NOT NULL,content VARCHAR NOT NULL,tags VARCHAR(200) NOT NULL,PRIMARY KEY (id));");
            if(cmd.execute() == SQLITE_OK) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    std::string question;
    while(1) {
        std::cout << "Question: ";
        std::cin >> question;
        question = lower(question);
        if (question == "quit" || question == "edit") {
            break;
        }
        std::cout << "Answer: " << question << std::endl;
    }
    return 0;
}
