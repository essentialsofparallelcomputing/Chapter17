#!/bin/sh

for exec in stream_triad stream_triad?
do
   printf "Running $exec: " 
  ./$exec
done
