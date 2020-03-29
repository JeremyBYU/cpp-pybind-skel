#!/usr/bin/env bash

set -eu

# First create new repo on GitHub and copy the SSH repo url
# Then run "./scripts/liftoff.sh" from within your local cpp-pybind-skel root directory
# and it will create your new local project repo side by side with cpp-pybind-ske directory

echo "What is the name of your new project (e.g., SimpleImageFilter)? "
read name
echo "What is the remote repo url for your new project? "
read url

mkdir ../$name
cp -R ../cpp-pybind-skel/. ../$name/
cd ../$name/
rm -rf .git
git init

git checkout -b master
git add .
git commit -m "Port from cpp-pybind-skel"
# git remote add origin $url
# git push -u origin master
