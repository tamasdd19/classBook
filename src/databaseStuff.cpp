#include "databaseStuff.h"

int callbackFunction(void* data, int argc, char** argv, char** columnNames) 
{
    LoginData* loginData = static_cast<LoginData*>(data);
    for (int i = 0; i < argc; i++) 
    {
        if(!strcmp(columnNames[i], "username"))
        {
            std::string checkName = argv[i];

            if(checkName == loginData->name)
            {

                loginData->found = true;
                std::string checkPass = argv[i+1];

                if(checkPass == loginData->password) // User has logged in
                {
                    if(std::stoi(argv[i+2]))
                    {
                        loginData->user = new Student(loginData->name, std::stoi(argv[i+3]));
                        loginData->isStudent = true;
                    }
                    else
                    {
                        loginData->user = new Professor(loginData->name);
                    }
                    loginData->user->setDateOfBirth(std::stoi(argv[i+6]), std::stoi(argv[i+7]), std::stoi(argv[i+8]));
                    loginData->user->setId(std::stoi(argv[i-1]));
                    loginData->user->setFirstName(argv[i+4]);
                    loginData->user->setLastName(argv[i+5]);
                    loginData->user->setMale(std::stoi(argv[i+9]));
                    loginData->user->setCountryOrigin(argv[i+10]);
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

int checkIfGradeExists(void* data, int argc, char** argv, char** columnNames)
{
    bool* check = static_cast<bool*>(data);
    *check = true;
    return 0;
}

// Encrypt a password using AES
std::string encryptPassword(const std::string& password, const std::string& key)
{
    std::string encrypted;
    
    AES_KEY aesKey;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aesKey);
    
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, sizeof(iv));
    
    int inputLength = password.length();
    
    // AES requires input to be a multiple of block size (16 bytes for AES-128)
    int paddedLength = ((inputLength + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    unsigned char* input = new unsigned char[paddedLength];
    memset(input, 0x00, paddedLength);
    memcpy(input, password.c_str(), inputLength);
    
    unsigned char* output = new unsigned char[paddedLength];
    memset(output, 0x00, paddedLength);
    
    AES_cbc_encrypt(input, output, paddedLength, &aesKey, iv, AES_ENCRYPT);
    
    encrypted.assign(reinterpret_cast<char*>(output), paddedLength);
    
    delete[] input;
    delete[] output;
    
    return encrypted;
}

// Decrypt an encrypted password using AES
std::string decryptPassword(const std::string& encrypted, const std::string& key)
{
    std::string decrypted;
    
    AES_KEY aesKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aesKey);
    
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, sizeof(iv));
    
    int inputLength = encrypted.length();
    
    unsigned char* input = new unsigned char[inputLength];
    memset(input, 0x00, inputLength);
    memcpy(input, encrypted.c_str(), inputLength);
    
    unsigned char* output = new unsigned char[inputLength];
    memset(output, 0x00, inputLength);
    
    AES_cbc_encrypt(input, output, inputLength, &aesKey, iv, AES_DECRYPT);
    
    decrypted.assign(reinterpret_cast<char*>(output));
    
    delete[] input;
    delete[] output;
    
    return decrypted;
}