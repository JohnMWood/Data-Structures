/***********************************************************************
* File:
*    student.h
* Authors:
*    John Wood and Etienne Beaulac (Group 3)
* Description:
*    Student information for nowServing
************************************************************************/

#ifndef STUDENT_H
#define STUDENT_H

#include <assert.h>
#include <string>
using std::string;


/***********************************************************************
* STUDENT CLASS
* Contains information about students for the nowServing implementation
************************************************************************/
class Student
{
private:
    string className;
    string name;
    int timeLeft;
    bool emergency;

public:
    Student() : timeLeft(0), emergency(0) { }
    Student(string className, string name, int timeLeft, bool emergency)
    {
        this->className = className;
        this->name = name;
        this->timeLeft = timeLeft;
        this->emergency = emergency;
    }

    bool isDone()                       { return timeLeft == 1;         }
    void decreaseTime()                 { timeLeft--;                   }

    void setClassName(string className) { this->className = className;  }
    void setName(string name)           { this->name = name;            }
    void setTimeLeft(int timeLeft)      { this->timeLeft = timeLeft;    }
    void setEmergency(bool emergency)   { this->emergency = emergency;  }

    string getClassName()    const      { return className;             }
    string getName()         const      { return name;                  }
    int getTimeLeft()        const      { return timeLeft;              }
    bool isEmergency()       const      { return emergency;             }


};

/***********************************************************************
* OSTREAM OPERATOR OVERLOAD
* "Currently serving <name> for class <className>. Time left: <timeLeft>"
* "Emergency for <name> for class <className>. Time left: <timeLeft>"
************************************************************************/
std::ostream & operator << (std::ostream & out, const Student & rhs)
{
    if (!rhs.isEmergency())
    {
        out << "\tCurrently serving " << rhs.getName() << " for class "
            << rhs.getClassName() << ". Time left: " << rhs.getTimeLeft();
    }
    else
    {
        out << "\tEmergency for " << rhs.getName() << " for class "
            << rhs.getClassName() << ". Time left: " << rhs.getTimeLeft();
    }
    return out;
}

#endif // STUDENT_H
