#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the student struct for inserting to the grade struct
typedef struct { 
    char *name;
    int id;
    struct list *studGrades;
} student;

// Define the course struct for inserting to the student grades struct
typedef struct {
    char *name;
    int grade;
} course;

// Define the grades strcut from grades.h to use in main.c
struct grades{
    struct list* students;
};



/**
 * @brief Clones a course element to the *output
 * @returns A cloned element to *output, returns 0 on success
 * @note User function defined in linked-list.h
 */
int element_clone_course(void *element, void **output){
    course* given = (course*)element;
    course* new = (course*)malloc(sizeof(course));
    if(new == NULL){
        free(new);
        return -1;
    }////////
    new->name = malloc(sizeof(char)*(strlen(given->name)+1));
    if(new->name == NULL){
	    free(new->name);
        free(new);
        return -1;
    }
    strcpy(new->name,given->name);
    new->grade = given->grade;
    *output = new;
    return 0;
}

/**
 * @brief Destroys a course element
 * @note always succeedes
 */
void element_destroy_course(void *element){
    course* destroy = (course*)element;
    free(destroy->name);
    free(element);
}

/**
 * @brief Destroys a student element
 * @note always succeedes
 */
void element_destroy_student(void *element){
    student* destroy = (student*)element;
    list_destroy(destroy->studGrades);
    free(destroy->name);
    free(destroy);
}

/**
 * @brief Clones a student element to the *output
 * @returns A cloned element to *output, returns 0 on success
 * @note User function defined in linked-list.h
 */
int element_clone_student(void *element, void **output){
    element_clone_t elem_clone = &element_clone_course;
    element_destroy_t elem_destroy = &element_destroy_course;
    student* given = (student*)element;
    student* new = (student*)malloc(sizeof(student));
    if(new == NULL){
        free(new); 
        return -1;
    }///////
    new->name = (char*)malloc(sizeof(char)*(strlen(given->name)+1));
    if(new->name == NULL){
	free(new->name);
        free(new);
        return -1;
    }
    strcpy(new->name,given->name);
    new->id = given->id;
    new->studGrades = list_init(elem_clone,elem_destroy);
    struct iterator* it = list_begin(given->studGrades);
    while(it != NULL){
        course* temp = list_get(it);
        int result = list_push_back(new->studGrades,temp);
        if(result != 0){
            list_destroy(new->studGrades);
            free(new->name);
            free(new);
            return -1;
        }
        it = list_next(it);
    }
    *output = new;
    return 0;
}

/**
 * @brief initiates a grades struct 
 * @returns A pointer to the new grades struct
 */
struct grades* grades_init(){
    element_clone_t elem_clone = &element_clone_student;
    element_destroy_t elem_destroy = &element_destroy_student;
    struct grades *grades = (struct grades*)malloc(sizeof(struct grades));
    if(grades == NULL){
        free(grades);
        return NULL;
    }
    grades->students = list_init(elem_clone,elem_destroy);
    return grades;
}

/**
 * @brief destroyes a grades struct
 * @note always succeedes
 */
void grades_destroy(struct grades *grades){
    list_destroy(grades->students);
    free(grades);
}


/**
 * @brief Adds a student to the grades list
 * @returns 0 on success, -1 otherwise
 */
int grades_add_student(struct grades *grades, const char *name, int id){
    if(!grades){
        return -1;
    }
    int result;
    element_clone_t elem_clone = &element_clone_course;
    element_destroy_t elem_destroy = &element_destroy_course;
    struct iterator* it = list_begin(grades->students);
    student *new = (student*)malloc(sizeof(student));
    if(!new){
        free(new);
        return -1;
    }
    new->name = (char*)malloc(sizeof(name));
    if(!new->name){
        element_destroy_student(new);
        return -1;
    }
    strcpy(new->name,name);
    new->id = id;
    new->studGrades = list_init(elem_clone,elem_destroy);
    //check if list is empty
    if(it == NULL){
        result = list_push_back(grades->students,new);
        element_destroy_student(new);
        return result;
    }
    while(it != NULL){
        student *current = list_get(it);
        if(current->id == id){
	        element_destroy_student(new);
            return -1;
        }
        it = list_next(it);
    }
    result = list_push_back(grades->students,new);
    element_destroy_student(new);	
    return result;
}

