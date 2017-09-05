/***********************************************************************
* Implementation:
*    NOW SERVING
* Summary:
*    This will contain the implementation for nowServing() as well as any
*    other function or class implementations you may need
* Author
*    John Wood & Etienne Beaulac (Group 3)
**********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include <sstream>      // for STRINGSTREAM
#include <cstdlib>      // for atoi
#include <vector>       // for VECTOR
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "student.h"    // for STUDENT
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::stringstream;
using std::vector;
using namespace custom;

/************************************************
* NOW SERVING
* The interactive function allowing the user to
* handle help requests in the Linux lab
***********************************************/
void nowServing()
{
    // instructions
    cout << "Every prompt is one minute.  The following input is accepted:\n";
    cout << "\t<class> <name> <#minutes>    : a normal help request\n";
    cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
    cout << "\tnone                         : no new request this minute\n";
    cout << "\tfinished                     : end simulation\n";

    string input;
    int counter = 0;
    deque <Student> students;
    deque <Student> emergency_students;
    vector <string> student_info;

    cin.ignore();

    do
    {
        cout << "<" << counter << "> ";
        counter++;

        getline(cin, input);

        bool emergency = false;
        string temp_str;
        stringstream ss(input);

        while (ss >> temp_str)
        {
            if (temp_str == "!!")
                emergency = true;
            else
                student_info.push_back(temp_str);
        }

        if (student_info[0] != "none" && student_info[0] != "finished")
        {
            Student tempStudent(student_info[0], student_info[1],
                                atoi(student_info[2].c_str()), emergency);

            if (emergency)
                emergency_students.push_front(tempStudent);
            else
                students.push_back(tempStudent);
        }

        if (!students.empty())
        {
            // use the output operator from the student class
            cout << students.front() << endl;

            // isDone returns true if there is no time left
            if (students.front().isDone())
            {
                students.pop_front();

                if (!emergency_students.empty())
                    for (int i = 0; i < emergency_students.size(); i++)
                    {
                        students.push_front(emergency_students.front());
                        emergency_students.pop_front();
                    }
            }
            else
                students.front().decreaseTime();
        }

        student_info.clear();
    }
    while (input != "finished");

    cout << "End of simulation\n";
}
