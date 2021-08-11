#!/bin/bash
VAR1=one
VAR2=two
VAR3=three
VAR4=four
VAR5=five
FILE=file
STDERR=stderr
STDOUT=stdout
STDIN=stdin

echo -n ${VAR1} > ${STDIN}
echo -n ${VAR4} > ${FILE}

export ENVVAR=${VAR3} 
./myst < ${STDIN} ${VAR2} ${VAR5} ${FILE} 2> ${STDERR} | cat > ${STDOUT}

echo "output 1"
# must be VAR1, VAR2, VAR3 on 3 lines
cat ${STDOUT} 
echo "output 2"
# must be VAR4, VAR5 on 2 lines
cat ${STDERR}
