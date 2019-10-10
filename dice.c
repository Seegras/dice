/* 

 Electronic Diceroller

 Author: Peter Keel <seegras@discordia.ch>
 Date:   2001-05-11

 Dice is free software under the MIT License

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <popt.h>

#define GETOPT_NUMBER                        1010

int diceinit(void);
int dice(int num,int size);
//void diceinit(void);
//int dice(int num, int size)

static void printHelp(void) {
    fprintf(stderr,"Usage: dice [OPTION] <num>d<sides>\n");
    fprintf(stderr,"-h, --help                 print this message\n");
    fprintf(stderr,"-v, --version              print the version\n");
    fprintf(stderr,"\n");
}

static void printVersion(void) {
    fprintf(stderr,"Dice v.1.0  by <killer@discordia.ch>\n");
}

int main(int argc, const char ** argv) {

int times, rc, sides;
int help = 0, version = 0;
char * leftarg;
char * number;
struct poptOption optionsTable[] = {
    { "help", 'h', 0, &help, 0, "gives help" },
    { "version", 'v', 0, &version, 0 },
    { 0, 0, 0, 0, 0 } 
};

poptContext poptcon;

/*--- Initialisation of the random number generator ---*/
diceinit();

/*--- parameter-processing ----------------------------*/

    poptcon = poptGetContext("popti", argc, argv, optionsTable, 0);
    while ((rc = poptGetNextOpt(poptcon)) > 0) { 
        switch (rc) {
            case 'h': 
                help = 1;
                    break;
            case 'v': 
                version = 1;
                    break;
            default:
                fprintf(stderr, "Internal Error with parameter-processing\n");
                exit(1);
        }
    }
    leftarg = (char*) poptGetArg(poptcon);
    number = leftarg;

if (!(help) && !(version)) {
    if ((number == NULL) || number[0] == '-') {
    fprintf(stderr, "dice: too few arguments\n");
    fprintf(stderr, "Try `dice --help' for more information.\n");
    exit(1);
    }

}
    poptFreeContext(poptcon);
    if (version) printVersion();
    if (help) printHelp();


    if (!(help) && !(version)) {
        if (strchr(number,'d') != 0) {
            times = atoi(strsep(&number, "d"));
            sides = atoi(strsep(&number, "d"));
            fprintf(stdout, "%d\n",dice(times,sides));
        }
        else if (strchr(number,'w') != 0) {
            times = atoi(strsep(&number, "w"));
            sides = atoi(strsep(&number, "w"));
            fprintf(stdout, "%d\n",dice(times,sides));
        }
    }
return (0);
}

/*--- roll dice -------------------------------------------*/
int dice(int num, int size) {
    int val=0;

    while (num) {
        val += (rand() % size+1);
        --num;
    }
    return(val);
}
/*--- initialize dice w/ random seed ----------------------*/
int diceinit() {
    long tick;

    srand(time(&tick) %20000 );
    return(0);
}
