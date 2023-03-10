#include "utils.hpp"

void check_args(int argc) {
    if(argc < 4) {
		cout<<"Insufficient number of parameters: ./tema1 nr_mappers nr_reducers input_file\n";
		exit(1);
	}
}

priority_queue<pair<int, string>> get_files_q(string filename) {
    string name;
    string path = "";
    priority_queue<pair<int, string>> files;
    int file_nr, file_size;

    ifstream fin(filename);

    if(!fin) {
        cout << "File " << filename << " can't be opened.\n";
		exit(1);
    }

    fin >> file_nr;

    for (int i = 0; i < file_nr; ++i) {
        fin >> name;
        path += strtok(&name[0], "\\");

        FILE *f = fopen(path.c_str(),"rb");
        fseek(f, 0, SEEK_END);
        file_size = ftell(f);
        fclose(f);

        files.push(make_pair(file_size, path));
        path = "";
    }

    fin.close();
    return files;
}

unordered_map<int, vector<int>> *initialize_lists(int nr_reducers) {
    unordered_map<int, vector<int>> *umap = new unordered_map<int, vector<int>>;
    vector<int> list;

    for (int i = 2; i <= nr_reducers + 1; ++i) {
        umap->insert({i, list});
    }

    return umap;
}