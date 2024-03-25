if (student.debt.type() == typeid(std::nullptr_t))
    {
        os
            << std::left << std::setw(20)
            << " null"
            << " |";
    }
    else if (student.debt.type() == typeid(std::string))
    {
        os
            << " " << std::left << std::setw(20)
            << std::any_cast<std::string>(student.debt) << "|";
    }
    else
    {
        int dsize = std::any_cast<std::vector<std::string>>(student.debt).size();
        os
            << " " << std::left << std::setw(20)
            << std::to_string(dsize) + " items"
            << "|";
    }
    os
        << std::endl
        << std::setfill('-') << std::left << std::setw(22) << "|"
        << std::left << std::setw(22) << "|"
        << std::left << std::setw(22) << "|"
        << std::left << std::setw(22) << "|"
        << "|" << std::endl;
}

int main(int argc, char *argv[])
{
    const std::string jsonPath = argv[1];
    std::ifstream file{"./" + jsonPath};
    try
    {
         if (!file) {
            throw  "Error: unable to open file ";
        }
    }
      catch(const char* e)
    {
        std::cout << e << '\n';
        exit(0);
    }
    
    json data;
        file >> data;
    try {
       
    
        if (!isItemsArray(data)) {
            throw "Error: \"items\" expected to be array" ;
        }
        if (!isMetaValid(data)) {
            throw "Error: number of students doesn’t match \"meta\"";
            
        }
    }
      catch(const char* e)
    {
        std::cout << e << '\n';
       return(0);
    }

    for (auto const &item : data.at("items"))
    {
        student_t student = item.get<student_t>();
        printStudent(student, std::cout);
    }
}
