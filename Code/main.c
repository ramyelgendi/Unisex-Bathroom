// Ramy ElGendi
// 900170269
// OS Project 2

// Library
#include <pthread.h> // For man and woman threads
#include <stdio.h>  // Standard linux library
#include <unistd.h> // For sleep() function
#include <semaphore.h> // For creating the new bathroom

// Global Variables
int n=0,m=0,men_in_bathroom=0,women_in_bathroom=0,men_in_line=0,women_in_line=0,MAX=100;
#define MaleTimeInbathroom 5 // Time female spends in bathroom in minutes
#define FemaleTimeInbathroom 9 // Time female spends in bathroom in minutes

// Semaphores
sem_t mutex, female_s, male_s;

void Bathroom_Sign() { // Function to view the bathroom sign
    if(women_in_bathroom > 0 && men_in_bathroom == 0 ) {
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
        printf("▐ Bathroom Sign: Female Present ▐\n");
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
    }
    else if(men_in_bathroom > 0 && women_in_bathroom == 0) {
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
        printf("▐ Bathroom Sign: Male Present ▐\n");
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
    }
    else if(men_in_bathroom==0 && women_in_bathroom==0) {
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
        printf("▐ Bathroom Sign: Empty ▐\n");
        printf("▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
    }
}

void Man_Wants_To_Enter() {
    while (sem_wait(&mutex) != 0) {
        printf("[ERROR] Mutex Failed\n");
    }
    if (women_in_bathroom > 0) {
        men_in_line++;
        sem_post(&mutex);
        while (sem_wait(&male_s) != 0) {
            printf("[ERROR] Male Mutex Failed\n");
        }
        men_in_line--;
    }
    men_in_bathroom++;
    if (men_in_line > 0)
        sem_post(&male_s);
    else
        sem_post(&mutex);
}

void Man_Leaves()
{
    while (sem_wait(&mutex) != 0) {
        printf("[ERROR] Mutex Failed\n");
    }
    men_in_bathroom--;
    if ((women_in_line > 0) && (men_in_bathroom == 0))
        sem_post(&female_s);
    else if (men_in_line > 0)
        sem_post(&male_s);
    else sem_post(&mutex);
}

void Woman_Wants_To_Enter()
{
    while (sem_wait(&mutex) != 0) {
        printf("[ERROR] Mutex Failed\n");
    }
    if (men_in_bathroom > 0) {
        women_in_line++;
        sem_post(&mutex);
        while (sem_wait(&female_s) != 0) {
            printf("[ERROR] Female Mutex Failed\n");
        }
        women_in_line--;
    }
    women_in_bathroom++;
    if (women_in_line > 0)
        sem_post(&female_s);
    else
        sem_post(&mutex);
}

void Woman_Leaves()
{
    while (sem_wait(&mutex) != 0) {
        printf("[ERROR] Mutex Failed\n");
    }
    women_in_bathroom--;
    if ((men_in_line > 0) && (women_in_bathroom == 0))
        sem_post(&male_s);
    else if (women_in_line > 0)
        sem_post(&female_s);
    else
        sem_post(&mutex);
}
void Gender(char gender, int x) // Function (without for loop) from the project template sent
{
    Bathroom_Sign();
    if(gender == 'f') {
        Woman_Wants_To_Enter();
        printf("♀ Female %d is in the bathroom.\n",x);
        Bathroom_Sign();
        sleep(FemaleTimeInbathroom);
        printf("♀ Female %d is leaving the bathroom.\n",x);
        Woman_Leaves();
    } else if(gender == 'm') {
        Man_Wants_To_Enter();
        printf("♂ Male %d is in the bathroom.\n",x);
        Bathroom_Sign();
        sleep(MaleTimeInbathroom);
        printf("♂ Male %d is leaving the bathroom.\n",x);
        Man_Leaves();
    }
    Bathroom_Sign();
}

void *Begin(void* line) // Function called by threads to begin threading
{
    int x = *((int*)line);
    if (x >= (m+n)) {
        printf("♂ Male %d is in the line.\n",x-(m+n));
        Gender('m',x-((m+n)));
    }
    else {
        printf("♀ Female %d is in the line.\n",x);
        Gender('f',x);
    }
    return NULL;
}

int GetTotal() { // Getting input from user
    printf("* Enter total number of males in queue: (Max %d) \n♂ Males: ",MAX);
    scanf("%d",&n);
    while(n>MAX || n<0) { // Max is 100 as stated in the template
        printf("[ERROR] %d is beyond the limit, reenter: \n♂ Males: ", n);
        scanf("%d",&n);
    }


    printf("* Enter total number of females in queue: (Max %d) \n♀ Females: ", MAX);
    scanf("%d",&m);
    while(m>MAX || m<0) { // Max is 100 as stated in the template
        printf("[ERROR] %d is beyond the limit, reenter: \n♀ Females: ", m);
        scanf("%d",&m);
    }


    return n+m;
}
void MakeLine(int *line) { // Function to transform input into an array to be sent to threadding function
    int j = 0;
    for(int i=m;i>0;i--) { // Idea is that men will be numbers < Total, women > Total
        line[j] = i;
        j++;
    }
    for(int i=n;i>0;i--) {
        line[j] = i+(m+n);
        j++;
    }
}

int main() {
    int total = GetTotal(); // Getting user input
    int line[total]; // Creating array to be sent to thread
    MakeLine(line); // Adding males and females array to the array
    pthread_t t[total]; // Threadding array
    sem_init(&mutex, 0, 1); // Semaphore to lock
    sem_init(&male_s, 0, 0); // Male semaphore
    sem_init(&female_s, 0, 0); // Female semaphore

    printf("\nBathroom Simulation:\n\n");
    for (int i = 0; i < total; i++)
        pthread_create(&t[i], NULL, Begin, (void*)&line[i]);

    for (int i = 0; i < total; i++)
        pthread_join(t[i], NULL);

    return 0;

}