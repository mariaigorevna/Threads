FROM debian
RUN apt update
RUN apt install g++ python3 python -y
RUN apt install  nano -y
COPY ./FirstPart.py /home/masha/FirstPart.py
COPY ./SecondPart.cpp /home/masha/SecondPart.cpp
COPY ./FirstPart /home/masha/FirstPart
COPY ./SecondPart.py /home/masha/SecondPart.py
COPY ./lab5 /home/masha/lab5
COPY ./chek /home/masha/chek
ENTRYPOINT /bin/bash
