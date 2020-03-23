git rm -r --cached SqueletteProjet/compiler/antlr4-generated/
git rm -r --cached SqueletteProjet/compiler/output/
git rm -r --cached SqueletteProjet/tests/pld-test-output/

git reset HEAD

sudo git update-index --assume-unchanged SqueletteProjet/compiler/antlr4-generated/*
sudo git update-index --assume-unchanged SqueletteProjet/compiler/output/*
sudo git update-index --assume-unchanged SqueletteProjet/tests/pld-test-output/tests-Init-0_Main/*
sudo git update-index --assume-unchanged SqueletteProjet/tests/pld-test-output/tests-Init-1_fail/*


