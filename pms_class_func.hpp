#ifndef PMS_CLASS_FUNC_HPP
#define PMS_CLASS_FUNC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "pms_class.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Date::Date(){}

std::string Date::get_date(){
   std::string d = "";
    if(std::to_string(m_month).length() < 2){
        d += "0" + std::to_string(m_month) + "/";
    }
    else{
        d += std::to_string(m_month) + "/";
    }

    if(std::to_string(m_day).length() < 2){
        d += "0" + std::to_string(m_day) + "/";
    }
    else{
        d += std::to_string(m_day) + "/";
    }
    d += std::to_string(m_year);
            
    return d;
}

void Date::set_date(const std::string &date_line){ // 03/18/2022
    m_month = std::stoi(date_line.substr(0,2)); // <- 03
    m_day = std::stoi(date_line.substr(3,2)); // <- 18
    m_year = std::stoi(date_line.substr(6,4)); // <- 2022
}

void Date::show_date(){
    std::string d = "";
    if(std::to_string(m_month).length() < 2){
        d = "0" + std::to_string(m_month);
    }
    else{
        d = std::to_string(m_month);
    }
    std::cout << d << "/";

    if(std::to_string(m_day).length() < 2){
        d = "0" + std::to_string(m_day);
    }
    else{
        d = std::to_string(m_day);
    }
    std::cout << d << "/";

    d = std::to_string(m_year);
    std::cout << d;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Task::Task(){}
Task::Task(const std::string &task_line){
    std::string token = "";
    std::string line = "";

    for(int i = 6; i < task_line.length(); ++i){ // starting from 6, to ignore 'task:'
        if(task_line[i] == ' '){
            if(token.compare("status:") == 0){
                m_task_name = line.substr(0, line.length() - 1);
                line = "";
                token = "";
                continue;
            }
            else if(token.compare("assignee:") == 0){
                m_status = line.substr(0, line.length() - 1);
                line = "";
                token = "";
                continue;
            }
            else if(token.compare("deadline:") == 0){
                m_assignee = line.substr(0, line.length() - 1);
                line = "";
                token = "";
                continue;
            }

            line += token + " ";
            token = "";
            continue;
        }
        token += task_line[i];
    }
    m_deadline.set_date(line);
}

std::string Task::get_task_name(){
    return m_task_name;
}
std::string Task::get_task_assignee(){
    return m_assignee;
}
std::string Task::get_task_status(){
    return m_status;
}
std::string Task::get_task_deadline(){
    return m_deadline.get_date();
}

void Task::set_task_name(const std::string &name){
    m_task_name = name;
}
void Task::set_task_assignee(const std::string &assignee){
    m_assignee = assignee;
}
void Task::set_task_status(const std::string &status){
    m_status = status;
}
void Task::set_task_deadline(const std::string &date){
    m_deadline.set_date(date);
}

void Task::show_task(){
    std::cout << "task: " << m_task_name << "   status: " << m_status << "   assignee: " << m_assignee << "   deadline: ";
    m_deadline.show_date();
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Project::Project(){}
Project::Project(const std::string &project_line){
    for(int i = 9; i < project_line.length(); ++i){ // starting from 9, to ignore 'project:'
        m_project_name += project_line[i];
    }
}

std::string Project::get_project_name(){
    return m_project_name;
}

std::string Project::get_project_task_line(){
    std::string task_line = "";
    for(int i = 0; i < m_tasks.size(); ++i){
        task_line += "task: " + m_tasks[i].get_task_name() + " status: " + m_tasks[i].get_task_status() 
                  + " assignee: " + m_tasks[i].get_task_assignee() + " deadline: " + m_tasks[i].get_task_deadline() + "\n";
    }
    return task_line;
}

int Project::get_project_tasks_count(){
    return m_tasks.size();
}

void Project::set_project_name(const std::string &name){
    m_project_name = name;
}

void Project::add_task(const Task &task){

    m_tasks.push_back(task);
}

void Project::set_project_task(const int index){
    std::string token;
    std::cin.ignore();
    std::cout << std::endl << "You can pass changing the element by writing 'pass'" << std::endl;
    std::cout << std::endl << "Insert Task's name: ";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0){
        m_tasks[index].set_task_name(token);
    }

    std::cout << std::endl << "Insert Task's status: ";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0){
        m_tasks[index].set_task_status(token);
    }

    std::cout << std::endl << "Insert Task's assignee: ";
    std::getline(std::cin, token);
    if(token.compare("pass") != 0){
         m_tasks[index].set_task_assignee(token);
    }

    std::cout << "\nInsert Task's deadline: ";
    std::cin >> token;
    if(token.compare("pass") != 0){
        m_tasks[index].set_task_deadline(token);
    }
}

void Project::remove_task(const int index){
    int i = 0;
    for(auto it = m_tasks.begin(); it != m_tasks.end(); ++it){
        if(i == index - 1){
            m_tasks.erase(it);
            break;
        }
        ++i;
    }
}

