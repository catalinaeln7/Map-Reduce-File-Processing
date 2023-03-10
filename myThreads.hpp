#pragma once

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <cmath>

void *reducer(void *arg);
void *mapper(void *arg);

// for (int i = 2; i <= nr_reducers + 1; ++i) {
//     my_data[i].thread_id = i;
//     my_data[i].pkt = pkt;
//     r = pthread_create(&threads[i], NULL, reducer, &my_data[i]);

//     if (r) {
// 		printf("Eroare la crearea reducer-ului %d\n", i);
// 		exit(-1);
// 	}
// }



// TEST VALORI FISIERE
        // pthread_mutex_lock(&pkt->mutex_test);
        // fin>>n; 
        // cout<<n<<endl;
        // for (int i = 0; i < n; ++i) {
        //     fin>>nr; 
        //     cout<<nr<<" ";
        // }
        // cout<<endl<<endl;
        // pthread_mutex_unlock(&pkt->mutex_test);