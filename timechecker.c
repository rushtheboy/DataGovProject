#include <stdio.h>
#include <json.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int time_to_int(char *start) {
char *newstart;

int i;

for(i=0;i<=4;i++){
newstart[i] = start[i];
}

char stm1 = newstart[3];
char stm2 = newstart[4];

newstart[2] = stm1;
newstart[3] = stm2;

int time = atoi(newstart);
time = time/10;
//printf("%d \n", time);
return(time);
}


int system_time_to_int(char *systime){

int i=0;
while(systime[i]!=':'){
i++;
}

int i1 = systime[i-2] - '0';
int i2 = systime[i-1] - '0';
int i3 = systime[i+1] - '0';
int i4 = systime[i+2] - '0';

int newsystime = (1000*i1)+(100*i2)+(10*i3)+i4;

return(newsystime);

}


int main(){

struct json_object *dir_object, *dir_array, *dir_array_object, *dir_array_object_path, *dir_array_object_start, *dir_array_object_end;

struct json_object *file_object, *file_array, *file_array_object, *file_array_object_path, *file_array_object_Chmod;

int arraylen, arraylooper;
char start[5];
char end[5];
char *startpass;
char *endpass;
char *path; 

static const char filesjson[] = "/home/rushilroy/Documents/IBMProject2019/timeaccess2.json";
dir_object = json_object_from_file(filesjson);
dir_array = json_object_object_get(dir_object, "Directories");

static const char propertiesjson[] = "/home/rushilroy/Testing/propertiesjson.json";
file_object = json_object_from_file(filesjson);
file_array = json_object_object_get(file_object, "Files");



// dir_array is an array of objects
arraylen = json_object_array_length(dir_array);

for (arraylooper = 0; arraylooper < arraylen; arraylooper++) {
  // get the i-th object in dir_array
  dir_array_object = json_object_array_get_idx(dir_array, arraylooper);
 // file_array_object = json_object_array_get_idx(file_array, arraylooper);
  
//  file_array_object_path = json_object_object_get(dir_array_object, "Path");
//  printf("Path: %s\n", json_object_get_string(file_array_object_path));
  
  // get the start time attribute in the i-th object
  dir_array_object_start = json_object_object_get(dir_array_object, "Start_time_to_prevent_access");

  startpass = strdup(json_object_get_string(dir_array_object_start));
    
  // get the end time attribute in the i-th object
  dir_array_object_end = json_object_object_get(dir_array_object, "End_time_to_prevent_access");
  //print the start time attribute
  //  printf("End_time: %s\n", json_object_get_string(dir_array_object_end));
  endpass = strdup(json_object_get_string(dir_array_object_end));
  
  dir_array_object_path = json_object_object_get(dir_array_object, "Path");
  path = strdup(json_object_get_string(dir_array_object_path));
  printf("%s\n", path);

  int stime = time_to_int(startpass);
  int etime = time_to_int(endpass);
  printf("\nStart time: %d\n", stime);
  printf("End time: %d\n", etime);
  
   
   time_t curtime;
   struct tm *loc_time;
   //Getting current time of system
   curtime = time (NULL);
   // Converting current time to local time
   loc_time = localtime (&curtime);
   int systime = system_time_to_int(asctime(loc_time));
   printf("Current system time: %d\n",systime);
   
   if(stime>etime){
   printf("Case in which starts in the evening ends in the morning\n");
   if(stime<=systime<=2400 && 0<=systime<=etime){
   printf("The file is not accessible right now.\n");
   if(chown(json_object_get_string(dir_array_object_path), 0 ,1000)!=0)
   perror("chown() error");
   printf("%s \n",strdup(json_object_get_string(dir_array_object_path)));
   if (chmod(json_object_get_string(dir_array_object_path), S_IRWXU) != 0)
   perror("chmod() error");
   }
   else if(stime<=systime<=etime){
   printf("The file is accessible right now.\n");
   if (chmod(json_object_get_string(dir_array_object_path), S_IRWXU||S_IRGRP||S_IROTH) != 0)
   perror("chmod() error");
   }
   }
   
   else if(stime<etime){
   printf("Case in which starts in the morning ends in the evening\n");
   if(stime<=systime<=etime){
   printf("The file is accessible right now.\n");
   }
   else if(stime<=systime<=2400 && 0<=systime<=etime){
   printf("The file is not accessible right now.\n");
   if(chown(json_object_get_string(dir_array_object_path), 0 ,1000)!=0)
   perror("chown() error");
   if (chmod(json_object_get_string(dir_array_object_path), S_IRWXU) != 0)
   perror("chmod() error");
   }
   }
  
}


}
