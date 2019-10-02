#define _POSIX_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include <json.h>
#include <stdlib.h>


int getChmod(const char *path){
    struct stat st;

    if (stat(path, &st) == -1) {
        return -1;
    }

    int p=0;
    
    if(stat(path, &st)==0){
    if(st.st_mode & S_IRUSR)
    p+=400;
    if(st.st_mode & S_IWUSR)
    p+=200;
    if(st.st_mode & S_IXUSR)
    p+=100;
    else if(st.st_mode & S_IRWXU)
    p+=700;
    if(st.st_mode & S_IRGRP)
    p+=40;
    if(st.st_mode & S_IWGRP)
    p+=20;
    if(st.st_mode & S_IXGRP)
    p+=10;
    else if(st.st_mode & S_IRWXG)
    p+=70;
    if(st.st_mode & S_IROTH)
    p+=4;
    if(st.st_mode & S_IWOTH)
    p+=2;
    if(st.st_mode & S_IXOTH)
    p+=1;
    else if(st.st_mode & S_IRWXO)
    p+=7;
    }
    return p;
}

void jsonmaker(const char *path){
   /*Creating a json object*/
  json_object * jobj = json_object_new_object();
  json_object * file = json_object_new_object();
  
  /*Creating a json array*/
  json_object *jarray = json_object_new_array();
  
  json_object_object_add(file, "Path", json_object_new_string(path));
  json_object_object_add(file, "Properties", json_object_new_int(getChmod(path)));
  
  json_object_array_add(jarray, file);
  
  /*Form the json object*/
  json_object_object_add(jobj,"Files", jarray);

 /*Now printing the json object*/
 FILE *fptr;
  fptr = fopen("/home/rushilroy/Testing/propertiesjson.json", "a");
  fprintf(fptr, "%s" , json_object_to_json_string(jobj));
  fclose(fptr);
  printf ("The json object created: %s\n",json_object_to_json_string(jobj));
}



int main(){
struct json_object *dir_object, *dir_array, *dir_array_object, *dir_array_object_path, *dir_array_object_start, *dir_array_object_end;
int arraylen, arraylooper;
char *path;
char patharray[100];
static const char filename[] = "/home/rushilroy/Documents/IBMProject2019/timeaccess2.json";
dir_object = json_object_from_file(filename);
dir_array = json_object_object_get(dir_object, "Directories");



  /*Creating a json object*/
//  json_object * jobj = json_object_new_object();

  /*Creating a json array*/
//  json_object *jarray = json_object_new_array();


// dir_array is an array of objects
arraylen = json_object_array_length(dir_array);

for (arraylooper = 0; arraylooper < arraylen; arraylooper++) {
  // get the i-th object in dir_array
  dir_array_object = json_object_array_get_idx(dir_array, arraylooper);
  // get the name attribute in the i-th object
  dir_array_object_path = json_object_object_get(dir_array_object, "Path");
  // print out the name attribute
  path = strdup(json_object_get_string(dir_array_object_path));
  jsonmaker(path);
/*
  json_object_array_add(jarray,json_object_new_string(path));
  json_object_array_add(jarray,json_object_new_int(getChmod(path)));
  */
}


}
