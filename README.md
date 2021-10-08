# Brian Yu
## CS50 Fall 2021, Lab 3

GitHub username: brianyu20

Notes&Assumptions

1. For each module, the test file and makefile is designed so that it creates a testing.out that it prints out to. That is why all the test files mostly use 'printf' instead of fprintf. 

2. Each module shows no memory leak when run with myvalgrind. Therefore, no special testing of module_delete was tested because of the delete function wasn't working correctly, there would have been memory leaks. 

3. running make all makes all the subdirectories. 