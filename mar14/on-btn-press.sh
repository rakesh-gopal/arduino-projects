#!/bin/bash

while :
do
  myIn=$(cat /dev/ttyUSB0);

  if [ -z "$myIn" ]; then
    sleep 0.5;
    continue;
  fi

  $(echo "$*") > /dev/null 2> /dev/null;
done


