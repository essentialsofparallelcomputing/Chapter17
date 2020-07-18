#!/bin/sh
docker build -t chapter17 .
docker run -it --entrypoint /bin/bash chapter17
