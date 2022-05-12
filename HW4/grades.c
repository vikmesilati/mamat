#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the student struct for inserting to the grade struct
typedef struct { 
    char *name;
    int id;
    struct list *stud_grades;
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
    }
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
    list_destroy(destroy->stud_grades);
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
    }
    new->name = (char*)malloc(sizeof(char)*(strlen(given->name)+1));
    if(new->name == NULL){
	free(new->name);
        free(new);
        return -1;
    }
    strcpy(new->name,given->name);
    new->id = given->id;
    new->stud_grades = list_init(elem_clone,elem_destroy);
    struct iterator* it = list_begin(given->stud_grades);
    while(it != NULL){
        course* temp = list_get(it);
        int result = list_push_back(new->stud_grades,temp);
        if(result != 0){
            list_destroy(new->stud_grades);
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
    new->stud_grades = list_init(elem_clone,elem_destroy);
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
    course *new_grade = (course*)malloc(sizeof(course));
    if(!new_grade){
        free(new_grade);
        return -1;
    }
    new_grade->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    if(!new_grade->name){
	    element_destroy_course(new_grade);
        return -1;
    }
    strcpy(new_grade->name,name);
    new_grade->grade = grade;
    struct iterator *it_stud, *it_grade;
    it_stud = list_begin(grades->students);
    while(it_stud != NULL){
        student *current_stud = list_get(it_stud);
        if(current_stud->id == id){
            it_grade = list_begin(current_stud->stud_grades);
            while(it_grade != NULL){
                course *current_grade = list_get(it_grade);
                if(strcmp(current_grade->name,name) == 0){
		            element_destroy_course(new_grade);
                    return -1;
                }
                it_grade = list_next(it_grade);
            }
            int result = list_push_back(current_stud->stud_grades,new_grade);
	        element_destroy_course(new_grade);
            return result;
        }
        it_stud = list_next(it_stud);
    }
    element_destroy_course(new_grade);
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
    struct iterator *it_stud, *it_grade;
    it_stud = list_begin(grades->students);
    while(it_stud != NULL){
        student *current_stud = (student*)list_get(it_stud);
        if(current_stud->id == id){
            *out = malloc(sizeof(char)*(strlen(current_stud->name)+1));
            if(*out == NULL){
                return -1;
            }
            strcpy(*out, current_stud->name);
            float sum = 0;
            size_t num_of_grades = list_size(current_stud->stud_grades);
            if(num_of_grades == 0){
                return 0;
            }
            it_grade = list_begin(current_stud->stud_grades);
            while(it_grade != NULL){
                course *current_grade = list_get(it_grade);
                sum += current_grade->grade;
                it_grade = list_next(it_grade);
            }
            sum = sum / num_of_grades;
            return sum;
        }
        it_stud = list_next(it_stud);
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
    struct iterator *it_stud, *it_grade;
    it_stud = list_begin(grades->students);
    while(it_stud != NULL){
        student *current_stud = list_get(it_stud);
        if(current_stud->id == id){
            printf("%s %d:",current_stud->name,current_stud->id);
            it_grade = list_begin(current_stud->stud_grades);
            if(it_grade == NULL){
                printf("\n");
            }
            while(it_grade != NULL){
                course *current_grade = list_get(it_grade);
                it_grade = list_next(it_grade);
                if(it_grade == NULL){
                    printf(" %s %d\n",current_grade->name,current_grade->grade);
                }else{
                    printf(" %s %d,",current_grade->name,current_grade->grade);
                }
            }
            return 0;
        }
        it_stud = list_next(it_stud);
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
    struct iterator *it_stud, *it_grade;
    it_stud = list_begin(grades->students);
    while(it_stud != NULL){
        student *current_stud = list_get(it_stud);
        printf("%s %d:",current_stud->name,current_stud->id);
        it_grade = list_begin(current_stud->stud_grades);
        if(it_grade == NULL){
            printf("\n");
        }
        while(it_grade != NULL){
            course *current_grade = list_get(it_grade);
            it_grade = list_next(it_grade);
            if(it_grade == NULL){
                printf(" %s %d\n",current_grade->name,current_grade->grade);
            }else{
                printf(" %s %d,",current_grade->name,current_grade->grade);
            }
        }
        it_stud = list_next(it_stud);
    }
    return 0;
}
