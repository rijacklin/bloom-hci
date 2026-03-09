# Bloom - Project Management System

Source code of my final project submission for the course [COMP 482: Human Computer Interaction](https://www.athabascau.ca/syllabi/comp/comp482.html). The project represents a stub functionality implementation of task-management software. The project uses [DearImGui](https://github.com/ocornut/imgui) (with OpenGL backend) and a MVC architecture approach. As the focus of the project was to design and then critically assess a UI, rather than a significant programming project, most functionality is written as stubs. The database-like functionality is simply text files and network processing functionality is conveyed to the user through a mock progress bar. Further discussion is included in a Word document at the root of this repo.

## Installation Instructions

This application only supports Linux and MacOS.

To compile the bloom application, from the main directory run:

```bash
make && make clean
```

Then from the main directory run:

```bash
./out/bloom
```

Or, to both compile and run in one command:

```bash
make && make clean && ./out/bloom
```

## Usage Instructions

Once Bloom opens, use the following credentials to log in:

username: admin
password: 1234

After logging in, you will be requested to change the temp password. The password
you set will be used going forward. To manually change the password or prevent the 
"Set New Password" window from appearing after login, edit the file in `./data/auth.txt`.

For example, the default credentials for the admin user are:

```text
USERNAME:admin
PASSWORD:pass
TEMPPW:true
---
```

To skip the "Set New Password" flow, update the `auth.txt` file as follows:

```text
USERNAME:admin
PASSWORD:pass
TEMPPW:false
---
```

All other application data (tasks, task cards, wiki pages, notifications) are included
in files within the `./data/` directory and do not require user intervention. As described
in the final report contained in this zip file, changes can be made to these files and
will be reflected in the application on reload (these files will also be updated based
on interactions with the application).
