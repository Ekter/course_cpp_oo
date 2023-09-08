#include <iostream>
#include <vector>
#include <string>


int open_file_and_read(std::string filename, std::vectordouble& v){
    ifstream file(filename);
    if (file.is_open()){
        double value;
        while (file  value){
            v.push_back(value);
        }
        file.close();
        return 0;
    }
    else{
        return 1;
    }
}