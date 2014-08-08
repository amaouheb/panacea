#!/bin/bash
for fichier in *.log
do
	cat $fichier >>concat.log
done
