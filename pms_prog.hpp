#ifndef PMS_PROG_HPP
#define PMS_PROG_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "pms_class_func.hpp"

void pms_program(const std::string &, const std::string &); // Start of the program
void pms_show_commands(); // Show all commands for User


void pms_show_commands(){

    std::cout << "\n====== User Commands ======\n\n";
    std::cout << "[1] List all Projects ands Tasks.\n";
    std::cout << "[2] Add a new Project.\n";
    std::cout << "[3] Add a new Task for Project.\n";
    std::cout << "[4] Show Project information.\n";
    std::cout << "[5] Edit Project.\n";
    std::cout << "[6] Edit Task.\n";
    std::cout << "[7] Delete Project.\n";
    std::cout << "[8] Delete Task.\n";
    std::cout << "[/exit] Save and exit the program.\n";
    std::cout << "\n===========================\n"; 
}

void pms_program(const std::string &path, const std::string &reserve){

    std::ifstream fin; // Read from file stream
    std::ofstream fout; // Insert to file stream

    fin.open(path);
    std::cout << "\n->> Checking the path...\n";
    
    if(fin.is_open()){
        std::cout << "\n->> Managing the Data...\n";

        PMS projects_data(fin);

        std::cout << "\n->> Data is Managed, ready to do Commands\n";
        projects_data.list_of_projects_and_tasks();
        pms_show_commands();
        
        // Empty original file
        fout.open(path, std::ofstream::out | std::ofstream::trunc);
        fout.close();

        // Add original file data to reserve file
        fout.open(reserve, std::ofstream::out | std::ofstream::trunc);
        projects_data.add_projects_to_file(fout);
        fout.close();

        // Command string for the User
        std::string com = "";
        
        // User can Edit the data now
        while(!(com.compare("/exit") == 0)){
            
            std::cout << "\nWaiting_for_command_number : ";
            std::cin >> com;

            if(com.compare("1") == 0){
                projects_data.list_of_projects_and_tasks();
            }
            else if(com.compare("2") == 0){
                projects_data.add_new_project();
            }
            else if(com.compare("3") == 0){
                projects_data.add_new_task_to_the_project();
            }
            else if(com.compare("4") == 0){
                projects_data.show_projec_information();
            }
            else if(com.compare("5") == 0){
                projects_data.edit_project();
            }
            else if(com.compare("6") == 0){
                projects_data.edit_project_task();
            }
            else if(com.compare("7") == 0){
                projects_data.remove_project();
            }
            else if(com.compare("8") == 0){
                projects_data.remove_project_task();
            }
            else if(com.compare("/help") == 0){
                pms_show_commands();
            }
            else if(com.compare("/exit") == 0){
                // save and exit
            }
            else{
                std::cout << "\nCommand is Unknown, please write '/help' to show information about the commands.\n";
            }
        }
        fout.open(path);
        projects_data.add_projects_to_file(fout);
        fout.close();
    }
    else{
        std::cout << "\n-----The file was not found or path is given wrong. The program will be closed !-----\n\n";
    }
    fin.close();
}

#endif