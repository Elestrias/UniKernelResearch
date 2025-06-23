#!/bin/bash
name="a.out"
SCRIPTPATH="$(cd "$(dirname "$0")" && pwd)"

gcc $SCRIPTPATH/main.c $SCRIPTPATH/../utils.c -o $name -O2 -pthread -lm -static
ops run $name
rm $name