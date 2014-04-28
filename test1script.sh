#!/bin/bash

echo -n "Enter the pictures file location: "
read pictures

cd $pictures/

ls | grep -e .jpg > pics.txt

cd ..

cp $pictures/pics.txt pics.txt
