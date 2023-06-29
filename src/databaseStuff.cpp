#include "databaseStuff.h"

int callbackFunction(void* data, int argc, char** argv, char** columnNames) 
{
    MyData* mydata = static_cast<MyData*>(data);
    for (int i = 0; i < argc; i++) 
    {
        if(!strcmp(columnNames[i], "username"))
        {
            std::string checkName = argv[i];

            if(checkName == mydata->name)
            {

                mydata->gasit = true;
                std::string checkPass = argv[i+1];

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
                    mydata->user->setDateOfBirth(std::stoi(argv[i+6]), std::stoi(argv[i+7]), std::stoi(argv[i+8]));
                    mydata->user->setId(std::stoi(argv[i-1]));
                    mydata->user->setFirstName(argv[i+4]);
                    mydata->user->setLastName(argv[i+5]);
                    mydata->user->setMale(std::stoi(argv[i+9]));
                    mydata->user->setCountryOrigin(argv[i+10]);
                    std::cout << mydata->user->getUsername() << " has logged in!\n";
                    break;
                }
                else
                {
                    std::cout << "Incorrect password!\n";
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

int getGrades(void* data, int argc, char** argv, char** columnNames) 
{
    float* grade = static_cast<float*>(data);
    *grade = std::stof(argv[2]);
    return 0;
}

int getProfessorCourses(void* data, int argc, char** argv, char** columnNames)
{
    std::vector<Course*>* courses = static_cast<std::vector<Course*>*>(data);
    courses->push_back(new Course(std::stoi(argv[0]), argv[1], std::stoi(argv[2])));
    return 0;
}

int getStudents(void* data, int argc, char** argv, char** columnNames)
{
    std::vector<Student*>* students = static_cast<std::vector<Student*>*>(data);
    Student* newStudent = new Student(argv[1], std::stoi(argv[4]));

    newStudent->setId(std::stoi(argv[0]));
    newStudent->setFirstName(argv[5]);
    newStudent->setLastName(argv[6]);

    students->push_back(newStudent);

    return 0;
}