/**
 * @brief Adds a course with name,grade to the student with id
 * @returns 0 on success, -1 otherwise
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    if(!grades || grade < 0 || grade > 100){
        return -1;
    }
    course *newGrade = (course*)malloc(sizeof(course));
    if(!newGrade){
        free(newGrade);
        return -1;
    }
    newGrade->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if(!newGrade->name){
	    element_destroy_course(newGrade);
        return -1;
    }
    strcpy(newGrade->name,name);
    newGrade->grade = grade;
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades->students);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        if(currentStud->id == id){
            itGrade = list_begin(currentStud->studGrades);
            while(itGrade != NULL){
                course *currentGrade = list_get(itGrade);
                if(strcmp(currentGrade->name,name) == 0){
		            element_destroy_course(newGrade);
                    return -1;
                }
                itGrade = list_next(itGrade);
            }
            int result = list_push_back(currentStud->studGrades,newGrade);
	        element_destroy_course(newGrade);
            return result;
        }
        itStud = list_next(itStud);
    }
    element_destroy_course(newGrade);
    return -1;
}

/**
 * @brief Calculates the avg of the student with id 
 * @returns The avg of students grades, his name in *out
 */
float grades_calc_avg(struct grades *grades, int id, char **out){
    if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades->students);
    while(itStud != NULL){
        student *currentStud = (student*)list_get(itStud);
        if(currentStud->id == id){
            *out = malloc(sizeof(char)*(strlen(currentStud->name)+1));
            if(*out == NULL){
                return -1;
            }
            strcpy(*out, currentStud->name);
            float sum = 0;
            size_t numOfGrades = list_size(currentStud->studGrades);
            if(numOfGrades == 0){
                return 0;
            }
            itGrade = list_begin(currentStud->studGrades);
            while(itGrade != NULL){
                course *currentGrade = list_get(itGrade);
                sum += currentGrade->grade;
                itGrade = list_next(itGrade);
            }
            sum = sum / numOfGrades;
            return sum;
        }
        itStud = list_next(itStud);
    }
    *out = NULL;
    return -1;
}

/**
 * @brief prints a student with id and all his courses
 * @returns 0 on success, -1 otherwise
 */
int grades_print_student(struct grades *grades, int id){
     if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades->students);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        if(currentStud->id == id){
            printf("%s %d:",currentStud->name,currentStud->id);
            itGrade = list_begin(currentStud->studGrades);
            if(itGrade == NULL){printf("\n");}
            while(itGrade != NULL){
                course *currentGrade = list_get(itGrade);
                itGrade = list_next(itGrade);
                if(itGrade == NULL){
                    printf(" %s %d\n",currentGrade->name,currentGrade->grade);
                }else{
                    printf(" %s %d,",currentGrade->name,currentGrade->grade);
                }
            }
            return 0;
        }
        itStud = list_next(itStud);
    }
    return -1;
}

/**
 * @brief Prints all the students and their grades by order
 * @returns 0 on success, -1 otherwise
 * @note User function defined in linked-list.h
 */
int grades_print_all(struct grades *grades){
    if(!grades){
        return -1;
    }
    struct iterator *itStud, *itGrade;
    itStud = list_begin(grades->students);
    while(itStud != NULL){
        student *currentStud = list_get(itStud);
        printf("%s %d:",currentStud->name,currentStud->id);
        itGrade = list_begin(currentStud->studGrades);
        if(itGrade == NULL){printf("\n");}
        while(itGrade != NULL){
            course *currentGrade = list_get(itGrade);
            itGrade = list_next(itGrade);
            if(itGrade == NULL){
                printf(" %s %d\n",currentGrade->name,currentGrade->grade);
            }else{
                printf(" %s %d,",currentGrade->name,currentGrade->grade);
            }
        }
        itStud = list_next(itStud);
    }
    return 0;
}
