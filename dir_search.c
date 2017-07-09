#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dirent.h>


int is_match_name(char* fname, int* num)
{

    /*** hoge_0000.raw ********/

    const char* match_name = "hoge_****.raw";
    const int num_start = 5;

    int len_match = strlen(match_name);

    int len = strlen(fname);
    int i;


    if (len == len_match) {
        
        //check fname, "hoge_"
        for (i = 0; i < num_start; i++) {

            if (match_name[i] != fname[i]) {
                return 0;
            }
        }

        //extension check
        for (i = num_start+4; i < num_start+8; i++)  {
            if (match_name[i] != fname[i]) {
                return 0;
            }
        }

        //check nuber
        int digit = 0;
        int j = 0;
        for (i = num_start; i < num_start+4; i++,j++) {
            if (fname[i] >= 0x30 && fname[i] <= 0x39) {
                digit += (fname[i] -48) * pow(10, 3-j);
            }
            else {
                return 0;
            }

            if (j == 3) {
                *num = digit;
            }
        }

    
    }
    else {
        return 0;
    }

    return 1;
    
}

int search_file(const char* dir_path, int *max_index)
{

    DIR *dir;
    struct dirent *dp;

    dir = opendir(dir_path);
    int num;
    int max_num = 0;
    int flg = 0;
    for (dp=readdir(dir); dp != NULL; dp = readdir(dir)) {
        
        if (is_match_name(dp->d_name, &num)) {
            flg = 1;
            if (num > max_num) {
                max_num = num;
            }
            printf("match = %s, num = %d\n",dp->d_name, num);
        }
    }

    closedir(dir);

    *max_index = max_num; 

    return flg;

}

int main()
{

    int max_num;

    if (search_file("./", &max_num)) {
        printf("max_num = %d\n", max_num);
    }
    else {
        printf("no file match\n");
    }


    return 0;


}
