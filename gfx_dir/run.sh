#!/bin/zsh

cd output
javac -cp ../lib/* ../src/**/*.java -d .
cp -R ../res .
jar xf ../lib/lwjgl-2.9.1.jar
jar cvfm zappy.jar ./MET-INF/MANIFEST.MF **/*.class res/* org/* natives/*
java -Djava.library.path=natives/macosx -jar zappy.jar 4101
