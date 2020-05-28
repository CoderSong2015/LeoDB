#include <iostream>

#include "metacommand.h"
#include "sqlhandler.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using simpledb::MetaCommand;
void Prompt(){
    cout << "db> ";
}

void Gomain(){
    while(true){
        string command;
        Prompt();
        getline(cin, command);
        //cin >> command;
        int ret = simpledb::JudgeMetaCommand(command);
        if (MetaCommand::META_SUCCESS == ret){
            continue;
        }else if (MetaCommand::META_QUIT == ret){
            cout<< "quit db";
            exit(1);
        }else if (MetaCommand::META_NOT_META_COMMAND == ret){
            simpledb::handlesql(command);
        }
    }

}
int main() {

    cout << "Simple Database" << std::endl;
    cout << "Made By Leo" << std::endl;
    cout << "Version:0.0.0" << std::endl;

    Gomain();
    return 0;
}