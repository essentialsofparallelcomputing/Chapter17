#!/bin/sh
docker build --no-cache -t chapter17 .
#docker run -it --entrypoint /bin/bash chapter17
docker build --no-cache -f Dockerfile.Ubuntu20.04 -t chapter17 .
#docker run -it --entrypoint /bin/bash chapter17
docker build --no-cache -f Dockerfile.debian -t chapter17 .
#docker run -it --entrypoint /bin/bash chapter17
