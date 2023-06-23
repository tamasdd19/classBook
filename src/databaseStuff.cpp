#include "databaseStuff.h"

int callbackFunction(void* data, int argc, char** argv, char** columnNames) 
{
    MyData* mydata = static_cast<MyData*>(data);
    for (int i = 0; i < argc; i++) 
    {
        if(!strcmp(columnNames[i], "name"))
        {
            std::string checkName = argv[i];

            if(checkName == mydata->name)
            {

                mydata->gasit = true;
                std::string checkPass = argv[i+1];
                std::cout << "parola verificata:\n" << checkPass.size() << "\nParola trimisa:\n" << mydata->password.size() << "\n";

                if(checkPass == mydata->password) // User has logged in
                {
                    if(std::stoi(argv[i+2]))
                    {
                        mydata->user = new Student(mydata->name, std::stoi(argv[i+3]));
                        mydata->student = true;
                    }
                    else
                    {
                        mydata->user = new Professor(mydata->name);
                    }
                    mydata->user->setId(std::stoi(argv[i-1]));
                    std::cout << mydata->user->getName() << " has logged in!\n";
                    break;
                }
                else
                {
                    std::cout << "Incorrect password!\n";
                    std::cout << checkPass << "  " << mydata->password;
                    break;
                }
            }
        }
    }
    return 0;
}

int getMajor(void* data, int argc, char** argv, char** columnNames) 
{
    Major* major = static_cast<Major*>(data);
    major->setId(std::stoi(argv[0]));
    major->setName(argv[1]);
    std::cout << major->getName();
    major->setYear(std::stoi(argv[2]));
    major->setFacultyId(std::stoi(argv[3]));
    return 0;
}

int setMajorCourses(void* data, int argc, char** argv, char** columnNames) 
{
    MyData2* data2 = static_cast<MyData2*>(data);
    Course* course;
    course = new Course(std::stoi(argv[0]), argv[1], data2->id);
    data2->courses.push_back(course);
    return 0;
}