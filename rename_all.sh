#!/bin/bash

for aa1 in */
do
    (cd ${aa1} && pwd )
    (cd ${aa1} && rename_fix_special_chat.sh * )
done

for aa1 in */*/
do
    (cd ${aa1} && pwd )
    (cd ${aa1} && rename_fix_special_chat.sh * )
done
