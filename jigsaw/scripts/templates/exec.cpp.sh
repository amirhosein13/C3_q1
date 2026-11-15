#!/bin/bash

# Customized for this task (Communication, std_io, no grader):
# the solution talks to the manager through its stdin/stdout,
# which are redirected to the FIFOs given as arguments ($1: manager->solution, $2: solution->manager).
# stdin is opened before stdout, exactly like the CMS sandbox does.

problem_name=PROBLEM_NAME_PLACE_HOLDER
sandbox=$(dirname "$0")

"${sandbox}/${problem_name}.exe" < "$1" > "$2"