void Project::show_project(){
    std::cout << "project: " << m_project_name << "\n";
    for(int i = 0; i < m_tasks.size(); ++i){
        std::cout << "[" << i+1 << "]";
        m_tasks[i].show_task();
    }
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PMS::PMS(){}
PMS::PMS(std::ifstream &fin){

    std::string token; // token to read strings from the file
    std::string project_line;
    std::string task_line;

    fin >> token;
    if(token.compare("project:") != 0){
        std::cout << "\n-----File Data format is wrong !-----\n";
        exit(0);
    }

    while(!fin.eof()){

        while(token.compare("task:") != 0){
            project_line += token + " ";
            fin >> token;
        }

        Project project(project_line.substr(0, project_line.length() - 1));
        project_line = "";

        while(token.compare("project:") != 0 && token.compare("end") != 0){

            task_line += token + " ";
            fin >> token;

            while(token.compare("task:") != 0 && token.compare("project:") != 0 && token.compare("end") != 0){
                task_line += token + " ";
                fin >> token;
            }

            Task task(task_line);
            task_line = "";
            project.add_task(task);
        }
        m_projects.push_back(project);
    }
}

void PMS::add_new_project(){
    std::string token;

    std::cin.ignore();
    std::cout << std::endl << "Insert Project's name: ";
    std::getline(std::cin, token);
    Project project;
    project.set_project_name(token);
    Task task;

    std::cout << std::endl << "Insert Task's name: ";
    std::getline(std::cin, token);
    task.set_task_name(token);

    std::cout << std::endl << "Insert Task's status: ";
    std::getline(std::cin, token);
    task.set_task_status(token);

    std::cout << std::endl << "Insert Task's assignee: ";
    std::getline(std::cin, token);
    task.set_task_assignee(token);

    std::cout << "\nInsert Task's deadline: ";
    std::cin >> token;
    task.set_task_deadline(token);

    project.add_task(task);
    m_projects.push_back(project);
}

void PMS::add_new_task_to_the_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projects.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        std::string token;
        Task task;

        std::cin.ignore();
        std::cout << std::endl << "Insert Task's name: ";
        std::getline(std::cin, token);
        task.set_task_name(token);

        std::cout << std::endl << "Insert Task's status: ";
        std::getline(std::cin, token);
        task.set_task_status(token);

        std::cout << std::endl << "Insert Task's assignee: ";
        std::getline(std::cin, token);
        task.set_task_assignee(token);

        std::cout << "\nInsert Task's deadline: ";
        std::cin >> token;
        task.set_task_deadline(token);
        m_projects[index - 1].add_task(task);
    }
}

void PMS::add_projects_to_file(std::ostream &fout){
    std::string project_line = "";
    std::string task_line = "";
    for(int i = 0; i < m_projects.size(); ++i){
        fout << "project: " << m_projects[i].get_project_name() << "\n";
        fout << m_projects[i].get_project_task_line() << "\n";
    }
    fout << "end";
}

void PMS::edit_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projects.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        std::string token;
        std::cin.ignore();
        std::cout << std::endl << "Type Project's name (write 'pass' if you don't want to change): ";
        std::getline(std::cin, token);
        if(token.compare("pass") == 0){
            return;
        }
        else{
            m_projects[index - 1].set_project_name(token);
        }
    }
}

void PMS::edit_project_task(){
    int project_index;
    std::cout << "\nType Project's index: ";
    std::cin >> project_index;

    if(project_index > m_projects.size() || project_index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int task_index;
        std::cout << "\nType Task's index: ";
        std::cin >> task_index;

        if(task_index > m_projects[project_index - 1].get_project_tasks_count() || task_index < 1){
            std::cout << "\nWrong Index !\n";
        }
        else{
            m_projects[project_index - 1].set_project_task(task_index - 1);
        }
    }
}

void PMS::remove_project(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projects.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int i = 0;
        for(auto it = m_projects.begin(); it != m_projects.end(); ++it){
            if(i == index - 1){
                m_projects.erase(it);
                break;
            }
            ++i;
        }
    }
}

void PMS::remove_project_task(){
    int project_index;
    std::cout << "\nType Project's index: ";
    std::cin >> project_index;

    if(project_index > m_projects.size() || project_index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        int task_index;
        std::cout << "\nType Task's index: ";
        std::cin >> task_index;

        if(task_index > m_projects[project_index - 1].get_project_tasks_count() || task_index < 1){
            std::cout << "\nWrong Index !\n";
        }
        else{
            m_projects[project_index - 1].remove_task(task_index - 1);
        }
    }
}

void PMS::show_projec_information(){
    int index;
    std::cout << "\nType Project's index: ";
    std::cin >> index;

    if(index > m_projects.size() || index < 1){
        std::cout << "\nWrong Index !\n";
    }
    else{
        m_projects[index - 1].show_project();
    }
}

void PMS::list_of_projects_and_tasks(){
    for(int i = 0; i < m_projects.size(); ++i){
        std::cout << "[" << i+1 << "]";
        m_projects[i].show_project();
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif