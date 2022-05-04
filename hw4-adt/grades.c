#include "grades.h"
#include "linked-list.h"

typedef struct { 
    char *name;
    int id;
    struct list *studGrades;
} student;

typedef struct {
    char *name;
    int grade;
} gradeStud;

struct grades* grades_init(){
    element_clone_t elem_clone;
    element_destroy_t elem_destroy;
    struct grades *grades = (struct grades*)malloc(sizeof(grades));
    grades = (struct grades*)list_init(elem_clone,elem_destroy);
    return grades;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades);
}

int grades_add_student(struct grades *grades, const char *name, int id){
    if(!grades){
        return -1;
    }
    struct iterator* it = list_begin(grades);
    student *new;
    new->name = name;
    new->id = id;
    element_clone_t elem_clone;
    element_destroy_t elem_destroy;
    new->studGrades = list_init(elem_clone,elem_destroy);
    //check if list is empty
    if(it == NULL){
        return list_push_front(grades,new);
    }
    while(it != NULL){
        student *current = list_get(it);
        if(current->id == id){
            return -1;
        }
        it = list_next(it);
    }
    return list_push_back(grades,new);
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    if(!grades || grade < 0 || grade > 100){
        return -1;
    }
    gradeStud *newGrade;
    newGrade->name = name;
    newGrade->grade = grade;
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        if(currentStud->id = id){
            itGrade = list_begin(currentStud->studGrades);
            while(itGrade != NULL){
                gradeStud *currentGrade = list_get(itGrade);
                if(currentGrade->name == name){
                    return -1;
                }
                itGrade = list_next(itGrade);
            }
            return list_push_back(currentStud->studGrades,newGrade);
        }
        itStud = list_next(itStud);
    }
    return -1;
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        if(currentStud->id = id){
            *out = (char*)malloc(sizeof(out));
            if(!*out){
                *out = NULL;
            }else{
                *out = currentStud->name;
            }
            float sum = 0;
            size_t numOfGrades = list_size(currentStud->studGrades);
            itGrade = list_begin(currentStud->studGrades);
            while(itGrade != NULL){
                gradeStud *currentGrade = list_get(itGrade);
                sum += currentGrade->grade;
                itGrade = list_next(itGrade);
            }
            sum = sum / numOfGrades;
            return sum;
        }
        itStud = list_next(itStud);
    }
    return -1;
}

int grades_print_student(struct grades *grades, int id){
     if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        if(currentStud->id = id){
            printf("%s %d: ",currentStud->name,currentStud->id);
            itGrade = list_begin(currentStud->studGrades);
            while(itGrade != NULL){
                gradeStud *currentGrade = list_get(itGrade);
                itGrade = list_next(itGrade);
                if(itGrade == NULL){
                    printf("%s %d",currentGrade->name,currentGrade->grade);
                }else{
                    printf("%s %d, ",currentGrade->name,currentGrade->grade);
                }
            }
            return 0;
        }
        itStud = list_next(itStud);
    }
    return -1;
}

int grades_print_all(struct grades *grades){
    if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        printf("%s %d: ",currentStud->name,currentStud->id);
        itGrade = list_begin(currentStud->studGrades);
        while(itGrade != NULL){
            gradeStud *currentGrade = list_get(itGrade);
            itGrade = list_next(itGrade);
            if(itGrade == NULL){
                printf("%s %d\n",currentGrade->name,currentGrade->grade);
            }else{
                printf("%s %d, ",currentGrade->name,currentGrade->grade);
            }
        }
        itStud = list_next(itStud);
    }
    return 0;
}
