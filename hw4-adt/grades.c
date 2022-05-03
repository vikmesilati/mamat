#include "grades.h"
#include "linked-list.h"

typedef struct { 
    char *name;
    int id;
} student;

struct grades* grades_init(){
    element_clone_t elem_clone;
    element_destroy_t elem_destroy;
    return list_init(elem_clone,elem_destroy);
}

void grades_destroy(struct grades *grades){
    list_destroy(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id){
    if(!grades){
        return 1;
    }
    struct iterator* it = list_begin(grades);
    student* new;
    new->name = name;
    new->id = id;
    //check if list is empty
    if(it == NULL){
        return list_push_front(grades,new);
    }
    while(it != NULL){
        student* current = list_get(it);
        if(current->id == id){
            return 1;
        }
        it = list_next(it);
    }


}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    

}

float grades_calc_avg(struct grades *grades, int id, char **out){

}

int grades_print_student(struct grades *grades, int id){

}

int grades_print_all(struct grades *grades){

}

