FROM ubuntu:18.04 AS builder
WORKDIR /project
RUN apt-get update -q && DEBIAN_FRONTEND=noninteractive \
    apt-get install -q -y cmake git vim gcc g++ gfortran software-properties-common wget gnupg-agent libzip-dev \
            mpich libmpich-dev \
            openmpi-bin openmpi-doc libopenmpi-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Installing latest GCC compiler (version 9)
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update -q && \
    apt-get install -q -y gcc-10 g++-10 gfortran-10 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 90\
                        --slave /usr/bin/g++ g++ /usr/bin/g++-10\
                        --slave /usr/bin/gfortran gfortran /usr/bin/gfortran-10\
                        --slave /usr/bin/gcov gcov /usr/bin/gcov-10

RUN apt-get update -q && DEBIAN_FRONTEND=noninteractive \
    apt-get install -q -y texlive-font-utils texlive-latex-extra libpod-latex-perl gnuplot && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN wget ftp://ftp.mcs.anl.gov/pub/darshan/releases/darshan-3.2.1.tar.gz 
RUN tar -xzvf darshan-3.2.1.tar.gz && cd darshan-3.2.1/darshan-util && ./configure && make && make install

SHELL ["/bin/bash", "-c"]

RUN groupadd chapter17 && useradd -m -s /bin/bash -g chapter17 chapter17

WORKDIR /home/chapter17
RUN chown -R chapter17:chapter17 /home/chapter17
USER chapter17

RUN git clone --recursive https://github.com/essentialsofparallelcomputing/Chapter17.git

#RUN darshan-job-summary.pl mpi_io_block2d.darshan



WORKDIR /home/chapter17/Chapter17
#RUN make

ENTRYPOINT ["bash"]
