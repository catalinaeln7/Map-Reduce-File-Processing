#pragma once 

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstring>
#include <queue>
#include <unordered_map>

using namespace std;

struct pack {
    int thread_id;
    int nr_reducers;
    pthread_mutex_t mutex_pop;
    pthread_mutex_t mutex_push;
    pthread_mutex_t mutex_test;
    priority_queue<pair<int, string>> files_queue;
    unordered_map<int, vector<int>> *p_lists;
};

void check_args(int argc);
priority_queue<pair<int, string>> get_files_q(string input_file);
unordered_map<int, vector<int>> *initialize_lists(int nr_reducers);