#!/bin/bash

scp -i ~/.ssh/id_rsa -P9016 -r "${PWD}" user_16@129.128.215.200:~/LocksComparison/;