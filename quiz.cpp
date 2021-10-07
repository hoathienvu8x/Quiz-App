#include <iostream>
#include <cstring>
#include <exception>
#include <sqlite.h>

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
    return 0;
}
