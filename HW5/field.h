#ifndef FIELD_H
#define FIELD_H

#include "string.h"

class Field {
private:
    String pattern;
protected:
    /* Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
       matches 1.1.*.*) */
    virtual bool match_value(String value) const = 0;
public:
    Field(String pattern);
    virtual ~Field();
    virtual bool set_value(String val) = 0;
    /* Returns true iff "packet" matches "this" */
    bool match(String packet) const;
};

#endif
