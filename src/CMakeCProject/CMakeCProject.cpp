// CMakeCProject.cpp: 定义应用程序的入口点。
//

#include "CMakeCProject.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#define bool int
#define true 1
#define false 0
#define NAME_LENGTH 30
#define TEL_LENGTH 15

typedef struct _Person
{
    int m_id;
    char m_name[NAME_LENGTH];
    char m_tel[TEL_LENGTH];
} Person;
void print_person(Person* person)
{
    //-表示左对齐，默认右对齐
    printf("%-5d%-15s%-20s\n", person->m_id, person->m_name, person->m_tel);
}
//返回 bool 表示读取到了文件的末尾
bool read_person(FILE* fp, Person* person)
{
    bool result = false;
    if (fscanf(fp, "%d %s %s", &person->m_id, &person->m_name, &person->m_tel) > 0)
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}
void write_person(FILE* fp, Person* person)
{
    // 就像read_person 是从文件里读取内容，使用的是fscanf
    // 写入文件使用fprintf ，语法类比printf
    //(1) your code
    fprintf(fp, "%d %s %s\n", person->m_id, person->m_name, person->m_tel);
}
typedef struct _PersonManager
{
    Person m_allPerson[100];
    int size;
} PersonManager;
void InitPersonMgr(PersonManager* personMgr)
{
    //(2) your code
    personMgr->size = 0;
}
void push_back(PersonManager* personMgr, Person* person)
{
    personMgr->m_allPerson[personMgr->size++] = *person;
}
void erase_person(PersonManager* personMgr, int index)
{
    assert(index >= 0 && index < personMgr->size);
    for (int i = index; i < personMgr->size - 1; i++)
    {
        //(3) your code

    }
    personMgr->size -= 1;
}
void InputOnePerson(PersonManager* personMgr);
bool DeletePerson(PersonManager* personMgr)
{
    printf("Please input person id for delete:");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < personMgr->size; i++)
    {
        if (personMgr->m_allPerson[i].m_id == id)
        {
            //(4) your code

            return true;
        }
    }
    return false;
}
bool QueryPersonByName(PersonManager* personMgr)
{
    printf("Please input name for query:");
    char name[NAME_LENGTH];
    scanf("%s", name);
    for (int i = 0; i < personMgr->size; i++)
    {
        if (strcmp(personMgr->m_allPerson[i].m_name, name) == 0)
        {
            printf("Find:\n");
            //(5) your code 
            print_person(&personMgr->m_allPerson[i]);
            return true;
        }
    }
    printf("not found %s\n", name);
    return false;
}
bool QueryPersonByTel(PersonManager* personMgr)
{
    printf("Please input tel for query:");
    char tel[TEL_LENGTH];
    scanf("%s", tel);
    for (int i = 0; i < personMgr->size; i++)
    {
        if (strcmp(personMgr->m_allPerson[i].m_tel, tel) == 0)
        {
            printf("Find:\n");
            print_person(&personMgr->m_allPerson[i]);
            return true;
        }
    }
    printf("not found %s\n", tel);
    return false;
}
void ShowAllPerson(PersonManager* personMgr)
{
    printf("All Person:\n");
    printf("id   name           tel\n");
    for (int i = 0; i < personMgr->size; i++)
    {
        print_person(&personMgr->m_allPerson[i]);
    }
}
bool SaveAllPersonToFile(PersonManager* personMgr)
{
    FILE* fp = fopen("data_saved.txt", "w");//以写方式打开文件
    if (fp == NULL)
    {
        printf("can not open file data_saved.txt for write data.\n");
        return false;
    }
    for (int i = 0; i < personMgr->size; i++)
    {
        //(6) your code
        write_person(fp, &personMgr->m_allPerson[i]);
    }
    fclose(fp);
    return true;
}
bool LoadAllPersonFromFile(PersonManager* personMgr, const char* fileName)
{
    FILE* fp = fopen(fileName, "r");//只读方式打开文本文件
    if (fp == NULL)
    {
        printf("load data failed . file %s not exits.\n", fileName);
        return false;
    }
    Person person;
    while (read_person(fp, &person))
    {
        push_back(personMgr, &person);
    }
    printf("load data from file success.\n");
    fclose(fp);
    return true;
}
void InputOnePerson(PersonManager* personMgr)
{
    printf("Please input one person：\n");
    printf("Please input id：");
    int id;
    scanf("%d", &id);
    Person person;
    memset(&person, 0, sizeof(Person));
    person.m_id = id;

    for (int i = 0; i < personMgr->size; i++)
    {
        if (personMgr->m_allPerson[i].m_id == id)
        {
            printf("%d already existed! Save failed.\n", id);
            return;
        }
    }

    printf("Please input name：");
    scanf("%s", person.m_name);

    printf("Please input tel：");
    scanf("%s", person.m_tel);

    printf("Input finished, save successed.\n");
    //(7) your code
    personMgr->m_allPerson[personMgr->size - 1] = person;
}
int main(int argv, char* argc[])
{
    PersonManager personMgr;
    InitPersonMgr(&personMgr);

    LoadAllPersonFromFile(&personMgr, "input_data.txt");
    ShowAllPerson(&personMgr);

    while (true)
    {
        printf("input a commond : \n");
        printf("1 [AddPerson]\n");
        printf("2 [ShowAllPerson]\n");
        printf("3 [QueryPerson by name]\n");
        printf("4 [QueryPerson by tel]\n");
        printf("5 [SaveAllPersonToFile]\n");
        printf("6 [DeletePerson]\n");
        printf("0 [ExitAndSaveChange]\n");
        int commond;
        scanf("%d", &commond);
        switch (commond)
        {
        case 1: { InputOnePerson(&personMgr); break; }
        case 2: { ShowAllPerson(&personMgr); break; }
        case 3: { QueryPersonByName(&personMgr); break; }
        case 4: { QueryPersonByTel(&personMgr); break; }
        case 5: { SaveAllPersonToFile(&personMgr); break; }
        case 6: { DeletePerson(&personMgr); break; }
        case 0: { SaveAllPersonToFile(&personMgr); return 0; }
        default: { printf("System Exit.\n"); return 0; }
        }
    }
    return 0;
}