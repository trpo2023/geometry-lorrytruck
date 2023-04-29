int check_str(char* a, char* b, int* error);

int check_find_close_bracket(char* a, int* l);

int check_first_num(char* a, int* open_bracket, int* error);

int check_second_num(char* a, int* first_num_elm, int* error);

int check_last_num(
        char* a, int* second_num_elm, int* close_bracket, int* error);

int check_close_bracket(char* a, int* l, int* last_num_elm, int* error);

int check_unexp_token(char* a, int* l, int* close_bracket, int* error);