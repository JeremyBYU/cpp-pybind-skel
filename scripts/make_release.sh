python scripts/manage_versions.py --bump patch
pip install .
cd src_docs && python make_docs.py && cd ..
git status

read -p "Are you sure? You wnat to add all these files " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    read -p "Enter commit message: " commmit_message
    git add .
    git commit -m "$commmit_message"
    python scripts/manage_versions.py --tag
    echo "Dont forget to push:\n \t git push origin dev --tags"
fi

