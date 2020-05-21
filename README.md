# Unisex Bathroom
 
## Abstract
The main abstract of this project is to practice solving problems with pthreads, and semaphores on Linux. The purpose of the project was to design a program that simulates how a shared bathroom in a university would work using pthreads and semaphores, with certain conditions regarding allowing males and females to enter the bathroom. Only one of the genders is allowed to use the bathroom at a time. The other gender must wait until the bathroom is empty to be allowed to enter it.
Approach

We were asked to create 4 different functions, 2 functions to allow males/females to enter, and 2 other functions for when they are leaving. There was no GUI required for this project. We decided to solve this problem by using the entering the bathroom functions to lock the bathroom for the specific gender entering, and the exiting the bathroom functions to unlock the bathroom if the counter inside the bathroom is 0 (which shows that the bathroom is empty). The simulation begins by asking the user to enter the amount of females and males in the university that will be using this shared bathroom. Then, the program randomly generates a dynamic queue for the bathroom. If there is a male in the bathroom, a female waiting next to enter, and another male approaching to enter the bathroom, the male will enter since the bathroom is locked to males at this time, and vice versa.

 ## Libraries
❏ Pthread: ​POSIX library that works best on linux only. Used to create threads and functions like: pthread_create/pthread_join.

❏ Semaphore:​ POSIX library used for synchronization and multithreading, and functions like: sem_wait/sem_post/sem_init.

❏ Stdio: ​Standard C library.

❏ Unistd: ​Library that allows access to POSIX operating system API. Used for the function sleep() which determines how long the male/female will spend in the bathroom.
Semaphores

❏ Mutex: ​Indicating that the bathroom is not used by male or female semaphores.

❏ Female_s:​ Indicating that the bathroom is locked by female semaphore

❏ Male_s:​ Indicating that the bathroom is locked by male semaphore

## Global Variables
❏ n/m: ​Number of males and females.

❏ men_in_bathroom/women_in_bathroom:​ gender bathroom counter.

❏ men_in_line/women_in_line:​ gender waiting to enter counter.

❏ MAX:​ Maximum number of inputs allowed by user for each gender
(Default is set to 100).

## Functions
❏ void Man_Wants_To_Enter(): ​This is a function that is called when there is a male in line. Function first checks if there is a female in the bathroom, if there is then the men_in_line is incremented, and the function waits until semaphore is unlocked so that the man can enter, locks the semaphore, and the men_in_line is decremented back again. Then, the men_in_bathroom counter is incremented, and the function checks if there are other men in line to unlock the male semaphore or not.

❏ void Woman_Wants_To_Enter(): ​This is a function that is called when there is a female in line. Function first checks if there is a male in the bathroom, if there is then the women_in_line is incremented, and the function waits until semaphore is unlocked so that the woman can
enter, locks the semaphore, and the women_in_line is decremented back again. Then, the women_in_bathroom counter is incremented, and the function checks if there are other women in line to unlock the male semaphore or not.

❏ void Man_Leaves(): ​This is a function that is called when the male is done with the bathroom (sleep is over), so the men_in_bathroom counter is incremented, and there is a condition to check if the bathroom is empty, and there are women in line to use the female semaphore. If there is male next in line, the male semaphore is unlocked, if nothing, the mutex semaphore indicating that the bathroom is empty will be unlocked.

❏ Void Woman_Leaves(): ​This is a function that is called when the female is done with the bathroom (sleep is over), so the women_in_bathroom counter is incremented, and there is a condition to check if the bathroom is empty, and there are men in line to use the male semaphore. If there is a female next in line, the female semaphore is unlocked, if nothing, the mutex semaphore indicating that the bathroom is empty will be unlocked.

❏ void Gender(char,int):​ This is a function that is called when the threading has begun, and males and females are created. The char passed indicates the gender of the one next to enter the bathroom, and the integer is the number of this user (whether 1st/2nd/3rd male or female). This is the function mentioned in the requirements of the project, that shows will call the ..._To_Enter() functions and .._Leaves() functions. This function will also call the Bathroom_sign() function to show the bathroom status.

❏ void Begin(int):​ This is the function that is being threaded. It receives an array of integers that was created in MakeLine function, that shows a dynamic list of males and females that will enter, and begins creating the Males and Females in line for simulation.

❏ void MakeLine():​ This function uses the number of males and females entered by the user to fill an array with numbers representing these females and males. Numbers less than total are females, numbers greater than total are males.

❏ void Bathroom_Sign():​ This function displays the status of the bathroom whether it is occupied by females, males or empty. It checks on women_in_bathroom, and men_in_bathroom to know.

❏ void GetTotal():​ This function is responsible for gathering the inputs from the user regarding the number of males and females, and performing checks on user entry.
Screenshots
