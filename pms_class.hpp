#ifndef PMS_CLASS_HPP
#define PMS_CLASS_HPP

#include <vector>

class Date{

    private:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        Date(); // Default

        std::string get_date(); // Get Date in string

        void set_date(const std::string &); // Set date (month/day/year)
        void show_date(); // Show date
};

class Task{

    private:
        std::string m_task_name{};
        std::string m_assignee{};
        std::string m_status{};
        Date m_deadline;
    
    public:
        Task();  // Default
        Task(const std::string &); // Task ctor (must start with 'task:' and have 'status:', 'assignee:', 'deadline:')

        std::string get_task_name(); // Get Task Name in string
        std::string get_task_assignee(); // Get Task Assignee's name in string
        std::string get_task_status(); // Get Task Status in string
        std::string get_task_deadline(); // Get Task Deadline in string
        
        void set_task_name(const std::string &); // Set Task's name
        void set_task_assignee(const std::string &); // Set Task's assignee
        void set_task_status(const std::string &); // Set Task's status
        void set_task_deadline(const std::string &); // Set Task's deadline

        void show_task(); // Show task
};

class Project{

    private:
        std::string m_project_name{};
        std::vector<Task> m_tasks;

    public:
        Project();  // Default
        Project(const std::string &); // Project ctor (must start with 'project:')

        std::string get_project_name(); // Get Project's name in string
        std::string get_project_task_line(); // Get Project's every task's line
        int get_project_tasks_count(); // Get number of Tasks of the Project

        void set_project_name(const std::string &); // Set Project's name
        void set_project_task(const int); // Set Project's Task
        void add_task(const Task &); // Add Task
        void remove_task(const int); // Remove Task
        void show_project(); // Show project
};

class PMS{

    private:
        std::vector<Project> m_projects;

    public:
        PMS(); // Default
        PMS(std::ifstream &); // Project Management System ctor

        void add_new_project(); // Add a new project to PMS
        void add_new_task_to_the_project(); // Add a new Task to existing project
        void add_projects_to_file(std::ostream &); // Add projects to given file
        void edit_project(); // Edit project
        void edit_project_task(); // Edit project's task
        void remove_project(); // Remove project
        void remove_project_task(); // Remove project's task
        void show_projec_information(); // Show Project's Tasks
        void list_of_projects_and_tasks(); // Show all projects with Tasks
};

#endif