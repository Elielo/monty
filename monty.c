#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char automate[20];
int doors[3];

int automated(char *yn) {
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	srand(tp.tv_nsec);
	int win = rand() % 3;
        clock_gettime(CLOCK_REALTIME, &tp); //reget nano
        srand(tp.tv_nsec);
	int test = rand() % 3; //test is a randomized choice
	doors[win] = 1;
        int other;
        int other2;
	
        for(int i = 0; i < 3; i++) {
                if(i != test && i != win) {   //this sets up other, which is not a win
                        other = i;      
                }
        }
        for(int i = 0; i < 3; i++) {
                if(i != test && i != other) {  //this sets up other2, which may or may not be a win
                        other2 = i;            
                }
        }
        FILE *file;
	if (*yn == 'y') { //if y
		test = other2;//test is now other2
        	if (doors[test] == 1) {
			file = fopen("yw", "a");
			fprintf(file, "w");
			fclose(file);
		}
                file = fopen("yt", "a");
                fprintf(file, "t");
        	fclose(file);
	}	
        if (*yn == 'n') {
		if (doors[test] == 1) {
			file = fopen("nw", "a");
			fprintf(file, "w");
			fclose(file);
		}	
		file = fopen("nt", "a");
		fprintf(file, "t");
		fclose(file);
	}
	exit(0);
}

int person() {
        srand(time(NULL));
        int win;
        win = rand() % 3;
        doors[win] = 1;
        printf("choose 0 1 or 2\n");
        int choice;     
        choice = getchar() - 48; //removed offset
        if (choice != 0 && choice != 1 && choice != 2) {
                printf("recieved %d. did not recieve 0 1 or 2. exiting.\n", choice);
                exit(1);
        }

        int other; 
        int other2;
        for(int i = 0; i < 3; i++) {
                if(i != choice && i != win) {   //this sets up other, which is not a win
                        other = i;      
                }
        }
        for(int i = 0; i < 3; i++) {
                if(i != choice && i != other) {  //this sets up other2, which may or may not be a win
                        other2 = i;            
                }
        }


        printf("door number %d is not a win. would you like to switch to door number %d?\ntype y or n\n", other, other2);
        int d;
        getchar();
        d = getchar();
        if (d == 121) {
              choice = other2;//choice is now other2
        }
        if (d != 121 && d != 110) {
              printf("error, entered %d, did not choose y or n. exiting\n", d);
              exit(1);
        }
        char correctness[10];
        strcpy(correctness, "wrong");
        if (doors[choice] == 1) {
              strcpy(correctness, "right"); //string for right or wrong 
        }

        printf("you chose door %d. you were %s\n", choice, correctness);
	exit(0);
}

int main (int argc, char *argv[]) {
        if (argc > 2) {
                printf("usage: %s [y/n]\n", argv[0]); //if they enter too many args
		exit(0);
        }
        for (int i = 0; i < 3; i++) {
                doors[i] = 0;
        }

        if (argc == 2) {
		if (*argv[1] == 'y' || *argv[1] == 'n') {
                	automated(argv[1]); //automate on y or n
        	}
	}
	
	person();	

}

