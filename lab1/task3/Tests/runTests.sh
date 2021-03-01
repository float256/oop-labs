#!/bin/bash

if [ "$1" == "--help" ]
then
    echo "Usage: runAllTests [TESTING_PROGRAM_NAME]"
    exit 0
fi

if [ "$#" != "1" ]
then
    echo "Incorrect number of arguments"
    exit 1
fi

readonly TESTING_PROGRAM_NAME=$1

if [ ! -f "$TESTING_PROGRAM_NAME" ]
then
    echo "File with program is not exist"
    exit 1
fi

allTestFolderNames=$(ls -d */ | cut -f1 -d'/')

readonly SUCCESSFUL_TEST_COLOR="\e[42m"
readonly FAILED_TEST_COLOR="\e[41m"
readonly NORMAL_TEST_COLOR="\e[0m"

numberOfSuccessTests=0
numberOfFailedTests=0

for currTestName in $allTestFolderNames
do
    inputFileData=$(cat "$currTestName/input.txt")
    expectedExitMessage=$(cat "${currTestName}/expectedExitMessage.txt")
    actualExitMessage=$(eval "$TESTING_PROGRAM_NAME $inputFileData")

    if [[ "$expectedExitMessage" != "$actualExitMessage" ]]
    then
        echo -e "[Test '${currTestName}']: ${FAILED_TEST_COLOR} FAILED ${NORMAL_TEST_COLOR}"
        echo "    Expected exit message: $expectedExitMessage"
        echo "    Actual exit message: $actualExitMessage"
        numberOfFailedTests=$(($numberOfFailedTests + 1))
    else
        echo -e "[Test '${currTestName}']: ${SUCCESSFUL_TEST_COLOR} SUCCESS ${NORMAL_TEST_COLOR}"
        numberOfSuccessTests=$(($numberOfSuccessTests + 1))
    fi
done

echo -e ${NORMAL_TEST_COLOR}
echo "Total:"
echo "    Success: $numberOfSuccessTests"
echo "    Failed:  $numberOfFailedTests"

exit 0
