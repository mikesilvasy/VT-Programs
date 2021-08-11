#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#include "outfoxed.h"

int clueColors[NUMBER_OF_CLUES];
sem_t briefcaseSem;
sem_t monocleSem;
sem_t hatSem;
sem_t glovesSem;
sem_t necklaceSem;
sem_t flowerSem;
sem_t coatSem;
sem_t umbrellaSem;
sem_t glassesSem;
sem_t watchSem;
sem_t caneSem;
sem_t scarfSem;
sem_t suspectSem;
int suspectCount;
sem_t chickenSem;
pthread_mutex_t mutex;
int iter;

// CHICKENS

/* Each detective thread will execute the chicken_detective_thread 
 * function, which you must implement.  A detective thread must return
 * when the suspect has been found.
 */
extern void * chicken_detective_thread(void * chicken) {
    const Suspect *thief = NULL;
    sem_wait(&chickenSem);
    while (true) {
        sem_post(&chickenSem);
        pthread_mutex_lock(&mutex);
        if (iter < NUMBER_OF_SUSPECTS) {
            const Suspect *suspect = &suspects[iter];
            iter += 1;
            if ((suspect->clues[0] == briefcase || suspect->clues[1] == briefcase || suspect->clues[2] == briefcase) && clueColors[0] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == monocle || suspect->clues[1] == monocle || suspect->clues[2] == monocle) && clueColors[1] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == hat || suspect->clues[1] == hat || suspect->clues[2] == hat) && clueColors[2] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == gloves || suspect->clues[1] == gloves || suspect->clues[2] == gloves) && clueColors[3] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == necklace || suspect->clues[1] == necklace || suspect->clues[2] == necklace) && clueColors[4] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == flower || suspect->clues[1] == flower || suspect->clues[2] == flower) && clueColors[5] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == coat || suspect->clues[1] == coat || suspect->clues[2] == coat) && clueColors[6] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == umbrella || suspect->clues[1] == umbrella || suspect->clues[2] == umbrella) && clueColors[7] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == glasses || suspect->clues[1] == glasses || suspect->clues[2] == glasses) && clueColors[8] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == watch || suspect->clues[1] == watch || suspect->clues[2] == watch) && clueColors[9] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == cane || suspect->clues[1] == cane || suspect->clues[2] == cane) && clueColors[10] == 0) {
                eliminate_suspect(suspect);
            }
            else if ((suspect->clues[0] == scarf || suspect->clues[1] == scarf || suspect->clues[2] == scarf) && clueColors[11] == 0) {
                eliminate_suspect(suspect);
            }
            else {
                thief = suspect;
            }
            pthread_mutex_unlock(&mutex);
        }
        else {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }

    sem_wait(&chickenSem);
    if (thief != NULL) {
        announce_thief(thief);
    }
    sem_post(&chickenSem);
    pthread_exit(NULL);
}

// SUSPECTS

/* (2) Suspects.  Whenever a new suspect card is turned over, a new thread
 * will be created and starts executing the function 'new_suspect_thread,'
 * which you must implement.  The void * argument points to the suspect
 * that was revealed.  Suspects may appear in random order!
 *
 * Suspect (thread)s must return before the game can end.
 */
extern void * new_suspect_thread(void * suspect) {
    sem_wait(&suspectSem);
    if (suspectCount < NUMBER_OF_SUSPECTS) {
        suspectCount += 1;
    }
    else {
        sem_post(&chickenSem);      // Signals chickens after all (16) suspect cards have been turned over
    }
    sem_post(&suspectSem);
    pthread_exit(NULL);
}

// CLUES

/* (3) Clues. Each clue shows up in a separate thread.
 * You must implement the 12 functions below such that 
 *
 * (a) Each clue is decoded by the clue thread responsible for it.
 * (b) The clues are decoded in exactly the order prescribed by your 
 *     personal code, which is listed on the website.
 *
 * Clue (thread)s must also return before the game can end.
 */
