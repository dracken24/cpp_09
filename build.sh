set echo on

echo  "\033[32mBuilding RPN...\n"

alias pupIn='cd'
alias popOut='cd ..'

pupIn ex02
make
popOut

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "\033[32m\nAll assemblies built successfully.\033[0m"
