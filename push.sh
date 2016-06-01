#!/bin/bash

echo "pushing to master..."
git add .
git commit -m "testing"
git push -u origin master
clear
echo "...done..."