extern void * briefcase_thread(void * clue) {
    sem_wait(&briefcaseSem);
    if (decode_clue(briefcase) == RED) {              // Saves value of 1 if red, 0 if green
        clueColors[0] = 1;
    }
    else {
        clueColors[0] = 0;
    }
    sem_post(&briefcaseSem);    // Release
    sem_post(&monocleSem);      // Signal
    pthread_exit(NULL);         // Exit thread
}
extern void * monocle_thread(void * clue) {
    sem_wait(&monocleSem);
    if (decode_clue(monocle) == RED) {
        clueColors[1] = 1;
    }
    else {
        clueColors[1] = 0;
    }
    sem_post(&monocleSem);
    sem_post(&hatSem);
    pthread_exit(NULL);
}
extern void * hat_thread(void * clue) {
    sem_wait(&hatSem);
    if (decode_clue(hat) == RED) {
        clueColors[2] = 1;
    }
    else {
        clueColors[2] = 0;
    }
    sem_post(&hatSem);
    sem_post(&glovesSem);
    pthread_exit(NULL);
}
extern void * gloves_thread(void * clue) {
    sem_wait(&glovesSem);
    if (decode_clue(gloves) == RED) {
        clueColors[3] = 1;
    }
    else {
        clueColors[3] = 0;
    }
    sem_post(&glovesSem);
    sem_post(&necklaceSem);
    pthread_exit(NULL);
}
extern void * necklace_thread(void * clue) {
    sem_wait(&necklaceSem);
    if (decode_clue(necklace) == RED) {
        clueColors[4] = 1;
    }
    else {
        clueColors[4] = 0;
    }
    sem_post(&necklaceSem);
    sem_post(&flowerSem);
    pthread_exit(NULL);
}
extern void * flower_thread(void * clue) {
    sem_wait(&flowerSem);
    if (decode_clue(flower) == RED) {
        clueColors[5] = 1;
    }
    else {
        clueColors[5] = 0;
    }
    sem_post(&flowerSem);
    sem_post(&coatSem);
    pthread_exit(NULL);
}
extern void * coat_thread(void * clue) {
    sem_wait(&coatSem);
    if (decode_clue(coat) == RED) {
        clueColors[6] = 1;
    }
    else {
        clueColors[6] = 0;
    }
    sem_post(&coatSem);
    sem_post(&umbrellaSem);
    pthread_exit(NULL);
}
extern void * umbrella_thread(void * clue) {
    sem_wait(&umbrellaSem);
    if (decode_clue(umbrella) == RED) {
        clueColors[7] = 1;
    }
    else {
        clueColors[7] = 0;
    }
    sem_post(&umbrellaSem);
    sem_post(&glassesSem);
    pthread_exit(NULL);
}
extern void * glasses_thread(void * clue) {
    sem_wait(&glassesSem);
    if (decode_clue(glasses) == RED) {
        clueColors[8] = 1;
    }
    else {
        clueColors[8] = 0;
    }
    sem_post(&glassesSem);
    sem_post(&watchSem);
    pthread_exit(NULL);
}
extern void * watch_thread(void * clue) {
    sem_wait(&watchSem);
    if (decode_clue(watch) == RED) {
        clueColors[9] = 1;
    }
    else {
        clueColors[9] = 0;
    }
    sem_post(&watchSem);
    sem_post(&caneSem);
    pthread_exit(NULL);
}
extern void * cane_thread(void * clue) {
    sem_wait(&caneSem);
    if (decode_clue(cane) == RED) {
        clueColors[10] = 1;
    }
    else {
        clueColors[10] = 0;
    }
    sem_post(&caneSem);
    sem_post(&scarfSem);
    pthread_exit(NULL);
}
extern void * scarf_thread(void * clue) {
    sem_wait(&scarfSem);
    if (decode_clue(scarf) == RED) {
        clueColors[11] = 1;
    }
    else {
        clueColors[11] = 0;
    }
    sem_post(&scarfSem);
    sem_post(&suspectSem);
    pthread_exit(NULL);
}

// OTHER

/* To give you a chance to (re-)initialize any data structures you may need,
 * we will call setup_play() every time a new game starts.
 * Thus, setup_play() may be called multiple times during one program run. 
 */
extern void setup_play(void) {
    int i;
    for (i = 0; i < NUMBER_OF_CLUES; i++) {
        clueColors[i] = -1;
    }
    sem_init(&briefcaseSem, 0, 1);
    sem_init(&monocleSem, 0, 1);
    sem_init(&hatSem, 0, 1);
    sem_init(&glovesSem, 0, 1);
    sem_init(&necklaceSem, 0, 1);
    sem_init(&flowerSem, 0, 1);
    sem_init(&coatSem, 0, 1);
    sem_init(&umbrellaSem, 0, 1);
    sem_init(&glassesSem, 0, 1);
    sem_init(&watchSem, 0, 1);
    sem_init(&caneSem, 0, 1);
    sem_init(&scarfSem, 0, 1);
    
    sem_init(&suspectSem, 0, 1);
    suspectCount = 1;

    sem_init(&chickenSem, 0, 1);
    pthread_mutex_init(&mutex, NULL);
    iter = 0;

    sem_wait(&monocleSem);
    sem_wait(&hatSem);
    sem_wait(&glovesSem);
    sem_wait(&necklaceSem);
    sem_wait(&flowerSem);
    sem_wait(&coatSem);
    sem_wait(&umbrellaSem);
    sem_wait(&glassesSem);
    sem_wait(&watchSem);
    sem_wait(&caneSem);
    sem_wait(&scarfSem);
    sem_wait(&suspectSem);
    sem_wait(&chickenSem);
    pthread_mutex_init(&mutex, NULL);
}