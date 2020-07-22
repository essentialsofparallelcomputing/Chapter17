FROM ubuntu:18.04 AS builder
WORKDIR /project
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -qq update && \
    apt-get -qq install -y cmake git vim gcc g++ gfortran software-properties-common wget libzip-dev \
            mpich libmpich-dev \
            openmpi-bin openmpi-doc libopenmpi-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Installing latest GCC compiler (version 10)
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get -qq update && \
    apt-get -qq install -y gcc-10 g++-10 gfortran-10 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# We are installing both OpenMPI and MPICH. We could use the update alternatives to switch between them
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 90\
                        --slave /usr/bin/g++ g++ /usr/bin/g++-10\
                        --slave /usr/bin/gfortran gfortran /usr/bin/gfortran-10\
                        --slave /usr/bin/gcov gcov /usr/bin/gcov-10

RUN apt-get -qq update && \
    apt-get -qq install -y texlive-font-utils texlive-latex-extra libpod-latex-perl gnuplot evince xpdf && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get -qq update && \
    apt-get -qq install -y libdmalloc-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN wget ftp://ftp.mcs.anl.gov/pub/darshan/releases/darshan-3.2.1.tar.gz 
RUN tar -xzvf darshan-3.2.1.tar.gz && cd darshan-3.2.1/darshan-util && ./configure && make && make install

RUN wget https://github.com/DynamoRIO/drmemory/releases/download/release_2.3.0/DrMemory-Linux-2.3.0-1.tar.gz
RUN tar -xzvf DrMemory-Linux-2.3.0-1.tar.gz

SHELL ["/bin/bash", "-c"]
ENV PATH=${PATH}:/project/DrMemory-Linux-2.3.0-1/bin64

RUN groupadd chapter17 && useradd -m -s /bin/bash -g chapter17 chapter17

WORKDIR /home/chapter17
RUN chown -R chapter17:chapter17 /home/chapter17
USER chapter17

RUN git clone --recursive https://github.com/essentialsofparallelcomputing/Chapter17.git

#RUN darshan-job-summary.pl mpi_io_block2d.darshan



WORKDIR /home/chapter17/Chapter17
#RUN make

ENTRYPOINT ["bash"]
