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
    if (argc <= 1) {
        std::cout << "Usage: quiz [initdb] [import <filepath>] [keyword]" << std::endl;
        std::cout << "    initdb: Initialize database" << std::endl;
        std::cout << "    import: Import to database with filepath" << std::endl;
        std::cout << "    keyword: Search in database" << std::endl;
        exit(0);
    }
    if (argc > 1) {
        if (strcmp(argv[1], "initdb") == 0) {
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
            exit(0);
        } else if (strcmp(argv[1],"import") == 0) {
            if (argc < 3) {
                std::cout << "Usage: quiz import <filepath>" << std::endl;
                exit(0);
            }
            std::string filepath = std::string(argv[2]);
            if (filepath.size() == 0) {
                std::cout << "Usage: quiz import <filepath>" << std::endl;
                exit(0);
            }
            std::cout << filepath << std::endl;
            exit(0);
        }
        std::string keyword = std::string(argv[1]);
        if (keyword.size() == 0) {
            std::cout << "Nothing to search" << std::endl;
            exit(0);
        }
        std::string tag = "";
        if (argc > 2) {
            tag = std::string(argv[2]);
        }
        if (tag.size() > 0) {
            std::cout << "[" << tag << "] " << keyword << std::endl;
        } else {
            std::cout << keyword << std::endl;
        }
        exit(0);
    }
    return 0;
}
