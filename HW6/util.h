
//menu
void menu();
void file_operations(char features[10][15]);
void search_products(char features[10][15]);
void check_stock();
void brand_stock_control();
//file operations
void add_a_new_product(char features[10][15]);
void delete_a_product();
void update_a_product(char features[10][15]);
void add_feature_to_products(char features[10][15]);
void add_a_new_stock();
void delete_a_stock();
void update_a_stock();
//search products
void list_all_products();
void filter_products(char features[10][15]);
//check stock
void check_stock_part1();
void check_stock_part2();
void check_stock_part3();


int mystrcmp(const char *s1, const char *s2);
int index_func(char arr[], char c, int start_index);